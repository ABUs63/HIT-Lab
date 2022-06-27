#include <iostream>
#include <queue>
#include <stack>
#define M 15

using namespace std;

typedef struct{
    int vertex[M];//顶点表
    int edge[M][M];//边表
    int n,e;//顶点数、边数
}MTGraph;//邻接矩阵
typedef struct node{
    int adjvex;//下标
    int cost;//边权值
    struct node *next;
}EdgeNode;//边表结点
typedef struct{
    int vertex;//数据域
    EdgeNode *firstedge;
}VertexNode;//顶点表
typedef struct{
    VertexNode vexlist[M];
    int n,e;
}AdjGraph;//邻接表
typedef struct{
    int degree[M];//各个顶点的度
    int n;//顶点个数
}Degree;//顶点的度

bool visited[M];//访问标记
int COUNT;//森林编号用
int COUNT2;//顶点编号用
int dfn[M];//遍历编号存储

void Menu();//功能菜单显示
void CreateMTGraph(MTGraph *G);//创建图的领接矩阵
void CreateAdjGraph(AdjGraph *G);//创建图的邻接表
void MT_toAdj(MTGraph MG,AdjGraph *AG);//邻接矩阵转化为邻接表
void Adj_toMT(AdjGraph AG,MTGraph *MG);//邻接表转化为邻接矩阵
void ADFSTraverse(AdjGraph G);//递归深度优先搜索主算法--邻接表
void ADFS(AdjGraph G,int i);//深度优先搜索递归子算法--邻接表
void MDFSTraverse(MTGraph G);//递归深度优先搜索主算法--邻接矩阵
void MDFS(MTGraph G,int i);//深度优先搜索递归子算法--邻接矩阵
void NoADFS(AdjGraph G);//非递归深度优先搜索--邻接表
void NoMDFS(MTGraph G);//非递归深度优先搜索--邻接矩阵
void ABFS(AdjGraph *G);//广度优先搜索--邻接表
void MBFS(MTGraph *G);//广度优先搜索--邻接矩阵
void CalculateDegree(AdjGraph AG,Degree *d);//利用邻接表计算各个顶点的度
void PrintMT(MTGraph G);//显示图的邻接矩阵信息
void PrintAdj(AdjGraph G);//显示图的邻接表信息

