#include "World.h"
#include "Constants.h"
#include "Textures.h"
#include "Tile.h"
#include "Mobs.h"
#include "Ai.h"
#include "Shadows.h"
#include <fstream>
#include <math.h>

Ai wAi;

Textures MobSheetTexture;
Textures TileSheetTexture;
Textures ShadowTexture;

World::World()
{
    Type = 0;
    Type_Mobs = 1;
	Type_Shadows = 1;
}

World::~World()
{
    //dtor
}

int World::LoadMedia(SDL_Renderer* Renderer, Tile* tiles[], Mobs* mobs[])
{
    //Load Tilemap
    if(!SetTiles(tiles, mobs))
    {
        cout << "Unable to load Tile Map! SDL_Error: " << SDL_GetError() << endl;
        return false;
    }
    if(!SetMobs(mobs))
    {
        cout << "Unable to load Mobs! SDL_Error: " << SDL_GetError() << endl;
        return false;
    }
    //Load PNG Shadow texture
    if((ShadowTexture.LoadFromFile(Renderer, "assets/shadows.png")) == 0)
    {
        cout << "Unable to Load texture image! SDL_Error: " << SDL_GetError() << endl;
        return false;
	} 
	else
    {
        //All mob textures
        ShadowClips[0].x = 0;
        ShadowClips[0].y = 0;
        ShadowClips[0].w = 500;
        ShadowClips[0].h = 500;
        
        ShadowClips[1].x = 500;
        ShadowClips[1].y = 0;
        ShadowClips[1].w = 500;
        ShadowClips[1].h = 500;
 
        ShadowClips[2].x = 1000;
        ShadowClips[2].y = 0;
        ShadowClips[2].w = 5;
        ShadowClips[2].h = 5;
    }
    //Load mobSheet
    if((MobSheetTexture.LoadFromFile(Renderer, "assets/mobSheet.png")) == 0)
    {
        cout << "Unable to load Mob Texture! SDL_Error: " << SDL_GetError() << endl;
        return false;
    }
    else
    {
        //All mob textures
        MobClips[MOB_CLEAR].x = -TILE_SIZE;
        MobClips[MOB_CLEAR].y = -2*TILE_SIZE;
        MobClips[MOB_CLEAR].w = TILE_SIZE;
        MobClips[MOB_CLEAR].h = TILE_SIZE;

        MobClips[MOB_TYPE_1].x = 0 * TILE_SIZE;
        MobClips[MOB_TYPE_1].y = 0 * TILE_SIZE;
        MobClips[MOB_TYPE_1].w = 1 * TILE_SIZE;
        MobClips[MOB_TYPE_1].h = 2 * TILE_SIZE;
    }
    //Load tilesheet
    if((TileSheetTexture.LoadFromFile(Renderer, "assets/tileSheet48.png")) == 0)
    {
        cout << "Unable to load Tile Texture! SDL_Error: " << SDL_GetError() << endl;
        return false;
    }
    else
    {
        //All tile textures
        TileClips[TILE_CLEAR].x = -TILE_SIZE;
        TileClips[TILE_CLEAR].y = -TILE_SIZE;
        TileClips[TILE_CLEAR].w = TILE_SIZE;
        TileClips[TILE_CLEAR].h = TILE_SIZE;

        TileClips[TILE_SKY].x = 0 * TILE_SIZE;
        TileClips[TILE_SKY].y = 0 * TILE_SIZE;
        TileClips[TILE_SKY].w = TILE_SIZE;
        TileClips[TILE_SKY].h = TILE_SIZE;

        TileClips[TILE_WALL].x = 1 * TILE_SIZE;
        TileClips[TILE_WALL].y = 0 * TILE_SIZE;
        TileClips[TILE_WALL].w = TILE_SIZE;
        TileClips[TILE_WALL].h = TILE_SIZE;

        TileClips[TILE_WOOD].x = 2 * TILE_SIZE;
        TileClips[TILE_WOOD].y = 0 * TILE_SIZE;
        TileClips[TILE_WOOD].w = TILE_SIZE;
        TileClips[TILE_WOOD].h = TILE_SIZE;

        TileClips[TILE_DOOR].x = 3 * TILE_SIZE;
        TileClips[TILE_DOOR].y = 0 * TILE_SIZE;
        TileClips[TILE_DOOR].w = TILE_SIZE;
        TileClips[TILE_DOOR].h = TILE_SIZE;

        TileClips[TILE_LAVA].x = 0 * TILE_SIZE;
        TileClips[TILE_LAVA].y = 1 * TILE_SIZE;
        TileClips[TILE_LAVA].w = TILE_SIZE;
        TileClips[TILE_LAVA].h = TILE_SIZE;

        TileClips[TILE_GRASS].x = 1 * TILE_SIZE;
        TileClips[TILE_GRASS].y = 1 * TILE_SIZE;
        TileClips[TILE_GRASS].w = TILE_SIZE;
        TileClips[TILE_GRASS].h = TILE_SIZE;

        TileClips[TILE_WATER].x = 2 * TILE_SIZE;
        TileClips[TILE_WATER].y = 1 * TILE_SIZE;
        TileClips[TILE_WATER].w = TILE_SIZE;
        TileClips[TILE_WATER].h = TILE_SIZE;

        TileClips[TILE_PLATFORM].x = 1 * TILE_SIZE;
        TileClips[TILE_PLATFORM].y = 2 * TILE_SIZE;
        TileClips[TILE_PLATFORM].w = TILE_SIZE;
        TileClips[TILE_PLATFORM].h = TILE_SIZE;

        TileClips[TILE_LADDER].x = 2 * TILE_SIZE;
        TileClips[TILE_LADDER].y = 2 * TILE_SIZE;
        TileClips[TILE_LADDER].w = TILE_SIZE;
        TileClips[TILE_LADDER].h = TILE_SIZE;

        TileClips[TILE_LADDER_TOP].x = 3 * TILE_SIZE;
        TileClips[TILE_LADDER_TOP].y = 2 * TILE_SIZE;
        TileClips[TILE_LADDER_TOP].w = TILE_SIZE;
        TileClips[TILE_LADDER_TOP].h = TILE_SIZE;

        TileClips[TILE_SLOPE_RIGHT].x = 0 * TILE_SIZE;
        TileClips[TILE_SLOPE_RIGHT].y = 3 * TILE_SIZE;
        TileClips[TILE_SLOPE_RIGHT].w = TILE_SIZE;
        TileClips[TILE_SLOPE_RIGHT].h = TILE_SIZE;

        TileClips[TILE_SLOPE_LEFT].x = 1 * TILE_SIZE;
        TileClips[TILE_SLOPE_LEFT].y = 3 * TILE_SIZE;
        TileClips[TILE_SLOPE_LEFT].w = TILE_SIZE;
        TileClips[TILE_SLOPE_LEFT].h = TILE_SIZE;
    }
    return true;
}

