//
// Created by solomspd on 05/11/2019.
//

#ifndef BONUS_HUFF_TREE_H
#define BONUS_HUFF_TREE_H

const int inside = 0;

class huff_tree {
    private:
        unsigned long long freq;
        char val;
        int sz;
        huff_tree *right, *left;

    public:
        huff_tree();
        huff_tree(huff_tree *r, huff_tree *l);
        huff_tree(char in_val);
        ~huff_tree();
        bool insert_right(huff_tree* in);
        bool insert_left(huff_tree* in);
        void inc_freq(int in = 1);
        void set_val(int in);
        int get_val();
        int get_freq();
        huff_tree *get_right();
        huff_tree *get_left();
        int combine(huff_tree *right, huff_tree *left);
};


#endif //BONUS_HUFF_TREE_H
