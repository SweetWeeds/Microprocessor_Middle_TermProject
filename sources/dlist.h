/* dlist.h */

#ifndef DLIST_H
#define DLIST_H

#include "stdio.h"
#include "stdlib.h"
#include "dataframe.h"

// Å¥ ³ëµå
typedef struct _Node {
	DataFrame* df;
	//int df;
	struct _Node* preNode;
	struct _Node* nextNode;
} Node;

void ERROR(const char*);
void Push(DataFrame* df);
DataFrame* Pop();
DataFrame* Front();

#endif /* DLIST_H */

/* dlist.h */