bool World::SetTiles(Tile* tiles[], Mobs* mobs[])
{
    int x = 0;
    int y = 0;

    std::ifstream map("assets/level.map");

    if (map == NULL)
    {
        cout << "Unable to load Tile Map file!" << endl;
        return false;
    }
    else
    {
        //Initialize tiles
        for(int i = 0; i < TOTAL_TILES; i++)
        {
            int Type_Tiles = -1;
            map >> Type_Tiles;

            if(map.fail())
            {
                cout << "Error loading map: Unexpected end of file!" << endl;
                return false;
                break;
            }
            //if number is valid tile number
            if((Type_Tiles >= 0) && (Type_Tiles < TOTAL_TILE_SPRITES))
            {
                tiles[i] = new Tile(x, y, Type_Tiles);
            }
            else
            {
               cout << "Error loading map: Invalid tile type!" << endl;
               return false;
               break;
            }
            x += TILE_SIZE;
			//If we've gone too far
			if(x >= LEVEL_WIDTH*TILE_SIZE)
			{
                //Move back
				x = 0;
				//Move to the next row
				y += TILE_SIZE;
			}
        }
    }
    return true;
}

bool World::SetMobs(Mobs* mobs[])
{
    int x = 0;
    int y = 0;

    std::ifstream mobmap("assets/mob.map");

    if (mobmap == NULL)
    {
        cout << "Unable to load Tile Map file!" << endl;
        return false;
    }
    else
    {
        //Initialize tiles
        for(int i = 0; i < TOTAL_TILES; i++)
        {
            int Type_Mobs = -1;
            mobmap >> Type_Mobs;

            if(mobmap.fail())
            {
                cout << "Error loading mobmap: Unexpected end of file!" << endl;
                return false;
                break;
            }
            //if number is valid tile number
            if((Type_Mobs >= 0) && (Type_Mobs < TOTAL_MOB_SPRITES))
            {
                mobs[i] = new Mobs(x, y, Type_Mobs);
            }
            else
            {
               cout << "Error loading mobmap: Invalid tile type!" << endl;
               return false;
               break;
            }
            x += TILE_SIZE;
			//If we've gone too far
			if(x >= LEVEL_WIDTH*TILE_SIZE)
			{
                //Move back
				x = 0;
				//Move to the next row
				y += TILE_SIZE;
			}
        }
    }
    return true;
}

