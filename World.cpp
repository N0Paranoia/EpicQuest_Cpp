#include "World.h"
#include "Constants.h"
#include "Textures.h"
#include "Tile.h"
#include "Mobs.h"
#include <fstream>

Textures MobSheetTexture;
Textures TileSheetTexture;

World::World()
{
    Type = 0;
}

World::~World()
{
    //dtor
}

int World::LoadMedia(SDL_Renderer* Renderer, Tile* tiles[], Mobs* mobs[])
{
    //Load Tilemap
    if(!SetTiles(tiles))
    {
        cout << "Unable to load Tile Map! SDL_Error: " << SDL_GetError() << endl;
        return false;
    }
    if(!SetMobs(mobs))
    {
        cout << "Unable to load Mobs! SDL_Error: " << SDL_GetError() << endl;
        return false;
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

bool World::SetTiles(Tile* tiles[])
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
            //int Type = -1;

            map >> Type;

            if(map.fail())
            {
                cout << "Error loading map: Unexpected end of file!" << endl;
                return false;
                break;
            }
            //if number is valid tile number
            if((Type >= 0) && (Type < TOTAL_TILE_SPRITES))
            {
                tiles[i] = new Tile(x, y, Type);
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
    for(int i = 0; i < 2; i++)
    {
        mobs[i] = new Mobs(i*TILE_SIZE, 2*TILE_SIZE, 0);
    }
    return true;
}

void  World::UpdateMobs(Mobs* mobs[])
{
    // ------On to somthing-------
    cout << "MobBox[0].x = " << mobs[0]->getMobBox().x << endl;
}

void World::Render(SDL_Renderer* Renderer, SDL_Rect* camera, Tile* tiles[], Mobs* mobs[])
{
    for(int i = 0; i < TOTAL_TILES; i++)
    {
        tiles[i]->Render(&TileSheetTexture, &TileClips[Type], Renderer, camera);
    }

    // -------------
    // FOR TESTING!!
    //Render Mobs
    for(int i = 0; i < 2; i++)
    {
        mobs[i]->Render(&MobSheetTexture, &MobClips[1], Renderer, camera);
    }
    // -------------
}
