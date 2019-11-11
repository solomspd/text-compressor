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
		double L;

	public:
		compress();
		compress(const std::string &in_file);
		~compress();
		bool set_up(const std::string &in_file);
		void short_hand(huff_tree *in, unsigned int depth, unsigned int node);
		void build_tree();
		bool create_stream(const std::string &in_file);
		void compress_tree(huff_tree *in);
		bool create_file(const std::string &in_file);
		double get_ratio();
		double get_eff();
};

#endif //BONUS_COMPRESS_H
