#include "Enemy.h"

void Enemy::addRandomDevice(std::random_device *rnd)
{
    rand = rnd;
}

void Enemy::reverse()
{
    speed = -speed;
    direction = 0;
}

void Enemy::stabilize()
{
    std::mt19937 gen((*rand)());
    std::uniform_int_distribution<> trigger(0, 1);

    int opposite = 1;
    if (trigger(gen)) opposite = -1;

    speed = opposite * startSpeed;
}

void Enemy::update()
{
    if (direction < 0 && speed > 0 || direction > 0 && speed < 0) {
        stabilize();
        speed /= 2;
        reverse();
    }

    x += speed;
    image->rect->x = int(x + (width >> 1));
}

void Enemy::stop()
{
    speed = 0;
}

void Enemy::reset()
{
    Actor::reset();
    stabilize();
}

void Enemy::setDirection(float sp)
{
    direction = sp;
}
