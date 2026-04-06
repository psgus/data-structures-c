//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 2 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

// 노드 구조체: 값(item) + 다음 노드 주소(next)
typedef struct _listnode
{
	int item;
	struct _listnode *next;
} ListNode;

// 리스트 구조체: 노드 수(size) + 첫 노드 주소(head)
typedef struct _linkedlist
{
	int size;
	ListNode *head;
} LinkedList;


//////////////////////// function prototypes /////////////////////////////////////

void alternateMergeLinkedList(LinkedList *ll1, LinkedList *ll2); // ← 네가 구현한 함수

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode *findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);


//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll1, ll2;
	int c, i, j;
	c = 1;

	ll1.head = NULL;
	ll1.size = 0;

	ll2.head = NULL;
	ll2.size = 0;

	printf("1: Insert an integer to the linked list 1:\n");
	printf("2: Insert an integer to the linked list 2:\n");
	printf("3: Create the alternate merged linked list:\n");
	printf("0: Quit:\n");

	while (c != 0)
	{
		printf("Please input your choice(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list 1: ");
			scanf("%d", &i);
			j = insertNode(&ll1, ll1.size, i);
			printf("Linked list 1: ");
			printList(&ll1);
			break;
		case 2:
			printf("Input an integer that you want to add to the linked list 2: ");
			scanf("%d", &i);
			j = insertNode(&ll2, ll2.size, i);
			printf("Linked list 2: ");
			printList(&ll2);
			break;
		case 3:
		    printf("The resulting linked lists after merging the given linked list are:\n");
			alternateMergeLinkedList(&ll1, &ll2); // ll2 노드를 ll1에 번갈아 끼워넣기
			printf("The resulting linked list 1: ");
			printList(&ll1);
			printf("The resulting linked list 2: ");
			printList(&ll2);
			removeAllItems(&ll1);
			removeAllItems(&ll2);
			break;
		case 0:
			removeAllItems(&ll1);
			removeAllItems(&ll2);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void alternateMergeLinkedList(LinkedList *ll1, LinkedList *ll2)
{
	ListNode *cur1 = ll1->head;
	ListNode *cur2 = ll2->head;

	while (cur1 != NULL && cur2 != NULL)
	{
		ListNode *next1 = cur1->next; // ll1 다음 노드 저장
		ListNode *next2 = cur2->next; // ll2 다음 노드 저장

		cur1->next = cur2;  // ll1 현재 뒤에 ll2 현재 연결
		cur2->next = next1; // ll2 현재 뒤에 원래 ll1 다음 연결

		cur1 = next1; // ll1 다음으로 이동
		cur2 = next2; // ll2 다음으로 이동

		ll1->size++;
		ll2->size--;
	}

	ll2->head = cur2; // 남은 ll2 노드 처리
}

///////////////////////////////////////////////////////////////////////////////////

// 리스트 전체 출력
void printList(LinkedList *ll){

	ListNode *cur;

	if (ll == NULL)
		return;

	cur = ll->head;

	if (cur == NULL)
		printf("Empty");

	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}

// 모든 노드 메모리 해제 후 초기화
void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL){
		tmp = cur->next; // free 전에 다음 노드 저장
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}

// index번째 노드 포인터 반환, 없으면 NULL
ListNode *findNode(LinkedList *ll, int index){

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

// index 위치에 value 삽입, 성공 0 / 실패 -1
int insertNode(LinkedList *ll, int index, int value){

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// 빈 리스트이거나 맨 앞 삽입 → head 갱신
	if (ll->head == NULL || index == 0){
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}

	// index-1번 노드 뒤에 새 노드 끼워넣기
	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}

// index 위치 노드 삭제, 성공 0 / 실패 -1
int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// 첫 번째 노드 삭제 → head 갱신
	if (index == 0){
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;

		return 0;
	}

	// index-1번 노드에서 삭제 대상을 건너뛰고 연결
	if ((pre = findNode(ll, index - 1)) != NULL){

		if (pre->next == NULL)
			return -1;

		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 0;
	}

	return -1;
}
