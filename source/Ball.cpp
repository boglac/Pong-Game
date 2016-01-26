#include "Ball.h"
#include <iostream>

void Ball::addRandomDevice(std::random_device *rnd)
{
    Rand = rnd;
}

void Ball::reverseXVelocity()
{    
    Speed[0] = -Speed[0];
}

void Ball::reverseYVelocity()
{
    Speed[1] = -Speed[1];
}

void Ball::moveRight()
{
    if (Speed[0] < 0) Speed[0] = -Speed[0];
}

void Ball::moveLeft()
{
    if (Speed[0] > 0) Speed[0] = -Speed[0];
}

void Ball::alterXVelocity(float x)
{
    if (x < -10) x = -10;
    if (x > 10) x = 10;
    Speed[0] = x;
}

void Ball::setBoost(float bst)
{
    if (BoostApproved) Boost = bst;
}

void Ball::approveBoost(bool bst)
{
    if (bst) ApproveTime = SDL_GetTicks();
    BoostApproved = bst;
}

void::Ball::reset()
{
    Actor::reset();
    
    // prepare some randomized (partly) move parameters for ball at reset
    // (after scoring or loosing a point)
    const short range = 2;
    float options[range + 1] = {0.7f, 1.0f, 1.4f};

    std::mt19937 gen((*rand)());
    std::uniform_int_distribution<> dist(0, range);
    
    float rndX = options[dist(gen)];
    float rndY = options[dist(gen)];
        
    std::mt19937 gen2((*rand)());
    std::uniform_int_distribution<> trigger(0, 1);
    
    int opposite = 1;
    if (!trigger(gen)) opposite = -1;

    // starting speed is the same on both axes
    float defSpeed = StartSpeed[0];

    Speed[0] = defSpeed * rndX * opposite;
    Speed[1] = defSpeed * rndY * (opposite);

    Boost = 0;
    PrevBorCol = 0;
    PrevColHor = PrevColVert = 0;
}

float Ball::getXSpeed() const
{
    return Speed[0];
}

eCollisionResult Ball::handleBorderCollision(eBorderPosition borderPos, ushort borderID)
{
    // Because current Ball object has collided with a border (and a border isn't an Actor
    // object for sure), set prevColHor and prevColVert pointers to nullptr, so
    // that collisions with other Actor objects is possible again.
    PrevColHor = 0;
    PrevColVert = 0;

    if (borderPos == BORDER_TOP) return RESULT_SCORE;
    if (borderPos == BORDER_BOTTOM) return RESULT_LOSE;
    
    if ((borderPos == BORDER_LEFT || borderPos == BORDER_RIGHT) && PrevBorCol != borderID) {
        PrevBorCol = borderID;
        reverseXVelocity();
        return RESULT_BALLCOLL;
    }
}

void Ball::update()
{
    X += (Speed[0] * Boost);
    Y += (Speed[1] * Boost);

    if (Boost > 1) Boost -= 0.025f;
    else if (Boost < 1) Boost = 1;

    ImageHandler->Rect->x = int(X - (Width >> 1));
    ImageHandler->Rect->y = int(Y - (Height >> 1));

    // wait a while before disabling boost posibility
    if (BoostApproved && SDL_GetTicks() - ApproveTime > 150)
        BoostApproved = false;
}

