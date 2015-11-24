#pragma once
#include <SDL.h>
#include "ImageData.h"
#include "ActorData.h"
#include "GameData.h"
#include "GameParams.h"
#include "BorderData.h"

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

    // some game behaviour parameters
    const int GAME_BOOST_THRESHOLD = 50;
    const float GAME_BOOST_VALUE = 2.5f;
    const int GAME_POINTS_FOR_GOAL = 10;

    // Borders defining game area. 
    // It's obligatory that rectangle elements in the array define borders in such order:
    //   1st element -  top border
    //   2nd element -  bottom border
    //   3rd elememnt - left border
    //   4th element -  right border.
    const mySDL_Rect rectangles[] = {
        mySDL_Rect(0, 0, SCR_WIDTH, 1),
        mySDL_Rect(0, SCR_HEIGHT - 1, SCR_WIDTH, 1),
        mySDL_Rect(0, 0, 1, SCR_HEIGHT),
        mySDL_Rect(SCR_WIDTH - 1, 0, 1, SCR_HEIGHT)
    };

    const BorderData borders(rectangles, 4);

    // In order to change some of the game's parameters, alter this array. New actors can be added, or current modified 
    // (image, position, speed). If a new actor is added, remember to increase the value of the second argument for GameData object creation.
    // Game class object  goes through this array on game initialization process - if there is not 
    // at least on of the types PLAYER, ENEMY and BALL present, returns an error. Also, only one PLAYER actor is allowed.
    const ActorData actors[] = {
        ActorData(TYPE_PICTURE, ImageData("images/field.jpg", SCR_WIDTH, SCR_HEIGHT), SCR_WIDTH / 2 , SCR_HEIGHT / 2, 1),
        ActorData(TYPE_PICTURE, ImageData("images/logo.png", 120, 40), SCR_WIDTH - 75, SCR_HEIGHT - 30, 1),
        
        ActorData(TYPE_PICTURE, ImageData("images/score.png", 230, 40), SCR_WIDTH / 2, SCR_HEIGHT / 2 - 6, 0, PURPOSE_YOUSCORE),
        ActorData(TYPE_PICTURE, ImageData("images/lost.png", 230, 40), SCR_WIDTH / 2, SCR_HEIGHT / 2 - 6, 0, PURPOSE_YOULOSE),
        ActorData(TYPE_PICTURE, ImageData("images/boost.png", 110, 32), 75, SCR_HEIGHT - 40, 0, PURPOSE_BOOST),

        // Text object are type of images (are rendered to textures as well).
        // When creating data for text object, first argument in ImageData constructor determines what text will be displayed.
        // Second and third arguments determine text boundaries - it won't stretch more, than it's limited too by these parameters.
        ActorData(TYPE_TEXT, ImageData("POINTS", 125, 50), SCR_WIDTH - 85, 35, 1, PURPOSE_STATIC),
        ActorData(TYPE_TEXT, ImageData("0", 80, 50), SCR_WIDTH - 180, 35, 1, PURPOSE_SCORE),

        ActorData(TYPE_PLAYER, ImageData("images/player.png", 180, 31), SCR_WIDTH / 2, SCR_HEIGHT - 115, 1, 3),
        ActorData(TYPE_ENEMY, ImageData("images/enemy.png", 180, 31), SCR_WIDTH / 2 , 115, 1, 8),
        ActorData(TYPE_BALL, ImageData("images/ball2.png", 55, 55), SCR_WIDTH / 2 , SCR_HEIGHT / 2 , 1, 11.5)
    };   

    const GameData data(actors, 10);
    const GameParams params(GAME_POINTS_FOR_GOAL, GAME_BOOST_THRESHOLD, GAME_BOOST_VALUE);

    
}