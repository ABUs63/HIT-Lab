#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 30

typedef struct data
{
    double avg;
    char number[N];//学号
    char name[N];//姓名
    int standard[5];//代表学生得到A,B,C,D,E的数量
    double data[8];//分别为语、数、外、其他三门课、语数外总和、六门课成绩之和
}DATA;

void Menu1();
void Menu2();
void Getscorestandard(DATA *p,int len);//统计学生六科成绩等级总和情况
void Getavg(DATA *p,int len,double avg[]);//计算班级每门课程平均分
void Hsort(DATA *p,int len);//按照用户选择进行成绩降序排序
void Lsort(DATA *p,int len);//按照用户选择进行成绩升序排序
void Nasort(DATA *p,int len);//按照学生姓名排序
void Nusort(DATA *p,int len);//按照学生学号排序
void Print(DATA *p,int len,double *avg);//打印数据
void NaSearch(DATA *p,int len,char *obj);//按姓名分别查找
void NuSearch(DATA *p,int len,char *obj);//按学号分别查找
void VagueNuSearch(DATA *p,int len);//按照不完整学号查找并输出查询结果
int Otherstandard(DATA *op,DATA *p,int len);//得出其他学生（样本外）在样本中的排名
void Quicksort(DATA *p,int low,int high);//快速排序（内含递归）
int Getsortpos(DATA *p,int low,int high);//快速排序的准备数据

int main()
{
    int n = 0,choice = 0;
    double avg[9];
    char obj[N];
    FILE *p = NULL;
    DATA op ;
    Menu1();

    do{
        printf("有多少学生成绩需要进行操作(最多不超过20)?\n");
        scanf("%d",&n);
        if(n <= 0||n >20)
        {
            printf("\a");
        }
    }while(n <= 0||n > 20);

    DATA *px = NULL;
    px = (DATA *)malloc(n*sizeof(DATA));
    if (px == NULL)
    {
        printf("指针创建失败\a\n");
        exit(1);//指针创建失败
    }
    p = fopen("scoredata.txt","r");
    if (p == NULL)
    {
        printf("文件打开失败\a\n");
        exit(2);//文件打开失败
    }

    for (int i = 0;i < n;i++)//读取文件数据
    {
        fscanf(p,"%s",(px+i)->number);
        fscanf(p,"%s",(px+i)->name);
        for (int j = 0;j < 6;j++)
        {
            fscanf(p,"%lf",&(px+i)->data[j]);
        }
        (px+i)->data[6] = (px+i)->data[0] + (px+i)->data[1] + (px+i)->data[2];
        (px+i)->data[7] = (px+i)->data[6] + (px+i)->data[4] + (px+i)->data[5] + (px+i)->data[3];
        (px+i)->avg = ((px+i)->data[7])/6;
    }
    Getscorestandard(px,n);
    Getavg(px,n,avg);//前期数据准备完成

    do{
        Menu2();
        printf("输入选择的功能序号(不在范围内默认退出):\n");
        scanf("%d",&choice);
        if (choice == 1)
        {
            Hsort(px,n);
            Print(px,n,avg);
        }
        else if (choice == 2)
        {
            Lsort(px,n);
            Print(px,n,avg);
        }
        else if (choice == 3)
        {
            Nasort(px,n);
            Print(px,n,avg);
        }
        else if (choice == 4)
        {
            Nusort(px,n);
            Print(px,n,avg);
        }
        else if (choice == 5)
        {
            NaSearch(px,n,obj);
        }
        else if (choice == 6)
        {
            NuSearch(px,n,obj);
        }
        else if (choice == 7)
        {
            VagueNuSearch(px,n);
        }
        else if (choice == 8)
        {
            printf("该学生的排名是:%d\n",Otherstandard(&op,px,n));
        }
    }while(choice >= 1&&choice <= 8);

    printf("感谢使用本系统~~\n");
    fclose(p);//释放指针、内存
    free(px);
    return 0;
}

