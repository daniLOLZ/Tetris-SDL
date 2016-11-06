
#include "Superficie.h"

Superficie::Superficie() {
}

SDL_Surface * Superficie::onLoad(char * immagine, Uint32 supFormat) {
	SDL_Surface * temp = nullptr;
	SDL_Surface * toReturn = nullptr;

	if ((temp = SDL_LoadBMP(immagine)) == nullptr) {
		return nullptr;
	}
	toReturn = SDL_ConvertSurfaceFormat(temp, supFormat, 0);
	SDL_FreeSurface(temp);
	return toReturn;

}

bool Superficie::onDraw(SDL_Surface * destinazione, SDL_Surface * origine, int x, int y) {
	if (destinazione == nullptr || origine == nullptr) {
		return false;
	}
	SDL_Rect posizione;
	posizione.x = x;
	posizione.y = y;
	if (SDL_BlitSurface(origine, NULL, destinazione, &posizione) != 0) {
		std::cerr << "Blit Unsuccessful" << std::endl;
		return false;
	}
	return true;

}