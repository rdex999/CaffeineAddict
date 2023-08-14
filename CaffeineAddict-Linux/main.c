#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <time.h>
#include "main.h"
#include "StatusScreen.h"
#include "ChangeText.h"

#define WIDTH 1920
#define HIGHT 1280
#define MAX_ZOMBIE 4
#define MAX_COFFEE 5

// to compile run: gcc -o main main.c StatusScreen.c ChangeText.c `sdl2-config --cflags --libs` -lSDL2_image -Wall -lSDL2_ttf -lSDL2_mixer

int load(GameO *gameO)
{
    SDL_Surface *backgroundSurface = IMG_Load("src/background.png");
    if(backgroundSurface == NULL){
        printf("Could not creat background surface.");
        SDL_Quit();
        return 1;
    }
    gameO->textures.background = SDL_CreateTextureFromSurface(gameO->renderer, backgroundSurface);
    SDL_FreeSurface(backgroundSurface);

    SDL_Surface *skinSurface = IMG_Load("src/skinLeft.png");
    if(skinSurface == NULL){
        printf("Error, could not creat skin surface.\n");
        SDL_Quit();
        return 1;
    }
    gameO->textures.skin[0] = SDL_CreateTextureFromSurface(gameO->renderer, skinSurface);
    SDL_FreeSurface(skinSurface);

    SDL_Surface *skinWalkSurface = IMG_Load("src/skinWalk.png");
    if(skinWalkSurface == NULL){
        printf("Error, could not create skinWalk surface.\n");
        SDL_Quit();
        return 1;
    }
    gameO->textures.skin[1] = SDL_CreateTextureFromSurface(gameO->renderer, skinWalkSurface);
    SDL_FreeSurface(skinWalkSurface);

    SDL_Surface *BulletLeftSurface = IMG_Load("src/BulletLeft.png");
    if(BulletLeftSurface == NULL){
        printf("Could not create BulletRight Surface.\n");
        SDL_Quit();
        return 1;
    }
    gameO->textures.Bullet = SDL_CreateTextureFromSurface(gameO->renderer, BulletLeftSurface);
    SDL_FreeSurface(BulletLeftSurface);
    
    SDL_Surface *JumpThingSurface = IMG_Load("src/JumpThing2.png");
    if(JumpThingSurface == NULL){
        printf("Could not create JumpThing surface.\n");
        SDL_Quit();
        return 1;
    }
    gameO->textures.JumpThing = SDL_CreateTextureFromSurface(gameO->renderer, JumpThingSurface);
    SDL_FreeSurface(JumpThingSurface);

    SDL_Surface *skinReload1Surface = IMG_Load("src/skinReload1.png");
    if(skinReload1Surface == NULL){
        printf("Could not create skinReload1 surface.\n");
        SDL_Quit();
        return 1;
    }
    gameO->textures.skin[2] = SDL_CreateTextureFromSurface(gameO->renderer, skinReload1Surface);
    SDL_FreeSurface(skinReload1Surface);

    SDL_Surface *skinReload2Surface = IMG_Load("src/skinReload2.png");
    if(skinReload2Surface == NULL){
        printf("Could not create skinReload2 surface.\n");
        SDL_Quit();
        return 1;
    }
    gameO->textures.skin[3] = SDL_CreateTextureFromSurface(gameO->renderer, skinReload2Surface);
    SDL_FreeSurface(skinReload2Surface);

    SDL_Surface *SmallWallSurface = IMG_Load("src/SmallWall.png");
    if(SmallWallSurface == NULL){
        printf("Could not create SmallWall surface.\n");
        SDL_Quit();
        return 1;
    }
    gameO->textures.SmallWall = SDL_CreateTextureFromSurface(gameO->renderer, SmallWallSurface);
    SDL_FreeSurface(SmallWallSurface);

    SDL_Surface *zombieW0Surface = IMG_Load("src/zombie.png");
    if(zombieW0Surface == NULL){
        printf("Could not create zombieW0 surface.\n");
        SDL_Quit();
        return 1;
    }
    gameO->textures.zombie[0] = SDL_CreateTextureFromSurface(gameO->renderer, zombieW0Surface);
    SDL_FreeSurface(zombieW0Surface);

    SDL_Surface *zombieW1Surface = IMG_Load("src/ZombieWalk1.png");
    if(zombieW1Surface == NULL){
        printf("Could not create zombieW1 surface.\n");
        SDL_Quit();
        return 1;
    }
    gameO->textures.zombie[1] = SDL_CreateTextureFromSurface(gameO->renderer, zombieW1Surface);
    SDL_FreeSurface(zombieW1Surface);

    SDL_Surface *zombieW2Surface = IMG_Load("src/ZombieWalk2.png");
    if(zombieW2Surface == NULL){
        printf("Could not create zombieW2 surface.\n");
        SDL_Quit();
        return 1;
    }
    gameO->textures.zombie[2] = SDL_CreateTextureFromSurface(gameO->renderer, zombieW2Surface);
    SDL_FreeSurface(zombieW2Surface);

    SDL_Surface *CoffeeSurface = IMG_Load("src/coffee.png");
    if(CoffeeSurface == NULL){
        printf("Could not create CoffeeBean surface.\n");
        SDL_Quit();
        return 1;
    }
    gameO->textures.Coffee = SDL_CreateTextureFromSurface(gameO->renderer, CoffeeSurface);
    SDL_FreeSurface(CoffeeSurface);

    gameO->font = TTF_OpenFont("src/Tilt_Warp/TiltWarp-Regular-VariableFont_XROT,YROT.ttf", 25);
    if(gameO->font == NULL){
        printf("Error: %s\n", TTF_GetError());
        SDL_Quit();
        TTF_Quit();
        return 1;
    }
    gameO->failScreenInfo.font = TTF_OpenFont("src/Tilt_Warp/TiltWarp-Regular-VariableFont_XROT,YROT.ttf", 64);
    if(gameO->failScreenInfo.font == NULL){
        printf("Error: %s\n", TTF_GetError());
        SDL_Quit();
        TTF_Quit();
        return 1;
    }

    SDL_Color white = {255,255,255,255};
    SDL_Surface *HPsurface = TTF_RenderText_Blended(gameO->font, gameO->playerHP.currentHP, white);
    gameO->textures.HPlable = SDL_CreateTextureFromSurface(gameO->renderer, HPsurface);
    gameO->playerHP.lableH = HPsurface->h;
    gameO->playerHP.lableW = HPsurface->w;
    SDL_FreeSurface(HPsurface);

    SDL_Surface *BulletNumSurface = TTF_RenderText_Blended(gameO->font, gameO->BulletChar, white);
    gameO->textures.BulletNumLable = SDL_CreateTextureFromSurface(gameO->renderer, BulletNumSurface);
    gameO->player1.bullet.BulletCharW = BulletNumSurface->w;
    gameO->player1.bullet.BulletCharH = BulletNumSurface->h;
    SDL_FreeSurface(BulletNumSurface);

    SDL_Surface *ScoreSurface = TTF_RenderText_Blended(gameO->font, gameO->gameStats.ScoreChar, white);
    gameO->textures.ScoreLable = SDL_CreateTextureFromSurface(gameO->renderer, ScoreSurface);
    gameO->gameStats.ScoreLableW = ScoreSurface->w;
    gameO->gameStats.ScoreLableH = ScoreSurface->h;
    SDL_FreeSurface(ScoreSurface);

    SDL_Surface *CoffeeNumSurface = TTF_RenderText_Blended(gameO->font, gameO->coffeeNumText.CoffeeNumChar, white);
    gameO->textures.CoffeeNumLable = SDL_CreateTextureFromSurface(gameO->renderer, CoffeeNumSurface);
    gameO->coffeeNumText.CoffeeNumW = CoffeeNumSurface->w;
    gameO->coffeeNumText.CoffeeNumH = CoffeeNumSurface->h;
    SDL_FreeSurface(CoffeeNumSurface);
    
    SDL_Surface *TimeTextSurface = TTF_RenderText_Blended(gameO->font, gameO->timeLeft.TimeChar, white);
    gameO->textures.TimeTextLable = SDL_CreateTextureFromSurface(gameO->renderer, TimeTextSurface);
    gameO->timeLeft.TimeTextW = TimeTextSurface->w;
    gameO->timeLeft.TimeTextH = TimeTextSurface->h;
    SDL_FreeSurface(TimeTextSurface);

    gameO->sounds.ShootSound = Mix_LoadWAV("src/sounds/GunShoot.wav");
    if(gameO->sounds.ShootSound == NULL){
        printf("Could not load GunShoot.wav.\n");
        SDL_Quit();
        TTF_Quit();
        Mix_Quit();
        return 1;
    }
    Mix_VolumeChunk(gameO->sounds.ShootSound, 100); // volume from 1 to 128

    gameO->sounds.JumpSound = Mix_LoadWAV("src/sounds/Jump.wav");
    if(gameO->sounds.JumpSound == NULL){
        printf("Could not load Jump.wav.\n");
        SDL_Quit();
        TTF_Quit();
        Mix_Quit();
        return 1;
    }
    Mix_VolumeChunk(gameO->sounds.JumpSound, 128);

    gameO->sounds.CaffeineSound = Mix_LoadWAV("src/sounds/CaffeineSound.wav");
    if(gameO->sounds.CaffeineSound == NULL){
        printf("Could not load CaffeineSound.wav.\n");
        SDL_Quit();
        TTF_Quit();
        Mix_Quit();
        return 1;
    }
    Mix_VolumeChunk(gameO->sounds.CaffeineSound, 60);

    gameO->sounds.LandSound = Mix_LoadWAV("src/sounds/LandSound.wav");
    if(gameO->sounds.LandSound == NULL){
        printf("Could not load LandSound.wav.\n");
        SDL_Quit();
        TTF_Quit();
        Mix_Quit();
        return 1;
    }
    Mix_VolumeChunk(gameO->sounds.LandSound, 100);
    return 0;
}


