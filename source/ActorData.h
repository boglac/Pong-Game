#pragma once
#include "ImageData.h"

typedef unsigned short ushort;

/*
    enum
    actorType
    Collects possible actor types.
*/
enum actorType {
    TYPE_PLAYER = 1,
    TYPE_ENEMY = 2,
    TYPE_BALL = 4,
    TYPE_PICTURE = 8,
    TYPE_TEXT = 16
};

/*
    enum
    actorPurpose
    Collects possible purposes for actors (used by Picture and Text class).
*/
enum actorPurpose {
    PURPOSE_STATIC = 0,
    PURPOSE_SCORE = 1,
    PURPOSE_YOUSCORE = 2,
    PURPOSE_YOULOSE = 3,
    PURPOSE_BOOST = 4
};

/*
    struct
    ActorData
    Stores data about single Actor (Ball, Player or Enemy type).
*/
struct ActorData
{
    const actorType type;
    const ImageData image;
    const ushort visible;    
    const float x;
    const float y;
    const short extra;
    
    // value of 'extra' is interpreted differently for various objects:
    // TYPE_ENEMY - speed
    // TYPE_BALL - speed
    // TYPE_PLAYER - number of lives (not used currently)
    // TYPE_PICTURE - purpose (ex. Picture with score.png image should be displayed, when player scores)
    // TYPE_TEXT - purpose (static text, score, etc)
    ActorData(actorType actype, ImageData acimg, float acposX, float acposY, ushort acvisible, short acextra = 0)
        : type(actype), image(acimg), x(acposX), y(acposY), visible(acvisible), extra(acextra) {}

};



