#pragma once
#include<ostream>
#include<string>

class Letter
{
public:

	unsigned char ch;
	long freq = 0;
	std::string byte_code;
	Letter* left;
	Letter* right;
	bool is_char;

	Letter();
	bool operator==(const Letter& l);
	const bool operator<(const Letter& l);
	const bool operator>(const Letter& l);
	friend std::ostream& operator<<(std::ostream& ost, const Letter& l);
};


std::ostream& operator<<(std::ostream& ost, const Letter& l);




