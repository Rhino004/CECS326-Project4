/*
 * Priority scheduling
 */
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

#include "task.h"
#include "list.h"
#include "cpu.h"
#include "schedulers.h"


Task *pickNextTask() {
  struct node *current = head;
  Task *highestPriorityTask = NULL;

  // Find the task with the highest priority
  while (current != NULL) {
    Task *task = current->task;
    if (highestPriorityTask == NULL || task -> priority > highestPriorityTask -> priority) {
        highestPriorityTask = task;
    }
    
    current = current -> next;
  }
  
  return highestPriorityTask;
}

void schedule(struct node *head) {
  while (head != NULL) {
    Task *task = pickNextTask();

    // Complete task 
    run(task, task -> burst);

    // Remove task from list
    delete(&head, task);
  }
}
