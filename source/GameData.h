#pragma once
#include "ActorData.h"

/*
    struct
    GameData
    Keeps information about objects (Actors) participation in the game.
*/
struct GameData
{
    const ushort actorsCount;
    const ActorData *actorsData;
    
    GameData(const ActorData *enData, ushort numOfActors)
        : actorsCount(numOfActors), actorsData(enData) {}
};