#include "../header files/Applicazione.h"

Piece::Piece(int type, int orX, int orY) {
	this->_type = type;
	this->_originX = orX;
	this->_originY = orY;

};

Piece::~Piece() {
	_whatToDraw(BLOCK_TILE, TetrisApp::griglia);
}

void Piece::getNew(int type, int orX, int orY, char** tipoGriglia) {
	_type = type;
	_originX = orX;
	_originY = orY;
	_boundH = 5;
	_boundW = 5;
	srand(time(NULL));
	_rotation = rand() % 4 + 1;
	char ** ptr = tipoGriglia;

	_whatToDraw(ACTIVE_BLOCK_TILE, ptr);

}

void Piece::fillNewPiece() {
	/* Per far si che venga disegnato agli indirizzi corretti, devo modificare
	temporaneamente _originX e _originY mettendoli a 0, così che si possa
	disegnare sulla griglia "nextToDraw", poi verranno riportati al loro stato
	iniziale
	*/
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			TetrisApp::nextToDraw[i][j] = ' ';
		}
	}

	int tempX = _originX, tempY = _originY;
	this->_originX = 0;
	this->_originY = 0;
	_whatToDraw(ACTIVE_BLOCK_TILE, TetrisApp::nextToDraw);

	// Li faccio tornare allo stato iniziale
	this->_originX = tempX;
	this->_originY = tempY;
};

void Piece::draw() {
	_whatToDraw(ACTIVE_BLOCK_TILE, TetrisApp::griglia);
}

bool Piece::moveDown() {

	if (_checkInRange(1, 0)) {
		this->_originX++;
		if (_checkNotColliding(1, 0)) {
			this->_originX--;
			_erasePiece(TetrisApp::griglia);
			this->_originX++;
			_whatToDraw(ACTIVE_BLOCK_TILE, TetrisApp::griglia);
		}
		else {
			this->_originX--; // ...idem vvv
			return false;
		}
	}
	else {
		return false;
	}  // ...and nothing happens
	return true;
}

void Piece::moveLeft() {
	if (_checkInRange(0, -1)) {
		this->_originY--;
		if (_checkNotColliding(0, -1)) {
			this->_originY++;
			_erasePiece(TetrisApp::griglia);
			this->_originY--;
			_whatToDraw(ACTIVE_BLOCK_TILE, TetrisApp::griglia);
		}
		else this->_originY++; // and nothing happens...
	}
}

void Piece::moveRight() {
	if (_checkInRange(0, 1)) {
		this->_originY++;
		if (_checkNotColliding(0, 1)) {
			this->_originY--;
			_erasePiece(TetrisApp::griglia);
			this->_originY++;
			_whatToDraw(ACTIVE_BLOCK_TILE, TetrisApp::griglia);
		}
		else this->_originY--; // ...and nothing happens
	}
}

void Piece::rotate() {
	if (_type == 1) return; // Se è un quadrato è inutile ruotarlo
	_erasePiece(TetrisApp::griglia);
	this->_rotation = this->_rotation % 4;
	this->_rotation = this->_rotation + 1;
	if (!_checkGoodRotation()) {
		this->_rotation = this->_rotation % 4; // Torna alla rotazione iniziale e annulla la rotazione			
		this->_rotation = this->_rotation + 3;
		if (this->_rotation > 4) this->_rotation -= 4;

	}
	_whatToDraw(ACTIVE_BLOCK_TILE, TetrisApp::griglia); // Anche se non ruota, siccome ho cancellato il pezzo
														// sopra ora lo ridisegno
}



// Private funcs

// Controlla se il posizionamento del pezzo va oltre i limiti
bool Piece::_checkInRange(int deltaX, int deltaY) {
	for (int i = 0; i < this->_boundH; i++) {
		for (int j = 0; j < this->_boundW; j++) {
			if (TetrisApp::griglia[_originX + i][_originY + j] == ACTIVE_BLOCK_TILE) {
				if (((this->_originX + i + deltaX) >= HEIGHT) || ((this->_originX + i + deltaX) < 0) ||
					((this->_originY + j + deltaY) - 2 >= WIDTH) || ((this->_originY + j + deltaY) - 2 < 0)) return false;
			}
		}
	}
	return true;
}

