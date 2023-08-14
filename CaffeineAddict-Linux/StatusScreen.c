#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include "main.h"

void InitStartScreen(GameO *gameO)
{
    SDL_Color white = {255,255,255,255};
    SDL_Surface *baseSurface = TTF_RenderText_Blended(gameO->font, "Kill all of them!", white);
    SDL_Surface *hpSurface = TTF_RenderText_Blended(gameO->font, "Start hp: 100", white);
    SDL_Surface *maxBulletSurface = TTF_RenderText_Blended(gameO->font, "Max bullets: 16", white);
    gameO->startScreenInfo.base = SDL_CreateTextureFromSurface(gameO->renderer, baseSurface);
    gameO->startScreenInfo.hp = SDL_CreateTextureFromSurface(gameO->renderer, hpSurface);
    gameO->startScreenInfo.maxBullets = SDL_CreateTextureFromSurface(gameO->renderer, maxBulletSurface);
    gameO->startScreenInfo.baseW = baseSurface->w;
    gameO->startScreenInfo.baseH = baseSurface->h;
    gameO->startScreenInfo.hpW = hpSurface->w;
    gameO->startScreenInfo.hpH = hpSurface->h;
    gameO->startScreenInfo.maxBulletsW = maxBulletSurface->w;
    gameO->startScreenInfo.maxBulletsH = maxBulletSurface->h;
    SDL_FreeSurface(baseSurface);
    SDL_FreeSurface(hpSurface);
    SDL_FreeSurface(maxBulletSurface);
}

void StartScreen(GameO *gameO)
{
    SDL_Rect BaseRect = {800, 400, gameO->startScreenInfo.baseW, gameO->startScreenInfo.baseH};
    SDL_Rect hpRect = {800, 450, gameO->startScreenInfo.hpW, gameO->startScreenInfo.hpH};
    SDL_Rect maxBulletsRect = {800, 500, gameO->startScreenInfo.maxBulletsW, gameO->startScreenInfo.maxBulletsH};
    SDL_SetRenderDrawColor(gameO->renderer, 0,0,0,255); // draw color black
    SDL_RenderClear(gameO->renderer); // clear screen to black
    SDL_RenderCopy(gameO->renderer, gameO->startScreenInfo.base, NULL, &BaseRect);
    SDL_RenderCopy(gameO->renderer, gameO->startScreenInfo.hp, NULL, &hpRect);
    SDL_RenderCopy(gameO->renderer, gameO->startScreenInfo.maxBullets, NULL, &maxBulletsRect);
    SDL_RenderPresent(gameO->renderer);
}

void DestroyStartScreen(GameO *gameO)
{
    SDL_DestroyTexture(gameO->startScreenInfo.base);
    SDL_DestroyTexture(gameO->startScreenInfo.hp);
    SDL_DestroyTexture(gameO->startScreenInfo.maxBullets);
}


void InitFailScreen(GameO *gameO)
{
    SDL_Color white = {255,255,255,255};
    switch (gameO->gameStats.Death){
    case 1:
        strcpy(gameO->failScreenInfo.CauseDeathChar, "Slained by a zombie.");
        break;
    case 2:
        strcpy(gameO->failScreenInfo.CauseDeathChar, "Out of caffeine.");
        break;
    case 3:
        strcpy(gameO->failScreenInfo.CauseDeathChar, "Out of time.");
        break;
    default:
        break;
    }
    SDL_Surface *GameOverSurface = TTF_RenderText_Blended(gameO->failScreenInfo.font, "Game Over", white);
    SDL_Surface *CauseDeathSurface = TTF_RenderText_Blended(gameO->font, gameO->failScreenInfo.CauseDeathChar, white);
    gameO->failScreenInfo.GameOverW = GameOverSurface->w;
    gameO->failScreenInfo.GameOverH = GameOverSurface->h;
    gameO->failScreenInfo.CauseDeathW = CauseDeathSurface->w;
    gameO->failScreenInfo.CauseDeathH = CauseDeathSurface->h;
    gameO->failScreenInfo.GameOverLable = SDL_CreateTextureFromSurface(gameO->renderer, GameOverSurface);
    gameO->failScreenInfo.CauseDeathLable = SDL_CreateTextureFromSurface(gameO->renderer, CauseDeathSurface);
    switch (gameO->gameStats.Death){
        case 1: // zombie
            gameO->failScreenInfo.CauseDeathX = 740 + CauseDeathSurface->w/5;
            break;
        case 2: // out of coffee
            gameO->failScreenInfo.CauseDeathX = 740 + CauseDeathSurface->w/3 + 5;
            break;
        case 3:
            gameO->failScreenInfo.CauseDeathX = 740 + CauseDeathSurface->w/2 + 15;
            break;
        default:
            break;
    }
    SDL_FreeSurface(GameOverSurface);
    SDL_FreeSurface(CauseDeathSurface);
}

