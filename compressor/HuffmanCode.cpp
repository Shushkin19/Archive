#include<iostream>
#include"Archive.h"
#include<map>
#include<fstream>
#include<queue>

int main() {
	//archive a("pingpong.txt");
	//archive a("cmex.mp4");
	//archive a("quetzal.jpg");
	//archive a("sample.txt");
	//archive a("huffman.txt");
	//a.compress_file();
	
	archive a("cmex.shuco");
	a.decompress_file();
	
	return 0;
}