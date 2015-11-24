#pragma once
#include <SDL.h>
#include "Actor.h"
#include "Enemy.h"
#include "Player.h"
#include "Ball.h"
#include "Text.h"
#include "View.h"
#include "BorderData.h"

/*
    class
    Scene
    Represents bottom layer of the game - collects objects, administrates their behaviour,
    keeps track of their positions / states / etc., controls game events.
*/
class Scene
{
public:
    Scene(const BorderData &brdrs)
    {
        addBorders(brdrs);
        children = nullptr;
        
        enemy = nullptr;
        player = nullptr;
        ball = nullptr;
    }

    ~Scene()
    {
        // TODO go through all children and delete them
        delete children;
    }

    void addBorders(const BorderData &borders);
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
        Actor *elem;
        Item *next;
        Item() { elem = nullptr; next = nullptr; }
    };

    struct BorderItem {
        SDL_Rect *elem;
        BorderItem *next;
        BorderItem() { elem = nullptr; next = nullptr; }
    };

    // every child (Actor) added to the scene is appended to this list
    Item *children;

    // handy pointers
    Player *player;
    Enemy *enemy;
    Ball *ball;
        
    // 'flags' are set by the scene, when an event, about which Game object
    // should be notified, occurs. Game object then decides what to do.
    unsigned short flags;
    
    // every border added to the scene is appended to this list
    BorderItem *borders;
    SDL_Rect *topBorder;
    SDL_Rect *bottomBorder;
    SDL_Rect *leftBorder;
    SDL_Rect *rightBorder;

    // random device pointer, delivered by parent Game object
    std::random_device *rand;
};

enum eventType {
    EVENT_WIN = 1,
    EVENT_LOSE = 2,
    EVENT_BALLCOLL = 4
};