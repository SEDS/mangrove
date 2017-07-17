#include "phylip.h"
#include "moves.h"
#include "seq.h"
#define maxsz           999   
typedef struct treeset_t {
} treeset_t;
typedef enum {
  horiz,           question
  } chartype;
typedef enum {
     none
  } rearrtype;
typedef struct gbase2 {
} gbase2;
typedef enum {
    spec
  } howtree;
typedef enum {beforenode, atnode} movet;
movet fromtype;
typedef node **pointptr;
node *root,  *grbg = NULL;
boolean usertree,  nodep, goteof, firsttree, haslengths;  
pointptr treenode;   
boolean reversed[(long)question - (long)horiz + 1];
boolean graphic[(long)question - (long)horiz + 1];
void dnamove_re_move(node **item, node **fork)
{
  node *p=NULL, *q;
  int nodecount;
  if ((*item)->back == NULL) {
    *fork = NULL;
    return;
  }
  *fork = treenode[(*item)->back->index - 1];
  nodecount = 0;
  if ((*fork)->next->back == *item)
    p = *fork;
  q = (*fork)->next;
  do {
    nodecount++;
    if (q->next->back == *item)
      p = q;
    q = q->next;
  } while (*fork != q);
  if (nodecount > 2)
  {
    fromtype = atnode;
    p->next = (*item)->back->next;
    chuck(&grbg, (*item)->back);
    (*item)->back = NULL;
    *fork = NULL;
  } else {
    if (*item == (*fork)->next->back) {
      if (root == *fork)
     root = (*fork)->next->next->back;
    } else {
      if (root == *fork)
     root = (*fork)->next->back;
    }
    fromtype = beforenode;
    p = (*item)->back->next->back;
    q = (*item)->back->next->next->back;
    if (p != NULL)
      p->back = q;
    if (q != NULL)
      q->back = p;
    if (haslengths) {
      if (p != NULL && q != NULL) {
     p->length += q->length;
     q->length = p->length;
      } else
     (*item)->length = (*fork)->next->length + (*fork)->next->next->length;
    }
    (*fork)->back = NULL;
    p = (*fork)->next;
    while (p != *fork) {
      p->back = NULL;
      p = p->next;
    }
    (*item)->back = NULL;
  } 
}  
int main(int argc, Char *argv[])
;  
