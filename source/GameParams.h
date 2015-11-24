#pragma once

typedef unsigned short ushort;

/*
    struct
    GameParams
    Use and/or extend this structure to set additional game parameters.
*/
struct GameParams {
    ushort goalPoints;
    ushort boostThreshold;
    float boostValue;

    GameParams() 
    {
        goalPoints = 0;
        boostThreshold = 0;
        boostValue = 0.0f;
    };

    GameParams(ushort score, ushort thrsh, float boost)
        : goalPoints(score), boostThreshold(thrsh), boostValue(boost) {};
};