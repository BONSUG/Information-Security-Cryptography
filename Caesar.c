#include <stdio.h>

#include <windows.h>

#define MAX 100



char str[MAX];
static int n;

void intro();

void caesar(char ch);



int main() {

	char ch;
	while (1) {

		intro();

		ch = getchar();

		if (ch == '4') break;

		caesar(ch);

	}

	return 0;



}



void intro() {
	printf("\t\t시저 암호 프로그램\t\t\n\n");
	printf("1.문장 입력\t2.암호화\t3.복호화\t4.종료\n");
	printf("\n\n결과 : %s", str);
	printf("\n\n키 : %d", n);
	printf("\n\n선택 : ");



}

void caesar(char ch) {

	switch (ch) {

	case '1':

		system("cls");

		printf("문장을 입력하시오.\n:");

		getchar();
		fgets(str, MAX, stdin);

		printf("\n키값을 입력하시오\n:");
		scanf_s("%d", &n);
		system("cls");

		break;

	case '2':

		for (int i = 0; i < MAX; i++) {

			if (str[i] >= 'a' && str[i] <= 'z')

				str[i] = (str[i] - 'a' + n) % 26 + 'A';

			else if (str[i] >= 'A' && str[i] <= 'Z')

				str[i] = (str[i] - 'A' + n) % 26 + 'a';

		}

		break;

	case '3':

		for (int i = 0; i < MAX; i++) {

			if (str[i] >= 'A' && str[i] <= 'Z') {
				str[i] = str[i] - 'A' - n;
				if (str[i] < 0) str[i] = (str[i] + 26) % 26 + 'a';
				else str[i] = str[i] % 26 + 'a';
			}
			
			else if (str[i] >= 'a' && str[i] <= 'z') {
				str[i] = str[i] - 'a' - n;
				if (str[i] < 0) str[i] = (str[i] + 26) % 26 + 'A';
				else str[i] = str[i] % 26 + 'A';
			}
		}

		break;

	default:

		printf("잘못된 입력\n");

		break;

	}

	system("cls");

}