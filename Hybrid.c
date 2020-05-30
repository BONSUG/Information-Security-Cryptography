#include<stdio.h>
#include <windows.h>
#include <time.h>
#include<string.h>

#define MAX 150
int p, q, n, l, e, d,k; //k=세션키

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
	printf("\t\tRSA 프로그램\t\t\n\n");
	printf("1.초기화\t2.암호화\t3.복호화\t4.종료\n\n");
	printf("공개키(E = %d, N = %d) 개인키(D = %d, N = %d)\n\n", e, n, d,n);
	printf("P = %d		Q = %d		L = %d		K = %d\n",p, q, l,k);
	printf("\n선택 : ");
}

int LCM(int p1, int q1) { //최소공배수
	int temp;
	if (p1 < q1) {
		temp=q1;
		q1=p1;
		p1 = temp;
	}
	return (p1 * q1) / GCD(p1, q1);
}
int GCD(int p1, int q1) { //최대공약수
	if (q1 == 0) return p1;
	return GCD(q1, p1 % q1);
}
int GetDemicalNum() { //소수 생성
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
	k = rand() % 256;
}

void encryption() { //암호화
	char str[MAX];
	int arr[MAX];

	FILE* fp = NULL;
	fp = fopen("plain.txt", "r");
	if (fp == NULL) {
		printf("없는 파일입니다.");
		Sleep(2000);
		return;
	}
	fgets(str, MAX, fp); //파일의 내용을 읽어 str에 저장
	fclose(fp);
	
	//세션키 부호화
	int session[8] = { 0 };
	int m = k;
	for (int l = 7; l != -1; l--) {
		session[l] = m % 2;
		m /= 2;
	}
	//세션키 암호화
	int s = k;
	long long sum1=1;
	for (int j = 0; j < e; j++)
	{
		sum1 *= s;
		if (sum1 < n) continue;
		else sum1 %= n;
	}
	arr[0] = (int)sum1;
	
	//메세지 암호화
	int len = strlen(str);
	int sum;
	for (int i = 0; i < len; i++) {
		int temp1[8] = { 0 };
		sum = 0;
		char c = str[i];
		for (int l = 7; l != -1; l--) {
			temp1[l] = c % 2;
			c /= 2;
		}//한 글자씩 부호화
		for (int l = 7; l != -1; l--) {
			int doub = 1;
			temp1[l] = temp1[l] ^ session[l];//세션키와 XOR
			if (l == 7) sum += temp1[l];
			else {
				for (int j = 7-l; j > 0; j--) {
					doub *= 2;
				}
				sum += (temp1[l] * doub); // 2의 (7-l)승
			}
		}
		arr[i + 1] = sum;
	}
	

//암호화된 문장을 파일에 입력
	FILE* fp1 = NULL;
	fp1 = fopen("encryption.txt", "w");
	if (fp1 == NULL) {
		printf("없는 파일입니다.");
		Sleep(2000);
		return;
	}
	for (int i = 0; i < len+1; i++)
		fprintf(fp1, "%d\n", arr[i]);
	fclose(fp1);
	system("cls");
	printf("암호화 완료!");
	Sleep(1000);
}

void decryption() {
	char str2[MAX] = {'\0'};
	FILE* fp = NULL;
	int cnt=0;
	int arr2[MAX] = { 0 };
	fp = fopen("encryption.txt","r");
	if (fp == NULL) {
		printf("없는 파일입니다.");
		Sleep(2000);
		return;
	}

	else {
		while (!feof(fp)) {
			fscanf(fp, "%d", arr2 + cnt); //파일의 내용을 한 줄씩 읽어 arr2 정수배열에 저장
			cnt++;
		}
		fclose(fp);
	}
	int sk = arr2[0]; // 암호화된 세션키
	long long sum1 = 1;
	for (int j = 0; j < d; j++)
	{
		sum1 *= sk;
		if (sum1 < n) continue;
		else sum1 %= n;
	}
	int dsk = (int)sum1; //복호화된 세션키

	//세션키 부호화
	int session1[8] = { 0 };
	for (int l = 7; l != -1; l--) {
		session1[l] = dsk % 2;
		dsk /= 2;
	}

	int sum;
	for (int i = 1; i < cnt; i++) {
		int temp1[8] = { 0 };
		sum = 0;
		int num = arr2[i];
		for (int l = 7; l != -1; l--) {
			temp1[l] = num % 2;
			num /= 2;
		}//한 글자씩 부호화
		for (int l = 7; l != -1; l--) {
			int doub = 1;
			temp1[l] = temp1[l] ^ session1[l];//세션키와 XOR
			if (l == 7) sum += temp1[l];
			else {
				for (int j = 7 - l; j > 0; j--) {
					doub *= 2;
				}
				sum += (temp1[l] * doub); // 2의 (7-l)승
			}
		}
		str2[i-1] = (char)sum;
	}

	//복호화된 문장을 파일에 입력
	int len = strlen(str2);
	FILE* fp1 = NULL;
	fp1 = fopen("decryption.txt", "w");
	if (fp1 == NULL) {
		printf("없는 파일입니다.");
		Sleep(2000);
		return;
	}
	for (int i = 0; i < len-1; i++)
		fprintf(fp1, "%c", str2[i]);
	fclose(fp1);
	system("cls");
	printf("복호화 완료!");
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

		printf("잘못된 입력\n");

		break;

	}

	system("cls");

}