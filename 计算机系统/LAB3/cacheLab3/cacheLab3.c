// cacheLab3.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define M 1920
#define N 1080
long img1[N];
long img2[N];
int size = 30;
void Method3(long img[M][N])
{
    for (int i = 0; i < M - size; i += (size-2))//分块，30行*1080列
    {
        for (int i1 = i + 1; i1 < i + size - 1; i1++)
        {
            int i2 = i1 - 1;
            for (int j = 0; j < N; j+=4)
            {
                img1[j] = img[i2][j];
                img1[j + 1] = img[i2][j + 1];
                img1[j + 2] = img[i2][j + 2];
                img1[j + 3] = img[i2][j + 3];
                img2[j] = img[i1][j];
                img2[j + 1] = img[i1][j + 1];
                img2[j + 2] = img[i1][j + 2];
                img2[j + 3] = img[i1][j + 3];
            }
            for (int j = 1; j < N - 1; j += 2)
            {
                img[i1][j] = (img1[j] + img2[j - 1] + img2[j + 1] + img[i1 + 1][j]) >> 2;
                img[i1][j + 1] = (img1[j + 1] + img2[j] + img2[j + 2] + img[i1 + 1][j + 1]) >> 2;
            }
        }
    }
}
int main()
{
    static long img[M][N];
    srand((unsigned)time(NULL));
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            img[i][j] = rand() % 255;
        }
    }
    clock_t start = clock();
    for (int i = 0; i < 50; i++)
    {
        Method3(img);
    }
    clock_t end = clock();
    printf("%lf(ms)\n", 1.0*(end - start) / 50);
    return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
