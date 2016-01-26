#include "Scene.h"

//#define DEBUG_MODE
#ifdef DEBUG_MODE
#include <iostream>
#endif

void Scene::addBorders(const Border &brdrs)
{
    /*
    // it is possible to don't have any borders
    if (!brdrs.bordersCount) return;
    
    // there is data for one border at least - create it
    Borders = new BorderItem;

    Borders->Elem = new Border;
    Borders->Elem->x = brdrs.borders[0].x;
    Borders->Elem->y = brdrs.borders[0].y;
    Borders->Elem->w = brdrs.borders[0].w;
    Borders->Elem->h = brdrs.borders[0].h;
        
    Borders->Elem->topBorder = true;

    BorderItem *temp = Borders;
    Border *tempRect;

    for (int i = 1; i < brdrs.bordersCount; ++i)
    {
        temp->Next = new BorderItem;
        temp->Next->Elem = new Border;

        tempRect = temp->Next->Elem;
        tempRect->x = brdrs.borders[i].x;
        tempRect->y = brdrs.borders[i].y;
        tempRect->w = brdrs.borders[i].w;
        tempRect->h = brdrs.borders[i].h;

        // set outer borders
        if (i == 1) tempRect->bottomBorder = true;
        else if (i == 2) {
            tempRect->leftBorder = true;
            LeftBorderX = tempRect->x;
        }
        else if (i == 3) {
            tempRect->rightBorder = true;
            RightBorderX = tempRect->x;
        }

        temp = temp->Next;
    }
    */
}

void Scene::addChild(Actor *child)
{
    eActorType type;
    if (!Children) {
        Children = new Item;
        Children->Elem = child;
    } 
    else {
        Item *temp = Children, *last = nullptr;
        while (temp)
        {
            last = temp;
            temp = temp->Next;
        }

        last->Next = new Item;
        last->Next->Elem = child;

    }

    child->addRandomDevice(Rand);

    type = child->getType();
    switch (type) {

        case TYPE_PLAYER:
            // keep player at hand
            PlayerHandler = static_cast<Player*>(child);
        break;

        case TYPE_BALL:
            // keep ball at hand
            BallHandler = static_cast<Ball*>(child);
        break;
        
        case TYPE_ENEMY:
            // keep enemy at hand (the first added enemy will be the main one - the one with AI)
            EnemyHandler = static_cast<Enemy*>(child);
        break;
        
        case TYPE_BORDER:
        {
            Border *tempBorder = static_cast<Border*>(child);
            if (tempBorder->getPosition() == BORDER_LEFT) LeftBorderX = tempBorder->getX();
            else if (tempBorder->getPosition() == BORDER_RIGHT) RightBorderX = tempBorder->getX();
        }
        break;

    }

}

void Scene::addRandomDevice(std::random_device *rnd)
{
    Rand = rnd;
}

void Scene::setPlayerPos(int x)
{
    // prevent from moving beyond borders
    if (x < LeftBorderX + (PlayerHandler->getWidth() >> 1)) 
        x = LeftBorderX + (PlayerHandler->getWidth() >> 1);
    else if (x > RightBorderX - (PlayerHandler->getWidth() >> 1))
        x = RightBorderX - (PlayerHandler->getWidth() >> 1);

    PlayerHandler->setPos(float(x));
}

void Scene::boostBall(float boost)
{
    BallHandler->setBoost(boost);
}

void Scene::update()
{
    // nothing to do, if there are no children
    if (!Children) return;

    Item *child = Children, *otherChild;
    eActorType childType, otherType;    
    SDL_Rect *childRect, *tempRect;

    // go through all scene's children
    while (child)
    {
        otherChild = Children;

        // update every child
        child->Elem->update();

        // store type of a current child
        childType = child->Elem->getType();

        // select types for which collisions are not checked (in fact - static actors)
        if (childType == TYPE_PICTURE || childType == TYPE_TEXT || childType == TYPE_BORDER) {
            child = child->Next;
            continue;
        }

        // store current child rectangle reference
        childRect = child->Elem->getImageRect();

        // go through all the other children and check collision with current
        while (otherChild)
        {           
            otherType = otherChild->Elem->getType();

            // prevent collision with self and don't check collision with not colliding types
            if (child == otherChild || otherType == TYPE_PICTURE || otherType == TYPE_TEXT) {
                otherChild = otherChild->Next;
                continue;
            }
            
            tempRect = otherChild->Elem->getImageRect();
                        
            if (SDL_HasIntersection(childRect, tempRect)) {
            
                eCollisionResult result = RESULT_NORMAL;

                // react to collision with a border
                if (otherType == TYPE_BORDER) 
                {
                    Border *tempBorder = static_cast<Border*>(otherChild->Elem);
                    result = child->Elem->handleBorderCollision(tempBorder->getPosition(), tempBorder->getID());
                }
                else if (otherType == TYPE_BALL) 
                {
                    result = child->Elem->handleBallCollision(otherChild->Elem);
                }
                else if (otherType == TYPE_ENEMY)
                {
                    result = child->Elem->handleEnemyCollision();
                }

                if (result == RESULT_SCORE) Flags |= EVENT_WIN;
                else if (result == RESULT_LOSE) Flags |= EVENT_LOSE;
                else if (result == RESULT_BALLCOLL) Flags |= EVENT_BALLCOLL;

            }

            otherChild = otherChild->Next;

        }

        child = child->Next;

    }

}

void Scene::tellEnemies() const
{
    EnemyHandler->setDirection(BallHandler->getXSpeed());
}

void Scene::playerCoords(float &x, float &y)
{
    PlayerHandler->getPos(x, y);
}

unsigned short Scene::getFlags()
{
    return Flags;
}

void Scene::resetFlags()
{
    Flags = 0;
}

void Scene::resetChildren()
{
    if (!Children) return;

    Item *tempChild = Children;

    while (tempChild)
    {           
        tempChild->Elem->reset();
        tempChild = tempChild->Next;
    }
}

