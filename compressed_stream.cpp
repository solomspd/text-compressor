//
// Created by solomspd on 04/11/2019.
//

#include "compressed_stream.h"

compressed_stream::compressed_stream(){
    char *new_char = new char;
    *new_char = int(0);
    top = new_char;
    tot_length = 0;
}

compressed_stream::~compressed_stream() {
    while (!stream.empty()) {
        char *temp = stream[stream.size() - 1];
        delete temp;
        stream.pop_back();
    }
}

bool compressed_stream::add(int compressed_char, int length) {
    int remaining_in_byte = tot_length % cell_size;
    tot_length += length;
    while (length > 0) {
        if (remaining_in_byte == 0) {
            char* new_char = new char;
            *new_char = int(0);
            stream.push_back(new_char);
            top = new_char;
            remaining_in_byte = cell_size;
        }
        *top = *top | ((compressed_char >> length--) & 1);
        remaining_in_byte--;
    }
}

bool compressed_stream::clear() {
    bool ret;
    ret = !stream.empty();
    stream.clear();
    return ret;
}

bool compressed_stream::is_empty() {
    return stream.empty();
}

unsigned long long compressed_stream::get_size() {
    return stream.size();
}
