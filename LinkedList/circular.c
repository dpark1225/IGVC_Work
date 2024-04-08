#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct list_s {
  struct list_s *prev;
  struct list_s *next;
} list_t;

typedef struct data_s {
  int **matrix;
  size_t dim[2];
  list_t list;
} data_t;

// functions to implement
void list_init(list_t *list);
int list_prepend(list_t *list, list_t *node);
int list_append(list_t *list, list_t *node);
int list_insert(list_t *list, list_t *node, size_t pos);
int list_rm(list_t *list, size_t pos);
int list_set(list_t *list, list_t *node, size_t pos);
int list_get(list_t *list, list_t **node, size_t pos);

void list_init(list_t *list) {
  list->prev = list;
  list->next = list;
}

int list_prepend(list_t *list, list_t *node) {
  if (list == NULL || node == NULL) {
    return 1;
  }

  node->next = list->next;
  node->prev = list->prev;
  list->next->prev = node;
  list->next = node;

  return 0;
}

int list_append(list_t *list, list_t *node) {
  if (list == NULL || node == NULL) {
    return 1;
  }
  node->next = list;
  node->prev = list->prev;
  list->prev->next = node;
  list->prev = node;

  return 0;
}

int list_insert(list_t *list, list_t *node, size_t pos) {
  if (list == NULL || node || NULL) {
    return 1;
  }

  list_t *temp = list;
  size_t i = 0;
  while (i < pos && temp != list->prev) {
    temp = temp->next;
    i++;
  }
  node->next = temp->next;
  node->prev = temp->prev;
  temp->next->prev = node;
  temp->next = node;

  return 0;
}

int list_rm(list_t *list, size_t pos) {
  if (list == NULL) {
    return 1;
  }
  list_t *temp = list;
  size_t i = 0;
  while (i < pos && temp != list->prev) {
    temp = temp->next;
    i++;
  }

  if (temp == list) {
    return 1;
  }

  temp->prev->next = temp->next;
  temp->next->prev = temp->prev;
  free(temp);

  return 0;
}

int list_set(list_t *list, list_t *node, size_t pos) {
  if (list == NULL || node == NULL) {
    return 1;
  }

  list_t *temp = list;
  size_t i = 0;
  while (i < pos) {
    temp = temp->next;
    i++;
  }

  node->next = temp->next;
  node->prev = temp->prev;
  temp->prev->next = node;
  temp->next->prev = node;

  free(temp);

  return 0;
}

int list_get(list_t *list, list_t **node, size_t pos) {
  if (list == NULL || node == NULL) {
    return 1;
  }

  list_t *temp = list;
  size_t i = 0;
  while (i < pos) {
    temp = temp->next;
    i++;
  }
  *node = temp;
  return 0;
}

int main() {
  return 0; // probably done idk
}
