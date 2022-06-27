#include <iostream>
#include <queue>
#include <stack>
#define M 15

using namespace std;

typedef struct{
    int vertex[M];//�����
    int edge[M][M];//�߱�
    int n,e;//������������
}MTGraph;//�ڽӾ���
typedef struct node{
    int adjvex;//�±�
    int cost;//��Ȩֵ
    struct node *next;
}EdgeNode;//�߱���
typedef struct{
    int vertex;//������
    EdgeNode *firstedge;
}VertexNode;//�����
typedef struct{
    VertexNode vexlist[M];
    int n,e;
}AdjGraph;//�ڽӱ�
typedef struct{
    int degree[M];//��������Ķ�
    int n;//�������
}Degree;//����Ķ�

bool visited[M];//���ʱ��
int COUNT;//ɭ�ֱ����
int COUNT2;//��������
int dfn[M];//������Ŵ洢

void Menu();//���ܲ˵���ʾ
void CreateMTGraph(MTGraph *G);//����ͼ����Ӿ���
void CreateAdjGraph(AdjGraph *G);//����ͼ���ڽӱ�
void MT_toAdj(MTGraph MG,AdjGraph *AG);//�ڽӾ���ת��Ϊ�ڽӱ�
void Adj_toMT(AdjGraph AG,MTGraph *MG);//�ڽӱ�ת��Ϊ�ڽӾ���
void ADFSTraverse(AdjGraph G);//�ݹ���������������㷨--�ڽӱ�
void ADFS(AdjGraph G,int i);//������������ݹ����㷨--�ڽӱ�
void MDFSTraverse(MTGraph G);//�ݹ���������������㷨--�ڽӾ���
void MDFS(MTGraph G,int i);//������������ݹ����㷨--�ڽӾ���
void NoADFS(AdjGraph G);//�ǵݹ������������--�ڽӱ�
void NoMDFS(MTGraph G);//�ǵݹ������������--�ڽӾ���
void ABFS(AdjGraph *G);//�����������--�ڽӱ�
void MBFS(MTGraph *G);//�����������--�ڽӾ���
void CalculateDegree(AdjGraph AG,Degree *d);//�����ڽӱ�����������Ķ�
void PrintMT(MTGraph G);//��ʾͼ���ڽӾ�����Ϣ
void PrintAdj(AdjGraph G);//��ʾͼ���ڽӱ���Ϣ

