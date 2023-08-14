#ifndef StatusScreen_h
#define StatusScreen_h

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include "main.h"

void InitStartScreen(GameO *gameO);
void StartScreen(GameO *gameO);
void DestroyStartScreen(GameO *gameO);

void InitFailScreen(GameO *gameO);
void FailScreen(GameO *gameO);
void DestroyFailScreen(GameO *gameO);

void InitWinScreen(GameO *gameO);
void WinScreen(GameO *gameO);
void DestroyWinScreen(GameO *gameO);
#endif