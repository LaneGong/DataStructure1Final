#include <iostream>
#include "UFSets.h"
#include <fstream>
#include <sstream>
using namespace std;

int main() {
    int n,m,i,j,k=0,order=1;
    char buffer[256],type;
    stringstream inputstream;
    ifstream infile("../virus5.in");
    ofstream outfile("../virus5.out");
    cout<<"题目一：病毒株种类"<<endl;
    if((!infile.is_open()) && (!outfile.is_open()))
        cout<<"Error!The file is not opened properly."<<endl;
    else{
        cout<<"正在根据virus.in文件数据判断运算处理中..."<<endl;
        //读取 n、m
        infile.getline(buffer,100);
        inputstream.clear();
        inputstream<<buffer;
        inputstream>>n;
        infile.getline(buffer,100);
        inputstream.clear();
        inputstream<<buffer;
        inputstream>>m;

        int **message = new int* [m];
        int viruskinds[n];
        int record[m][2];
        //根据文件信息初始化
        for(int i=0;i<m;i++){
            inputstream.clear();
            message[i]=new int [3];
            infile.getline(buffer,100);
            inputstream<<buffer;
            inputstream>>type;
            inputstream>>message[i][1];
            inputstream>>message[i][2];
            if(type=='S')
                message[i][0]=0;
            else
                message[i][0]=1;
        }
        for(i=0;i<n;i++)
            viruskinds[i]=i+1;//初始化数组
        UFSets<int> virus(viruskinds,n);//以每个病毒作为根结点建立并查集

        for(i=0;i<m;i++){//m条信息进行分别判断是否合并
            if(message[i][0]==0){
                virus.Union(message[i][1],message[i][2]);
            }
            else{
                record[k][0]=message[i][1];
                record[k][1]=message[i][2];
                k++;
                for(j=0;j<k-1;j++){
                    if((message[i][1])==record[j][0])
                        virus.Union(message[i][2],record[j][1]);
                    else if((message[i][2])==record[j][0])
                        virus.Union(message[i][1],record[j][1]);
                    else if((message[i][1])==record[j][1])
                        virus.Union(message[i][2],record[j][0]);
                    else if((message[i][2])==record[j][1])
                        virus.Union(message[i][1],record[j][0]);
                }
            }
        }

        //同种病株及结果输出至virus.out
        outfile<<"第"<<order++<<"组测试结果为(最大可能的病毒株数)："<<virus.nodesnum()<<"\n";//至多有多少种不同病毒株
        outfile<<"同类病毒株详情：\n";
        bool out[n];
        for (i = 0; i < n; i++)
            out[i] = false;
        int p = 0;
        while (p < n){
            outfile << "{" << virus.GetElem(p);
            out[p] = true;
            for (i = p + 1; i < n; i++)	{
                if (!virus.Differ(virus.GetElem(p), virus.GetElem(i)))	{
                    outfile << "," << virus.GetElem(i);
                    out[i] = true;
                }
            }
            outfile << "}\n";
            while (p < n && out[p]) p++;
        }
    }
    infile.close();
    outfile.close();
    cout<<"程序运行完毕，各组测试数据已保存至virus.out，可查看！"<<endl;
    return 0;
}
