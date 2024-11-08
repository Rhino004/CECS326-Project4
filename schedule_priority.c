/*
 * Priority scheduling
 */
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

#include "task.h"
#include "list.h"
#include "cpu.h"
#include "scheduler.h"

 void schedule(struct node *head) {
    while (head != NULL) {
        struct node *current = head;
        struct node *highestPriorityNode = NULL;

        // Find task with highest priority
        while (current != NULL) {
            if (highestPriorityNode == NULL || current -> task -> priority > highestPriorityNode -> task->priority) {
                highestPriorityNode = current;
            }
            current = current -> next;
        }

        if (highestPriorityNode != NULL) {
            Task *task = highestPriorityNode -> task;

            // Run selected task
            run(task, task -> burst);

            // Remove completed task
            delete(&head, task);
        }
    }
}
