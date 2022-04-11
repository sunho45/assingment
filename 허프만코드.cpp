#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#pragma warning(disable:4996)
#define MAX 10000
#define askii 122 //�ҹ���z������ �ƽ�Ű�ڵ�
//Ʈ�� ���
typedef struct node
{
	char character;  // ����
	int freq;//�󵵼�
	struct node* left; //���� �ڽ� ���
	struct node* right; //������ �ڽ� ���
}node;

node* make_Huffman_tree(char arr[]);  //������ �ڵ� Ʈ�� ����(�����ϰ��� �ϴ� ���ڿ�)
node* makenode(char character, int freq, struct node* left, struct node* right); //�� ��� ����
void make_table(node* n, char str[], int len, char* table[]); //���� �� �������� �ڵ� �迭 ����
void decode(char* str, node* root); //���ڵ��Լ�
node node_arr[askii] = { NULL };
int ind = 0;//���� ����

//�� ��� ����(����,�󵵼�,���� �ڽ� ���,������ �ڽ� ���) 
node* makenode(char character, int freq, struct node* left, struct node* right)
{
	node* new_node = (node*)malloc(sizeof(node));
	new_node->character = character;
	new_node->freq = freq;
	new_node->left = left;
	new_node->right = right;
	return new_node;
}

//������ �ڵ� Ʈ�� ����(�����ϰ��� �ϴ� ���ڿ�)
node* make_Huffman_tree(char arr[])
{
	int i = 0;
	int j;
	int temp_n = 0;
	int min = 0;  //���� �󵵼��� ���� index
	int min2 = 0; //�� ��°�� �󵵼��� ���� index
	int fre[askii] = { 0 };  //����(space~z) �� ��
	int check[askii] = { 0 };  //���������� Ȯ��(�������� ���� �� �ʿ䰡 ������ -1)
	node* tree[askii] = { NULL };  //���� ��� �迭
	node* new_node; //�� ���

	while (arr[i] != NULL)
	{
		//�󵵼� ���ϱ�
		fre[arr[i]]++;
		i++;
	}
	for (int i = 32; i < askii; i++)
	{
		//���ڰ� �����ϸ�
		if (fre[i] != 0)
		{
			node_arr[ind] = *makenode(i, fre[i], NULL, NULL);//space���� z����
			tree[ind++] = makenode(i, fre[i], NULL, NULL); //��� ����
		}
	}
	for (i = 0; i < ind - 1; i++)
	{
		//���� ���� �� ã��
		j = 0;
		while (check[j] == -1)	j++; //������ ��带 ������ �迭 �� ���� �� index
		min = j; //�켱 ���� �۴ٰ� ����

		for (j = min; j < ind - 1; j++) //��� �迭�� �˻�
			if (check[j] != -1) //�̹� ������ ��尡 �ƴϸ�(�˻��غ� �ʿ䰡 ������)
				if (tree[min]->freq > tree[j]->freq)
					//min�ε��� �󵵼� ���� �󵵼��� ���� ���
					min = j;

		//�ι�°�� ���� �� ã��.
		j = 0;
		while (check[j] == -1 || j == min) j++;
		//������ ���� �ּ� ��� ������ �迭 �� ���� �� index
		min2 = j;  //�ι�°�� �۴ٰ� ����

		for (j = min2; j < ind; j++)
			if (check[j] != -1) //�̹� ������ ��尡 �ƴϸ�
				if (tree[min2]->freq > tree[j]->freq)
					//min2�ε��� �󵵼� ���� �󵵼��� ���� ���
					if (j != min) //���� ���� index�� �ƴ� ���
						min2 = j;

		tree[min] = makenode(NULL, tree[min]->freq + tree[min2]->freq, tree[min], tree[min2]);
		//min�� min2�ε����� �󵵼��� ��ģ �󵵼��� �� ��� ����
		//���� ���� ��带 min�ε��� �ڸ��� �ִ´�.

		check[min2] = -1;
		//min2�ε����� min�ε��� �ڸ��� ��忡 ���������Ƿ� check[min2]<-=1
	}
	return tree[min]; //������� Ʈ���� ��Ʈ ��� ��ȯ
}
void make_table(node* n, char str[], int len, char* table[])
{
	if (n->left == NULL && n->right == NULL) //n�� �ܳ���� ���
	{
		str[len] = '\0'; //������ ���� str���� �־��ְ�
						 //�� ����� ���ڸ� Ȯ���Ͽ� table�� ������ ��ġ�� str���ڿ��� �ִ´�.
		strcpy(table[(n->character)], str);
	}
	else //�� ��尡 �ƴ� ���
	{
		if (n->left != NULL) //���� �ڽ��� �ִ� ���
		{
			str[len] = '0'; //���ڿ��� 0 ����
			make_table(n->left, str, len + 1, table);
			//���ȣ��(���ڿ��� �� ��ġ�� +1)
		}
		if (n->right != NULL) //������ �ڽ��� �ִ� ���
		{
			str[len] = '1'; //���ڿ��� 1 ����
			make_table(n->right, str, len + 1, table);
			//���ȣ��(���ڿ��� �� ��ġ�� +1)
		}
	}
}
//���� �� �������� �ڵ� �迭 ����
//(Ʈ�� ��Ʈ ���,���� ���� �ڵ� ���ڿ�,���ڿ��� �� ��ġ, ���� �� �迭)

