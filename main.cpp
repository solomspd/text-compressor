#include <iostream>
#include <string>

#include "compress.h"
#include "decompress.h"

#define cannot_open_file 404
#define cannot_create_file 405
#define invalid_file 102
#define success 0


const char compress_sym = 'c';
const char decompress_sym = 'd';

char mode_sym = 'd';

int main(int argc, char **argv) {

	if (!argc) {
		std::cout << "manual" << std::endl;
	}


	std::string original = "test.txt";
	std::string compressed = "compressed.txt";
	std::string decompressed = "decompressed.txt";

	mode_sym = tolower(mode_sym);

	switch (mode_sym) {
		case compress_sym: {
			compress compressor;
			if (original.substr(original.length() - 4, 5) != ".txt") {
				std::cout << "Please enter a .txt file";
				return invalid_file;
			}
			if (!compressor.set_up(original)) { return cannot_open_file; }
			compressor.build_tree();
			if (!compressor.create_stream(original)) { return cannot_open_file; }
			if (!compressor.create_file(compressed)) { return cannot_create_file; }
			break;
		}

		case decompress_sym: {
			decompress decompressor;
			if (!decompressor.open_file(compressed)) { return cannot_open_file; }
			decompressor.decompress_txt(decompressed);
			break;
		}

		default: {
			std::cout << "error 101 (invalid arguments)";
			break;
		}
	}

	return success;
}