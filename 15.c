#include <stdio.h>
//��������
 

int main() {

    int matrix[100][100];

    int m, n;

    int i, j;

    // ��������

    scanf("%d%d", &m, &n);

    for (i = 0; i < m; ++i) {

        for (j = 0; j < n; ++j) {

            scanf("%d", &matrix[i][j]);

        }

    }

    // ���巽������

    int direct[4][2] = {

        {0, 1}, {1, 0},

        {0, -1}, {-1, 0}

    };

    // (x, y) �������꣬k ������l ����ڼ�Ȧ

    int x, y, k, l;

    x = y = k = l = 0;

    while (1) {

        if (x != 0 || y != 0) printf(" ");

        printf("%d", matrix[x][y]);

        if (direct[k][0] != 0) {

            if (x + direct[k][0] >= m - l || x + direct[k][0] <= l) {

                ++k;

                if (k == 4) {

                    k = 0;

                    ++l;

                }

            }

        } else {

            if (y + direct[k][1] >= n - l || y + direct[k][1] < l) {

                ++k;

            }

        }

        x += direct[k][0];

        y += direct[k][1];

        if (direct[k][0] != 0 && (x >= m - l || x <= l)) break;

        if (direct[k][1] != 0 && (y >= n - l || y < l)) break;

    }

    return 0;

}