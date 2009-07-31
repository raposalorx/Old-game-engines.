#ifndef AI_RADIXTRIE_H
#define AI_RADIXTRIE_H

#include <iostream>

#include <vector>

using namespace std;

struct RadixElement
{
	char ch;
	void* end;
	int end_type;
	bool valid_end;
	int ends;
	vector<RadixElement*> childDB;
};

class RadixTrie
{
	public:
		RadixTrie();
		~RadixTrie();

		void AddString(const char* new_str, void* end, int type);
		int Search(const char* tar_str);
		void* GetLast();
		int GetLastType();
	protected:
	private:
		RadixElement* last;
		RadixElement* AddElement(RadixElement* element, char new_ch);
		RadixElement* GetElement(RadixElement* element, char tar_ch);
		RadixElement* top_child;
};

enum SearchResults
{
	RESULT_NONE,
	RESULT_EXACT,
	RESULT_SINGLE,
	RESULT_MULTIPLE
};

#endif
