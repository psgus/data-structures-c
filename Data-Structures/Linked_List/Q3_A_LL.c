//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 3 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

// 노드 하나를 표현하는 구조체
// 파이썬의 클래스 인스턴스 하나와 비슷하게 생각하면 돼
typedef struct _listnode
{
	int item;               // 노드가 저장하는 정수 값
	struct _listnode *next; // 다음 노드를 가리키는 포인터 (마지막 노드면 NULL)
} ListNode;			// You should not change the definition of ListNode

// 링크드 리스트 전체를 관리하는 구조체
// head 포인터와 전체 크기(size)를 들고 다님
typedef struct _linkedlist
{
	int size;       // 현재 리스트에 들어있는 노드 수
	ListNode *head; // 첫 번째 노드를 가리키는 포인터 (빈 리스트면 NULL)
} LinkedList;			// You should not change the definition of LinkedList


//////////////////////// function prototypes /////////////////////////////////////

// You should not change the prototype of this function
void moveOddItemsToBack(LinkedList *ll); // ← 네가 구현할 함수!

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);

//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll;
	int c, i, j;
	c = 1;

	// 링크드 리스트를 빈 상태로 초기화
	ll.head = NULL;
	ll.size = 0;

	printf("1: Insert an integer to the linked list:\n");
	printf("2: Move all odd integers to the back of the linked list:\n");
	printf("0: Quit:\n");

	while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			// 정수 하나를 입력받아 리스트 맨 뒤(ll.size 위치)에 삽입
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			j = insertNode(&ll, ll.size, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			// 홀수 노드를 뒤로 보내는 함수 호출 (네가 구현!)
			moveOddItemsToBack(&ll);
			printf("The resulting linked list after moving odd integers to the back of the linked list is: ");
			printList(&ll);
			removeAllItems(&ll); // 출력 후 리스트 전체 메모리 해제
			break;
		case 0:
			removeAllItems(&ll); // 종료 전 메모리 해제
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void moveOddItemsToBack(LinkedList *ll)
{
	ListNode *tail, *newTail, *pre, *cur;

	// 빈 리스트거나 노드가 1개면 아무것도 할 필요 없음
	if (ll->head == NULL || ll->size <= 1)
		return;

	// 1단계: 원래 마지막 노드(tail)를 찾아서 경계선으로 설정
	// tail은 "여기까지만 처리하자"는 sentinel 역할 → 절대 바꾸면 안 됨!
	// 파이썬으로 치면: tail = linked_list[-1]
	tail = ll->head;
	while (tail->next != NULL)
		tail = tail->next;

	// newTail: 홀수 노드를 붙일 위치 (처음엔 원래 마지막 노드 = tail과 동일)
	// tail과 별개로 관리해야 sentinel이 안 망가짐!
	newTail = tail;

	// 2단계: head부터 순회 시작
	pre = NULL; // cur의 이전 노드 (처음엔 없으니까 NULL)
	cur = ll->head;

	// cur이 원래 tail에 도달하면 멈춤 (tail 이후는 이미 뒤로 보낸 노드들)
	while (cur != tail && cur != NULL) {
		if (cur->item % 2 != 0) {
			// 홀수 노드: 현재 위치에서 떼어내고 맨 뒤(newTail)에 붙이기
			ListNode *next = cur->next; // 다음 노드를 미리 저장 (연결 끊기 전에!)

			// cur을 현재 위치에서 떼어내기
			if (pre == NULL)
				ll->head = next;  // cur이 head였을 때: head를 다음 노드로 교체
			else
				pre->next = next; // 일반적인 경우: 이전 노드가 다음 노드를 가리키게

			// cur을 newTail 뒤에 붙이기
			newTail->next = cur; // 현재 맨 뒤(newTail)에 cur 연결
			cur->next = NULL;    // cur이 새 마지막 노드가 됨
			newTail = cur;       // newTail을 cur로 업데이트 (다음 홀수는 여기 뒤에)

			cur = next;          // 다음 노드로 이동 (pre는 그대로, 위치가 안 바뀌었으니)
		} else {
			// 짝수 노드: 건드리지 않고 앞으로 이동
			pre = cur;
			cur = cur->next;
		}
	}
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
ListNode *findNode(LinkedList *ll, int index){

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
                                                                                                                                      