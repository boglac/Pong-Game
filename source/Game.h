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
    }

    void attachRandomizer(std::random_device *rnd);
    void attachScene(Scene *scene);
    void attachView(View *view);

    Actor * createObject(ActorData data, ushort &created);
    short init(const GameData &data, ushort typesMinimum);

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

    Picture *ScorePicture;
    Picture *LosePicture;
    Picture *BoostPicture;

    ushort DemandedTypes;
    ushort ActorID;

    struct Stats
    {
        int Score;
        int ScoreGain;

        Stats() { Score = 0; ScoreGain = 0; }
    };

    Stats PlayerStats;
    
};

