#ifndef character_h
#define character_h


void handleMovements(SDL_Event &e, bool &moveLeft, bool &moveRight, bool &moveUp, bool &moveDown, bool &fire,bool &idle, bool &pause, mainCharacter &player)
{
    if (e.type == SDL_KEYDOWN)
    {
        switch (e.key.keysym.sym)
        {
            case SDLK_a:
                moveLeft = true;
                break;
            case SDLK_d:
                moveRight = true;
                break;
            case SDLK_w:
                moveUp = true;
                break;
            case SDLK_s:
                moveDown = true;
                break;
            case SDLK_ESCAPE:
                pause = true;
                break;
            case SDLK_j:
                if(!fire)
                {
                    shootBullet(player);
                    fire = true;
                }
                Uint32 currentShoot = SDL_GetTicks();
                if (currentShoot - lastShoot >= coolDown)
                {
                    shootBullet(player);
                    lastShoot = currentShoot;
                }
                break;
                /* case SDLK_j:
                Uint32 currentShoot = SDL_GetTicks();
                if (!fire && currentShoot - lastShoot >= coolDown) {
                    shootBullet(player);
                    fire = true;
                    lastShoot = currentShoot;
                }
                break;*/
        }
    }
    else if (e.type == SDL_KEYUP)
    {
        switch (e.key.keysym.sym)
        {
            case SDLK_a:
                moveLeft = false;
                idle = true;
                break;
            case SDLK_d:
                moveRight = false;
                idle = true;
                break;
            case SDLK_w:
                moveUp = false;
                idle = true;
                break;
            case SDLK_s:
                moveDown = false;
                idle = true;
                break;
        }
    }
}
void limit(int &characterX, int &characterY, int &characterW, int &characterH)
{
    if (characterX < 0) {
           characterX = 0;
       }
       if (characterY < 0) {
           characterY = 0;
       }
       if (characterX + characterW > WINDOW_WIDTH) {
           characterX = WINDOW_WIDTH - characterW;
       }
       if (characterY + characterH > WINDOW_HEIGHT) {
           characterY = WINDOW_HEIGHT - characterH;
       }
   }

void move(bool &moveLeft, bool &moveRight, bool &moveUp, bool &moveDown,bool &idle, SDL_Rect &pos, int &currentFrame)
{
        if(moveLeft)
        {
            pos.x -= velocity;
            handleAnimationUpdate(renderer, mainCharacterRun, pos, 1, 6, currentFrame, 0, 6);
        }
        else if(moveRight)
        {
            pos.x += velocity;
            handleAnimationUpdate(renderer, mainCharacterRun, pos, 1, 6, currentFrame, 0, 6);
        }
        else if(moveUp)
        {
            pos.y -= velocity;
            handleAnimationUpdate(renderer, mainCharacterRun, pos, 1, 6, currentFrame, 0, 6);
        }
        else if(moveDown)
        {
            pos.y += velocity;
            handleAnimationUpdate(renderer, mainCharacterRun, pos, 1, 6, currentFrame, 0, 6);
        }
         else if(idle){
            handleAnimationUpdate(renderer, mainCharacterIdle, pos, 1, 5, currentFrame, 0, 5);
        }
    }

#endif /* character_h */