void Menu1()
{
    printf(" ----------学生成绩管理系统V7.0---------- \n");
    printf("|本系统实现功能：                        |\n");
    printf("|1.数据从文本读入                        |\n");
    printf("|2.计算学生平均成绩                      |\n");
    printf("|3.统计学生成绩等级                      |\n");
    printf("|4.按照主科成绩总和或六科成绩总和排序    |\n");
    printf("|5.按照学生姓名进行字典顺序排序          |\n");
    printf("|6.按照学生学号进行排序                  |\n");
    printf("|7.查询目标姓名的学生成绩                |\n");
    printf("|8.查询目标学号的学生成绩                |\n");
    printf("|9.查询不完整目标学号的学生成绩          |\n");
    printf("|10.得出其他学生在样本中的排名           |\n");
    printf(" ---------------------------------------- \n");
}

void Menu2()
{
    printf(" ----------学生成绩管理系统V7.0---------- \n");
    printf("|选择功能序号：                          |\n");
    printf("|1.按照成绩总分由高到低排序              |\n");
    printf("|2.按照成绩总分由低到高排序              |\n");
    printf("|3.按照姓名排序                          |\n");
    printf("|4.按照学号排序                          |\n");
    printf("|5.按照姓名查询                          |\n");
    printf("|6.按照学号查询                          |\n");
    printf("|7.按照不完整学号查询                    |\n");
    printf("|8.得出其他学生在样本中的排名            |\n");
    printf("------------------------------------------\n");
}

void Getscorestandard(DATA *p,int len)//统计样本中学生成绩等级个数
{
    int i = 0,j = 0,temp = 0;
    for (i = 0;i < len;i++)
    {
        for (j = 0;j < 5;j++)
        {
            (p+i)->standard[j]=0;
        }
        for (j = 0;j < 6;j++)
        {
            temp = (int)((p+i)->data[j])/10;
            switch (temp)
            {
                case 10:
                    {
                        (p+i)->standard[0]++;
                        break;
                    }
                case 9:
                    {
                        (p+i)->standard[0]++;
                        break;
                    }
                case 8:
                    {
                        (p+i)->standard[1]++;
                        break;
                    }
                case 7:
                    {
                        (p+i)->standard[2]++;
                        break;
                    }
                case 6:
                    {
                        (p+i)->standard[3]++;
                        break;
                    }
                case 5:
                    {
                        (p+i)->standard[4]++;
                        break;
                    }
                case 4:
                    {
                        (p+i)->standard[4]++;
                        break;
                    }
                case 3:
                    {
                        (p+i)->standard[4]++;
                        break;
                    }
                case 2:
                    {
                        (p+i)->standard[4]++;
                        break;
                    }
                case 1:
                    {
                        (p+i)->standard[4]++;
                        break;
                    }
                case 0:
                    {
                        (p+i)->standard[4]++;
                        break;
                    }
                default:
                    break;
            }
        }
    }
}

void Getavg(DATA *p,int len,double avg[])//计算样本学科平均成绩
{
    int i = 0,j = 0;
    double sum = 0.0;
    for (i = 0;i < 9;i++)
    {
        sum = 0.0;
        for (j = 0;j < len;j++)
        {
            sum = sum + (double)(p+j)->data[i];
        }
        avg[i] = (sum)/len;
    }
}

void Hsort(DATA *px,int len)//交换法降序排序
{
    int k = 0,m = 0,choice = 0;
    DATA temp;
    do{
        printf("1代表按照语数外三科总和排序\n");
        printf("2代表按照六科总和排序\n");
        scanf("%d",&choice);
        if (choice != 1&&choice != 2)
        {
            printf("\a请认真读提示信息\n");
        }
    }while(choice != 1&&choice != 2);//直到用户按要求输入选择停止
    for (int i = 0;i < len-1;i++)
    {
        k = i;
        for (int j = i+1;j < len;j++)
        {
            switch (choice)//根据用户不同选择，选择排序对象
            {
                case 1:
                    {
                        m = 6;
                        break;
                    }
                case 2:
                    {
                        m = 7;
                        break;
                    }
                default:
                    {
                        printf("error\a\n");
                        break;
                    }
            }
            if ((int)(px+k)->data[m] < (int)(px+j)->data[m])
            {
                k = j;
            }
        }
        if (k != i)
        {
            temp = *(px+i);
            *(px+i) = *(px+k);
            *(px+k) = temp;
        }
    }
    printf("按照成绩总和排序如下\n");
}

