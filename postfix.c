/** 
 * postfix.c
 *
 * School of Computer Science, 
 * Chungbuk National University
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STACK_SIZE 10 //������ �ִ� ũ�⸦ 10���� ����
#define MAX_EXPRESSION_SIZE 20 //���� �ִ� ũ�⸦ 20���� ����

/* stack ������ �켱����, lparen = 0 ���� ���� */
typedef enum{
	lparen = 0,  /* ( ���� ��ȣ */
	rparen = 9,  /* ) ������ ��ȣ*/
	times = 7,   /* * ���� */
	divide = 6,  /* / ������ */
	plus = 5,    /* + ���� */
	minus = 4,   /* - ���� */
	operand = 1 /* �ǿ����� */
} precedence;

char infixExp[MAX_EXPRESSION_SIZE];   	/* infix expression�� �����ϴ� �迭 */
char postfixExp[MAX_EXPRESSION_SIZE];	/* postfix�� ����� ���ڿ��� �����ϴ� �迭 */
char postfixStack[MAX_STACK_SIZE];	/* postfix�� ��ȯ�� ���� �ʿ��� ���� */
int evalStack[MAX_STACK_SIZE];		/* ����� ���� �ʿ��� ���� */

int postfixStackTop = -1;  /* postfixStack�� top */
int evalStackTop = -1;	   /* evalStack�� top */

int evalResult = 0;	   /* ��� ����� ���� */

void postfixpush(char x);
char postfixPop();
void evalPush(int x);
int evalPop();
void getInfix();
precedence getToken(char symbol);
precedence getPriority(char x);
void charCat(char* c);
void toPostfix();
void debug();
void reset();
void evaluation();

