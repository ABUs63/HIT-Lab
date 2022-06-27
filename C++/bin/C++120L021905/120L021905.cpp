#include <iostream>
#include <iomanip>
#include <cstring>
#include <stdlib.h>
#define N 100

using namespace std;

typedef struct data//�ṹ�嶨��
{
    char number[N];//ѧ��
    char name[N];//����
    double data[8];//�ֱ�Ϊ������⡢�������ſΡ��������ܺ͡����ſγɼ�֮��
    int standard[5];//����ѧ���õ�A,B,C,D,E������
    double avg;
}DATA;

void Login(const string &usename,const string &password);//�ɼ�����ϵͳ����Ա��¼
void Menu1();//ϵͳ���ܲ˵�
void Menu2();//�������ܲ˵�
void Getpersonal(DATA *p,int len);//�Զ���ȡ�����ܳɼ���ƽ���ɼ�
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
    int num = 0,choice = 0;
    double avg[9];
    char obj[N];
    const string usename = "Lang",password = "123456";//����Ա��Ϣ
    DATA op;
    DATA stu[10]={{"120L026601","������",80,90,60,70,88,95},{"120L026602","������",91,85,99,73,78,90},
    {"120L026603","��÷÷",93,80,100,75,86,92},{"120L026604","��ǿ",51,63,73,58,59,70},{"120L026605","�½���",88,70,83,55,57,86},
    {"120L026606","����",84,99,70,86,88,93},{"120L026607","����",99,95,98,86,88,96},{"120L026608","����",100,93,88,77,62,87},
    {"120L026609","���Ƶ�",100,100,100,100,100,100},{"120L026610","MC����",85,88,97,87,98,99}};
    cout << "��ȷ���û���:Lang\t��ȷ������:123456" << endl;
    Login(usename,password);
    Menu1();
    do{
        cout << "�����������д�ǰ���������������.(������10��)" << endl;
        cin >> num;
        if(num <= 0||num > 10)
        {
            cout << '\a';
        }
    }while(num > 10||num <= 0);
    DATA *p = &stu[0];
    Getscorestandard(p,num);//ͳ�Ƴɼ��ȼ�
    Getavg(p,num,avg);//����ɼ�ƽ��ֵ
    Getpersonal(p,num);//�������ƽ���ɼ����ܳɼ�
    do{
        Menu2();
        cout << "����ѡ��Ĺ������(���ڷ�Χ��Ĭ���˳�):\n";
        cin >> choice;
        if (choice == 1)
        {
            Hsort(p,num);
            Print(p,num,avg);
        }
        else if (choice == 2)
        {
            Lsort(p,num);
            Print(p,num,avg);
        }
        else if (choice == 3)
        {
            Nasort(p,num);
            Print(p,num,avg);
        }
        else if (choice == 4)
        {
            Nusort(p,num);
            Print(p,num,avg);
        }
        else if (choice == 5)
        {
            NaSearch(p,num,obj);
        }
        else if (choice == 6)
        {
            NuSearch(p,num,obj);
        }
        else if (choice == 7)
        {
            VagueNuSearch(p,num);
        }
        else if (choice == 8)
        {
            cout << "��ѧ����������:" << Otherstandard(&op,p,num) << endl;
        }
    }while(choice >= 1 && choice <= 8);

    cout << "��лʹ�ñ�ϵͳ~~\n";
    return 0;
}
void Login(const string &usename,const string &password)
{
    int tries = 1;//���Դ���
    string tryusename,trypassword;
    cout << "�����������û�����" << endl;
    cout << "�������������û����Ļ��ᣡ" << endl;
    do{
        if(tries == 4)
        {
            cout << "���Ļ����ù⣬���Ժ����ԣ�" << endl;
            exit(1);//�����þ�
        }
        cin >> tryusename;
        if(tryusename.compare(usename) != 0)//�жϸ��û��Ƿ���Ȩ��
        {
            cout << '\a' << "����Ȩ�ޣ������³����û�����(ʣ�����" << (3-tries) << "�Σ�)"<<endl;
            tries++;
        }
        else
        {
            cout << "����������������룡(�������λ���)" << endl;
            break;
        }
    }while(1);
    tries = 1;//���ó��Դ���
    while(tries <= 3)
    {
        cin >> trypassword;
        if(trypassword.compare(password) == 0)//�ж������Ƿ���ȷ
        {
            cout << "��ϲ!��¼�ɹ�" << endl;
            return;
        }
        else
        {
            cout << '\a' << "������������³��ԣ�(ʣ�����" << (3-tries) << "�Σ�)" << endl;
            tries++;
        }
    }
    cout<<"���Ļ����ù⣬���Ժ����ԣ�"<<endl;
    exit(1);
}
void Menu1()
{
    cout<<" ----------ѧ���ɼ�����ϵͳMAX----------- "<<endl;
    cout<<"|��ϵͳʵ�ֹ��ܣ�                        |"<<endl;
    cout<<"|1.����ѧ��ƽ���ɼ�                      |"<<endl;
    cout<<"|2.ͳ��ѧ���ɼ��ȼ�                      |"<<endl;
    cout<<"|3.�������Ƴɼ��ܺͻ����Ƴɼ��ܺ�����    |"<<endl;
    cout<<"|4.����ѧ�����������ֵ�˳������          |"<<endl;
    cout<<"|5.����ѧ��ѧ�Ž�������                  |"<<endl;
    cout<<"|6.��ѯĿ��������ѧ���ɼ�                |"<<endl;
    cout<<"|7.��ѯĿ��ѧ�ŵ�ѧ���ɼ�                |"<<endl;
    cout<<"|8.��ѯ������Ŀ��ѧ�ŵ�ѧ���ɼ�          |"<<endl;
    cout<<"|9.�ó�����ѧ���������е�����            |"<<endl;
    cout<<" ---------------------------------------- "<<endl;
}
void Menu2()
{
    cout<<" ----------ѧ���ɼ�����ϵͳMAX----------- \n";
    cout<<"|ѡ������ţ�                          |\n";
    cout<<"|1.���ճɼ��ܷ��ɸߵ�������              |\n";
    cout<<"|2.���ճɼ��ܷ��ɵ͵�������              |\n";
    cout<<"|3.������������                          |\n";
    cout<<"|4.����ѧ������                          |\n";
    cout<<"|5.����������ѯ                          |\n";
    cout<<"|6.����ѧ�Ų�ѯ                          |\n";
    cout<<"|7.���ղ�����ѧ�Ų�ѯ                    |\n";
    cout<<"|8.�ó�����ѧ���������е�����            |\n";
    cout<<"------------------------------------------\n";
}
void Getpersonal(DATA *p,int len)//��������ܳɼ���ƽ���ɼ�
{
    int i = 0,j = 0;
    for (i = 0;i < len;i++)
    {
        (p+i)->data[6] = 0;
        (p+i)->data[7] = 0;
        for(j = 0;j < 3;j++)
        {
            (p+i)->data[6] += (p+i)->data[j];
        }
        for(j = 3;j < 7;j++)
        {
            (p+i)->data[7] += (p+i)->data[j];
        }
        (p+i)->avg = (p+i)->data[7]/6;
    }
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
            sum = sum + (p+j)->data[i];
        }
        avg[i] = (sum)/len;
    }
}
void Hsort(DATA *px,int len)//��������������
{
    int k = 0,m = 0,choice = 0;
    DATA temp;
    do{
        cout << "1�����������������ܺ�����\n";
        cout << "2�����������ܺ�����\n";
        cin >> choice;
        if (choice != 1&&choice != 2)
        {
            cout << "\a���������ʾ��Ϣ\n";
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
                        cout << "error\a\n";
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
    cout << "���ճɼ��ܺ���������\n";
}
void Lsort(DATA *px,int len)//��������������
{
    int k = 0,m = 0,choice = 0;
    DATA temp;
    do{
        cout << "1�����������������ܺ�����\n";
        cout << "2�����������ܺ�����\n";
        cin >> choice;
        if (choice != 1&&choice != 2)
        {
            cout << "\a���������ʾ��Ϣ\n";
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
                        cout << "error\n";
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
    cout << "���ճɼ��ܺ���������\n";
}
void Nasort(DATA *px,int len)//������������
{
    int k = 0,m = 0;
    DATA temp;
    cout << "������������\n";
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
    cout << "ѧ����������\n";
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
    cout << "ѧ��\t\t����\t����\t��ѧ\tӢ��\t����\t��ѧ\t����\t����\t����\tƽ��\n";
    for (int i = 0;i < len;i++)
    {
        cout <<(px+i)->number << "\t";
        cout <<(px+i)->name << "\t";
        for (int j = 0;j < 8;j++)
        {
            cout << fixed << setprecision(1) <<(px+i)->data[j] << "\t";
        }
        cout << (px+i)->avg << "\t\n";
        cout << "A:"<< (px+i)->standard[0] << "B:" << (px+i)->standard[1] << "C:" << (px+i)->standard[2] << "D:" << (px+i)->standard[3] << "E:" << (px+i)->standard[4]<<endl;
    }
    cout << "�γ�ƽ��\t\t";
    for (int i = 0;i < 6;i++)
    {
        cout << *(avg+i) << "\t";
    }
    cout << "\n";
}
void NaSearch(DATA *p,int len,char *obj)//����������ѯѧ���ɼ�
{
    int i = 0,j = 0,flag = -1;
    cout << "\n������ҵ�����\n";
    cin >> obj;
    for (i = 0;i < len;i++)
    {
        flag = strcmp((p+i)->name,obj);
        if (flag == 0)
        {
            cout << "�д�ѧ��,�����������\n";
            cout << (p+i)->number << "\t";
            cout << (p+i)->name << "\t";
            for (j = 0;j < 8;j++)
            {

                cout << (p+i)->data[j] << "\t";
            }
            cout << "\n";
            break;
        }
    }
    if (flag != 0)
    {
        cout<<"û�и�ѧ��\n";
    }
}
void NuSearch(DATA *p,int len,char *obj)//����ѧ�Ų�ѯѧ���ɼ�
{
    int i = 0,j = 0,flag = -1;
    cout << "\n������ҵ�����ѧ��\n";
    cin >> obj;
    for (i = 0;i < len;i++)
    {
        flag = strcmp((p+i)->number,obj);
        if (flag == 0)
        {
            cout << "�д�ѧ��,�����������\n";
            cout << (p+i)->number << "\t";
            cout << (p+i)->name << "\t";
            for (j = 0;j < 8;j++)
            {

                cout << (p+i)->data[j] << "\t";
            }
            cout << "\n";
            break;
        }
    }
    if (flag != 0)
    {
        cout<<"û�и�ѧ��\n";
    }
}
void VagueNuSearch(DATA *p,int len)//ģ��ƥ�䣬��ѯ������ѧ�ŵ�ѧ���ɼ�
{
    char obj[N];
    int count = 0;
    cout << "\n������ҵĲ�����ѧ��Ƭ��\n";
    cin >> obj;
    Nusort(p,len);
    for (int i = 0;i < len;i++)
    {
        if (strstr((p+i)->number,obj) != NULL)
        {
            count++;
            cout << "��"<< count << "�����:\n";
            cout << (p+i)->number  <<"\t";
            cout << (p+i)->name  <<"\t";
            for (int j = 0;j < 8;j++)
            {
                cout << (p+i)->data[j] << "\t";
            }
            cout << "\n";
        }
    }
    if (count == 0)
    {
        cout << "û�а�����Ƭ�ε�ѧ�ŵ�ѧ��\n";
    }
}
int Otherstandard(DATA *op,DATA *p,int len)//��ȡ������ѧ���������е�����
{
    int i = 0;
    cout << "�����ѧ����ѧ�š��������ɼ�:\n";
    cin >> op->number;
    cin >> op->name;
    for (i = 0;i < 6;i++)
    {
        do{
            cin >> op->data[i];
            if (op->data[i]<0||op->data[i]>100)
            {
                cout << "\a������ĳɼ������Ϲ淶�����������������\n";
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
