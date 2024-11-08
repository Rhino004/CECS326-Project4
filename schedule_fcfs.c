/**
 * FCFS scheduling
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "task.h"
#include "list.h"
#include "cpu.h"
#include "schedulers.h"

struct node *head = NULL;

void schedule()
{
    // Pointer holds current task node in list
    struct node *current = head;

    // Loop through task list
    while (current != NULL)
    {
        // Get task from current node
        Task *task = current->task;

        // Run task with run function from CPU.c
        run(task, task->burst);

        // Cycles next task
        current = current->next;
    }
}

void add(char *name, int priority, int burst)
{
    Task *new_task = malloc(sizeof(Task));
    if (new_task == NULL)
    {
        return;
    }
    new_task->name = strdup(name);
    new_task->priority = priority;
    new_task->burst = burst;

    struct node *new_node = malloc(sizeof(struct node));
    if (new_node == NULL)
    {
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
