#pragma once

// A structure for storing a value in a node.
typedef struct NodeValue {
    const char* key;
    const char* value;
} NodeValue;

// Tree Node.
typedef struct Node Node;

// Creates a tree.
Node* createTree(const char* key, const char* value, bool* errorCode);

// Delete a tree.
void deleteTree(Node** root);

// Searches for a value by key.
const char* searchByKey(Node* node, const char* key);

// Adds a new value to the tree (if such a key exists, the value for the old key will be deleted).
Node* addNode(Node* node, const char* key, const char* value, bool* isHeightChanged, bool* errorCode);

// Deletes a node by key.
Node* deleteNode(Node* node, const char* key, bool* isHeightChanged, bool* errorCode);

// Creates a value that can be stored in the node.
NodeValue createNodeValue(const char* key, const char* value);
