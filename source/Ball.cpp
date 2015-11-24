#include "Ball.h"
#include <iostream>

void Ball::addRandomDevice(std::random_device *rnd)
{
    //rand = rnd;
}

void Ball::reverseXVelocity()
{    
    speed[0] = -speed[0];
}

void Ball::reverseYVelocity()
{
    speed[1] = -speed[1];
}

void Ball::moveRight()
{
    if (speed[0] < 0) speed[0] = -speed[0];
}

void Ball::moveLeft()
{
    if (speed[0] > 0) speed[0] = -speed[0];
}

void Ball::alterXVelocity(float x)
{
    if (x < -10) x = -10;
    if (x > 10) x = 10;
    speed[0] = x;
}

void Ball::setBoost(float bst)
{
    if (boostApproved) boost = bst;
}

void Ball::approveBoost(bool bst)
{
    if (bst) approveTime = SDL_GetTicks();
    boostApproved = bst;
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
    float defSpeed = startSpeed[0];

    speed[0] = defSpeed * rndX * opposite;
    speed[1] = defSpeed * rndY * (opposite);

    boost = 0;
}

float Ball::getXSpeed() const
{
    return speed[0];
}

void Ball::update()
{
    x += (speed[0] * boost);
    y += (speed[1] * boost);

    if (boost > 1) boost -= 0.025f;
    else if (boost < 1) boost = 1;

    image->rect->x = int(x - (width >> 1));
    image->rect->y = int(y - (height >> 1));

    // wait a while before disabling boost posibility
    if (boostApproved && SDL_GetTicks() - approveTime > 150)
        boostApproved = false;
}

