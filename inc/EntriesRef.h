#pragma once
#include <Entries.h>
#include <QString>
#include <vector>
#include <algorithm>

class EntriesRef{
public:
	using Index = size_t;
	using iterator = std::vector<Index>::iterator;
	using const_iterator = std::vector<Index>::const_iterator;
	EntriesRef(Entries* entries_raw_ptr,
			   const QString& filter);
	size_t size();
	Index getIndex(size_t page_index);
	Entry at(const Index index) const;
	Entry& operator[](const Index index);
	void push_back(const Entry& entry);
	void erase(const Index index);
	iterator begin();
	iterator end();
	QString getFilter() const;
private:
	QString m_filter;
	Entries* m_entries_raw_ptr;
	std::vector<Index> m_page;
};
