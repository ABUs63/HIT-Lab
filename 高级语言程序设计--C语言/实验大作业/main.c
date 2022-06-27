#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 30

typedef struct data
{
    double avg;
    char number[N];//ѧ��
    char name[N];//����
    int standard[5];//����ѧ���õ�A,B,C,D,E������
    double data[8];//�ֱ�Ϊ������⡢�������ſΡ��������ܺ͡����ſγɼ�֮��
}DATA;

void Menu1();
void Menu2();
void Getscorestandard(DATA *p,int len);//ͳ��ѧ�����Ƴɼ��ȼ��ܺ����
void Getavg(DATA *p,int len,double avg[]);//����༶ÿ�ſγ�ƽ����
void Hsort(DATA *p,int len);//�����û�ѡ����гɼ���������
void Lsort(DATA *p,int len);//�����û�ѡ����гɼ���������
void Nasort(DATA *p,int len);//����ѧ����������
void Nusort(DATA *p,int len);//����ѧ��ѧ������
void Print(DATA *p,int len,double *avg);//��ӡ����
void NaSearch(DATA *p,int len,char *obj);//�������ֱ����
void NuSearch(DATA *p,int len,char *obj);//��ѧ�ŷֱ����
void VagueNuSearch(DATA *p,int len);//���ղ�����ѧ�Ų��Ҳ������ѯ���
int Otherstandard(DATA *op,DATA *p,int len);//�ó�����ѧ���������⣩�������е�����
void Quicksort(DATA *p,int low,int high);//���������ں��ݹ飩
int Getsortpos(DATA *p,int low,int high);//���������׼������

int main()
{
    int n = 0,choice = 0;
    double avg[9];
    char obj[N];
    FILE *p = NULL;
    DATA op ;
    Menu1();

    do{
        printf("�ж���ѧ���ɼ���Ҫ���в���(��಻����20)?\n");
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
        printf("ָ�봴��ʧ��\a\n");
        exit(1);//ָ�봴��ʧ��
    }
    p = fopen("scoredata.txt","r");
    if (p == NULL)
    {
        printf("�ļ���ʧ��\a\n");
        exit(2);//�ļ���ʧ��
    }

    for (int i = 0;i < n;i++)//��ȡ�ļ�����
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
    Getavg(px,n,avg);//ǰ������׼�����

    do{
        Menu2();
        printf("����ѡ��Ĺ������(���ڷ�Χ��Ĭ���˳�):\n");
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
            printf("��ѧ����������:%d\n",Otherstandard(&op,px,n));
        }
    }while(choice >= 1&&choice <= 8);

    printf("��лʹ�ñ�ϵͳ~~\n");
    fclose(p);//�ͷ�ָ�롢�ڴ�
    free(px);
    return 0;
}

void Menu1()
{
    printf(" ----------ѧ���ɼ�����ϵͳV7.0---------- \n");
    printf("|��ϵͳʵ�ֹ��ܣ�                        |\n");
    printf("|1.���ݴ��ı�����                        |\n");
    printf("|2.����ѧ��ƽ���ɼ�                      |\n");
    printf("|3.ͳ��ѧ���ɼ��ȼ�                      |\n");
    printf("|4.�������Ƴɼ��ܺͻ����Ƴɼ��ܺ�����    |\n");
    printf("|5.����ѧ�����������ֵ�˳������          |\n");
    printf("|6.����ѧ��ѧ�Ž�������                  |\n");
    printf("|7.��ѯĿ��������ѧ���ɼ�                |\n");
    printf("|8.��ѯĿ��ѧ�ŵ�ѧ���ɼ�                |\n");
    printf("|9.��ѯ������Ŀ��ѧ�ŵ�ѧ���ɼ�          |\n");
    printf("|10.�ó�����ѧ���������е�����           |\n");
    printf(" ---------------------------------------- \n");
}

void Menu2()
{
    printf(" ----------ѧ���ɼ�����ϵͳV7.0---------- \n");
    printf("|ѡ������ţ�                          |\n");
    printf("|1.���ճɼ��ܷ��ɸߵ�������              |\n");
    printf("|2.���ճɼ��ܷ��ɵ͵�������              |\n");
    printf("|3.������������                          |\n");
    printf("|4.����ѧ������                          |\n");
    printf("|5.����������ѯ                          |\n");
    printf("|6.����ѧ�Ų�ѯ                          |\n");
    printf("|7.���ղ�����ѧ�Ų�ѯ                    |\n");
    printf("|8.�ó�����ѧ���������е�����            |\n");
    printf("------------------------------------------\n");
}

void Getscorestandard(DATA *p,int len)//ͳ��������ѧ���ɼ��ȼ�����
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

void Getavg(DATA *p,int len,double avg[])//��������ѧ��ƽ���ɼ�
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

