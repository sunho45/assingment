# 허프만코드


## 허프만코드 in c

 
```
#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT 200
#pragma warning(disable:4996)
typedef struct TreeNode
{
	int weight;
	char ch;
	struct TreeNode* left;
	struct TreeNode* right;
} TreeNode;

typedef struct
{
	TreeNode* ptree;
	char ch;
	int key;
} element;

typedef struct
{
	element heap[MAX_ELEMENT];
	int heap_size;
} HeapType;

// 생성 함수
HeapType* create()
{
	return (HeapType*)malloc(sizeof(HeapType));
}
// 초기화 함수
void init(HeapType* h)
{
	h->heap_size = 0;
}
// 삽입 함수
void insert_min_heap(HeapType* h, element item)
{
	int i;
	i = ++(h->heap_size);
	while ((i != 1) && (item.key < h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;
}
// 삭제 함수
element delete_min_heap(HeapType* h)
{
	int parent, child;
	element item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child <= h->heap_size)
	{
		if ((child > h->heap_size) &&
			(h->heap[child].key) > h->heap[child + 1].key)
			child++;
		if (temp.key < h->heap[child].key) break;
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}
// 이진 트리 생성 함수
TreeNode* make_tree(TreeNode* left, TreeNode* right)
{
	TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
	node->left = left;
	node->right = right;
	return node;
}
// 이진 트리 제거 함수
void destroy_tree(TreeNode* root)
{
	if (root == NULL) return;
	destroy_tree(root->left);
	destroy_tree(root->right);
	free(root);
}
int is_leaf(TreeNode* root)
{
	return !(root->left) && !(root->right);
}
void print_array(int codes[], int n)
{
	for (int i = 0; i < n; i++)
		printf("%d", codes[i]);
	printf("\n");
}

void print_codes(TreeNode* root, int codes[], int top)
{
	// 0을 저장하고 순환호출 
	if (root->left)
	{
		codes[top] = 0;
		print_codes(root->left, codes, top + 1);
	}

	// 1을 저장하고 순환호출 
	if (root->right)
	{
		codes[top] = 1;
		print_codes(root->right, codes, top + 1);
	}

	// 단말노드이면 코드를 출력 
	if (is_leaf(root))
	{
		printf("%c: ", root->ch);
		print_array(codes, top);
	}
}
// 허프만 코드 생성 함수
void huffman_tree(int freq[], char ch_list[], int n)
{
	int i;
	TreeNode* node, * x;
	HeapType* heap;
	element e, e1, e2;
	int codes[100];
	int top = 0;

	heap = create();
	init(heap);
	for (i = 0; i < n; i++)
	{
		node = make_tree(NULL, NULL);
		e.ch = node->ch = ch_list[i];
		e.key = node->weight = freq[i];
		e.ptree = node;
		insert_min_heap(heap, e);
	}
	for (i = 1; i < n; i++)
	{
		// 최소값을 가지는 두개의 노드를 삭제
		e1 = delete_min_heap(heap);
		e2 = delete_min_heap(heap);
		// 두개의 노드를 합침
		x = make_tree(e1.ptree, e2.ptree);
		e.key = x->weight = e1.key + e2.key;
		e.ptree = x;
		printf("%d+%d->%d \n", e1.key, e2.key, e.key);
		insert_min_heap(heap, e);
	}
	e = delete_min_heap(heap); // 최종 트리
	print_codes(e.ptree, codes, top);
	destroy_tree(e.ptree);
	free(heap);
}
int main() {
	int size = 0;
	char a[200];
	scanf("%s", a);
	char ch_list[26] = { NULL };
	int num = 0; \
		int freq[26] = { 0 };
	int k = 0;
	int freql[26] = { 0 };
	for (int i = 0; a[i] != NULL; i++) {
		if (a[i] == ' ') {

		}
		else {
			int num = 1;
			for (int j = 0; j < i; j++) {
				if (a[j] == a[i]) {

					num++;
				}


			}


			if (num == 1) {

				ch_list[k] = a[i];
				k++;
				size++;
			}
			freq[a[i] - 'A']++;


		}
	}
	printf("%d\n", freq[4]);
	for (int k = 0; k < 26; k++) {
		for (int p = 0; p < 26; p++) {
			if (ch_list[k] == 'A' + p) {
				freql[k] = freq[p];

			}
		}
	}


	huffman_tree(freql, ch_list, size);
	return 0;

}
```


```
typedef struct TreeNode
{
	int weight;
	char ch;
	struct TreeNode* left;
	struct TreeNode* right;
} TreeNode;
```
다음과 같이 노드의 구조체를 만들어준다

```

HeapType* create()
{
	return (HeapType*)malloc(sizeof(HeapType));
}


```

구조체를 생성하는 함수이다.
```

void init(HeapType* h)
{
	h->heap_size = 0;
}
```
힙을 초기화 시켜준다.
```
void insert_min_heap(HeapType* h, element item)
{
	int i;
	i = ++(h->heap_size);
	while ((i != 1) && (item.key < h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;
}
```
최소힙에 삽입시키는 함수로 삽입된 함수는 힙의 마지막 위치에 삽입된다. 삽입된 값이 부모노드보다 작다면 부모노드와 자신을 교환시켜준다.


