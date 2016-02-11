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
        Speed[0] = StartSpeed[0] = float(params.extra);
        Speed[1] = StartSpeed[1] = float(params.extra);

        Acceleration = 10.0f;

        Boost = 0;
        BoostApproved = false;
        ApproveTime = 0;

        PrevColVert = 0;
        PrevColHor = 0;
        PrevBorCol = 0;

        Rand = nullptr;
    }    

    // prevColHor and prevColVert are used to store the last Actor object's ID the ball 
    // has collided with, to prevent colliding with the same object over and over again.
    ushort PrevColHor;
    ushort PrevColVert;

    // the same, as above, for border
    ushort PrevBorCol;

    // movement modifiers, fired on collisions
    void reverseXVelocity();
    void reverseYVelocity();
    void alterXVelocity(float x);
    void moveRight();
    void moveLeft();

    void setAcceleration(float accel);
    void setBoost(float boost);
    void approveBoost(bool boost);

    float getXSpeed() const;
    float getAcceleration() const;

    eCollisionResult handleBorderCollision(eBorderPosition borderPos, ushort borderID);

    void reset();
    void update();

    void addRandomDevice(std::random_device *rnd);

private:

    // current ball speed
    float Speed[2];

    // startSpeed holds values given at config time
    float StartSpeed[2];

    // determines acceleration the ball gains after a collision
    float Acceleration;

    // speed boost, decreasing with time, triggered by Game through Scene
    float Boost;

    // boost is approved, if ball collides with player at the moment of left click
    bool BoostApproved;
    Uint32 ApproveTime;

    // random device is used on Ball reset, to generate random movement
    // delivered by parent Scene object
    std::random_device *Rand;
};

