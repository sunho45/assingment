# 허프만 코드

## 허프만 코드 in C

전체 
```
#include<stdio.h>
#include <stdlib.h>

#include<string.h>
#pragma warning(disable:4996)
#define MAX 5000
#define alph_num 26
//트리 노드
typedef struct node
{
	char alphabet;  //알파벳
	int freq;//빈도수
	struct node* left; //왼쪽 자식 노드
	struct node* right; //오른쪽 자식 노드
}node;

node* make_Huffman_tree(char arr[]);  //허프만 코드 트리 생성(압축하고자 하는 문자열)
node* makenode(char alphabet, int freq, struct node* left, struct node* right); //새 노드 생성
void make_table(node* n, char str[], int len, char* table[]); //알파벳 별 가변길이 코드 배열 생성
void decode(char* str, node* root); //디코드함수
node node_arr[alph_num] = { NULL };
int ind = 0;//문자 갯수

//새 노드 생성(알파벳,빈도수,왼쪽 자식 노드,오른쪽 자식 노드) 
node* makenode(char alphabet, int freq, struct node* left, struct node* right)
{
	node* new_node = (node*)malloc(sizeof(node));
	new_node->alphabet = alphabet;
	new_node->freq = freq;
	new_node->left = left;
	new_node->right = right;
	return new_node;
}

//허프만 코드 트리 생성(압축하고자 하는 문자열)
node* make_Huffman_tree(char arr[])
{
	int i = 0;
	int j;
	int temp_n = 0;
	int min = 0;  //제일 빈도수가 작은 index
	int min2 = 0; //두 번째로 빈도수가 작은 index
	int fre[alph_num] = { 0 };  //알파벳(A~Z) 빈도 수
	int check[alph_num] = { 0 };  //합쳐졌는지 확인(합쳐져서 살펴 볼 필요가 없으면 -1)
	node* tree[alph_num] = { NULL };  //비교할 노드 배열
	node* new_node; //새 노드

	while (arr[i] != NULL)
	{
		//빈도수 구하기
		fre[arr[i] - 'A']++;
		i++;
	}
	for (int i = 0; i < alph_num; i++)
	{
		//알파벳이 존재하면
		if (fre[i] != 0)
		{
			node_arr[ind] = *makenode(i + 'A', fre[i], NULL, NULL);
			tree[ind++] = makenode(i + 'A', fre[i], NULL, NULL); //노드 생성
		}
	}
	for (i = 0; i < ind - 1; i++)
	{
		//가장 작은 수 찾기
		j = 0;
		while (check[j] == -1)	j++; //합쳐진 노드를 제외한 배열 중 가장 앞 index
		min = j; //우선 제일 작다고 가정

		for (j = min; j < ind - 1; j++) //모든 배열을 검사
			if (check[j] != -1) //이미 합쳐진 노드가 아니면(검사해볼 필요가 있으면)
				if (tree[min]->freq > tree[j]->freq)
					//min인덱스 빈도수 보다 빈도수가 작은 경우
					min = j;

		//두번째로 작은 수 찾기
		j = 0;
		while (check[j] == -1 || j == min) j++;
		//합쳐진 노드와 최소 노드 제외한 배열 중 가장 앞 index
		min2 = j;  //두번째로 작다고 가정

		for (j = min2; j < ind; j++)
			if (check[j] != -1) //이미 합쳐진 노드가 아니면
				if (tree[min2]->freq > tree[j]->freq)
					//min2인덱스 빈도수 보다 빈도수가 작은 경우
					if (j != min) //가장 작은 index가 아닌 경우
						min2 = j;

		tree[min] = makenode(NULL, tree[min]->freq + tree[min2]->freq, tree[min], tree[min2]);
		//min과 min2인덱스의 빈도수를 합친 빈도수로 새 노드 생성
		//새로 만든 노드를 min인덱스 자리에 넣는다.

		check[min2] = -1;
		//min2인덱스는 min인덱스 자리의 노드에 합쳐졌으므로 check[min2]<-=1
	}
	return tree[min]; //만들어진 트리의 루트 노드 반환
}
void make_table(node* n, char str[], int len, char* table[])
{
	if (n->left == NULL && n->right == NULL) //n이 단노드인 경우
	{
		str[len] = '\0'; //문장의 끝을 str끝에 넣어주고
						 //단 노드의 알파벳을 확인하여 table의 적절한 위치에 str문자열을 넣는다.
		strcpy(table[(n->alphabet) - 'A'], str);
	}
	else //단 노드가 아닌 경우
	{
		if (n->left != NULL) //왼쪽 자식이 있는 경우
		{
			str[len] = '0'; //문자열에 0 삽입
			make_table(n->left, str, len + 1, table);
			//재귀호출(문자열에 들어갈 위치에 +1)
		}
		if (n->right != NULL) //오른쪽 자식이 있는 경우
		{
			str[len] = '1'; //문자열에 1 삽입
			make_table(n->right, str, len + 1, table);
			//재귀호출(문자열에 들어갈 위치에 +1)
		}
	}
}
//알파벳 별 가변길이 코드 배열 생성
//(트리 루트 노드,가변 길이 코드 문자열,문자열에 들어갈 위치, 저장 될 배열)

//디코드함수(디코딩 하고 싶은 문자열, 트리 루트 노드)


int main()
{

	char arr[MAX]; //압축하고자 하는 문자열
	char* code[alph_num]; //각 알파벳에 대한 가변길이 코드 배열
	char str[MAX]; //문자열 변수
	char encoding[MAX] = ""; //인코딩해서 나온 이진수 배열
	int i; //반복문 변수
	char answer; //디코딩 원하는가에 대한 대답 변수
	node* root;//트리의 루트
	float num = 1;
	for (i = 0; i < alph_num; i++)
		code[i] = (char*)malloc(sizeof(char));

	printf("압축하고자 하는 문자열(대문자) : ");
	scanf("%s", arr); //압축하고자 하는 문자열 입력
	for (int i = 1; arr[i] != NULL; i++) {


		num++;
	}
	float num2 = 1;
	root = make_Huffman_tree(arr); //허프만코드를 이용한 트리 생성
	make_table(root, str, 0, code); //트리를 사용한 알파벳 별 가변길이 코드 생성

	i = 0;
	while (arr[i] != NULL) { //입력받은 문자열이 끝날때까지
		strcat(encoding, code[arr[i] - 'A']); //문자별 코드 인코딩 문자열 뒤에 넣기

		i++;
	}
	for (int o = 1; encoding[o] != NULL; o++) {

		num2++;

	}
	if (num == 1) {
		printf("압축결과 :   1 \n  ");
		printf("압축률 :   800 ");
	}


	else {
		for (i = 0; i < ind; i++)
			printf("%c : %s\n", node_arr[i].alphabet, code[node_arr[i].alphabet - 'A']);

		printf("압축 결과 : %s\n", encoding); //인코딩 한 이진수 배열 출력
		printf("압축률은 %f 이다", ((num * 8) / num2) * 100);
	}
	return 0;
}


}
```
새로운 노드를 만드는 함수이다. 새로운 노드의 구조체를 반환해준다.