bool Piece::_checkNotColliding(int deltaX, int deltaY) {
	// Questi parametri controllano per ogni movimento (giù, destra, sinistra) 
	// se il pezzo andrà a collidere con qualcos'altro quando andrà
	// nella nuova posizione
	for (int i = 0; i < this->_boundH; i++) {
		for (int j = 0; j < this->_boundW; j++) {
			if (TetrisApp::griglia[_originX + i][_originY + j] == ACTIVE_BLOCK_TILE) {
				if (TetrisApp::griglia[_originX + i + deltaX][_originY + j + deltaY] != ' ' &&
					TetrisApp::griglia[_originX + i + deltaX][_originY + j + deltaY] != ACTIVE_BLOCK_TILE)
					return false; // Vedi un po'
			}
		}
	}
	return true;
}

bool Piece::_checkGoodRotation() {

	_whatToDraw(ACTIVE_BLOCK_TILE, TetrisApp::supportoGriglia);

	bool toReturn = true;
	// Controlla che non interagisce con pezzi già sistemati
	for (int i = 0; i < this->_boundH; i++) {
		for (int j = 0; j < this->_boundW; j++) {
			if (TetrisApp::supportoGriglia[_originX + i][_originY + j] == ACTIVE_BLOCK_TILE) { // Se consideriamo effettivamente un blocco disegnato
				if (TetrisApp::griglia[_originX + i][_originY + j] == BLOCK_TILE) { // Se incontra un pezzo già fissato, non lo ruotiamo
					toReturn = false;
					i = this->_boundH;
					j = this->_boundW;
				}
			}
		}
	}

	// Controlla che non si incastri nei muri
	for (int i = 0; i < this->_boundH; i++) {
		for (int j = 0; j < this->_boundW; j++) {
			if (TetrisApp::supportoGriglia[_originX + i][_originY + j] == ACTIVE_BLOCK_TILE) {
				if ((this->_originY + j >= WIDTH + 2 || this->_originY + j < 2) || // Se un blocco si trova nella parte di griglia oltre ai limiti laterali
					(this->_originX + i >= HEIGHT)) {	// o se si trova al di sotto del limite massimo
					toReturn = false;
					i = this->_boundH;
					j = this->_boundW;
				}
			}
		}
	}
	// Pulisci la griglia di supporto
	_erasePiece(TetrisApp::supportoGriglia);
	return toReturn;
};

// Cancella il pezzo nella vecchia posizione
void Piece::_erasePiece(char** &tipoGriglia) {
	for (int i = 0; i < this->_boundH; i++) {
		for (int j = 0; j < this->_boundW; j++) {
			if (tipoGriglia[_originX + i][_originY + j] == ACTIVE_BLOCK_TILE)
				tipoGriglia[_originX + i][_originY + j] = ' ';
		}
	}
}

void Piece::_whatToDraw(char blockTile, char **tipoGriglia) {

	switch (_type) {
	case 1:
		_drawSquare(blockTile, tipoGriglia);
		break;
	case 2:
		_drawT(blockTile, tipoGriglia);
		break;
	case 3:
		_drawL(blockTile, tipoGriglia);
		break;
	case 4:
		_drawReverseL(blockTile, tipoGriglia);
		break;
	case 5:
		_drawLine(blockTile, tipoGriglia);
		break;
	case 6:
		_drawS(blockTile, tipoGriglia);
		break;
	case 7:
		_drawReverseS(blockTile, tipoGriglia);
		break;
	default:
		std::cout << "Couldn't find piece with index " << _type << std::endl;
		break;
	}
}

