#pragma once
#include <QString>
#include <Entry.h>
#include <vector>

QString wordGenerator(const size_t word_size);

QString numberGenerator();

Entry entryGenerator();

std::vector<Entry> entriesGenerator(size_t amount);
