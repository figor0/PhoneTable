#include <Validate.h>
#include <vector>

const QString digits{
	"1234567890"
};

bool nameValidator(const QString& name){
	return name.size() > 0;
}

bool phoneValidator(const QString &phone_str)
{
	// +79818764773
	bool right = false;
	if ( phone_str.size() == 7){
		for (const auto& item: phone_str){
			right = digits.contains(item);
		}
	} else if (phone_str.size() == 11){
		if (phone_str.at(0) != '+'){
			for (const auto& item: phone_str){
				right = digits.contains(item);
			}
		}
	} else if (phone_str.size() == 12){
		right = phone_str[0] == "+";
		for (int i = 1; i < phone_str.size(); i++){
			right = digits.contains(phone_str.at(i));
		}
	}
	return right;
}
