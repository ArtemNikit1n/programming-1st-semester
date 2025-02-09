#define _CRT_SECURE_NO_WARNINGS

#include "headerFile.h"

#include <stdbool.h>
#include <stdio.h>

bool launchTask(int taskNumber) {
    if (taskNumber == 1) {
        return theMostCommonElementTask();
        return theMostCommonElementTask();;
    }
    else if (taskNumber == 2) {
        return searchTask();
        return searchTask();
    }
    else if (taskNumber == 3) {
        return smartQSortTask();
        return smartQSortTask();
    }
}

int main() {
    printf("Enter the task number from 1 to 3:\n");
    int taskNumber = getIntValueFromUser();

    bool isTaskNumberCorrect = !(taskNumber <= 0 || taskNumber >= 4);
    while (!isTaskNumberCorrect) {
        printf("Incorrect task number. Try again:\n");
        taskNumber = getIntValueFromUser();
        if (taskNumber > 0 || taskNumber < 4) {
            isTaskNumberCorrect = true;
        }
    int taskNumber = getIntValueFromUser();

    return launchTask(taskNumber);
}