#include <endian.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_s {
  int data;
  struct node_s *next;
} node_t;

typedef struct list_s {
  node_t *head;
  node_t *tail;
  size_t size;
} list_t;
// functions to implement

list_t *list_alloc(void);
void list_free(list_t *list);
int list_prepend(list_t *list, int val);
int list_append(list_t *list, int val);
int list_insert(list_t *list, int val, size_t pos);
int list_rm(list_t *list, int *val, size_t pos);
int list_set(list_t *list, int val, size_t pos);
int list_get(list_t *list, int *val, size_t pos);
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

void list_free(list_t *list) {
  if (list == NULL) {
    return;
  }
  node_t *temp = list->head;
  while (temp != NULL) {
    node_t *next = temp->next;
    free(temp);
    temp = next;
  }

  free(list);
}

int list_prepend(list_t *list, int val) {

  node_t *prepend = (node_t *)malloc(sizeof(node_t));
  if (prepend == NULL) {
    return 1;
  }
  prepend->data = val;
  prepend->next = list->head;
  list->head = prepend;
  (list->size)++;
  if (list->size == 1) {
    list->tail = prepend;
  }
  return 0;
}

int list_append(list_t *list, int val) {
  node_t *append = (node_t *)malloc(sizeof(node_t));
  if (append == NULL) {
    return 1;
  }
  append->data = val;
  append->next = NULL;
  if (list->tail != NULL) {
    list->tail->next = append;
  }
  list->tail = append;
  (list->size)++;
  if (list->size == 1) {
    list->head = append;
  }
  return 0;
}

int list_insert(list_t *list, int val, size_t pos) {
  node_t *insert = (node_t *)malloc(sizeof(node_t));
  if (insert == NULL) {
    return 1;
  }
  if (pos > list->size) {
    printf("Invalid position");
    return 1;
  }
  node_t *temp = list->head;
  node_t *prev = NULL;

  insert->data = val;
  insert->next = NULL;

  if (pos == 0) {
    insert->next = list->head;
    list->head = insert;
    if (list->size == 0) {
      list->tail = insert;
    }
  } else {
    for (size_t i = 0; i < pos; i++) {
      prev = temp;
      temp = temp->next;
    }
    insert->next = temp;
    if (prev != NULL) {
      prev->next = insert;
    } else {
      list->head = insert;
    }
    if (temp == NULL) {
      list->tail = insert;
    }
  }
  (list->size)++;
  return 0;
}

int list_rm(list_t *list, int *val, size_t pos) {
  node_t *temp = list->head;
  node_t *prev = NULL;

  if (pos >= list->size) {
    return 1;
  }

  for (size_t i = 0; i < pos; i++) {
    prev = temp;
    temp = temp->next;
  }

  if (prev != NULL) {
    prev->next = temp->next;
  } else {
    list->head = temp->next;
  }

  if (temp == list->tail) {
    list->tail = prev;
  }

  if (val != NULL) {
    *val = temp->data;
  }

  free(temp);
  (list->size)--;

  return 0;
}

int list_set(list_t *list, int val, size_t pos) {
  node_t *temp = list->head;

  if (list->size == 0) {
    printf("list size is 0");
    return 1;
  }

  for (size_t i = 0; i < pos; i++) {
    temp = temp->next;
  }

  temp->data = val;
  return 0;
}

int list_get(list_t *list, int *val, size_t pos) {

  node_t *temp = list->head;
  if (list == NULL || list->size == 0 || list->head == NULL ||
      pos >= list->size) {
    printf("list size is 0");
    return 1;
  }

  for (size_t i = 0; i < pos; i++) {
    if (temp == NULL) {
      printf("Position out of bounds\n");
      return 1;
    }
    temp = temp->next;
  }
  if (temp == NULL) {
    printf("Position out of bounds??\n");
    return 1;
  }
  *val = temp->data;
  return 0;
}

int main(void) {

  printf("TESTING LINKED LIST\n");

  list_t *list = list_alloc();
  printf("Allocation Succeeded\n");
  list_append(list, 0);
  printf("Appending Succeeded\n");
  list_insert(list, 1, 1);
  printf("Insert Succeeded\n");
  list_append(list, 2);
  printf("Append 2 Succeeded\n");

  printNodes(list);

  list_free(list);
}

void printNodes(list_t *list) {
  int data;
  for (size_t i = 0; i < list->size; i++) {
    list_get(list, &data, i);
    printf("data at %ldth index: %d\n", i, data);
  }
}