void Hsort(DATA *px,int len)//��������������
{
    int k = 0,m = 0,choice = 0;
    DATA temp;
    do{
        printf("1�����������������ܺ�����\n");
        printf("2�����������ܺ�����\n");
        scanf("%d",&choice);
        if (choice != 1&&choice != 2)
        {
            printf("\a���������ʾ��Ϣ\n");
        }
    }while(choice != 1&&choice != 2);//ֱ���û���Ҫ������ѡ��ֹͣ
    for (int i = 0;i < len-1;i++)
    {
        k = i;
        for (int j = i+1;j < len;j++)
        {
            switch (choice)//�����û���ͬѡ��ѡ���������
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
    printf("���ճɼ��ܺ���������\n");
}

void Lsort(DATA *px,int len)//��������������
{
    int k = 0,m = 0,choice = 0;
    DATA temp;
    do{
        printf("1�����������������ܺ�����\n");
        printf("2�����������ܺ�����\n");
        scanf("%d",&choice);
        if (choice != 1&&choice != 2)
        {
            printf("\a���������ʾ��Ϣ\n");
        }
    }while(choice != 1&&choice != 2);//ֱ���û���Ҫ������ѡ��ֹͣ
    for (int i = 0;i < len-1;i++)
    {
        k = i;
        for (int j = i+1;j < len;j++)
        {
            switch (choice)//�����û���ͬѡ��ѡ���������
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
    printf("���ճɼ��ܺ���������\n");
}

void Nasort(DATA *px,int len)//������������
{
    int k = 0,m = 0;
    DATA temp;
    printf("������������\n");
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

void Nusort(DATA *px,int len)//����ѧ������
{
    int k = 0,m = 0;
    DATA temp;
    printf("ѧ����������\n");
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

void Print(DATA *px,int len,double *avg)//��ӡ���
{
    printf("ѧ��\t\t����\t����\t��ѧ\tӢ��\t����\t��ѧ\t����\t����\t����\tƽ��\n");
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
    printf("�γ�ƽ��\t\t");
    for (int i = 0;i < 9;i++)
    {
        printf("%.2lf\t",*(avg+i));
    }
    printf("\n");
}

void NaSearch(DATA *p,int len,char *obj)//����������ѯѧ���ɼ�
{
    int i = 0,j = 0,flag = -1;
    printf("����Ŀ������\n");
    scanf("%s",obj);
    for (i = 0;i < len;i++)
    {
        flag = strcmp((p+i)->name,obj);
        if (flag == 0)
        {
            printf("�д�ѧ��,�����������\n");
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
        printf("û�и�ѧ��\n");
    }
}

void NuSearch(DATA *p,int len,char *obj)//����ѧ�Ų�ѯѧ���ɼ�
{
    int i = 0,j = 0,flag = -1;
    printf("����Ŀ��ѧ��\n");
    scanf("%s",obj);
    for (i = 0;i < len;i++)
    {
        flag = strcmp((p+i)->number,obj);
        if (flag == 0)
        {
            printf("�д�ѧ��,�����������\n");
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
        printf("û�и�ѧ��\n");
    }
}

void VagueNuSearch(DATA *p,int len)//ģ��ƥ�䣬��ѯ������ѧ�ŵ�ѧ���ɼ�
{
    char obj[N];
    int count = 0;
    printf("\n������ҵĲ�����ѧ��Ƭ��\n");
    scanf("%s",obj);
    Nusort(p,len);
    for (int i = 0;i < len;i++)
    {
        if (strstr((p+i)->number,obj) != NULL)
        {
            count++;
            printf("��%d�����:\n",count);
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
        printf("û�а�����Ƭ�ε�ѧ�ŵ�ѧ��\n");
    }
}

int Otherstandard(DATA *op,DATA *p,int len)//��ȡ������ѧ���������е�����
{
    int i = 0;
    printf("�����ѧ����ѧ�š��������ɼ�:\n");
    scanf("%s",op->number);
    scanf("%s",op->name);
    for (i = 0;i < 6;i++)
    {
        do{
            scanf("%lf",&op->data[i]);
            if (op->data[i]<0||op->data[i]>100)
            {
                printf("\a������ĳɼ������Ϲ淶�����������������\n");
            }
        }while(op->data[i]<0||op->data[i]>100);//�û�����Ϸ��Լ��
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

int Getsortpos(DATA *p,int low,int high)//����������̲��һ�û�׼����λ��
{
    DATA *standard = (p+low);
    while(low < high)//���������½�С���Ͻ�����
    {
        while (low < high && (p+high)->data[7] >= standard->data[7])//��׼λ�ò���Ҫ���Ͻ����ݽ���
        {
            high--;
        }
        if (low < high)
        {
            *(p+low) = *(p+high);
        }
        while (low < high && (p+low)->data[7] <= standard->data[7])//��׼λ�ò���Ҫ���½����ݽ���
        {
            low++;
        }
        if (low < high)
        {
            *(p+high) = *(p+low);
        }
    }
    *(p+low) = *standard;//����׼���ݷ����׼Ӧ��λ�ã���ʱ���½����
    return low;//Ҳ�ɷ���high
}

void Quicksort(DATA *p,int low,int high)//���������ں��ݹ飩����ܣ�
{
    int pos = 0;
    if (low > high)//����Ҫ��������
    {
        return ;
    }
    else
    {
        pos = Getsortpos(p,low,high);
    }
    Quicksort(p,low,pos-1);//�Ի�׼����������
    Quicksort(p,pos+1,high);//�Ի�׼����������
}
