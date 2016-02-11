#pragma once
#include <string>
#include <random>

#include "Player.h"
#include "Enemy.h"
#include "Ball.h"
#include "Border.h"
#include "Picture.h"
#include "Text.h"
#include "Scene.h"
#include "View.h"
#include "GameData.h"

/*
    class
    Game
    Represents the game. Initializes the game, gives tasks to other objects (scene, view).
*/
class Game
{
public:
    enum gameState {
        STATE_INIT,
        STATE_GAME,
        STATE_WIN,
        SATE_LOOSE,
        STATE_EXIT,
        STATE_NEXTROUND
    };

    gameState State;

    Game()
    {
        State = STATE_INIT;

        Score = nullptr;

        SceneHandler = nullptr;
        ViewHandler = nullptr;

        LosePicture = nullptr;
        ScorePicture = nullptr;

        ActorID = 1;

        // set defaults for game behaviour parameters
        GameParameters.BallAcceleration = 10.0f;
        GameParameters.BallBoost = 2.5f;
        GameParameters.GainThreshold = 50;
        GameParameters.PointsForScore = 10;
        GameParameters.RoundDelay = 500;
    }

    void attachRandomizer(std::random_device *rnd);
    void attachScene(Scene *scene);
    void attachView(View *view);

    Actor * createObject(ActorData data, ushort &created);
    short init(const GameData &data, ushort typesMinimum);

    // If this function is not called, default parameters for game behaviour will be used.
    void setGameParameters(int scorePoints, int gainThreshold = 0, float ballAccell = 0, float ballBoost = 0, unsigned int delay = 0);

    void update();
    void incPoints();
    void decPoints();
    void nextRound();

    void onMouseMove(int x);
    void onLeftClick();

private:
    Scene *SceneHandler;
    View *ViewHandler;

    std::random_device *Randomizer;

    Text *Score;

    // references to GUI images
    Picture *ScorePicture;
    Picture *LosePicture;
    Picture *BoostPicture;

    ushort DemandedTypes;

    // Game object distributes IDs between Actors
    ushort ActorID;

    // Stats class is used to store current game statistics (like score)
    struct Stats
    {
        int Score;
        int ScoreGain;
    };

    /** Object of type Parameters is used to store values for parameters
    defining game behaviour (like amount of points for score or acceleration the
    ball receives after collision) */
    struct Parameters
    {
        float BallAcceleration;
        float BallBoost;

        int GainThreshold;
        int PointsForScore;

        unsigned int RoundDelay;
    };

    Stats PlayerStats;
    Parameters GameParameters;
    
};

