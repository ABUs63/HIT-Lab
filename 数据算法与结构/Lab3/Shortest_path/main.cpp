#include <iostream>
#include <stack>
#include <fstream>
#include <istream>
#define M 15
#define MIN 65535

using namespace std;

typedef struct{
    int vertex[M];//顶点下标,默认与数组下标相同
    int edge[M][M];//边权值
    int n,e;//顶点数,边数
}MTGraph;
typedef struct{
    bool Get[M][M];//两个顶点是否可达(有向图)
    int n;//顶点数
}MT_Get;

bool S[M];//判断每个顶点是否已经求出最短路径
int D[M];//存放从源点到各个顶点的最短路径长度
int P[M];//记录每个最短路径的某个节点的前一个节点的编号
int D2[M][M];//存放任意两个顶点之间的最短路径长度
int P2[M][M];//存放任意两个顶点之间的最短路径编号

void Menu();//功能菜单显示
void CreateG(MTGraph *G);//创建邻接矩阵
void GetData(MTGraph *G);//从文件中读取邻接矩阵数据
int Mincost(MTGraph G);//计算当前最短路径的下标w
void Dijkstra(MTGraph G);//求源点0到每个顶点的最短路径
void PrintDijkstra(MTGraph G);//输出源点0到每个顶点的最短路径长度和最短路径
void Floyd(MTGraph G);//Floyd算法初始化
void Floyd_mn(MTGraph G,int m,int n);//求m,n最短路径并存储在P2中
void FloydPrint(MTGraph G);//显示Floyd算法求解结果
void PrintFloy1(MTGraph G);//显示每个顶点v到某个指定顶点c之间的最短路径结果
void PrintFloy2(MTGraph G);//显示任意两个指定顶点间最短路径结果
void Warshall(MTGraph G,MT_Get *MT);//Warshall算法初始化可达矩阵信息D3[M][M]
void PrintWarshall(MT_Get MT);//显示Floyd算法实现有向图可达矩阵
void PrintMTG(MTGraph G);//显示邻接矩阵结果

