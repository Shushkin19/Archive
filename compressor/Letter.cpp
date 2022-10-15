#include "Letter.h"

Letter::Letter() {
	this->ch = 0;
	this->freq = 0; 
	this->left = nullptr;
	this->right = nullptr;
	is_char = 0;
}

bool Letter::operator==(const Letter& l) {
	if (this->ch == l.ch) {
		return true;
	}
	else {
		return false;
	}
}

const bool Letter::operator<(const Letter& l) {
	if (this->freq < l.freq) {
		return true;
	}
	else {
		return false;
	}
}

const bool Letter::operator>(const Letter& l) {
	if (this->freq > l.freq) {
		return true;
	}
	else {
		return false;
	}
}

std::ostream& operator<<(std::ostream& ost, const Letter& l) {
	ost << "||| char: " << l.ch << " freq: " << l.freq<<" byte: ->> "<<l.byte_code;
	return ost;
}