// ***
// *** You MUST modify this file
// ***

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

bool readList(char * filename, List * arithlist)
{
  if (arithlist == NULL)
  {
    return false;
  }

  FILE * file = fopen(filename, "r");
  if (file == NULL)
  {
    return false;
  }

  char word[WORDLENGTH];
  while (fgets(word, WORDLENGTH, file) != NULL)
  {
    size_t len = strlen(word);
    if (len > 0 && word[len - 1] != '\n')
    {
      char wordWithNewline[WORDLENGTH + 1];
      snprintf(wordWithNewline, WORDLENGTH + 1, "%s\n", word);
      addNode(arithlist, wordWithNewline);
    }
    else
    {
      addNode(arithlist, word);
    }
  }

  fclose(file);
  return true;
}

void deleteList(List * list)
{
  if (list == NULL)
  {
    return;
  }

  while (list->head != NULL)
  {
    ListNode *temp = list->head;
    list->head = list->head->next;

    free(temp);
  }
  list->tail = NULL;
  free(list);
}

void addNode(List * arithlist, char * word)
{
  if (arithlist == NULL)
  {
    return;
  }
  
  ListNode * newNode = malloc(sizeof(ListNode));
  strncpy(newNode->word, word, WORDLENGTH - 1);
  newNode->word[WORDLENGTH - 1] = '\0';
  newNode->next = NULL;
  newNode->prev = NULL;

  if (arithlist->head == NULL)
  {
    arithlist->head = newNode;
    arithlist->tail = newNode;
  }
  else
  {
    ListNode *tail = arithlist->tail;
    tail->next = newNode;
    newNode->prev = tail;
    arithlist->tail = newNode;
  }
  
  // Add a newline character to the word if it doesn't already have one
  size_t len = strlen(newNode->word);
  if (len < WORDLENGTH - 1 && newNode->word[len - 1] != '\n')
  {
    newNode->word[len] = '\n';
    newNode->word[len + 1] = '\0';
  }
}

bool deleteNode(List * list, ListNode * node)
{
  if (list == NULL || node == NULL)
  {
    return false;
  }

  if (node->prev != NULL)
  {
    node->prev->next = node->next;
  }
  else
  {
    list->head = node->next;
  }

  if (node->next != NULL)
  {
    node->next->prev = node->prev;
  }
  else
  {
    list->tail = node->prev;
  }

  node->next = NULL;
  node->prev = NULL;

  return true;
}