void Lsort(DATA *px,int len)//交换法升序排序
{
    int k = 0,m = 0,choice = 0;
    DATA temp;
    do{
        printf("1代表按照语数外三科总和排序\n");
        printf("2代表按照六科总和排序\n");
        scanf("%d",&choice);
        if (choice != 1&&choice != 2)
        {
            printf("\a请认真读提示信息\n");
        }
    }while(choice != 1&&choice != 2);//直到用户按要求输入选择停止
    for (int i = 0;i < len-1;i++)
    {
        k = i;
        for (int j = i+1;j < len;j++)
        {
            switch (choice)//根据用户不同选择，选择排序对象
            {
                case 1:
                    {
                        m = 6;
                        break;
                    }
                case 2:
                    {
                        m = 7;
                        break;
                    }
                default:
                    {
                        printf("error\n");
                        break;
                    }
            }
            if ((int)(px+k)->data[m] > (int)(px+j)->data[m])
            {
                k = j;
            }
        }
        if (k != i)
        {
            temp = *(px+i);
            *(px+i) = *(px+k);
            *(px+k) = temp;
        }
    }
    printf("按照成绩总和排序如下\n");
}

void Nasort(DATA *px,int len)//按照姓名排序
{
    int k = 0,m = 0;
    DATA temp;
    printf("姓名排序如下\n");
    for (int i = 0;i < len-1;i++)
    {
        k = i;
        for (int j = i+1;j < len;j++)
        {
            m = strcmp((px+k)->name,(px+j)->name);
            if (m > 0)
            {
                k = j;
            }
        }
        if (k != i)
        {
            temp = *(px+i);
            *(px+i) = *(px+k);
            *(px+k) = temp;
        }
    }
}

void Nusort(DATA *px,int len)//按照学号排序
{
    int k = 0,m = 0;
    DATA temp;
    printf("学号排序如下\n");
    for (int i = 0;i < len-1;i++)
    {
        k = i;
        for (int j = i+1;j < len;j++)
        {
            m = strcmp((px+k)->number,(px+j)->number);
            if (m > 0)
            {
                k = j;
            }
        }
        if (k != i)
        {
            temp = *(px+i);
            *(px+i) = *(px+k);
            *(px+k) = temp;
        }
    }
}

void Print(DATA *px,int len,double *avg)//打印结果
{
    printf("学号\t\t姓名\t语文\t数学\t英语\t物理\t化学\t生物\t三科\t六科\t平均\n");
    for (int i = 0;i < len;i++)
    {
        printf("%s\t",(px+i)->number);
        printf("%s\t",(px+i)->name);
        for (int j = 0;j < 8;j++)
        {
            printf("%.0lf\t",(px+i)->data[j]);
        }
        printf("%.2lf\t",(px+i-1)->data[8]);
        printf("A:%d,B:%d,C:%d,D:%d,E:%d\n",(px+i)->standard[0],(px+i)->standard[1],(px+i)->standard[2],(px+i)->standard[3],(px+i)->standard[4]);
    }
    printf("课程平均\t\t");
    for (int i = 0;i < 9;i++)
    {
        printf("%.2lf\t",*(avg+i));
    }
    printf("\n");
}

void NaSearch(DATA *p,int len,char *obj)//按照姓名查询学生成绩
{
    int i = 0,j = 0,flag = -1;
    printf("输入目标姓名\n");
    scanf("%s",obj);
    for (i = 0;i < len;i++)
    {
        flag = strcmp((p+i)->name,obj);
        if (flag == 0)
        {
            printf("有此学生,相关数据如下\n");
            printf("%s\t",(p+i)->number);
            printf("%s\t",(p+i)->name);
            for (j = 0;j < 8;j++)
            {
                printf("%.0lf\t",(p+i)->data[j]);
            }
            printf("\n");
            break;
        }
    }
    if (flag != 0)
    {
        printf("没有该学生\n");
    }
}

