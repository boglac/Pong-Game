#pragma once
#include <random>
#include "Actor.h"

/*
    class
    Ball
    inherits Actor
*/
class Ball : public Actor
{
public:
    Ball(const ActorData &params) : Actor(params)
    {
        speed[0] = startSpeed[0] = float(params.extra);
        speed[1] = startSpeed[1] = float(params.extra);

        boost = 0;
        boostApproved = false;
        approveTime = 0;

        prevColVert = nullptr;
        prevColHor = nullptr;
        prevBorCol = nullptr;

        rand = nullptr;
    }    

    // prevColHor and prevColVert pointers are used to store the last Actor object the ball 
    // has collided with, to prevent colliding with the same object over and over again.
    SDL_Rect *prevColHor;
    SDL_Rect *prevColVert;

    // the same, as above, for border
    SDL_Rect *prevBorCol;

    // movement modifiers, fired on collisions
    void reverseXVelocity();
    void reverseYVelocity();
    void alterXVelocity(float x);
    void moveRight();
    void moveLeft();

    void setBoost(float boost);
    void approveBoost(bool boost);

    float getXSpeed() const;

    void reset();
    void update();

    void addRandomDevice(std::random_device *rnd);

private:

    // current ball speed
    float speed[2];

    // startSpeed holds values given at config time
    float startSpeed[2];

    // speed boost, decreasing with time, triggered by Game through Scene
    float boost;

    // boost is approved, if ball collides with player at the moment of left click
    bool boostApproved;
    Uint32 approveTime;

    // random device is used on Ball reset, to generate random movement
    // delivered by parent Scene object
    std::random_device *rand;
};

