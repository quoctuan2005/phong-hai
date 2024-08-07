#ifndef animation_h
#define animation_h
void handleAnimationUpdate(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect characterPos, int column, int width, int &currentFrame, int animationPosition, int numberFrame)
{
    int textureW, textureH;
    SDL_QueryTexture(texture, NULL, NULL, &textureW, &textureH);
    textureW /= width;
    textureH /= column;
    SDL_Rect src = {currentFrame * textureW, textureH * animationPosition, textureW, textureH};
    SDL_Rect dst = {characterPos.x, characterPos.y, characterPos.w, characterPos.h};
    currentFrame = (currentFrame + 1) % numberFrame;
    SDL_RenderCopy(renderer, texture, &src, &dst);
}

#endif /* animation_h */
