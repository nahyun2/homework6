/** 
 * postfix.c
 *
 * School of Computer Science, 
 * Chungbuk National University
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STACK_SIZE 10 //스택의 최대 크기를 10으로 정의
#define MAX_EXPRESSION_SIZE 20 //식의 최대 크기를 20으로 정의

/* stack 내에서 우선순위, lparen = 0 가장 낮음 */
typedef enum{
	lparen = 0,  /* ( 왼쪽 괄호 */
	rparen = 9,  /* ) 오른쪽 괄호*/
	times = 7,   /* * 곱셈 */
	divide = 6,  /* / 나눗셈 */
	plus = 5,    /* + 덧셈 */
	minus = 4,   /* - 뺄셈 */
	operand = 1 /* 피연산자 */
} precedence;

char infixExp[MAX_EXPRESSION_SIZE];   	/* infix expression을 저장하는 배열 */
char postfixExp[MAX_EXPRESSION_SIZE];	/* postfix로 변경된 문자열을 저장하는 배열 */
char postfixStack[MAX_STACK_SIZE];	/* postfix로 변환을 위해 필요한 스택 */
int evalStack[MAX_STACK_SIZE];		/* 계산을 위해 필요한 스택 */

int postfixStackTop = -1;  /* postfixStack용 top */
int evalStackTop = -1;	   /* evalStack용 top */

int evalResult = 0;	   /* 계산 결과를 저장 */

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
		printf("------------------ [최나현]   [2023041039] ------------------\n");
		printf("----------------------------------------------------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); // 사용자로부터 명령어 입력받음

		switch(command) {
		case 'i': case 'I':
			getInfix(); // infixExp에 infix expression을 입력받는 함수 실행
			break;
		case 'p': case 'P':
			toPostfix(); // infixExp를 postfixExp로 변경하는 함수 실행
			break;
		case 'e': case 'E':
			evaluation(); // postfixExp를 계산하는 함수 실행
			break;
		case 'd': case 'D':
			debug(); // infixExp, postfixExp, evalResult, postfixStack 출력하는 함수 실행
			break;
		case 'r': case 'R':
			reset(); // 초기화하는 함수 실행
			break;
		case 'q': case 'Q':
			break; 
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); // q나 Q를 입력받으면 종료

	return 1;
}

void postfixPush(char x) //후위표기 스택 push
{
    postfixStack[++postfixStackTop] = x;
}

char postfixPop() //후위표기 스택 pop
{
    char x;
    if(postfixStackTop == -1) // top이 -1이면 스택이 비어있는 경우이므로 pop할 수 없다.
        return '\0';
    else {
    	x = postfixStack[postfixStackTop--];
    }
    return x;
}

void evalPush(int x) //계산 스택 push
{
    evalStack[++evalStackTop] = x;
}

int evalPop() //계산 스택 pop
{
    if(evalStackTop == -1)
        return -1;
    else
        return evalStack[evalStackTop--];
}

/**
 * infix expression을 입력받는다.
 * infixExp에는 입력된 값을 저장한다.
 */
void getInfix()
{
    printf("Type the expression >>> ");
    scanf("%s",infixExp);
}

//각 연산자의 우선순위를 반환하는 함수
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
 * 문자하나를 전달받아, postfixExp에 추가
 */
void charCat(char* c)
{
	if (postfixExp == '\0')
		strncpy(postfixExp, c, 1);
	else
		strncat(postfixExp, c, 1);
}

/**
 * infixExp의 문자를 하나씩 읽어가면서 stack을 이용하여 postfix로 변경한다.
 * 변경된 postfix는 postFixExp에 저장된다.
 */
