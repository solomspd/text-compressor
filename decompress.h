//
// Created by solomspd on 05/11/2019.
//

#ifndef BONUS_DECOMPRESS_H
#define BONUS_DECOMPRESS_H

#include <string>
#include <map>
#include <fstream>

#include "huff_tree.h"

class decompress {
	private:
		huff_tree *tree;
		std::map<unsigned int, char> opti;
		std::ifstream in_stream;
		char cur_char;
		unsigned short pos;

	public:
		decompress();
		decompress(const std::string &in_file);
		~decompress();
		bool open_file(const std::string &in_file);
		void rebuild_tree(huff_tree *in);
		char get_equi(char);
		char get_char();
		char get_bit();
};


#endif //BONUS_DECOMPRESS_H
