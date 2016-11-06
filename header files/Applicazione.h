#ifndef _TETRIS_H_
#define _TETRIS_H_

#include <iostream>
#include <SDL.h>
#include "Superficie.h"
#include "Pezzo.h"
#include <time.h>
#include <conio.h>

// #define HEIGHT 20  // Per funzionare, HEIGHT deve essere >= 6
// #define WIDTH 20  // Per funzionare, WIDTH deve essere >= 6
#define KEY_UP 72 
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define NUMPAD_0 82
#define KEY_Z 122
#define KEY_X 120
#define ESCAPE 27
#define ORIGIN_X 0
#define ORIGIN_Y (WIDTH/2)

//SDL Related variables
#define WINDOW_W 640
#define WINDOW_H 480
#define TICKS_PER_DROP 1000 // Ogni quanti tick il pezzo DEVE scendere di uno

extern int HEIGHT;
extern int WIDTH;

extern Piece curPiece;
extern Piece nextPiece;
extern Piece helPiece;

extern int wtf;
extern int test;

// Con extern, i pointer non servono neanche più,
// perchè tutti fanno riferimento esclusivamente a questo simbolo

/*

					// Spiegazione nel caso (certo) che mi scordi che succede

	Se qua avessi messo 
		extern int wtf = 5;
		extern int test = 5;
	avrei dichiarato E definito la stessa variabile in un unico punto.
	Il problema è che, sì sono passato per tutte le fasi per creare una variabile
	usata da più file, però, non avendola definita in un punto dove tutti possano vederla,
	(Applicazione.cpp) si crea un errore di simbolo non trovato.

					// Procedimentamento (circa)
	[	Trovo la dichiarazione nell'header Applicazione.h
	[	Vado a controllare se vi è una definizione in Applicazione.cpp
	[	Non la trovo
	[	*** Il simbolo non è definito ***

	Se aggiungo ad Applicazione.cpp, mantendo la sintassi di sopra quella che dovrebbe
	essere la definizione, si crea una duplice definizione, perchè, assegnando un valore
	in Applicazione.h, l'ho già definita

	// Procedimentamento (circa)
	[	Trovo la dichiarazione nell'header Applicazione.h
	[	Vado a controllare se vi è una definizione in Applicazione.cpp
	[	La trovo
	[	Ritorno alla dichiarazione, per finalizzare il controllo
	[	Noto che dopo la dichiarazione del simbolo c'è anche un'altra definizione
	[	*** Il simbolo è definito molteplici volte ***



*/

enum tipoPezzo { QUADRATO = 1, T, L, REVERSEL, LINEA, S, REVERSES };

class TetrisApp {

public:

	static char ** griglia; // Dichiarazione
	static char ** supportoGriglia; //
	static char ** nextToDraw; // 

	int direction;  // Lo spostamento del pezzo
	int scelta;
	int linesCompleted = 0;
	int ultimeLinee = 0;
	int Score = 0;
	int numMoveDown = 0;
	bool continua = true;
	bool canDescend = true;
	bool gameLost = false;
	bool canExit = false;

	TetrisApp();
	int onExecute();

	bool onInit();

	void onEvent(SDL_Event *evento);
	
	void onLoop();
	
	void onRender();

	void onCleanup();

	void scriviIstruzioni();
	void capFramerate(Uint32 start_tick);

	SDL_Surface* getSurface();

private:
	
	bool _running = true;
	int _distBordoVerticale;
	int _distBordoOrizzontale;
	int _distGriglia_Successivo;
	int _distBordo_Successivo;
	int _previousSecond = 0; // In realtà non è per forza un secondo :/
	unsigned long long _myTicks = 0; // Vedi onLoop.cpp

	Uint32 start_tick;
	SDL_Window *finestra = nullptr;
	SDL_Surface * supFinestra = nullptr;
	SDL_Surface * appoggio = nullptr;
	SDL_Texture * textureAppoggio = nullptr;
	SDL_Rect ** grigliaTexture; // Dove andrà a essere disegnato ogni blocchetto
	SDL_Rect ** nextTexture; // /	/	/	/	/	/	/	/	/	/	/	/	 del prossimo pezzo
	SDL_Texture * yellowBlock = nullptr;
	SDL_Texture * greenBlock = nullptr;
	SDL_Texture * greyBlock = nullptr;
	SDL_Texture * blackBlock = nullptr;
	SDL_Texture * testImmagine = nullptr;
	SDL_Texture * textToDraw = nullptr;
	SDL_Renderer * theRenderer = nullptr;
/*	Uint32 giallo;
	Uint32 verde;
	Uint32 grigio;
*/

};


#endif // 0
