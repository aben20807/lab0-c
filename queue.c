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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    if (q != NULL) {
        q->head = NULL;
        q->tail = NULL;
        q->size = 0;
    }
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if (q == NULL)
        return;

    while (q->size)
        q_remove_head(q, NULL, 0);
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
    if (q == NULL)
        goto fail;

    list_ele_t *newh;
    if ((newh = malloc(sizeof(list_ele_t))) == NULL)
        goto fail;
    newh->next = NULL;

    int len = strlen(s) + 1;
    if ((newh->value = malloc(len)) == NULL)
        goto fail_and_free;
    snprintf(newh->value, len, "%s", s);

    newh->next = q->head;
    q->head = newh;
    if (q->tail == NULL)
        q->tail = newh;
    q->size++;
    return true;

fail_and_free:
    free(newh);

fail:
    return false;
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
    if (q == NULL)
        goto fail;

    list_ele_t *newt;
    if ((newt = malloc(sizeof(list_ele_t))) == NULL)
        goto fail;
    newt->next = NULL;

    int len = strlen(s) + 1;
    if ((newt->value = malloc(len)) == NULL)
        goto fail_and_free;
    snprintf(newt->value, len, "%s", s);

    if (q->tail != NULL)
        q->tail->next = newt;
    q->tail = newt;
    if (q->head == NULL)
        q->head = newt;
    q->size++;
    return true;

fail_and_free:
    free(newt);

fail:
    return false;
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
    if (q == NULL || q->size == 0)
        return false;

    list_ele_t *rm = q->head;
    if (sp != NULL)
        snprintf(sp, bufsize, "%s", rm->value);

    q->head = q->head->next;
    if (q->head == NULL)
        q->tail = NULL;
    q->size--;
    free(rm->value);
    free(rm);
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    if (q == NULL)
        return 0;
    return q->size;
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
    if (q == NULL || q->size == 0)
        return;

    list_ele_t *cur = q->head;
    list_ele_t *nxt = cur->next;
    q->head = q->tail;
    q->tail = cur;
    q->tail->next = NULL;
    while (nxt != NULL) {
        list_ele_t *nnxt = nxt->next;
        nxt->next = cur;
        cur = nxt;
        nxt = nnxt;
    }
}
