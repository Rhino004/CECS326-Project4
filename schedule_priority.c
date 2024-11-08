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

struct node *head = NULL;

Task *pickNextTask() {
  struct node *current = head;
  Task *highestPriorityTask = NULL;

  // Find task with highest priority
  while (current != NULL) {
    Task *task = current->task;
    if (highestPriorityTask == NULL || task -> priority > highestPriorityTask -> priority) {
        highestPriorityTask = task;
    }
    
    current = current -> next;
  }
  
  return highestPriorityTask;
}

void schedule() {
  while (head != NULL) {
    Task *task = pickNextTask(head);

    // Complete task 
    run(task, task -> burst);

    // Remove task from list
    delete(&head, task);
  }
}
