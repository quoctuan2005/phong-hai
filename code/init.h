#ifndef init_h
#define init_h

void initSDL2(SDL_Renderer *&renderer, SDL_Window *&window)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG);
    Mix_Init( MIX_INIT_WAVPACK|MIX_INIT_MP3);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    TTF_Init();
    window = SDL_CreateWindow("Ban Quai", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}
Mix_Music *loadMusic(const std::string &filePath) {
    Mix_Music *music = Mix_LoadMUS(filePath.c_str());
    if (!music) {
            std::cerr << "Error loading music:" << Mix_GetError() << std::endl;
            return nullptr;
        }
    return music;
}
SDL_Texture *loadTexture (const std::string filePath, SDL_Renderer *renderer)
{
    SDL_Surface *surface = IMG_Load(filePath.c_str());
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}
void playMusic(Mix_Music *music) {
    if (Mix_PlayMusic(music, -1) == -1) { // -1 means loop forever
        std::cerr << "Error playing music: " << Mix_GetError() << std::endl;
    }
}
void handleTexture()
{
    background = loadTexture("background.png", renderer);
    mainCharacterIdle = loadTexture("Gunner_Green_Idle.png", renderer);
    mainCharacterRun = loadTexture("Gunner_Green_Run.png", renderer);
    bulletTexture = loadTexture("bullet.png", renderer);
    enemy = loadTexture("monster.png", renderer);
    menuTexture = loadTexture("mainMenu.png", renderer);
    instructionTexture = loadTexture("controlsInstruction.png", renderer);
    heartTexture = loadTexture("heart.png", renderer);
    scoreMenuTexture = loadTexture("background.png", renderer);
    pauseTexture = loadTexture("pause.png", renderer);
    continueTexture = loadTexture("continue.png", renderer);
    exitTexture = loadTexture("exit.png", renderer);
    playTexture = loadTexture("play.png", renderer);
    controlTexture = loadTexture("controls.png", renderer);
    backTexture = loadTexture("back_button.png", renderer);
    restartTexture = loadTexture("restart.png", renderer);
}
#endif /* init_h */
