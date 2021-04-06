/* dlist.c */

#include "dlist.h"

Node* Head = NULL;
Node* Tail = NULL;

// ���� �߻� ���
void ERROR(const char* err_msg) {
	// LCD�� ������ ���
}

void Push(DataFrame* df) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	// �����Ҵ� ���� üũ
	if (newNode == NULL) {
		ERROR("Mem Alloc Failed");
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
		ERROR("Queue Fault");
	}
}

DataFrame* Pop() {
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
DataFrame* Front() {
	// ��尡 ������� ���� ���
	if (Head != NULL) {
		return Head->df;
	}
	// ��尡 �� ���
	else {
		return NULL;
	}
}

/* dlist.c */