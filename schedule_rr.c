/**
 * Round-robin scheduling
 */

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

#include "task.h"
#include "list.h"
#include "cpu.h"
#include "schedulers.h"

#define TIME_QUANTUM 5

void schedule(struct node *head) {
    while (head != NULL) {
        struct node *current = head;

        // Iterates task list
        while (current != NULL) {
            Task *task = current -> task;

            // Runs task for smaller time, either time quantum or remaining burst time
            int runTime = (task -> burst > TIME_QUANTUM) ? TIME_QUANTUM : task -> burst;
            run(task, runTime);

            // Updates remaining burst time
            task -> burst -= runTime;

            // Checks task is completed
            if (task->burst <= 0) {
                // Removes completed task 
                struct node *nextNode = current -> next;
                delete(&head, task);
                current = nextNode;
            } else {
                // Cycles to next task list
                current = current -> next;
            }
        }
    }
}
