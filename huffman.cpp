#include "huffman.h"

Node* buildHuffmanTree(const std::vector<uint64_t> &freq) {
    std::priority_queue<Node*, std::vector<Node*>, NodeCmp> pq;

    for (int i = 0; i < 256; ++i) {
        if (freq[i] > 0) {
            pq.push(new Node(static_cast<uint8_t>(i), freq[i]));
        }
    }

    if (pq.empty()) return nullptr; // empty file

    while (pq.size() > 1) {
        Node *a = pq.top(); pq.pop();
        Node *b = pq.top(); pq.pop();
        pq.push(new Node(a, b));
    }
    return pq.top();
}

void buildCodes(Node *root, std::string cur, std::string codes[256]) {
    if (!root->left && !root->right) {
        codes[root->byte] = cur.empty() ? "0" : cur; // handle single-symbol case
        return;
    }
    if (root->left)  buildCodes(root->left,  cur + "0", codes);
    if (root->right) buildCodes(root->right, cur + "1", codes);
}

void freeTree(Node *root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}
