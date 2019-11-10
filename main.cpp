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


int main(int argc, char **argv) {
	bool another_job = false;

	std::string original = "test.txt";
	do {
		char mode_sym;

		if (argc != 3 | another_job) {
			std::cout << "Enter operation to complete compress/decompressed" << std::endl << "[c/d]";
			std::cin >> mode_sym;
			std::cout << "Enter text file name (dont forget to include the .txt)" << std::endl;
			std::cin >> original;
		} else {
			mode_sym = argv[1][1];
			original = argv[2];
		}

		mode_sym = tolower(mode_sym);

		if (original.substr(original.length() - 4, 5) != ".txt") {
			std::cout << "Please enter a .txt file";
			return invalid_file;
		}

		switch (mode_sym) {
			case compress_sym: {
				std::string compressed = "compressed_" + original;
				compress compressor;
				if (!compressor.set_up(original)) { return cannot_open_file; }
				compressor.build_tree();
				if (!compressor.create_stream(original)) { return cannot_open_file; }
				if (!compressor.create_file(compressed)) { return cannot_create_file; }
				std::cout << std::endl << "Done!";
				break;
			}

			case decompress_sym: {
				std::string decompressed = "decompressed_" + original.substr(11, original.length() - 1);
				decompress decompressor;
				if (!decompressor.open_file(original)) { return cannot_open_file; }
				decompressor.decompress_txt(decompressed);
				std::cout << std::endl << "Done!" << std::endl << "Extracted to " << decompressed;
				break;
			}

			default: {
				std::cout << "error 101 (invalid arguments)";
				break;
			}
		}
		std::cout << std::endl << std::endl << "Initiate another job?" << std::endl << "[y/n]";
		char temp;
		std::cin >> temp;
		another_job = tolower(temp) == 'y';
		if (another_job) {
			std::cout << std::endl << std::endl;
		}
	} while (another_job);

	return success;
}