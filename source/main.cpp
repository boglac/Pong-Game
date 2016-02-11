#include <iostream>
#include <random>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#undef main

#include "source\config.h"
#include "source\Actor.h"
#include "source\Scene.h"
#include "source\View.h"
#include "source\Game.h"
#include "source\Player.h"

using namespace std;

int main()
{
    // SDL handlers
    SDL_Window *appWindow = nullptr;
    SDL_Surface *appScreen = nullptr;
    SDL_Event appEvent;

    // SDL initialization attempt - returns 0 on success or negative number on error
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
        cout << "-! SDL_Init error: " << SDL_GetError();
    else
    {
        // ---------- Initialize SDL components

        cout << "+ SDL initialized successfully" << endl;
        cout << "\t+ Platform: " << SDL_GetPlatform() << endl;

        if (!(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) & IMG_INIT_PNG)) {
            cout << "-! IMG_Init error: \n\t" << IMG_GetError();
            SDL_Quit();
            getchar();
            return 1; 
        }

        cout << "\t+ SDL_Image component ready" << endl;

        if (TTF_Init() != 0) {
            cout << "-! TTF_Init error: \n\t" << TTF_GetError();
            SDL_Quit();
            getchar();
            return 1;
        }

        cout << "\t+ SDL_ttf component ready" << endl;

        // Window creation attempt
        appWindow = SDL_CreateWindow("Pong2000", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, config::SCR_WIDTH, config::SCR_HEIGHT, SDL_WINDOW_SHOWN);
        if (appWindow == NULL) {
            cout << "-! SDL_CreateWindow error: " << SDL_GetError();
            SDL_Quit();
            getchar();
            return 1;
        }

        cout << "\t+ Window created" << endl;

        // Rednerer creation attempt
        SDL_Renderer *renderer = SDL_CreateRenderer(appWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (renderer == nullptr) {
            cout << "SDL_CreateRenderer Error: " << SDL_GetError() << endl;
            SDL_DestroyWindow(appWindow);
            SDL_Quit();
            getchar();
            return 1;
        }

        cout << "\t+ Renderer created" << endl << endl;

        // ---------- Initialize game system objects
        View view;

        TTF_Font *font;
        font = TTF_OpenFont(config::TEXT_FONT, config::TEXT_SIZE);
        if (!font) {
            cout << "-! Couldn't load font: " << TTF_GetError();
            SDL_Quit();
            getchar();
            return 1;
        }
                
        view.setFont(font, config::TEXT_COLOR, config::TEXT_SIZE);
        view.setRenderer(renderer);
                
        Scene scene;
        
        Game game;
        random_device rd;

        game.attachRandomizer(&rd);
        game.attachScene(&scene);
        game.attachView(&view);

        game.setGameParameters(config::SCORE_POINTS, config::GAIN_THRESHOLD, config::BALL_ACCELERATION, config::BALL_BOOST, config::ROUND_DELAY);
        short result = game.init(config::data, config::DEMANDED_ACTORS);
        
        if (result == 1) cout << endl << "-! Game system error: scene or view not attached" << endl;
        else if (result == 2) {
            cout << endl << "-! Game system error: some necessary actors missing:";
            cout << "\n\t- Check config for PLAYER, ENEMY or BALL" << endl;
        }
        else cout << endl << "+ Game initialized" << endl;

        // Get window surface
        appScreen = SDL_GetWindowSurface(appWindow);

        // hide mouse cursor
        SDL_ShowCursor(0);
                
        SDL_Surface* loadedSurface = IMG_Load("images/ball.png");

        bool play = true;
        bool setRel = true;

        float playerX, playerY;
        scene.playerCoords(playerX, playerY);
        SDL_WarpMouseInWindow(appWindow, (int)playerX, (int)playerY);        
        
        while (play)
        {
            while (SDL_PollEvent(&appEvent))
            {
                switch (appEvent.type) {
                    
                case SDL_QUIT:
                    play = false;
                    break;

                case SDL_MOUSEMOTION:
                    if (setRel) {
                        SDL_SetRelativeMouseMode(SDL_TRUE);
                        setRel = false;
                    }

                    game.onMouseMove(appEvent.motion.x);
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if (appEvent.button.button == SDL_BUTTON_LEFT)
                        game.onLeftClick();
                    break;

                case SDL_KEYDOWN:
                    if (appEvent.key.keysym.sym == SDLK_ESCAPE) {
                        play = false;
                    }
                    break;
                }
            }
            
            game.update();
         }        
    }

    // Close and destroy the window
    SDL_DestroyWindow(appWindow);

    // Clean up
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}