#pragma once
#include <vector>
#include <Entry.h>
#include <algorithm>

class Entries
{
public:
	using iterator = std::vector<Entry>::iterator;
	using const_interator = std::vector<Entry>::const_iterator;
	Entries(const std::vector<Entry>& entries = std::vector<Entry>());
	size_t size() const;
	void push_back(const Entry& entry);
	std::vector<Entry>::iterator begin();
	std::vector<Entry>::iterator end();
	void erase(size_t index);
	void erase(iterator it);
	Entry& operator[](size_t index);
	Entry at(size_t index) const;
	std::vector<Entry> entries() const;
private:
	std::vector<Entry> m_entries;
};
