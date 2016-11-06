#include <iostream>
#include "Applicazione.h"

#define FPS 30
// *** DEFINIZIONE DELLE VARIABILI DICHIARATE IN Applicazione.h ***
char ** TetrisApp::griglia;
char ** TetrisApp::supportoGriglia; 
char ** TetrisApp::nextToDraw; 

Piece curPiece;
Piece nextPiece;
Piece helPiece;

int wtf;
int test;

int WIDTH;
int HEIGHT;
/// *** FINE DEFINIZIONE *** 


TetrisApp::TetrisApp() {
	_running = true;
}

SDL_Surface* TetrisApp::getSurface() {

	return this->supFinestra;

}


int TetrisApp::onExecute() {

	if (!onInit()) {
		return -1;
	}

	SDL_Event evento;

	while (_running) {
		start_tick = SDL_GetTicks();
		while (SDL_PollEvent(&evento)) {
			onEvent(&evento);
		}
		onLoop();
		onRender();

		capFramerate(start_tick);
	}
	if (this->gameLost) {
		for (int i = 0; i < 25; i++) {
			std::cout << std::endl << " hai perso xd" << std::endl;
		}
	}
	onCleanup();

	return 0;

}

void TetrisApp::capFramerate(Uint32 start_tick) {
	if (1000 / FPS > SDL_GetTicks() - start_tick) {		// Se il tempo minimo che ci dovrebbe mettere un frame
														// è maggiore
														// del tempo che ci è stato messo
		SDL_Delay(1000 / FPS - (SDL_GetTicks() - start_tick));		// Aspetta un tempo pari
				//Tempo giusto		//Tempo trascorso				// al tempo rimanente fino al minimo sindacale
	}
}

void TetrisApp::scriviIstruzioni() {

	std::cout << " Comandi :" << std::endl << std::endl;
	std::cout << " Z o Freccia su: ruota il pezzo \n X o Invio: fai cadere il pezzo" << std::endl;
	std::cout << " Freccia giu': accelera la caduta del pezzo " << std::endl;
	std::cout << " Esc: chiudi l'applicazione " << std::endl;
	std::cout << std::endl;

}