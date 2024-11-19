#pragma once

Node* buildTree(FILE* file, bool* errorCode);

void readingAPostfixEntry(const Node* node, bool* errorCode);