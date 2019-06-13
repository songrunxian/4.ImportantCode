#include <stdio.h>

void upper_case_count(char arr[31]) {

    // 请在下面实现统计并输出大写字母个数的功能

    int i, cnt = 0;

    for (i = 0; i < 30; ++i) {

        if (arr[i] <= 'Z' && arr[i] >= 'A') ++cnt;

    }

    printf("%d\n",cnt);

}

void lower_case_count(char arr[31]) {

    // 请在下面实现统计并输出小写字母个数的功能

    int i, cnt = 0;

    for (i = 0; i < 30; ++i) {

        if (arr[i] <= 'z' && arr[i] >= 'a') ++cnt;

    }

    printf("%d\n",cnt);

}

void digit_count(char arr[31]) {

    // 请在下面实现统计并输出数字个数的功能

    int i, cnt = 0;

    for (i = 0; i < 30; ++i) {

        if (arr[i] <= '9' && arr[i] >= '0') ++cnt;

    }

    printf("%d\n",cnt);

}

void space_count(char arr[31]) {

    // 请在下面实现统计并输出空格个数的功能

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