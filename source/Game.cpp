#include "Game.h"
void Game::attachScene(Scene *s)
{
    SceneHandler = s;
    SceneHandler->addRandomDevice(Randomizer);
}

void Game::attachView(View *v)
{
    ViewHandler = v;
}

void Game::attachRandomizer(std::random_device *rnd)
{
    Randomizer = rnd;
}

Actor * Game::createObject(ActorData data, ushort &created)
{
    Actor *temp = nullptr;

    switch (data.type)
    {
        case TYPE_PLAYER:
        {
            temp = new Player(data);
            temp->attachImage(ViewHandler->loadTexture(data.image.path));

            created |= TYPE_PLAYER;
        }
        break;

        case TYPE_BALL:
        {
            temp = new Ball(data);
            temp->attachImage(ViewHandler->loadTexture(data.image.path));
            
            static_cast<Ball*>(temp)->setAcceleration(GameParameters.BallAcceleration);            

            created |= TYPE_BALL;
        }
        break;

        case TYPE_ENEMY:
        {
            temp = new Enemy(data);
            temp->attachImage(ViewHandler->loadTexture(data.image.path));

            created |= TYPE_ENEMY;
        }
        break;

        case TYPE_BORDER:
        {
            temp = new Border(data);
            temp->attachImage(nullptr);
        }
        break;

        case TYPE_PICTURE:
        {
            temp = new Picture(data);
            temp->attachImage(ViewHandler->loadTexture(data.image.path));

            Picture *tempPicture = static_cast<Picture*>(temp);

            // store some pictures references
            if (data.extra == PURPOSE_YOULOSE) LosePicture = tempPicture;
            else if (data.extra == PURPOSE_YOUSCORE) ScorePicture = tempPicture;
            else if (data.extra == PURPOSE_BOOST) BoostPicture = tempPicture;
        }
        break;

        case TYPE_TEXT:
        {
            temp = new Text(data);
            temp->attachImage(ViewHandler->loadText(data.image.path));

            Text *tempText = static_cast<Text*>(temp);
            ViewHandler->setTextSize(tempText);

            // store score text reference
            if (data.extra == PURPOSE_SCORE) Score = tempText;
        }
        break;

    }

    temp->setID(ActorID++);

    return temp;
}

short Game::init(const GameData &gadata, ushort typesMinimum)
{
    if (!SceneHandler || !ViewHandler) return 1;

    DemandedTypes = typesMinimum;
    unsigned short createdTypes = 0;
    
    const ActorData *data = gadata.actorsData;
    Actor *temp = nullptr;
        
    for (short i = 0; i < gadata.actorsCount; ++i)
    {
        temp = createObject(data[i], createdTypes);
        if (temp) SceneHandler->addChild(temp);
    }

    // check if all neccesary entity types has been created (PLAYER, BALL and ENEMY)
    if (createdTypes < DemandedTypes) return 2;

    State = STATE_GAME;
    return 0;
}

void Game::setGameParameters(int scorePoints, int gainThreshold, float ballAccell, float ballBoost, unsigned int delay)
{
    GameParameters.PointsForScore = scorePoints;
    GameParameters.GainThreshold = gainThreshold;
    GameParameters.BallAcceleration = ballAccell;
    GameParameters.BallBoost = ballBoost;
    GameParameters.RoundDelay = delay;
}

void Game::update()
{
    if (State != STATE_GAME) return;
    
    SceneHandler->update();

    // check scene flags
    unsigned short flags = SceneHandler->getFlags();

    if (flags & EVENT_WIN) incPoints();
    if (flags & EVENT_LOSE) decPoints();

    if (flags & EVENT_BALLCOLL) SceneHandler->tellEnemies();
    
    SceneHandler->resetFlags();

    // update view
    ViewHandler->update();
}

void Game::onMouseMove(int x)
{
    SceneHandler->setPlayerPos(x);
}

void Game::onLeftClick()
{
    if (PlayerStats.ScoreGain >= GameParameters.GainThreshold) {
        SceneHandler->boostBall(GameParameters.BallBoost);
        PlayerStats.ScoreGain = 0;

        BoostPicture->setVisibility(false);
    }

}

void Game::incPoints()
{
    PlayerStats.Score += GameParameters.PointsForScore;
    PlayerStats.ScoreGain += GameParameters.PointsForScore;

    if (PlayerStats.ScoreGain >= GameParameters.GainThreshold) BoostPicture->setVisibility(true);

    ScorePicture->setVisibility(1);
    ViewHandler->updateText(Score, std::to_string(PlayerStats.Score).std::string::c_str());

    ViewHandler->update();
    nextRound();
}

void Game::decPoints()
{
    PlayerStats.Score -= GameParameters.PointsForScore;
    PlayerStats.ScoreGain -= GameParameters.PointsForScore;

    if (PlayerStats.ScoreGain < GameParameters.GainThreshold) BoostPicture->setVisibility(false);

    LosePicture->setVisibility(1);
    ViewHandler->updateText(Score, std::to_string(PlayerStats.Score).std::string::c_str());

    ViewHandler->update();
    nextRound();
}

void Game::nextRound()
{
    State = STATE_NEXTROUND;
    SceneHandler->resetChildren();
    SDL_Delay(GameParameters.RoundDelay);
    LosePicture->setVisibility(0);
    ScorePicture->setVisibility(0);
    State = STATE_GAME;
    
}