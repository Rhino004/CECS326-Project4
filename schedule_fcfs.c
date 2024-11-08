/**
 * FCFS scheduling
 */

#include <stdlib.h>
#include <stdio.h>

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
