
#ifndef _PIECE_H_
	#define _PIECE_H_

#define ACTIVE_BLOCK_TILE 'O'
#define BLOCK_TILE 'X'


class Piece {

public:

	// Crea il pezzo .-. (a.k.a. Constructor) Praticamente mai utilizzzato
	Piece::Piece(int type = 1, int orX = 0, int orY = 0);
	// Destructor
	Piece::~Piece();

	void getNew(int type, int orX, int orY, char** tipoGriglia);
	// Ciò che veramente crea il pezzo
//	void getNew(int type, int orX, int orY, char** tipoGriglia);
	// Disegna il pezzo successivo sulla griglia apposita
	void fillNewPiece();
	// Disegna il pezzo sulla griglia e niente di più
	void draw();

	bool moveDown();
	void moveLeft();
	void moveRight();
	void rotate();

private:

	int _boundH;
	int _boundW;
	int _originX;
	int _originY;
	int _rotation; // In che fase della rotazione si trova (1 - 2 - 3 - 4)
	int _type;
	int _app; // Aiuto generale

	// Controlla se il posizionamento del pezzo va oltre i limiti
	bool _checkInRange(int deltaX, int deltaY);
	bool _checkNotColliding(int deltaX, int deltaY);
	bool _checkGoodRotation();
	// Cancella il pezzo nella vecchia posizione
	void _erasePiece(char** &tipoGriglia);
	// Per evitare di riscirvere lo switch nei 4 movimenti
	void _whatToDraw(char blockTile, char ** tipoGriglia);
	// Disegna "tutti" i tipi di pezzetti
	void _drawSquare(char blockTile, char ** tipoGriglia);
	void _drawT(char blockTile, char ** tipoGriglia);
	void _drawL(char blockTile, char ** tipoGriglia);
	void _drawReverseL(char blockTile, char ** tipoGriglia);
	void _drawLine(char blockTile, char ** tipoGriglia);
	void _drawS(char blockTile, char ** tipoGriglia);
	void _drawReverseS(char blockTile, char ** tipoGriglia);

};
#endif // !_PEZZO_H_
