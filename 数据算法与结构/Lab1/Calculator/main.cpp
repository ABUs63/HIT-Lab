#include <iostream>
#include <fstream>
#include <istream>
#include <cmath>

using namespace std;

struct polynode{
    double coef;//ϵ��
    int exp;//ָ��
    struct polynode *next;//ָ����һ��ָ��
};
typedef struct polynode *polypointer;

void Menu();//���ܲ˵�
void PrintScreen(polypointer a);//����ʽ�����Ļ���
void RecodeDataFile(polypointer a);//�����д���ļ�result��,���������ʾ
polypointer Sort(polypointer a);//����ʽָ������
polypointer Attach(double x,int y,polypointer z);//��ϵ��Ϊx,ָ��Ϊy�Ķ���ʽ����z��
polypointer PolyAdd(polypointer a,polypointer b);//����������ʽ��
polypointer PolyMinus(polypointer a,polypointer b);//����������ʽ��
polypointer PolyMulti(polypointer a,polypointer b);//����������ʽ��
polypointer PolyDao(polypointer a,int k);//�������ʽk�׵������ʽ
double GetXData(polypointer a,double x);//����ȡֵΪxʱ����ʽ��ֵ
void PolyDiv(polypointer a,polypointer b);//�������ʽ����,��ӡ���������
char Compare_exp(polypointer p,polypointer q);//�Ƚ�����ָ����С������'=','>','<'
int main()
{
    int choice,k,exp;//����ѡ��,��������,ָ��
    double x0,data,coef;//xȡֵ,��ֵ���,ϵ��
    char ch;//��¼��ȡ����
    ifstream file1;//��ȡ��ʼ����
    file1.open("data.txt");//���ļ�����
    if(file1.fail())//�ļ��Ƿ��ʧ��
    {
        cout<<"data�ļ���ʧ��"<<endl;
        return 1;
    }
    polypointer x,y,temp,result,create;
    x=new polynode;
    y=new polynode;
    result=new polynode;
    temp=x;//��¼ͷָ��
    do{
        file1>>coef;
        for(int i=0;i<3;i++)
        {
            file1.get();//��ȡ�ļ���*x^����
        }
        file1>>exp;
        file1.get(ch);
        x->coef=coef;
        x->exp=exp;
        if(ch==';')//����ʽĩβ
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
    temp=y;//����ͬ��
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
    cout<<"������������ʽΪ:"<<endl;
    PrintScreen(x);
    PrintScreen(y);
    Menu();//���ܲ˵���ʾ
    cout<<"����������ѡ��:"<<endl;
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
        cout<<"�����󵼴���:(�����Զ�ȡ��)"<<endl;
        cin>>k;
        result=PolyDao(x,k);
        PrintScreen(result);
        RecodeDataFile(result);
        break;
    case 5:
        cout<<"����xȡֵ:(��������)"<<endl;
        cin>>x0;
        data=GetXData(x,x0);
        cout<<"���Ϊ:"<<data<<endl;
        break;
    case 6:
        PolyDiv(x,y);
        break;
    default:
        cout<<"ѡ�񳬳���Χ,�������"<<endl;
        break;
    }
    delete create;
    return 0;
}
polypointer Attach(double x,int y,polypointer z)//��ϵ��Ϊx,ָ��Ϊy�Ľ�����z��
{
    polypointer m;
    m=new polynode;//Ϊ�¼ӵ���ʽ���ٿռ�
    m->coef=x;
    m->exp=y;
    m->next=NULL;
    z->next=m;
    return m;//���ض���ʽβ��ַ
}
polypointer Sort(polypointer a)//������������,��ɾ�����Ժϲ�Ϊ0����
{
    polypointer head,rear,temp;
    head=new polynode;//�½������ͷ
    head->next=NULL;
    rear=head;
    while(a)
    {
        rear=head;
        while(rear->next&&rear->next->exp>a->exp)
        {
            rear=rear->next;
        }
        if(rear->next&&rear->next->exp==a->exp)//��ǰλ�ÿ��Ժϲ�ͬ����
        {
            if(rear->next->coef+a->coef)//�ϲ���ϵ����Ϊ0
            {
                rear->next->coef=rear->next->coef+a->coef;
            }
            else//�ϲ���ϵ��Ϊ0,ɾ���ý��
            {
                temp=rear->next;
                rear->next=temp->next;
                delete temp;
            }
        }
        else//��ǰλ�ò����Ժϲ�,ֱ�ӽ���������ĩβ
        {
            temp=new polynode;
            temp->coef=a->coef;
            temp->exp=a->exp;
            temp->next=rear->next;
            rear->next=temp;
            rear=rear->next;
        }
        a=a->next;//׼��������һ������
    }
    temp=head;//ɾ����ͷ��ز���
    head=head->next;
    delete temp;
    return head;//�����ޱ�ͷ�����׵�ַ
}
char Compare_exp(polypointer p,polypointer q)
{
    if(p->exp==q->exp)//ָ�����
    {
        return '=';
    }
    else if(p->exp>q->exp)//pָ����
    {
        return '>';
    }
    else//qָ����
    {
        return '<';
    }
}
polypointer PolyAdd(polypointer a,polypointer b)//�ޱ�ͷ����ʽ�ӷ�
{
    polypointer p,q,d,c;
    double y;
    p=a;
    q=b;
    c=new polynode;//Ϊ����ʽ��ͽ�����ٿռ�
    d=c;//��ͽ����ͷ��ֵ
    while((p!=NULL)&&(q!=NULL))//��ǰλ��������ʽ���ǿ�
        switch(Compare_exp(p,q))
        {
        case '='://���ϵ�����
            y=p->coef+q->coef;
            if(y)
            {
                d=Attach(y,p->exp,d);
            }
            p=p->next;
            q=q->next;
            break;
        case '>'://pָ����,����p
            d=Attach(p->coef,p->exp,d);
            p=p->next;
            break;
        case '<'://qָ����,����q
            d=Attach(q->coef,q->exp,d);
            q=q->next;
            break;
        default:
            break;
        }
    while(p!=NULL)//һ������ʽλ��Ϊ��,ֱ�Ӳ�����һ������ʽʣ����
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
polypointer PolyMinus(polypointer a,polypointer b)//�ޱ�ͷ����ʽ����
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
            d=Attach(-(q->coef),q->exp,d);//������ӷ����,q����ʽϵ��ȡ��
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
        d=Attach(-(q->coef),q->exp,d);//������ӷ����,q����ʽϵ��ȡ��
        q=q->next;
    }
    d->next=NULL;
    p=c;
    c=c->next;
    delete p;
    return c;
}
polypointer PolyMulti(polypointer a,polypointer b)//�ޱ�ͷ����ʽ�˷�
{
    polypointer p,q,c,d;
    double x;
    int y;
    p=a;
    q=b;//�洢����ʽb��ַ,����ѭ���ֽ�˷�
    c=new polynode;
    c->next=NULL;
    d=c;
    while(p)
    {
        while(q)//pĳһ����q���
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
    if(k<0)//�󵼴����Ǹ�
    {
        k=-k;
    }
    if(k>a->exp)//�󵼴����������ָ��
    {
        a->next=NULL;
        a->coef=0;
        a->exp=0;
        return a;
    }
    result=new polynode;
    result->next=a;//�б�ͷ,����������next����,����0ʱ��մ���
    temp=result;
    while(k!=0)
    {
        while(temp->next!=NULL)
        {
            if(temp->next->exp>=1)//ָ����Ϊ0
            {
                temp->next->coef*=temp->next->exp;
                temp->next->exp--;
                temp=temp->next;
            }
            else if(temp->next->exp==0)//ָ��Ϊ0��ֱ����մ���
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
double GetXData(polypointer a,double x)//����ʽ��ֵ
{
    polypointer temp;
    double result=0.0;//�����ʼ��
    temp=a;
    while(temp!=NULL)
    {
        result+=temp->coef*pow(x,temp->exp);//���ÿ⺯�����ָ��������ֵ;
        temp=temp->next;
    }
    return result;
}
void Menu()
{
    cout<<"��������:"<<endl;
    cout<<"1.������ʽ���"<<endl;
    cout<<"2.������ʽ���"<<endl;
    cout<<"3.������ʽ���"<<endl;
    cout<<"4.����ʽһ��"<<endl;
    cout<<"5.����ʽһ��ֵ"<<endl;
    cout<<"6.������ʽ���"<<endl;
    cout<<"ע:ֻ����һ�ι���ѡ��,ǰ������Ҳ��д���ļ�"<<endl;
}
void PrintScreen(polypointer a)//����Ļ����ʾ���
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
        if(temp->coef>0)//�鿴��һ��ϵ���Ƿ�Ϊ��
        {
            cout<<"+";
        }
    }
    cout<<temp->coef<<"*x^"<<temp->exp<<";"<<endl;
}
void RecodeDataFile(polypointer a)//���ļ�����ʾ���
{
    double coef;
    int exp;
    polypointer temp;
    ofstream file2;//д���ļ�����
    file2.open("result.txt");
    if(file2.fail())//�ļ��Ƿ�򿪳ɹ�
    {
        cout<<"result�ļ���ʧ��"<<endl;
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
            file2.put('*');//����һ������д���ļ�(ͬ�����ļ�)//
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
void PolyDiv(polypointer a,polypointer b)//����ʽ���,��ӡ�������ʽ���������ʽ
{
    if(a->exp<b->exp)//Ĭ�϶���ʽa,b��Ϊ����˳��
    {
        cout<<"��Ϊ:0"<<endl;
        cout<<"����Ϊ:";
        PrintScreen(a);
    }
    else
    {
        polypointer p,q,c,d,f;
        p=a;
        q=b;
        c=new polynode;//�������ʽ�洢
        d=c;
        f=new polynode;//�м�����洢
        f->next=NULL;
        float coef;
        int exp;
        while(p!=NULL)
        {
            if(p->exp>=q->exp)
            {
                coef=p->coef/q->coef;//�����
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
        cout<<"��Ϊ��";
        PrintScreen(c);
        cout<<"����Ϊ:";
        PrintScreen(p);
    }
}
