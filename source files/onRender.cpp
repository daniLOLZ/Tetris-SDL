#include "../header files/Applicazione.h"

void TetrisApp::onRender() {	

	SDL_RenderClear(theRenderer);
	
	// Disegna la griglia blocchetto per blocchetto
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 2; j < WIDTH + 2; j++) {
			switch (griglia[i][j]) {
			case BLOCK_TILE:
				textureAppoggio = greyBlock;
				break;
			case ACTIVE_BLOCK_TILE:
				textureAppoggio = yellowBlock;
				break;
			default:
				textureAppoggio = blackBlock;
				break;
			}
			SDL_RenderCopy(theRenderer, textureAppoggio, NULL, &grigliaTexture[i][j-2]);
		}
	}
	
	//Disegna il pezzo successivo a lato
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if(nextToDraw[i][j + (WIDTH/2) ] == ACTIVE_BLOCK_TILE) {
				SDL_RenderCopy(theRenderer, yellowBlock, NULL, &nextTexture[i][j]);
			}
		}
	}
	
	SDL_RenderPresent(theRenderer);
}