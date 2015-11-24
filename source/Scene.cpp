#include "Scene.h"

//#define DEBUG_MODE
#ifdef DEBUG_MODE
#include <iostream>
#endif
void Scene::addBorders(const BorderData &brdrs)
{
    // it is possible to don't have any borders
    if (!brdrs.bordersCount) return;
    
    // there is data for one border at least - create it
    borders = new BorderItem;

    borders->elem = new SDL_Rect;
    borders->elem->x = brdrs.borders[0].x;
    borders->elem->y = brdrs.borders[0].y;
    borders->elem->w = brdrs.borders[0].w;
    borders->elem->h = brdrs.borders[0].h;
        
    topBorder = borders->elem;

    BorderItem *temp = borders;
    SDL_Rect *tempRect;

    for (int i = 1; i < brdrs.bordersCount; ++i)
    {
        temp->next = new BorderItem;
        temp->next->elem = new SDL_Rect;

        tempRect = temp->next->elem;
        tempRect->x = brdrs.borders[i].x;
        tempRect->y = brdrs.borders[i].y;
        tempRect->w = brdrs.borders[i].w;
        tempRect->h = brdrs.borders[i].h;

        // set outer borders
        if (i == 1) bottomBorder = tempRect;
        else if (i == 2) leftBorder = tempRect;
        else if (i == 3) rightBorder = tempRect;

        temp = temp->next;
    }
}

void Scene::addChild(Actor *child)
{
    if (!children) {
        children = new Item;
        children->elem = child;
    } 
    else {
        Item *temp = children, *last = nullptr;
        while (temp)
        {
            last = temp;
            temp = temp->next;
        }

        last->next = new Item;
        last->next->elem = child;

    }

    // keep player at hand
    if (child->getType() == TYPE_PLAYER) player = static_cast<Player*>(child);

    // keep ball at hand
    if (child->getType() == TYPE_BALL) ball = static_cast<Ball*>(child);

    // keep enemy at hand
    if (child->getType() == TYPE_ENEMY) enemy = static_cast<Enemy*>(child);

    if (enemy) enemy->addRandomDevice(rand);
    if (ball) ball->addRandomDevice(rand);
}

void Scene::addRandomDevice(std::random_device *rnd)
{
    rand = rnd;
}

void Scene::setPlayerPos(int x)
{
    // prevent from moving beyond borders
    if (x < leftBorder->x + (player->getWidth() >> 1)) 
        x = leftBorder->x + (player->getWidth() >> 1);
    else if (x > rightBorder->x - (player->getWidth() >> 1)) 
        x = rightBorder->x - (player->getWidth() >> 1);

    player->setPos(float(x));
}

void Scene::boostBall(float boost)
{
    ball->setBoost(boost);
}

