#include "../header files/Applicazione.h"

void TetrisApp::onCleanup() {

	SDL_FreeSurface(supFinestra);
	SDL_DestroyWindow(finestra);
	SDL_DestroyRenderer(theRenderer);

	supFinestra = nullptr;
	finestra = nullptr;
	theRenderer = nullptr;

	SDL_Quit();
}