```
element delete_min_heap(HeapType* h)
{
	int parent, child;
	element item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child <= h->heap_size)
	{
		if ((child > h->heap_size) &&
			(h->heap[child].key) > h->heap[child + 1].key)
			child++;
		if (temp.key < h->heap[child].key) break;
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}
```
최소 힙에서 삭제시켜주는 함수로 최소히프에서 삭제 연산은 루트노드 즉 힙에서 최솟값을 삭제시킨다. 루트노드의 위치에 힙에서 마지막 위치의 값을 넣은 다음 최소힙의 규칙에 따라 배열시킨다.
```
TreeNode* make_tree(TreeNode* left, TreeNode* right)
{
	TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
	node->left = left;
	node->right = right;
	return node;
}
```
제일 작은 값과 두번째로 작은 값을가진 노드를 왼쪽부터 오른쪽으로 자식노드로 구성시켜 트리를 만든다.

```
int is_leaf(TreeNode* root)
{
	return !(root->left) && !(root->right);
}
```
단말노드인지 true or false를 나타내는 함수


```
void print_array(int codes[], int n)
{
	for (int i = 0; i < n; i++)
		printf("%d", codes[i]);
	printf("\n");
}
```
주어진 코드값을 출력시키는 함수


void print_codes(TreeNode* root, int codes[], int top)
{
	// 0을 저장하고 순환호출 
	if (root->left)
	{
		codes[top] = 0;
		print_codes(root->left, codes, top + 1);
	}

	// 1을 저장하고 순환호출 
	if (root->right)
	{
		codes[top] = 1;
		print_codes(root->right, codes, top + 1);
	}

	// 단말노드이면 코드를 출력 
	if (is_leaf(root))
	{
		printf("%c: ", root->ch);
		print_array(codes, top);
	}
}

주어진 트리에 왼쪽인지 오른쪽인지에 따라 가중치 0,1을 매긴다.
```
void huffman_tree(int freq[], char ch_list[], int n)
{
	int i;
	TreeNode* node, * x;
	HeapType* heap;
	element e, e1, e2;
	int codes[100];
	int top = 0;

	heap = create();
	init(heap);
	for (i = 0; i < n; i++)
	{
		node = make_tree(NULL, NULL);
		e.ch = node->ch = ch_list[i];
		e.key = node->weight = freq[i];
		e.ptree = node;
		insert_min_heap(heap, e);
	}
	for (i = 1; i < n; i++)
	{
		// 최소값을 가지는 두개의 노드를 삭제
		e1 = delete_min_heap(heap);
		e2 = delete_min_heap(heap);
		// 두개의 노드를 합침
		x = make_tree(e1.ptree, e2.ptree);
		e.key = x->weight = e1.key + e2.key;
		e.ptree = x;
		printf("%d+%d->%d \n", e1.key, e2.key, e.key);
		insert_min_heap(heap, e);
	}
	e = delete_min_heap(heap); // 최종 트리
	print_codes(e.ptree, codes, top);
	destroy_tree(e.ptree);
	free(heap);
}
```
최소 히프에서 가장작은 값과 두번쨰로 작은 값을 골라낸 다음 트리를 만든다. 이러한 과정을 반복해서 허프만 트리를 만든다.

```
int main() {
	int size = 0;
	char a[200];
	scanf("%s", a);
	char ch_list[26] = { NULL };
	int num = 0; \
		int freq[26] = { 0 };
	int k = 0;
	int freql[26] = { 0 };
```
```
	for (int i = 0; a[i] != NULL; i++) {
		if (a[i] == ' ') {

		}
		else {
			int num = 1;
			for (int j = 0; j < i; j++) {
				if (a[j] == a[i]) {

					num++;
				}


			}


			if (num == 1) {

				ch_list[k] = a[i];
				k++;
				size++;
			}
			freq[a[i] - 'A']++;


		}
	}



	for (int k = 0; k < 26; k++) {
		for (int p = 0; p < 26; p++) {
			if (ch_list[k] == 'A' + p) {
				freql[k] = freq[p];

			}
		}
	}
```
문자열에서 어떤 문자가 쓰였는지 알아내고 문자의 빈도수를 뽑아낸다.
```
	huffman_tree(freql, ch_list, size);
	return 0;

}
```

각 문자의 이진코드를 출력한다.

## 압축비

예를 들어 문자열 DDDDAAAEEEEE을 입력해보자. 아스키코드는 1바이트 즉 8비트 이진문자 0,1은 1비트를 할당한다.
즉 압축비는
![image](https://user-images.githubusercontent.com/100903674/162156968-d3931d17-ae9c-4eb8-8a4a-d876cc3c50f3.png)



빈도수는 
A|D|E
---|---|---|
3|4|5

A|D|E
---|---|---|
10|11|0


DDDDAAAEEEEE을 인코딩하면
1111111110101000000


즉 압축비는
 (12*8) /19=5.05이다.



![image](https://user-images.githubusercontent.com/100903674/162157628-07efda64-547e-4c90-a067-17d7ec8f73f2.png)






