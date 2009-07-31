#include "radixtrie.h"

RadixTrie::RadixTrie()
{
	top_child = new RadixElement;
}

RadixTrie::~RadixTrie()
{
}

void RadixTrie::AddString(const char* new_str, void* end, int type)
{
	if (Search(new_str)) return;
	RadixElement* element = top_child;
	int aa = 0;
	while (new_str[aa] != '\0')
	{
		element = AddElement(element, new_str[aa]);
		element->ends++;
		aa++;
	}
	element->end = end;
	element->end_type = type;
	element->valid_end = true;
}

int RadixTrie::Search(const char* tar_str)
{
	RadixElement* element = top_child;
	int aa = 0;
	while (tar_str[aa] != '\0')
	{
		element = GetElement(element, tar_str[aa]);
		if (element == NULL)
			return false;
		aa++;
	}

	if (element->valid_end)
	{
		last = element;
		return RESULT_EXACT;
	}
	else if (element->ends == 1)
	{
		while (element->valid_end == false)
		{
			element = element->childDB[0];
		}
		last = element;
		return RESULT_SINGLE;
	}
	else if (element->ends > 1)
	{
		last = NULL;
		return RESULT_MULTIPLE;
	}
	else
	{
		last = NULL;
		return RESULT_NONE;
	}
}

void* RadixTrie::GetLast()
{
	return last->end;
}

int RadixTrie::GetLastType()
{
	return last->end_type;
}

RadixElement* RadixTrie::AddElement(RadixElement* element, char new_ch)
{
	RadixElement* new_element;

	// Check if the new element already exists
	new_element = GetElement(element, new_ch);
	if (new_element == NULL)
	{
		// Fill the element's properties in
		new_element = new RadixElement;
		new_element->ch = new_ch;
		new_element->end = NULL;
		new_element->valid_end = false;
		new_element->ends = 0;
		element->childDB.push_back(new_element);
	}

	// Return the new element
	return new_element;
}

RadixElement* RadixTrie::GetElement(RadixElement* element, char tar_ch)
{
	RadixElement* tar_element;

	// Search for the specified element
	int size = element->childDB.size();
	for (int aa = 0; aa < size; aa++)
	{
		tar_element = element->childDB[aa];
		if (tar_element->ch == tar_ch)
			return tar_element;
	}

	return NULL;
}
