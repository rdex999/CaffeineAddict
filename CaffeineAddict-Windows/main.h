#ifndef main_h
#define main_h

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <time.h>

typedef struct Sounds{
    Mix_Chunk *ShootSound;
    Mix_Chunk *JumpSound;
    Mix_Chunk *CaffeineSound;
    Mix_Chunk *LandSound;
    int Channel;
}Sounds;

typedef struct TimeLeft{
    int min,sec;
    int ChangeTimer;
    int TimeTextW, TimeTextH;
    char TimeChar[30];
    time_t Stime;
    time_t Etime;
}TimeLeft;

typedef struct CoffeeNumText{
    char CoffeeNumChar[20];
    int CoffeeNumW;
    int CoffeeNumH;
}CoffeeNumText;

typedef struct CoffeeBean{
    int x, y;
    int SlowSpeed;
    int UpDown; // 1 for up 0 for down
}CoffeeBean;

typedef struct GameStats{
    int Score;
    int ScoreLableW;
    int ScoreLableH;
    char ScoreChar[19];
    int Death; // 0 is not dead 1 zombie 2 low caffeine 3 out of time
    int ZombieKillGoal;
}GameStats;

typedef struct Bullet{
    int BulletLR; // 0 for left 1 for right
    int BulletX;
    int BulletY;
    int BulletsLeft;
    int CurrentBullet;
    int BulletCharW, BulletCharH;
}Bullet;

typedef struct player{
    int hp;
    int x, y;
    double caffein;
    char *name;
    int LR;
    int walk;
    int reloadState;  // 1 is not reloading 0 in reloading
    int CanShot;
    int ShotTimer;
    Bullet bullet;
    int ReloadCounter;
    int walkSpeed;
    int CanTakeDamage;
    int DamageFrameCounter;
    int HealthTimer;
    int GotHit;
    int HitTimer;
}player;

typedef struct HP{
    char currentHP[9];
    int lableW;
    int lableH;
}HP;

typedef struct Textures{
    SDL_Texture *Bullet;
    SDL_Texture *BulletNumLable;
    SDL_Texture *skin[4];
    SDL_Texture *HPlable;
    SDL_Texture *background;
    SDL_Texture *JumpThing;
    SDL_Texture *SmallWall;
    SDL_Texture *zombie[3];
    SDL_Texture *ScoreLable;
    SDL_Texture *Coffee;
    SDL_Texture *CoffeeNumLable;
    SDL_Texture *TimeTextLable;
}Textures;

typedef struct Zombie{
    int zombieX;
    int zombieY;
    int zombieLife;
    int LR;
    int zombieWcounter; // note: W is for walk
    int walkState;
    int IsAlive;
}Zombie;

typedef struct StartScreenInfo{
    int baseW, baseH;
    int hpW, hpH;
    int maxBulletsW, maxBulletsH;
    int startScreenTime;
    SDL_Texture *base;
    SDL_Texture *hp;
    SDL_Texture *maxBullets;
    int startScreenState;
}StartScreenInfo;

typedef struct FailScreenInfo{
    TTF_Font *font;
    SDL_Texture *GameOverLable;
    SDL_Texture *CauseDeathLable;
    int GameOverW, GameOverH;
    char CauseDeathChar[21];
    int CauseDeathW, CauseDeathH;
    int CauseDeathX;
}FailScreenInfo;

typedef struct WinScreenInfo{
    SDL_Texture *WinLable;
    SDL_Texture *WinTimeLable;
    char WinTimeChar[69];
    int WinW, WinH;
    int WinTimeW, WinTimeH;
}WinScreenInfo;

typedef struct GameO{
    SDL_Renderer *renderer;
    player player1;
    HP playerHP;
    TTF_Font *font;
    Textures textures;
    char BulletChar[18];
    Zombie zombie[6];
    StartScreenInfo startScreenInfo;
    FailScreenInfo failScreenInfo;
    GameStats gameStats;
    CoffeeBean coffeeBean[5];
    CoffeeNumText coffeeNumText;
    TimeLeft timeLeft;
    WinScreenInfo winScreenInfo;
    Sounds sounds;

    int DisplayStartScreen;
    int maxZombieNum;
    int frameCounter;
    int gravityPower;
    int gravity;
    int run;
    int SlowPlayerL;
    int SlowPlayerR;
    int SlowSpeed;
    int slowDown;
    int fire;
    int LR;
    int counter;
    int jump;
    int SetTime;
    int JumpThingState;
    int zombieGravityPower;
    int zombieSpawnSide; // 0 for left 1 for right
    int CaffeineTimer;
    int ZombiesToKill;
}GameO;

#endif