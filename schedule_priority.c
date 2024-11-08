/*
 * Priority scheduling
 */
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

#include "task.h"
#include "list.h"
#include "cpu.h"

 void schedule(struct node *head) {
    while (head != NULL) {
        struct node *current = head;
        struct node *highestPriorityNode = NULL;

        // Find the task with the highest priority
        while (current != NULL) {
            if (highestPriorityNode == NULL || current -> task -> lpriority > highestPriorityNode -> task->priority) {
                highestPriorityNode = current;
            }
            current = current -> next;
        }

        if (highestPriorityNode != NULL) {
            Task *task = highestPriorityNode -> task;

            // Run the selected task
            run(task, task -> burst);

            // Remove the completed task from the list
            delete(&head, task);
        }
    }
}
