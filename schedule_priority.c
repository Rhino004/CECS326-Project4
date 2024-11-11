/*
 * Priority scheduling
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
    Task *task = pickNextTask();

    // Complete task 
    run(task, task -> burst);

    // Remove task from list
    delete(&head, task);
  }
}

void add(char *name, int priority, int burst)
{
  Task *new_task = malloc(sizeof(Task));
  if (new_task == NULL) { return; }
  new_task->name = strdup(name);
  new_task->priority = priority;
  new_task->burst = burst;

  struct node *new_node = malloc(sizeof(struct node));

  if (new_node == NULL) {
    free(new_task);
    return;
  }

  new_node->task = new_task;
  new_node->next = NULL;

  if (head == NULL) { head = new_node; }
  else {
    struct node *current = head;
    while (current->next != NULL) {current = current->next;}
    current->next = new_node;
  }
}
