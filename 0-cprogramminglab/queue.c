/* 
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q =  malloc(sizeof(queue_t));
    
    if (!q) {
      return NULL;
    }

    q->elem_count = 0;
    q->head = NULL;
    q->tail = NULL;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if (!q) {
      return;
    }

    list_ele_t *cur = q->head;
    while (cur) {
      list_ele_t *next = cur->next;
      free(cur->value);
      free(cur);
      cur = next;
    } 

    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    if (!q) {
      return false;
    }

    list_ele_t *newh;
    newh = malloc(sizeof(list_ele_t));

    if (!newh) {
      return false;
    }

    char *t = malloc((strlen(s) + 1) * sizeof(char));
    if (!t) {
      free(newh);
      return false;
    }
    strcpy(t, s);
    newh->value = t;

    newh->next = q->head;
    if (!q->tail) {
      q->tail = newh;
    }
    q->head = newh;

    q->elem_count++;
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    if (!q) {
      return false;
    }

    list_ele_t *newt;
    newt = malloc(sizeof(list_ele_t));

    if (!newt) {
      return false;
    }

    char *t = malloc((strlen(s) + 1) * sizeof(char));
    if (!t) {
      free(newt);
      return false;
    }
    strcpy(t, s);
    newt->value = t;
    newt->next = NULL;

    if (!q->head) {
      q->head = newt;
      q->head->next = NULL;
    }
    if (q->tail) {
      q->tail->next = newt;
    }
    q->tail = newt;

    q->elem_count++;
    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    if (q_size(q) == 0 || !sp) {
      return false;
    }

    list_ele_t *head_elem = q->head;
    size_t copied_size = bufsize - 1;
    if (strlen(head_elem->value) * sizeof(char) < bufsize - 1) {
      copied_size = strlen(head_elem->value) * sizeof(char);
    }
    strncpy(sp, head_elem->value, copied_size);
    sp[copied_size] = '\0';

    if (q->head == q->tail) {
      q->tail = NULL;
    }
    q->head = q->head->next;
    free(head_elem->value);
    free(head_elem);

    q->elem_count--;
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    if (!q) {
      return 0;
    }

    return q->elem_count;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    if (q_size(q) <= 1) {
      return;
    }

    list_ele_t *prev = NULL;
    list_ele_t *cur = q->head;
    list_ele_t *next = NULL;

    while(cur) {
      next = cur->next;
      cur->next = prev;
      prev = cur;
      cur = next;
    }

    list_ele_t *tmp = q->head;
    q->head = q->tail;
    q->tail = tmp;
}

