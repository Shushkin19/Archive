

#include"Letter.h"
#include<vector>
#include<string>
#include<deque>
#include<unordered_map>

class archive  {

	std::vector<Letter> data;
	int base_data_size;
	std::string file;
	std::string file_compressed;
	std::string file_type;

	std::unordered_map<unsigned char, Letter> code_book;
	std::unordered_map<std::string, Letter> byte_book;
	int size_file_in_byte(std::string s);
	int pos;


	//compress
	void read_file_to_data();
	void sort_data();
	void show_for_debug();
	void show_code_book();
	void rebuild_file_from_code_book();
	unsigned char make_byte(std::vector<bool> bits, int start);
	void write_code_book_in_file();
	inline std::string to_bit_str(unsigned char ch);
	//decompress
	void fill_data();
	void create_decompress_file();
	void create_byte_book();
public:
	archive(std::string file_name);
	~archive();
	void compress_file();
	void decompress_file();

	//std::fstream get_compressed_file();

};


