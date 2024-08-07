#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <iostream>
#include <vector>
#include "struct.h"
#include "variable.h"
#include "animation.h"
#include "init.h"
#include "menu.h"
#include "movement.h"
#include "bullets.h"
#include "enemy.h"
#include "collisionAndScore.h"

int main(int argc, char* argv[])
{
   initSDL2(renderer, window);
   handleTexture();
   font1 = TTF_OpenFont("AldotheApache.ttf", 100);
   font2 = TTF_OpenFont("SunnySpellsBasic.ttf", 40);
   Mix_Music *music = loadMusic("highlands.mp3");
   if (music) {
    playMusic(music);
   }

    scoreTexture = nullptr;
    mainCharacter player;

    bool quit = false;
    renderMenu(renderer, quit, startGame, menuActive);

    SDL_Event e;

    while (!quit){
        while (SDL_PollEvent(&e)){
            handleMovements(e, player.moveLeft, player.moveRight, player.moveUp, player.moveDown, player.fire, player.idle, pause, player);
            if (e.type == SDL_KEYDOWN)
        {
            switch (e.key.keysym.sym)
            {
                case SDLK_0:
                    quit = true;
                    break;
                case SDLK_ESCAPE:
                    pause = true;
                    break;
            }
        }
    }
    while (menuActive && !quit)
        {
            renderMenu(renderer, startGame, quit, menuActive);
            
        }
    if (pause) {
        renderPauseMenu(renderer, quit, pause, menuActive);
        continue;
    }
    if (lives <= 0)
    {
        gameOver = true;
    }
    if (gameOver)
    {
        renderGameOver(renderer, font1,font2, fontColor, quit, startGame, score);
            
    }
    
    SDL_RenderClear(renderer);
    SDL_Delay(50);
    SDL_RenderCopy(renderer, background, NULL, NULL);
    move(player.moveLeft, player.moveRight, player.moveUp, player.moveDown, player.idle, player.pos, player.currentFrame);
    moveBullets();
    for (auto &bullet : bullets)
    {
        SDL_RenderCopy(renderer, bullet.texture, NULL, &bullet.bulletRect);
    }
        handleCollision();
        enemyMove(player);
        updateEnemy();

        updateScoreTexture(renderer, font2, score, scoreTexture, scoreRect);
        SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);
        renderLives(renderer, heartTexture, lives);
        SDL_RenderPresent(renderer);
        limit(player.pos.x, player.pos.y, player.pos.w, player.pos.h);
       }
       Mix_FreeMusic(music);
       Mix_Quit();
       TTF_Quit();
       SDL_DestroyRenderer(renderer);
       SDL_DestroyWindow(window);
       SDL_Quit();
       return 0;
}

