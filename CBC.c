#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>

#define plain 8 //�� ��� : 8��Ʈ
#define MAX 33//�ִ� 32�� �Է� ����
#define IMAX 64 //�ʱ�ȭ ���� 64��Ʈ
char str[MAX];//�Է� ���� ����

char PB1[plain]; //�� �Ǵ� ��ȣ�����
char PB2[plain];
char PB3[plain];
char PB4[plain];

int IV1[IMAX]; //�ʱ�ȭ ����
int IV2[IMAX];
int IV3[IMAX];
int IV4[IMAX];
int bit[IMAX]; //��ȣȭ

void intro();
void input();
void GetIV1();
void PrintPB(char* n);
void En(char* s1, int* n1, int* n2);
void En2(char* s1, int* n1);
void De(char* s1, int* n1, int* n2);
void select1(char ch);
void ChangedStr(char* s);
void PrintIV(int* n);

int main() {
	char ch;
	while (1) {
		intro();
		ch = getchar();
		select1(ch);
		if (ch == '4') break;
	}
	return 0;
}

void intro() {

	printf("\t\tCBC ��� ���α׷�\t\t\n\n");
	printf("1.�Է�\t2.��ȣȭ\t3.��ȣȭ\t4.����\n\n");
	printf("���1 : "); PrintPB(PB1);
	printf("���2 : "); PrintPB(PB2);
	printf("���3 : "); PrintPB(PB3);
	printf("���4 : "); PrintPB(PB4);
	printf("\nIV1 : "); PrintIV(IV1);
	printf("IV2 : "); PrintIV(IV2);
	printf("IV3 : "); PrintIV(IV3);
	printf("IV4 : "); PrintIV(IV4);
	printf("\n���� : ");
}

void PrintPB(char* n) {
	for (int i = 0; i < plain; i++) {
		printf("%x ", *(n + i));
	}
	printf("\t");
	for (int i = 0; i < plain; i++) {
		printf("%c ", *(n + i));
	}
	printf("\n");
}
void input() {
	getchar();
	for (int i = 0; i < plain; i++) {
		PB1[i] = ' '; //10���� 32 16���� 20
		PB2[i] = ' '; //�е��� ���� ���ڷ� ��
		PB3[i] = ' ';
		PB4[i] = ' ';
	}
	printf("�Է� : ");
	fgets(str, MAX, stdin);
	int len = strlen(str);
	int distribute = (len-1) / 4;

	if (len == 2) 
		PB1[0] = str[0];
	else if (len == 3) {
		PB1[0] = str[0];
		PB2[0] = str[1];
	}
	else if (len == 4) {
		PB1[0] = str[0];
		PB2[0] = str[1];
		PB3[0] = str[2];
	}
	else { ///7�ΰ�� 1/1/1/4	11�ΰ�� 2/2/2/5
		for (int j = 0; j < distribute; j++) {
			PB1[j] = str[j];
			PB2[j] = str[j + distribute];
			PB3[j] = str[j + distribute * 2];
		}
		for (int k = 0; k < len - (distribute * 3)-1; k++)
			PB4[k]=str[(distribute * 3)+k];
	}

}
void PrintIV(int* n) {
	for (int i = 0; i < IMAX; i++) {
		printf("%d", *(n+i));
		if (i % 8 == 7 && i != (IMAX - 1)) printf(" / ");
	}
	printf("\n");
}
void GetIV1() { 
	//���� ���� : 2���� ���� 64��Ʈ �ʱ�ȭ ���� ����
	srand((unsigned)time(NULL));
	for (int j = 0; j < plain; j++) {
		IV1[j] = 0;
	}
	int cut = 7;
	int current = cut;
	for(int i =0; plain>=i; i++)
	{
		int n = rand() % 256;
		while (1) {
			IV1[cut] = n % 2;
			n /= 2;
			cut--;
			if ((cut > 0 && cut == current - 8) || cut < 0) break;
		}
		cut = current + 8;
		current = cut;
		}
}

void En(char* s1, int *n1,int *n2) {
	for (int j = 0; j < IMAX; j++) {
		bit[j] = 0;
	}
	int cut = 7;
	int current = cut;

	int len = plain;
	for (int i = 0; i < len; i++)
	{
		int c = *(s1 + i); //PB
		while (1) {
			bit[cut] = c % 2;
			c /= 2;
			cut--;
			if ((cut > 0 && cut == current - 8) || cut < 0) break;
		}
		cut = current + 8;
		current = cut;
	}
	for (int j = 0; j < IMAX; j++) {
		bit[j] = bit[j] ^ *(n1 + j); //IV
		*(n2 + j) = bit[j];
	}
	ChangedStr(s1);
}
void En2(char* s1, int* n1) {
	for (int j = 0; j < IMAX; j++) {
		bit[j] = 0;
	}
	int cut = 7;
	int current = cut;

	int len = plain;
	for (int i = 0; i < len; i++)
	{
		int c = *(s1 + i); //PB
		while (1) {
			bit[cut] = c % 2;
			c /= 2;
			cut--;
			if ((cut > 0 && cut == current - 8) || cut < 0) break;
		}
		cut = current + 8;
		current = cut;
	}
	for (int j = 0; j < IMAX; j++) {
		bit[j] = bit[j] ^ *(n1+j); //IV
	}
	ChangedStr(s1);
}
void De(char* s1, int* n1, int* n2) {

	for (int j = 0; j < IMAX; j++) {
		bit[j] = 0;
	}
	int cut = 7;
	int current = cut;

	int len = plain;
	for (int i = 0; i < len; i++)
	{
		int c = *(s1 + i); //PB
		while (1) {
			bit[cut] = c % 2;
			c /= 2;
			cut--;
			if ((cut > 0 && cut == current - 8) || cut < 0) break;
		}
		cut = current + 8;
		current = cut;
	}
	for (int j = 0; j < IMAX; j++) {
		*(n2 + j) = bit[j];
		bit[j] = bit[j] ^ *(n1 + j); //IV
	}
	ChangedStr(s1);
}
void ChangedStr(char *s) {
	int cnt = 0;
	int sum = 0;
	int num;
	for (int i = 0; i < IMAX; i++) {
		char c;
		int doub = 1;

		if (i % 8 == 7)doub = 1;
		else {
			for (int j =7-(i % 8); j > 0; j--) {
				doub *= 2;
			}
		}
		num = (8 * (cnt + 1) - 1) - (7-(i % 8));
		sum = sum + bit[num] * doub;
		//127�ʰ��� 0���� �����ϵ��� ������.
		if (i % 8 == 7) {
			c = sum % 128;
			*(s+cnt) = c;
			cnt++;
			sum = 0;
		}
	}
}
void select1(char ch) {

	switch (ch) {

	case '1':
		system("cls");
		input();
		GetIV1();
		system("cls");
		break;

	case '2':
		En(PB1, IV1, IV2);
		En(PB2, IV2, IV3);
		En(PB3, IV3, IV4);
		En2(PB4, IV4);
		system("cls");
		break;

	case '3':
		De(PB1, IV1, IV2);
		De(PB2, IV2, IV3);
		De(PB3, IV3, IV4);
		En2(PB4,IV4);
		system("cls");
		break;

	default:

		printf("�߸��� �Է�\n");

		break;

	}

	system("cls");

}