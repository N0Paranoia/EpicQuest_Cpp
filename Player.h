#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include <SDL_image.h>
#include "Tile.h"
#include <iostream>

using namespace std;

class Player
{
	private:
		enum State
		{
			state_idle,
			state_jumping,
			state_walking,
			state_running,
			state_attacking,
			state_blocking,
			state_climbing
		};

		enum Direction
		{
			left,
			right,
			up,
			down,
			jump
		};
		
		int _state;
		
		const Uint8* keyState;
		int Xvel;
		int Yvel;
		int Jvel;
		int walkingSpeed;
		int runningSpeed;

		int frame;
		int StartFrameLeft;
		int EndFrameLeft;
		int StartFrameRight;
		int EndFrameRight;
		int IdleFrameLeft;
		int IdleFrameRight;
		int frameCounter;
		int frameSpeed;
		int frameSwitch;

		int jumpCount;
		int jumpSpeed;
		int jumpHeight;

		int climbingSpeed;

		bool WalkingLeft;
		bool WalkingRight;
		bool FacingLeft;
		bool FacingRight;
		bool isRunning;
		bool isFalling;
		bool canJump;
		bool isJumping;

		bool canEnterDoor;
		bool isClimbing;

		bool attack;
		bool isAttacking;
		bool block;
		bool isBlocking;
		
		int attackEnergy;
		int blockEnergy;

		int maxEnergy;
		int energy;
		bool energyRecover;
		int maxHealth;
		int health;

		SDL_Rect PlayerClips[18];
		SDL_Rect ShieldBox;
		SDL_Rect Shield;
		SDL_Rect SwordBox;
		SDL_Rect Sword;
		SDL_Rect HealthBar;
		SDL_Rect StaminBar;
	public:
		//Collision box
		SDL_Rect playerRect;
		SDL_Rect playerBox;

		Player();
		virtual ~Player();
		//void Event(SDL_Event* event);
		void Input(Tile* tiles[]);
		int LoadMedia(SDL_Renderer* Renderer);
		void Move(int Dir, Tile* tiles[]);
		void Attack();
		void Block();
		void Jump(Tile* tiles[]);
		void Climb(int Dir, Tile* tiles[]);
		void Falling(Tile* tiles[]);
		void GoTroughDoor(Tile* tiles[]);
		int Health();
		int Energy(int action);
		void Render(SDL_Renderer* Renderer, SDL_Rect* camera);
		void Cleanup();

	protected:
};

#endif // PLAYER_H
