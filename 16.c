#include <stdio.h>

void upper_case_count(char arr[31]) {

    // ��������ʵ��ͳ�Ʋ������д��ĸ�����Ĺ���

    int i, cnt = 0;

    for (i = 0; i < 30; ++i) {

        if (arr[i] <= 'Z' && arr[i] >= 'A') ++cnt;

    }

    printf("%d\n",cnt);

}

void lower_case_count(char arr[31]) {

    // ��������ʵ��ͳ�Ʋ����Сд��ĸ�����Ĺ���

    int i, cnt = 0;

    for (i = 0; i < 30; ++i) {

        if (arr[i] <= 'z' && arr[i] >= 'a') ++cnt;

    }

    printf("%d\n",cnt);

}

void digit_count(char arr[31]) {

    // ��������ʵ��ͳ�Ʋ�������ָ����Ĺ���

    int i, cnt = 0;

    for (i = 0; i < 30; ++i) {

        if (arr[i] <= '9' && arr[i] >= '0') ++cnt;

    }

    printf("%d\n",cnt);

}

void space_count(char arr[31]) {

    // ��������ʵ��ͳ�Ʋ�����ո�����Ĺ���

    int i, cnt = 0;

    for (i = 0; i < 30; ++i) {

        if (arr[i] <= ' ') ++cnt;

    }

    printf("%d\n",cnt);

}

 

int main() {

    char string[31];

    int i;

    for (i = 0; i < 30; ++i) {

        scanf("%c", &string[i]);

    }

    upper_case_count(string);

    lower_case_count(string);

    digit_count(string);

    space_count(string);

    return 0;

    

}