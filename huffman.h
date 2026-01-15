#pragma once
#include <cstdint>
#include <vector>
#include <string>
#include <queue>
#include <memory>
#include <unordered_map>

struct Node {
    uint8_t byte;
    uint64_t freq;
    Node *left;
    Node *right;

    Node(uint8_t b, uint64_t f) : byte(b), freq(f), left(nullptr), right(nullptr) {}
    Node(Node *l, Node *r) : byte(0), freq(l->freq + r->freq), left(l), right(r) {}
};

struct NodeCmp {
    bool operator()(Node *a, Node *b) const {
        return a->freq > b->freq; // min-heap
    }
};

Node* buildHuffmanTree(const std::vector<uint64_t> &freq);
void buildCodes(Node *root, std::string cur, std::string codes[256]);
void freeTree(Node *root);
