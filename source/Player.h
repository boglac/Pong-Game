#pragma once
#include "Actor.h"

class Player : public Actor
{
public:
    Player(const ActorData &params) : Actor(params) 
    {
        lives = params.extra;
    }

    void reset() {};
    void update();
    void setPos(float posX);
    void getPos(float &x, float &y) const;
    
private:
    unsigned short lives;
};

