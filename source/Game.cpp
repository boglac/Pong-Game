#include "Game.h"
void Game::attachScene(Scene *s)
{
    scene = s;
    scene->addRandomDevice(randomizer);
}

void Game::attachView(View *v)
{
    view = v;
}

void Game::attachRandomizer(std::random_device *rnd)
{
    randomizer = rnd;
}


short Game::init(const GameData &gadata)
{
    if (!scene || !view) return 1;

    unsigned short createdTypes = 0, demandedTypes = TYPE_PLAYER | TYPE_BALL | TYPE_ENEMY;
    
    const ActorData *data = gadata.data;
    Actor *temp = nullptr;
        
    for (short i = 0; i < gadata.dataCount; ++i)
    {
        if (data[i].type == TYPE_PLAYER) {
            temp = new Player(data[i]);
            temp->attachImage(view->loadTexture(data[i].image.path));

            createdTypes |= data[i].type;
        }
        else if (data[i].type == TYPE_BALL) {
            temp = new Ball(data[i]);
            temp->attachImage(view->loadTexture(data[i].image.path));

            createdTypes |= data[i].type;
        }
        else if (data[i].type == TYPE_ENEMY) {
            temp = new Enemy(data[i]);
            temp->attachImage(view->loadTexture(data[i].image.path));

            createdTypes |= data[i].type;
        }
        else if (data[i].type == TYPE_PICTURE) {
            temp = new Picture(data[i]);
            temp->attachImage(view->loadTexture(data[i].image.path));

            Picture *tempPicture = static_cast<Picture*>(temp);

            // store some pictures references
            if (data[i].extra == PURPOSE_YOULOSE) losePicture = tempPicture;
            else if (data[i].extra == PURPOSE_YOUSCORE) scorePicture = tempPicture;
            else if (data[i].extra == PURPOSE_BOOST) boostPicture = tempPicture;
        }
        else if (data[i].type == TYPE_TEXT) {
            temp = new Text(data[i]);
            temp->attachImage(view->loadText(data[i].image.path));

            Text *tempText = static_cast<Text*>(temp);            
            view->setTextSize(tempText);

            // store score text reference
            if (data[i].extra == PURPOSE_SCORE) score = tempText;
        }

        // [ add other types creation here ]

        if (temp) scene->addChild(temp);
    }

    // check if all neccesary entity types has been created (PLAYER, BALL and ENEMY)
    if (createdTypes != demandedTypes) return 2;

    state = STATE_GAME;
    return 0;
}

void Game::setParams(GameParams p)
{
    params = p;
}

void Game::update()
{
    if (state != STATE_GAME) return;
    
    scene->update();

    // check scene flags
    unsigned short flags = scene->getFlags();

    if (flags & EVENT_WIN) incPoints();
    if (flags & EVENT_LOSE) decPoints();

    if (flags & EVENT_BALLCOLL) scene->tellEnemies();
    
    scene->resetFlags();

    // update view
    view->update();
}

void Game::onMouseMove(int x)
{
    scene->setPlayerPos(x);
}

void Game::onLeftClick()
{
    if (playerStats.scoreGain >= params.boostThreshold) {
        scene->boostBall(params.boostValue);
        playerStats.scoreGain = 0;

        boostPicture->setVisibility(false);
    }
}

void Game::incPoints()
{
    playerStats.score += params.goalPoints;
    playerStats.scoreGain += params.goalPoints;

    if (playerStats.scoreGain >= params.boostThreshold) boostPicture->setVisibility(true);

    scorePicture->setVisibility(1);
    view->updateText(score, std::to_string(playerStats.score).std::string::c_str());

    view->update();
    nextRound();
}

void Game::decPoints()
{
    playerStats.score -= params.goalPoints;
    playerStats.scoreGain -= params.goalPoints;

    if (playerStats.scoreGain < params.boostThreshold) boostPicture->setVisibility(false);

    losePicture->setVisibility(1);
    view->updateText(score, std::to_string(playerStats.score).std::string::c_str());

    view->update();
    nextRound();
}

void Game::nextRound()
{
    state = STATE_NEXTROUND;
    scene->resetChildren();
    SDL_Delay(500);
    losePicture->setVisibility(0);
    scorePicture->setVisibility(0);
    state = STATE_GAME;
}