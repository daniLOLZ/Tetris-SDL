#ifndef _SUPERFICIE_H_
#define _SUPERFICIE_H_

#include <SDL.h>
#include <iostream>

class Superficie {

public:

	Superficie();

	static SDL_Surface * onLoad(char* immagine, Uint32 supFormat);

	static bool onDraw(SDL_Surface * destinazione, SDL_Surface * origine, int x, int y);

private:

};


#endif // !_SUPERFICIE_H_

