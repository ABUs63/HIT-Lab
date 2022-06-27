#include <iostream>
#include <fstream>
#include <istream>
#include <cmath>

using namespace std;

struct polynode{
    double coef;//系数
    int exp;//指数
    struct polynode *next;//指向下一项指针
};
typedef struct polynode *polypointer;

void Menu();//功能菜单
void PrintScreen(polypointer a);//多项式结果屏幕输出
void RecodeDataFile(polypointer a);//将结果写入文件result中,错误输出提示
polypointer Sort(polypointer a);//多项式指数降序
polypointer Attach(double x,int y,polypointer z);//将系数为x,指数为y的多项式加在z后
polypointer PolyAdd(polypointer a,polypointer b);//计算两多项式和
polypointer PolyMinus(polypointer a,polypointer b);//计算两多项式减
polypointer PolyMulti(polypointer a,polypointer b);//计算两多项式乘
polypointer PolyDao(polypointer a,int k);//计算多项式k阶导数表达式
double GetXData(polypointer a,double x);//计算取值为x时多项式的值
void PolyDiv(polypointer a,polypointer b);//计算多项式除法,打印商项和余项
char Compare_exp(polypointer p,polypointer q);//比较两项指数大小，返回'=','>','<'
int main()
{
    int choice,k,exp;//功能选择,导数阶数,指数
    double x0,data,coef;//x取值,求值结果,系数
    char ch;//记录读取符号
    ifstream file1;//读取初始数据
    file1.open("data.txt");//打开文件操作
    if(file1.fail())//文件是否打开失败
    {
        cout<<"data文件打开失败"<<endl;
        return 1;
    }
    polypointer x,y,temp,result,create;
    x=new polynode;
    y=new polynode;
    result=new polynode;
    temp=x;//记录头指针
    do{
        file1>>coef;
        for(int i=0;i<3;i++)
        {
            file1.get();//读取文件中*x^符号
        }
        file1>>exp;
        file1.get(ch);
        x->coef=coef;
        x->exp=exp;
        if(ch==';')//多项式末尾
        {
            x->next=NULL;
            break;
        }
        else
        {
            create=new polynode;
            x->next=create;
            x=x->next;
        }
    }while(1);
    x=temp;
    temp=y;//功能同上
    do{
        file1>>coef;
        for(int i=0;i<3;i++)
        {
            file1.get();
        }
        file1>>exp;
        file1.get(ch);
        y->coef=coef;
        y->exp=exp;
        if(ch==';')
        {
            y->next=NULL;
            break;
        }
        else
        {
            create=new polynode;
            y->next=create;
            y=y->next;
        }
    }while(1);
    y=temp;
    x=Sort(x);
    y=Sort(y);
    cout<<"现在两个多项式为:"<<endl;
    PrintScreen(x);
    PrintScreen(y);
    Menu();//功能菜单显示
    cout<<"请输入您的选择:"<<endl;
    cin>>choice;
    switch (choice)
    {
    case 1:
        result=PolyAdd(x,y);
        PrintScreen(result);
        RecodeDataFile(result);
        break;
    case 2:
        result=PolyMinus(x,y);
        PrintScreen(result);
        RecodeDataFile(result);
        break;
    case 3:
        result=PolyMulti(x,y);
        result=Sort(result);
        PrintScreen(result);
        RecodeDataFile(result);
        break;
    case 4:
        cout<<"输入求导次数:(负数自动取正)"<<endl;
        cin>>k;
        result=PolyDao(x,k);
        PrintScreen(result);
        RecodeDataFile(result);
        break;
    case 5:
        cout<<"输入x取值:(结果会近似)"<<endl;
        cin>>x0;
        data=GetXData(x,x0);
        cout<<"结果为:"<<data<<endl;
        break;
    case 6:
        PolyDiv(x,y);
        break;
    default:
        cout<<"选择超出范围,程序结束"<<endl;
        break;
    }
    delete create;
    return 0;
}
polypointer Attach(double x,int y,polypointer z)//将系数为x,指数为y的结点插在z表
{
    polypointer m;
    m=new polynode;//为新加单项式开辟空间
    m->coef=x;
    m->exp=y;
    m->next=NULL;
    z->next=m;
    return m;//返回多项式尾地址
}
polypointer Sort(polypointer a)//降序排列链表,并删除可以合并为0的项
{
    polypointer head,rear,temp;
    head=new polynode;//新建链表表头
    head->next=NULL;
    rear=head;
    while(a)
    {
        rear=head;
        while(rear->next&&rear->next->exp>a->exp)
        {
            rear=rear->next;
        }
        if(rear->next&&rear->next->exp==a->exp)//当前位置可以合并同类项
        {
            if(rear->next->coef+a->coef)//合并后系数不为0
            {
                rear->next->coef=rear->next->coef+a->coef;
            }
            else//合并后系数为0,删除该结点
            {
                temp=rear->next;
                rear->next=temp->next;
                delete temp;
            }
        }
        else//当前位置不可以合并,直接接在新链表末尾
        {
            temp=new polynode;
            temp->coef=a->coef;
            temp->exp=a->exp;
            temp->next=rear->next;
            rear->next=temp;
            rear=rear->next;
        }
        a=a->next;//准备链表下一结点插入
    }
    temp=head;//删除表头相关操作
    head=head->next;
    delete temp;
    return head;//返回无表头链表首地址
}
char Compare_exp(polypointer p,polypointer q)
{
    if(p->exp==q->exp)//指数相等
    {
        return '=';
    }
    else if(p->exp>q->exp)//p指数大
    {
        return '>';
    }
    else//q指数大
    {
        return '<';
    }
}
polypointer PolyAdd(polypointer a,polypointer b)//无表头多项式加法
{
    polypointer p,q,d,c;
    double y;
    p=a;
    q=b;
    c=new polynode;//为多项式求和结果开辟空间
    d=c;//求和结果表头赋值
    while((p!=NULL)&&(q!=NULL))//当前位置两多项式均非空
        switch(Compare_exp(p,q))
        {
        case '='://相等系数相加
            y=p->coef+q->coef;
            if(y)
            {
                d=Attach(y,p->exp,d);
            }
            p=p->next;
            q=q->next;
            break;
        case '>'://p指数大,插入p
            d=Attach(p->coef,p->exp,d);
            p=p->next;
            break;
        case '<'://q指数大,插入q
            d=Attach(q->coef,q->exp,d);
            q=q->next;
            break;
        default:
            break;
        }
    while(p!=NULL)//一个多项式位置为空,直接插入另一个多项式剩余项
    {
        d=Attach(p->coef,p->exp,d);
        p=p->next;
    }
    while(q!=NULL)
    {
        d=Attach(q->coef,q->exp,d);
        q=q->next;
    }
    d->next=NULL;
    p=c;
    c=c->next;
    delete p;
    return c;
}
polypointer PolyMinus(polypointer a,polypointer b)//无表头多项式减法
{
    polypointer p,q,d,c;
    double y;
    p=a;
    q=b;
    c=new polynode;
    d=c;
    while((p!=NULL)&&(q!=NULL))
        switch(Compare_exp(p,q))
        {
        case '=':
            y=p->coef-q->coef;
            if(y)
            {
                d=Attach(y,p->exp,d);
            }
            p=p->next;
            q=q->next;
            break;
        case '>':
            d=Attach(p->coef,p->exp,d);
            p=p->next;
            break;
        case '<':
            d=Attach(-(q->coef),q->exp,d);//减法与加法差别,q多项式系数取负
            q=q->next;
            break;
        default:
            break;
        }
    while(p!=NULL)
    {
        d=Attach(p->coef,p->exp,d);
        p=p->next;
    }
    while(q!=NULL)
    {
        d=Attach(-(q->coef),q->exp,d);//减法与加法差别,q多项式系数取负
        q=q->next;
    }
    d->next=NULL;
    p=c;
    c=c->next;
    delete p;
    return c;
}
polypointer PolyMulti(polypointer a,polypointer b)//无表头多项式乘法
{
    polypointer p,q,c,d;
    double x;
    int y;
    p=a;
    q=b;//存储多项式b地址,便于循环分解乘法
    c=new polynode;
    c->next=NULL;
    d=c;
    while(p)
    {
        while(q)//p某一项与q相乘
        {
            x=(p->coef)*(q->coef);
            y=(p->exp)+(q->exp);
            d=Attach(x,y,d);
            q=q->next;
        }
        p=p->next;
        q=b;
    }
    p=c;
    c=c->next;
    delete p;
    return c;
}
polypointer PolyDao(polypointer a,int k)
{
    polypointer result,temp;
    if(k<0)//求导次数非负
    {
        k=-k;
    }
    if(k>a->exp)//求导次数超过最大指数
    {
        a->next=NULL;
        a->coef=0;
        a->exp=0;
        return a;
    }
    result=new polynode;
    result->next=a;//有表头,后续操作以next操作,便于0时清空此项
    temp=result;
    while(k!=0)
    {
        while(temp->next!=NULL)
        {
            if(temp->next->exp>=1)//指数不为0
            {
                temp->next->coef*=temp->next->exp;
                temp->next->exp--;
                temp=temp->next;
            }
            else if(temp->next->exp==0)//指数为0求导直接清空此项
            {
                temp->next=NULL;
            }
        }
        k--;
        temp=result;
    }
    temp=result;
    result=result->next;
    delete temp;
    return result;
}
double GetXData(polypointer a,double x)//多项式求值
{
    polypointer temp;
    double result=0.0;//结果初始化
    temp=a;
    while(temp!=NULL)
    {
        result+=temp->coef*pow(x,temp->exp);//调用库函数完成指数函数求值;
        temp=temp->next;
    }
    return result;
}
void Menu()
{
    cout<<"功能如下:"<<endl;
    cout<<"1.两多项式相加"<<endl;
    cout<<"2.两多项式相减"<<endl;
    cout<<"3.两多项式相乘"<<endl;
    cout<<"4.多项式一求导"<<endl;
    cout<<"5.多项式一求值"<<endl;
    cout<<"6.两多项式相除"<<endl;
    cout<<"注:只进行一次功能选择,前四项结果也会写入文件"<<endl;
}
void PrintScreen(polypointer a)//在屏幕中显示结果
{
    polypointer temp;
    temp=a;
    if(temp==NULL)
    {
        cout<<"0;";
        return ;
    }
    if(temp->exp==0&&temp->next==NULL)
    {
        cout<<temp->coef;
        return ;
    }
    for(int i=1;temp->next!=NULL;i++)
    {
        cout<<temp->coef<<"*x^"<<temp->exp;
        temp=temp->next;
        if(temp->coef>0)//查看下一个系数是否为负
        {
            cout<<"+";
        }
    }
    cout<<temp->coef<<"*x^"<<temp->exp<<";"<<endl;
}
void RecodeDataFile(polypointer a)//在文件中显示结果
{
    double coef;
    int exp;
    polypointer temp;
    ofstream file2;//写入文件操作
    file2.open("result.txt");
    if(file2.fail())//文件是否打开成功
    {
        cout<<"result文件打开失败"<<endl;
        return ;
    }
    temp=a;
    while(temp!=NULL)
    {
        if(temp->exp==0)
        {
            file2<<temp->coef;
        }
        else
        {
            coef=temp->coef;
            exp=temp->exp;
            file2<<coef;
            file2.put('*');//按照一定规则写入文件(同输入文件)//
            file2.put('x');
            file2.put('^');
            file2<<exp;
            if(temp->next!=NULL&&temp->next->coef>0)
            {
                file2.put('+');
            }
        }
        temp=temp->next;
    }
    file2.put(';');
}
void PolyDiv(polypointer a,polypointer b)//多项式相除,打印商项多项式和余项多项式
{
    if(a->exp<b->exp)//默认多项式a,b均为降序顺序
    {
        cout<<"商为:0"<<endl;
        cout<<"余数为:";
        PrintScreen(a);
    }
    else
    {
        polypointer p,q,c,d,f;
        p=a;
        q=b;
        c=new polynode;//商项多项式存储
        d=c;
        f=new polynode;//中间变量存储
        f->next=NULL;
        float coef;
        int exp;
        while(p!=NULL)
        {
            if(p->exp>=q->exp)
            {
                coef=p->coef/q->coef;//商项处理
                exp=p->exp-q->exp;
                f->coef=coef;
                f->exp=exp;
                d=Attach(coef,exp,d);
                if(p->next!=NULL)
                {
                    p=p->next;
                    p=PolyMinus(p,PolyMulti(q->next,f));
                }
                else
                {
                    p=PolyMinus(p,PolyMulti(q,f));
                }
            }
            else
            {
                break;
            }
        }
        c=c->next;
        cout<<"商为：";
        PrintScreen(c);
        cout<<"余数为:";
        PrintScreen(p);
    }
}
