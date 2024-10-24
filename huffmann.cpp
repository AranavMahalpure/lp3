#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;

// A Huffman Tree node
struct HuffmanNode {
    char data;
    int freq;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char data, int freq) {
        left = right = nullptr;
        this->data = data;
        this->freq = freq;
    }
};

// Compare structure for the priority queue
struct Compare {
    bool operator()(HuffmanNode* left, HuffmanNode* right) {
        return left->freq > right->freq;
    }
};

// Function to print Huffman codes from the root of Huffman Tree
void printHuffmanCodes(HuffmanNode* root, string str) {
    if (!root) return;

    // If this is a leaf node, print character and its code
    if (!root->left && !root->right)
        cout << root->data << ": " << str << "\n";

    printHuffmanCodes(root->left, str + "0");
    printHuffmanCodes(root->right, str + "1");
}

// Main function to build Huffman Tree and print codes
void buildHuffmanTree(const unordered_map<char, int>& freqMap) {
    // Create a priority queue to store live nodes of the Huffman tree
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> pq;

    // Create a leaf node for each character and add it to the priority queue
    for (auto pair : freqMap) {
        pq.push(new HuffmanNode(pair.first, pair.second));
    }

    // Iterate until the size of the priority queue becomes 1
    while (pq.size() != 1) {
        // Extract the two nodes with the lowest frequency
        HuffmanNode* left = pq.top();
        pq.pop();
        HuffmanNode* right = pq.top();
        pq.pop();

        // Create a new internal node with the sum of the two nodes' frequencies
        int sum = left->freq + right->freq;
        HuffmanNode* node = new HuffmanNode('$', sum);

        // Set the two extracted nodes as left and right children of this node
        node->left = left;
        node->right = right;

        // Add this new node to the priority queue
        pq.push(node);
    }

    // The remaining node is the root of the Huffman Tree
    HuffmanNode* root = pq.top();

    // Print the Huffman codes
    printHuffmanCodes(root, "");
}

// Helper function to calculate frequencies of characters in the input string
unordered_map<char, int> calculateFrequencies(const string& data) {
    unordered_map<char, int> freqMap;
    for (char c : data) {
        freqMap[c]++;
    }
    return freqMap;
}

int main() {
    string data;
    cout << "Enter a string to encode: ";
    cin >> data;

    // Calculate frequency of each character
    unordered_map<char, int> freqMap = calculateFrequencies(data);

    // Build Huffman Tree and display the codes
    buildHuffmanTree(freqMap);

    return 0;
}


// Enter a string to encode: aabcc
// c: 0
// a: 10
// b: 11
