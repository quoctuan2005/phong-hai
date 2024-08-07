#ifndef struct_h
#define struct_h
struct mainCharacter
{
    SDL_Rect pos = {0,100,100,100};
    int currentFrame = 0;
    bool moveLeft = false, moveRight = false, moveDown = false, moveUp = false;
    bool fire = false;
    bool idle = true;
};
struct Enemy
{
    SDL_Rect posEnemy;
    int currentFrame = 0;
    bool alive = true;
    int speed;
};
struct Bullet
{
    SDL_Texture* texture;
    SDL_Rect bulletRect;
};

#endif /* struct_h */
