#ifndef ROGUEMUD_NS_GAME_H
#define ROGUEMUD_NS_GAME_H

#include <SDL_net.h>
#include <SDL_opengl.h>
#include <vector>

#include "texture.h"
#include "being.h"

class Game;
class State;

using namespace std;

/**
	The game namespace is used to statically store information introduced by game.h/cpp
**/

namespace ns_game
{
	extern int WIDTH, HEIGHT, fps, cur_fps, cur_state, next_state, ID;
	extern bool FULLSCREEN;
	extern SDL_Surface* screen;
	extern vector<Texture> textureDB;
	extern vector<Being> beingDB;
	extern SDL_Event event;

	extern UDPsocket sd;
	extern IPaddress srvadd;
	extern UDPpacket *p;

	enum States
	{
		STATE_NULL,
		STATE_LOGIN,
		STATE_GAME,
		STATE_EXIT,
	};
}

string itoa (int n);
void StringExplode(string str, string separator, vector<string>* results);
char* GetUDP();
void SendUDP(const char* data);

#endif
