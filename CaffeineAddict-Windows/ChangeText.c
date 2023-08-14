#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include "main.h"

void ChangeHP(GameO *gameO){   //function to change the HP texture and make a new one with new hp
    SDL_Color white = {255, 255, 255, 255};
    SDL_DestroyTexture(gameO->textures.HPlable);
    sprintf(gameO->playerHP.currentHP, "hp:  %d", gameO->player1.hp);
    SDL_Surface *HPsurface = TTF_RenderText_Blended(gameO->font, gameO->playerHP.currentHP, white);
    gameO->playerHP.lableW = HPsurface->w;
    gameO->playerHP.lableH = HPsurface->h;
    gameO->textures.HPlable = SDL_CreateTextureFromSurface(gameO->renderer, HPsurface);
    SDL_FreeSurface(HPsurface);
}

void showBulletsLeft(GameO *gameO){
    SDL_Color white = {255,255,255,255};
    SDL_DestroyTexture(gameO->textures.BulletNumLable);
    sprintf(gameO->BulletChar, "Bullets Left:  %d", gameO->player1.bullet.BulletsLeft);
    SDL_Surface *BulletNumSurface = TTF_RenderText_Blended(gameO->font, gameO->BulletChar, white);
    gameO->player1.bullet.BulletCharW = BulletNumSurface->w;
    gameO->player1.bullet.BulletCharH = BulletNumSurface->h;
    gameO->textures.BulletNumLable = SDL_CreateTextureFromSurface(gameO->renderer, BulletNumSurface);
    SDL_FreeSurface(BulletNumSurface);
}

void ChangeScore(GameO *gameO){
    SDL_Color white = {255,255,255,255};
    SDL_DestroyTexture(gameO->textures.ScoreLable);
    sprintf(gameO->gameStats.ScoreChar, "Zombies left:  %d", gameO->gameStats.Score);
    SDL_Surface *ScoreSurface = TTF_RenderText_Blended(gameO->font, gameO->gameStats.ScoreChar, white);
    gameO->gameStats.ScoreLableW = ScoreSurface->w;
    gameO->gameStats.ScoreLableH = ScoreSurface->h;
    gameO->textures.ScoreLable = SDL_CreateTextureFromSurface(gameO->renderer, ScoreSurface);
    SDL_FreeSurface(ScoreSurface);
}

void ChangeCaffeine(GameO *gameO){
    SDL_Color white = {255,255,255,255};
    SDL_DestroyTexture(gameO->textures.CoffeeNumLable);
    sprintf(gameO->coffeeNumText.CoffeeNumChar, "Caffeine:  %.2f", gameO->player1.caffein);
    SDL_Surface *CoffeeNumSurface = TTF_RenderText_Blended(gameO->font, gameO->coffeeNumText.CoffeeNumChar, white);
    gameO->textures.CoffeeNumLable = SDL_CreateTextureFromSurface(gameO->renderer, CoffeeNumSurface);
    gameO->coffeeNumText.CoffeeNumW = CoffeeNumSurface->w;
    gameO->coffeeNumText.CoffeeNumH = CoffeeNumSurface->h;
    SDL_FreeSurface(CoffeeNumSurface);
}

void ChangeTime(GameO *gameO){
    SDL_Color white = {255,255,255,255};
    SDL_DestroyTexture(gameO->textures.TimeTextLable);
    sprintf(gameO->timeLeft.TimeChar, "Time left:  %d:%d", gameO->timeLeft.min, gameO->timeLeft.sec);
    SDL_Surface *TimeTextSurface = TTF_RenderText_Blended(gameO->font, gameO->timeLeft.TimeChar, white);
    gameO->timeLeft.TimeTextW = TimeTextSurface->w;
    gameO->timeLeft.TimeTextH = TimeTextSurface->h;
    gameO->textures.TimeTextLable = SDL_CreateTextureFromSurface(gameO->renderer, TimeTextSurface);
    SDL_FreeSurface(TimeTextSurface);
}