void reloadGun(GameO *gameO){
    int currentTime = time(NULL);
    while(1){
        if(time(NULL)-currentTime >= 2){
            gameO->player1.bullet.BulletsLeft = 16;
            break;
        }
    }
}


void destroy(GameO *gameO, SDL_Window *screen){
    if(gameO->textures.background != NULL){
        SDL_DestroyTexture(gameO->textures.background);
    }
    if(gameO->textures.skin[0] != NULL){
        SDL_DestroyTexture(gameO->textures.skin[0]);
    }
    if(gameO->textures.Bullet != NULL){
        SDL_DestroyTexture(gameO->textures.Bullet);
    }
    if(gameO->textures.HPlable != NULL){
        SDL_DestroyTexture(gameO->textures.HPlable);
    }
    if(gameO->textures.JumpThing != NULL){
        SDL_DestroyTexture(gameO->textures.JumpThing);
    }
    if(gameO->textures.zombie[0] != NULL){
        SDL_DestroyTexture(gameO->textures.zombie[0]);
    }
    if(gameO->textures.ScoreLable != NULL){
        SDL_DestroyTexture(gameO->textures.ScoreLable);
    }
    if(gameO->textures.Coffee != NULL){
        SDL_DestroyTexture(gameO->textures.Coffee);
    }
    if(gameO->textures.CoffeeNumLable != NULL){
        SDL_DestroyTexture(gameO->textures.CoffeeNumLable);
    }
    if(gameO->textures.TimeTextLable != NULL){
        SDL_DestroyTexture(gameO->textures.TimeTextLable);
    }
    if(gameO->font != NULL){
        TTF_CloseFont(gameO->font);
    }
    if(gameO->failScreenInfo.font != NULL){
        TTF_CloseFont(gameO->failScreenInfo.font);
    }
    if(gameO->sounds.ShootSound != NULL){
        Mix_FreeChunk(gameO->sounds.ShootSound);
    }
    if(gameO->sounds.JumpSound != NULL){
        Mix_FreeChunk(gameO->sounds.JumpSound);
    }
    if(gameO->sounds.CaffeineSound != NULL){
        Mix_FreeChunk(gameO->sounds.CaffeineSound);
    }
    if(gameO->sounds.LandSound != NULL){
        Mix_FreeChunk(gameO->sounds.LandSound);
    }
    SDL_DestroyWindow(screen);
    SDL_DestroyRenderer(gameO->renderer);
    TTF_Quit();
    SDL_Quit();
    Mix_Quit();
}

