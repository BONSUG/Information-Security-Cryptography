#include<stdio.h>
#include <windows.h>
#include <time.h>
#include<string.h>

#define MAX 50
int p, q, n, l, e, d;

void intro();
void getALL();
int GCD(int p1, int q1);
int LCM(int p1, int q1);
int GetDemicalNum();
void select1(char ch);
void encryption();
void decryption();


int main() {
	char ch;
	while (1) {
		intro();
		ch = getchar();
		if (ch == '4') break;
		select1(ch);
	}
	return 0;
}
void intro() {
	printf("\t\tRSA ���α׷�\t\t\n\n");
	printf("1.�ʱ�ȭ\t2.��ȣȭ\t3.��ȣȭ\t4.����\n\n");
	printf("����Ű(E = %d, N = %d) ����Ű(D = %d, N = %d)\n\n", e, n, d,n);
	printf("P = %d		Q = %d		L = %d\n",p, q, l);
	printf("\n���� : ");
}

int LCM(int p1, int q1) { //�ּҰ����
	int temp;
	if (p1 < q1) {
		temp=q1;
		q1=p1;
		p1 = temp;
	}
	return (p1 * q1) / GCD(p1, q1);
}
int GCD(int p1, int q1) { //�ִ�����
	if (q1 == 0) return p1;
	return GCD(q1, p1 % q1);
}
int GetDemicalNum() { //�Ҽ� ����
	srand((unsigned)time(NULL));
	int n, i;
	while (1) {
		n = 3 + rand()%1000;
		i = 2;
		while (1) {
			if (n % i == 0) {
				if (n == i) return n;
				else break;
			}
			else i++;
		}
	}
}
void getALL() {
	p = GetDemicalNum();
	Sleep(1000);
	q = GetDemicalNum();
	n = p * q;
	l = LCM(p - 1, q - 1);
	//e
	for (int i = 2; i < l; i++) {
		if (GCD(l, i) == 1) {
			e = i;
			break;
		}
	}
	//d
	for (int j = 2; j < l; j++) {
		if ((j * e) % l == 1) {
			d = j;
			break;
		}
	}
}

void encryption() { //��ȣȭ
	char str[MAX];
	int arr[MAX];

	FILE* fp = NULL;
	fp = fopen("plain.txt", "r");
	if (fp == NULL) {
		printf("���� �����Դϴ�.");
		Sleep(2000);
		return;
	}
	fgets(str, MAX, fp); //������ ������ �о� str�� ����
	fclose(fp);
	
	//��ȣȭ
	long long sum;
	int len = strlen(str);
	for (int i = 0; i < len; i++) {
		sum = 1;
		int a = str[i];
		for (int j = 0; j < e; j++)
		{
			sum *= a;
			if (sum < n) continue;
			else sum %= n;
		}
		arr[i] = (int)sum;
	}

//��ȣȭ�� ������ ���Ͽ� �Է�
	FILE* fp1 = NULL;
	fp1 = fopen("encryption.txt", "w");
	if (fp1 == NULL) {
		printf("���� �����Դϴ�.");
		Sleep(2000);
		return;
	}
	for (int i = 0; i < len; i++)
		fprintf(fp1, "%d\n", arr[i]);
	fclose(fp1);
	system("cls");
	printf("��ȣȭ �Ϸ�!");
	Sleep(1000);
}

void decryption() {
	char str2[MAX];
	FILE* fp = NULL;
	int cnt=0;
	int arr2[MAX] = { 0 };
	fp = fopen("encryption.txt","r");
	if (fp == NULL) {
		printf("���� �����Դϴ�.");
		Sleep(2000);
		return;
	}

	else {
		while (!feof(fp)) {
			fscanf(fp, "%d", arr2 + cnt); //������ ������ �� �پ� �о� arr2 �����迭�� ����
			cnt++;
		}
		fclose(fp);
	}

	//��ȣȭ
	long long sum;
	for (int i = 0; i < cnt+1; i++) {
		sum = 1;
		int a = arr2[i];
		for (int j = 0; j < d; j++)
		{
			sum *= a;
			if (sum < n)  continue;
			else sum %= n;
		}

		char c = (char)sum;
		str2[i] = c;
	}

	//��ȣȭ�� ������ ���Ͽ� �Է�
	int len = strlen(str2);
	FILE* fp1 = NULL;
	fp1 = fopen("decryption.txt", "w");
	if (fp1 == NULL) {
		printf("���� �����Դϴ�.");
		Sleep(2000);
		return;
	}
	for (int i = 0; i < len; i++)
		fprintf(fp1, "%c", str2[i]);
	fclose(fp1);
	system("cls");
	printf("��ȣȭ �Ϸ�!");
	Sleep(1000);
}
void select1(char ch) {
	switch (ch) {

	case '1':
		getALL();
		system("cls");
		break;

	case '2':
		system("cls");
		getchar();
		encryption();
		system("cls");
		break;

	case '3':
		system("cls");
		decryption();
		system("cls");
		break;
	default:

		printf("�߸��� �Է�\n");

		break;

	}

	system("cls");

}