void Scene::update()
{
    // nothing to do, if there are no children
    if (!children) return;

    actorType type;
    Item *tempChild = children;
    SDL_Rect *rect;
    BorderItem *tempBorder;

    while (tempChild)
    {
        tempChild->elem->update();
        type = tempChild->elem->getType();

        if (!borders && type != TYPE_BALL || type == TYPE_PICTURE || type == TYPE_TEXT) {
            tempChild = tempChild->next;
            continue;
        }
        
        // store current tempChild rectandle reference
        rect = tempChild->elem->getImageRect();

        // check collisions with borders
        tempBorder = borders;
        while (tempBorder)
        {
            if (SDL_HasIntersection(tempBorder->elem, rect)) {

                if (type == TYPE_ENEMY) {
                    Enemy *tempEnemy = static_cast<Enemy*>(tempChild->elem);
                    tempEnemy->reverse();
                }
                else if (type == TYPE_BALL) {
                    Ball *tempBall = static_cast<Ball*>(tempChild->elem);

                    if (tempBorder->elem == topBorder) {
                        flags |= EVENT_WIN;
                        //tempBall->reverseYVelocity();
                    }
                    else if (tempBorder->elem == bottomBorder) {
                        flags |= EVENT_LOSE;
                        //tempBall->reverseYVelocity();
                    }
                    else if ((tempBorder->elem == leftBorder || tempBorder->elem == rightBorder)
                        && tempBall->prevBorCol != tempBorder->elem) {

                        tempBall->prevBorCol = tempBorder->elem;
                        tempBall->reverseXVelocity();

                        flags |= EVENT_BALLCOLL;
                    }

                    // Because current Ball object has collided with a border (and a border isn't an Actor
                    // object for sure), set prevColHor and prevColVert pointers to nullptr, so
                    // that collisions with other Actor objects is possible again.
                    tempBall->prevColHor = nullptr;
                    tempBall->prevColVert = nullptr;
                }

                // [ add other types collision with borders handling here ]
            }

            tempBorder = tempBorder->next;
        }
        
        // only ball can collide with other objects as well
        if (type == TYPE_BALL) {
            
            SDL_Rect *otherRect = nullptr;
            actorType typeOther;
            Item *tempOther = children;
            Ball *tempBall = static_cast<Ball*>(tempChild->elem);
            int startX, startY, endX, endY;

            while (tempOther)
            {
                // prevent detecting collision with self
                if (tempOther == tempChild) {
                    tempOther = tempOther->next;
                    continue;
                }

                otherRect = tempOther->elem->getImageRect();
                if (SDL_HasIntersection(otherRect, rect)) {

                    #ifdef DEBUG_MODE
                    std::cout << " --- Collision with an object";
                    #endif
                                        
                    typeOther = tempOther->elem->getType();

                    // [ choose types ball can collide with here (add or remove type from condition) ]
                    if (typeOther == TYPE_PLAYER || typeOther == TYPE_BALL || typeOther == TYPE_ENEMY) {

                        // set a flag informing, that a ball has collided with something
                        if (typeOther == TYPE_PLAYER) {

                            // tell the ball, that it boost is available for it
                            tempBall->approveBoost(true);

                            if (!tempBall->prevBorCol) flags |= EVENT_BALLCOLL;
                        }

                        if (typeOther == TYPE_ENEMY)
                            static_cast<Enemy*>(tempOther->elem)->stabilize();

                        // check collision with all sides
                        tempOther->elem->leftSideLine(startX, startY, endX, endY);
                        if (SDL_IntersectRectAndLine(rect, &startX, &startY, &endX, &endY)) {
                            if (tempBall->prevColHor != otherRect) {
                                tempBall->moveLeft();

                                // store an object a ball currently collides with horizontally
                                tempBall->prevColHor = otherRect;
                            }
                        }
                        else {
                            tempOther->elem->rightSideLine(startX, startY, endX ,endY);
                            if (SDL_IntersectRectAndLine(rect, &startX, &startY, &endX, &endY)) {
                                if (tempBall->prevColHor != otherRect) {
                                    tempBall->moveRight();
                                    tempBall->prevColHor = otherRect;
                                }
                            }
                        }

                        // handle top/bottom collision a bit differently
                        tempOther->elem->topSideLine(startX, startY, endX, endY);
                        if (SDL_IntersectRectAndLine(rect, &startX, &startY, &endX, &endY)) {
                            if (tempBall->prevColVert != otherRect) {

                                // calculate new angle (more to the sides of object, greater the angle)
                                float xVel = -10.0f * (tempOther->elem->getX() - tempBall->getX()) / tempOther->elem->getWidth();
                                tempBall->alterXVelocity(xVel);
                                tempBall->reverseYVelocity();

                                // store an object a ball currently collides with vertically
                                tempBall->prevColVert = otherRect;
                            }
                        }
                        else {
                            tempOther->elem->bottomSideLine(startX, startY, endX, endY);
                            if (SDL_IntersectRectAndLine(rect, &startX, &startY, &endX, &endY)) {
                                if (tempBall->prevColVert != otherRect) {

                                    float xVel = -10.0f * (tempOther->elem->getX() - tempBall->getX()) / tempOther->elem->getWidth();
                                    tempBall->alterXVelocity(xVel);
                                    tempBall->reverseYVelocity();

                                    tempBall->prevColVert = otherRect;
                                }
                            }
                        }
                    }

                    tempBall->prevBorCol = nullptr;

                }

                tempOther = tempOther->next;
            }
        }

        tempChild = tempChild->next;
    }    

}

void Scene::tellEnemies() const
{
    enemy->setDirection(ball->getXSpeed());
}

void Scene::playerCoords(float &x, float &y)
{
    player->getPos(x, y);
}

unsigned short Scene::getFlags()
{
    return flags;
}

void Scene::resetFlags()
{
    flags = 0;
}

void Scene::resetChildren()
{
    if (!children) return;

    Item *tempChild = children;

    while (tempChild)
    {           
        tempChild->elem->reset();
        tempChild = tempChild->next;
    }
}

