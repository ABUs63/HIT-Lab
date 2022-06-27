#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <cstring>
#define MAX 54//包括字母大小写',''.'以及' '
#define N 2*MAX-1//n个叶子结点的哈夫曼树有2n-1结点
#define KN 2*MAX//三进制编码结点

using namespace std;
typedef struct data DATA;
typedef struct htnode Huffman[N];
typedef struct khtnode KHuffman[KN];
typedef char *Huffmancode[MAX];
typedef struct worddata WORDDATA;
struct data{
    int data[MAX];//统计出现次数
    char value[MAX];//记录对应字符
    double weight[MAX];//记录对应字符权重
    int total;//统计文章总字符数
};
struct htnode{
    double weight;//权重
    int lchild;//左孩子
    int rchild;//右孩子
    int parent;//父亲
};
struct khtnode{
    double weight;//权重
    int child1;//左孩子
    int child2;//右孩子1
    int child3;//右孩子2
    int parent;//父亲
    bool temp;//是否被选择过
};
struct worddata{
    int data[1000];//统计出现次数
    string value[1000];//记录对应单词,忽略空格,标点
    double weight[1000];//记录对应单词权值
    int total;//统计文章总单词数
    int typenum;//统计种类
};

void PrintForm(DATA *data,Huffmancode HT);//显示文件字符统计表
void GetData(DATA *data);//打开文件,统计出现次数
void GetValue(DATA *data);//初始化value在data每一项对应字符以及总字符数
void SelectMin(Huffman &T,int k,int &s1,int &s2);//选出权重最小的两个结点
void CreateHuffTree(Huffman &T,DATA *data,int n);//构造哈夫曼树
void EncodeHuff(Huffman T,Huffmancode &HT);//对每个叶结点编码
void GetFile(Huffmancode HT,DATA *data);//对文件进行哈夫曼压缩
void DecodeHuffFile(Huffman T,DATA *data);//解哈夫曼码并写入文件
void DecodeHuff(Huffman T,DATA *data,char test[],char *result);//寻找哈夫曼码对应字符
void Calculate(Huffmancode HT,DATA *data);//计算长度、压缩率等
void GetWData(WORDDATA *wdata);//打开文件,统计出现次数
void WCreateHuffTree(Huffman &T,WORDDATA *wdata,int n);//单词操作--构造哈夫曼树
void WGetFile(Huffmancode HT,WORDDATA *wdata);//单词操作--对文件进行哈夫曼压缩
void WDecodeHuffFile(Huffman T,WORDDATA *wdata);//单词操作--解哈夫曼码并写入文件
void WDecodeHuff(Huffman T,WORDDATA *wdata,char test[]);//单词操作--寻找哈夫曼码对应字符
void WCalculate(Huffmancode HT,WORDDATA *wdata);//单词操作--计算长度、压缩率等
void KEncodeHuff(KHuffman T,Huffmancode &KHT);//对每个叶节点进行K进制编码
int KCreateHuffTree(KHuffman &T,DATA *data,int n);//构造K进制哈夫曼树
void SelectKMin(KHuffman &T,int k,int *s1,int *s2,int *s3);//选出权重最小的3个结点
void KGetFile(Huffmancode HT,DATA *data);//对文件进行K进制哈夫曼压缩
void KDecodeHuffFile(KHuffman T,DATA *data,int knode);//解哈夫曼码并写入文件
void KDecodeHuff(KHuffman T,DATA *data,char test[],char *result,int knode);//寻找哈夫曼码对应字符
void Menu();//功能菜单显示

