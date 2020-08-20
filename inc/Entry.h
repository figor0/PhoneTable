#pragma once
#include <QString>

struct Entry{
	QString first_name;
	QString last_name;
	QString father_name;
	QString phone;
	bool contain(const QString& filter) const;
	bool lastNameContain(const QString& filter) const{
		return last_name.contains(filter);
	}
};

bool operator==(const Entry& left, const Entry& right);

bool operator>(const Entry& left, const Entry& right);

