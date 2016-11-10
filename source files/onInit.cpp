#include "../header files/Applicazione.h"



bool TetrisApp::onInit() {

	// Inizializza SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cerr << "Couldn't initialize SDL" << std::endl;
		return false;
	}




	// Richiede la grandezza desiderata della griglia
	// Lo faccio prima di inizializzare la finestra così l'unica cosa sullo schermo è il prompt
	std::cout << "\n ***** INSERISCI LA LARGHEZZA DELLA GRIGLIA ( >= 6 ) default: 10 ***** \n              ";
	std::cin >> WIDTH;
	std::cout << "\n ***** INSERISCI L'ALTEZZA DELLA GRIGLIA ( >= 6 ) default: 20 ***** \n              ";
	std::cin >> HEIGHT;
	
	
	// Inizializza tutte le parti che compongono la finestra
	if ((finestra = SDL_CreateWindow(" xd ", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_W, WINDOW_H, 
										SDL_WINDOW_SHOWN | SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_MOUSE_FOCUS | SDL_WINDOW_INPUT_GRABBED)
									) == NULL) {
		std::cerr << "Couldn't create window" << std::endl;
		return false;
	}

	// Setta il focus sulla finestra appena create invece del prompt
	SDL_RaiseWindow(finestra);

	if ((supFinestra = SDL_GetWindowSurface(finestra)) == NULL) {
		std::cerr << "Couldn't get the window surface" << std::endl;
		return false;
	}																// LOL vvvvv
	if ((theRenderer = SDL_CreateRenderer(finestra, -1, 0)) == NULL) {
		std::cerr << "Couldn't create renderer" << std::endl;
		return false;
	}



	// Crea le texture, usando la superficie di appoggio
	if ((appoggio = Superficie::onLoad("Texture/Yellow Tile.bmp", supFinestra->format->format)) == NULL) {
		std::cerr << "Couldn't load yellow tile" << std::endl;
		return false;
	}
	yellowBlock = SDL_CreateTextureFromSurface(theRenderer, appoggio);

	if ((appoggio = Superficie::onLoad("Texture/Green Tile.bmp", supFinestra->format->format)) == NULL) {
		std::cerr << "Couldn't load green tile" << std::endl;
		return false;
	}
	greenBlock = SDL_CreateTextureFromSurface(theRenderer, appoggio);

	if ((appoggio = Superficie::onLoad("Texture/Grey Tile.bmp", supFinestra->format->format)) == NULL) {
		std::cerr << "Couldn't load grey tile" << std::endl;
		return false;
	}
	greyBlock = SDL_CreateTextureFromSurface(theRenderer, appoggio);

	if ((appoggio = Superficie::onLoad("Texture/Blank Tile.bmp", supFinestra->format->format)) == NULL) {
		std::cerr << "Couldn't load black tile" << std::endl;
		return false;
	}
	blackBlock = SDL_CreateTextureFromSurface(theRenderer, appoggio);
	



	// Setta il colore di sfondo della finestra a grigio(?)
	SDL_SetRenderDrawColor(theRenderer, 64, 64, 64, 255);





	// Crea la griglia su cui si andrà a lavorare per far muovere i pezzi
	// Crea inoltre 1 griglia di supporto e una per tenere il prossimo pezzo
	TetrisApp::griglia = new char*[HEIGHT + 5]; // 3 linee in più sotto, 2 sopra. Non chiedere
	TetrisApp::supportoGriglia = new char*[HEIGHT + 5];
	TetrisApp::nextToDraw = new char*[5];

	for (int i = 0; i < HEIGHT + 5; i++) {
		TetrisApp::griglia[i] = new char[WIDTH + 4];
		TetrisApp::supportoGriglia[i] = new char[WIDTH + 4];
		// Inizializza un po' alla volta gli array a spazi vuoti
		for (int j = 0; j < WIDTH + 4; j++) {
			TetrisApp::griglia[i][j] = ' ';
			TetrisApp::supportoGriglia[i][j] = ' ';
		}
	}

	TetrisApp::nextToDraw = new char*[5];
	for (int i = 0; i < 5; i++) {	
		TetrisApp::nextToDraw[i] = new char[WIDTH];
		for (int j = 0; j < WIDTH; j++) {
			TetrisApp::nextToDraw[i][j] = ' ';
		}
	}

	_distBordoVerticale = 20;						//
	_distBordoOrizzontale = 40;						//	Valori desiderati per la distanza
	_distGriglia_Successivo = 20;					//	dai vari bordi
	_distBordo_Successivo = (WINDOW_H / 2) - 20;	//


	// Troviamo delle misure che non permettono alla griglia di uscire fuori dai bordi della finestra
	// Se la distanza che si puà utilizzare orizzontalmente è maggiore di quella che si
	// può usare verticalmente, scegliamo la seconda
	int usableY = (WINDOW_H - (_distBordoVerticale * 2) - 10*2) / HEIGHT;
	int usableX = (WINDOW_W - (_distBordoOrizzontale * 2) - 5*24) / WIDTH;
	int usableSpace; // = usableX < usableY ? usableX : usableY;
	// SI aggiustano i valori della distanza dai bordi così che la griglia risulti centrata
	if (usableX < usableY) {	
		usableSpace = usableX;
		_distBordoVerticale = (WINDOW_H - (usableSpace * HEIGHT)) / 2;
	}
	else {
		usableSpace = usableY;
		_distBordoOrizzontale = (WINDOW_W - (usableSpace * WIDTH)) / 2;
	}


	// "Inizializza" la griglia da disegnare
	SDL_Rect rectAppoggio;
	grigliaTexture = new SDL_Rect *[HEIGHT];
	for (int i = 0; i < HEIGHT; i++) {
		grigliaTexture[i] = new SDL_Rect [WIDTH];
		for (int j = 0; j < WIDTH; j++) {
			rectAppoggio.h = usableSpace; // I quadrati si rimpiccioliscono se ce ne sono di più
			rectAppoggio.w = rectAppoggio.h; // Se sono quadrati i lati sono uguali
			rectAppoggio.y = _distBordoVerticale + 20 + (i*rectAppoggio.h); //Spaziatura più la distanza fra 2 blocchi
			rectAppoggio.x = _distBordoOrizzontale + (j*rectAppoggio.w);
			/*
				Non capisco perchè non sia il contrario con rectAppoggio.x e .y			
			*/
			grigliaTexture[i][j] = rectAppoggio;/* Vediamo che quadrato metterci */
		}
	}

	nextTexture = new SDL_Rect *[5];
	for (int i = 0; i < 5; i++) {
		nextTexture[i] = new SDL_Rect[5];
		for (int j = 0; j < 5; j++) {
			rectAppoggio.h = usableSpace;
			rectAppoggio.w = rectAppoggio.h;
			rectAppoggio.y = _distBordo_Successivo + (i*rectAppoggio.h);
			rectAppoggio.x = _distBordoOrizzontale + (WIDTH * rectAppoggio.w) + _distGriglia_Successivo + j*rectAppoggio.w;
			/*
				è una versione più lunga di sopra perchè considero anche 
				lo spazio occupato dalla griglia
			*/
			nextTexture[i][j] = rectAppoggio;
		}
	}

	//Setta i valori di curPiece e nextPiece
	scelta = rand() % 7 + 1;
	curPiece.getNew(scelta, ORIGIN_X, ORIGIN_Y, griglia);
	scelta = rand() % 7 + 1;
	nextPiece.getNew(scelta, ORIGIN_X, ORIGIN_Y, nextToDraw);
	
	TetrisApp::onRender();


	SDL_FreeSurface(appoggio);

	scriviIstruzioni();

	return true;
}