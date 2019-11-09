//
// Created by solomspd on 05/11/2019.
//

#include "huff_tree.h"

huff_tree::huff_tree() {
	freq = 0;
	val = 0;
	sz = 0;
	right = nullptr;
	left = nullptr;
}

huff_tree::huff_tree(huff_tree *r, huff_tree *l) { combine(r,l); }

huff_tree::huff_tree(char in_val) {
	val = in_val;
	freq = 0;
	right = nullptr;
	left = nullptr;
}

huff_tree::~huff_tree() {
	delete right;
	delete left;
}

bool huff_tree::insert_right(huff_tree *in) {
	right = in;
	sz++;
	return right == nullptr;
}

bool huff_tree::insert_left(huff_tree *in) {
	left = in;
	sz++;
	return left == nullptr;
}

void huff_tree::inc_freq(int in) { freq = in; }

void huff_tree::set_val(int in) { val = in; }

int huff_tree::get_val() { return val; }

int huff_tree::get_freq() { return freq; }

huff_tree *huff_tree::get_right() { return right; }

huff_tree *huff_tree::get_left() { return left; }

int huff_tree::combine(huff_tree *inr, huff_tree *inl) {
	val = inside;
	right = inr;
	left = inl;
	freq = right->freq + left->freq;
}
