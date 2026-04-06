//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 자료구조
실습 시험: Section A - 연결 리스트 문제
목적: 2번 문제에 필요한 함수를 구현 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

/*
	연결 리스트 빠른 개념 정리

	1. 연결 리스트는 각 노드가
	   - 데이터(item)
	   - 다음 노드 주소(next)
	   를 가지며 줄처럼 연결된 구조입니다.

	2. head는 첫 번째 노드를 가리킵니다.
	   - head == NULL 이면 빈 리스트
	   - head != NULL 이면 첫 노드 존재

	3. size는 현재 노드 개수입니다.
	   삽입/삭제 가능한 인덱스 범위를 판단할 때 사용됩니다.

	4. 이 문제는 정렬 문제가 아니라
	   "두 리스트를 번갈아 연결하는 방식"을 이해하는 문제입니다.
	   즉, ll1과 ll2의 노드를 교대로 섞는 흐름을 생각하면 됩니다.
*/

typedef struct _listnode
{
	int item;				// 현재 노드가 저장하는 정수 값
	struct _listnode *next;	// 다음 노드를 가리키는 포인터
} ListNode;			// ListNode의 정의는 변경하면 안 됩니다.

typedef struct _linkedlist
{
	int size;			// 연결 리스트에 들어 있는 노드 개수
	ListNode *head;		// 첫 번째 노드를 가리키는 포인터
} LinkedList;			// LinkedList의 정의는 변경하면 안 됩니다.


//////////////////////// 함수 원형 선언 /////////////////////////////////////

// 이 함수의 원형은 변경하면 안 됩니다.
void alternateMergeLinkedList(LinkedList *ll1, LinkedList *ll2);