void FailScreen(GameO *gameO)
{
    SDL_Rect GameOverRect = {740, 300, gameO->failScreenInfo.GameOverW, gameO->failScreenInfo.GameOverH};
    SDL_Rect CauseDeathRect = {gameO->failScreenInfo.CauseDeathX, 400, gameO->failScreenInfo.CauseDeathW, gameO->failScreenInfo.CauseDeathH};
    SDL_SetRenderDrawColor(gameO->renderer, 0,0,0,255);
    SDL_RenderClear(gameO->renderer); // clear the screen to black
    SDL_RenderCopy(gameO->renderer, gameO->failScreenInfo.GameOverLable, NULL, &GameOverRect);
    SDL_RenderCopy(gameO->renderer, gameO->failScreenInfo.CauseDeathLable, NULL, &CauseDeathRect);
    SDL_RenderPresent(gameO->renderer);   
}

void DestroyFailScreen(GameO *gameO)
{
    SDL_DestroyTexture(gameO->failScreenInfo.GameOverLable);
    SDL_DestroyTexture(gameO->failScreenInfo.CauseDeathLable);
}



void InitWinScreen(GameO *gameO)
{
    SDL_Color white = {255,255,255,255};
    gameO->timeLeft.Etime = time(NULL) - gameO->timeLeft.Stime;
    sprintf(gameO->winScreenInfo.WinTimeChar, "You killed %d zombies in %ld minutes and %ld seconds.", gameO->gameStats.ZombieKillGoal,
            gameO->timeLeft.Etime/60 , (gameO->timeLeft.Etime)%60);
    SDL_Surface *WinSurface = TTF_RenderText_Blended(gameO->failScreenInfo.font, "YOU WON!", white);
    SDL_Surface *WinTimeSurface = TTF_RenderText_Blended(gameO->font, gameO->winScreenInfo.WinTimeChar, white);
    gameO->winScreenInfo.WinW = WinSurface->w;
    gameO->winScreenInfo.WinH = WinSurface->h;
    gameO->winScreenInfo.WinTimeW = WinTimeSurface->w;
    gameO->winScreenInfo.WinTimeH = WinTimeSurface->h;
    gameO->winScreenInfo.WinLable = SDL_CreateTextureFromSurface(gameO->renderer, WinSurface);
    gameO->winScreenInfo.WinTimeLable = SDL_CreateTextureFromSurface(gameO->renderer, WinTimeSurface);
    SDL_FreeSurface(WinSurface);
    SDL_FreeSurface(WinTimeSurface);
}

void WinScreen(GameO *gameO)
{
    SDL_Rect WinTextRect = {1920/2 - gameO->winScreenInfo.WinW/2, 300, gameO->winScreenInfo.WinW, gameO->winScreenInfo.WinH};
    SDL_Rect WinTimeRect = {(1920/2 - gameO->winScreenInfo.WinW/2)-gameO->winScreenInfo.WinTimeW/5, 400, gameO->winScreenInfo.WinTimeW, gameO->winScreenInfo.WinTimeH};
    SDL_SetRenderDrawColor(gameO->renderer, 0,0,0,255);
    SDL_RenderClear(gameO->renderer);
    SDL_RenderCopy(gameO->renderer, gameO->winScreenInfo.WinLable, NULL, &WinTextRect);
    SDL_RenderCopy(gameO->renderer, gameO->winScreenInfo.WinTimeLable, NULL, &WinTimeRect);
    SDL_RenderPresent(gameO->renderer);
}

void DestroyWinScreen(GameO *gameO)
{
    SDL_DestroyTexture(gameO->winScreenInfo.WinLable);
    SDL_DestroyTexture(gameO->winScreenInfo.WinTimeLable);
}