int randNum(int min, int max){
    int randomeNum;
    randomeNum = rand()%(max-min)+min;
    return randomeNum;
}


void Events(SDL_Window *screen, GameO *gameO){
    if(!gameO->startScreenInfo.startScreenState){
        SDL_Event event;

        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_WINDOWEVENT_CLOSE:
                {
                    if(screen)
                    {
                        screen = NULL;
                        gameO->run = 0;
                    }
                }
                case SDL_KEYDOWN:
                {
                    switch(event.key.keysym.sym) //case normal key is pressed
                    {
                        case SDLK_ESCAPE:
                        {
                            gameO->run = 0;
                            break;
                        }
                        case SDLK_SPACE:
                        {
                            if(((gameO->player1.y >= 795) || (gameO->player1.y > 350-200 && gameO->player1.y < 350-180)) && gameO->jump == 0 && gameO->player1.reloadState){
                                gameO->jump = 1;
                                Mix_PlayChannel(-1, gameO->sounds.JumpSound, 0);
                            }
                            break;
                        }
                        case SDLK_w:  // alternative to space
                        {
                            if(((gameO->player1.y >= 795) || (gameO->player1.y > 350-200 && gameO->player1.y < 350-180)) && gameO->jump == 0 && gameO->player1.reloadState){
                                gameO->jump = 1;
                            }
                            break;  
                        }
                        case SDLK_RSHIFT:
                        {
                            if(gameO->player1.bullet.BulletsLeft == 0){
                                gameO->player1.reloadState = 0;
                                gameO->player1.walkSpeed = 3;
                                break;
                            }
                            if(gameO->player1.bullet.BulletsLeft > 0 && gameO->player1.reloadState && gameO->player1.CanShot){
                                gameO->fire = 1;
                                gameO->player1.CanShot = 0;
                                Mix_PlayChannel(-1, gameO->sounds.ShootSound, 0);
                                if(gameO->LR){
                                    gameO->player1.bullet.BulletX = gameO->player1.x + 100;
                                }else if(gameO->LR == 0){
                                    gameO->player1.bullet.BulletX = gameO->player1.x + 30;
                                }
                                gameO->player1.bullet.BulletY = gameO->player1.y + 90;
                                gameO->player1.bullet.BulletLR = gameO->LR;
                                gameO->player1.bullet.BulletsLeft--;
                                showBulletsLeft(gameO);
                            }
                            break;
                        }
                        case SDLK_r:
                        {
                            if(gameO->player1.bullet.BulletsLeft < 16){
                                gameO->player1.reloadState = 0;
                                gameO->player1.walkSpeed = 3;
                            }
                            break;
                        }
                        case SDLK_RCTRL:
                            {
                            if(gameO->player1.reloadState && gameO->player1.y < 790 && gameO->player1.y > 320){ 
                                gameO->gravity = 1;
                                gameO->gravityPower = 40;
                            }
                            break;
                            }
                    }
                }
                break;

                case SDL_KEYUP:
                {
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_d:
                            if(gameO->player1.reloadState){
                                gameO->SlowPlayerR = 1;
                                gameO->player1.walk = 0;
                            }
                            break;
                        case SDLK_a:
                            if(gameO->player1.reloadState){
                                gameO->SlowPlayerL = 1;
                                gameO->player1.walk = 0;
                            }
                            break;
                    }
                }
                break;
                case SDL_QUIT:  // quit if user clicks on the close window button
                {
                    gameO->run = 0;
                    break;
                }
            }
        }

        const Uint8 *state = SDL_GetKeyboardState(NULL);
        if(state[SDL_SCANCODE_D]){
            if(gameO->player1.x + 10 < 1810){
                gameO->player1.x += gameO->player1.walkSpeed;
                gameO->LR = 1;
                if(gameO->frameCounter >= 15 && gameO->player1.reloadState){
                    if(gameO->player1.walk){
                        gameO->player1.walk = 0;
                    }else if(gameO->player1.walk == 0){
                        gameO->player1.walk = 1;
                    }
                    gameO->frameCounter = 0;
                }
                gameO->frameCounter++;
            }
        }
        if(state[SDL_SCANCODE_A]){
            if(gameO->player1.x + 10 > -65){
                gameO->player1.x -= gameO->player1.walkSpeed;
                gameO->LR = 0;
                if(gameO->frameCounter >= 15 && gameO->player1.reloadState){
                    if(gameO->player1.walk){
                        gameO->player1.walk = 0;
                    }else if(gameO->player1.walk == 0){
                        gameO->player1.walk = 1;
                    }
                    gameO->frameCounter = 0;
                }
                gameO->frameCounter++;
            }
        }
    }
}