// 아래 helper 함수들은 이미 구현되어 있으므로
// alternateMergeLinkedList를 풀 때 적극적으로 활용하면 됩니다.
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
	// c: 메뉴 선택 번호
	// i: 사용자가 방금 입력한 정수 값
	// j: insertNode의 반환값(성공이면 0, 실패면 -1)
	c = 1;

	// 연결 리스트 ll1을 빈 연결 리스트로 초기화
	ll1.head = NULL;
	ll1.size = 0;

	// 연결 리스트 ll2를 빈 연결 리스트로 초기화
	ll2.head = NULL;
	ll2.size = 0;

	// 프로그램 시작 시 한 번 메뉴를 보여 줌
	printf("1: Insert an integer to the linked list 1:\n");
	printf("2: Insert an integer to the linked list 2:\n");
	printf("3: Create the alternate merged linked list:\n");
	printf("0: Quit:\n");

	// 사용자가 0을 입력할 때까지 반복
	while (c != 0)
	{
		// 메뉴 번호 입력받기
		printf("Please input your choice(1/2/3/0): ");
		scanf("%d", &c);

		// 입력한 메뉴 번호에 따라 다른 작업 수행
		switch (c)
		{
		case 1:
			// ll1의 맨 뒤에 새 값을 추가
			printf("Input an integer that you want to add to the linked list 1: ");
			scanf("%d", &i);
			j = insertNode(&ll1, ll1.size, i);
			printf("Linked list 1: ");
			printList(&ll1);
			break;
		case 2:
			// ll2의 맨 뒤에 새 값을 추가
			printf("Input an integer that you want to add to the linked list 2: ");
			scanf("%d", &i);
			j = insertNode(&ll2, ll2.size, i);
			printf("Linked list 2: ");
			printList(&ll2);
			break;
		case 3:
		    printf("The resulting linked lists after merging the given linked list are:\n");
			// 이 함수 안에서 번갈아 섞는 동작을 직접 구현해야 함
			alternateMergeLinkedList(&ll1, &ll2);
			printf("The resulting linked list 1: ");
			printList(&ll1);
			printf("The resulting linked list 2: ");
			printList(&ll2);
			// 결과를 확인한 뒤 두 리스트 메모리를 정리
			removeAllItems(&ll1);
			removeAllItems(&ll2);
			break;
		case 0:
			// 프로그램 종료 전 메모리 해제
			removeAllItems(&ll1);
			removeAllItems(&ll2);
			break;
		default:
			// 메뉴에 없는 번호를 입력한 경우
			printf("Choice unknown;\n");
			break;
		}
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void alternateMergeLinkedList(LinkedList *ll1, LinkedList *ll2)
{
	/*
		가이드라인만 적어둔 상태입니다. 정답 코드는 직접 작성하세요.

		이 함수의 목표:
		ll2의 노드를 ll1에 "번갈아" 끼워 넣는 것입니다.
		보통은 ll1의 각 노드 뒤에 ll2의 노드를 하나씩 붙이는 방식으로 생각하면 쉽습니다.

		중요한 관찰:
		- 이 문제는 새 값을 입력받아 새 노드를 만드는 문제가 아닐 수 있습니다.
		- 이미 존재하는 노드들의 연결(next)을 바꾸는 문제로 생각하면 더 자연스럽습니다.
		- 따라서 포인터를 직접 다루는 방식이 핵심입니다.

		예시로 흐름 생각해 보기:
		ll1: 1 -> 2 -> 3
		ll2: 10 -> 20 -> 30 -> 40

		번갈아 합치면 보통
		ll1: 1 -> 10 -> 2 -> 20 -> 3 -> 30
		ll2: 40
		처럼 "남는 노드"는 ll2에 남게 됩니다.

		풀이 순서:
		1. 예외 상황부터 생각하세요.
		   - ll1 또는 ll2가 NULL이면 어떻게 할지
		   - ll1이 비어 있으면 어떻게 할지
		   - ll2가 비어 있으면 사실 바꿀 것이 없는지

		2. 순회에 필요한 포인터를 준비하세요.
		   - ll1에서 현재 보고 있는 노드
		   - ll2에서 현재 가져올 노드
		   - 다음 노드를 잃어버리지 않기 위해 잠시 저장할 포인터

		3. 왜 "다음 노드 저장"이 필요할까요?
		   - next를 바꾸는 순간 원래 연결 정보가 사라질 수 있기 때문입니다.
		   - 그래서 연결을 바꾸기 전에 다음 노드를 먼저 저장해야 합니다.

		4. 반복은 언제까지 하면 될까요?
		   - ll1에도 아직 끼워 넣을 자리가 남아 있고
		   - ll2에도 가져올 노드가 남아 있는 동안

		5. 한 번의 반복에서 해야 할 핵심 작업:
		   - ll1의 현재 노드 다음을 잠시 저장
		   - ll2의 현재 노드 다음도 잠시 저장
		   - ll1 현재 노드 뒤에 ll2 현재 노드를 연결
		   - 방금 붙인 ll2 노드 뒤에 원래 ll1의 다음 노드를 연결
		   - 그 다음 순회 포인터들을 다음 위치로 이동

		6. 반복이 끝난 뒤 확인할 것:
		   - ll2 노드가 남았는지
		   - 남았다면 ll2의 head는 남은 첫 노드를 가리켜야 함
		   - 다 썼다면 ll2의 head는 NULL이 되어야 함

		7. size도 꼭 맞게 갱신해야 합니다.
		   - ll1은 합쳐진 만큼 size가 증가
		   - ll2는 빠져나간 만큼 size가 감소

		작성 전에 스스로 체크해 볼 질문:
		- ll1이 한 노드뿐이어도 동작할까?
		- ll2가 더 길면 남은 부분은 어디에 있어야 할까?
		- 연결을 바꾸기 전에 어떤 next를 먼저 저장해야 안전할까?
	*/
}

///////////////////////////////////////////////////////////////////////////////////

// printList:
// head부터 시작해서 연결 리스트 끝(NULL)까지 차례대로 출력한다.
// 이 함수는 리스트 내용을 "읽기만" 하고 구조를 바꾸지는 않는다.
void printList(LinkedList *ll){

	ListNode *cur;		// 리스트를 순회할 때 사용할 임시 포인터

	// 잘못된 입력이면 바로 종료
	if (ll == NULL)
		return;

	// head부터 시작해서 끝까지 출력
	cur = ll->head;

	// 첫 노드가 없다는 뜻은 빈 리스트라는 의미
	if (cur == NULL)
		printf("Empty");

	// cur이 NULL이 될 때까지 한 칸씩 이동하며 출력
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}


// removeAllItems:
// 연결 리스트의 모든 노드를 free하여 메모리를 정리한다.
// free된 노드는 더 이상 사용할 수 없으므로 next를 미리 저장해야 한다.
void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;	// 현재 지울 노드
	ListNode *tmp;				// 다음 노드를 잠시 저장할 포인터

	// 노드를 하나씩 해제하면서 다음 노드를 잃어버리지 않도록 tmp에 저장
	while (cur != NULL){
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}


// findNode:
// index번째 노드의 "주소"를 찾아 반환한다.
// 찾지 못하면 NULL을 반환한다.
//
// 인덱스 기준:
// head가 0번, 그 다음 노드가 1번, ...
//
// 중요한 점:
// 이 함수는 노드의 "값"이 아니라 "노드 자체의 주소(포인터)"를 돌려준다.
ListNode *findNode(LinkedList *ll, int index){

	ListNode *temp;		// head부터 이동하면서 index번째 노드를 찾는 포인터

	// 범위를 벗어난 인덱스는 찾을 수 없음
	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	// index번째 노드까지 한 칸씩 이동
	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

// insertNode:
// index 위치에 새 노드를 삽입한다.
// 성공하면 0, 실패하면 -1을 반환한다.
//
// 예:
// [10, 20, 30] 에서 index 1에 15를 넣으면
// [10, 15, 20, 30] 이 된다.
//
// index 의미 다시 보기:
// - index 0: 맨 앞 삽입
// - index size: 맨 뒤 삽입
int insertNode(LinkedList *ll, int index, int value){

	ListNode *pre, *cur;
	// pre: 새 노드 앞에 있는 노드
	// cur: 삽입 위치에 원래 있던 노드

	// 삽입 가능한 인덱스 범위를 벗어나면 실패
	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// 빈 리스트이거나 첫 번째 노드를 삽입하는 경우 head 포인터를 갱신해야 함
	if (ll->head == NULL || index == 0){
		// 기존 첫 노드를 잠시 저장
		cur = ll->head;

		// malloc으로 새 노드가 들어갈 메모리 공간을 확보
		// 그리고 head가 그 새 노드를 가리키게 함
		ll->head = malloc(sizeof(ListNode));
		ll->head->item = value;

		// 새 노드의 next는 원래 첫 노드를 가리키게 함
		ll->head->next = cur;
		ll->size++;
		return 0;
	}


	// 목표 위치의 이전 노드를 찾고
	// 새 노드를 만든 뒤 링크를 다시 연결
	if ((pre = findNode(ll, index - 1)) != NULL){
		// 삽입 위치에 원래 있던 노드를 저장
		cur = pre->next;

		// pre 다음에 새 노드를 연결
		// 즉, "앞 노드 -> 새 노드 -> 원래 노드" 순서로 이어 붙인다.
		pre->next = malloc(sizeof(ListNode));
		pre->next->item = value;

		// 새 노드의 다음은 원래 노드를 가리키게 설정
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}


// removeNode:
// index 위치의 노드를 삭제한다.
// 성공하면 0, 실패하면 -1을 반환한다.
// 삭제도 결국은 링크를 건너뛰게 만들어서 리스트에서 분리하는 작업이다.
int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;
	// pre: 삭제할 노드 바로 앞 노드
	// cur: 실제로 삭제할 노드

	// 제거할 수 있는 가장 큰 인덱스는 size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// 첫 번째 노드를 삭제하는 경우 head 포인터를 갱신해야 함
	if (index == 0){
		// 두 번째 노드를 미리 저장
		cur = ll->head->next;

		// 첫 번째 노드를 해제
		free(ll->head);

		// head가 두 번째 노드를 가리키도록 변경
		ll->head = cur;
		ll->size--;

		return 0;
	}

	// 목표 위치의 이전/이후 노드를 기준으로
	// 대상 노드를 해제한 뒤 링크를 다시 연결
	if ((pre = findNode(ll, index - 1)) != NULL){

		if (pre->next == NULL)
			return -1;

		// 삭제할 노드를 cur에 저장
		cur = pre->next;

		// pre가 삭제할 노드 다음 노드를 가리키도록 변경
		// 즉, 삭제할 노드를 링크에서 건너뛰게 만든다.
		pre->next = cur->next;

		// 더 이상 사용하지 않는 노드 메모리 해제
		free(cur);
		ll->size--;
		return 0;
	}

	return -1;
}
