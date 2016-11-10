#include <iostream>
#include "../header files/Superficie.h"
#include "../header files/Applicazione.h"


int main(int argc, char* argv[]) {

	TetrisApp Tetris;

	return Tetris.onExecute();

}

/*
		IUSFUL STAF
	
	SDL_GetMouseState(&rectToOverwrite.x, &rectToOverwrite.y);


	SDL_RenderClear(theRenderer);
	SDL_RenderCopy(theRenderer, textToDraw, &sourceRect, &destRect);
	SDL_RenderPresent(theRenderer);

	http://stackoverflow.com/questions/1410563/what-is-the-difference-between-a-definition-and-a-declaration
	 ^^^^^ Sacro Graal delle differenze fra definizioni e dichiarazioni

	// Dichiarazione: Crei un modello per una sola variabile/funzione/classe

	Compilatore: "Ok, ora che l'hai dichiarato posso capire che esiste una variabile/funzione/classe
				   fatta in quel modo! >:3 "

	// Definizione: Fai si che quel modello possa essere utilizzato dal codice sorgente

	Linker: "Ok, ora che l'hai definito posso far usare al tuo programma questa 
			  variabile/funzione/classe ^^ "



			  Clockwise spiral rule for C / C++
		 http://c-faq.com/decl/spiral.anderson.html


							Utilizzo di extern
	http://stackoverflow.com/questions/10422034/when-to-use-extern-in-c
									e
					 http://www.keil.com/forum/21633/

*/