#include <iostream>
#include <stack>
#include <fstream>
#include <istream>
#define M 15
#define MIN 65535

using namespace std;

typedef struct{
    int vertex[M];//�����±�,Ĭ���������±���ͬ
    int edge[M][M];//��Ȩֵ
    int n,e;//������,����
}MTGraph;
typedef struct{
    bool Get[M][M];//���������Ƿ�ɴ�(����ͼ)
    int n;//������
}MT_Get;

bool S[M];//�ж�ÿ�������Ƿ��Ѿ�������·��
int D[M];//��Ŵ�Դ�㵽������������·������
int P[M];//��¼ÿ�����·����ĳ���ڵ��ǰһ���ڵ�ı��
int D2[M][M];//���������������֮������·������
int P2[M][M];//���������������֮������·�����

void Menu();//���ܲ˵���ʾ
void CreateG(MTGraph *G);//�����ڽӾ���
void GetData(MTGraph *G);//���ļ��ж�ȡ�ڽӾ�������
int Mincost(MTGraph G);//���㵱ǰ���·�����±�w
void Dijkstra(MTGraph G);//��Դ��0��ÿ����������·��
void PrintDijkstra(MTGraph G);//���Դ��0��ÿ����������·�����Ⱥ����·��
void Floyd(MTGraph G);//Floyd�㷨��ʼ��
void Floyd_mn(MTGraph G,int m,int n);//��m,n���·�����洢��P2��
void FloydPrint(MTGraph G);//��ʾFloyd�㷨�����
void PrintFloy1(MTGraph G);//��ʾÿ������v��ĳ��ָ������c֮������·�����
void PrintFloy2(MTGraph G);//��ʾ��������ָ����������·�����
void Warshall(MTGraph G,MT_Get *MT);//Warshall�㷨��ʼ���ɴ������ϢD3[M][M]
void PrintWarshall(MT_Get MT);//��ʾFloyd�㷨ʵ������ͼ�ɴ����
void PrintMTG(MTGraph G);//��ʾ�ڽӾ�����

