#ifndef collisionAndScore_h
#define collisionAndScore_h

void handleCollision() {
    zombiesToRemove.clear();
    bulletsToRemove.clear();

    for (size_t i = 0; i < bullets.size(); ++i) {
        for (size_t j = 0; j < zombie.size(); ++j) {
            if (bullets[i].bulletRect.x + bullets[i].bulletRect.w >= zombie[j].posEnemy.x + 40 &&
                bullets[i].bulletRect.x <= zombie[j].posEnemy.x + zombie[j].posEnemy.w - 40 &&
                bullets[i].bulletRect.y + bullets[i].bulletRect.h >= zombie[j].posEnemy.y + 40 &&
                bullets[i].bulletRect.y <= zombie[j].posEnemy.y + zombie[j].posEnemy.h - 40) {
                zombiesToRemove.push_back(j);
                bulletsToRemove.push_back(i);
                score += 1;
            }
        }
    }

    std::sort(zombiesToRemove.rbegin(), zombiesToRemove.rend());
    std::sort(bulletsToRemove.rbegin(), bulletsToRemove.rend());

    for (size_t index : zombiesToRemove) {
        if (index < zombie.size()) {
            zombie.erase(zombie.begin() + index);
        }
    }

    for (size_t index : bulletsToRemove) {
        if (index < bullets.size()) {
            bullets.erase(bullets.begin() + index);
        }
    }
}
void renderLives(SDL_Renderer* renderer, SDL_Texture* heartTexture, int lives)
{
    for (int i = 0; i < lives; i++){
        SDL_Rect heartRect = {10 + i * 40, 0 , 100 , 100};
        SDL_RenderCopy(renderer, heartTexture, NULL, &heartRect);
    }
}
void updateScoreTexture(SDL_Renderer *renderer, TTF_Font *font2, int score, SDL_Texture *&scoreTexture, SDL_Rect &scoreRect){
    std::string scoreText = "KILL: " + std::to_string(score);
    SDL_Surface *surface = TTF_RenderText_Solid(font2, scoreText.c_str(), fontColor);
    
    if (scoreTexture!= nullptr) {
        SDL_DestroyTexture(scoreTexture);
    }
    
    scoreTexture = SDL_CreateTextureFromSurface(renderer, surface);
    int textWidth, textHeight;
    SDL_QueryTexture(scoreTexture, NULL, NULL, &textWidth, &textHeight);
    
    scoreRect.x = WINDOW_WIDTH - textWidth - 20;
    scoreRect.y = 20;
    scoreRect.w = textWidth;
    scoreRect.h = textHeight;
    
    SDL_FreeSurface(surface);
}



#endif /* collisionAndScore_h */
