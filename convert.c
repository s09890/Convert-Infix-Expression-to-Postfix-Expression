// ***
// *** You MUST modify this file
// ***

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "list.h"
#include "convert.h"

// DO NOT MODIFY FROM HERE --->>>
const int Operations[] = {'+', '-', '*', '(', ')'};

// return -1 if the word is not an operator
// return 0 if the word contains '+'
//        1                      '-'
//        2                      '*'
//        3                      '('
//        4                      ')'
int isOperator(char * word)
{
  int ind;
  int numop = sizeof(Operations) / sizeof(int);
  for (ind = 0; ind < numop; ind ++)
    {
    char *loc = strchr(word, Operations[ind]);
    if (loc != NULL && !isdigit(loc[1]))
	{
	  return ind;
	}
    }
  return -1;
}
// <<<--- UNTIL HERE
void add(List *stack, char *word)
{
  addNode(stack, word);
}

ListNode * delete(List * stack)
{
  if (stack == NULL || stack -> tail == NULL)
  {
    return NULL;
  }

  ListNode * deletedNode = stack->tail;
  if (!deleteNode(stack, stack->tail))
  {
    return NULL;
  }

  return deletedNode;
}

int precedence(int operatorIndex)
{
  switch (operatorIndex)
  {
    case 0:
    case 1:
      return 1;
    case 2:
      return 2;
    default:
      return -1;
  }
}

bool isStackEmpty(List *stack)
{
  return stack == NULL || stack -> head == NULL;
}

// ***
// *** You MUST modify the convert function
// ***
#ifdef TEST_CONVERT
bool convert(List * arithlist)
{
  if (arithlist == NULL)
  {
    return true;
  }
  if ((arithlist -> head) == NULL)
  {
    return true;
  }

  List stack;
  stack.head = NULL;
  stack.tail = NULL;

  List output;
  output.head = NULL;
  output.tail = NULL;

  ListNode *current = arithlist->head;
  while (current != NULL)
  {
    int opIndex = isOperator(current->word);
    if (opIndex == -1)
    {
      addNode(&output, current->word);
    }
    else if (opIndex == 3) // Open parenthesis
    {
      add(&stack, current->word);
    }
    else if (opIndex == 4) // Close parenthesis
    {
      while (!isStackEmpty(&stack) && isOperator(stack.tail->word) != 3)
      {
        ListNode *deletedNode = delete(&stack);
        addNode(&output, deletedNode->word);
        free(deletedNode);
      }
      if (!isStackEmpty(&stack))
      {
        ListNode *deletedNode = delete(&stack);
        free(deletedNode);
      }
    }
    else
    {
      while (!isStackEmpty(&stack) && precedence(isOperator(stack.tail->word)) >= precedence(opIndex))
      {
        ListNode *deletedNode = delete(&stack);
        addNode(&output, deletedNode->word);
        free(deletedNode);
      }
      add(&stack, current->word);
    }
    current = current->next;
  }

  while (!isStackEmpty(&stack))
  {
    ListNode *deletedNode = delete(&stack);
    addNode(&output, deletedNode->word);
    free(deletedNode);
  }
  // Replace the original list with the postfix list
  deleteList(arithlist);
  arithlist->head = output.head;
  arithlist->tail = output.tail;

  return true;
}
#endif