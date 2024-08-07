#ifndef menu_h
#define menu_h

bool checkMouseClick(int mouseX, int mouseY, int buttonX, int buttonY, int buttonWidth, int buttonHeight) {
    return (mouseX >= buttonX && mouseX <= buttonX + buttonWidth && mouseY >= buttonY && mouseY <= buttonY + buttonHeight);
}
void renderMenu(SDL_Renderer *renderer, bool &startGame, bool &quit, bool &menuActive) {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            quit = true;
        } else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);

            if (checkMouseClick(mouseX, mouseY, MENU_PLAY_X, MENU_PLAY_Y, MENU_PLAY_WIDTH, MENU_PLAY_HEIGHT)) {
                startGame = true;
                menuActive = false;
            } else if (checkMouseClick(mouseX, mouseY, MENU_INSTRUCTION_X, MENU_INSTRUCTION_Y, MENU_INSTRUCTION_WIDTH, MENU_INSTRUCTION_HEIGHT)) {
                renderInstruction(renderer,quit, menuActive);
            } else if (checkMouseClick(mouseX, mouseY, MENU_EXIT_X, MENU_EXIT_Y, MENU_EXIT_WIDTH, MENU_EXIT_HEIGHT)) {
                quit = true;
            }
        }
    }

    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, menuTexture, NULL, NULL);

    SDL_Rect playRect = {MENU_PLAY_X, MENU_PLAY_Y, MENU_PLAY_WIDTH, MENU_PLAY_HEIGHT};
    SDL_RenderCopy(renderer, playTexture, NULL, &playRect);

    SDL_Rect controlRect = {MENU_INSTRUCTION_X, MENU_INSTRUCTION_Y, MENU_INSTRUCTION_WIDTH, MENU_INSTRUCTION_HEIGHT};
    SDL_RenderCopy(renderer, controlTexture, NULL, &controlRect);

    SDL_Rect exitRect = {MENU_EXIT_X, MENU_EXIT_Y, MENU_EXIT_WIDTH, MENU_EXIT_HEIGHT};
    SDL_RenderCopy(renderer, exitTexture, NULL, &exitRect);

    SDL_RenderPresent(renderer);
}
void renderInstruction(SDL_Renderer *renderer,bool &quit, bool &menuActive) {
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, instructionTexture, NULL, NULL);
    
    SDL_Rect backButtonRect = { 10 , 10 , 50 , 50};
    SDL_RenderCopy (renderer, backTexture, NULL, &backButtonRect);
    SDL_RenderPresent(renderer);

    SDL_Event event;
    while (SDL_WaitEvent(&event)) {
        if (event.type == SDL_QUIT) {
            menuActive = false;
            break;
        } else if (event.type == SDL_MOUSEBUTTONDOWN) {
            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);
            if (checkMouseClick(mouseX, mouseY, 10, 10, 50, 50)) {
                menuActive = true;
                renderMenu(renderer, quit, startGame, menuActive);
                break;
            }
        }
    }
}

void renderPauseMenu(SDL_Renderer* renderer, bool& quit, bool& paused, bool& menuActive)
{
    SDL_RenderCopy(renderer, pauseTexture, NULL, NULL);
   
    SDL_Rect continueRect = { MENU_CONTINUE_X, MENU_CONTINUE_Y, MENU_CONTINUE_WIDTH, MENU_CONTINUE_HEIGHT };
    SDL_RenderCopy(renderer, continueTexture, NULL, &continueRect);

    SDL_Rect exitRect = { MENU_EXIT_X, MENU_EXIT_Y, MENU_EXIT_WIDTH, MENU_EXIT_HEIGHT };
    SDL_RenderCopy(renderer, exitTexture, NULL, &exitRect);

    SDL_RenderPresent(renderer);

    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            quit = true;
            paused = false;
            menuActive = false;
            break;
        } else if (e.type == SDL_MOUSEBUTTONDOWN) {
            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);
            if (checkMouseClick(mouseX, mouseY, continueRect.x, continueRect.y, continueRect.w, continueRect.h))
            {
                paused = false;
                menuActive = false;
                break; // Exit the event loop
            } else if (checkMouseClick(mouseX, mouseY, exitRect.x, exitRect.y, exitRect.w, exitRect.h)) {
                paused = false;
                menuActive = true;
                gameOver = false;
                score = 0;
                lives = 3;
                bullets.clear();
                zombie.clear();
                break;
            }
        }
    }
}
void resetGame()
{
    score = 0;
    lives = 3;
    bullets.clear();
    zombie.clear();
    velocity = 20;
    lastEnemySpawnTime = 0;
    enemySpawnDelay = 2000;
    enemyCountIncrease = 1;
    speedIncrease = 1;
    enemySpawnDelayDecrease = 100;

}
void renderGameOver(SDL_Renderer *renderer, TTF_Font *font1,TTF_Font* font2, SDL_Color fontColor, bool &quit, bool &startGame, int score) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    
    SDL_RenderCopy(renderer, scoreMenuTexture, NULL, NULL);
    
    std::string gameOverText = "GAME OVER";
    SDL_Surface *gameOverSurface = TTF_RenderText_Solid(font1, gameOverText.c_str(), fontColor);
    SDL_Texture *gameOverTexture = SDL_CreateTextureFromSurface(renderer, gameOverSurface);
    SDL_Rect gameOverRect;
    SDL_QueryTexture(gameOverTexture, NULL, NULL, &gameOverRect.w, &gameOverRect.h);
    gameOverRect.x = (WINDOW_WIDTH - gameOverRect.w) / 2;
    gameOverRect.y = WINDOW_HEIGHT / 4;
    SDL_RenderCopy(renderer, gameOverTexture, NULL, &gameOverRect);
    SDL_FreeSurface(gameOverSurface);
    SDL_DestroyTexture(gameOverTexture);
    
    std::string scoreText = "YOUR SCORE IS: " + std::to_string(score);
    SDL_Surface *scoreSurface = TTF_RenderText_Solid(font2, scoreText.c_str(), fontColor);
    SDL_Texture *scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
    SDL_Rect scoreRect;
    SDL_QueryTexture(scoreTexture, NULL, NULL, &scoreRect.w, &scoreRect.h);
    scoreRect.x = (WINDOW_WIDTH - scoreRect.w) / 2;
    scoreRect.y = WINDOW_HEIGHT / 2;
    SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);
    SDL_FreeSurface(scoreSurface);
    SDL_DestroyTexture(scoreTexture);
    
    SDL_Rect restartRect = {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + 100 , 100 , 100};
    SDL_RenderCopy(renderer, restartTexture, NULL, &restartRect);
    
    SDL_RenderPresent(renderer);
    
    SDL_Event event;
    
    bool restartClicked = false;
        while (!quit && !restartClicked) {
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    quit = true;
                } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                    int mouseX, mouseY;
                    SDL_GetMouseState(&mouseX, &mouseY);
                    if (checkMouseClick(mouseX, mouseY, restartRect.x, restartRect.y, restartRect.w, restartRect.h)) {
                        startGame = true;
                        gameOver = false;
                        resetGame();
                        restartClicked = true;
                        break;
                }
            }
        }
    }
}


#endif /* menu_h */
