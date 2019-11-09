//
// Created by solomspd on 05/11/2019.
//

#include "decompress.h"
#include "compressed_stream.h"

decompress::decompress() {
	pos = cell_size + 1;
}

decompress::decompress(const std::string &in_file) {

}

decompress::~decompress() {

}

bool decompress::open_file(const std::string &in_file) {
	in_stream.open(in_file.c_str());
	return in_stream.is_open();
}

huff_tree *decompress::rebuild_tree() {
	if (get_bit()) {
		return new huff_tree(get_char());
	}
	else {
		huff_tree *new_node = new huff_tree(0);
		new_node->bind_right(rebuild_tree());
		new_node->bind_left(rebuild_tree());
		return new_node;
	}
}

void decompress::decompress_txt(const std::string &out_file) {
	tree = rebuild_tree();

	std::ofstream out_stream(out_file.c_str());
	while (!in_stream.eof()) {
		unsigned int cur;
		char res;
		huff_tree *cursor = tree;
		while (cursor->get_val() == inside) {
			if (get_bit()) {
				cursor = cursor->get_right();
			} else {
				cursor = cursor->get_left();
			}
		}
		out_stream.put(cursor->get_val());
	}
	out_stream.close();
	in_stream.close();
}

char decompress::get_char() {
	char ret = int(0);
	for (int i = cell_size; i >= 0; i--) {
		ret |= get_bit() << i;
	}
	return ret;
}

bool decompress::get_bit() {
	if (pos == cell_size + 1) {
		pos = 0;
		in_stream.get(cur_char);
	}
	return (cur_char >> (cell_size - pos++)) & 1;
}
