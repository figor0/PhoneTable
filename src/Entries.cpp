#include <Entries.h>

Entries::Entries(const std::vector<Entry> &entries):
	m_entries(entries)
{}

size_t Entries::size() const{
	return m_entries.size();
}

void Entries::push_back(const Entry &entry){
	m_entries.push_back(entry);
}

void Entries::erase(Entries::iterator it)
{
	m_entries.erase(it);
}

Entry &Entries::operator[](size_t index)
{
	return m_entries[index];
}

Entry Entries::at(size_t index) const
{
	return m_entries.at(index);
}

std::vector<Entry> Entries::entries() const
{
	return m_entries;
}

std::vector<Entry>::iterator Entries::begin(){
	return m_entries.begin();
}

std::vector<Entry>::iterator Entries::end(){
	return m_entries.end();
}

void Entries::erase(size_t index){
	auto it  = std::find(m_entries.begin(), m_entries.end(), at(index));
	if (it != end()){
		m_entries.erase(it);
	}
}
