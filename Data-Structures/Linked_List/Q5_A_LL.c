//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 5 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

// 노드 하나를 표현하는 구조체
// 파이썬의 클래스 인스턴스 하나와 비슷하게 생각하면 돼
typedef struct _listnode{
	int item;               // 노드가 저장하는 정수 값
	struct _listnode *next; // 다음 노드를 가리키는 포인터 (마지막 노드면 NULL)
} ListNode;			// You should not change the definition of ListNode

// 링크드 리스트 전체를 관리하는 구조체
// head 포인터와 전체 크기(size)를 들고 다님
typedef struct _linkedlist{
	int size;       // 현재 리스트에 들어있는 노드 수
	ListNode *head; // 첫 번째 노드를 가리키는 포인터 (빈 리스트면 NULL)
} LinkedList;			// You should not change the definition of LinkedList


///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototype of this function
void frontBackSplitLinkedList(LinkedList* ll, LinkedList *resultFrontList, LinkedList *resultBackList);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *l);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);


///////////////////////////// main() /////////////////////////////////////////////

int main()
{
	int c = 1, i;  // c를 1로 초기화해야 while 루프에 진입함 (원본 코드 누락)
	LinkedList ll;
	LinkedList resultFrontList, resultBackList;

	//Initialize the linked list as an empty linked list
	ll.head = NULL;
	ll.size = 0;

	//Initialize the front linked list as an empty linked list
	resultFrontList.head = NULL;
	resultFrontList.size = 0;

	// Initialize the back linked list as an empty linked list
	resultBackList.head = NULL;
	resultBackList.size = 0;

	printf("1: Insert an integer to the linked list:\n");
	printf("2: Split the linked list into two linked lists, frontList and backList:\n");
	printf("0: Quit:\n");

	while (c != 0)
	{
	    printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			insertNode(&ll, ll.size, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			printf("The resulting linked lists after splitting the given linked list are:\n");
			frontBackSplitLinkedList(&ll, &resultFrontList, &resultBackList); // You need to code this function
			printf("Front linked list: ");
			printList(&resultFrontList);
			printf("Back linked list: ");
			printList(&resultBackList);
			printf("\n");
			removeAllItems(&ll);
			removeAllItems(&resultFrontList);
			removeAllItems(&resultBackList);
			break;
		case 0:
			removeAllItems(&ll);
			removeAllItems(&resultFrontList);
			removeAllItems(&resultBackList);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void frontBackSplitLinkedList(LinkedList *ll, LinkedList *resultFrontList, LinkedList *resultBackList)
{
	// 빈 리스트면 아무것도 할 필요 없음
	if (ll->head == NULL || ll->size == 0)
		return;

	// 앞 리스트 크기 계산: (size+1)/2 → 홀수일 때 앞에 하나 더 들어감
	// 예) size=4 → 2개 / size=5 → 3개
	int frontSize = (ll->size + 1) / 2;

	// 앞 리스트의 마지막 노드 (index: frontSize-1)
	ListNode *midNode = findNode(ll, frontSize - 1);

	// 앞 리스트 설정: 원본 head부터 midNode까지
	resultFrontList->head = ll->head;
	resultFrontList->size = frontSize;

	// 뒤 리스트 설정: midNode->next부터 끝까지
	resultBackList->head = midNode->next;
	resultBackList->size = ll->size - frontSize;

	// 두 리스트 연결 끊기: 안 하면 frontList 끝에서 backList로 넘어가버림!
	midNode->next = NULL;

	// 원본 ll을 비워주기: 노드들은 이미 front/back으로 넘어갔으니
	// ll까지 removeAllItems 하면 같은 노드를 두 번 free() → double free 에러!
	ll->head = NULL;
	ll->size = 0;
}

///////////////////////////////////////////////////////////////////////////////////

// 리스트의 모든 노드를 순서대로 출력하는 함수
void printList(LinkedList *ll){

	ListNode *cur;
	if (ll == NULL)
		return;
	cur = ll->head; // 첫 번째 노드부터 시작

	if (cur == NULL)
		printf("Empty"); // 빈 리스트면 "Empty" 출력
	while (cur != NULL)
	{
		printf("%d ", cur->item); // 현재 노드의 값 출력
		cur = cur->next;          // 다음 노드로 이동
	}
	printf("\n");
}


// 리스트의 모든 노드를 메모리에서 해제하고 초기화하는 함수
// free()를 안 하면 메모리 누수(memory leak) 발생! (파이썬은 GC가 자동으로 해줬지만 C는 직접 해야 해)
void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL){
		tmp = cur->next; // 다음 노드 주소를 미리 저장 (free 하면 cur->next 접근 불가)
		free(cur);       // 현재 노드 메모리 해제
		cur = tmp;       // 저장해둔 다음 노드로 이동
	}
	ll->head = NULL; // head를 NULL로 초기화
	ll->size = 0;    // size를 0으로 초기화
}


// index 번째 노드의 포인터를 반환하는 함수
// 없으면 NULL 반환
ListNode * findNode(LinkedList *ll, int index){

	ListNode *temp;

	// 유효하지 않은 입력 체크
	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head; // 첫 번째 노드부터 시작

	if (temp == NULL || index < 0)
		return NULL;

	// index번만큼 next를 따라가면 원하는 노드에 도달
	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp; // 찾은 노드 반환
}

// index 위치에 value를 가진 새 노드를 삽입하는 함수
// 성공하면 0, 실패하면 -1 반환
int insertNode(LinkedList *ll, int index, int value){

	ListNode *pre, *cur;

	// 유효하지 않은 입력 체크
	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// 빈 리스트이거나 맨 앞(index==0)에 삽입할 때 → head를 새 노드로 교체
	if (ll->head == NULL || index == 0){
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode)); // 새 노드 메모리 할당
		ll->head->item = value;              // 값 설정
		ll->head->next = cur;                // 기존 head를 새 노드 뒤에 연결
		ll->size++;
		return 0;
	}

	// index-1 번째 노드(pre)를 찾고, 그 뒤에 새 노드를 끼워넣기
	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode)); // 새 노드 메모리 할당
		pre->next->item = value;              // 값 설정
		pre->next->next = cur;                // 새 노드 뒤에 기존 노드 연결
		ll->size++;
		return 0;
	}

	return -1;
}


// index 위치의 노드를 리스트에서 제거하고 메모리 해제하는 함수
// 성공하면 0, 실패하면 -1 반환
int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// 유효하지 않은 입력 체크
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// 맨 앞 노드(index==0) 제거 → head를 다음 노드로 교체
	if (index == 0){
		cur = ll->head->next; // 두 번째 노드를 미리 저장
		free(ll->head);       // 첫 번째 노드 메모리 해제
		ll->head = cur;       // head를 두 번째 노드로 교체
		ll->size--;

		return 0;
	}

	// index-1 번째 노드(pre)를 찾아서, pre->next(삭제 대상)를 건너뛰고 연결
	if ((pre = findNode(ll, index - 1)) != NULL){

		if (pre->next == NULL)
			return -1;

		cur = pre->next;         // 삭제할 노드
		pre->next = cur->next;   // 삭제할 노드를 건너뛰고 연결
		free(cur);               // 삭제할 노드 메모리 해제
		ll->size--;
		return 0;
	}

	return -1;
}
