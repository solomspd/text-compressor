//
// Created by solomspd on 04/11/2019.
//

#ifndef BONUS_COMPRESSED_STREAM_H
#define BONUS_COMPRESSED_STREAM_H

#include <vector>

const int cell_size = 8;

class compressed_stream {
	private:
		std::vector<char*> stream;
		char *top;
		unsigned long long tot_length;

public:
    compressed_stream();
    ~compressed_stream();
    bool add(int compressed_char, int length);
    bool pop_front(char &in);
    bool is_empty();
    bool clear();
    unsigned long long get_size();
};


#endif //BONUS_COMPRESSED_STREAM_H
