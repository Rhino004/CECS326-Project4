/*
 * Priority scheduling
 */
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include "schedulers.h"
#include "task.h"
#include "list.h"
#include "cpu.h"

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

struct node *head = NULL;

void add(char *name, int priority, int burst)
{
    Task *new_task = malloc(sizeof(Task));
    if (new_task == NULL)
    {
        fprintf(stderr, "Memory allocation failed for new task.\n");
        return;
    }
    new_task->name = strdup(name);
    new_task->priority = priority;
    new_task->burst = burst;

    struct node *new_node = malloc(sizeof(struct node));
    if (new_node == NULL)
    {
        fprintf(stderr, "Memory allocation failed for new node.\n");
        free(new_task);
        return;
    }
    new_node->task = new_task;
    new_node->next = NULL;

    if (head == NULL)
    {
        head = new_node;
    }
    else
    {
        struct node *current = head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = new_node;
    }
}