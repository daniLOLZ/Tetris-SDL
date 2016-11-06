#include "Applicazione.h"

int checkLines() {
	// Check which lines got completed
	bool lineaCompleta;
	int count = 0;
	for (int i = HEIGHT - 1; i >= 2; i--) {
		lineaCompleta = true;
		for (int j = 2; j < WIDTH + 2; j++) {
			if (TetrisApp::griglia[i][j] == ' ') {
				lineaCompleta = false;
				j = WIDTH + 2;

			}
		}
		if (lineaCompleta) {
			for (int k = i; k > 0; k--) {
				for (int l = 2; l <= WIDTH + 2; l++) {
					TetrisApp::griglia[k][l] = TetrisApp::griglia[k - 1][l];
				}
			}
			for (int l = 2; l < WIDTH + 2; l++) {
				TetrisApp::griglia[0][l] = ' ';
			}
			i++;
			count++;
		}
	}
	return count;
}

void TetrisApp::onLoop() {

	if (!canDescend) {
		curPiece.~Piece();
		std::cout << " Nuovo Pezzo \n\n :D\n";
		if (numMoveDown == 0) { // Se non è riuscito a scendere mai, termina il programma
			continua = false;
			gameLost = true;
			_running = false;
		}
		ultimeLinee = checkLines();
		linesCompleted += ultimeLinee;
		Score += (ultimeLinee*ultimeLinee * 100);
		curPiece = nextPiece;
		srand(time(NULL));
		scelta = rand() % 7 + 1;
		// Resetta nextToDraw
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < WIDTH; j++) {
				nextToDraw[i][j] = ' ';
			}
		}
		nextPiece.getNew(scelta, ORIGIN_X, ORIGIN_Y, nextToDraw);
		numMoveDown = 0;
		canDescend = true;
		curPiece.draw();
	}
		// Ogni (TICKS_PER_DROP / 1000) secondi il pezzo scende
	_myTicks = SDL_GetTicks();
	if (_myTicks / TICKS_PER_DROP > _previousSecond) {
		// Aggiorniamo _previousSecond
		_previousSecond = _myTicks / TICKS_PER_DROP;
		if (!curPiece.moveDown()) canDescend = false;
		else {
			numMoveDown++;
			Score += 2;
		}
	}

}