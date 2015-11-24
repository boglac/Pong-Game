#pragma once
#include "ActorData.h"

typedef unsigned short ushort;

/*
    struct
    GameData
    Keeps information about objects (Actors) participation in the game.
*/
struct GameData
{
    const ushort dataCount;
    const ActorData *data;

    GameData(const ActorData *enData, ushort count)
        : dataCount(count), data(enData) {}
};