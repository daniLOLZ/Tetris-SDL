#include "../header files/Applicazione.h"

void TetrisApp::onEvent(SDL_Event *evento) {
	if (evento->type == SDL_QUIT) {
		_running = false;
	}
/*	if (evento.type == SDL_KEYDOWN) {
		switch (evento.key.keysym.sym)
		{

		case SDLK_f: 
			std::cout << "\n xd";
			textToDraw = testImmagine;
			break;
		case SDLK_1:
			std::cout << "\n gialloxd";
			textToDraw = yellowBlock;
			break;
		default:
			textToDraw = nullptr;
			break;
		}
	}
	if (evento.type == SDL_MOUSEMOTION) {
		std::cout << "Mi sto muovendo 8D";
		SDL_GetMouseState(&destRect.x, &destRect.y); // Mi prende la posizione del mouse
		destRect.x -= 10;	// La altero un po' qui sotto
		destRect.y -= 10;	// ------
		destRect.h = 10;
		destRect.w = 10;
		textToDraw = greenBlock;
	}
*/

	if (evento->type == SDL_KEYDOWN) {

		switch (evento->key.keysym.sym)
		{
		case SDLK_RIGHT:
			curPiece.moveRight();
			break;
		case SDLK_LEFT:
			curPiece.moveLeft();
			break;
		case SDLK_DOWN:
			if (!curPiece.moveDown()) canDescend = false;
			else {
				numMoveDown++;
				Score += 2;
			}
			break;
		case SDLK_UP:
			curPiece.rotate();
			break;
		case SDLK_z:
			curPiece.rotate();
			break;
		case SDLK_x:
			while (curPiece.moveDown()) {
				Score += 4;
				numMoveDown++;
			}
			SDL_PumpEvents();
			SDL_FlushEvent(SDL_KEYDOWN);
			canDescend = false;
			break;
		case SDLK_RETURN:
			if (!gameLost) {
				while (curPiece.moveDown()) {
					Score += 4;
					numMoveDown++;
				}
				canDescend = false;
				SDL_PumpEvents();
				SDL_FlushEvent(SDL_KEYDOWN);
			}
			break;
		case SDLK_ESCAPE:
			_running = false;
			break;
		default:
			break;
		}
	}
}