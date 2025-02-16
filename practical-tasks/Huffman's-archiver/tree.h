#pragma once

typedef struct {
    char value;
    int frequency;
} NodeValue;

typedef struct Node Node;

Node* createNode(NodeValue value, bool* errorCode);

void addLeftChild(Node* node, Node* child, bool* errorCode);

void addRightChild(Node* node, Node* child, bool* errorCode);

Node* getLeftChild(Node* node, bool* errorCode);

Node* getRightChild(Node* node, bool* errorCode);

NodeValue getValue(Node* node, bool* errorCode);

void setValue(Node* node, NodeValue value, bool* errorCode);

void disposeNode(Node* node);