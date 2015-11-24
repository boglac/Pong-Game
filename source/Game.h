#pragma once
#include <string>
#include <random>

#include "Player.h"
#include "Enemy.h"
#include "Ball.h"
#include "Picture.h"
#include "Text.h"
#include "Scene.h"
#include "View.h"
#include "GameData.h"
#include "GameParams.h"

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

    gameState state;

    Game()
    {
        state = STATE_INIT;

        score = nullptr;

        scene = nullptr;
        view = nullptr;

        losePicture = nullptr;
        scorePicture = nullptr;

        // set default values for some parameters
        params.boostThreshold = 10;
        params.boostValue = 1.0f;
        params.goalPoints = 1;        
    }

    void attachRandomizer(std::random_device *rnd);
    void attachScene(Scene *scene);
    void attachView(View *view);

    short init(const GameData &data);
    void setParams(GameParams params);

    void update();
    void incPoints();
    void decPoints();
    void nextRound();

    void onMouseMove(int x);
    void onLeftClick();

private:
    Scene *scene;
    View *view;

    std::random_device *randomizer;

    Text *score;

    Picture *scorePicture;
    Picture *losePicture;
    Picture *boostPicture;

    struct Stats
    {
        int score;
        int scoreGain;

        Stats() { score = 0; scoreGain = 0; }
    };

    Stats playerStats;
    GameParams params;
    
};

