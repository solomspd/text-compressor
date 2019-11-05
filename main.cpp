#include <iostream>
#include <string>
#include <fstream>
#include <memory>
#include <algorithm>
#include <queue>
#include <map>
#include "compressed_stream.h"

#define cannot_open_file 404
#define success 0

const int char_count = 256;

struct node {
    unsigned long long freq;
    int val;
    node *left, *right;
};

void search_tree (node *, unsigned int, unsigned int, std::map<char, std::pair<int, int>> &);

int main(int argc, char **argv) {

    if (!argc) {
        std::cout << "manual" << std::endl;
    }

    std::string file_name;
    std::ifstream in;

    //// create trie tree

    /// get tally
    std::pair<unsigned long long, char> tally[char_count];

    for (int i = 0; i < char_count; i++) {
        tally[i].first = 0;
        tally[i].second = char(i);
    }

    in.open(file_name.c_str());

    if (!in.is_open()) {
        return cannot_open_file;
    }

    while (!in.eof()) {
        char temp;
        in.get(temp);
        tally[int(temp)].first++;
    }
    in.close();

    //// construct tree

    std::sort(std::begin(tally), std::end(tally));

    std::priority_queue<node *> tree_builder;


    for (auto i: tally) {
        node *new_node = new node;
        new_node->val = i.second;
        new_node->freq = i.first;
        tree_builder.push(new_node);
    }

    while (tree_builder.size() > 1) {
        node *comb1, *comb2;
        comb1 = tree_builder.top();
        tree_builder.pop();
        comb2 = tree_builder.top();
        tree_builder.pop();

        node *new_node = new node;
        new_node->freq = comb1->freq + comb2->freq;
        new_node->val = -1;
        new_node->right = comb1;
        new_node->left = comb2;

        tree_builder.push(new_node);
    }

    node* tree = tree_builder.top();
    tree_builder.pop();


    in.open(file_name.c_str());

    if (!in.is_open()) {
        return cannot_open_file;
    }

    compressed_stream out;

    std::map<char, std::pair<int, int>> opti;

    search_tree (tree, 0, 0, opti);



    while (!in.eof()) {
        char temp;
        in.get(temp);
        out.add(opti[temp].first, opti[temp].second);
    }

    return success;
}

void search_tree (node *in, unsigned int depth, unsigned int node, std::map<char, std::pair<int, int>> &opti) {
    if (in->val != -1) {
        opti[in->val] = std::pair<int, int>(depth, node);
    }

    if (in->right != nullptr) {
        search_tree(in->right, ++depth, (node << 1) | 1, opti);
    }

    if (in->left != nullptr) {
        search_tree(in->left, depth, node << 1, opti);
    }

}