void toPostfix()
{
	// infixExp의 문자를 하나씩 읽기 위한 포인터
	char *exp = infixExp;
	char x; // 문자하나를 임시로 저장하기 위한 변수 선언

	/* exp를 증가시키며, 문자를 읽고 postfix로 변경 */
	while(*exp != '\0')
	{
		/* 필요한 로직 완성 */
		if(getToken(*exp) == operand) //연산자가 아닌 상수일 경우
			charCat(exp);
			//postfixExp로 전달

		else if(getToken(*exp) == rparen) //오른쪽 소괄호인 경우
		{
			while(postfixStack[postfixStackTop] != '(') //스택의 top이 왼쪽 소괄호를 만날 때까지
				charCat(&postfixStack[postfixStackTop--]);
				//pop하면서 postfixExp에 추가
			postfixPop(); //왼쪽 괄호 pop, postfixExp에 추가하지 않음
		}
		
		else if (getPriority(*exp) == lparen) //왼쪽 소괄호인 경우
			postfixPush(*exp); // 출력하지는 않고 푸시만함

		else //상수와 괄호가 아닌 다른 연산자인 경우
		{
			/* 스택 안의 연산자가 스택으로 들어갈 연산자보다 우선순위가 높은 경우
			   스택 안의 연산자의 우선순위가 작을때까지 pop */
			while (getPriority(postfixStack[postfixStackTop]) >= getPriority(*exp))
			{
				//pop한 데이터는 출력할 문자열로 전달
				x = postfixPop();
				charCat(&x);
			}
			// 스택 안의 연산자의 우선순위가 스택으로 들어갈 연산자보다 작으면
			postfixPush(*exp); // 스택 안으로 연산자를 푸시
		}


		exp++; // 다음 infixExp의 원소로
	}
	/* 위의 과정을 진행한 후, postfixStack에 데이터가 남아있다면
	 * 데이터를 전부 pop하여 postfixExp배열로 전달 */
	while (postfixStackTop != -1)
	{
		x = postfixPop();
		charCat(&x);
	}

	/* 필요한 로직 완성 */

}
// 전체 내용을 출력하는 함수
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
	//NULL로 초기화
	infixExp[0] = '\0';
	postfixExp[0] = '\0';

	//포스트픽스 스택 초기화
	for(int i = 0; i < MAX_STACK_SIZE; i++)
		postfixStack[i] = '\0';
    
	//포스트픽스 스택의 top과 계단스택의 top을 -1로 초기화하여 스택을 비움
	postfixStackTop = -1;
	evalStackTop = -1;
	evalResult = 0;
}

//후위표기식을 계산하는 함수
void evaluation()
{
	/* postfixExp, evalStack을 이용한 계산 */
	char *exp = postfixExp; //포인터 변수 exp에 postfixExp 주소 할당
	int x1, x2; // 정수형 변수 x1, x2를 선언

	while (*exp != '\0') // postfixExp의 길이만큼 반복
	{
		// exp의 값이 '+'일 경우
		if (*exp == '+')
		{
			// 연산자 앞의 두 상수를 계산 스택에서 추출해 더함
			x2 = evalPop(); 
			x1 = evalPop();
			// 계산한 결과를 계산 스택으로 푸시
			evalPush(x1 + x2);
		}
		// exp의 값이 '-'일 경우
		else if (*exp == '-')
		{
			// 연산자 앞의 두 상수 추출
			x2 = evalPop();
			x1 = evalPop();
			// 계산한 결과를 계산 스택으로 푸시
			evalPush(x1 - x2);
		}
		// exp의 값이 '*'일 경우
		else if (*exp == '*')
		{
			// 연산자 앞의 두 상수 추출
			x2 = evalPop();
			x1 = evalPop();
			// 계산한 결과를 계산 스택으로 푸시
			evalPush(x1 * x2);
		}
		// exp의 값이 '/'일 경우
		else if (*exp == '/')
		{
			// 연산자 앞의 두 상수 추출
			x2 = evalPop();
			x1 = evalPop();
			// 계산한 결과를 계산 스택으로 푸시
			evalPush(x1 / x2);
		}
		
		// 문자로 표현한 숫자를 int 형 배열인 evalStack에서 실제 숫자값으로 사용
		else if(getPriority(*exp) == operand)
			evalPush(*exp - '0');
		else
			break;
		exp++;// 문자열 다음 원소로
	}
	//위 루프를 모두 수행한 뒤 evalStack의 top에 위치한 데이터가 후위 표기식의 총 연산 결과
	evalResult = evalPop(); 
}

