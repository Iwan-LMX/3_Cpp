// Set ADT interface ... COMP9024 23T2

#include <stdbool.h>

// users of the ADT only see a pointer to the internal representation
typedef struct SetRep *Set;

// and the various interface methods
Set    newSet();                 // allocate and returns a new, empty Set
void   freeSet(Set);             // destroy a Set by freeing all memory
void   addtoSet(Set, int);       // add an element to a Set
void   removeFromSet(Set, int);  // remove an element from a Set
bool   memberOfSet(Set, int);    // check if an element is a member of a Set
int    sizeSet(Set);             // #elements in a Set