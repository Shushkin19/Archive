#include "huffman_tree.h"
#include<iostream>

huffman_tree::huffman_tree() {
	this->head = nullptr;
	this->freq = 0;
	
}


huffman_tree::huffman_tree(const huffman_tree& hf_t) {
	this->head = hf_t.head;
}

inline Letter huffman_tree::extract(std::vector<Letter>& data) {
	if (data.size() == 0) {
		Letter zero;
		zero.ch = 0;
		zero.freq = 0;
		return zero;
	}
	else {
		Letter l = data.back();
		data.pop_back();
		return l;
	}
}

inline void huffman_tree::push_sort(std::vector<Letter>& data, const Letter l) {
	data.push_back(l);
	int pos = data.size();
	if (pos == 1) {
		return;
	}
	pos--;
	
	while (data[pos] > data[pos-1]) {
		std::swap(data[pos], data[pos - 1]);
		if (pos == 1) {
			break;
		}
		pos--;
	}

}

void huffman_tree::insert(std::vector<Letter>& data) {

	while (data.size() > 1) {
		Letter tmp;
		tmp.left = new Letter;
		tmp.right = new Letter;
		*tmp.right = extract(data);
		*tmp.left = extract(data);
		tmp.freq = tmp.left->freq + tmp.right->freq;
		push_sort(data, tmp);

	}
	head = new huffman_tree;
	head->val = data.back();
}

void huffman_tree::show(huffman_tree* tr, Letter* l) {
	if (tr != nullptr) {
		std::cout << " frequency: " << tr->head->freq << "[][][] LETTER:  " << tr->head->val << std::endl;
		show(nullptr, tr->head->val.left);
		std::cout << "|||||||||||||||||||||||||||||||||||"<<std::endl;
		show(nullptr, tr->head->val.right);
	}
	else if (tr == nullptr && l != nullptr) {
		std::cout << *l << std::endl;
		show(nullptr, l->left);
		std::cout << "=======================\n";
		show(nullptr, l->right);
	}
	else {
		return;
	}
}

void huffman_tree::create_bytes(huffman_tree* tr, Letter* l) {

	if (tr != nullptr) {
		
		tr->head->val.left->byte_code = "0";
		tr->head->val.right->byte_code = "1";
		create_bytes(nullptr, tr->head->val.left);
		create_bytes(nullptr, tr->head->val.right);
	}
	else if (tr == nullptr && l != nullptr) {
		if (l->left != nullptr) {
			l->left->byte_code = l->byte_code + "0";

		}
		if (l->right != nullptr) {

			l->right->byte_code = l->byte_code + "1";

		}
		create_bytes(nullptr, l->left);
		create_bytes(nullptr, l->right);
	}
	else {
		return;
	}
}

void huffman_tree::get_bytecode(huffman_tree* tr, Letter* l, std::unordered_map<unsigned char, Letter>& code_book){

	if (tr != nullptr) {

		if (tr->head->val.left->is_char == true) {
			code_book.emplace(std::make_pair(tr->head->val.left->ch, *tr->head->val.left));
		}

		if (tr->head->val.right->is_char == true) {
			code_book.emplace(std::make_pair(tr->head->val.right->ch, *tr->head->val.right));
		}


		get_bytecode(nullptr, tr->head->val.left, code_book);
		get_bytecode(nullptr, tr->head->val.right, code_book);
	}



	else if (tr == nullptr && l != nullptr) {

		if (l->left != nullptr) {
			if (l->left->is_char == true) {
				code_book.emplace(std::make_pair(l->left->ch, *l->left));
			}
		}

		if (l->right != nullptr) {
			if (l->right->is_char == true) {
				code_book.emplace(std::make_pair(l->right->ch, *l->right));
			}
		}

		get_bytecode(nullptr, l->left, code_book);
		get_bytecode(nullptr, l->right, code_book);
	}
	else {
		return;
	}

}





