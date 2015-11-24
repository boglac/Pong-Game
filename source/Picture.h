#pragma once
#include "Actor.h"

/*
    class
    Picture
    inherits Actor
    Represents visual object in the game, that has no other meaning, than to look fancy.
*/
class Picture : public Actor
{
public:
    Picture(const ActorData &params) : Actor(params) 
    {
        purpose = params.extra;
    }
    
    void update() {};
private:

    short purpose;
};