int main()
{
    int choice;
    MTGraph G;
    MT_Get MT;
    CreateG(&G);
    PrintMTG(G);
    do{
        Menu();
        cout<<"����ѡ����:"<<endl;
        cin>>choice;
        if(choice<=0||choice>=6)
        {
            break;
        }
        switch (choice)
        {
        case 1:
            Dijkstra(G);
            PrintDijkstra(G);
            break;
        case 2:
            Floyd(G);
            FloydPrint(G);
            break;
        case 3:
            Floyd(G);
            PrintFloy1(G);
            break;
        case 4:
            Floyd(G);
            PrintFloy2(G);
            break;
        case 5:
            Warshall(G,&MT);
            PrintWarshall(MT);
            break;
        default:
            break;
        }
    }while(choice>0&&choice<6);
    return 0;
}
void Menu()
{
    cout<<"1.Dijkstra�㷨,���ԭ�㼰�䵽������������·�����Ⱥ����·��;"<<endl;
    cout<<"2.Floyd�㷨,�������������������·�����Ⱥ����·��;"<<endl;
    cout<<"3.��Ŀ�����·������(ÿ������v��ָ������c);"<<endl;
    cout<<"4.������Լ����·��(ĳ������u��ĳ������v);"<<endl;
    cout<<"5.Warshall�ó�����ͼ�Ŀɴ����."<<endl;
}
void CreateG(MTGraph *G)//����ͼ���ڽӾ���
{
    for(int i=0;i<M;i++)//�����ʼ��
    {
        G->vertex[i]=i;
        G->edge[i][i]=0;
        for(int j=i+1;j<M;j++)
        {
            G->edge[i][j]=MIN;
            G->edge[j][i]=MIN;
        }
    }
    GetData(G);
}
void GetData(MTGraph *G)
{
    int x1,x2,y;//�ڽӾ����ʼ���м����
    ifstream file;
    file.open("graph.txt");
    if(file.fail())
    {
        cout<<"�ļ���ʧ��.";
    }
    else
    {
        file>>G->n>>G->e;
        while(!file.eof())
        {
            file>>x1>>x2>>y;
            G->edge[x1][x2]=y;
        }
    }
    file.close();
}
int Mincost(MTGraph G)//��ȡ��ǰ���·�����±�
{
    int temp=MIN;//�趨Ĭ��ֵΪ��Сֵ
    int w=1;
    for(int i=1;i<G.n;i++)
    {
        if(S[i]!=true&&D[i]<temp)//δ�ҵ����·����·������
        {
            temp=D[i];
            w=i;//��¼�±�,׼������
        }
    }
    return w;
}
void Dijkstra(MTGraph G)//Dijstrat�㷨���
{
    int k,sum;
    for(int i=0;i<G.n;i++)//��ʼĬ��0Ϊ������Ļ���Ϊ���·��
    {
        D[i]=G.edge[0][i];
    }
    for(int i=0;i<G.n;i++)//����������ʼ��
    {
        P[i]=0;
        S[i]=false;
    }
    S[0]=true;
    for(int i=1;i<G.n;i++)
    {
        k=Mincost(G);//��õ�ǰ���·���±�
        S[k]=true;//����k�Ѿ�����
        for(int j=1;j<G.n;j++)
        {
            if(S[j]!=true)
            {
                sum=D[k]+G.edge[k][j];
                if(sum<D[j])//��ǰ·����ԭ·����
                {
                    D[j]=sum;
                    P[j]=k;
                }
            }
        }
    }
}
void PrintDijkstra(MTGraph G)//��ʾDijkstra�㷨�����
{
    for(int i=1;i<G.n;i++)//���Դ�㵽������������·��������
    {
        if(D[i]!=MIN)//Դ�㵽����i����·��
        {
            cout<<"0---"<<i<<"��̳���Ϊ:\t"<<D[i]<<endl;
            stack<int>s;
            s.push(i);
            int x=P[i];
            while(x!=0)//����ջ,���±귴�����,��Ϊ·��
            {
                s.push(x);
                x=P[x];
            }
            s.push(0);
            cout<<"0---"<<i<<"·��Ϊ�� ";
            while(!s.empty())
            {
                cout<<s.top() <<"-";
                s.pop() ;
            }
            cout<<endl;
        }
        else
        {
        cout<<"0��"<<i<<"��·��"<<endl;
        }
    }
}
void PrintMTG(MTGraph G)//��ʾ�ڽӾ�����
{
    cout<<"�ڽӾ���������:\n";
    for(int i=0;i<G.n;i++)
    {
        cout<<"\t"<<i;
    }
    cout<<endl;
    for(int i=0;i<G.n;i++)
    {
        cout<<i<<"\t";
        for(int j=0;j<G.n;j++)
        {
            if(G.edge[i][j]==MIN)
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
void Floyd(MTGraph G)//Floyd�㷨���ݳ�ʼ��
{
    for(int i=0;i<G.n;i++)
    {
        for(int j=0;j<G.n;j++)
        {
            D2[i][j]=G.edge[i][j];
            if(D2[i][j]!=MIN)
            {
                P2[i][j]=-1;
            }
            else
            {
                P2[i][j]=-2;
            }
        }
    }
    for(int k=0;k<G.n;k++)
    {
        for(int i=0;i<G.n;i++)
        {
            for(int j=0;j<G.n;j++)
            {
                if(D2[i][k]+D2[k][j]<D2[i][j])
                {
                    D2[i][j]=D2[i][k]+D2[k][j];//���¶���֮�����̾���
                    P2[i][j]=k;//��¼���·�������Ķ���
                }
            }
        }
    }
}
void FloydPrint(MTGraph G)//��ʾFloyd�㷨�����
{
    cout<<"ÿ������֮������·����������:"<<endl;
    for(int i=0;i<G.n;i++)
    {
        cout<<"\t"<<i;
    }
    cout<<endl;
    for(int i=0;i<G.n;i++)
    {
        cout<<i<<"\t";
        for(int j=0;j<G.n;j++)
        {
            if(D2[i][j]!=MIN)
            {
                cout<<D2[i][j]<<"\t";
            }
            else
            {
                cout<<"��\t";
            }
        }
        cout<<endl;
    }
}
void Floyd_mn(MTGraph G,int m,int n)//�ݹ���ⶥ��m,n�����·���;���
{
    if(P2[m][n]==-2)
    {
        cout<<m<<"��"<<n<<"֮��û��·��"<<endl;
    }
    else if(P2[m][n]==-1)
    {
        cout<<m<<"-"<<n<<" ";
    }
    else
    {
        Floyd_mn(G,m,P2[m][n]);
        Floyd_mn(G,P2[m][n],n);
    }
}
void PrintFloy2(MTGraph G)//��ʾ����ָ����������֮��·�����
{
    int m,n;
    cout<<"������������������·�����±�:"<<endl;
    cin>>m;
    cin>>n;
    if(D2[m][n]!=MIN)
    {
        cout<<"����"<<m<<" "<<n<<"֮�����·��Ϊ:"<<endl;
    }
    Floyd_mn(G,m,n);
    if(D2[m][n]!=MIN)
    {
        cout<<"����"<<m<<" "<<n<<"֮�����·������Ϊ:"<<D2[m][n]<<endl;
    }
}
void PrintFloy1(MTGraph G)//��ʾÿ������v��ĳ��ָ������c���·�����
{
    int c;
    cout<<"����ָ������c�±�:"<<endl;
    cin>>c;
    for(int i=0;i<G.n;i++)
    {
        if(i!=c)
        {
            if(D2[i][c]!=MIN)
            {
                cout<<"����"<<i<<" "<<c<<"֮�����·��Ϊ:"<<endl;
            }
            Floyd_mn(G,i,c);
            if(D2[i][c]!=MIN)
            {
                cout<<"����"<<i<<" "<<c<<"֮�����·������Ϊ:"<<D2[i][c]<<endl;
            }
        }
        cout<<endl;
    }
}
void Warshall(MTGraph G,MT_Get *MT)
{
    MT->n=G.n;
    for(int i=0;i<MT->n;i++)//D3�����ʼ��
    {
        for(int j=0;j<MT->n;j++)
        {
            if(i==j||G.edge[i][j]!=MIN)
            {
                MT->Get[i][j]=true;//ͬһ������ɴ�
            }
            else
            {
                MT->Get[i][j]=false;//��������
            }
        }
    }
    for(int i=0;i<MT->n;i++)//������˳��,���λ�����пɴ����ֵ
    {
        for(int j=0;j<MT->n;j++)
        {
            if(MT->Get[i][j])//��ǰԪ���Ƿ�����ɴ��ϵ
            {
                for(int k=0;k<MT->n;k++)
                {
                    MT->Get[i][k]=MT->Get[i][k]||MT->Get[j][k];//[i][j]�ɴ���[j][k]�ɴ���[i][k]�ɴ�
                }
            }
        }
    }
}
void PrintWarshall(MT_Get MT)
{
    for(int i=0;i<MT.n;i++)
    {
        cout<<"\t"<<i;
    }
    cout<<endl;
    for(int i=0;i<MT.n;i++)
    {
        cout<<i<<"\t";
        for(int j=0;j<MT.n;j++)
        {
            if(MT.Get[i][j])//�ɴ���ʾ1
            {
                cout<<"1\t";
            }
            else//���ɴ���ʾ0
            {
                cout<<"0\t";
            }
        }
        cout<<endl;
    }
}
