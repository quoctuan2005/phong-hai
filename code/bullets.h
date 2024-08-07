#ifndef bullets_h
#define bullets_h


void shootBullet(mainCharacter &player)
{
    Bullet newBullet;
    newBullet.texture = loadTexture("bullet.png", renderer);
    newBullet.bulletRect.x = player.pos.x + 27;
    newBullet.bulletRect.y = player.pos.y + 17;
    newBullet.bulletRect.w = BULLET_WIDTH;
    newBullet.bulletRect.h = BULLET_HEIGHT;
    bullets.push_back(newBullet);
}
void moveBullets()
{
    for(auto &bullet : bullets){
            bullet.bulletRect.x += 50;
    }
    bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](Bullet &bullet){
        return bullet.bulletRect.x > WINDOW_WIDTH;
    }), bullets.end());
}

#endif /* bullets_h */
