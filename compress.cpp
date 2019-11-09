//
// Created by solomspd on 05/11/2019.
//

#include <fstream>
#include <algorithm>
#include <queue>
#include <functional>

#include "compress.h"

bool compare_tally(const std::pair<unsigned long long, char> &lhs, const std::pair<unsigned long long, char> &rhs) { return lhs.first > rhs.first; }

class compare_pq // TODO replace with in class comparison
{
	public:
		bool operator() (huff_tree *lhs, huff_tree *rhs)
		{
			bool ret = lhs->get_freq() > rhs->get_freq();
			return ret;
		}
};

compress::compress() {
	for (int i = 0; i < char_count; i++) {
		tally[i].first = 0;
		tally[i].second = char(i);
	}
}
compress::compress(const std::string &in_file) {
	set_up(in_file);
	build_tree();
	create_stream(in_file);
}

compress::~compress() {
	opti.clear();
	delete tree;
}

bool compress::set_up(const std::string &in_file) {
	std::ifstream in(in_file.c_str());

	if (!in.is_open()) { return false; }

	while (!in.eof()) {
		char temp;
		in.get(temp);
		tally[int(temp)].first++;
	}

	in.close();

	std::sort(std::begin(tally), std::end(tally), compare_tally);

	return true;
}

void compress::build_tree() {
	std::priority_queue<huff_tree *, std::vector<huff_tree *>, compare_pq> tree_builder;

	for (int i = 0; tally[i].first > 0 && i < char_count; i++) {
		auto *new_node = new huff_tree;
		new_node->set_val(tally[i].second);
		new_node->inc_freq(tally[i].first);
		tree_builder.push(new_node);
	}

	while (tree_builder.size() > 1) {
		huff_tree *comb1, *comb2;
		comb1 = tree_builder.top();
		tree_builder.pop();
		comb2 = tree_builder.top();
		tree_builder.pop();

		auto *new_node = new huff_tree(comb1, comb2);
		tree_builder.push(new_node);
	}

	tree = tree_builder.top();
	tree_builder.pop();

	compress_tree(tree);

	short_hand(tree, 0, 0);

}

void compress::short_hand(huff_tree *in, unsigned int depth, unsigned int node) {
	if (in->get_val() != 0) { opti[in->get_val()] = std::pair<int, int>(node, depth); }

	if (in->get_right() != nullptr) { short_hand(in->get_right(), ++depth, (node << 1) | 1); }
	if (in->get_left() != nullptr) { short_hand(in->get_left(), depth, node << 1); }
}

bool compress::create_stream(const std::string &in_file) {
	std::ifstream in(in_file.c_str());

	if (!in.is_open()) { return false; }

	while (!in.eof()) {
		char temp;
		in.get(temp);
		out_stream.add_char(opti[temp].first, opti[temp].second - 1);
	}

	in.close();

	return true;
}

void compress::compress_tree(huff_tree *in) {

	if (in->get_val() != inside) {
		out_stream.add_bit(1);
		out_stream.add_char(in->get_val(), cell_size);
	} else {
		out_stream.add_bit(0);
		if (in->get_right() != nullptr) { compress_tree(in->get_right()); }
		if (in->get_left() != nullptr) { compress_tree(in->get_left()); }
	}
}

bool compress::create_file(const std::string &in_file) {

	std::ofstream in(in_file.c_str());

	if (!in.is_open()) { return false; }

	char temp;
	while (!out_stream.pop_front(temp)) { in.put(temp); }

	in.close();

	return true;
}
