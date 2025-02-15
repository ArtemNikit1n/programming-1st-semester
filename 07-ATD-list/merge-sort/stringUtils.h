#pragma once

// Returns values similar to strcmp, but works for null pointers. (NULL < any string).
int compareTwoString(const char* string1, const char* string2);