//function for calculating the end point from one location, to specific end location
//like a bullet moving forward in a line
//x,y start location(mouse), x2,y2(rect point location one of the 4) mid point, qx,qy end point(shadow or triangle draw location)
//startx, starty, endx, endy window in which calculate everything
void World::ScreenEnd(int x, int y, int x2, int y2, int*qx,int*qy,int startx,int starty, int endx,int endy)
{
	x = x2-x;
	y = y2-y;

	float tx = x2,ty = y2;

	float result = atan2((float)y,(float)x) * 180 / PI;

	float tempx = cos ( result * PI / 180.0 );
	float tempy = sin ( result * PI / 180.0 );

	bool check = true;
	//this part needs optimization
	while(check)
	{
		if(tx < startx || ty < starty || tx > endx || ty > endy)
		{
			check = false;
		}
		else
		{
			tx += tempx;
			ty += tempy;
		}
	}

	*qx = tx;
	*qy = ty;
}

bool World::GenerateShadows(SDL_Rect* source_rect, Tile* tiles[], Shadows* shadows[])
{
	int x = 0;
	int y = 0;
	
	SDL_Rect shadowR1 = tiles[0]->getTileBox();
	SDL_Rect shadowR2 = tiles[0]->getTileBox();
	SDL_Rect cubeR = {0,0,0,0};
	bool finish = false;
	int draw = 0;

	if(source_rect->x < tiles[0]->getTileBox().x && source_rect->y < tiles[0]->getTileBox().y)
	{
		//calculate up to where calculate the end location
		// I reuse the old info of the triangle
		if(shadowR2.x+shadowR2.w >= WINDOW_WIDTH)
		{
			this->ScreenEnd(source_rect->x ,source_rect->y, tiles[0]->getTileBox().x, tiles[0]->getTileBox().x + tiles[0]->getTileBox().h, &x, &y, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
		}
	}
	shadows[1] = new Shadows(shadowR1.x, shadowR1.y, Type_Shadows);
	return true;
}

void  World::UpdateMobs(Mobs* mobs[], Tile* tiles[], SDL_Rect* playerRect)
{
    for(int i = 0; i < TOTAL_TILES; i++)
    {
        if(wAi.Health(mobs, i) == false)
        {
            if(mobs[i]->getType() == MOB_TYPE_1)
            {
                mobs[i] = new Mobs(wAi.Update(mobs, i, tiles, playerRect, Type_Mobs, X_AXIS), wAi.Update(mobs, i, tiles, playerRect, Type_Mobs, Y_AXIS), Type_Mobs);
            }
        }
    }
}
void World::Render(SDL_Renderer* Renderer, SDL_Rect* camera, Tile* tiles[], Mobs* mobs[], Shadows* shadows[], SDL_Rect* player)
{
    //Render Tiles
    for(int i = 0; i < TOTAL_TILES; i++)
    {
        tiles[i]->Render(&TileSheetTexture, &TileClips[Type], Renderer, camera);
    }
    //Render Mobs
    for(int i = 0; i < TOTAL_TILES; i++)
    {
        if(wAi.Health(mobs, i) == false)
        {
            mobs[i]->Render(&MobSheetTexture, &MobClips[Type], Renderer, camera);
	    }
    }
	shadows[1]->Render(&ShadowTexture, &ShadowClips[Type], Renderer, camera);
}