void CollisionDetection(GameO *gameO){
    if(gameO->startScreenInfo.startScreenState){
        StartScreen(gameO);
        gameO->startScreenInfo.startScreenTime++;
        if(gameO->startScreenInfo.startScreenTime >= 120){
            gameO->startScreenInfo.startScreenState = 0;
            DestroyStartScreen(gameO);
        }
    }
    if(!gameO->startScreenInfo.startScreenState){
        if(gameO->jump == 1 && gameO->counter <= 28){  // jump
            if(gameO->counter <= 18){
                gameO->gravity = 0;
                gameO->player1.y -= 17;
                gameO->counter += 1;
                }
            if(gameO->counter >= 18){
                gameO->slowDown *= 0.99;    // Slow down the jump
                gameO->player1.y -= gameO->slowDown;
                gameO->counter += 1;
            }
            if(gameO->counter >= 27){
                gameO->counter = 0;
                gameO->jump = 0;
                gameO->gravity = 1;
                gameO->slowDown = 12;
            }
        }

        if(gameO->player1.y <= 350 && gameO->player1.x >= 1130 && gameO->player1.x <= 1300 && !gameO->JumpThingState && !gameO->jump){
            gameO->player1.y += gameO->gravityPower;   // fall from the hole in the small wall
        }

        if(((gameO->player1.y < 810 && gameO->player1.y > 350) && gameO->gravity))  // normal gravity
        {
            gameO->player1.y += gameO->gravityPower;
            if(gameO->player1.y >= 800){
                Mix_PlayChannel(-1, gameO->sounds.LandSound, 0);
            }
            if(gameO->player1.y >= 805 && gameO->gravityPower > 15){
                gameO->gravityPower = 15;
            }
        }

        if((gameO->player1.y < 350-198 && gameO->gravity)){  // gravity above the small wall
            gameO->player1.y += gameO->gravityPower;
            if(gameO->player1.y >= 350-198){
                Mix_PlayChannel(-1, gameO->sounds.LandSound, 0);
            }
        }

        if(gameO->fire){  // gun shot
            if(gameO->player1.bullet.BulletLR){
                gameO->player1.bullet.BulletX += 60;
            }else if(gameO->player1.bullet.BulletLR == 0){
                gameO->player1.bullet.BulletX -= 60;
            }
            if(gameO->player1.bullet.BulletX >= 1920 || gameO->player1.bullet.BulletX <= -60){
                gameO->fire = 0;
            }
        }
        if(!gameO->player1.CanShot){
            if(gameO->player1.ShotTimer >= 7){  // player can shot 10 times in a second
                gameO->player1.CanShot = 1;
                gameO->player1.ShotTimer = 0;
            }
            gameO->player1.ShotTimer++;
        }



        if(gameO->SlowPlayerR){    //Slow down walking
            if(gameO->player1.x + gameO->SlowSpeed < 1810){
                gameO->player1.x += gameO->SlowSpeed; 
                gameO->SlowSpeed *= 0.99;
            }
            if(gameO->SlowSpeed <= 0){
                gameO->SlowPlayerR = 0;
                gameO->SlowSpeed = 10;
            }
        }
        if(gameO->SlowPlayerL){   //Slow down Walking
            if(gameO->player1.x - gameO->SlowSpeed > -65){
                gameO->player1.x -= gameO->SlowSpeed;
                gameO->SlowSpeed *= 0.99;
            }
            if(gameO->SlowSpeed <= 0){
                gameO->SlowPlayerL = 0;
                gameO->SlowSpeed = 10;
            }
        }
        if(gameO->player1.reloadState == 0){   // reload animation
            if(gameO->SetTime){
                gameO->player1.ReloadCounter = 0;
                gameO->SetTime = 0;
                gameO->player1.walk = 2;

            }
            if(gameO->player1.ReloadCounter >= 45){
                gameO->player1.walk = 3;
            }
            if(gameO->player1.ReloadCounter >= 90){
                gameO->player1.walk = 2;
            }
            if(gameO->player1.ReloadCounter >= 120){
                gameO->player1.bullet.BulletsLeft = 16;
                gameO->player1.reloadState = 1;
                gameO->SetTime = 1;
                gameO->player1.walk = 0;
                gameO->player1.walkSpeed = 10;
                showBulletsLeft(gameO);
            }
            gameO->player1.ReloadCounter ++;
        }

        if(gameO->player1.y > 810 && gameO->jump == 0 && gameO->gravity){ // if the player is underground
            gameO->player1.y--;
        }

        if((gameO->player1.x >= 1120 && gameO->player1.x <= 1300) && gameO->player1.y  >= 800){   // if player touched Jump Thing then activate it 
            gameO->gravity = 0;
            gameO->JumpThingState = 1;
            gameO->slowDown = 23;
        }
        if(gameO->JumpThingState){      // if the Jump Thing is activated
            if(gameO->player1.y >= 300){
                gameO->player1.y -= 23;
            }else if(gameO->player1.y < 300){
                gameO->slowDown *= 0.99;
                gameO->player1.y -= gameO->slowDown;
            }
            if(gameO->slowDown <= 0){
                gameO->JumpThingState = 0;
                gameO->gravity = 1;
                gameO->slowDown = 12;
            }
        }

        if(gameO->player1.x > 1300 && gameO->player1.y >= 370 && gameO->player1.y < 455){ // from below the small wall, the player
            gameO->gravity = 1;                                                             //  cannot go throught the smal wall
            gameO->JumpThingState = 0;
        }
        if(gameO->player1.x <= 1100 && gameO->player1.y >= 370 && gameO->player1.y < 455){  // same here but for the left side
            gameO->gravity = 1;
            gameO->JumpThingState = 0;
        }

        if(gameO->player1.y >= 350-180 && gameO->player1.y <= 350+90){ // check if player is touching the sides of the small wall
            if(gameO->player1.x >= 1300){
                gameO->player1.x -= gameO->player1.walkSpeed;
                gameO->player1.y += gameO->gravityPower;
            }else if(gameO->player1.x <= 1080){
                gameO->player1.x += gameO->player1.walkSpeed;
                gameO->player1.y += gameO->gravityPower;
            }
        }


        if(gameO->player1.y > 350-198 && gameO->player1.y < 350-185){  // if the player is a little below the small wall
            gameO->player1.y--;
        }

        for(int c=0; c<MAX_COFFEE; c++) // loop to check on the coffee beans
        {
            if(gameO->player1.y <= 350 && gameO->player1.y >= 350-198){
                if((gameO->player1.x <= (gameO->coffeeBean[c].x + 20)) && (gameO->player1.x >= (gameO->coffeeBean[c].x - 20))){  // if the player touched the coffee bean
                    if(randNum(1, 20) < 15){
                        gameO->coffeeBean[c].x = randNum(67, 1100); // randum position for coffe on the left side of the small wall
                    }else{
                        gameO->coffeeBean[c].x = randNum(1370, 1800); // randum position for coffe on the right side of the small wall
                    }
                    gameO->player1.caffein++;
                    Mix_PlayChannel(-1, gameO->sounds.CaffeineSound, 0);
                    ChangeCaffeine(gameO);
                }
            }
            if(gameO->coffeeBean[c].UpDown){
                gameO->coffeeBean[c].y -= gameO->coffeeBean[c].SlowSpeed;
                gameO->coffeeBean[c].SlowSpeed *= 0.99;
                if(gameO->coffeeBean[c].SlowSpeed <= 0){
                    gameO->coffeeBean[c].SlowSpeed = 10;
                    gameO->coffeeBean[c].UpDown = 0;
                }
            }else if(!gameO->coffeeBean[c].UpDown){
                gameO->coffeeBean[c].y += gameO->coffeeBean[c].SlowSpeed;
                gameO->coffeeBean[c].SlowSpeed *= 0.99;
                if(gameO->coffeeBean[c].SlowSpeed <= 0){
                    gameO->coffeeBean[c].SlowSpeed = 10;
                    gameO->coffeeBean[c].UpDown = 1;
                }
            }
        }
        

        for(int c=0 ;c<gameO->maxZombieNum; c++){   // loop to check thing on all of the zombies
            if(!gameO->zombie[c].IsAlive){
                if(randNum(0, 10) >= 5){
                    gameO->zombie[c].zombieX = randNum(1920, 2600);
                    gameO->zombie[c].zombieLife = 30;
                    gameO->zombie[c].IsAlive = 1;
                }else if(randNum(0, 10) < 5){
                    gameO->zombie[c].zombieX = randNum(-680, 0);
                    gameO->zombie[c].zombieLife = 30;
                    gameO->zombie[c].IsAlive = 1;
                }
            }
            if(gameO->zombie[c].IsAlive){
                if(gameO->zombie[c].zombieLife <= 0){
                    gameO->zombie[c].IsAlive = 0;
                    gameO->gameStats.Score--;
                    ChangeScore(gameO);
                }
                
                if(gameO->zombie[c].zombieY > 795){   // if zombie is underground
                    gameO->zombie[c].zombieY--;
                }

                if(gameO->zombie[c].zombieY < 795){   // normal zombie gravity
                    gameO->zombie[c].zombieY += gameO->zombieGravityPower;
                }

                if(-1*((gameO->zombie[c].zombieX + 3) - gameO->player1.x) < ((gameO->zombie[c].zombieX - 3) - gameO->player1.x)){    // zombie move close to player
                    if(-1*((gameO->zombie[c].zombieX + 3) - gameO->player1.x) < 3 && ((gameO->zombie[c].zombieX - 3) - gameO->player1.x) > 3){
                        gameO->zombie[c].zombieX -= 3;
                        gameO->zombie[c].LR = 0;
                        gameO->zombie[c].zombieWcounter++;
                        if((gameO->zombie[c].zombieWcounter >= 30) && (gameO->zombie[c].walkState == 0)){
                            gameO->zombie[c].walkState = 1;
                            gameO->zombie[c].zombieWcounter = 0;
                        }
                        if((gameO->zombie[c].zombieWcounter >= 30) && (gameO->zombie[c].walkState == 1)){
                            gameO->zombie[c].walkState = 2;
                            gameO->zombie[c].zombieWcounter = 0;
                        }
                        if((gameO->zombie[c].zombieWcounter >= 30) && (gameO->zombie[c].walkState == 2)){
                            gameO->zombie[c].walkState = 1;
                            gameO->zombie[c].zombieWcounter = 0;
                        }
                        if(gameO->fire){
                            if(gameO->zombie[c].zombieX <= gameO->player1.bullet.BulletX && gameO->player1.bullet.BulletY >= gameO->zombie[c].zombieY){
                                gameO->zombie[c].zombieLife -= 7;
                                gameO->fire = 0;
                            }
                        }
                        if(gameO->zombie[c].zombieX - 50 <= gameO->player1.x && gameO->player1.y >= 700 && gameO->player1.CanTakeDamage){
                            gameO->player1.hp -= 15;
                            gameO->player1.CanTakeDamage = 0;
                            gameO->player1.GotHit = 1;
                            gameO->player1.HitTimer = 0;
                            if(gameO->player1.hp <= 0){
                                gameO->gameStats.Death = 1; // slained by zombie
                            }
                            ChangeHP(gameO);
                        }
                    }
                }else if(-1*((gameO->zombie[c].zombieX + 3) - gameO->player1.x) > ((gameO->zombie[c].zombieX - 3) - gameO->player1.x)){
                    if(-1*((gameO->zombie[c].zombieX + 3) - gameO->player1.x) > 3 && ((gameO->zombie[c].zombieX - 3) - gameO->player1.x) < 3){
                        gameO->zombie[c].zombieX += 3;
                        gameO->zombie[c].LR = 1;
                        gameO->zombie[c].zombieWcounter++;
                        if((gameO->zombie[c].zombieWcounter >= 30) && (gameO->zombie[c].walkState == 0)){
                            gameO->zombie[c].walkState = 1;
                            gameO->zombie[c].zombieWcounter = 0;
                        }
                        if((gameO->zombie[c].zombieWcounter >= 30) && (gameO->zombie[c].walkState == 1)){
                            gameO->zombie[c].walkState = 2;
                            gameO->zombie[c].zombieWcounter = 0;
                        }
                        if((gameO->zombie[c].zombieWcounter >= 30) && (gameO->zombie[c].walkState == 2)){
                            gameO->zombie[c].walkState = 1;
                            gameO->zombie[c].zombieWcounter = 0;
                        }
                        if(gameO->fire){
                            if(gameO->zombie[c].zombieX >= gameO->player1.bullet.BulletX && gameO->player1.bullet.BulletY >= gameO->zombie[c].zombieY){
                                gameO->zombie[c].zombieLife -= 7;
                                gameO->fire = 0;
                            }
                        }
                        if(gameO->zombie[c].zombieX + 50 >= gameO->player1.x && gameO->player1.y >= 700 && gameO->player1.CanTakeDamage){
                            gameO->player1.hp -= 15;
                            gameO->player1.CanTakeDamage = 0;
                            gameO->player1.GotHit = 1;
                            gameO->player1.HitTimer = 0;
                            if(gameO->player1.hp <= 0){
                                gameO->gameStats.Death = 1; // slained by zombie
                            }
                            ChangeHP(gameO);
                        }
                    }
                }
            }
        }  // end of for loop

        if(!gameO->player1.CanTakeDamage){  // some time before getting another hit by a zombie
            gameO->player1.DamageFrameCounter++;
            if(gameO->player1.DamageFrameCounter >= 30){
                gameO->player1.CanTakeDamage = 1;
                gameO->player1.DamageFrameCounter = 0;
            }
        }

        if(gameO->player1.hp <= 95 && !gameO->player1.GotHit){  // regenerate health
            gameO->player1.HealthTimer++;
            if(gameO->player1.HealthTimer >= 100){ // 100 frames
                gameO->player1.HealthTimer = 0;
                gameO ->player1.hp += 5;
                ChangeHP(gameO);
            }
        }

        if(gameO->gameStats.Death != 0){ // end the game if the hp is equal or below 0
            InitFailScreen(gameO);           
            for(int c=0; c<=200; c++){
                FailScreen(gameO);
            }
            DestroyFailScreen(gameO);
            gameO->run = 0;
        }

        if(gameO->player1.GotHit){ // if the player got hit some time pass before he can be hit again
            gameO->player1.HitTimer++;
            if(gameO->player1.HitTimer >= 120){
                gameO->player1.GotHit = 0;
                gameO->player1.HitTimer = 0;
            }
        }
        ChangeTime(gameO);
        gameO->CaffeineTimer++;
        if(gameO->CaffeineTimer >= 10){
            gameO->player1.caffein -= 0.05;
            gameO->CaffeineTimer = 0;
            ChangeCaffeine(gameO);
        }
        if(gameO->player1.caffein <= 0){
            gameO->gameStats.Death = 2;
        }

        gameO->timeLeft.ChangeTimer++;
        if(gameO->timeLeft.ChangeTimer >= 60){
            gameO->timeLeft.sec--;
            gameO->timeLeft.ChangeTimer = 0;
        }
        if(gameO->timeLeft.sec <= 0 && gameO->timeLeft.min > 0){
            gameO->timeLeft.min--;
            gameO->timeLeft.sec = 60;
        }
        if(gameO->timeLeft.min <= 0 && gameO->timeLeft.sec <= 0 && gameO->gameStats.Score > 0){
            gameO->gameStats.Death = 3;
        }
        if(gameO->timeLeft.min >= 0 && gameO->timeLeft.sec > 0 && gameO->gameStats.Score <= 0){
            InitWinScreen(gameO);
            for(int c=0; c<=200; c++){
                WinScreen(gameO);
            }
            DestroyWinScreen(gameO);
            gameO->run = 0;
        }
    }
}   


