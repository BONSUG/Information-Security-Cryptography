#include<stdio.h>
#include <windows.h>
#include <time.h>
#include<string.h>

#define MAX 150
int p, q, n, l, e, d,k; //k=����Ű

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
	printf("P = %d		Q = %d		L = %d		K = %d\n",p, q, l,k);
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
	k = rand() % 256;
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
	
	//����Ű ��ȣȭ
	int session[8] = { 0 };
	int m = k;
	for (int l = 7; l != -1; l--) {
		session[l] = m % 2;
		m /= 2;
	}
	//����Ű ��ȣȭ
	int s = k;
	long long sum1=1;
	for (int j = 0; j < e; j++)
	{
		sum1 *= s;
		if (sum1 < n) continue;
		else sum1 %= n;
	}
	arr[0] = (int)sum1;
	
	//�޼��� ��ȣȭ
	int len = strlen(str);
	int sum;
	for (int i = 0; i < len; i++) {
		int temp1[8] = { 0 };
		sum = 0;
		char c = str[i];
		for (int l = 7; l != -1; l--) {
			temp1[l] = c % 2;
			c /= 2;
		}//�� ���ھ� ��ȣȭ
		for (int l = 7; l != -1; l--) {
			int doub = 1;
			temp1[l] = temp1[l] ^ session[l];//����Ű�� XOR
			if (l == 7) sum += temp1[l];
			else {
				for (int j = 7-l; j > 0; j--) {
					doub *= 2;
				}
				sum += (temp1[l] * doub); // 2�� (7-l)��
			}
		}
		arr[i + 1] = sum;
	}
	

//��ȣȭ�� ������ ���Ͽ� �Է�
	FILE* fp1 = NULL;
	fp1 = fopen("encryption.txt", "w");
	if (fp1 == NULL) {
		printf("���� �����Դϴ�.");
		Sleep(2000);
		return;
	}
	for (int i = 0; i < len+1; i++)
		fprintf(fp1, "%d\n", arr[i]);
	fclose(fp1);
	system("cls");
	printf("��ȣȭ �Ϸ�!");
	Sleep(1000);
}

void decryption() {
	char str2[MAX] = {'\0'};
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
	int sk = arr2[0]; // ��ȣȭ�� ����Ű
	long long sum1 = 1;
	for (int j = 0; j < d; j++)
	{
		sum1 *= sk;
		if (sum1 < n) continue;
		else sum1 %= n;
	}
	int dsk = (int)sum1; //��ȣȭ�� ����Ű

	//����Ű ��ȣȭ
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
		}//�� ���ھ� ��ȣȭ
		for (int l = 7; l != -1; l--) {
			int doub = 1;
			temp1[l] = temp1[l] ^ session1[l];//����Ű�� XOR
			if (l == 7) sum += temp1[l];
			else {
				for (int j = 7 - l; j > 0; j--) {
					doub *= 2;
				}
				sum += (temp1[l] * doub); // 2�� (7-l)��
			}
		}
		str2[i-1] = (char)sum;
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
	for (int i = 0; i < len-1; i++)
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