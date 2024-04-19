/* circularQ.c
 *
 *  Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */
#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4 // 원형 큐의 최대 크기를 4로 정의

typedef char element; // char를 element로 정의

typedef struct // 원형 큐 구조체 정의
{ 
	element queue[MAX_QUEUE_SIZE]; // 크기가 4인 원형 큐의 요소를 저장할 배열
	int front, rear; // 원형 큐의 front와 rear를 저장할 변수
}QueueType;

//함수 원형 선언
QueueType *createQueue();
int freeQueue(QueueType *cQ);
int isEmpty(QueueType *cQ);
int isFull(QueueType *cQ);
void enQueue(QueueType *cQ, element item);
void deQueue(QueueType *cQ, element* item);
void printQ(QueueType *cQ);
void debugQ(QueueType *cQ);
element getElement();

int main(void)
{
	
	QueueType *cQ = createQueue(); // 구조체 포인터 cQ를 선언하고 createQueue()함수를 호출해 초기화
	element data; // element형 변수 data 선언
	char command;

	do{
		printf("\n[--------------- [최나현]   [2023041039] ---------------]\n");
		printf("-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); // 사용자로부터 명령어 입력 받기

		switch(command) {
		case 'i': case 'I':
			data = getElement(); //원형 큐에 추가할 요소 입력 받기
			enQueue(cQ, data); // 원형 큐에 요소 추가
			break;
		case 'd': case 'D':
			deQueue(cQ, &data); // 원형 큐에서 요소 제거
			break;
		case 'p': case 'P':
			printQ(cQ); //원형 큐 출력
			break;
		case 'b': case 'B':
			debugQ(cQ); // 원형 큐 디버그
			break;
		case 'q': case 'Q':
   	        freeQueue(cQ); //원형 큐 해제
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); //'q'나 'Q'를 입력하면 종료


	return 0;
}

// 원형 큐를 생성하는 함수
QueueType *createQueue()
{
	QueueType *cQ; // 구조체 포인터 cQ 선언
	cQ = (QueueType *)malloc(sizeof(QueueType)); // cQ에 선언한 구조체(QueueType)의 크기만큼 동적 메모리 할당
	// front와 rear를 0으로 초기화 = 원형 큐가 비어있음
	cQ->front = 0;
	cQ->rear = MAX_QUEUE_SIZE;
	return cQ; // 생성한 원형 큐의 주소 반환
}

// 동적할당한 원형 큐를 해제하는 함수
int freeQueue(QueueType *cQ)
{
    if(cQ == NULL) return 1;
    free(cQ);
    return 1;
}

// 원형 큐에 추가할 요소를 item 변수에 입력받아 반환하는 함수
element getElement()
{
	element item;
	printf("Input element = ");
	scanf(" %c", &item);
	return item;
}


// 원형 큐가 비어있는지 확인하는 함수
int isEmpty(QueueType *cQ)
{
	if(cQ->front == (cQ->rear)%MAX_QUEUE_SIZE) // front와 rear가 같을 경우
	{
		printf("Queue is empty.\n"); 
		return 1;
		// 큐가 비어있다는 메시지를 출력하고 1 반환
	}
	// front와 rear가 같지 않으면 0 반환 = 큐가 비어있지 않음
	else
    	return 0;
}

// 원형 큐가 가득 찼는지 확인하는 함수
int isFull(QueueType *cQ)
{
	// (rear의 다음 인덱스)%(큐의 전체크기)의 값이 front와 같을 경우
	if((cQ->rear + 1) % MAX_QUEUE_SIZE == cQ->front)
	{
		printf("Queue is full.\n");
		return 1;
		// 큐가 가득 찼다는 메시지를 출력하고 1 반환
	}
	// 같지 않다면 큐가 가득 차지 않았으므로 0 반환
	else
    	return 0;
}


// 원형 큐에 요소를 추가하는 함수
void enQueue(QueueType *cQ, element item)
{
	if(isFull(cQ)) // 데이터를 넣기 전 큐가 가득 찼는지 확인
		return; // 가득 차있다면 함수 종료
	else // 가득 차있지 않다면
	{	
		// rear를 다음 인덱스로 이동, 나머지 연산을 이용해 
		// rear가 배열의 끝에 있다면 0으로 이동
		cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE;
		cQ->queue[cQ->rear] = item; // rear가 가리키는 위치에 item 저장
	}
	return;
}

// 원형 큐에서 요소를 제거하는 함수
void deQueue(QueueType *cQ, element *item)
{
	if(isEmpty(cQ)) // 데이터를 빼기 전 큐가 비어있는지 확인
		return; // 비어있다면 함수 종료
	else // 비어있지 않다면
	{
		// front를 다음 인덱스로 이동, 나머지 연산을 이용해 
		// front가 배열의 끝에 있다면 0으로 이동
		cQ->front = (cQ->front + 1) % MAX_QUEUE_SIZE;
		*item = cQ->queue[cQ->front]; // front가 가리키는 위치의 요소를 item에 저장
	}
    return ;
}

// 원형 큐를 출력하는 함수
void printQ(QueueType *cQ)
{
	int i, first, last; // i, first, last 변수 선언
	// 큐의 처음과 끝을 front와 rear가 이동하는 방식으로 할당
	first = (cQ->front + 1)%MAX_QUEUE_SIZE;
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE;

	printf("Circular Queue : [");

	i = first;
	
	while(i != last) // first부터 last까지 반복
	{ 
		printf("%3c", cQ->queue[i]); // 큐의 요소 출력
		i = (i+1)%MAX_QUEUE_SIZE; // i를 다음 인덱스로 이동

	}
	printf(" ]\n");
}

// 큐의 front와 rear의 위치를 확인할 수 있는 함수
// 큐의 각각의 인덱스에 저장된 요소를 확인할 수 있음
void debugQ(QueueType *cQ)
{

	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		if(i == cQ->front) {
			printf("  [%d] = front\n", i);
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);
}


