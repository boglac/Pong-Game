#pragma once
#include <SDL.h>
#include "Actor.h"
#include "Border.h"
#include "Enemy.h"
#include "Player.h"
#include "Ball.h"
#include "Text.h"
#include "View.h"

/*
    class
    Scene
    Represents bottom layer of the game - collects objects, administrates their behaviour,
    keeps track of their positions / states / etc., controls game events.
*/
class Scene
{
public:
    Scene()
    {
        Children = nullptr;
        
        EnemyHandler = nullptr;
        PlayerHandler = nullptr;
        BallHandler = nullptr;
    }

    ~Scene()
    {
        // TODO go through all children and delete them
        delete Children;
    }

    void addBorders(const Border &borders);
    void addChild(Actor *child);

    void addRandomDevice(std::random_device *rnd);
    
    void playerCoords(float &x, float &y);
    void setPlayerPos(int x);
    void boostBall(float boost);

    void update();
           
    void tellEnemies() const;
    void resetChildren();
    void resetFlags();

    unsigned short getFlags();

private:
    struct Item {
        Actor *Elem;
        Item *Next;
        Item() { Elem = nullptr; Next = nullptr; }
    };

    // every child (Actor) added to the scene is appended to this list
    Item *Children;

    // handy pointers
    Player *PlayerHandler;
    Enemy *EnemyHandler;
    Ball *BallHandler;
        
    // 'flags' are set by the scene, when an event, about which Game object
    // should be notified, occurs. Game object then decides what to do.
    unsigned short Flags;

    int LeftBorderX;
    int RightBorderX;

    // random device pointer, delivered by parent Game object
    std::random_device *Rand;
};

enum eventType {
    EVENT_WIN = 1,
    EVENT_LOSE = 2,
    EVENT_BALLCOLL = 4
};