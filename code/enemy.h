#ifndef enemy_h
#define enemy_h

void updateEnemy()
{
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - lastEnemySpawnTime >= enemySpawnDelay) {
        lastEnemySpawnTime = currentTime;
        int numEnemy = rand() % 3 + 1 + (score / 20) * enemyCountIncrease;
        for (int i = 0; i < enemyCountIncrease; i++) {
            Enemy newEnemy;
            newEnemy.posEnemy.x = WINDOW_WIDTH;
            newEnemy.posEnemy.y = rand() % (WINDOW_HEIGHT - CHARACTER_HEIGHT);
            newEnemy.posEnemy.w = CHARACTER_WIDTH;
            newEnemy.posEnemy.h = CHARACTER_HEIGHT;
            newEnemy.alive = true;
            newEnemy.speed = rand()%( 8 + (score / 20) * speedIncrease) +  2 + (score / 20) * speedIncrease ;
            zombie.push_back(newEnemy);
        }
    }
    if (score % 20 == 0 && score > 0)
    {
        enemySpawnDelay = std::max(500U, enemySpawnDelay - enemySpawnDelayDecrease);
    }
}
void enemyMove(mainCharacter player)
{
    for (auto &z : zombie) {
        if (z.alive) {
            z.posEnemy.x -= z.speed; 
            if (z.posEnemy.x < -CHARACTER_WIDTH) {
                lives--;
                z.alive = false;
            }else {
                handleAnimationUpdate(renderer, enemy, z.posEnemy, 1, 6, z.currentFrame, 0, 6);
            }
        }
    }
    zombie.erase(std::remove_if(zombie.begin(), zombie.end(), [](Enemy &z) {
        return !z.alive;
    }), zombie.end());
}
#endif /* enemy_h */
