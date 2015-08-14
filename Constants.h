#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED

const int FPS = 60;
const int TICK_PER_FRAME = 1000 / FPS;

const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 576;

const int TILE_SIZE = 48;

const int LEVEL_WIDTH = 30;
const int LEVEL_HEIGHT = 30;

//Set Tile Types
const int TOTAL_TILES = 900;
const int TOTAL_TILE_SPRITES = 15;

const int TILE_CLEAR = 0;
const int TILE_SKY = 1;
const int TILE_WALL = 2;
const int TILE_WOOD = 3;
const int TILE_DOOR = 4;
const int TILE_LAVA = 5;
const int TILE_GRASS = 6;
const int TILE_WATER = 7;
const int TILE_PLATFORM = 10;
const int TILE_LADDER = 11;
const int TILE_LADDER_TOP = 12;
const int TILE_SLOPE_RIGHT = 13;
const int TILE_SLOPE_LEFT = 14;

const int TOTAL_DOORS = 2;

const float GRAVITY = 900;

struct Box
{
	float x;
	float y;
	float w;
	float h;
};


#endif // CONSTANTS_H_INCLUDED
