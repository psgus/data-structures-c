#include <stdio.h>
#include <stdlib.h>

// 노드 구조체: 값(item) + 다음 노드 주소(next)
typedef struct _listnode{
	int item;
	struct _listnode *next;
} ListNode;

// 리스트 구조체: 노드 수(size) + 첫 노드 주소(head)
typedef struct _linkedlist{
	int size;
	ListNode *head;
} LinkedList;

int insertSortedLL(LinkedList *ll, int item); // ← 네가 구현한 함수

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode *findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);

int main()
{
	LinkedList ll;
	int c, i, j;
	c = 1;

	ll.head = NULL;
	ll.size = 0;

	printf("1: Insert an integer to the sorted linked list:\n");
	printf("2: Print the index of the most recent input value:\n");
	printf("3: Print sorted linked list:\n");
	printf("0: Quit:");

	while (c != 0)
	{
		printf("\nPlease input your choice(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			j = insertSortedLL(&ll, i); // 정렬 상태 유지하며 삽입, 삽입 인덱스 반환
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			printf("The value %d was added at index %d\n", i, j); // 마지막 삽입 위치 출력
			break;
		case 3:
			printf("The resulting sorted linked list is: ");
			printList(&ll);
			removeAllItems(&ll);
			break;
		case 0:
			removeAllItems(&ll);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}
	return 0;
}

// 정렬된 상태를 유지하면서 item을 삽입, 삽입된 인덱스 반환
int insertSortedLL(LinkedList *ll, int item)
{
	int index = 0;
	ListNode *cur;

	if (ll == NULL)
		return -1;

	cur = ll->head;

	// item보다 작은 노드를 건너뛰며 삽입 위치 탐색
	while (cur != NULL && cur->item < item){
		cur = cur->next;
		index++;
	}

	if (insertNode(ll, index, item) == -1)
		return -1;

	return index;
}

// 리스트 전체 출력
void printList(LinkedList *ll){

	ListNode *cur;

	if (ll == NULL)
		return -1;

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
