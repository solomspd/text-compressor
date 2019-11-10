//
// Created by solomspd on 04/11/2019.
//

#include "compressed_stream.h"

compressed_stream::compressed_stream() {
	pos = 0;
	char *new_char = new char;
	*new_char = int(0);
	stream.push_back(new_char);
	top = new_char;
}

compressed_stream::~compressed_stream() {
	for (auto i: stream) {
		delete i;
	}
}

void compressed_stream::add_char(int compressed_char, int length) {
    while (length >= 0) { add_bit((compressed_char >> length--) & 1); }
}

void compressed_stream::add_bit(bool in) {
	*top |= in << (cell_size - pos++);
	if (pos == cell_size + 1) {
		pos = 0;
		char *new_char = new char;
		stream.push_back(new_char);
		top = new_char;
		*top = int(0);
	}
}

bool compressed_stream::clear() {
    bool ret;
    ret = !stream.empty();
    stream.clear();
    return ret;
}

bool compressed_stream::is_empty() { return stream.empty(); }
unsigned long long compressed_stream::get_size() { return stream.size(); }
bool compressed_stream::pop_front(char &in) {

	in = *stream[0];
	delete stream[0];
	stream.erase(stream.begin());

	return stream.empty();
}
