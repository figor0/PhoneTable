#include <generate.h>

QString wordGenerator(const size_t word_size)
{
	QString result;
	int a_code = static_cast<int>('a');
	int z_code = static_cast<int>('z');
	for (size_t i = 0; i < word_size; i++){
		int code = rand()%(z_code - a_code);
		result.push_back(static_cast<char>(code + a_code));
	}
	assert(result.size() == word_size);
	return result;
}

QString numberGenerator()
{
	QString result("+");
	for (size_t i = 0; i < 11; i++){
		int number = rand()%10;
		result.push_back(QString::number(number));
	}
	assert(result.size() == 12);
	return result;
}

Entry entryGenerator()
{
	return {
		wordGenerator(8),
				wordGenerator(8),
				wordGenerator(8),
				numberGenerator()
	};
}

std::vector<Entry> entriesGenerator(size_t amount)
{
	std::vector<Entry> result;
	for ( size_t i = 0; i < amount; i++)
	{
		result.push_back(entryGenerator());
	}
	assert(result.size() == amount);
	return result;
}
