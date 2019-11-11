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
		std::ifstream in_stream;
		char cur_char;
		unsigned short pos;

	public:
		decompress();
		decompress(const std::string &in_file);
		~decompress();
		bool open_file(const std::string &in_file);
		huff_tree *rebuild_tree();
		char get_char();
		bool get_bit();
		void decompress_txt(const std::string &out_file);
};


#endif //BONUS_DECOMPRESS_H