void Piece::_drawSquare(char blockTile, char ** tipoGriglia) {
	tipoGriglia[_originX + 2][_originY + 2] = blockTile;
	tipoGriglia[_originX + 2][_originY + 3] = blockTile;
	tipoGriglia[_originX + 3][_originY + 2] = blockTile;
	tipoGriglia[_originX + 3][_originY + 3] = blockTile;
}
void Piece::_drawT(char blockTile, char ** tipoGriglia) {
	switch (_rotation) {
	default:
		break;
	case 1: { // Punta in alto
		tipoGriglia[_originX + 2][_originY + 2] = blockTile;
		tipoGriglia[_originX + 1][_originY + 2] = blockTile;
		tipoGriglia[_originX + 2][_originY + 1] = blockTile;
		tipoGriglia[_originX + 2][_originY + 3] = blockTile;
		break;
	}
	case 2: { // Punta a destra
		tipoGriglia[_originX + 2][_originY + 2] = blockTile;
		tipoGriglia[_originX + 1][_originY + 2] = blockTile;
		tipoGriglia[_originX + 3][_originY + 2] = blockTile;
		tipoGriglia[_originX + 2][_originY + 3] = blockTile;
		break;
	}
	case 3: { // Punta in basso
		tipoGriglia[_originX + 2][_originY + 2] = blockTile;
		tipoGriglia[_originX + 2][_originY + 1] = blockTile;
		tipoGriglia[_originX + 2][_originY + 3] = blockTile;
		tipoGriglia[_originX + 3][_originY + 2] = blockTile;
		break;
	}
	case 4: { // Punta a sinistra
		tipoGriglia[_originX + 2][_originY + 2] = blockTile;
		tipoGriglia[_originX + 1][_originY + 2] = blockTile;
		tipoGriglia[_originX + 2][_originY + 1] = blockTile;
		tipoGriglia[_originX + 3][_originY + 2] = blockTile;
		break;
	}
	}
}
void Piece::_drawL(char blockTile, char ** tipoGriglia) {
	switch (_rotation) {
	default:
		break;
	case 1: {
		tipoGriglia[_originX + 2][_originY + 2] = blockTile;
		tipoGriglia[_originX + 1][_originY + 2] = blockTile;
		tipoGriglia[_originX + 3][_originY + 2] = blockTile;
		tipoGriglia[_originX + 3][_originY + 3] = blockTile;
		break;
	}
	case 2: {
		tipoGriglia[_originX + 2][_originY + 2] = blockTile;
		tipoGriglia[_originX + 2][_originY + 3] = blockTile;
		tipoGriglia[_originX + 2][_originY + 1] = blockTile;
		tipoGriglia[_originX + 3][_originY + 1] = blockTile;
		break;
	}
	case 3: {
		tipoGriglia[_originX + 2][_originY + 2] = blockTile;
		tipoGriglia[_originX + 1][_originY + 1] = blockTile;
		tipoGriglia[_originX + 1][_originY + 2] = blockTile;
		tipoGriglia[_originX + 3][_originY + 2] = blockTile;
		break;
	}
	case 4: {
		tipoGriglia[_originX + 2][_originY + 2] = blockTile;
		tipoGriglia[_originX + 1][_originY + 3] = blockTile;
		tipoGriglia[_originX + 2][_originY + 1] = blockTile;
		tipoGriglia[_originX + 2][_originY + 3] = blockTile;
		break;
	}
	}
}
void Piece::_drawReverseL(char blockTile, char ** tipoGriglia) {
	switch (_rotation) {
	default:
		break;
	case 1: {
		tipoGriglia[_originX + 2][_originY + 2] = blockTile;
		tipoGriglia[_originX + 1][_originY + 2] = blockTile;
		tipoGriglia[_originX + 3][_originY + 1] = blockTile;
		tipoGriglia[_originX + 3][_originY + 2] = blockTile;
		break;
	}
	case 2: {
		tipoGriglia[_originX + 2][_originY + 2] = blockTile;
		tipoGriglia[_originX + 2][_originY + 1] = blockTile;
		tipoGriglia[_originX + 1][_originY + 1] = blockTile;
		tipoGriglia[_originX + 2][_originY + 3] = blockTile;
		break;
	}
	case 3: {
		tipoGriglia[_originX + 2][_originY + 2] = blockTile;
		tipoGriglia[_originX + 1][_originY + 2] = blockTile;
		tipoGriglia[_originX + 3][_originY + 2] = blockTile;
		tipoGriglia[_originX + 1][_originY + 3] = blockTile;
		break;
	}
	case 4: {
		tipoGriglia[_originX + 2][_originY + 2] = blockTile;
		tipoGriglia[_originX + 2][_originY + 1] = blockTile;
		tipoGriglia[_originX + 2][_originY + 3] = blockTile;
		tipoGriglia[_originX + 3][_originY + 3] = blockTile;
		break;
	}
	}
}
void Piece::_drawLine(char blockTile, char ** tipoGriglia) {
	switch (_rotation) {
	default:
		break;
	case 1: {
		tipoGriglia[_originX + 1][_originY + 2] = blockTile;
		tipoGriglia[_originX + 2][_originY + 2] = blockTile;
		tipoGriglia[_originX + 3][_originY + 2] = blockTile;
		tipoGriglia[_originX + 4][_originY + 2] = blockTile;
		break;
	}
	case 2: {
		tipoGriglia[_originX + 2][_originY + 0] = blockTile;
		tipoGriglia[_originX + 2][_originY + 1] = blockTile;
		tipoGriglia[_originX + 2][_originY + 2] = blockTile;
		tipoGriglia[_originX + 2][_originY + 3] = blockTile;
		break;
	}
	case 3: {
		tipoGriglia[_originX + 0][_originY + 2] = blockTile;
		tipoGriglia[_originX + 1][_originY + 2] = blockTile;
		tipoGriglia[_originX + 2][_originY + 2] = blockTile;
		tipoGriglia[_originX + 3][_originY + 2] = blockTile;
		break;
	}
	case 4: {
		tipoGriglia[_originX + 2][_originY + 1] = blockTile;
		tipoGriglia[_originX + 2][_originY + 2] = blockTile;
		tipoGriglia[_originX + 2][_originY + 3] = blockTile;
		tipoGriglia[_originX + 2][_originY + 4] = blockTile;
		break;
	}
	}
}
void Piece::_drawS(char blockTile, char ** tipoGriglia) {
	switch (_rotation) {
	default:
		break;
	case 1: {
		tipoGriglia[_originX + 2][_originY + 2] = blockTile;
		tipoGriglia[_originX + 2][_originY + 3] = blockTile;
		tipoGriglia[_originX + 3][_originY + 1] = blockTile;
		tipoGriglia[_originX + 3][_originY + 2] = blockTile;
		break;
	}
	case 2: {
		tipoGriglia[_originX + 1][_originY + 1] = blockTile;
		tipoGriglia[_originX + 2][_originY + 1] = blockTile;
		tipoGriglia[_originX + 2][_originY + 2] = blockTile;
		tipoGriglia[_originX + 3][_originY + 2] = blockTile;
		break;
	}
	case 3: {
		tipoGriglia[_originX + 1][_originY + 2] = blockTile;
		tipoGriglia[_originX + 1][_originY + 3] = blockTile;
		tipoGriglia[_originX + 2][_originY + 2] = blockTile;
		tipoGriglia[_originX + 2][_originY + 1] = blockTile;
		break;
	}
	case 4: {
		tipoGriglia[_originX + 1][_originY + 2] = blockTile;
		tipoGriglia[_originX + 2][_originY + 2] = blockTile;
		tipoGriglia[_originX + 2][_originY + 3] = blockTile;
		tipoGriglia[_originX + 3][_originY + 3] = blockTile;
		break;
	}
	}
}
void Piece::_drawReverseS(char blockTile, char ** tipoGriglia) {
	switch (_rotation) {
	default:
		break;
	case 1: {
		tipoGriglia[_originX + 2][_originY + 1] = blockTile;
		tipoGriglia[_originX + 2][_originY + 2] = blockTile;
		tipoGriglia[_originX + 3][_originY + 2] = blockTile;
		tipoGriglia[_originX + 3][_originY + 3] = blockTile;
		break;
	}
	case 2: {
		tipoGriglia[_originX + 1][_originY + 2] = blockTile;
		tipoGriglia[_originX + 2][_originY + 2] = blockTile;
		tipoGriglia[_originX + 2][_originY + 1] = blockTile;
		tipoGriglia[_originX + 3][_originY + 1] = blockTile;
		break;
	}
	case 3: {
		tipoGriglia[_originX + 1][_originY + 1] = blockTile;
		tipoGriglia[_originX + 2][_originY + 2] = blockTile;
		tipoGriglia[_originX + 1][_originY + 2] = blockTile;
		tipoGriglia[_originX + 2][_originY + 3] = blockTile;
		break;
	}
	case 4: {
		tipoGriglia[_originX + 1][_originY + 3] = blockTile;
		tipoGriglia[_originX + 2][_originY + 3] = blockTile;
		tipoGriglia[_originX + 2][_originY + 2] = blockTile;
		tipoGriglia[_originX + 3][_originY + 2] = blockTile;
		break;
	}
	}
}