int main()
{
    MTGraph G1;//�ڽӾ���
    AdjGraph G2;//�ڽӱ�
    Degree degree;//�����
    int choice;
    do{
        Menu();
        cout<<"���빦��ѡ��\n";
        cin>>choice;
        switch (choice)
        {
            case 1:
                CreateMTGraph(&G1);
                PrintMT(G1);
                break;
            case 2:
                CreateAdjGraph(&G2);
                PrintAdj(G2);
                break;
            case 3:
                MT_toAdj(G1,&G2);
                PrintAdj(G2);
                break;
            case 4:
                Adj_toMT(G2,&G1);
                PrintMT(G1);
                break;
            case 5:
                cout<<"�ڽӾ���:\n";
                MDFSTraverse(G1);
                cout<<"�������:\n";
                for(int i=0;i<G1.n;i++)
                {
                    cout<<G1.vertex[i]<<"->"<<dfn[i]<<endl;
                }
                cout<<endl;
                cout<<"�ڽӱ�:\n";
                ADFSTraverse(G2);
                cout<<"�������:\n";
                for(int i=0;i<G2.n;i++)
                {
                    cout<<G2.vexlist[i].vertex<<"->"<<dfn[i]<<endl;
                }
                cout<<endl;
                break;
            case 6:
                cout<<"�ڽӾ���:\n";
                NoMDFS(G1);
                cout<<"�������:\n";
                for(int i=0;i<G1.n;i++)
                {
                    cout<<G1.vertex[i]<<"->"<<dfn[i]<<endl;
                }
                cout<<endl;
                cout<<"�ڽӱ�:\n";
                NoADFS(G2);
                cout<<"�������:\n";
                for(int i=0;i<G2.n;i++)
                {
                    cout<<G2.vexlist[i].vertex<<"->"<<dfn[i]<<endl;
                }
                cout<<endl;
                break;
            case 7:
                cout<<"�ڽӾ���:\n";
                MBFS(&G1);
                cout<<"�ȹ㶥����:\n";
                for(int i=0;i<G1.n;i++)
                {
                    cout<<G1.vertex[i]<<"->"<<dfn[i]<<endl;
                }
                cout<<endl;
                cout<<"�ڽӱ�:\n";
                ABFS(&G2);
                cout<<"�ȹ㶥����:\n";
                for(int i=0;i<G2.n;i++)
                {
                    cout<<G2.vexlist[i].vertex<<"->"<<dfn[i]<<endl;
                }
                cout<<endl;
                break;
            case 8:
                CalculateDegree(G2,&degree);
                break;
            default:
                break;
        }
    }while(choice>0&&choice<9);
    return 0;
}
void Menu()
{
    cout<<"Ĭ�϶�����±�Ϊ0~n-1;"<<endl;
    cout<<"1.�����ڽӾ�����ʾ���;"<<endl;
    cout<<"2.�����ڽӱ���ʾ���;"<<endl;
    cout<<"3.�����õ��ڽӾ���ת��Ϊ�ڽӱ���ʾ���;"<<endl;
    cout<<"4.�����õ��ڽӱ�ת��Ϊ�ڽӾ�����ʾ���;"<<endl;
    cout<<"5.�ݹ������������;"<<endl;
    cout<<"6.�ǵݹ������������;"<<endl;
    cout<<"7.�����������;"<<endl;
    cout<<"8.�������е��ڽӱ���������ĶȲ���ʾ���;"<<endl;
}
void CreateMTGraph(MTGraph *G)//�����ڽӾ���
{
    int i,j,k,w;
    cout<<"���붥����:\n";
    cin>>G->n;
    cout<<"�������:\n";
    cin>>G->e;
    for(i=0;i<G->n;i++)
    {
        G->vertex[i]=i;//Ĭ�϶����±�����0~n-1
    }
    for(i=0;i<G->n;i++)
    {
        for(j=0;j<G->n;j++)
        {
            G->edge[i][j]=0;//��Ȩֵ��ʼ��
        }
    }
    for(k=0;k<G->e;k++)
    {
        cout<<"�ֱ����붥��i,j��(i,j)��Ȩֵ:\n";
        cin>>i;
        cin>>j;
        cin>>w;
        G->edge[i][j]=w;
        G->edge[j][i]=w;
    }
}
void CreateAdjGraph(AdjGraph *G)//�����ڽӱ�
{
    int tail,head,weight;
    cout<<"�ֱ����붥�����,����:\n";
    cin>>G->n;
    cin>>G->e;
    for(int i=0;i<G->n;i++)
    {
        G->vexlist[i].vertex=i;//Ĭ���±�Ϊ����0~n-1
        G->vexlist[i].firstedge=NULL;//�ڽӱ��ʼ�ÿ�
    }
    for(int i=0;i<G->e;i++)//ͷ�巨�����½��
    {
        cout<<"���붥��i,j,��(i,j)��Ȩֵ:\n";
        cin>>tail;//����1
        cin>>head;//����j
        cin>>weight;//(i,j)��Ȩֵ
        EdgeNode *p=new EdgeNode;//����ͼ���ڽӱ�,ͬʱ��������������ڽӱ�
        p->adjvex=head;
        p->cost=weight;
        p->next=G->vexlist[tail].firstedge;
        G->vexlist[tail].firstedge=p;
        EdgeNode *q=new EdgeNode;
        q->adjvex=tail;
        q->cost=weight;
        q->next=G->vexlist[head].firstedge;
        G->vexlist[head].firstedge=q;
    }
}
void MT_toAdj(MTGraph MG,AdjGraph *AG)//�ڽӾ���ת��Ϊ�ڽӱ�
{
    int i,j,k;
    AG->n=MG.n;
    AG->e=MG.e;
    for(i=0;i<AG->n;i++)//�ڽӱ��ʼ��
    {
        AG->vexlist[i].vertex=MG.vertex[i];
        AG->vexlist[i].firstedge=NULL;
    }
    for(j=0;j<AG->n;j++)
    {
        for(k=j;k<AG->n;k++)
        {
            if(MG.edge[j][k]!=0)//(j,k)�ߴ���,������Ӧ�߱������
            {
                EdgeNode *p=new EdgeNode;//j�߱�
                p->cost=MG.edge[j][k];
                p->adjvex=j;
                p->next=AG->vexlist[k].firstedge;
                AG->vexlist[k].firstedge=p;
                EdgeNode *q=new EdgeNode;//k�߱�
                q->cost=p->cost;
                q->adjvex=k;
                q->next=AG->vexlist[j].firstedge;
                AG->vexlist[j].firstedge=q;
            }
        }
    }
}
void Adj_toMT(AdjGraph AG,MTGraph *MG)//�ڽӱ�ת��Ϊ�ڽӾ���
{
    MG->n=AG.n;
    MG->e=AG.e;
    EdgeNode *temp=NULL;
    for(int i=0;i<AG.n;i++)//�ڽӾ����ʼ��
    {
        for(int j=0;j<AG.n;j++)
        {
            MG->edge[i][j]=0;
        }
    }
    for(int i=0;i<AG.n;i++)
    {
        MG->vertex[i]=AG.vexlist[i].vertex;
        temp=AG.vexlist[i].firstedge;
        while(temp!=NULL)//�����ڽӱ�ĳ����߱�������Ӧ�������
        {
            MG->edge[i][temp->adjvex]=temp->cost;
            MG->edge[temp->adjvex][i]=temp->cost;
            temp=temp->next;
        }
    }
}
void ADFSTraverse(AdjGraph G)//����ݹ�--��--�ڽӱ�
{
    COUNT=1;//ȫ�ֱ�����ʼ��
    COUNT2=1;
    for(int i=0;i<G.n;i++)
    {
        visited[i]=false;
    }
    for(int i=0;i<G.n;i++)
    {
        if(!visited[i])
        {
            cout<<"ɭ��"<<COUNT++<<" ";//��ʾ����ɭ��
            ADFS(G,i);
            cout<<endl;
        }
    }
}
void ADFS(AdjGraph G,int i)//����ݹ�--��--�ڽӱ�
{
    EdgeNode *p=NULL;
    cout<<G.vexlist[i].vertex<<" ";//��ʾ����ɭ�ֵ���Ӧ����
    visited[i]=true;
    dfn[i]=COUNT2++;//��¼����������
    p=G.vexlist[i].firstedge;
    while(p)//�˶������ڽӵĶ���
    {
        if(!visited[p->adjvex])
        {
            ADFS(G,p->adjvex);//�ݹ������һ������ڽӶ���
        }
        p=p->next;
    }
}
void MDFSTraverse(MTGraph G)//����ݹ�--��--�ڽӾ���
{
    COUNT=1;//ȫ�ֱ�����ʼ��
    COUNT2=1;
    for(int i=0;i<G.n;i++)
    {
        visited[i]=false;
    }
    for(int i=0;i<G.n;i++)
    {
        if(!visited[i])
        {
            cout<<"ɭ��"<<COUNT++<<":";//��ʾ����ɭ��
            MDFS(G,i);
            cout<<endl;
        }
    }
}
void MDFS(MTGraph G,int i)//����ݹ�--��--�ڽӾ���
{
    int j;
    cout<<G.vertex[i]<<" ";//��ʾ����ɭ�ֵĶ���
    visited[i]=true;
    dfn[i]=COUNT2++;//�������������
    for(j=0;j<G.n;j++)
    {
        if((G.edge[i][j]!=0)&&!visited[j])//i������j������jδ����
        {
            MDFS(G,G.vertex[j]);//�ݹ����j������������
        }
    }
}
void NoADFS(AdjGraph G)//����ǵݹ�--�ڽӱ�
{
    for(int i=0;i<G.n;i++)//ȫ�ֱ�����ʼ��
    {
        visited[i]=false;
    }
    COUNT=1;
    COUNT2=1;
    EdgeNode *p=NULL;
    bool flag;
    stack<int>s;//����ջ�ﵽ�ݹ�Ч��
    for(int i=0;i<G.n;i++)
    {
        if(!visited[i])
        {
            cout<<"ɭ��"<<COUNT++<<":";//����ɭ����ʾ
            visited[i]=true;
            dfn[i]=COUNT2++;//������
            s.push(i);
            cout<<G.vexlist[i].vertex<<" ";//ɭ�ֶ�����ʾ
            p=G.vexlist[i].firstedge;
            while(!s.empty())
            {
                p=G.vexlist[s.top()].firstedge;
                flag=false;
                while(p)//����i���ڽӵĶ���
                {
                    if(!visited[p->adjvex])//��ǰ�ڽӵĵ�δ����
                    {
                        visited[p->adjvex]=true;
                        cout<<G.vexlist[p->adjvex].vertex<<" ";//������ʾ
                        dfn[p->adjvex]=COUNT2++;//���
                        s.push(p->adjvex);//��¼�˶���,������ĳ�ڽӶ����,������һ�ڽӶ������
                        p=G.vexlist[p->adjvex].firstedge;
                        flag=true;
                        break;
                    }
                    else//��ǰ�ڽӵĵ����,����һ���ڽӵĶ���
                    {
                        p=p->next;
                    }
                }
                if(!flag)//û���ڽӵĶ���
                {
                    s.pop();
                }
            }
            cout<<endl;
        }
    }
}
void NoMDFS(MTGraph G)//����ǵݹ�--�ڽӾ���
{
    for(int i=0;i<G.n;i++)//ȫ�ֱ�����ʼ��
    {
        visited[i]=false;
    }
    stack<int>s;
    int t;
    bool flag;
    COUNT=1;
    COUNT2=1;
    for(int j=0;j<G.n;j++)
    {
        if(!visited[j])
        {
            cout<<"ɭ��"<<COUNT++<<":";//����ɭ����ʾ
            dfn[j]=COUNT2++;//����������
            visited[j]=true;
            s.push(j);
            cout<<G.vertex[j]<<" ";//ɭ�ֶ�����ʾ
            while(!s.empty())
            {
                t=s.top();
                flag=false;
                for(int k=0;k<G.n;k++)
                {
                    if(G.edge[t][k]!=0)//t,k�ڽ�
                    {
                        if(!visited[k])//kδ����
                        {
                            visited[k]=true;
                            cout<<G.vertex[k]<<" ";//������ʾ
                            dfn[k]=COUNT2++;//���
                            s.push(k);//��¼��ǰ����k,������kĳ�ڽӶ����,����k��һ�ڽӶ������
                            flag=true;
                            break;
                        }
                    }
                }
                if(!flag)//�������ڽӶ���
                {
                    s.pop();
                }
            }
            cout<<endl;
        }
    }
}
void ABFS(AdjGraph *G)//�ȹ�--�ڽӱ�
{
    COUNT=1;//ȫ�ֱ�����ʼ��
    COUNT2=1;
    for(int j=0;j<G->n;j++)
    {
        visited[j]=false;
    }
    queue<int>s;//���Ʋ������,�ö���
    EdgeNode *p;
    for(int i=0;i<G->n;i++)
    {
        if(!visited[i])
        {
            cout<<"ɭ��"<<COUNT++<<":";//�ȹ�ɭ����ʾ
            visited[i]=true;
            dfn[i]=COUNT2++;//������
            cout<<G->vexlist[i].vertex<<" ";
            s.push(G->vexlist[i].vertex);//��¼��ǰ����i
            while(!s.empty())
            {
                p=G->vexlist[s.front()].firstedge;
                s.pop();
                while(p!=NULL)//������i�ڽ���δ���ʵĶ�����ʲ���Ӽ�¼
                {
                    if(!visited[p->adjvex])
                    {
                        visited[p->adjvex]=true;
                        cout<<G->vexlist[p->adjvex].vertex<<" ";
                        dfn[p->adjvex]=COUNT2++;//�ȹ���
                        s.push(p->adjvex);
                    }
                    p=p->next;
                }
            }
            cout<<endl;
        }
    }
}
void MBFS(MTGraph *G)//�ȹ�--�ڽӾ���
{
    for(int i=0;i<G->n;i++)//ȫ�ֱ�����ʼ��
    {
        visited[i]=false;
    }
    COUNT=1;
    COUNT2=1;
    int k;
    queue<int>s;
    for(int i=0;i<G->n;i++)
    {
        if(!visited[i])
        {
            cout<<"ɭ��"<<COUNT++<<":";//�ȹ�ɭ����ʾ
            visited[i]=true;
            cout<<G->vertex[i]<<" ";
            dfn[i]=COUNT2++;//�ȹ���
            s.push(G->vertex[i]);//��¼��ǰ����i
            while(!s.empty())
            {
                k=s.front();
                s.pop();
                for(int j=0;j<G->n;j++)
                {
                    if(G->edge[k][j]!=0)//k�ڽ���δ���ʵĶ���j���з��ʲ���Ӽ�¼
                    {
                        if(!visited[j])
                        {
                            cout<<G->vertex[j]<<" ";
                            visited[j]=true;
                            dfn[j]=COUNT2++;//�ȹ���
                            s.push(G->vertex[j]);
                        }
                    }
                }
            }
            cout<<endl;
        }
    }
}
void CalculateDegree(AdjGraph AG,Degree *d)//�ڽӱ���������Ķ�
{
    d->n=AG.n;
    EdgeNode *temp=NULL;
    for(int i=0;i<d->n;i++)//��¼����ȳ�ʼ��
    {
        d->degree[i]=0;
    }
    for(int i=0;i<AG.n;i++)
    {
        temp=AG.vexlist[i].firstedge;
        while(temp!=NULL)//�������б߱�Ķ��������
        {
            d->degree[i]++;
            temp=temp->next;
        }
    }
    for(int i=0;i<d->n;i++)//��ʾ���
    {
        cout<<"�±�Ϊ:"<<AG.vexlist[i].vertex<<"�Ķ����Ϊ:"<<d->degree[i]<<endl;
    }
}
void PrintMT(MTGraph G)
{
    cout<<"ͼ���ڽӾ�������:\n";
    cout<<"������Ϣ:\n";
    for(int i=0;i<G.n;i++)
    {
        cout<<G.vertex[i]<<endl;
    }
    cout<<"����Ϣ:\n";
    for(int i=0;i<G.n;i++)
    {
        for(int j=0;j<G.n;j++)
        {
            if(G.edge[i][j]==0)//���ڽ�,ȨֵΪ��
            {
                cout<<"��\t";
            }
            else
            {
                cout<<G.edge[i][j]<<"\t";
            }
        }
        cout<<endl;
    }
}
void PrintAdj(AdjGraph G)
{
    EdgeNode *temp=NULL;
    cout<<"ͼ���ڽӱ�����:\n";
    for(int i=0;i<G.n;i++)
    {
        cout<<G.vexlist[i].vertex<<"\t��ö����ڽӵĵ㼰��:\n";
        temp=G.vexlist[i].firstedge;
        if(temp==NULL)
        {
            cout<<"û����ö����ڽӵĶ���"<<endl;
        }
        while(temp!=NULL)
        {
            cout<<"�±�:"<<temp->adjvex<<"\t�ߵ�Ȩֵ:"<<temp->cost<<endl;
            temp=temp->next;
        }
    }
}