```
node* makenode(char alphabet, int freq, struct node* left, struct node* right)
{
	node* new_node = (node*)malloc(sizeof(node));
	new_node->alphabet = alphabet;
	new_node->freq = freq;
	new_node->left = left;
	new_node->right = right;
	return new_node;
}

```

### 주어진 값을 토대로 **허프만 트리**를 만들어야 한다.
``` 
node* make_Huffman_tree(char arr[])
```

```
{
	int i = 0;
	int j;
	int temp_n = 0;
	int min = 0;  //제일 빈도수가 작은 index
	int min2 = 0; //두 번째로 빈도수가 작은 index
	int fre[alph_num] = { 0 };  //알파벳(A~Z) 빈도 수
	int check[alph_num] = { 0 };  //합쳐졌는지 확인(합쳐져서 살펴 볼 필요가 없으면 -1)
	node* tree[alph_num] = { NULL };  //비교할 노드 배열
	node* new_node; //새 노드


```

필요한 변수들을 선언해준다
```
	while (arr[i] != NULL)
	{
		//빈도수 구하기
		fre[arr[i] - 'A']++;
		i++;
	}
```	
예를 들어 A가 들어간다면 fre[0]의 값이 증가하고 arr[i] Z라면 fre[25]의 값이 증가한다. 들어온 값이 AAZAZ라면 fre[0]의 값은 3고 fre[25]의 값은 2이다.








```	
	for (int i = 0; i < alph_num; i++)
	{
		//알파벳이 존재하면
		if (fre[i] != 0)
		{
			node_arr[ind] = *makenode(i + 'A', fre[i], NULL, NULL);
			tree[ind++] = makenode(i + 'A', fre[i], NULL, NULL); //노드 생성
		}
	}
```

A~Z중에서 빈도수가 0이 아니라면 알파벳이 존재한다. 알파벳이 존재한다면 알파벳과 알파벳의 빈도수가 있는 노드를 생성한다.



```
	for (i = 0; i < ind - 1; i++)
	{
		//가장 작은 수 찾기
		j = 0;
		while (check[j] == -1)	j++; //합쳐진 노드를 제외한 배열 중 가장 앞 index
		min = j; //우선 제일 작다고 가정

		for (j = min; j < ind - 1; j++) //모든 배열을 검사
			if (check[j] != -1) //이미 합쳐진 노드가 아니면(검사해볼 필요가 있으면)
				if (tree[min]->freq > tree[j]->freq)
					//min인덱스 빈도수 보다 빈도수가 작은 경우
					min = j;

		//두번째로 작은 수 찾기
		j = 0;
		while (check[j] == -1 || j == min) j++;
		//합쳐진 노드와 최소 노드 제외한 배열 중 가장 앞 index
		min2 = j;  //두번째로 작다고 가정

		for (j = min2; j < ind; j++)
			if (check[j] != -1) //이미 합쳐진 노드가 아니면
				if (tree[min2]->freq > tree[j]->freq)
					//min2인덱스 빈도수 보다 빈도수가 작은 경우
					if (j != min) //가장 작은 index가 아닌 경우
						min2 = j;

```
가장작은 값과 가장큰 값의 배열 번호를 알아낸다. min은 가장 작은 원소의 인덱스 번호이고 min2는 두번째로 작은 원소의 인덱스 번호 값이다.