int main()
{
    int choice;
    MTGraph G;
    MT_Get MT;
    CreateG(&G);
    PrintMTG(G);
    do{
        Menu();
        cout<<"输入选择功能:"<<endl;
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
    cout<<"1.Dijkstra算法,输出原点及其到其他顶点的最短路径长度和最短路径;"<<endl;
    cout<<"2.Floyd算法,输出任意两个顶点间最短路径长度和最短路径;"<<endl;
    cout<<"3.单目标最短路径问题(每个顶点v到指定顶点c);"<<endl;
    cout<<"4.单顶点对间最短路径(某个顶点u到某个顶点v);"<<endl;
    cout<<"5.Warshall得出有向图的可达矩阵."<<endl;
}
void CreateG(MTGraph *G)//创建图的邻接矩阵
{
    for(int i=0;i<M;i++)//矩阵初始化
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
    int x1,x2,y;//邻接矩阵初始化中间变量
    ifstream file;
    file.open("graph.txt");
    if(file.fail())
    {
        cout<<"文件打开失败.";
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
int Mincost(MTGraph G)//获取当前最短路径的下标
{
    int temp=MIN;//设定默认值为最小值
    int w=1;
    for(int i=1;i<G.n;i++)
    {
        if(S[i]!=true&&D[i]<temp)//未找到最短路径且路径更短
        {
            temp=D[i];
            w=i;//记录下标,准备返回
        }
    }
    return w;
}
void Dijkstra(MTGraph G)//Dijstrat算法求解
{
    int k,sum;
    for(int i=0;i<G.n;i++)//初始默认0为到各点的弧长为最短路径
    {
        D[i]=G.edge[0][i];
    }
    for(int i=0;i<G.n;i++)//辅助变量初始化
    {
        P[i]=0;
        S[i]=false;
    }
    S[0]=true;
    for(int i=1;i<G.n;i++)
    {
        k=Mincost(G);//获得当前最短路径下标
        S[k]=true;//顶点k已经考虑
        for(int j=1;j<G.n;j++)
        {
            if(S[j]!=true)
            {
                sum=D[k]+G.edge[k][j];
                if(sum<D[j])//当前路径比原路径短
                {
                    D[j]=sum;
                    P[j]=k;
                }
            }
        }
    }
}
void PrintDijkstra(MTGraph G)//显示Dijkstra算法求解结果
{
    for(int i=1;i<G.n;i++)//输出源点到其他顶点的最短路径及长度
    {
        if(D[i]!=MIN)//源点到顶点i存在路径
        {
            cout<<"0---"<<i<<"最短长度为:\t"<<D[i]<<endl;
            stack<int>s;
            s.push(i);
            int x=P[i];
            while(x!=0)//借助栈,将下标反向输出,即为路径
            {
                s.push(x);
                x=P[x];
            }
            s.push(0);
            cout<<"0---"<<i<<"路径为： ";
            while(!s.empty())
            {
                cout<<s.top() <<"-";
                s.pop() ;
            }
            cout<<endl;
        }
        else
        {
        cout<<"0到"<<i<<"无路径"<<endl;
        }
    }
}
void PrintMTG(MTGraph G)//显示邻接矩阵结果
{
    cout<<"邻接矩阵结果如下:\n";
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
                cout<<"∞\t";
            }
            else
            {
                cout<<G.edge[i][j]<<"\t";
            }
        }
        cout<<endl;
    }
}
void Floyd(MTGraph G)//Floyd算法数据初始化
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
                    D2[i][j]=D2[i][k]+D2[k][j];//更新顶点之间的最短距离
                    P2[i][j]=k;//记录最短路径经过的顶点
                }
            }
        }
    }
}
void FloydPrint(MTGraph G)//显示Floyd算法求解结果
{
    cout<<"每个顶点之间的最短路径长度如下:"<<endl;
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
                cout<<"∞\t";
            }
        }
        cout<<endl;
    }
}
void Floyd_mn(MTGraph G,int m,int n)//递归求解顶点m,n的最短路径和距离
{
    if(P2[m][n]==-2)
    {
        cout<<m<<"和"<<n<<"之间没有路径"<<endl;
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
void PrintFloy2(MTGraph G)//显示任意指定两个顶点之间路径结果
{
    int m,n;
    cout<<"输入待求两个顶点最短路径的下标:"<<endl;
    cin>>m;
    cin>>n;
    if(D2[m][n]!=MIN)
    {
        cout<<"顶点"<<m<<" "<<n<<"之间最短路径为:"<<endl;
    }
    Floyd_mn(G,m,n);
    if(D2[m][n]!=MIN)
    {
        cout<<"顶点"<<m<<" "<<n<<"之间最短路径长度为:"<<D2[m][n]<<endl;
    }
}
void PrintFloy1(MTGraph G)//显示每个顶点v到某个指定顶点c最短路径结果
{
    int c;
    cout<<"输入指定顶点c下标:"<<endl;
    cin>>c;
    for(int i=0;i<G.n;i++)
    {
        if(i!=c)
        {
            if(D2[i][c]!=MIN)
            {
                cout<<"顶点"<<i<<" "<<c<<"之间最短路径为:"<<endl;
            }
            Floyd_mn(G,i,c);
            if(D2[i][c]!=MIN)
            {
                cout<<"顶点"<<i<<" "<<c<<"之间最短路径长度为:"<<D2[i][c]<<endl;
            }
        }
        cout<<endl;
    }
}
void Warshall(MTGraph G,MT_Get *MT)
{
    MT->n=G.n;
    for(int i=0;i<MT->n;i++)//D3矩阵初始化
    {
        for(int j=0;j<MT->n;j++)
        {
            if(i==j||G.edge[i][j]!=MIN)
            {
                MT->Get[i][j]=true;//同一个顶点可达
            }
            else
            {
                MT->Get[i][j]=false;//其他顶点
            }
        }
    }
    for(int i=0;i<MT->n;i++)//按照行顺序,依次获得整行可达矩阵值
    {
        for(int j=0;j<MT->n;j++)
        {
            if(MT->Get[i][j])//当前元素是否满足可达关系
            {
                for(int k=0;k<MT->n;k++)
                {
                    MT->Get[i][k]=MT->Get[i][k]||MT->Get[j][k];//[i][j]可达且[j][k]可达则[i][k]可达
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
            if(MT.Get[i][j])//可达显示1
            {
                cout<<"1\t";
            }
            else//不可达显示0
            {
                cout<<"0\t";
            }
        }
        cout<<endl;
    }
}