void Renderer(GameO *gameO){
    if(!gameO->startScreenInfo.startScreenState){
        SDL_Rect SkinRect = {gameO->player1.x, gameO->player1.y, 200, 198};
        SDL_Rect backgroundRect = {0, -200, 1920, 1280};
        SDL_Rect BulletRect = {gameO->player1.bullet.BulletX, gameO->player1.bullet.BulletY, 65, 10};
        SDL_Rect hpRect = {15, 15, gameO->playerHP.lableW, gameO->playerHP.lableH};
        SDL_Rect BulletNumRect = {15, 47, gameO->player1.bullet.BulletCharW, gameO->player1.bullet.BulletCharH};
        SDL_Rect JumpRightRect = {1160, 972, 265, 44};
        SDL_Rect SmallWallRect = {0, 350, 1920, 90};
        SDL_Rect CaffeineTextRect = {15, 79, gameO->coffeeNumText.CoffeeNumW, gameO->coffeeNumText.CoffeeNumH};
        SDL_Rect zombieRect[MAX_ZOMBIE];
        SDL_Rect CoffeeBeanRect[MAX_COFFEE];
        SDL_Rect scoreRect = {1710, 15, gameO->gameStats.ScoreLableW, gameO->gameStats.ScoreLableH};
        SDL_Rect TimeTextRect = {1710, 47, gameO->timeLeft.TimeTextW, gameO->timeLeft.TimeTextH};

        SDL_RenderCopy(gameO->renderer, gameO->textures.background, NULL, &backgroundRect);
        if(gameO->fire){
            SDL_RenderCopyEx(gameO->renderer, gameO->textures.Bullet, NULL, &BulletRect, 0, NULL, gameO->player1.bullet.BulletLR);
        }
        for(int c=0; c<MAX_COFFEE; c++){
            CoffeeBeanRect[c].x = gameO->coffeeBean[c].x;
            CoffeeBeanRect[c].y = gameO->coffeeBean[c].y;
            CoffeeBeanRect[c].w = 59;
            CoffeeBeanRect[c].h = 60;
            SDL_RenderCopy(gameO->renderer, gameO->textures.Coffee, NULL, &CoffeeBeanRect[c]);
        }
        SDL_RenderCopyEx(gameO->renderer, gameO->textures.skin[gameO->player1.walk], NULL, &SkinRect, 0, NULL, gameO->LR);
        SDL_RenderCopy(gameO->renderer, gameO->textures.JumpThing, NULL, &JumpRightRect);
        for(int c=0; c<gameO->maxZombieNum; c++){
            zombieRect[c].x = gameO->zombie[c].zombieX;
            zombieRect[c].y = gameO->zombie[c].zombieY;
            zombieRect[c].w = 200;
            zombieRect[c].h = 210;
            if(gameO->zombie[c].IsAlive){
                SDL_RenderCopyEx(gameO->renderer, gameO->textures.zombie[gameO->zombie[c].walkState], NULL, &zombieRect[c], 0, NULL, gameO->zombie[c].LR);
            }
        }
        SDL_RenderCopy(gameO->renderer, gameO->textures.SmallWall, NULL, &SmallWallRect);
        SDL_RenderCopy(gameO->renderer, gameO->textures.HPlable, NULL, &hpRect);
        SDL_RenderCopy(gameO->renderer, gameO->textures.BulletNumLable, NULL, &BulletNumRect);
        SDL_RenderCopy(gameO->renderer, gameO->textures.CoffeeNumLable, NULL, &CaffeineTextRect);
        SDL_RenderCopy(gameO->renderer, gameO->textures.ScoreLable, NULL, &scoreRect);
        SDL_RenderCopy(gameO->renderer, gameO->textures.TimeTextLable, NULL, &TimeTextRect);
        SDL_RenderPresent(gameO->renderer);
    }
}


