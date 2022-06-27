#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <cstring>
#define MAX 54//������ĸ��Сд',''.'�Լ�' '
#define N 2*MAX-1//n��Ҷ�ӽ��Ĺ���������2n-1���
#define KN 2*MAX//�����Ʊ�����

using namespace std;
typedef struct data DATA;
typedef struct htnode Huffman[N];
typedef struct khtnode KHuffman[KN];
typedef char *Huffmancode[MAX];
typedef struct worddata WORDDATA;
struct data{
    int data[MAX];//ͳ�Ƴ��ִ���
    char value[MAX];//��¼��Ӧ�ַ�
    double weight[MAX];//��¼��Ӧ�ַ�Ȩ��
    int total;//ͳ���������ַ���
};
struct htnode{
    double weight;//Ȩ��
    int lchild;//����
    int rchild;//�Һ���
    int parent;//����
};
struct khtnode{
    double weight;//Ȩ��
    int child1;//����
    int child2;//�Һ���1
    int child3;//�Һ���2
    int parent;//����
    bool temp;//�Ƿ�ѡ���
};
struct worddata{
    int data[1000];//ͳ�Ƴ��ִ���
    string value[1000];//��¼��Ӧ����,���Կո�,���
    double weight[1000];//��¼��Ӧ����Ȩֵ
    int total;//ͳ�������ܵ�����
    int typenum;//ͳ������
};

void PrintForm(DATA *data,Huffmancode HT);//��ʾ�ļ��ַ�ͳ�Ʊ�
void GetData(DATA *data);//���ļ�,ͳ�Ƴ��ִ���
void GetValue(DATA *data);//��ʼ��value��dataÿһ���Ӧ�ַ��Լ����ַ���
void SelectMin(Huffman &T,int k,int &s1,int &s2);//ѡ��Ȩ����С���������
void CreateHuffTree(Huffman &T,DATA *data,int n);//�����������
void EncodeHuff(Huffman T,Huffmancode &HT);//��ÿ��Ҷ������
void GetFile(Huffmancode HT,DATA *data);//���ļ����й�����ѹ��
void DecodeHuffFile(Huffman T,DATA *data);//��������벢д���ļ�
void DecodeHuff(Huffman T,DATA *data,char test[],char *result);//Ѱ�ҹ��������Ӧ�ַ�
void Calculate(Huffmancode HT,DATA *data);//���㳤�ȡ�ѹ���ʵ�
void GetWData(WORDDATA *wdata);//���ļ�,ͳ�Ƴ��ִ���
void WCreateHuffTree(Huffman &T,WORDDATA *wdata,int n);//���ʲ���--�����������
void WGetFile(Huffmancode HT,WORDDATA *wdata);//���ʲ���--���ļ����й�����ѹ��
void WDecodeHuffFile(Huffman T,WORDDATA *wdata);//���ʲ���--��������벢д���ļ�
void WDecodeHuff(Huffman T,WORDDATA *wdata,char test[]);//���ʲ���--Ѱ�ҹ��������Ӧ�ַ�
void WCalculate(Huffmancode HT,WORDDATA *wdata);//���ʲ���--���㳤�ȡ�ѹ���ʵ�
void KEncodeHuff(KHuffman T,Huffmancode &KHT);//��ÿ��Ҷ�ڵ����K���Ʊ���
int KCreateHuffTree(KHuffman &T,DATA *data,int n);//����K���ƹ�������
void SelectKMin(KHuffman &T,int k,int *s1,int *s2,int *s3);//ѡ��Ȩ����С��3�����
void KGetFile(Huffmancode HT,DATA *data);//���ļ�����K���ƹ�����ѹ��
void KDecodeHuffFile(KHuffman T,DATA *data,int knode);//��������벢д���ļ�
void KDecodeHuff(KHuffman T,DATA *data,char test[],char *result,int knode);//Ѱ�ҹ��������Ӧ�ַ�
void Menu();//���ܲ˵���ʾ

