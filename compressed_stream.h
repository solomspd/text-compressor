//
// Created by solomspd on 04/11/2019.
//

#ifndef BONUS_COMPRESSED_STREAM_H
#define BONUS_COMPRESSED_STREAM_H

#include <vector>

class compressed_stream {
private:
    std::vector<char*> stream;
    char *top;
    unsigned long long tot_length;
    const int cell_size = 8;

public:
    compressed_stream();
    ~compressed_stream();
    bool add(int, int);
    bool is_empty();
    bool clear();
    unsigned long long get_size();
};


#endif //BONUS_COMPRESSED_STREAM_H
