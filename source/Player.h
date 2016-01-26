#pragma once
#include "Actor.h"
#include "Ball.h"

class Player : public Actor
{
public:
    Player(const ActorData &params) : Actor(params) 
    {
        Lives = params.extra;
    }

    void reset() {};
    void update();
    
    void setPos(float posX);
    void getPos(float &x, float &y) const;
    
    eCollisionResult handleBallCollision(Actor *ball);

private:
    unsigned short Lives;
};