void NuSearch(DATA *p,int len,char *obj)//按照学号查询学生成绩
{
    int i = 0,j = 0,flag = -1;
    printf("输入目标学号\n");
    scanf("%s",obj);
    for (i = 0;i < len;i++)
    {
        flag = strcmp((p+i)->number,obj);
        if (flag == 0)
        {
            printf("有此学生,相关数据如下\n");
            printf("%s\t",(p+i)->number);
            printf("%s\t",(p+i)->name);
            for (j = 0;j < 8;j++)
            {

                printf("%.0lf\t",(p+i)->data[j]);
            }
            printf("\n");
            break;
        }
    }
    if (flag != 0)
    {
        printf("没有该学生\n");
    }
}

void VagueNuSearch(DATA *p,int len)//模糊匹配，查询不完整学号的学生成绩
{
    char obj[N];
    int count = 0;
    printf("\n输入查找的不完整学号片段\n");
    scanf("%s",obj);
    Nusort(p,len);
    for (int i = 0;i < len;i++)
    {
        if (strstr((p+i)->number,obj) != NULL)
        {
            count++;
            printf("第%d个结果:\n",count);
            printf("%s\t",(p+i)->number);
            printf("%s\t",(p+i)->name);
            for (int j = 0;j < 8;j++)
            {
                printf("%.0lf\t",(p+i)->data[j]);
            }
            printf("\n");
        }
    }
    if (count == 0)
    {
        printf("没有包含该片段的学号的学生\n");
    }
}

int Otherstandard(DATA *op,DATA *p,int len)//获取样本外学生在样本中的排名
{
    int i = 0;
    printf("输入该学生的学号、姓名、成绩:\n");
    scanf("%s",op->number);
    scanf("%s",op->name);
    for (i = 0;i < 6;i++)
    {
        do{
            scanf("%lf",&op->data[i]);
            if (op->data[i]<0||op->data[i]>100)
            {
                printf("\a您输入的成绩不符合规范，请重新输入该数据\n");
            }
        }while(op->data[i]<0||op->data[i]>100);//用户输入合法性检查
    }
    op->data[6] = op->data[0] + op->data[1] + op->data[2];
    op->data[7] = op->data[6] + op->data[4] + op->data[5] + op->data[3];

    Quicksort(p,0,len-1);

    for (i = len-1;i > 0 ;i--)
    {
        if ((int)op->data[7] >= (int)(p+len-1)->data[7])
        {
            return 1;
        }
        else if ((int)op->data[7] <= (int)(p+0)->data[7])
        {
            return len+1;
        }
        else if ((int)op->data[7] <= (int)(p+i)->data[7] && (int)op->data[7] >= (int)(p+i-1)->data[7])
        {
            break;
        }
    }
    return len-i+1;
}

int Getsortpos(DATA *p,int low,int high)//快速排序过程并且获得基准数据位置
{
    DATA *standard = (p+low);
    while(low < high)//控制仍在下界小于上界排序
    {
        while (low < high && (p+high)->data[7] >= standard->data[7])//基准位置不需要和上界数据交换
        {
            high--;
        }
        if (low < high)
        {
            *(p+low) = *(p+high);
        }
        while (low < high && (p+low)->data[7] <= standard->data[7])//基准位置不需要和下界数据交换
        {
            low++;
        }
        if (low < high)
        {
            *(p+high) = *(p+low);
        }
    }
    *(p+low) = *standard;//将基准数据放入基准应在位置，此时上下界相等
    return low;//也可返回high
}

void Quicksort(DATA *p,int low,int high)//快速排序（内含递归）（框架）
{
    int pos = 0;
    if (low > high)//不需要继续排序
    {
        return ;
    }
    else
    {
        pos = Getsortpos(p,low,high);
    }
    Quicksort(p,low,pos-1);//对基准左区间排序
    Quicksort(p,pos+1,high);//对基准右区间排序
}
