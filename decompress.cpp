//
// Created by solomspd on 05/11/2019.
//

#include "decompress.h"
#include "compressed_stream.h"

decompress::decompress() {
	pos = 0;
}

decompress::decompress(const std::string &in_file) {

}

decompress::~decompress() {

}

bool decompress::open_file(const std::string &in_file) {
	in_stream.open(in_file.c_str());
	return in_stream.is_open();
}

void decompress::rebuild_tree(huff_tree *in) {
	if (get_bit()) { in = new huff_tree(get_char()); }
	bool still_can;
	if (still_can) {
		rebuild_tree(in->get_right());
		rebuild_tree(in->get_left());
		in = new huff_tree(-1);
	}
}

void decompress::decompress_tree() {

}

void decompress::decompress_txt(const std::string &out_file) {
	std::ofstream out_stream(out_file.c_str());
	while (!in_stream.eof()) {
		unsigned int cur;
		char res;
		huff_tree *cursor = tree;
		while (cursor->get_val() != 0) {
			if (get_bit()) {
				cursor = cursor->get_right();
			} else {
				cursor = cursor->get_left();
			}
		}
		out_stream.put(cursor->get_val());
	}
	out_stream.close();
}

char decompress::get_char() {
	char ret = int(0);
	for (int i = cell_size - 1; i >= 0; i--) {
		ret |= get_bit() << i;
	}
	return ret;
}

bool decompress::get_bit() {
	if (pos == cell_size) {
		pos = 0;
		in_stream.get(cur_char);
	}
	return (cur_char >> (cell_size - pos++)) & 1;
}
