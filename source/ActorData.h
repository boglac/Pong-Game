#pragma once
#include "ImageData.h"

typedef unsigned short ushort;

/*
    enum
    eActorType
    Collects possible actor types.
*/
enum eActorType : ushort {
    TYPE_PLAYER = 1,
    TYPE_ENEMY = 2,
    TYPE_BALL = 4,
    TYPE_PICTURE = 8,
    TYPE_TEXT = 16,
    TYPE_BORDER = 24
};

/*
    enum
    eActorPurpose
    Collects possible purposes for actors (used by Picture and Text class).
*/
enum eActorPurpose : ushort {
    PURPOSE_STATIC = 0,
    PURPOSE_SCORE = 1,
    PURPOSE_YOUSCORE = 2,
    PURPOSE_YOULOSE = 3,
    PURPOSE_BOOST = 4
};

/*
    enum
    eBorderPosition
    Collects possible positions for borders.
*/
enum eBorderPosition : ushort {
    BORDER_TOP = 0,
    BORDER_BOTTOM = 1,
    BORDER_LEFT = 2,
    BORDER_RIGHT = 3
};

/*
    enum
    eCollisionResult
    Collects possible result of collisions (ex. if a ball collides with top border - it's a score)
    shared by actors.
*/
enum eCollisionResult : ushort {
    RESULT_SCORE = 0,
    RESULT_LOSE = 1,
    RESULT_BALLCOLL = 2,
    RESULT_NORMAL = 3
};

/*
    struct
    ActorData
    Stores data about single Actor (Ball, Player or Enemy type).
*/
struct ActorData
{
    const eActorType type;
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
    // TYPE_BORDER - border positioning (top border, bottom border, etc)
    ActorData(eActorType actype, ImageData acimg, float acposX, float acposY, ushort acvisible, short acextra = 0)
        : type(actype), image(acimg), x(acposX), y(acposY), visible(acvisible), extra(acextra) {}

};



