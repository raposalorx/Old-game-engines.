#include "game.h"

Game::Game()
{

}

Game::~Game()
{
}

bool Game::LoopEvents()
{
	// Wait a packet. UDP_Recv returns != 0 if a packet is coming
	char* data;
	if ((data = GetUDP())!=NULL)
	{
		if (strcmp(data, "login") == 0)
		{
			printf("logging in...\n");
			if(inActiveList.size()>0)
			{
				SendUDP(itoa(inActiveList[inActiveList.size()-1]).c_str());// gives the loggie an id
				inActiveList.pop_back();
			}
			else
			{
				SendUDP(itoa(beingDB.size()).c_str());// gives the loggie an id
				beingDB.push_back(*(new Being));// creates a new being for the loggie
			}
			// init
			beingDB[atoi((char*)p->data)].x = 0;
			beingDB[atoi((char*)p->data)].y = 0;
			beingDB[atoi((char*)p->data)].active = true;
			
			printf("data:%s\n", (char*)p->data);
			
			printf("logged in!\n");
		}
		else
		{
			vector<string> action;
			action.clear();
			StringExplode(data, ":", &action);
			//movments are based around the dwarfs dementions
			if(strcmp(action[1].c_str(), "DOWN") == 0 && beingDB[atoi(action[0].c_str())].y+22 <= 480)
				beingDB[atoi(action[0].c_str())].y+=11;
			if(strcmp(action[1].c_str(), "UP") == 0 && beingDB[atoi(action[0].c_str())].y-11 >= 0)
				beingDB[atoi(action[0].c_str())].y-=11;
			if(strcmp(action[1].c_str(), "LEFT") == 0 && beingDB[atoi(action[0].c_str())].x-8 >= 0)
				beingDB[atoi(action[0].c_str())].x-=8;
			if(strcmp(action[1].c_str(), "RIGHT") == 0 && beingDB[atoi(action[0].c_str())].x+16 <= 640)
				beingDB[atoi(action[0].c_str())].x+=8;
			if(strcmp(action[1].c_str(), "logout") == 0)
			{
				printf("logging out...\n");
				// save the ID for recycling
				beingDB[atoi(action[0].c_str())].active = false;
				inActiveList.push_back(atoi(action[0].c_str()));
				printf("logged out!\n");
			}
		}
		
		string beings;
		beings[0] = '\0';
		for(int i = 0; i < beingDB.size(); i++)// send being list to clients
		{
			if(beingDB[i].active)// only bother with ID's that are in use
			{
				strcat((char*)beings.c_str(), itoa(i).c_str());// ID
				strcat((char*)beings.c_str(), ":");
				strcat((char*)beings.c_str(), itoa(beingDB[i].x).c_str()); // ID:x
				strcat((char*)beings.c_str(), ":");
				strcat((char*)beings.c_str(), itoa(beingDB[i].y).c_str());// ID:x:y
				if(i != beingDB.size()-1)
					strcat((char*)beings.c_str(), ";");// ID:x:y;...
			}
		}
		SendUDP(beings.c_str());
		
	}	
	return false;
}

bool Game::LoopLogic()
{
	return false;
}