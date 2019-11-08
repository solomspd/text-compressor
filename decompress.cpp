//
// Created by solomspd on 05/11/2019.
//

#include "decompress.h"
#include "compressed_stream.h"

decompress::decompress() {

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

char decompress::get_equi(char) {

	return 0;
}

char decompress::get_char() {
	if (!pos) {
		in_stream.get(cur_char);
		return cur_char;
	}


}

char decompress::get_bit() {

}
