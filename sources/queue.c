/* queue.c */

#include "queue.h"

Node* Head = NULL;
Node* Tail = NULL;

void QueuePush(DataFrame* df) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	// �����Ҵ� ���� üũ
	if (newNode == NULL) {
		//ExceptionHandling(DynamicAllocFailed);
		return;
	}
	newNode->df = df;
	// ť�� �� ���
	if (Head == NULL && Tail == NULL) {
		// �����Ҵ� ���� üũ
		Head = newNode;
		Head->preNode = NULL;
		Head->nextNode = NULL;
		Tail = Head;
	}
	// ť�� ������� ���� ���
	else if (Head != NULL && Tail != NULL) {
		newNode->preNode = Tail;
		newNode->nextNode = NULL;
		Tail->nextNode = newNode;
		Tail = newNode;
	}
	// ���� ó�� (�߸��� �ڵ鸵)
	else {
		//ExceptionHandling(QueueFault);
        return;
	}
}

DataFrame* QueuePop() {
	// ��尡 ������� ���� ���
	if (Head != NULL) {
		Node* tmpNode = Head;
		DataFrame* df = tmpNode->df;
		// ���� ������ ��ġ (���� ��尡 �ϳ�)
		if (Head == Tail) {
			Head = NULL;
			Tail = NULL;
		}
		// ��� != ���� : ���� ��尡 2�� �̻�
		else {
			Head = Head->nextNode;
			Head->preNode = NULL;
		}
		free(tmpNode);
		return df;
	}
	// ��尡 �� ���
	else {
		return NULL;
	}
}

// ť �� ��ȸ
DataFrame* QueueFront() {
	// ��尡 ������� ���� ���
	if (Head != NULL) {
		return Head->df;
	}
	// ��尡 �� ���
	else {
		return NULL;
	}
}

/* queue.c */