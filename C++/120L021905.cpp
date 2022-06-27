#include <iostream>
#include <iomanip>
#include <cstring>
#include <stdlib.h>
#define N 100

using namespace std;

typedef struct data//结构体定义
{
    char number[N];//学号
    char name[N];//姓名
    double data[8];//分别为语、数、外、其他三门课、语数外总和、六门课成绩之和
    int standard[5];//代表学生得到A,B,C,D,E的数量
    double avg;
}DATA;

void Login(const string &usename,const string &password);//成绩管理系统管理员登录
void Menu1();//系统功能菜单
void Menu2();//操作功能菜单
void Getpersonal(DATA *p,int len);//自动获取个人总成绩、平均成绩
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
    int num = 0,choice = 0;
    double avg[9];
    char obj[N];
    const string usename = "Lang",password = "123456";//管理员信息
    DATA op;
    DATA stu[10]={{"120L026601","李云龙",80,90,60,70,88,95},{"120L026602","李雷雷",91,85,99,73,78,90},
    {"120L026603","韩梅梅",93,80,100,75,86,92},{"120L026604","王强",51,63,73,58,59,70},{"120L026605","陈建军",88,70,83,55,57,86},
    {"120L026606","韩信",84,99,70,86,88,93},{"120L026607","张良",99,95,98,86,88,96},{"120L026608","萧何",100,93,88,77,62,87},
    {"120L026609","刘云德",100,100,100,100,100,100},{"120L026610","MC子龙",85,88,97,87,98,99}};
    cout << "正确的用户名:Lang\t正确的密码:123456" << endl;
    Login(usename,password);
    Menu1();
    do{
        cout << "请输入样本中从前往后数所需的人数.(不超过10人)" << endl;
        cin >> num;
        if(num <= 0||num > 10)
        {
            cout << '\a';
        }
    }while(num > 10||num <= 0);
    DATA *p = &stu[0];
    Getscorestandard(p,num);//统计成绩等级
    Getavg(p,num,avg);//计算成绩平均值
    Getpersonal(p,num);//计算个人平均成绩、总成绩
    do{
        Menu2();
        cout << "输入选择的功能序号(不在范围内默认退出):\n";
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
            cout << "该学生的排名是:" << Otherstandard(&op,p,num) << endl;
        }
    }while(choice >= 1 && choice <= 8);

    cout << "感谢使用本系统~~\n";
    return 0;
}
void Login(const string &usename,const string &password)
{
    int tries = 1;//尝试次数
    string tryusename,trypassword;
    cout << "请输入您的用户名！" << endl;
    cout << "您有三次输入用户名的机会！" << endl;
    do{
        if(tries == 4)
        {
            cout << "您的机会用光，请稍后再试！" << endl;
            exit(1);//次数用尽
        }
        cin >> tryusename;
        if(tryusename.compare(usename) != 0)//判断该用户是否有权限
        {
            cout << '\a' << "暂无权限，请重新尝试用户名！(剩余机会" << (3-tries) << "次！)"<<endl;
            tries++;
        }
        else
        {
            cout << "请继续输入您的密码！(您有三次机会)" << endl;
            break;
        }
    }while(1);
    tries = 1;//重置尝试次数
    while(tries <= 3)
    {
        cin >> trypassword;
        if(trypassword.compare(password) == 0)//判断密码是否正确
        {
            cout << "恭喜!登录成功" << endl;
            return;
        }
        else
        {
            cout << '\a' << "密码错误，请重新尝试！(剩余机会" << (3-tries) << "次！)" << endl;
            tries++;
        }
    }
    cout<<"您的机会用光，请稍后再试！"<<endl;
    exit(1);
}
void Menu1()
{
    cout<<" ----------学生成绩管理系统MAX----------- "<<endl;
    cout<<"|本系统实现功能：                        |"<<endl;
    cout<<"|1.计算学生平均成绩                      |"<<endl;
    cout<<"|2.统计学生成绩等级                      |"<<endl;
    cout<<"|3.按照主科成绩总和或六科成绩总和排序    |"<<endl;
    cout<<"|4.按照学生姓名进行字典顺序排序          |"<<endl;
    cout<<"|5.按照学生学号进行排序                  |"<<endl;
    cout<<"|6.查询目标姓名的学生成绩                |"<<endl;
    cout<<"|7.查询目标学号的学生成绩                |"<<endl;
    cout<<"|8.查询不完整目标学号的学生成绩          |"<<endl;
    cout<<"|9.得出其他学生在样本中的排名            |"<<endl;
    cout<<" ---------------------------------------- "<<endl;
}
void Menu2()
{
    cout<<" ----------学生成绩管理系统MAX----------- \n";
    cout<<"|选择功能序号：                          |\n";
    cout<<"|1.按照成绩总分由高到低排序              |\n";
    cout<<"|2.按照成绩总分由低到高排序              |\n";
    cout<<"|3.按照姓名排序                          |\n";
    cout<<"|4.按照学号排序                          |\n";
    cout<<"|5.按照姓名查询                          |\n";
    cout<<"|6.按照学号查询                          |\n";
    cout<<"|7.按照不完整学号查询                    |\n";
    cout<<"|8.得出其他学生在样本中的排名            |\n";
    cout<<"------------------------------------------\n";
}
void Getpersonal(DATA *p,int len)//计算个人总成绩、平均成绩
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
            sum = sum + (p+j)->data[i];
        }
        avg[i] = (sum)/len;
    }
}
void Hsort(DATA *px,int len)//交换法降序排序
{
    int k = 0,m = 0,choice = 0;
    DATA temp;
    do{
        cout << "1代表按照语数外三科总和排序\n";
        cout << "2代表按照六科总和排序\n";
        cin >> choice;
        if (choice != 1&&choice != 2)
        {
            cout << "\a请认真读提示信息\n";
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
    cout << "按照成绩总和排序如下\n";
}
void Lsort(DATA *px,int len)//交换法升序排序
{
    int k = 0,m = 0,choice = 0;
    DATA temp;
    do{
        cout << "1代表按照语数外三科总和排序\n";
        cout << "2代表按照六科总和排序\n";
        cin >> choice;
        if (choice != 1&&choice != 2)
        {
            cout << "\a请认真读提示信息\n";
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
    cout << "按照成绩总和排序如下\n";
}
void Nasort(DATA *px,int len)//按照姓名排序
{
    int k = 0,m = 0;
    DATA temp;
    cout << "姓名排序如下\n";
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
    cout << "学号排序如下\n";
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
    cout << "学号\t\t姓名\t语文\t数学\t英语\t物理\t化学\t生物\t三科\t六科\t平均\n";
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
    cout << "课程平均\t\t";
    for (int i = 0;i < 6;i++)
    {
        cout << *(avg+i) << "\t";
    }
    cout << "\n";
}
void NaSearch(DATA *p,int len,char *obj)//按照姓名查询学生成绩
{
    int i = 0,j = 0,flag = -1;
    cout << "\n输入查找的姓名\n";
    cin >> obj;
    for (i = 0;i < len;i++)
    {
        flag = strcmp((p+i)->name,obj);
        if (flag == 0)
        {
            cout << "有此学生,相关数据如下\n";
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
        cout<<"没有该学生\n";
    }
}
void NuSearch(DATA *p,int len,char *obj)//按照学号查询学生成绩
{
    int i = 0,j = 0,flag = -1;
    cout << "\n输入查找的完整学号\n";
    cin >> obj;
    for (i = 0;i < len;i++)
    {
        flag = strcmp((p+i)->number,obj);
        if (flag == 0)
        {
            cout << "有此学生,相关数据如下\n";
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
        cout<<"没有该学生\n";
    }
}
void VagueNuSearch(DATA *p,int len)//模糊匹配，查询不完整学号的学生成绩
{
    char obj[N];
    int count = 0;
    cout << "\n输入查找的不完整学号片段\n";
    cin >> obj;
    Nusort(p,len);
    for (int i = 0;i < len;i++)
    {
        if (strstr((p+i)->number,obj) != NULL)
        {
            count++;
            cout << "第"<< count << "个结果:\n";
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
        cout << "没有包含该片段的学号的学生\n";
    }
}
int Otherstandard(DATA *op,DATA *p,int len)//获取样本外学生在样本中的排名
{
    int i = 0;
    cout << "输入该学生的学号、姓名、成绩:\n";
    cin >> op->number;
    cin >> op->name;
    for (i = 0;i < 6;i++)
    {
        do{
            cin >> op->data[i];
            if (op->data[i]<0||op->data[i]>100)
            {
                cout << "\a您输入的成绩不符合规范，请重新输入该数据\n";
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
