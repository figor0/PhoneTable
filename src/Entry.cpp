#include <Entry.h>

bool operator>(const Entry &left, const Entry &right){
	bool equality = false;
	if (left.first_name == right.first_name){
		if (left.last_name == right.last_name){
			if (left.father_name == right.father_name){
				equality = left.phone > right.phone;
			} else{
				equality = left.father_name > right.father_name;
			}
		} else {
			equality = left.last_name > right.last_name;
		}
	} else {
		equality = left.first_name > right.first_name;
	}
	return equality;
}

bool operator==(const Entry &left, const Entry &right)
{
	return left.first_name == right.first_name &&
			left.last_name == right.last_name &&
			left.father_name == right.father_name &&
			left.phone == right.phone;
}

bool contain(const QString& str, const QString& sub_str)
{
	return str.contains(sub_str);
}

bool Entry::contain(const QString &filter) const{
	bool contain_flag =
			first_name.contains(filter) ||
			last_name.contains(filter) ||
			father_name.contains(filter) ||
			phone.contains(filter);
	return contain_flag;
}
