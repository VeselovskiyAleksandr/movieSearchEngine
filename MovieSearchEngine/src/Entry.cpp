#include "Entry.h"

struct Entry
{
	size_t docId, freqWordsCount;
	string word;
	bool operator ==(const Entry& other) const {
		return (docId == other.docId && freqWordsCount == other.freqWordsCount);
	}
};