int main()
{
    MTGraph G1;//邻接矩阵
    AdjGraph G2;//邻接表
    Degree degree;//顶点度
    int choice;
    do{
        Menu();
        cout<<"输入功能选择\n";
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
                cout<<"邻接矩阵:\n";
                MDFSTraverse(G1);
                cout<<"先深顶点编号:\n";
                for(int i=0;i<G1.n;i++)
                {
                    cout<<G1.vertex[i]<<"->"<<dfn[i]<<endl;
                }
                cout<<endl;
                cout<<"邻接表:\n";
                ADFSTraverse(G2);
                cout<<"先深顶点编号:\n";
                for(int i=0;i<G2.n;i++)
                {
                    cout<<G2.vexlist[i].vertex<<"->"<<dfn[i]<<endl;
                }
                cout<<endl;
                break;
            case 6:
                cout<<"邻接矩阵:\n";
                NoMDFS(G1);
                cout<<"先深顶点编号:\n";
                for(int i=0;i<G1.n;i++)
                {
                    cout<<G1.vertex[i]<<"->"<<dfn[i]<<endl;
                }
                cout<<endl;
                cout<<"邻接表:\n";
                NoADFS(G2);
                cout<<"先深顶点编号:\n";
                for(int i=0;i<G2.n;i++)
                {
                    cout<<G2.vexlist[i].vertex<<"->"<<dfn[i]<<endl;
                }
                cout<<endl;
                break;
            case 7:
                cout<<"邻接矩阵:\n";
                MBFS(&G1);
                cout<<"先广顶点编号:\n";
                for(int i=0;i<G1.n;i++)
                {
                    cout<<G1.vertex[i]<<"->"<<dfn[i]<<endl;
                }
                cout<<endl;
                cout<<"邻接表:\n";
                ABFS(&G2);
                cout<<"先广顶点编号:\n";
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
    cout<<"默认顶点的下标为0~n-1;"<<endl;
    cout<<"1.创建邻接矩阵并显示结果;"<<endl;
    cout<<"2.创建邻接表并显示结果;"<<endl;
    cout<<"3.创建好的邻接矩阵转化为邻接表并显示结果;"<<endl;
    cout<<"4.创建好的邻接表转化为邻接矩阵并显示结果;"<<endl;
    cout<<"5.递归深度优先搜索;"<<endl;
    cout<<"6.非递归深度优先搜索;"<<endl;
    cout<<"7.广度优先搜索;"<<endl;
    cout<<"8.根据已有的邻接表计算各顶点的度并显示结果;"<<endl;
}
void CreateMTGraph(MTGraph *G)//创建邻接矩阵
{
    int i,j,k,w;
    cout<<"输入顶点数:\n";
    cin>>G->n;
    cout<<"输入边数:\n";
    cin>>G->e;
    for(i=0;i<G->n;i++)
    {
        G->vertex[i]=i;//默认顶点下标依次0~n-1
    }
    for(i=0;i<G->n;i++)
    {
        for(j=0;j<G->n;j++)
        {
            G->edge[i][j]=0;//边权值初始化
        }
    }
    for(k=0;k<G->e;k++)
    {
        cout<<"分别输入顶点i,j和(i,j)的权值:\n";
        cin>>i;
        cin>>j;
        cin>>w;
        G->edge[i][j]=w;
        G->edge[j][i]=w;
    }
}
void CreateAdjGraph(AdjGraph *G)//创建邻接表
{
    int tail,head,weight;
    cout<<"分别输入顶点个数,边数:\n";
    cin>>G->n;
    cin>>G->e;
    for(int i=0;i<G->n;i++)
    {
        G->vexlist[i].vertex=i;//默认下标为依次0~n-1
        G->vexlist[i].firstedge=NULL;//邻接表初始置空
    }
    for(int i=0;i<G->e;i++)//头插法连接新结点
    {
        cout<<"输入顶点i,j,边(i,j)的权值:\n";
        cin>>tail;//顶点1
        cin>>head;//顶点j
        cin>>weight;//(i,j)的权值
        EdgeNode *p=new EdgeNode;//无向图的邻接表,同时创建两个顶点的邻接表
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
void MT_toAdj(MTGraph MG,AdjGraph *AG)//邻接矩阵转化为邻接表
{
    int i,j,k;
    AG->n=MG.n;
    AG->e=MG.e;
    for(i=0;i<AG->n;i++)//邻接表初始化
    {
        AG->vexlist[i].vertex=MG.vertex[i];
        AG->vexlist[i].firstedge=NULL;
    }
    for(j=0;j<AG->n;j++)
    {
        for(k=j;k<AG->n;k++)
        {
            if(MG.edge[j][k]!=0)//(j,k)边存在,创建相应边表、顶点表
            {
                EdgeNode *p=new EdgeNode;//j边表
                p->cost=MG.edge[j][k];
                p->adjvex=j;
                p->next=AG->vexlist[k].firstedge;
                AG->vexlist[k].firstedge=p;
                EdgeNode *q=new EdgeNode;//k边表
                q->cost=p->cost;
                q->adjvex=k;
                q->next=AG->vexlist[j].firstedge;
                AG->vexlist[j].firstedge=q;
            }
        }
    }
}
void Adj_toMT(AdjGraph AG,MTGraph *MG)//邻接表转化为邻接矩阵
{
    MG->n=AG.n;
    MG->e=AG.e;
    EdgeNode *temp=NULL;
    for(int i=0;i<AG.n;i++)//邻接矩阵初始化
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
        while(temp!=NULL)//根据邻接表某顶点边表，创建相应矩阵的行
        {
            MG->edge[i][temp->adjvex]=temp->cost;
            MG->edge[temp->adjvex][i]=temp->cost;
            temp=temp->next;
        }
    }
}
void ADFSTraverse(AdjGraph G)//先深递归--主--邻接表
{
    COUNT=1;//全局变量初始化
    COUNT2=1;
    for(int i=0;i<G.n;i++)
    {
        visited[i]=false;
    }
    for(int i=0;i<G.n;i++)
    {
        if(!visited[i])
        {
            cout<<"森林"<<COUNT++<<" ";//显示先深森林
            ADFS(G,i);
            cout<<endl;
        }
    }
}
void ADFS(AdjGraph G,int i)//先深递归--子--邻接表
{
    EdgeNode *p=NULL;
    cout<<G.vexlist[i].vertex<<" ";//显示先深森林的相应顶点
    visited[i]=true;
    dfn[i]=COUNT2++;//记录顶点先深编号
    p=G.vexlist[i].firstedge;
    while(p)//此顶点有邻接的顶点
    {
        if(!visited[p->adjvex])
        {
            ADFS(G,p->adjvex);//递归访问下一顶点的邻接顶点
        }
        p=p->next;
    }
}
void MDFSTraverse(MTGraph G)//先深递归--主--邻接矩阵
{
    COUNT=1;//全局变量初始化
    COUNT2=1;
    for(int i=0;i<G.n;i++)
    {
        visited[i]=false;
    }
    for(int i=0;i<G.n;i++)
    {
        if(!visited[i])
        {
            cout<<"森林"<<COUNT++<<":";//显示先深森林
            MDFS(G,i);
            cout<<endl;
        }
    }
}
void MDFS(MTGraph G,int i)//先深递归--字--邻接矩阵
{
    int j;
    cout<<G.vertex[i]<<" ";//显示先深森林的顶点
    visited[i]=true;
    dfn[i]=COUNT2++;//顶点进行先深编号
    for(j=0;j<G.n;j++)
    {
        if((G.edge[i][j]!=0)&&!visited[j])//i顶点与j相邻且j未访问
        {
            MDFS(G,G.vertex[j]);//递归进行j顶点先深搜索
        }
    }
}
void NoADFS(AdjGraph G)//先深非递归--邻接表
{
    for(int i=0;i<G.n;i++)//全局变量初始化
    {
        visited[i]=false;
    }
    COUNT=1;
    COUNT2=1;
    EdgeNode *p=NULL;
    bool flag;
    stack<int>s;//利用栈达到递归效果
    for(int i=0;i<G.n;i++)
    {
        if(!visited[i])
        {
            cout<<"森林"<<COUNT++<<":";//先深森林显示
            visited[i]=true;
            dfn[i]=COUNT2++;//先深编号
            s.push(i);
            cout<<G.vexlist[i].vertex<<" ";//森林顶点显示
            p=G.vexlist[i].firstedge;
            while(!s.empty())
            {
                p=G.vexlist[s.top()].firstedge;
                flag=false;
                while(p)//顶点i有邻接的顶点
                {
                    if(!visited[p->adjvex])//当前邻接的点未访问
                    {
                        visited[p->adjvex]=true;
                        cout<<G.vexlist[p->adjvex].vertex<<" ";//顶点显示
                        dfn[p->adjvex]=COUNT2++;//编号
                        s.push(p->adjvex);//记录此顶点,遍历完某邻接顶点后,进行下一邻接顶点遍历
                        p=G.vexlist[p->adjvex].firstedge;
                        flag=true;
                        break;
                    }
                    else//当前邻接的点访问,看下一个邻接的顶点
                    {
                        p=p->next;
                    }
                }
                if(!flag)//没有邻接的顶点
                {
                    s.pop();
                }
            }
            cout<<endl;
        }
    }
}
void NoMDFS(MTGraph G)//先深非递归--邻接矩阵
{
    for(int i=0;i<G.n;i++)//全局变量初始化
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
            cout<<"森林"<<COUNT++<<":";//先深森林显示
            dfn[j]=COUNT2++;//顶点先深编号
            visited[j]=true;
            s.push(j);
            cout<<G.vertex[j]<<" ";//森林顶点显示
            while(!s.empty())
            {
                t=s.top();
                flag=false;
                for(int k=0;k<G.n;k++)
                {
                    if(G.edge[t][k]!=0)//t,k邻接
                    {
                        if(!visited[k])//k未访问
                        {
                            visited[k]=true;
                            cout<<G.vertex[k]<<" ";//顶点显示
                            dfn[k]=COUNT2++;//编号
                            s.push(k);//记录当前顶点k,遍历完k某邻接顶点后,进行k下一邻接顶点遍历
                            flag=true;
                            break;
                        }
                    }
                }
                if(!flag)//顶点无邻接顶点
                {
                    s.pop();
                }
            }
            cout<<endl;
        }
    }
}
void ABFS(AdjGraph *G)//先广--邻接表
{
    COUNT=1;//全局变量初始化
    COUNT2=1;
    for(int j=0;j<G->n;j++)
    {
        visited[j]=false;
    }
    queue<int>s;//类似层序遍历,用队列
    EdgeNode *p;
    for(int i=0;i<G->n;i++)
    {
        if(!visited[i])
        {
            cout<<"森林"<<COUNT++<<":";//先广森林显示
            visited[i]=true;
            dfn[i]=COUNT2++;//顶点编号
            cout<<G->vexlist[i].vertex<<" ";
            s.push(G->vexlist[i].vertex);//记录当前顶点i
            while(!s.empty())
            {
                p=G->vexlist[s.front()].firstedge;
                s.pop();
                while(p!=NULL)//将顶点i邻接且未访问的顶点访问并入队记录
                {
                    if(!visited[p->adjvex])
                    {
                        visited[p->adjvex]=true;
                        cout<<G->vexlist[p->adjvex].vertex<<" ";
                        dfn[p->adjvex]=COUNT2++;//先广编号
                        s.push(p->adjvex);
                    }
                    p=p->next;
                }
            }
            cout<<endl;
        }
    }
}
void MBFS(MTGraph *G)//先广--邻接矩阵
{
    for(int i=0;i<G->n;i++)//全局变量初始化
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
            cout<<"森林"<<COUNT++<<":";//先广森林显示
            visited[i]=true;
            cout<<G->vertex[i]<<" ";
            dfn[i]=COUNT2++;//先广编号
            s.push(G->vertex[i]);//记录当前顶点i
            while(!s.empty())
            {
                k=s.front();
                s.pop();
                for(int j=0;j<G->n;j++)
                {
                    if(G->edge[k][j]!=0)//k邻接且未访问的顶点j进行访问并入队记录
                    {
                        if(!visited[j])
                        {
                            cout<<G->vertex[j]<<" ";
                            visited[j]=true;
                            dfn[j]=COUNT2++;//先广编号
                            s.push(G->vertex[j]);
                        }
                    }
                }
            }
            cout<<endl;
        }
    }
}
void CalculateDegree(AdjGraph AG,Degree *d)//邻接表计算各顶点的度
{
    d->n=AG.n;
    EdgeNode *temp=NULL;
    for(int i=0;i<d->n;i++)//记录顶点度初始化
    {
        d->degree[i]=0;
    }
    for(int i=0;i<AG.n;i++)
    {
        temp=AG.vexlist[i].firstedge;
        while(temp!=NULL)//遍历所有边表的顶点表并计数
        {
            d->degree[i]++;
            temp=temp->next;
        }
    }
    for(int i=0;i<d->n;i++)//显示结果
    {
        cout<<"下标为:"<<AG.vexlist[i].vertex<<"的顶点度为:"<<d->degree[i]<<endl;
    }
}
void PrintMT(MTGraph G)
{
    cout<<"图的邻接矩阵如下:\n";
    cout<<"顶点信息:\n";
    for(int i=0;i<G.n;i++)
    {
        cout<<G.vertex[i]<<endl;
    }
    cout<<"边信息:\n";
    for(int i=0;i<G.n;i++)
    {
        for(int j=0;j<G.n;j++)
        {
            if(G.edge[i][j]==0)//不邻接,权值为∞
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
void PrintAdj(AdjGraph G)
{
    EdgeNode *temp=NULL;
    cout<<"图的邻接表如下:\n";
    for(int i=0;i<G.n;i++)
    {
        cout<<G.vexlist[i].vertex<<"\t与该顶点邻接的点及边:\n";
        temp=G.vexlist[i].firstedge;
        if(temp==NULL)
        {
            cout<<"没有与该顶点邻接的顶点"<<endl;
        }
        while(temp!=NULL)
        {
            cout<<"下标:"<<temp->adjvex<<"\t边的权值:"<<temp->cost<<endl;
            temp=temp->next;
        }
    }
}
