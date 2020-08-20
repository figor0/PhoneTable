#include <EntriesRef.h>

EntriesRef::EntriesRef(Entries *entries_raw_ptr, const QString &filter):
	m_filter(filter), m_entries_raw_ptr(entries_raw_ptr)
{
	Index counter = 0;
	for (const auto& item: *m_entries_raw_ptr){
		if (item.lastNameContain(filter) == true){
			m_page.push_back(counter);
		}
		counter++;
	}
}

size_t EntriesRef::size(){
	return m_page.size();
}

EntriesRef::Index EntriesRef::getIndex(size_t page_index){
	return m_page.at(page_index);
}

Entry EntriesRef::at(const EntriesRef::Index index) const{
	return m_entries_raw_ptr->at(m_page.at(index));
}

Entry &EntriesRef::operator[](const EntriesRef::Index index){
	return m_entries_raw_ptr->operator[](m_page.at(index));
}

void EntriesRef::push_back(const Entry &entry){
	if (entry.contain(m_filter)){
		m_page.push_back(m_entries_raw_ptr->size());
	}
	m_entries_raw_ptr->push_back(entry);
}

void EntriesRef::erase(const EntriesRef::Index index)
{
	auto it = std::find(m_page.begin(), m_page.end(), m_page.at(index));
	assert(it != m_page.end());
	m_entries_raw_ptr->erase(m_page.at(index));
	m_page.erase(it);
	for (auto& item: m_page){
		if (item > index){
			item--;
		}
	}
}

EntriesRef::iterator EntriesRef::begin(){
	return m_page.begin();
}

EntriesRef::iterator EntriesRef::end(){
	return m_page.end();
}

QString EntriesRef::getFilter() const
{
	return m_filter;
}
