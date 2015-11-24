#pragma once
#include "Actor.h"
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
        speed = params.extra;
        startSpeed = speed;

        rand = nullptr;
    }

    void setDirection(float sp);

    void reverse();
    void stabilize();
    void reset();
    void update();
    void stop();

    void addRandomDevice(std::random_device *rnd);

private:
    float speed;
    float startSpeed;
    float direction;

    std::random_device *rand;
};

