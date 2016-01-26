#pragma once
#include "Actor.h"
#include "Ball.h"
#include <random>

/*
    class
    Enemy
    inherits Actor
*/
class Enemy : public Actor
{
public:
    Enemy(const ActorData &params) : Actor(params)
    {
        Speed = params.extra;
        StartSpeed = Speed;

        rand = nullptr;
    }

    void setDirection(float sp);
    
    eCollisionResult handleBorderCollision(eBorderPosition borderPos, ushort borderID);
    eCollisionResult handleBallCollision(Actor *ball);

    void reverse();
    void stabilize();
    void reset();
    void update();
    void stop();

    void addRandomDevice(std::random_device *rnd);

private:
    float Speed;
    float StartSpeed;
    float Direction;

    std::random_device *rand;
};