int main()
{
    int choice,knode;
    DATA data;//按照字符统计频率
    WORDDATA wdata;//按照单词统计频率
    Huffman Tree,WTree;//二进制哈夫曼树
    KHuffman KTree;//k进制哈夫曼树
    Huffmancode HT,WHT,KHT;//编码结果
    GetData(&data);//从文本文件中读取字符
    GetValue(&data);//计算字符权值并初始化对应字符
    GetWData(&wdata);//计算单词权值
    CreateHuffTree(Tree,&data,MAX);//构造哈夫曼树
    WCreateHuffTree(WTree,&wdata,wdata.typenum);//构造基于单词哈夫曼树
    knode=KCreateHuffTree(KTree,&data,MAX);//创建K进制哈夫曼树
    EncodeHuff(Tree,HT);//哈夫曼编码
    KEncodeHuff(KTree,KHT);//K进制哈夫曼编码
    EncodeHuff(WTree,WHT);//基于单词哈夫曼编码
    do{
        Menu();
        cout<<"输入选择"<<endl;
        cin>>choice;
        if(choice<=0||choice>=7)
        {
            break;
        }
        switch (choice)
        {
        case 1:
            PrintForm(&data,HT);//显示字符相关信息
            break;
        case 2:
            GetFile(HT,&data);//字符文件压缩为哈夫曼文件
            break;
        case 3:
            DecodeHuffFile(Tree,&data);//解码字符哈夫曼文件，并输出解码结果到其他文件
            break;
        case 4:
            Calculate(HT,&data);//计算字符编码平均长度、压缩率
            break;
        case 5:
            cout<<"该文件的单词总数为:"<<wdata.total<<endl;
            cout<<"该文件的各单词统计:"<<endl;
            for(int i=0;i<wdata.typenum;i++)
            {
                cout<<wdata.value[i]<<"出现过"<<wdata.data[i]<<"次\t权重为"<<wdata.weight[i]<<"\n编码为:"<<WHT[i]<<endl;
            }
            WGetFile(WHT,&wdata);//压缩至文件中
            WDecodeHuffFile(WTree,&wdata);//解压至另一文件中
            WCalculate(WHT,&wdata);//计算并显示压缩效果
            break;
        case 6:
            PrintForm(&data,KHT);//显示字符相关信息
            KGetFile(KHT,&data);//压缩至文件
            KDecodeHuffFile(KTree,&data,knode);//解压至文件
            Calculate(KHT,&data);//计算压缩效果并显示
            break;
        default:
            break;
        }
    }while(choice>0&&choice<7);
    cout<<"不在选择范围内,结束功能"<<endl;
    return 0;
}
void GetData(DATA *data)//打开文件,并统计各字符出现的次序
{
    fstream file;
    file.open("text.txt");//打开编码文件
    if(file.fail())
    {
        cout<<"text文件打开失败,请检查文件"<<endl;
        return ;
    }
    else
    {
        data->total=0;//总计数目初始化
        for(int i=0;i<MAX;i++)
        {
            data->data[i]=0;//各项统计数目初始化
        }
        string temp;
        char ch;
        while(getline(file,temp))
        {
            ch='a';//1~26分别对应小写字母a~z
            for(int i=0;i<26;i++)
            {
                data->data[i]+=count(temp.begin(),temp.end(),ch);
                ch++;
            }
            ch='A';//27~54分别对应大写字母A~Z
            for(int i=0;i<26;i++)
            {
                data->data[i+26]+=count(temp.begin(),temp.end(),ch);
                ch++;
            }
            data->data[MAX-3]+=count(temp.begin(),temp.end(),',');
            data->data[MAX-2]+=count(temp.begin(),temp.end(),'.');
            data->data[MAX-1]+=count(temp.begin(),temp.end(),' ');
        }
        for(int i=0;i<MAX;i++)
        {
            data->total+=data->data[i];
        }
        for(int i=0;i<MAX;i++)
        {
            data->weight[i]=((double)data->data[i])/((double)data->total);
        }
        file.close();
    }
}
void GetValue(DATA *data)//计算权值,初始化对应字符
{
    char ch;
    ch='a';//1~26分别对应小写字母a~z
    for(int i=0;i<26;i++)
    {
        data->value[i]=ch;
        ch++;
    }
    ch='A';//27~54分别对应大写字母A~Z
    for(int i=0;i<26;i++)
    {
        data->value[i+26]=ch;
        ch++;
    }
    data->value[MAX-3]=',';
    data->value[MAX-2]='.';
    data->value[MAX-1]=' ';
}
void PrintForm(DATA *data,Huffmancode HT)//屏幕显示字符频率
{
    cout<<"该文件的字符总数为:"<<data->total<<endl;
    cout<<"该文件的各字符统计:"<<endl;
    for(int i=0;i<MAX;i++)
    {
        cout<<data->value[i]<<"出现过"<<data->data[i]<<"次\t权重为"<<data->weight[i]<<"\n编码为:"<<HT[i]<<endl;
    }
}
void SelectMin(Huffman &T,int k,int *s1,int *s2)//选择权重最小两个结点
{
    double Min=1.0;
    int tmp=0;
  	for(int i=0;i<=k;i++)//找最小的权值
    {
  	   if(T[i].parent==-1)
  	   {
            if(100000*Min>100000*T[i].weight)//扩大倍数比较小数
            {
                Min=T[i].weight;
                tmp=i;//记录最小权值结点位置
            }
   	   }
  	}
 	*s1=tmp;
 	Min=1.0;
 	tmp=0;
  	for(int j=0;j<=k;j++)//找第二小的权值
  	{
   	   if((T[j].parent==-1)&&(j!=*s1))
   	   {
            if(100000*Min>100000*T[j].weight)//扩大倍数比较小数
   	        {
     		    Min=T[j].weight;
      		    tmp=j;//记录第二小权值结点位置
            }
        }
 	 }
  	*s2=tmp;
}
void CreateHuffTree(Huffman &T,DATA *data,int n)//根据权值构造哈夫曼树
{
    if(n<=1)
    {
        return ;
    }
    int i,s1,s2;
    for(i=0;i<n;i++)//初始化哈夫曼树n个结点并赋权重
    {
        T[i].weight=data->weight[i];
        T[i].lchild=-1;
        T[i].rchild=-1;
        T[i].parent=-1;
    }
    for(;i<N;i++)//初始化哈夫曼树非叶结点
    {
        T[i].weight=0;
        T[i].lchild=-1;
        T[i].rchild=-1;
        T[i].parent=-1;
    }
    for(i=n;i<N;i++)
    {
        s1=0,s2=0;
        SelectMin(T,i-1,&s1,&s2);//选择最小权值的两个结点记录于s1,s2
        T[s1].parent=i;//将s1,s2合在一棵二叉树下
        T[s2].parent=i;
        T[i].lchild=s1;
        T[i].rchild=s2;
        T[i].weight=T[s1].weight+T[s2].weight;
    }
}
void EncodeHuff(Huffman T,Huffmancode &HT)//对每个叶节点进行编码
{
  	char cd[MAX];//临时保存每个节点的哈夫曼编码
  	int start,c,f;
  	for(int i=0;i<MAX;i++)//循环每个叶结点
    {
  	   start=MAX-1;
   	   c=i;
   	   f=T[i].parent;
   	   while(f!=-1)//向根回溯
   	   {
            if(T[f].lchild==c)//是左子树
            {
                cd[--start]='0';//当位编码为0
            }
            else//是右子树
            {
                cd[--start]='1';//当位编码为1
            }
        c=f;
        f=T[f].parent;
        }
        HT[i]=(char*)malloc((N-start)*sizeof(char));
        strcpy(HT[i],&cd[start]);//编码结果存放
  	}
}
void GetFile(Huffmancode HT,DATA *data)//将英文文件压缩为哈夫曼编码文件
{
    fstream file1,file2;
    file1.open("text.txt"); //打开英文文件
    file2.open("huffmanzip.txt"); //打开要压缩的哈夫曼编码文件
    if(file1.fail()||file2.fail())
    {
        cout<<"文件打开失败"<<endl;
        return ;
    }
    while(1)
    {
        char a[100000];
        file1.getline(a,100001);//读出英文文件的内容
        int len=strlen(a);//获得文本字符总长度
        for(int i=0;i<len;i++)
        {
            for(int j=0;j<MAX;j++)//查找对应字符的编码
            {
                if(data->value[j]==a[i])
                {
                    file2<<HT[j];//将每个字符的哈夫曼编码输入到哈夫曼编码文件中
                }
            }
        }
        file2.put('\n');
        if(file1.eof())//按行读取,检查是否到文件结尾
        {
            break;
        }
    }
    file1.close();
    file2.close();
}
void DecodeHuff(Huffman T,DATA *data,char test[],char *result)//字符解码过程
{
    int p=N-1;//根节点
    int i=0;//指示串的第i个字符
    int j=0;//解码出的第j个字符
    int len=strlen(test);
    while(i<len)
    {
        if(test[i]=='0')
        {
            p=T[p].lchild;
 	    }
  	    if(test[i]=='1')
  	    {
            p=T[p].rchild;
 	    }
	    if(p<MAX)//说明此时为叶节点
	    {
	        result[j]=data->value[p];
            j++;
            p=N-1;//重新指向根节点
	    }
	    i++;
    }
 	result[j]='\0';
}
void DecodeHuffFile(Huffman T,DATA *data)//将从文件读入的哈夫曼编码解码为英文文件
{
    fstream file1,file2;
    file1.open("huffmanzip.txt");//编码完成的文件
    file2.open("decode.txt");//解码完成文件
    if(file1.fail()||file2.fail())
    {
        cout<<"文件打开失败"<<endl;
        return ;
    }
    int i;
    do{
        i=0;
        char line1[100000];
        file1.getline(line1,100001);
        char line2[100000];
        DecodeHuff(T,data,line1,line2);
        while(line2[i]!='\0')//将解码结果写入文件中
        {
            file2<<line2[i];
            i++;
        }
        file2.put('\n');
        if(file1.eof())//按行读取,文件是否到末尾
        {
            break;
        }
    }while(1);
    file1.close();
    file2.close();
}
void Calculate(Huffmancode HT,DATA *data)//计算编码平均长度、压缩率
{
    double sum=0.0;
    for(int i=0;i<MAX;i++)
    {
        sum+=strlen(HT[i])*data->weight[i];
    }
    cout<<"哈夫曼树平均编码长度为:"<<sum<<endl;
    cout<<"哈夫曼树压缩率为:"<<(1-sum/8)<<endl;
}
void GetWData(WORDDATA *wdata)//统计单词出现频率
{
    fstream file;
    file.open("wordtext.txt");//打开单词编码文件
    if(file.fail())
    {
        cout<<"wordtext文件打开失败,请检查文件"<<endl;
        return ;
    }
    else
    {
        wdata->total=0;//总计数目初始化
        wdata->typenum=0;//种类数目初始化
        for(int i=0;i<1000;i++)
        {
            wdata->data[i]=0;//各项统计数目初始化
        }
        string temp;
        int i=0;
        while(file>>temp)
        {
            wdata->value[i]=temp;
            wdata->data[i]++;
            wdata->total++;
            i++;
        }
        wdata->typenum=wdata->total;//最初默认各单词种类不同
        for(int i=0;i<wdata->typenum-1;i++)//合并相同单词单元
        {
            for(int j=i+1;j<wdata->typenum;j++)
            {
                if(wdata->value[i]==wdata->value[j])
                {
                    wdata->data[i]+=wdata->data[j];
                    for(int k=j;k<wdata->typenum-1;k++)
                    {
                        wdata->value[k]=wdata->value[k+1];
                        wdata->data[k]=wdata->data[k+1];
                    }
                    wdata->typenum--;
                    j--;
                }
            }
        }
        int sum=0;
        for(int i=0;i<wdata->typenum;i++)
        {
            sum+=wdata->data[i];
        }
        for(int i=0;i<wdata->typenum;i++)
        {
            wdata->weight[i]=1.0*wdata->data[i]/sum;
        }
        file.close();
    }
}
void WCreateHuffTree(Huffman &T,WORDDATA *wdata,int n)//单词操作--构造哈夫曼树
{
    if(n<=1)
    {
        return ;
    }
    int i,s1,s2;
    for(i=0;i<n;i++)//初始化哈夫曼树n个结点并赋权重
    {
        T[i].weight=wdata->weight[i];
        T[i].lchild=-1;
        T[i].rchild=-1;
        T[i].parent=-1;
    }
    for(;i<2*n-1;i++)//初始化哈夫曼树非叶结点
    {
        T[i].weight=0;
        T[i].lchild=-1;
        T[i].rchild=-1;
        T[i].parent=-1;
    }
    for(i=n;i<2*n-1;i++)
    {
        s1=0,s2=0;
        SelectMin(T,i-1,&s1,&s2);//选择两个权值最小的结点准备合并
        T[s1].parent=i;
        T[s2].parent=i;
        T[i].lchild=s1;
        T[i].rchild=s2;
        T[i].weight=T[s1].weight+T[s2].weight;
    }
}
void WGetFile(Huffmancode HT,WORDDATA *wdata)//单词操作--对文件进行哈夫曼压缩
{
    fstream file1,file2;
    file1.open("wordtext.txt"); //打开英文文件
    file2.open("wordhuffmanzip.txt"); //打开要压缩的哈夫曼编码文件
    if(file1.fail()||file2.fail())
    {
        cout<<"文件打开失败"<<endl;
        return ;
    }
    string temp;
    while(1)
    {
        file1>>temp;
        for(int i=0;i<wdata->typenum;i++)//查找对应字符的编码
        {
            if(wdata->value[i]==temp)
            {
                file2<<HT[i];//将每个字符的哈夫曼编码输入到哈夫曼编码文件中
            }
        }
        file1.get();
        if(file1.eof())//按行读取,检查是否到文件结尾
        {
            break;
        }
    }
    file1.close();
    file2.close();
}
void WDecodeHuffFile(Huffman T,WORDDATA *wdata)//单词操作--解哈夫曼码并写入文件
{
    fstream file1;
    file1.open("wordhuffmanzip.txt");//编码完成的文件
    if(file1.fail())
    {
        cout<<"文件打开失败"<<endl;
        return ;
    }
    int i;
    do{
        i=-1;
        char test[10000];
        do{
            i++;
            file1>>test[i];
        }while(test[i]!='\0');
        WDecodeHuff(T,wdata,test);

        if(file1.eof())//按行读取,文件是否到末尾
        {
            break;
        }
    }while(1);
    file1.close();
}
void WDecodeHuff(Huffman T,WORDDATA *wdata,char test[])//单词操作--寻找哈夫曼码对应字符
{
    fstream file2;
    file2.open("worddecode.txt");//解码完成文件
    if(file2.fail())
    {
        cout<<"文件打开失败"<<endl;
        return ;
    }
    int p=2*wdata->typenum-2;//根节点
    int i=0;//指示串的第i个字符
    int len=strlen(test);
    while(i<len)
    {
        if(test[i]=='0')
        {
            p=T[p].lchild;
 	    }
  	    if(test[i]=='1')
  	    {
            p=T[p].rchild;
 	    }
	    if(p<wdata->typenum)//说明此时为叶节点
	    {
	        file2<<wdata->value[p];
	        file2<<" ";
            p=2*wdata->typenum-2;//重新指向根节点
	    }
	    i++;
    }
    file2.close();
}
void WCalculate(Huffmancode WHT,WORDDATA *wdata)//单词操作--计算长度、压缩率等
{
    double sum=0.0;
    for(int i=0;i<wdata->typenum;i++)
    {
        sum+=strlen(WHT[i])*wdata->weight[i];
    }
    cout<<"哈夫曼树平均编码长度为:"<<sum<<endl;
    cout<<"哈夫曼树压缩率为:"<<(1-sum/8)<<endl;
}
void KEncodeHuff(KHuffman T,Huffmancode &KHT)//对每个叶节点进行三进制编码
{
  	char cd[MAX];//临时保存每个节点的哈夫曼编码
  	int start,c,f;
  	for(int i=0;i<MAX;i++)//给每个叶结点进行编码
    {
  	    start=MAX-1;
   	    c=i;
   	    f=T[i].parent;
   	    while(f!=-1)//向根结点回溯
        {
            if(T[f].child1==c)//是左子树
            {
                cd[--start]='0';//当位编码为0
            }
            if(T[f].child2==c)//是右1子树
            {
                cd[--start]='1';//当位编码为1
            }
            if(T[f].child3==c)//是右2子树
            {
                cd[--start]='2';//当位编码为2
            }
        c=f;
        f=T[f].parent;
        }
        KHT[i]=(char*)malloc((KN-start)*sizeof(char));
        strcpy(KHT[i],&cd[start]);//各位编码存放
  	}
}
int KCreateHuffTree(KHuffman &T,DATA *data,int n)//构造三进制哈夫曼树
{
    if(n<=2)
    {
        return -1;
    }
    int i,s1,s2,s3;
    for(i=0;i<n;i++)//初始化哈夫曼树n个结点并赋权重
    {
        T[i].weight=data->weight[i];
        T[i].child1=-1;
        T[i].child2=-1;
        T[i].child3=-1;
        T[i].parent=-1;
        T[i].temp=true;
    }
    for(;i<KN;i++)//初始化哈夫曼树非叶结点
    {
        T[i].weight=0;
        T[i].child1=-1;
        T[i].child2=-1;
        T[i].child3=-1;
        T[i].parent=-1;
        T[i].temp=true;
    }
    for(i=n;i<KN;i++)//三个孩子,不确定结点个数,靠temp截断
    {
        s1=0,s2=0,s3=0;
        SelectKMin(T,i-1,&s1,&s2,&s3);//选择三个权值最小结点
        if(T[s1].temp)//是否之前被选过
        {
            T[s1].temp=false;
            T[s1].parent=i;
            T[i].child1=s1;
            T[i].weight+=T[s1].weight;
        }
        else//被选过,截止到i-2
        {
            return i-2;
        }
        if(T[s2].temp)//是否之前被选过
        {
            T[s2].temp=false;
            T[s2].parent=i;
            T[i].child2=s2;
            T[i].weight+=T[s2].weight;
        }
        else//被选过,截止到i-1
        {
            return i-1;
        }
        if(T[s3].temp)//是否之前被选过
        {
            T[s3].temp=false;
            T[s3].parent=i;
            T[i].child3=s3;
            T[i].weight+=T[s3].weight;
        }
        else//被选过,截止到i
        {
            return i;
        }
    }
    return -1;
}
void SelectKMin(KHuffman &T,int k,int *s1,int *s2,int *s3)//选择最小的三个结点
{
    double Min=1.0;
    int tmp=0;
  	for(int i=0;i<=k;i++)//找最小的权值
    {
  	   if(T[i].parent==-1)//根节点
  	   {
            if(100000*Min>100000*T[i].weight)//扩大倍数比较小数
            {
                Min=T[i].weight;
                tmp=i;//记录最小权值结点位置
            }
   	   }
  	}
  	if(T[tmp].temp)
    {
        *s1=tmp;
    }
 	Min=1.0;
 	tmp=0;
  	for(int j=0;j<=k;j++)//找第二小的权值
  	{
   	   if((T[j].parent==-1)&&(j!=*s1))//根节点且与s1不同
   	   {
            if(100000*Min>100000*T[j].weight)//扩大倍数比较小数
   	        {
     		    Min=T[j].weight;
      		    tmp=j;//记录第二小权值结点位置
            }
        }
 	 }
  	if(T[tmp].temp)
    {
        *s2=tmp;
    }
  	Min=1.0;
  	tmp=0;
  	for(int t=0;t<=k;t++)//找第三小的权值
  	{
   	   if((T[t].parent==-1)&&(t!=*s1)&&(t!=*s2))//根节点且与s1,s2不同
   	   {
            if(100000*Min>100000*T[t].weight)//扩大倍数比较小数
   	        {
     		    Min=T[t].weight;
      		    tmp=t;//记录第三小权值结点位置
            }
        }
 	 }
  	if(T[tmp].temp)
    {
        *s3=tmp;
    }
}
void KGetFile(Huffmancode HT,DATA *data)//对文件进行K进制哈夫曼压缩
{
    fstream file1,file2;
    file1.open("text.txt"); //打开英文文件
    file2.open("Khuffmanzip.txt"); //打开要压缩的哈夫曼编码文件
    if(file1.fail()||file2.fail())
    {
        cout<<"文件打开失败"<<endl;
        return ;
    }
    while(1)
    {
        char a[100000];
        file1.getline(a,100001);//读出英文文件的内容
        int len=strlen(a);//获得文本字符总长度
        for(int i=0;i<len;i++)
        {
            for(int j=0;j<MAX;j++)//查找对应字符的编码
            {
                if(data->value[j]==a[i])
                {
                    file2<<HT[j];//将每个字符的哈夫曼编码输入到哈夫曼编码文件中
                }
            }
        }
        file2.put('\n');
        if(file1.eof())//按行读取,检查是否到文件结尾
        {
            break;
        }
    }
    file1.close();
    file2.close();
}
void KDecodeHuffFile(KHuffman T,DATA *data,int knode)//解K进制哈夫曼码并写入文件
{
    fstream file1,file2;
    file1.open("Khuffmanzip.txt");//编码完成的文件
    file2.open("Kdecode.txt");//解码完成文件
    if(file1.fail()||file2.fail())
    {
        cout<<"文件打开失败"<<endl;
        return ;
    }
    int i;
    do{
        i=0;
        char line1[100000];
        file1.getline(line1,100001);
        char line2[100000];
        KDecodeHuff(T,data,line1,line2,knode);
        while(line2[i]!='\0')//将解码结果写入文件中
        {
            file2<<line2[i];
            i++;
        }
        file2.put('\n');
        if(file1.eof())//按行读取,文件是否到末尾
        {
            break;
        }
    }while(1);
    file1.close();
    file2.close();
}
void KDecodeHuff(KHuffman T,DATA *data,char test[],char *result,int knode)//寻找K进制哈夫曼码对应字符
{
    int p=knode;//根节点
    int i=0;//指示串的第i个字符
    int j=0;//解码出的第j个字符
    int len=strlen(test);
    while(i<len)
    {
        if(test[i]=='0')//访问左子树
        {
            p=T[p].child1;
 	    }
  	    if(test[i]=='1')//访问右1子树
  	    {
            p=T[p].child2;
 	    }
 	    if(test[i]=='2')//访问右2子树
  	    {
            p=T[p].child3;
 	    }
	    if(p<MAX)//说明此时为叶节点
	    {
	        result[j]=data->value[p];
            j++;
            p=knode;//重新指向根节点
	    }
	    i++;
    }
 	result[j]='\0';
}
void Menu()//功能显示菜单
{
    cout<<"1.显示对应字符频率、哈夫曼码;"<<endl;
    cout<<"2.将文件根据字符哈夫曼编码压缩文件至huffmanzip.txt"<<endl;
    cout<<"3.将字符压缩文件解码至decode.txt"<<endl;
    cout<<"4.计算字符编码平均长度、压缩率"<<endl;
    cout<<"5.完成单词哈夫曼编码其他文件上述1~4"<<endl;
    cout<<"6.完成三进制功能1~4"<<endl;
}
