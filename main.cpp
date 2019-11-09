#include <iostream>
#include <string>

#include "compress.h"

#define cannot_open_file 404
#define cannot_create_file 405
#define success 0


const char compress_sym = 'c';
const char decompress_sym = 'd';

char mode_sym = 'c';

int main(int argc, char **argv) {

	if (!argc) {
		std::cout << "manual" << std::endl;
	}

	compress compressor;

	std::string in_file = "test.txt";
	std::string out_file = "compressed.txt";

	mode_sym = tolower(mode_sym);

	switch (mode_sym) {
		case compress_sym: {
			if (in_file.substr(in_file.length() - 5, 4) != ".txt") { std::cout << "Please enter a .txt file"; }
			if (!compressor.set_up(in_file)) { return cannot_open_file; }
			compressor.build_tree();
			if (!compressor.create_stream(in_file)) { return cannot_open_file; }
			if (!compressor.create_file(out_file)) { return cannot_create_file; }
			break;
		}

		case decompress_sym: {

			break;
		}

		default: {
			std::cout << "error 101 (invalid arguments)";
			break;
		}
	}

	return success;
}