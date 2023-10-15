// Set ADT implementation ... COMP9024 23T2

#include "Set.h"
#include <assert.h>
#include <stdlib.h>

typedef struct Node {
   int         v;      // each node in the linked list stores an int, and
   struct Node *next;  // a pointer to the next node
} Node;

typedef struct SetRep {
   Node *head;         // the set is stored as a linked list,
                       // we keep a pointer to the head of the list, and
   int  len;           // the length of the list
} SetRep;

Set newSet() {
   Set s = malloc(sizeof(SetRep));
   assert (s != NULL);
   s->head = NULL;
   s->len = 0;
   return s;
}

void freeSet(Set s) {
   while (s->head != NULL) {
      Node *old = s->head;
      s->head = s->head->next;
      free(old);
   }
   
   free(s);
}

int sizeSet(Set s) {
   return s->len;
}

bool memberOfSet(Set s, int v) {
   assert(s != NULL);
   
   for (Node *curr = s->head; curr != NULL; curr = curr->next) {
      if (curr->v == v) {
         return true;
      }
   }
   
   return false;
}

void addtoSet(Set s, int v) {
   assert (s != NULL);

   // only add the element if it isn't already in the set
   if (!memberOfSet(s, v)) {
      // create a new list node for the element
      Node *n = malloc(sizeof(Node));
      assert(n != NULL);
      n->v = v;

      // insert it at the head of the list
      n->next = s->head;
      s->head = n;
      s->len++;
   }
}

void removeFromSet(Set s, int v) {
   assert (s != NULL);

   // if the set is empty then nothing to do
   if (s->head == NULL)
      return;

   Node *prev = NULL;
   Node *curr = s->head;
   bool found = false;

   // scan the list until we find the element or get to the end
   while (!found && curr != NULL) {
      if (curr->v == v) {
         found = true;

         if (prev == NULL) {
            // found in the first node, update the head
            s->head = curr->next;
         } else {
            // otherwise link the previous node to the next node
            prev->next = curr->next;
         }

         free(curr);
         s->len--;
      } else {

         prev = curr;
         curr = curr->next;
      }
   }
}