int main()
{
    int choice,knode;
    DATA data;//�����ַ�ͳ��Ƶ��
    WORDDATA wdata;//���յ���ͳ��Ƶ��
    Huffman Tree,WTree;//�����ƹ�������
    KHuffman KTree;//k���ƹ�������
    Huffmancode HT,WHT,KHT;//������
    GetData(&data);//���ı��ļ��ж�ȡ�ַ�
    GetValue(&data);//�����ַ�Ȩֵ����ʼ����Ӧ�ַ�
    GetWData(&wdata);//���㵥��Ȩֵ
    CreateHuffTree(Tree,&data,MAX);//�����������
    WCreateHuffTree(WTree,&wdata,wdata.typenum);//������ڵ��ʹ�������
    knode=KCreateHuffTree(KTree,&data,MAX);//����K���ƹ�������
    EncodeHuff(Tree,HT);//����������
    KEncodeHuff(KTree,KHT);//K���ƹ���������
    EncodeHuff(WTree,WHT);//���ڵ��ʹ���������
    do{
        Menu();
        cout<<"����ѡ��"<<endl;
        cin>>choice;
        if(choice<=0||choice>=7)
        {
            break;
        }
        switch (choice)
        {
        case 1:
            PrintForm(&data,HT);//��ʾ�ַ������Ϣ
            break;
        case 2:
            GetFile(HT,&data);//�ַ��ļ�ѹ��Ϊ�������ļ�
            break;
        case 3:
            DecodeHuffFile(Tree,&data);//�����ַ��������ļ���������������������ļ�
            break;
        case 4:
            Calculate(HT,&data);//�����ַ�����ƽ�����ȡ�ѹ����
            break;
        case 5:
            cout<<"���ļ��ĵ�������Ϊ:"<<wdata.total<<endl;
            cout<<"���ļ��ĸ�����ͳ��:"<<endl;
            for(int i=0;i<wdata.typenum;i++)
            {
                cout<<wdata.value[i]<<"���ֹ�"<<wdata.data[i]<<"��\tȨ��Ϊ"<<wdata.weight[i]<<"\n����Ϊ:"<<WHT[i]<<endl;
            }
            WGetFile(WHT,&wdata);//ѹ�����ļ���
            WDecodeHuffFile(WTree,&wdata);//��ѹ����һ�ļ���
            WCalculate(WHT,&wdata);//���㲢��ʾѹ��Ч��
            break;
        case 6:
            PrintForm(&data,KHT);//��ʾ�ַ������Ϣ
            KGetFile(KHT,&data);//ѹ�����ļ�
            KDecodeHuffFile(KTree,&data,knode);//��ѹ���ļ�
            Calculate(KHT,&data);//����ѹ��Ч������ʾ
            break;
        default:
            break;
        }
    }while(choice>0&&choice<7);
    cout<<"����ѡ��Χ��,��������"<<endl;
    return 0;
}
void GetData(DATA *data)//���ļ�,��ͳ�Ƹ��ַ����ֵĴ���
{
    fstream file;
    file.open("text.txt");//�򿪱����ļ�
    if(file.fail())
    {
        cout<<"text�ļ���ʧ��,�����ļ�"<<endl;
        return ;
    }
    else
    {
        data->total=0;//�ܼ���Ŀ��ʼ��
        for(int i=0;i<MAX;i++)
        {
            data->data[i]=0;//����ͳ����Ŀ��ʼ��
        }
        string temp;
        char ch;
        while(getline(file,temp))
        {
            ch='a';//1~26�ֱ��ӦСд��ĸa~z
            for(int i=0;i<26;i++)
            {
                data->data[i]+=count(temp.begin(),temp.end(),ch);
                ch++;
            }
            ch='A';//27~54�ֱ��Ӧ��д��ĸA~Z
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
void GetValue(DATA *data)//����Ȩֵ,��ʼ����Ӧ�ַ�
{
    char ch;
    ch='a';//1~26�ֱ��ӦСд��ĸa~z
    for(int i=0;i<26;i++)
    {
        data->value[i]=ch;
        ch++;
    }
    ch='A';//27~54�ֱ��Ӧ��д��ĸA~Z
    for(int i=0;i<26;i++)
    {
        data->value[i+26]=ch;
        ch++;
    }
    data->value[MAX-3]=',';
    data->value[MAX-2]='.';
    data->value[MAX-1]=' ';
}
void PrintForm(DATA *data,Huffmancode HT)//��Ļ��ʾ�ַ�Ƶ��
{
    cout<<"���ļ����ַ�����Ϊ:"<<data->total<<endl;
    cout<<"���ļ��ĸ��ַ�ͳ��:"<<endl;
    for(int i=0;i<MAX;i++)
    {
        cout<<data->value[i]<<"���ֹ�"<<data->data[i]<<"��\tȨ��Ϊ"<<data->weight[i]<<"\n����Ϊ:"<<HT[i]<<endl;
    }
}
void SelectMin(Huffman &T,int k,int *s1,int *s2)//ѡ��Ȩ����С�������
{
    double Min=1.0;
    int tmp=0;
  	for(int i=0;i<=k;i++)//����С��Ȩֵ
    {
  	   if(T[i].parent==-1)
  	   {
            if(100000*Min>100000*T[i].weight)//�������Ƚ�С��
            {
                Min=T[i].weight;
                tmp=i;//��¼��СȨֵ���λ��
            }
   	   }
  	}
 	*s1=tmp;
 	Min=1.0;
 	tmp=0;
  	for(int j=0;j<=k;j++)//�ҵڶ�С��Ȩֵ
  	{
   	   if((T[j].parent==-1)&&(j!=*s1))
   	   {
            if(100000*Min>100000*T[j].weight)//�������Ƚ�С��
   	        {
     		    Min=T[j].weight;
      		    tmp=j;//��¼�ڶ�СȨֵ���λ��
            }
        }
 	 }
  	*s2=tmp;
}
void CreateHuffTree(Huffman &T,DATA *data,int n)//����Ȩֵ�����������
{
    if(n<=1)
    {
        return ;
    }
    int i,s1,s2;
    for(i=0;i<n;i++)//��ʼ����������n����㲢��Ȩ��
    {
        T[i].weight=data->weight[i];
        T[i].lchild=-1;
        T[i].rchild=-1;
        T[i].parent=-1;
    }
    for(;i<N;i++)//��ʼ������������Ҷ���
    {
        T[i].weight=0;
        T[i].lchild=-1;
        T[i].rchild=-1;
        T[i].parent=-1;
    }
    for(i=n;i<N;i++)
    {
        s1=0,s2=0;
        SelectMin(T,i-1,&s1,&s2);//ѡ����СȨֵ����������¼��s1,s2
        T[s1].parent=i;//��s1,s2����һ�ö�������
        T[s2].parent=i;
        T[i].lchild=s1;
        T[i].rchild=s2;
        T[i].weight=T[s1].weight+T[s2].weight;
    }
}
void EncodeHuff(Huffman T,Huffmancode &HT)//��ÿ��Ҷ�ڵ���б���
{
  	char cd[MAX];//��ʱ����ÿ���ڵ�Ĺ���������
  	int start,c,f;
  	for(int i=0;i<MAX;i++)//ѭ��ÿ��Ҷ���
    {
  	   start=MAX-1;
   	   c=i;
   	   f=T[i].parent;
   	   while(f!=-1)//�������
   	   {
            if(T[f].lchild==c)//��������
            {
                cd[--start]='0';//��λ����Ϊ0
            }
            else//��������
            {
                cd[--start]='1';//��λ����Ϊ1
            }
        c=f;
        f=T[f].parent;
        }
        HT[i]=(char*)malloc((N-start)*sizeof(char));
        strcpy(HT[i],&cd[start]);//���������
  	}
}
void GetFile(Huffmancode HT,DATA *data)//��Ӣ���ļ�ѹ��Ϊ�����������ļ�
{
    fstream file1,file2;
    file1.open("text.txt"); //��Ӣ���ļ�
    file2.open("huffmanzip.txt"); //��Ҫѹ���Ĺ����������ļ�
    if(file1.fail()||file2.fail())
    {
        cout<<"�ļ���ʧ��"<<endl;
        return ;
    }
    while(1)
    {
        char a[100000];
        file1.getline(a,100001);//����Ӣ���ļ�������
        int len=strlen(a);//����ı��ַ��ܳ���
        for(int i=0;i<len;i++)
        {
            for(int j=0;j<MAX;j++)//���Ҷ�Ӧ�ַ��ı���
            {
                if(data->value[j]==a[i])
                {
                    file2<<HT[j];//��ÿ���ַ��Ĺ������������뵽�����������ļ���
                }
            }
        }
        file2.put('\n');
        if(file1.eof())//���ж�ȡ,����Ƿ��ļ���β
        {
            break;
        }
    }
    file1.close();
    file2.close();
}
void DecodeHuff(Huffman T,DATA *data,char test[],char *result)//�ַ��������
{
    int p=N-1;//���ڵ�
    int i=0;//ָʾ���ĵ�i���ַ�
    int j=0;//������ĵ�j���ַ�
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
	    if(p<MAX)//˵����ʱΪҶ�ڵ�
	    {
	        result[j]=data->value[p];
            j++;
            p=N-1;//����ָ����ڵ�
	    }
	    i++;
    }
 	result[j]='\0';
}
void DecodeHuffFile(Huffman T,DATA *data)//�����ļ�����Ĺ������������ΪӢ���ļ�
{
    fstream file1,file2;
    file1.open("huffmanzip.txt");//������ɵ��ļ�
    file2.open("decode.txt");//��������ļ�
    if(file1.fail()||file2.fail())
    {
        cout<<"�ļ���ʧ��"<<endl;
        return ;
    }
    int i;
    do{
        i=0;
        char line1[100000];
        file1.getline(line1,100001);
        char line2[100000];
        DecodeHuff(T,data,line1,line2);
        while(line2[i]!='\0')//��������д���ļ���
        {
            file2<<line2[i];
            i++;
        }
        file2.put('\n');
        if(file1.eof())//���ж�ȡ,�ļ��Ƿ�ĩβ
        {
            break;
        }
    }while(1);
    file1.close();
    file2.close();
}
void Calculate(Huffmancode HT,DATA *data)//�������ƽ�����ȡ�ѹ����
{
    double sum=0.0;
    for(int i=0;i<MAX;i++)
    {
        sum+=strlen(HT[i])*data->weight[i];
    }
    cout<<"��������ƽ�����볤��Ϊ:"<<sum<<endl;
    cout<<"��������ѹ����Ϊ:"<<(1-sum/8)<<endl;
}
void GetWData(WORDDATA *wdata)//ͳ�Ƶ��ʳ���Ƶ��
{
    fstream file;
    file.open("wordtext.txt");//�򿪵��ʱ����ļ�
    if(file.fail())
    {
        cout<<"wordtext�ļ���ʧ��,�����ļ�"<<endl;
        return ;
    }
    else
    {
        wdata->total=0;//�ܼ���Ŀ��ʼ��
        wdata->typenum=0;//������Ŀ��ʼ��
        for(int i=0;i<1000;i++)
        {
            wdata->data[i]=0;//����ͳ����Ŀ��ʼ��
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
        wdata->typenum=wdata->total;//���Ĭ�ϸ��������಻ͬ
        for(int i=0;i<wdata->typenum-1;i++)//�ϲ���ͬ���ʵ�Ԫ
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
void WCreateHuffTree(Huffman &T,WORDDATA *wdata,int n)//���ʲ���--�����������
{
    if(n<=1)
    {
        return ;
    }
    int i,s1,s2;
    for(i=0;i<n;i++)//��ʼ����������n����㲢��Ȩ��
    {
        T[i].weight=wdata->weight[i];
        T[i].lchild=-1;
        T[i].rchild=-1;
        T[i].parent=-1;
    }
    for(;i<2*n-1;i++)//��ʼ������������Ҷ���
    {
        T[i].weight=0;
        T[i].lchild=-1;
        T[i].rchild=-1;
        T[i].parent=-1;
    }
    for(i=n;i<2*n-1;i++)
    {
        s1=0,s2=0;
        SelectMin(T,i-1,&s1,&s2);//ѡ������Ȩֵ��С�Ľ��׼���ϲ�
        T[s1].parent=i;
        T[s2].parent=i;
        T[i].lchild=s1;
        T[i].rchild=s2;
        T[i].weight=T[s1].weight+T[s2].weight;
    }
}
void WGetFile(Huffmancode HT,WORDDATA *wdata)//���ʲ���--���ļ����й�����ѹ��
{
    fstream file1,file2;
    file1.open("wordtext.txt"); //��Ӣ���ļ�
    file2.open("wordhuffmanzip.txt"); //��Ҫѹ���Ĺ����������ļ�
    if(file1.fail()||file2.fail())
    {
        cout<<"�ļ���ʧ��"<<endl;
        return ;
    }
    string temp;
    while(1)
    {
        file1>>temp;
        for(int i=0;i<wdata->typenum;i++)//���Ҷ�Ӧ�ַ��ı���
        {
            if(wdata->value[i]==temp)
            {
                file2<<HT[i];//��ÿ���ַ��Ĺ������������뵽�����������ļ���
            }
        }
        file1.get();
        if(file1.eof())//���ж�ȡ,����Ƿ��ļ���β
        {
            break;
        }
    }
    file1.close();
    file2.close();
}
void WDecodeHuffFile(Huffman T,WORDDATA *wdata)//���ʲ���--��������벢д���ļ�
{
    fstream file1;
    file1.open("wordhuffmanzip.txt");//������ɵ��ļ�
    if(file1.fail())
    {
        cout<<"�ļ���ʧ��"<<endl;
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

        if(file1.eof())//���ж�ȡ,�ļ��Ƿ�ĩβ
        {
            break;
        }
    }while(1);
    file1.close();
}
void WDecodeHuff(Huffman T,WORDDATA *wdata,char test[])//���ʲ���--Ѱ�ҹ��������Ӧ�ַ�
{
    fstream file2;
    file2.open("worddecode.txt");//��������ļ�
    if(file2.fail())
    {
        cout<<"�ļ���ʧ��"<<endl;
        return ;
    }
    int p=2*wdata->typenum-2;//���ڵ�
    int i=0;//ָʾ���ĵ�i���ַ�
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
	    if(p<wdata->typenum)//˵����ʱΪҶ�ڵ�
	    {
	        file2<<wdata->value[p];
	        file2<<" ";
            p=2*wdata->typenum-2;//����ָ����ڵ�
	    }
	    i++;
    }
    file2.close();
}
void WCalculate(Huffmancode WHT,WORDDATA *wdata)//���ʲ���--���㳤�ȡ�ѹ���ʵ�
{
    double sum=0.0;
    for(int i=0;i<wdata->typenum;i++)
    {
        sum+=strlen(WHT[i])*wdata->weight[i];
    }
    cout<<"��������ƽ�����볤��Ϊ:"<<sum<<endl;
    cout<<"��������ѹ����Ϊ:"<<(1-sum/8)<<endl;
}
void KEncodeHuff(KHuffman T,Huffmancode &KHT)//��ÿ��Ҷ�ڵ���������Ʊ���
{
  	char cd[MAX];//��ʱ����ÿ���ڵ�Ĺ���������
  	int start,c,f;
  	for(int i=0;i<MAX;i++)//��ÿ��Ҷ�����б���
    {
  	    start=MAX-1;
   	    c=i;
   	    f=T[i].parent;
   	    while(f!=-1)//���������
        {
            if(T[f].child1==c)//��������
            {
                cd[--start]='0';//��λ����Ϊ0
            }
            if(T[f].child2==c)//����1����
            {
                cd[--start]='1';//��λ����Ϊ1
            }
            if(T[f].child3==c)//����2����
            {
                cd[--start]='2';//��λ����Ϊ2
            }
        c=f;
        f=T[f].parent;
        }
        KHT[i]=(char*)malloc((KN-start)*sizeof(char));
        strcpy(KHT[i],&cd[start]);//��λ������
  	}
}
int KCreateHuffTree(KHuffman &T,DATA *data,int n)//���������ƹ�������
{
    if(n<=2)
    {
        return -1;
    }
    int i,s1,s2,s3;
    for(i=0;i<n;i++)//��ʼ����������n����㲢��Ȩ��
    {
        T[i].weight=data->weight[i];
        T[i].child1=-1;
        T[i].child2=-1;
        T[i].child3=-1;
        T[i].parent=-1;
        T[i].temp=true;
    }
    for(;i<KN;i++)//��ʼ������������Ҷ���
    {
        T[i].weight=0;
        T[i].child1=-1;
        T[i].child2=-1;
        T[i].child3=-1;
        T[i].parent=-1;
        T[i].temp=true;
    }
    for(i=n;i<KN;i++)//��������,��ȷ��������,��temp�ض�
    {
        s1=0,s2=0,s3=0;
        SelectKMin(T,i-1,&s1,&s2,&s3);//ѡ������Ȩֵ��С���
        if(T[s1].temp)//�Ƿ�֮ǰ��ѡ��
        {
            T[s1].temp=false;
            T[s1].parent=i;
            T[i].child1=s1;
            T[i].weight+=T[s1].weight;
        }
        else//��ѡ��,��ֹ��i-2
        {
            return i-2;
        }
        if(T[s2].temp)//�Ƿ�֮ǰ��ѡ��
        {
            T[s2].temp=false;
            T[s2].parent=i;
            T[i].child2=s2;
            T[i].weight+=T[s2].weight;
        }
        else//��ѡ��,��ֹ��i-1
        {
            return i-1;
        }
        if(T[s3].temp)//�Ƿ�֮ǰ��ѡ��
        {
            T[s3].temp=false;
            T[s3].parent=i;
            T[i].child3=s3;
            T[i].weight+=T[s3].weight;
        }
        else//��ѡ��,��ֹ��i
        {
            return i;
        }
    }
    return -1;
}
void SelectKMin(KHuffman &T,int k,int *s1,int *s2,int *s3)//ѡ����С���������
{
    double Min=1.0;
    int tmp=0;
  	for(int i=0;i<=k;i++)//����С��Ȩֵ
    {
  	   if(T[i].parent==-1)//���ڵ�
  	   {
            if(100000*Min>100000*T[i].weight)//�������Ƚ�С��
            {
                Min=T[i].weight;
                tmp=i;//��¼��СȨֵ���λ��
            }
   	   }
  	}
  	if(T[tmp].temp)
    {
        *s1=tmp;
    }
 	Min=1.0;
 	tmp=0;
  	for(int j=0;j<=k;j++)//�ҵڶ�С��Ȩֵ
  	{
   	   if((T[j].parent==-1)&&(j!=*s1))//���ڵ�����s1��ͬ
   	   {
            if(100000*Min>100000*T[j].weight)//�������Ƚ�С��
   	        {
     		    Min=T[j].weight;
      		    tmp=j;//��¼�ڶ�СȨֵ���λ��
            }
        }
 	 }
  	if(T[tmp].temp)
    {
        *s2=tmp;
    }
  	Min=1.0;
  	tmp=0;
  	for(int t=0;t<=k;t++)//�ҵ���С��Ȩֵ
  	{
   	   if((T[t].parent==-1)&&(t!=*s1)&&(t!=*s2))//���ڵ�����s1,s2��ͬ
   	   {
            if(100000*Min>100000*T[t].weight)//�������Ƚ�С��
   	        {
     		    Min=T[t].weight;
      		    tmp=t;//��¼����СȨֵ���λ��
            }
        }
 	 }
  	if(T[tmp].temp)
    {
        *s3=tmp;
    }
}
void KGetFile(Huffmancode HT,DATA *data)//���ļ�����K���ƹ�����ѹ��
{
    fstream file1,file2;
    file1.open("text.txt"); //��Ӣ���ļ�
    file2.open("Khuffmanzip.txt"); //��Ҫѹ���Ĺ����������ļ�
    if(file1.fail()||file2.fail())
    {
        cout<<"�ļ���ʧ��"<<endl;
        return ;
    }
    while(1)
    {
        char a[100000];
        file1.getline(a,100001);//����Ӣ���ļ�������
        int len=strlen(a);//����ı��ַ��ܳ���
        for(int i=0;i<len;i++)
        {
            for(int j=0;j<MAX;j++)//���Ҷ�Ӧ�ַ��ı���
            {
                if(data->value[j]==a[i])
                {
                    file2<<HT[j];//��ÿ���ַ��Ĺ������������뵽�����������ļ���
                }
            }
        }
        file2.put('\n');
        if(file1.eof())//���ж�ȡ,����Ƿ��ļ���β
        {
            break;
        }
    }
    file1.close();
    file2.close();
}
void KDecodeHuffFile(KHuffman T,DATA *data,int knode)//��K���ƹ������벢д���ļ�
{
    fstream file1,file2;
    file1.open("Khuffmanzip.txt");//������ɵ��ļ�
    file2.open("Kdecode.txt");//��������ļ�
    if(file1.fail()||file2.fail())
    {
        cout<<"�ļ���ʧ��"<<endl;
        return ;
    }
    int i;
    do{
        i=0;
        char line1[100000];
        file1.getline(line1,100001);
        char line2[100000];
        KDecodeHuff(T,data,line1,line2,knode);
        while(line2[i]!='\0')//��������д���ļ���
        {
            file2<<line2[i];
            i++;
        }
        file2.put('\n');
        if(file1.eof())//���ж�ȡ,�ļ��Ƿ�ĩβ
        {
            break;
        }
    }while(1);
    file1.close();
    file2.close();
}
void KDecodeHuff(KHuffman T,DATA *data,char test[],char *result,int knode)//Ѱ��K���ƹ��������Ӧ�ַ�
{
    int p=knode;//���ڵ�
    int i=0;//ָʾ���ĵ�i���ַ�
    int j=0;//������ĵ�j���ַ�
    int len=strlen(test);
    while(i<len)
    {
        if(test[i]=='0')//����������
        {
            p=T[p].child1;
 	    }
  	    if(test[i]=='1')//������1����
  	    {
            p=T[p].child2;
 	    }
 	    if(test[i]=='2')//������2����
  	    {
            p=T[p].child3;
 	    }
	    if(p<MAX)//˵����ʱΪҶ�ڵ�
	    {
	        result[j]=data->value[p];
            j++;
            p=knode;//����ָ����ڵ�
	    }
	    i++;
    }
 	result[j]='\0';
}
void Menu()//������ʾ�˵�
{
    cout<<"1.��ʾ��Ӧ�ַ�Ƶ�ʡ���������;"<<endl;
    cout<<"2.���ļ������ַ�����������ѹ���ļ���huffmanzip.txt"<<endl;
    cout<<"3.���ַ�ѹ���ļ�������decode.txt"<<endl;
    cout<<"4.�����ַ�����ƽ�����ȡ�ѹ����"<<endl;
    cout<<"5.��ɵ��ʹ��������������ļ�����1~4"<<endl;
    cout<<"6.��������ƹ���1~4"<<endl;
}
