#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <stdexcept>

#include <Entry.h>
#include <Entries.h>
#include <EntriesRef.h>
#include <DBManager.h>
#include <generate.h>
#include <iostream>
#include <random>
#include <QFile>

BOOST_AUTO_TEST_CASE(Entry_contain_test)
{
	Entry input{
		"Furin",
		"Igor",
		"Olegovich",
		"+79818764773"
	};
	BOOST_CHECK(input.contain("Fu") == true);
	BOOST_CHECK(input.contain("or") == true);
	BOOST_CHECK(input.contain("govich") == true);
	BOOST_CHECK(input.contain("+79818764773") == true);
	BOOST_CHECK(input.contain("Olya") == false);
	BOOST_CHECK(input.contain("Furina") == false);
	BOOST_CHECK(input.contain("+79818764774") == false);
}

BOOST_AUTO_TEST_CASE(Entry_operators_test)
{
	Entry left{
		"Furin",
		"Igor",
		"Olegovich",
		"+79818764773"
	};
	{
		Entry left_copy = left;
		BOOST_CHECK(left == left_copy);
		BOOST_CHECK((left > left_copy) == false);
	}
	{
		Entry right{
			"Furina",
			"Igor",
			"Olegovich",
			"+79818764773"
		};
		BOOST_CHECK((left == right) == false);
		BOOST_CHECK( right > left );
	}
}

BOOST_AUTO_TEST_CASE(Entries_test)
{
	auto generated_entries = entriesGenerator(30);
	{
		Entries entries(generated_entries);
		BOOST_CHECK(entries.size() == generated_entries.size());
	}
	// empty size test
	{
		Entries empty_entries;
		BOOST_CHECK(empty_entries.size() == 0);
	}
	// for range test
	{
		Entries entries(generated_entries);
		for (const auto& entry: entries){
			BOOST_CHECK(entry.first_name.size() > 0);
			BOOST_CHECK(entry.last_name.size() > 0);
			BOOST_CHECK(entry.father_name.size() > 0);
			BOOST_CHECK(entry.phone.size() > 0);
		}
	}
	// push_back test
	{
		Entries entries;
		for (size_t i = 0; i < 10; i++ ){
			entries.push_back(entryGenerator());
			BOOST_CHECK(entries.size() == i+1);
		}
	}
	// erase test
	{
		Entries entries(generated_entries);
		size_t init_size = entries.size();
		for (size_t i = 0; i < entries.size(); ){
			entries.erase(i);
			init_size--;
			BOOST_CHECK(entries.size() == init_size);
		}
	}
	{
		Entries entries(generated_entries);
		for (size_t i = 0; i < entries.size(); i++){
			BOOST_CHECK(generated_entries.at(i) == entries.at(i));
		}
	}
	{
		Entries entries(generated_entries);
		for (size_t i = 0; i < entries.size(); i++){
			QString new_name("Vasya");
			entries[i].first_name = new_name;
			BOOST_CHECK(entries.at(i).first_name == new_name);
		}
	}
}

BOOST_AUTO_TEST_SUITE(EntriesRef_test)
BOOST_AUTO_TEST_CASE(EntryRef_size_test)
{
	auto generated_entries = entriesGenerator(30);
	// empty
	{
		Entries entries;
		EntriesRef entrise_ref(&entries, "");
		BOOST_CHECK(entrise_ref.size() == 0);
	}
	// full size
	{
		Entries entries(generated_entries);
		EntriesRef entries_ref(&entries, "");
		BOOST_CHECK(entries_ref.size() == entries.size());
	}
	// general size test
	{
		QString filter = "a";
		Entries entries(generated_entries);
		EntriesRef entries_ref(&entries, filter);
		size_t counter = 0;
		for (const auto& item: entries)
		{
			if (item.contain(filter)){
				counter++;
			}
		}
		BOOST_CHECK(entries_ref.size() == counter);
	}
}

BOOST_AUTO_TEST_CASE(EntryRef_catch_test)
{
	auto generated_entries = entriesGenerator(30);
	{
		Entries entries(generated_entries);
		QString filter = entries.at(0).first_name.at(0);
		EntriesRef entrise_ref(&entries, filter);
		for (size_t i = 0; i < entrise_ref.size(); i++){
			BOOST_CHECK(entries.at(entrise_ref.getIndex(i)) == entrise_ref.at(i));
		}
	}
}

BOOST_AUTO_TEST_CASE(EntryRef_append_test)
{
	auto generated_entries = entriesGenerator(30);
	// empty size
	{
		Entries entries;
		QString filter = "a";
		EntriesRef entrise_ref(&entries, filter);
		size_t counter = 0;
		for (size_t i = 0; i < 20; i++){
			Entry entry = entryGenerator();
			if (entry.contain(filter)){
				counter++;
			}
			entrise_ref.push_back(entry);
			BOOST_CHECK(entries.size() == i+1);
			BOOST_CHECK(entrise_ref.size() == counter);
		}
	}
	// entires.size == entrise_ref.size
	{
		Entries entrise(generated_entries);
		QString filter = "";
		EntriesRef entrise_ref(&entrise, filter);
		for (size_t i = 0; i < 20; i++){
			Entry entry = entryGenerator();
			entrise_ref.push_back(entry);
			BOOST_CHECK(entrise.size() == entrise_ref.size());
			BOOST_CHECK(entrise.at(entrise.size() - 1)
						== entrise_ref.at(entrise_ref.size() - 1));
		}
	}
}

BOOST_AUTO_TEST_CASE(EntryRef_erase_test){
	auto generated_entries = entriesGenerator(30);
	{
		Entries entrise(generated_entries);
		QString filter = generated_entries.at(0).first_name.at(0);
		EntriesRef entrise_ref(&entrise, filter);
		BOOST_CHECK(entrise_ref.size() > 0);
		size_t difference = entrise.size() - entrise_ref.size();
		while(entrise_ref.size() > 0){
			entrise_ref.erase(0);
			BOOST_CHECK((entrise.size() - entrise_ref.size()) == difference);
		}
		BOOST_CHECK(entrise_ref.size() == 0);
	}
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(DBManager_test)
BOOST_AUTO_TEST_CASE(load_save_test)
{
	QString db_name = "./mydb";
	auto data = entriesGenerator(20);
	DBManager manager;
	BOOST_CHECK(manager.save(db_name, data) == data.size());
	auto loaded_data = manager.load(db_name);
	qDebug() << "load size = " << loaded_data.size();
	BOOST_CHECK(data.size() == loaded_data.size());
	QFile file(db_name);
	file.remove();
}
BOOST_AUTO_TEST_SUITE_END()

