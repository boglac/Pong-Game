#include "Player.h"

void Player::update()
{
    image->rect->x = int(x - (width >> 1));
    image->rect->y = int(y - (height >> 1));
}

void Player::setPos(float posX)
{
    x = posX;
}

void Player::getPos(float &posX, float &posY) const
{
    posX = x;
    posY = y;
}
