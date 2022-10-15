#pragma once
#include"Letter.h"
#include<vector>
#include<unordered_map>



class huffman_tree
{
	huffman_tree* head;
	int freq;
	Letter val;
	

	Letter extract(std::vector<Letter>& data);
	void push_sort(std::vector<Letter>& data, const Letter l);
public:
	huffman_tree();
	huffman_tree(const huffman_tree& hf_t);
	void insert(std::vector<Letter>& data);
	void show(huffman_tree* tr, Letter* l);
	void create_bytes(huffman_tree* tree,Letter* l);
	


	void get_bytecode(huffman_tree* tree, Letter* l, std::unordered_map<unsigned char, Letter>& code_book);

};





