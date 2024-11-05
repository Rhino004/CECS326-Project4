/*
 * Priority scheduling
 */
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

#include "task.h"
#include "list.h"
#include "cpu.h"

 void schedule() {
    while (head != NULL) {
        // Picks task with highest priority
        Task *task = pickNextTask();

        // Runs task full burst time
        run(task, task -> burst);

        // Removes completed task
        delete(&head, task);
    }
}
