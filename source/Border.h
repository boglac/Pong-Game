#pragma once
#include "Actor.h"

class Border : public Actor
{
public:
    Border(const ActorData &params) : Actor(params)
    {        
        Position = static_cast<eBorderPosition>(params.extra);
    }

    ~Border() {};

    eBorderPosition getPosition() { return Position; }

    void update() {};

private:
    eBorderPosition Position;
};

