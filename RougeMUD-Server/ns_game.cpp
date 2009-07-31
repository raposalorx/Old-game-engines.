#include "ns_game.h"

int ns_game::fps, ns_game::cur_fps;
UDPsocket ns_game::sd; // Socket descriptor
IPaddress ns_game::srvadd;
UDPpacket *ns_game::p; // Pointer to packet memory

string itoa (int n) 
{
	char * s = new char[17];
	string u;

	if (n < 0) { //turns n positive
		n = (-1 * n); 
		u = "-"; //adds '-' on result string
	}

	int i=0; //s counter
  
	do {
		s[i++]= n%10 + '0'; //conversion of each digit of n to char
		n -= n%10; //update n value
	}

	while ((n /= 10) > 0);

	for (int j = i-1; j >= 0; j--) { 
		u += s[j]; //building our string number
	}

	delete[] s; //free-up the memory!
	return u;
}

void StringExplode(string str, string separator, vector<string>* results)
{
	results->clear();
    int found;
    found = str.find_first_of(separator);
    while(found != string::npos)
	{
        if(found > 0)
		{
            results->push_back(str.substr(0,found));
        }
        str = str.substr(found+1);
        found = str.find_first_of(separator);
    }
    if(str.length() > 0)
	{
        results->push_back(str);
    }
}

char* GetUDP()
{
	using namespace ns_game;
	
	char* buf; // swap var
	UDPpacket* pack = SDLNet_AllocPacket(512); // new packet
	if(SDLNet_UDP_Recv(sd, pack)) // grab a packet if you can
	{
		// printf("UDP Packet incoming\n");
		// printf("\tChan:    %d\n", pack->channel);
		// printf("\tData:    %s\n", (char *)pack->data);
		// printf("\tLen:     %d\n", pack->len);
		// printf("\tMaxlen:  %d\n", pack->maxlen);
		// printf("\tStatus:  %d\n", pack->status);
		// printf("\tAddress: %x %x\n", pack->address.host, pack->address.port);
		buf = (char *)pack->data;
	}
	else // no packet to grab
	{
		buf = NULL;
	}
	SDLNet_FreePacket(pack);
	return buf; // return packets data only
}

void SendUDP(const char* data)
{
	using namespace ns_game;
	
	p->data = (Uint8 *)data;// sets packet data
	p->len = strlen((char *)p->data) + 1;
	SDLNet_UDP_Send(sd, -1, p);// sends packet
}