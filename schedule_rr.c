/**
 * Round-robin scheduling
 */

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>

#include "task.h"
#include "list.h"
#include "cpu.h"
#include "schedulers.h"

struct node *head = NULL;

void schedule() {
    while (head != NULL) {
        struct node *current = head;

        // Iterates task list
        while (current != NULL) {
            Task *task = current -> task;

            // Runs task for smaller time, either time quantum or remaining burst time
            int runTime = (task -> burst > QUANTUM) ? QUANTUM : task -> burst;
            run(task, runTime);

            // Updates remaining burst time
            task -> burst -= runTime;

            // Checks task is completed
            if (task -> burst <= 0) {
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

void add(char *name, int priority, int burst) {
    Task *new_task = malloc(sizeof(Task));
    
    if (new_task == NULL) { return; }
    
    new_task -> name = strdup(name);
    new_task -> priority = priority;
    new_task -> burst = burst;

    struct node *new_node = malloc(sizeof(struct node));

    if (new_node == NULL) {
        free(new_task);
        return;
    }

    new_node -> task = new_task;
    new_node -> next = NULL;

    if (head == NULL) { head = new_node; }
    else {
        struct node *current = head;
        while (current -> next != NULL) { current = current -> next; }
        current -> next = new_node;
    }
}
