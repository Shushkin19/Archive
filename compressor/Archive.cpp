#include"Archive.h"
#include<exception>
#include<fstream>
#include<algorithm>
#include<iostream>
#include"huffman_tree.h"


using namespace std;


archive::archive(std::string file_name) {
	data.resize(256);
	file = file_name;
	base_data_size = 0;
}

archive::~archive() {
	data.clear();
}

void archive::show_for_debug() {
	for (int i = 0; i < data.size(); i++) {
		std::cout << i << "  <<||>>  " << data[i].ch << " - " << data[i].freq <<" \\/ bytecode: "<<data[i].byte_code<< std::endl;
	}
}

void archive::read_file_to_data() {


	std::fstream file_to_compress;

	file_to_compress.open(file, std::ios::binary | std::ios::in);

	if (file_to_compress.is_open() == 0) {
		std::cout << "file not opened!";
		exit(-1);
	}
	
	unsigned char c;
	
	while (!file_to_compress.eof()) {
		c = file_to_compress.get();
		data[c].ch = c;
		data[c].freq++;
		data[c].is_char = true;
		++base_data_size;
	}

	sort_data();
	file_to_compress.close();
}

void archive::sort_data() {
	std::sort(data.begin(), data.end(),std::greater<>());
	if (data.size() < 1) {
		exit(-1);
	}
	int tmp = data.size() - 1;
	while (data[tmp].freq == 0) {
		data.pop_back();
		tmp--;
	}
}

int archive::size_file_in_byte(std::string s)
{
	std::fstream fl;
	fl.open(s, std::ios::binary | std::ios::in);
	if (fl.is_open() == 0) {
		//не открыт ,  ошибка
	}

	long count_byte = 0;

	while (!fl.eof()) {
		fl.get();
		++count_byte;
	}
	return count_byte;
}

void archive::show_code_book() {
	for (auto it = code_book.begin(); it != code_book.end(); ++it) {
		std::cout << it->first << it->second << std::endl;
	}
}

unsigned char archive::make_byte(std::vector<bool> bits,int start) {
	//byte::put_bit();
	//byte::get_byte();
	int res = 0;
	for (int i = 0; i < 8; i++) {
		if (bits[start+i] == 1) {
			res += std::pow(2, 8 - i - 1);
		}
	}
	return res;
}

void archive::write_code_book_in_file() {
	std::fstream fl;
	fl.open(file_compressed, std::ios::binary | std::ios::out );
	if (fl.is_open() == 0) {
		//bad!
	}
	file_type.assign(file, file.find('.'));
	fl << file_type;
	for (auto it = code_book.begin(); it != code_book.end(); ++it) {
		fl << "/" << it->first << "." << it->second.freq;
	}
	fl << char(19);
	fl.close();

}

void archive::rebuild_file_from_code_book() {
	std::fstream filecomp;

	filecomp.open(file, std::ios::binary | std::ios::in);

	std::fstream compress_file;

	std::string name;
	name = file.substr(0, file.find('.'));
	file_compressed = name + ".shuco";

	compress_file.open(file_compressed, std::ios::binary | std::ios::out | std::ios::app);
	if (compress_file.is_open() == 0) {
		std::cout << "file compress not opened\n";
		exit(-1);
	}


	if (filecomp.is_open() == 0) {
		std::cout << "file not opened!";
		exit(-1);
	}

	write_code_book_in_file();

	unsigned char byte = 0;
	unsigned char tmpbyte;
	std::string tmp;	
	int count = 0;
	while (!filecomp.eof()) {
		auto it = code_book.find(filecomp.get());
		for (int i = 0; i < it->second.byte_code.size(); ++i) {
//			int b = (it->second.byte_code[i]);
	
			int bit = it->second.byte_code[i] - '0';
			
			if (bit == 1) {
				byte = byte << 1;
				byte |= 1;
			}
			else {
				byte <<= 1;
			}
			

//			byte << (it->second.byte_code[i] % 2);
			++count;
			if (count == 8) {
				compress_file << byte;
				byte = 0;
				count = 0;
			}
		}
	}
	compress_file.close();
}


void archive::compress_file() {

	huffman_tree h_tree;

	read_file_to_data();

	//show_for_debug();

	h_tree.insert(data);

	h_tree.create_bytes(&h_tree, nullptr);
	//h_tree.show(&h_tree, nullptr);

	h_tree.get_bytecode(&h_tree, nullptr, code_book);
//	show_code_book();

	rebuild_file_from_code_book();

	std::cout << "\n Based size: " << base_data_size << " Byte \n Compressed size: " << size_file_in_byte(file_compressed) << " Byte\n";
	
	
}


inline std::string archive::to_bit_str(unsigned char ch) {
	unsigned char bit = 1;
	int tmp;
	string ans;
	for (int i = 0; i < 8; i++) {
		tmp = ch & bit;
		if (tmp == bit) {
			ans += "1";
			ch ^= bit;
		}
		else {
			ans += "0";
		}

		bit <<= 1;
	}
	string rev(ans.rbegin(), ans.rend());
	return rev;

}

void archive::fill_data() {
	fstream fl;
	fl.open(file, ios::binary | ios::in);
	if (fl.is_open() == 0) {
		//pook!
		cout << "xexe";
	}
	size_t tmp = fl.get();
	
	std::string tempint;
	while (tmp != '/') {
		file_type += tmp;
		tmp = fl.get();
	}
	while (tmp != 19) {
		tempint.clear();
		if (tmp == '/') {
			unsigned char c = fl.get();
			tmp = fl.get();
			if (tmp == '.') {
				Letter l;
				tmp = fl.get();
				while (tmp >= '0' && tmp <= '9') {
					tempint += tmp;
					tmp = fl.get();
				}
				

				l.freq = std::stoi(tempint);
				l.ch = c;
				l.is_char = 1;
				data[c] = l;


				
			}
		}

	}

	pos = fl.tellg();
	sort_data();
	fl.close();
	//show_code_book();

}

void archive::create_byte_book() {
	int n = code_book.size();
	for (auto it = code_book.begin(); it != code_book.end(); ++it) {
		byte_book.emplace(make_pair(it->second.byte_code, it->second));
	}
}

void archive::create_decompress_file() {
	fstream fl;
	fl.open(file, ios::binary | ios::app | ios::in);
	if (fl.is_open() == 0) {
		//bad!
	}

	std::string name;
	name = file.substr(0, file.find('.'));
	name = "decomp_" + name + file_type;

	fstream file_decomp;
	file_decomp.open(name, ios::binary | ios::out);
	if (file_decomp.is_open() == 0) {
		cout << "bsd";
	}


	create_byte_book();
	string tmp;
	string byte;
	unsigned char bit = 128;
	unsigned char ch;
	int temp;
	unordered_map<string, Letter>::iterator srch;
	
	fl.seekg(pos);
	

	while (!fl.eof()) {
		ch = fl.get();
		byte = to_bit_str(ch);
		for (int i = 0; i < byte.size(); i++) {
			tmp += byte[i];
			srch = byte_book.find(tmp);
			if (srch != byte_book.end()) {
				bit = 128;
				file_decomp << srch->second.ch;
				tmp.clear();
			}
		}
	}
	file_decomp.close();
	fl.close();
}


void archive::decompress_file() {
	
	fill_data();

	huffman_tree h_tree;

	h_tree.insert(data);

	h_tree.create_bytes(&h_tree, nullptr);
	//h_tree.show(&h_tree, nullptr);

	h_tree.get_bytecode(&h_tree, nullptr, code_book);
	//show_code_book();
	create_decompress_file();
	

	//show_for_debug();
}
