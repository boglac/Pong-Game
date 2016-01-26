#include "Player.h"

void Player::update()
{
    ImageHandler->Rect->x = int(X - (Width >> 1));
    ImageHandler->Rect->y = int(Y - (Height >> 1));
}

void Player::setPos(float posX)
{
    X = posX;
}

void Player::getPos(float &posX, float &posY) const
{
    posX = X;
    posY = Y;
}

eCollisionResult Player::handleBallCollision(Actor *ball)
{
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

    return RESULT_BALLCOLL;
}