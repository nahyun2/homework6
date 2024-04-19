/* circularQ.c
 *
 *  Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */
#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4 // ���� ť�� �ִ� ũ�⸦ 4�� ����

typedef char element; // char�� element�� ����

typedef struct // ���� ť ����ü ����
{ 
	element queue[MAX_QUEUE_SIZE]; // ũ�Ⱑ 4�� ���� ť�� ��Ҹ� ������ �迭
	int front, rear; // ���� ť�� front�� rear�� ������ ����
}QueueType;

//�Լ� ���� ����
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
	
	QueueType *cQ = createQueue(); // ����ü ������ cQ�� �����ϰ� createQueue()�Լ��� ȣ���� �ʱ�ȭ
	element data; // element�� ���� data ����
	char command;

	do{
		printf("\n[--------------- [�ֳ���]   [2023041039] ---------------]\n");
		printf("-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); // ����ڷκ��� ��ɾ� �Է� �ޱ�

		switch(command) {
		case 'i': case 'I':
			data = getElement(); //���� ť�� �߰��� ��� �Է� �ޱ�
			enQueue(cQ, data); // ���� ť�� ��� �߰�
			break;
		case 'd': case 'D':
			deQueue(cQ, &data); // ���� ť���� ��� ����
			break;
		case 'p': case 'P':
			printQ(cQ); //���� ť ���
			break;
		case 'b': case 'B':
			debugQ(cQ); // ���� ť �����
			break;
		case 'q': case 'Q':
   	        freeQueue(cQ); //���� ť ����
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); //'q'�� 'Q'�� �Է��ϸ� ����


	return 0;
}

// ���� ť�� �����ϴ� �Լ�
QueueType *createQueue()
{
	QueueType *cQ; // ����ü ������ cQ ����
	cQ = (QueueType *)malloc(sizeof(QueueType)); // cQ�� ������ ����ü(QueueType)�� ũ�⸸ŭ ���� �޸� �Ҵ�
	// front�� rear�� 0���� �ʱ�ȭ = ���� ť�� �������
	cQ->front = 0;
	cQ->rear = MAX_QUEUE_SIZE;
	return cQ; // ������ ���� ť�� �ּ� ��ȯ
}

// �����Ҵ��� ���� ť�� �����ϴ� �Լ�
int freeQueue(QueueType *cQ)
{
    if(cQ == NULL) return 1;
    free(cQ);
    return 1;
}

// ���� ť�� �߰��� ��Ҹ� item ������ �Է¹޾� ��ȯ�ϴ� �Լ�
element getElement()
{
	element item;
	printf("Input element = ");
	scanf(" %c", &item);
	return item;
}


// ���� ť�� ����ִ��� Ȯ���ϴ� �Լ�
int isEmpty(QueueType *cQ)
{
	if(cQ->front == (cQ->rear)%MAX_QUEUE_SIZE) // front�� rear�� ���� ���
	{
		printf("Queue is empty.\n"); 
		return 1;
		// ť�� ����ִٴ� �޽����� ����ϰ� 1 ��ȯ
	}
	// front�� rear�� ���� ������ 0 ��ȯ = ť�� ������� ����
	else
    	return 0;
}

// ���� ť�� ���� á���� Ȯ���ϴ� �Լ�
int isFull(QueueType *cQ)
{
	// (rear�� ���� �ε���)%(ť�� ��üũ��)�� ���� front�� ���� ���
	if((cQ->rear + 1) % MAX_QUEUE_SIZE == cQ->front)
	{
		printf("Queue is full.\n");
		return 1;
		// ť�� ���� á�ٴ� �޽����� ����ϰ� 1 ��ȯ
	}
	// ���� �ʴٸ� ť�� ���� ���� �ʾ����Ƿ� 0 ��ȯ
	else
    	return 0;
}


// ���� ť�� ��Ҹ� �߰��ϴ� �Լ�
void enQueue(QueueType *cQ, element item)
{
	if(isFull(cQ)) // �����͸� �ֱ� �� ť�� ���� á���� Ȯ��
		return; // ���� ���ִٸ� �Լ� ����
	else // ���� ������ �ʴٸ�
	{	
		// rear�� ���� �ε����� �̵�, ������ ������ �̿��� 
		// rear�� �迭�� ���� �ִٸ� 0���� �̵�
		cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE;
		cQ->queue[cQ->rear] = item; // rear�� ����Ű�� ��ġ�� item ����
	}
	return;
}

// ���� ť���� ��Ҹ� �����ϴ� �Լ�
void deQueue(QueueType *cQ, element *item)
{
	if(isEmpty(cQ)) // �����͸� ���� �� ť�� ����ִ��� Ȯ��
		return; // ����ִٸ� �Լ� ����
	else // ������� �ʴٸ�
	{
		// front�� ���� �ε����� �̵�, ������ ������ �̿��� 
		// front�� �迭�� ���� �ִٸ� 0���� �̵�
		cQ->front = (cQ->front + 1) % MAX_QUEUE_SIZE;
		*item = cQ->queue[cQ->front]; // front�� ����Ű�� ��ġ�� ��Ҹ� item�� ����
	}
    return ;
}

// ���� ť�� ����ϴ� �Լ�
void printQ(QueueType *cQ)
{
	int i, first, last; // i, first, last ���� ����
	// ť�� ó���� ���� front�� rear�� �̵��ϴ� ������� �Ҵ�
	first = (cQ->front + 1)%MAX_QUEUE_SIZE;
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE;

	printf("Circular Queue : [");

	i = first;
	
	while(i != last) // first���� last���� �ݺ�
	{ 
		printf("%3c", cQ->queue[i]); // ť�� ��� ���
		i = (i+1)%MAX_QUEUE_SIZE; // i�� ���� �ε����� �̵�

	}
	printf(" ]\n");
}

// ť�� front�� rear�� ��ġ�� Ȯ���� �� �ִ� �Լ�
// ť�� ������ �ε����� ����� ��Ҹ� Ȯ���� �� ����
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