```
		tree[min] = makenode(NULL, tree[min]->freq + tree[min2]->freq, tree[min], tree[min2]);
		//min과 min2인덱스의 빈도수를 합친 빈도수로 새 노드 생성
		//새로 만든 노드를 min인덱스 자리에 넣는다.
```
가장작은수와 두번째로 작은수를 이어 두 빈도수의 합이 들어간 정보의 노드를 생성. 이러한 결합을  (문자열에 있는 알파벳의 개수-1)번한다.


```
		check[min2] = -1;
		//min2인덱스는 min인덱스 자리의 노드에 합쳐졌으므로 check[min2]<-=1
	}
	return tree[min]; //만들어진 트리의 루트 노드 반환
}

```
최종적으로 모든 값이 들어있는 트리의 루트노드를 반환시켜준다.



### 이제 허프만 테이블을 만들어 각 문자들을 encode 해준다

```
void make_table(node* n, char str[], int len, char* table[])
{
	if (n->left == NULL && n->right == NULL) //n이 단노드인 경우
	{
		str[len] = '\0'; //문장의 끝을 str끝에 넣어주고
						 //단 노드의 알파벳을 확인하여 table의 적절한 위치에 str문자열을 넣는다.
		strcpy(table[(n->alphabet) - 'A'], str);
	}
```	
노드의 자식이 없다면 노드의 알파벳을 확인하여 table의 적절하 위치에 str을 넣는다.

```
	else //단 노드가 아닌 경우
	{
		if (n->left != NULL) //왼쪽 자식이 있는 경우
		{
			str[len] = '0'; //문자열에 0 삽입
			make_table(n->left, str, len + 1, table);
			//재귀호출(문자열에 들어갈 위치에 +1)
		}
```
노드에게 왼쪽 자식이 있다면 0을 삽입

```
		if (n->right != NULL) //오른쪽 자식이 있는 경우
		{
			str[len] = '1'; //문자열에 1 삽입
			make_table(n->right, str, len + 1, table);
			//재귀호출(문자열에 들어갈 위치에 +1)
		}
		
		}
```		
노드에게 오른쪽 자식이 있다면 1을 삽입





```
int main()
{
	
	char arr[MAX]; //압축하고자 하는 문자열
	char* code[alph_num]; //각 알파벳에 대한 가변길이 코드 배열
	char str[MAX]; //문자열 변수
	char encoding[MAX] = ""; //인코딩해서 나온 이진수 배열
	int i; //반복문 변수
	char answer; //디코딩 원하는가에 대한 대답 변수
	node* root;//트리의 루트
	
	for (i = 0; i < alph_num; i++)
		code[i] = (char*)malloc(sizeof(char));

	printf("압축하고자 하는 문자열(대문자) : ");
	scanf("%s", arr); //압축하고자 하는 문자열 입력

	root = make_Huffman_tree(arr); //허프만코드를 이용한 트리 생성
	make_table(root, str, 0, code); //트리를 사용한 알파벳 별 가변길이 코드 생성

	i = 0;
	while (arr[i] != NULL) { //입력받은 문자열이 끝날때까지
		strcat(encoding, code[arr[i] - 'A']); //문자별 코드 인코딩 문자열 뒤에 넣기
		strcat(encoding, " ");
		i++;
	}
if (num == 1) {
		printf("압축결과 :   1 \n  ");
		printf("압축률 :   8");
	}

else {
	printf("압축 결과 : %s\n", encoding); //인코딩 한 이진수 배열 출력
	printf("압축률: %d", (num * 8) / num2);
	}
	

	return 0;
}


```

다음과 같이 프로그램을 실행하면
![image](https://user-images.githubusercontent.com/100903674/161934027-09c8eb09-053b-4bbc-a09c-841ce5b847c3.png)



다음과 같이 영어 대문자로 이루어진 문자열을 입력하면 인코딩된 이진 배열을 확인할 수 있다.

## 압축률
ex) 예를들어 JDLSFJDLSFLSDKFDLKFLKSJFLKFLJDFGFGFGFGFGFGFGFGFGFGFGFGFGFDGSRGRGRDGDRG 을 압축해보자
아스키코드는 하나당 8비트를 할당한다. 반면 이진숫자 0,1은 하나당 1비트를 할당한다. 즉 압축률은
![image](https://user-images.githubusercontent.com/100903674/161559128-5c4ce46d-8223-4cd2-a30f-673ff8b774bc.png)이다.








압축해보면

![image](https://user-images.githubusercontent.com/100903674/161564143-82ebd3ac-e800-47d0-834b-094855a55af0.png)

