int main()
{
	char command;

	do{
		printf("------------------ [�ֳ���]   [2023041039] ------------------\n");
		printf("----------------------------------------------------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); // ����ڷκ��� ��ɾ� �Է¹���

		switch(command) {
		case 'i': case 'I':
			getInfix(); // infixExp�� infix expression�� �Է¹޴� �Լ� ����
			break;
		case 'p': case 'P':
			toPostfix(); // infixExp�� postfixExp�� �����ϴ� �Լ� ����
			break;
		case 'e': case 'E':
			evaluation(); // postfixExp�� ����ϴ� �Լ� ����
			break;
		case 'd': case 'D':
			debug(); // infixExp, postfixExp, evalResult, postfixStack ����ϴ� �Լ� ����
			break;
		case 'r': case 'R':
			reset(); // �ʱ�ȭ�ϴ� �Լ� ����
			break;
		case 'q': case 'Q':
			break; 
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); // q�� Q�� �Է¹����� ����

	return 1;
}

void postfixPush(char x) //����ǥ�� ���� push
{
    postfixStack[++postfixStackTop] = x;
}

char postfixPop() //����ǥ�� ���� pop
{
    char x;
    if(postfixStackTop == -1) // top�� -1�̸� ������ ����ִ� ����̹Ƿ� pop�� �� ����.
        return '\0';
    else {
    	x = postfixStack[postfixStackTop--];
    }
    return x;
}

void evalPush(int x) //��� ���� push
{
    evalStack[++evalStackTop] = x;
}

int evalPop() //��� ���� pop
{
    if(evalStackTop == -1)
        return -1;
    else
        return evalStack[evalStackTop--];
}

/**
 * infix expression�� �Է¹޴´�.
 * infixExp���� �Էµ� ���� �����Ѵ�.
 */
void getInfix()
{
    printf("Type the expression >>> ");
    scanf("%s",infixExp);
}

//�� �������� �켱������ ��ȯ�ϴ� �Լ�
precedence getToken(char symbol)
{
	switch(symbol) {
	case '(' : return lparen;
	case ')' : return rparen;
	case '+' : return plus;
	case '-' : return minus;
	case '/' : return divide;
	case '*' : return times;
	default : return operand;
	}
}

precedence getPriority(char x)
{
	return getToken(x);
}

/**
 * �����ϳ��� ���޹޾�, postfixExp�� �߰�
 */
void charCat(char* c)
{
	if (postfixExp == '\0')
		strncpy(postfixExp, c, 1);
	else
		strncat(postfixExp, c, 1);
}

/**
 * infixExp�� ���ڸ� �ϳ��� �о�鼭 stack�� �̿��Ͽ� postfix�� �����Ѵ�.
 * ����� postfix�� postFixExp�� ����ȴ�.
 */
void toPostfix()
{
	// infixExp�� ���ڸ� �ϳ��� �б� ���� ������
	char *exp = infixExp;
	char x; // �����ϳ��� �ӽ÷� �����ϱ� ���� ���� ����

	/* exp�� ������Ű��, ���ڸ� �а� postfix�� ���� */
	while(*exp != '\0')
	{
		/* �ʿ��� ���� �ϼ� */
		if(getToken(*exp) == operand) //�����ڰ� �ƴ� ����� ���
			charCat(exp);
			//postfixExp�� ����

		else if(getToken(*exp) == rparen) //������ �Ұ�ȣ�� ���
		{
			while(postfixStack[postfixStackTop] != '(') //������ top�� ���� �Ұ�ȣ�� ���� ������
				charCat(&postfixStack[postfixStackTop--]);
				//pop�ϸ鼭 postfixExp�� �߰�
			postfixPop(); //���� ��ȣ pop, postfixExp�� �߰����� ����
		}
		
		else if (getPriority(*exp) == lparen) //���� �Ұ�ȣ�� ���
			postfixPush(*exp); // ��������� �ʰ� Ǫ�ø���

		else //����� ��ȣ�� �ƴ� �ٸ� �������� ���
		{
			/* ���� ���� �����ڰ� �������� �� �����ں��� �켱������ ���� ���
			   ���� ���� �������� �켱������ ���������� pop */
			while (getPriority(postfixStack[postfixStackTop]) >= getPriority(*exp))
			{
				//pop�� �����ʹ� ����� ���ڿ��� ����
				x = postfixPop();
				charCat(&x);
			}
			// ���� ���� �������� �켱������ �������� �� �����ں��� ������
			postfixPush(*exp); // ���� ������ �����ڸ� Ǫ��
		}


		exp++; // ���� infixExp�� ���ҷ�
	}
	/* ���� ������ ������ ��, postfixStack�� �����Ͱ� �����ִٸ�
	 * �����͸� ���� pop�Ͽ� postfixExp�迭�� ���� */
	while (postfixStackTop != -1)
	{
		x = postfixPop();
		charCat(&x);
	}

	/* �ʿ��� ���� �ϼ� */

}
// ��ü ������ ����ϴ� �Լ�
void debug()
{
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp);
	printf("postExp =  %s\n", postfixExp);
	printf("eval result = %d\n", evalResult);

	printf("postfixStack : ");
	for(int i = 0; i < MAX_STACK_SIZE; i++)
		printf("%c  ", postfixStack[i]);

	printf("\n");

}

void reset()
{	
	//NULL�� �ʱ�ȭ
	infixExp[0] = '\0';
	postfixExp[0] = '\0';

	//����Ʈ�Ƚ� ���� �ʱ�ȭ
	for(int i = 0; i < MAX_STACK_SIZE; i++)
		postfixStack[i] = '\0';
    
	//����Ʈ�Ƚ� ������ top�� ��ܽ����� top�� -1�� �ʱ�ȭ�Ͽ� ������ ���
	postfixStackTop = -1;
	evalStackTop = -1;
	evalResult = 0;
}

//����ǥ����� ����ϴ� �Լ�
void evaluation()
{
	/* postfixExp, evalStack�� �̿��� ��� */
	char *exp = postfixExp; //������ ���� exp�� postfixExp �ּ� �Ҵ�
	int x1, x2; // ������ ���� x1, x2�� ����

	while (*exp != '\0') // postfixExp�� ���̸�ŭ �ݺ�
	{
		// exp�� ���� '+'�� ���
		if (*exp == '+')
		{
			// ������ ���� �� ����� ��� ���ÿ��� ������ ����
			x2 = evalPop(); 
			x1 = evalPop();
			// ����� ����� ��� �������� Ǫ��
			evalPush(x1 + x2);
		}
		// exp�� ���� '-'�� ���
		else if (*exp == '-')
		{
			// ������ ���� �� ��� ����
			x2 = evalPop();
			x1 = evalPop();
			// ����� ����� ��� �������� Ǫ��
			evalPush(x1 - x2);
		}
		// exp�� ���� '*'�� ���
		else if (*exp == '*')
		{
			// ������ ���� �� ��� ����
			x2 = evalPop();
			x1 = evalPop();
			// ����� ����� ��� �������� Ǫ��
			evalPush(x1 * x2);
		}
		// exp�� ���� '/'�� ���
		else if (*exp == '/')
		{
			// ������ ���� �� ��� ����
			x2 = evalPop();
			x1 = evalPop();
			// ����� ����� ��� �������� Ǫ��
			evalPush(x1 / x2);
		}
		
		// ���ڷ� ǥ���� ���ڸ� int �� �迭�� evalStack���� ���� ���ڰ����� ���
		else if(getPriority(*exp) == operand)
			evalPush(*exp - '0');
		else
			break;
		exp++;// ���ڿ� ���� ���ҷ�
	}
	//�� ������ ��� ������ �� evalStack�� top�� ��ġ�� �����Ͱ� ���� ǥ����� �� ���� ���
	evalResult = evalPop(); 
}