//���ڵ��Լ�(���ڵ� �ϰ� ���� ���ڿ�, Ʈ�� ��Ʈ ���)
void decode(char* str, node* root)
{
	int i = 0;
	node* j = root;
	while (str[i] != '\0') //������ ���� �ƴ� ���.
	{
		if (str[i] == '0') //���ڰ� 0�� ���
			j = j->left; //���� �ڽ����� �̵�
		else if (str[i] == '1') //���ڰ� 1�� ���
			j = j->right; //������ �ڽ����� �̵�
		if (j->left == NULL && j->right == NULL) //�� ����� ���
		{
			printf("%c", j->character); //�� ����� ���� ���
			j = root;
		}
		i++;
	}
	printf("\n");
}

int main()
{

	char arr[MAX]; //�����ϰ��� �ϴ� ���ڿ�
	char* code[askii]; //�� ���ڿ� ���� �������� �ڵ� �迭
	char str[MAX]; //���ڿ� ����
	char encoding[MAX] = ""; //���ڵ��ؼ� ���� ������ �迭
	int i; //�ݺ��� ����
	char answer; //���ڵ� ���ϴ°��� ���� ��� ����
	node* root;//Ʈ���� ��Ʈ
	float num = 1.0;
	for (i = 32; i < askii; i++)
		code[i] = (char*)malloc(sizeof(char));

	printf("���๮��: ");
	scanf("%[^\n]s", arr); //�����ϰ��� �ϴ� ���ڿ� �Է�
	for (int i = 1; arr[i] != NULL; i++) {


		num++;
	}
	float num2 = 1.0;
	root = make_Huffman_tree(arr); //�������ڵ带 �̿��� Ʈ�� ����
	make_table(root, str, 0, code); //Ʈ���� ����� ���� �� �������� �ڵ� ����

	i = 0;
	while (arr[i] != NULL) { //�Է¹��� ���ڿ��� ����������

		strcat(encoding, code[arr[i]]); //���ں� �ڵ� ���ڵ� ���ڿ� �ڿ� �ֱ�

		i++;

	}
	for (int o = 1; encoding[o] != NULL; o++) {

		num2++;

	}
	if (num == 1) {
		printf("������ :   1 \n  ");
		printf("����� :   8 ");
	}


	else {
		for (i = 0; i < ind; i++)
			printf("%c : %s\n", node_arr[i].character, code[node_arr[i].character]);

		printf("���� ��� : %s\n", encoding); //���ڵ� �� ������ �迭 ���
		printf("������ %f �̴�\n", ((num * 8) / num2));
		printf("���� ���� : ");
		decode(encoding, root);
	}
	return 0;
}