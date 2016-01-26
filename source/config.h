#pragma once
#include <SDL.h>
#include "ImageData.h"
#include "ActorData.h"
#include "GameData.h"
#include "Border.h"

// Objects defined in 'config' namespace are used only in global context, as an arguments to functions' calls.
// Non of these objects should be related to in classes or structures, they only give application a starting point.
namespace config {   

    // screen width and height
    const int SCR_WIDTH = 640;
    const int SCR_HEIGHT = 960;

    // font parameters
    const int TEXT_SIZE = 30;
    const SDL_Color TEXT_COLOR = {255, 190, 100};
    const char *TEXT_FONT = "sansbi.ttf";

    // define what actors are necessary for our game
    const unsigned short DEMANDED_ACTORS = TYPE_BALL | TYPE_ENEMY | TYPE_PLAYER;

    // define which actors will be checked for collision
    const unsigned short COLLISION_MODE = TYPE_PLAYER | TYPE_BALL | TYPE_ENEMY;
    
    // In order to change some of the game's parameters, alter this array. New actors can be added, or current modified 
    // (image, position, speed). If a new actor is added, remember to increase the value of the second argument for GameData object creation.
    // Game class object  goes through this array on game initialization process - if there is not 
    // at least on of the types PLAYER, ENEMY and BALL present, returns an error. Also, only one PLAYER actor is allowed.
    const ActorData actors[] = {
        ActorData(TYPE_BORDER, ImageData(SCR_WIDTH, 1), SCR_WIDTH / 2, 0, 0, BORDER_TOP),
        ActorData(TYPE_BORDER, ImageData(SCR_WIDTH, 1), SCR_WIDTH / 2, SCR_HEIGHT - 1, 0, BORDER_BOTTOM),
        ActorData(TYPE_BORDER, ImageData(1, SCR_HEIGHT), 0, SCR_HEIGHT / 2, 0, BORDER_LEFT),
        ActorData(TYPE_BORDER, ImageData(1, SCR_HEIGHT), SCR_WIDTH, SCR_HEIGHT / 2, 0, BORDER_RIGHT),
        
        ActorData(TYPE_PICTURE, ImageData("images/field.jpg", SCR_WIDTH, SCR_HEIGHT), SCR_WIDTH / 2, SCR_HEIGHT / 2, 1),        
        ActorData(TYPE_PICTURE, ImageData("images/score.png", 210, 33), SCR_WIDTH / 2, SCR_HEIGHT / 2 - 16, 0, PURPOSE_YOUSCORE),
        ActorData(TYPE_PICTURE, ImageData("images/lost.png", 180, 33), SCR_WIDTH / 2, SCR_HEIGHT / 2 - 16, 0, PURPOSE_YOULOSE),
        ActorData(TYPE_PICTURE, ImageData("images/boost.png", 110, 32), 75, SCR_HEIGHT - 40, 0, PURPOSE_BOOST),

        // Text object are type of images (are rendered to textures as well).
        // When creating data for text object, first argument in ImageData constructor determines what text will be displayed.
        ActorData(TYPE_TEXT, ImageData("POINTS", 150, 20), SCR_WIDTH - 90, 35, 1, PURPOSE_STATIC),
        ActorData(TYPE_TEXT, ImageData("0", 20, 20), SCR_WIDTH - 180, 35, 1, PURPOSE_SCORE),

        ActorData(TYPE_PLAYER, ImageData("images/player.png", 190, 36), SCR_WIDTH / 2, SCR_HEIGHT - 145, 1, 3),
        ActorData(TYPE_ENEMY, ImageData("images/enemy.png", 190, 34), SCR_WIDTH / 2 , 145, 1, 8),
        ActorData(TYPE_BALL, ImageData("images/ball2.png", 55, 55), SCR_WIDTH / 2 , SCR_HEIGHT / 2 , 1, 10)
    };

    const GameData data(actors, 13);
}