//
// Created by solomspd on 05/11/2019.
//

#ifndef BONUS_COMPRESS_H
#define BONUS_COMPRESS_H

#include <utility>
#include <string>
#include <map>

#include "huff_tree.h"
#include "compressed_stream.h"

const int char_count = 255;

class compress {
	private:
		compressed_stream out_stream;
		huff_tree *tree;
		std::pair<unsigned long long, char> tally[char_count];
		std::map<char, std::pair<int, int>> opti; //first int depth, second sequence;

	public:
		compress();
		compress(const std::string &in_file);
		~compress();
		bool set_up(const std::string &in_file); // TODO consider finding frequency of more than just letters such as common suffixes "tion" and "er" and "aaaaaaaaaa"
		void short_hand(huff_tree *in, unsigned int depth, unsigned int node);
		void build_tree(); // TODO consider adding nodes for multiplications of characters for more effieicient recurring characters
		bool create_stream(const std::string &in_file);
		void compress_tree(huff_tree *in); // TODO try to make constant and become reference
		bool create_file(const std::string &in_file);
};

#endif //BONUS_COMPRESS_H
