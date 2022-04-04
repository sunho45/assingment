# 허프만 코드

## 허프만 코드 in C


```
typedef struct node
{
	char alphabet;  //알파벳
	int freq;//빈도수
	struct node* left; //왼쪽 자식 노드
	struct node* right; //오른쪽 자식 노드
}node;

```
다음과 같이 트리에 들어갈 노드의 구조체를 만든다.

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
새로운 노드를 만드는 함수이다. 새로운 노드의 구조체를 반환해준다.


```
``` 주어진 값을 토대로 허프만 트리를 만들어야 한다.
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












