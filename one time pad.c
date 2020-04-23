#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>

#define MAX 100
#define MAX2 1000

char str[MAX];
int bits[MAX2];
int current_key[MAX2];

int cut;
int current;


void intro();
void ChangeToBit();
void PrintBit_OR_Key(int* n);
void select1(char);
void GetKey();
void En_Decryption();
void ChangedStr();


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
	printf("\t\t일회용 패드 프로그램\t\t\n\n");
	printf("1.문장 입력\t2.암호화\t3.복호화\t4.종료\n");
	printf("\n\n문장\n\n\t%s", str);
	printf("\n\n결과    : ");
	PrintBit_OR_Key(bits);
	printf("\n\n현재 키 : ");
	PrintBit_OR_Key(current_key);
	printf("\n\n선택 : ");
}
void PrintBit_OR_Key(int *n) {
	for (int i = 0; i < current - 7; i++) {
		printf("%d", *(n+i));
		if (i % 8 == 7 && i != (current - 8)) printf(" / ");
	}
}

void ChangeToBit() {
	for (int j = 0; j < MAX2; j++) {
		bits[j] = 0;
	}
	cut = 7;
	current = cut;
	getchar();
	printf("문장 입력 : ");
	fgets(str, MAX, stdin);

	int len = strlen(str);
	for (int i = 0; i < len - 1; i++)
	{
		char c = str[i];
		while (1) {
			bits[cut] = c % 2;
			c /= 2;
			cut--;
			if ((cut > 0 && cut == current - 8) || cut < 0) break;
		}
		cut = current + 8;
		current = cut;
	}
}
void GetKey() {
	srand((unsigned)time(NULL));
	int length = strlen(str);
	for (int j = 0; j < MAX2; j++) {
		current_key[j] = 0;
	}
	cut = 7;
	current = cut;
	for (int i = 0; i < length - 1; i++)
	{
		int n = rand() % 256;
		while (1) {
			current_key[cut] = n % 2;
			n /= 2;
			cut--;
			if ((cut > 0 && cut == current - 8) || cut < 0) break;
		}
		cut = current + 8;
		current = cut;
	}

}

void En_Decryption() {
	int Changed[MAX2] = { 0 };
	for (int i = 0; i < current - 7; i++) {
		Changed[i] = bits[i] ^ current_key[i];
		bits[i] = Changed[i];
	}
}
void ChangedStr() {
	int cnt = 0;
	int sum = 0;
	int num;
	for (int i = 0; i < current - 7; i++) {
		char c;
		int doub = 1;

		if (i % 8 == 7)doub = 1;
		else {
			for (int j = (i % 8); j > 0; j--) {
				doub *= 2;
			}
		}
		num = (8 * (cnt + 1) - 1) - (i % 8);//8*cnt+7-(i%8)
		sum = sum + bits[num] * doub;
		//127초과시 0부터 시작하도록 설계함.
		if (i % 8 == 7) {
			c = sum % 128;
			str[cnt] = c;
			cnt++;
			sum = 0;
		}
	}
}
void select1(char ch) {

	switch (ch) {

	case '1':

		system("cls");
		ChangeToBit();
		GetKey();
		system("cls");
		break;

	case '2':
		En_Decryption();
		ChangedStr();
		system("cls");
		break;

	case '3':
		En_Decryption();
		ChangedStr();
		system("cls");
		break;

	default:

		printf("잘못된 입력\n");

		break;

	}

	system("cls");

}