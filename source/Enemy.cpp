#include "Enemy.h"
#include <iostream>

void Enemy::addRandomDevice(std::random_device *rnd)
{
    rand = rnd;
}

void Enemy::reverse()
{
    Speed = -Speed;
    Direction = 0;
}

void Enemy::stabilize()
{
    std::mt19937 gen((*rand)());
    std::uniform_int_distribution<> trigger(0, 1);

    int opposite = 1;
    if (trigger(gen)) opposite = -1;

    Speed = opposite * StartSpeed;
}

void Enemy::update()
{
    if (Direction < 0 && Speed > 0 || Direction > 0 && Speed < 0) {
        stabilize();
        Speed /= 2;
        reverse();
    }

    X += Speed;
    ImageHandler->Rect->x = int(X + (Width >> 1));
}

eCollisionResult Enemy::handleBorderCollision(eBorderPosition borderPos, ushort borderID)
{
    reverse();
    return RESULT_NORMAL;
}

eCollisionResult Enemy::handleBallCollision(Actor *ball)
{
    stabilize();

    Ball *tempBall = static_cast<Ball*>(ball);
    int startX, startY, endX, endY;

    leftSideLine(startX, startY, endX, endY);
    if (SDL_IntersectRectAndLine(tempBall->getImageRect(), &startX, &startY, &endX, &endY)) {
        if (tempBall->PrevColHor != ID) {
            tempBall->moveLeft();

            // store an object a ball currently collides with horizontally
            tempBall->PrevColHor = ID;
        }
    }
    else {
        rightSideLine(startX, startY, endX, endY);
        if (SDL_IntersectRectAndLine(tempBall->getImageRect(), &startX, &startY, &endX, &endY)) {
            if (tempBall->PrevColHor != ID) {
                tempBall->moveRight();
                tempBall->PrevColHor = ID;
            }
        }
    }

    // handle top/bottom collision a bit differently
    topSideLine(startX, startY, endX, endY);
    if (SDL_IntersectRectAndLine(tempBall->getImageRect(), &startX, &startY, &endX, &endY)) {
        if (tempBall->PrevColVert != ID) {

            // calculate new angle (more to the sides of object, greater the angle)
            float xVel = -10.0f * (X - tempBall->getX()) / Width;
            tempBall->alterXVelocity(xVel);
            tempBall->reverseYVelocity();

            // store an object a ball currently collides with vertically
            tempBall->PrevColVert = ID;
        }
    }
    else {
        bottomSideLine(startX, startY, endX, endY);
        if (SDL_IntersectRectAndLine(tempBall->getImageRect(), &startX, &startY, &endX, &endY)) {
            if (tempBall->PrevColVert != ID) {

                float xVel = -10.0f * (X - tempBall->getX()) / Width;
                tempBall->alterXVelocity(xVel);
                tempBall->reverseYVelocity();

                tempBall->PrevColVert = ID;
            }
        }
    }

    tempBall->PrevBorCol = 0;
    tempBall->approveBoost(true);

    return RESULT_NORMAL;
}

void Enemy::stop()
{
    Speed = 0;
}

void Enemy::reset()
{
    Actor::reset();
    stabilize();
}

void Enemy::setDirection(float sp)
{
    Direction = sp;
}
