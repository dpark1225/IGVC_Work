#include <endian.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_s {
  void *data;
  struct node_s *prev;
  struct node_s *next;
} node_t;

typedef struct list_s {
  node_t *head;
  node_t *tail;
  size_t size;
} list_t;

// functions to implement
list_t *list_alloc(void);
void list_free(list_t *list, void (*free_data)(void *data));
int list_prepend(list_t *list, void *val);
int list_append(list_t *list, void *val);
int list_insert(list_t *list, void *val, size_t pos);
int list_rm(list_t *list, void **val, size_t pos);
int list_set(list_t *list, void *val, size_t pos);
int list_get(list_t *list, void **val, size_t pos);
void printNodes(list_t *list);

list_t *list_alloc(void) {
  list_t *new = (list_t *)malloc(sizeof(list_t));
  if (new == NULL) {
    return NULL;
  }

  new->head = NULL;
  new->tail = NULL;
  new->size = 0;
  return new;
}

void list_free(list_t *list, void (*free_data)(void *data)) {
  if (list == NULL) {
    return;
  }
  node_t *temp = list->head;
  while (temp != NULL) {
    node_t *next = temp->next;
    if ((free_data != NULL) && (temp->data != NULL)) {
      free_data(temp->data);
    }
    free(temp);
    temp = next;
  }

  free(list);
}

int list_prepend(list_t *list, void *val) {
  if (list == NULL) {
    return 1;
  }
  node_t *prepend = ((node_t *)malloc(sizeof(node_t)));
  if (prepend == NULL) {
    return 1;
  }
  prepend->data = val;
  prepend->prev = NULL;
  prepend->next = list->head;
  if (list->head != NULL) {
    list->head->prev = prepend;
  } else {
    list->tail = prepend;
  }
  (list->size)++;

  list->head = prepend;

  return 0;
}

int list_append(list_t *list, void *val) {
  if (list == NULL) {
    return 1;
  }

  node_t *append = ((node_t *)malloc(sizeof(node_t)));
  if (append == NULL) {
    return 1;
  }
  append->data = val;
  append->prev = list->tail;
  append->next = NULL;
  if (list->tail != NULL) {
    list->tail->next = append;
  } else {
    list->head = append;
  }
  (list->size)++;

  list->tail = append;

  return 0;
}

int list_insert(list_t *list, void *val, size_t pos) {
  if (list == NULL || pos > list->size) {
    return 1;
  }
  if (pos == list->size) {
    return list_append(list, val);
  }
  if (pos == 0) {
    return list_prepend(list, val);
  }

  node_t *insert = ((node_t *)malloc(sizeof(node_t)));
  if (insert == NULL) {
    return 1;
  }
  node_t *temp = list->head;

  insert->data = val;
  size_t i = 0;
  while (i < pos - 1 && temp != NULL) {
    temp = temp->next;
    i++;
  }
  if (temp == NULL) {
    return 1;
  }

  insert->prev = temp;
  insert->next = temp->next;
  temp->next->prev = insert;
  temp->next = insert;

  (list->size)++;

  return 0;
}

int list_rm(list_t *list, void **val, size_t pos) {
  if (list == NULL || pos >= list->size) {
    return 1;
  }

  if (pos == 0) {
    node_t *temp = list->head;
    *val = temp->data;

    if (list->size == 1) { // nested if statement rip
      list->head = NULL;
      list->tail = NULL;

    } else {
      list->head = temp->next;
      temp->next->prev = NULL;
    }
    free(temp);
  } else if (pos == list->size - 1) {
    node_t *temp = list->tail;
    *val = temp->data;
    list->tail = temp->prev;
    list->tail->next = NULL;
    free(temp);

  } else {
    node_t *temp = list->head;
    size_t i = 0;

    while (i < pos) {
      temp = temp->next;
      i++;
    }

    *val = temp->data;
    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;
    free(temp);
  }
  (list->size)--;

  return 0;
}

int list_set(list_t *list, void *val, size_t pos) {
  if (list == NULL || pos > list->size) {

    return 1;
  }
  node_t *temp = list->head;
  size_t i = 0;
  while (i < pos) {
    temp = temp->next;
    i++;
  }
  temp->data = val;
  return 0;
}

int list_get(list_t *list, void **val, size_t pos) {
  if (list == NULL || pos > list->size) {

    return 1;
  }
  node_t *temp = list->head;
  size_t i = 0;
  while (i < pos) {
    temp = temp->next;
    i++;
  }
  *val = temp->data;
  return 0;
}

int main(void) {

  printf("TESTING LINKED LIST\n");

  list_t *list = list_alloc();
  int val = 1;
  int val2 = 2;
  printf("Allocation Succeeded\n");
  list_append(list, 0);
  printf("Appending Succeeded\n");
  list_insert(list, &val, 1);
  printf("Insert Succeeded\n");
  list_append(list, &val2);
  printf("Append 2 Succeeded\n");

  int *data = NULL;
  for (size_t i = 0; i < list->size; i++) {
    if (list_get(list, (void **)&data, i) != 0) {
      printf("Error retrieving data at index %ld\n", i);
      list_free(list, NULL);
      return 1;
    }
    printf("data at %ldth index: %d\n", i, *data);
  }

  list_free(list, NULL);
}
