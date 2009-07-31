#ifndef ROGUEMUD_NS_GAME_H
#define ROGUEMUD_NS_GAME_H

#include <SDL_net.h>
#include <vector>
#include <string>

using namespace std;

/**
**/

namespace ns_game
{
	extern int fps, cur_fps;
	extern UDPsocket sd; // Socket descriptor
	extern IPaddress srvadd;
	extern UDPpacket *p; // Pointer to packet memory
}

string itoa(int n);
void StringExplode(string str, string separator, vector<string>* results);
char* GetUDP();
void SendUDP(const char* data);

#endif
