#include "Ai.h"
#include "Constants.h"
#include "Collision.h"
#include "Physics.h"

Collision aiCollision;
Physics aiPhysics;

Ai::Ai()
{
    for(int i = 0; i < TOTAL_TILES; i++)
    {
        isFalling[i] = true;
    }
}

Ai::~Ai()
{
    //dtor
}

int Ai::Input(int i)
{
    if(movement[i] == left)
    {
        return -4;
    }
    if(movement[i] == right)
    {
        return 4;
    }
    if(movement[i] == idle)
    {
        return 0;
    }
    return 0;
}

void Ai::Agro(Mobs* mobs[], int i, Tile* tiles[], SDL_Rect* playerRect, int type)
{
    switch(type)
    {
        case MOB_TYPE_1:
        if(playerRect->y > (mobs[i]->getMobBox().y - AGRO_RANGE) && playerRect->y < ((mobs[i]->getMobBox().y + mobs[i]->getMobBox().h) + AGRO_RANGE))
        {
            if(playerRect->x + playerRect->w < mobs[i]->getMobBox().x && playerRect->x + playerRect->w > mobs[i]->getMobBox().x - AGRO_RANGE)
            {
                movement[i] = left;
            }
            else if(playerRect->x > (mobs[i]->getMobBox().x + mobs[i]->getMobBox().w) && playerRect->x < (mobs[i]->getMobBox().x + mobs[i]->getMobBox().w) + AGRO_RANGE)
            {
                movement[i] = right;
            }
        }
    }
}

int Ai::Fall(Mobs* mobs[], int i, Tile* tiles[])
{
    if(aiPhysics.Gravity(mobs[i]->getMobBox(), tiles))
    {
        isFalling[i] = false;
        return mobs[i]->getMobBox().y;
    }
    else
    {
        isFalling[i] = true;
        return mobs[i]->getMobBox().y + GRAVITY;
    }
}

int Ai::Move(Mobs* mobs[], int i, Tile* tiles[], SDL_Rect* playerRect, int type)
{
    //----Basic Wallcollision Ai----//
    if(aiCollision.Wall(mobs[i]->getMobBox(), tiles))
    {
        if(movement[i] == left)
        {
            movement[i] = right;
        }
        else if(movement[i] == right)
        {
            movement[i] = left;
        }
    }
    //----Basic Wallcollision Ai----//
    return mobs[i]->getMobBox().x + this->Input(i);
}

int Ai::Update(Mobs* mobs[], int i, Tile* tiles[], SDL_Rect* playerRect, int type, int axis)
{
    //---- Basic Ai "input"----//
    this->Input(i);
    //----Basic Agro Ai----//
    this->Agro(mobs, i, tiles, playerRect, type);
    switch(axis)
    {
        case 0:
        //----Basic Ai Horizontal Movement and collision ----//
        return this->Move(mobs, i, tiles, playerRect, type);
        break;

        case 1:
            //----Basic Ai Vertical Movement and collision ----//
        return this->Fall(mobs, i , tiles);
        break;
    }
    return 0;
}

void Ai::Debug()
{
    cout << "Debug!" << endl;
}