int main(){
    GameO gameO;
    SDL_Window *screen;
    SDL_Renderer *renderer;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Init(SDL_INIT_AUDIO);
    TTF_Init();
    srand(time(NULL));

    gameO.gameStats.ZombieKillGoal = 30;
    gameO.gameStats.Death = 0;
    gameO.player1.x = WIDTH/2-150;
    gameO.player1.y = 500;
    gameO.player1.hp = 100;
    gameO.player1.bullet.BulletsLeft = 16;
    gameO.gameStats.Score = gameO.gameStats.ZombieKillGoal;
    gameO.player1.caffein = 5;
    gameO.timeLeft.min = 2;
    gameO.timeLeft.sec = 0;
    screen = SDL_CreateWindow("Kill Them All",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        WIDTH,
        HIGHT,
        0);

    SDL_SetWindowFullscreen(screen, SDL_WINDOW_FULLSCREEN_DESKTOP);
    renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    gameO.renderer = renderer;

    sprintf(gameO.playerHP.currentHP, "hp:  %d", gameO.player1.hp);
    sprintf(gameO.BulletChar, "Bullets Left:  %d", gameO.player1.bullet.BulletsLeft);
    sprintf(gameO.gameStats.ScoreChar, "Zombies left:  %d", gameO.gameStats.Score);
    sprintf(gameO.coffeeNumText.CoffeeNumChar, "Caffeine:  %.2f", gameO.player1.caffein);
    sprintf(gameO.timeLeft.TimeChar, "Time left:  %d:%d", gameO.timeLeft.min, gameO.timeLeft.sec);

    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);
    int error = 0;
    error = load(&gameO);
    if(error){
        destroy(&gameO, screen);
        return 1;
    }
    InitStartScreen(&gameO);

    gameO.maxZombieNum = MAX_ZOMBIE;
    gameO.gravity = 1;
    gameO.gravityPower = 15;
    gameO.player1.walk = 0;
    gameO.SlowPlayerL = 0;
    gameO.SlowSpeed = 10;
    gameO.SlowPlayerR = 0;
    gameO.slowDown = 12;
    gameO.fire = 0;
    gameO.LR = 0; // 0 for left 1 for right
    gameO.counter = 0;
    gameO.jump = 0;
    gameO.run = 1;
    gameO.player1.walkSpeed = 10;
    gameO.JumpThingState = 0;
    gameO.zombieGravityPower = 15;
    gameO.startScreenInfo.startScreenTime = 0;
    gameO.player1.CanTakeDamage = 1;
    gameO.player1.DamageFrameCounter = 0;
    gameO.startScreenInfo.startScreenState = 1;
    gameO.player1.HealthTimer = 0;
    gameO.player1.GotHit = 0;
    gameO.CaffeineTimer = 0;
    gameO.player1.CanShot = 1;
    gameO.player1.ShotTimer = 0;
    gameO.timeLeft.ChangeTimer = 0;
    gameO.timeLeft.Stime = time(NULL);

    for(int c=0; c<MAX_COFFEE; c++){
        gameO.coffeeBean[c].y = 350 - 60;
        gameO.coffeeBean[c].SlowSpeed = 10;
        gameO.coffeeBean[c].UpDown = 1;
        if(randNum(1, 20) < 15){
            gameO.coffeeBean[c].x = randNum(67, 1100); // randum position for coffe on the left side of the small wall
        }else{
            gameO.coffeeBean[c].x = randNum(1370, 1800); // randum position for coffe on the right side of the small wall
        }
    }

    for(int c=0; c<gameO.maxZombieNum; c++){
        if(randNum(0, 10) >= 5){
            gameO.zombie[c].zombieX = randNum(1920, 2600);
        }else if(randNum(0, 10) < 5){
            gameO.zombie[c].zombieX = randNum(-680, 0);
        }
        gameO.zombie[c].zombieY = 400;
        gameO.zombie[c].LR = 0;
        gameO.zombie[c].walkState = 0;
        gameO.zombie[c].zombieWcounter = 0;
        gameO.zombie[c].IsAlive = 1;
        gameO.zombie[c].zombieLife = 30;
    }

    while(gameO.run){ // main game loop
        Renderer(&gameO);
        Events(screen, &gameO);
        CollisionDetection(&gameO);
    }

    destroy(&gameO, screen);  // free used memory
    return 0;
}