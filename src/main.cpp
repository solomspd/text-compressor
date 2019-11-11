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

	do {
		char mode_sym;

		std::string source, dest;

		if ((argc != 4) | another_job) {
			std::cout << "Enter operation to complete compress/decompressed" << std::endl << "[c/d]";
			std::cin >> mode_sym;
			std::cout << "Enter source text file name (dont forget to include the .txt)" << std::endl;
			std::cin >> source;
			std::cout << "Enter destination text file name (dont forget to include the .txt)";
			std::cin >> dest;
		} else {
			mode_sym = argv[1][1];
			source = argv[2];
			dest = argv[3];
		}

		mode_sym = tolower(mode_sym);

		if (source.substr(source.length() - 4, 5) != ".txt" || dest.substr(dest.length() - 4, 5) != ".txt") {
			std::cout << "Please enter a .txt file";
			return invalid_file;
		}

		switch (mode_sym) {
			case compress_sym: {
				compress compressor;
				if (!compressor.set_up(source)) { return cannot_open_file; }
				compressor.build_tree();
				if (!compressor.create_stream(source)) { return cannot_open_file; }
				if (!compressor.create_file(dest)) { return cannot_create_file; }
				std::cout << std::endl << "Compression ratio: " << compressor.get_ratio() << std::endl << "Efficiency: " << compressor.get_eff() << std::endl;
				break;
			}

			case decompress_sym: {
				decompress decompressor;
				if (!decompressor.open_file(source)) { return cannot_open_file; }
				decompressor.decompress_txt(dest);
				std::cout << std::endl << "Done!" << std::endl << "Extracted to " << dest;
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