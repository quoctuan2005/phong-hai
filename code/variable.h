#ifndef variable_h
#define variable_h

int WINDOW_WIDTH = 1024;
int WINDOW_HEIGHT = 704;
int CHARACTER_HEIGHT = 100;
int CHARACTER_WIDTH = 100;
int BULLET_HEIGHT = 60;
int BULLET_WIDTH = 60;
int MENU_CONTINUE_X = WINDOW_WIDTH / 2 - 50;
int MENU_CONTINUE_Y = WINDOW_HEIGHT / 2 - 50;
int MENU_CONTINUE_WIDTH = 200;
int MENU_CONTINUE_HEIGHT = 100;
int MENU_EXIT_X = WINDOW_WIDTH / 2 - 50;
int MENU_EXIT_Y = WINDOW_HEIGHT / 2 + 100;
int MENU_EXIT_WIDTH = 200;
int MENU_EXIT_HEIGHT = 50;
int MENU_PLAY_X = WINDOW_WIDTH / 2 - 50;
int MENU_PLAY_Y = WINDOW_HEIGHT / 2 - 50;
int MENU_PLAY_WIDTH = 200;
int MENU_PLAY_HEIGHT = 50;
int MENU_INSTRUCTION_X = WINDOW_WIDTH / 2 - 50;
int MENU_INSTRUCTION_Y = WINDOW_HEIGHT / 2 + 20;
int MENU_INSTRUCTION_WIDTH = 200;
int MENU_INSTRUCTION_HEIGHT = 50;

int velocity = 20;
Uint32 lastEnemySpawnTime = 0;
Uint32 enemySpawnDelay = 2000;
int enemyCountIncrease = 1;
int speedIncrease = 1;
Uint32 enemySpawnDelayDecrease = 100;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture* background, *mainCharacterIdle, *mainCharacterRun, *bulletTexture, *enemy, *menuTexture,  *instructionTexture,*pauseTexture, *heartTexture, *scoreMenuTexture,*continueTexture, *exitTexture, *playTexture, *controlTexture, *backTexture , *restartTexture;
bool pause = false;
bool startGame = false;
bool menuActive = true;
bool gameOver = false;
Uint32 lastShoot = 0;

TTF_Font *font1, *font2;
SDL_Color fontColor = { 255 , 255 , 255, 255};
int score = 0;
SDL_Texture *scoreTexture = NULL;
SDL_Rect scoreRect;
int lives = 3;
Uint32 coolDown = 200;


std::vector<Bullet>bullets;
std::vector<Enemy>zombie;
std::vector<size_t> zombiesToRemove;
std::vector<size_t> bulletsToRemove;

void initSDL2 (SDL_Renderer *&renderer, SDL_Window *&window);
void handleTexture();
void handleAnimationUpdate(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect characterPos, int column, int width, int &currentFrame, int animationPosition, int numberFrame);
void handleMovements(SDL_Event &e, bool &moveLeft, bool &moveRight, bool &moveUp, bool &moveDown, bool &fire,bool &idle, bool &pause, mainCharacter &player);
void move(bool &moveLeft, bool &moveRight, bool &moveUp, bool &moveDown,bool &idle,SDL_Rect &pos, int &currentFrame);
void bulletFire (bool &fire, int &bulletX);
void limit(int &characterX, int &characterY, int &characterW, int &characterH);
void shootBullet(mainCharacter &player);
void updateEnemy();
void enemyMove(mainCharacter player);
void moveBullets();
void handleCollision();
void updateScoreTexture(SDL_Renderer *renderer, TTF_Font *font2, int score, SDL_Texture *&scoreTexture, SDL_Rect &scoreRect);
void renderInstruction(SDL_Renderer *renderer,bool &quit, bool &menuActive);
void renderPauseMenu(SDL_Renderer* renderer, bool &quit, bool &pause, bool &menuActive);
void renderMenu(SDL_Renderer *renderer, bool &startGame, bool &quit, bool &menuActive);
#endif /* variable_h */
