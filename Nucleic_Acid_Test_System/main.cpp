#include <iostream>
#include "LinkQueue.h"
#include <fstream>
#include <string>
using namespace std;

void init_queue(int &n,int &m,LinkQueue &mixed_queue,LinkQueue &single_queue){
    char buffer[256];
    stringstream inputstream;
    ifstream infile("../queue2.txt");
    if(!infile.is_open())
        cout<<"Error!The file is not opened properly."<<endl;
    else{
        infile.getline(buffer,100);
        inputstream<<buffer;
        inputstream>>n;
        inputstream>>m;
        for(int i=0;i<n;i++){
            infile.getline (buffer,100);
            mixed_queue.EnQueue(string(buffer));
        }
        for(int j=0;j<m;j++){
            infile.getline (buffer,100);
            single_queue.EnQueue(string(buffer));
        }
    }
    infile.close();
}

void detection(int &x,int &y,LinkQueue &mixed_queue,LinkQueue &single_queue,LinkQueue &mix_complete,LinkQueue &single_complete){
    char buffer[256];
    int num=1,count=1;
    stringstream inputstream;
    ifstream infile2("../complete2.txt");
    if(!infile2.is_open())
        cout<<"Error!The file is not opened properly."<<endl;
    else{
        infile2.getline(buffer,100);
        inputstream<<buffer;
        inputstream>>x;
        inputstream>>y;
        //step1:分配试管
        mixed_queue.SetTube(0);
        single_queue.SetTube(1);
        //step2:已完成的出队，修改状态
        mixed_queue.SetComplete(x,mix_complete);
        single_queue.SetComplete(y,single_complete);
    }
    infile2.close();
}

void typein(LinkQueue &mixed_queue,LinkQueue &single_queue,LinkQueue &mix_complete,LinkQueue &single_complete){
    int xresult;
    string xtube;
    cout<<"已完成测试管(混管)：";
    mix_complete.mixtubeShow();
    cout<<"已完成测试管(单管)：";
    single_complete.ShowTube();
    cout<<"请输入测试管编号：";
    cin>>xtube;
    cout<<"请输入测试结果(1-确诊,2-阴性,3-可疑)：";
    cin>>xresult;
    if(xresult!=1&&xresult!=2&&xresult!=3)
        cout<<"结果有误！退出！"<<endl;
    else{
        if(xtube[0]=='1')
            single_complete.TypeinSingle(xtube,xresult,mixed_queue,single_queue,mix_complete);
        else{
            mix_complete.TypeinMix(xtube,xresult,mixed_queue,single_queue,mix_complete);
        }
    }
}

void showscreen(LinkQueue &mixed_queue,LinkQueue &single_queue,LinkQueue &mix_complete,LinkQueue &single_complete){
    cout<<"阴：";
    mix_complete.ShowStatus(2);
    mixed_queue.ShowStatus(2);
    single_complete.ShowStatus(2);
    single_queue.ShowStatus(2);
    cout<<endl;
    cout<<"阳：";
    mix_complete.ShowStatus(1);
    mixed_queue.ShowStatus(1);
    single_complete.ShowStatus(1);
    single_queue.ShowStatus(1);
    cout<<endl;
    cout<<"可疑：";
    mix_complete.ShowStatus(7);
    mixed_queue.ShowStatus(7);
    single_complete.ShowStatus(7);
    single_queue.ShowStatus(7);
    cout<<endl;
    cout<<"密接：";
    mix_complete.ShowRelation(5);
    mixed_queue.ShowRelation(5);
    single_complete.ShowRelation(5);
    single_queue.ShowRelation(5);
    cout<<endl;
    cout<<"次密接：";
    mix_complete.ShowRelation(6);
    mixed_queue.ShowRelation(6);
    single_complete.ShowRelation(6);
    single_queue.ShowRelation(6);
    cout<<endl;
    cout<<"待上传结果：";
    mix_complete.ShowStatus(3);
    mixed_queue.ShowStatus(3);
    single_complete.ShowStatus(3);
    single_queue.ShowStatus(3);
    cout<<endl;
    cout<<"在排队：";
    mix_complete.ShowStatus(4);
    mixed_queue.ShowStatus(4);
    single_complete.ShowStatus(4);
    single_queue.ShowStatus(4);
    cout<<endl;
}
Status showperson(LinkQueue &mixed_queue,LinkQueue &single_queue,LinkQueue &mix_complete,LinkQueue &single_complete){
    string xmember;
    cout<<"请输入人员代码：";
    cin>>xmember;
    cout<<"当前状态：";
    if(mixed_queue.Search(xmember)==SUCCESS)
        return SUCCESS;
    else if(mix_complete.Search(xmember)==SUCCESS)
        return SUCCESS;
    else if(single_queue.Search(xmember)==SUCCESS)
        return SUCCESS;
    else if(single_complete.Search(xmember)==SUCCESS)
        return SUCCESS;
    else{
        cout<<"未参加排队"<<endl;
        return SUCCESS;
    }
}

int main() {
    char choice;
    int n,m,x,y;
    LinkQueue mixedqueue,singlequeue,mixcomplete,singlecomplete;
    while(true){
        cout<<"\nNucleic Acid Test System"<<endl;
        cout<<"1. 排队"<<endl;
        cout<<"2. 检测"<<endl;
        cout<<"3. 查看排队情况"<<endl;
        cout<<"4. 登记测试管信息"<<endl;
        cout<<"5. 各类人员查询"<<endl;
        cout<<"6. 个人查询"<<endl;
        cout<<"0. 退出系统"<<endl;
        cout<<"请选择相应选项(0~6)：";
        cin>>choice;
        if(choice=='0')break;
        switch(choice){
            case '1':
                cout<<"\n正在根据人员信息分别加入混管/单管排队队伍中..."<<endl;
                init_queue(n,m,mixedqueue,singlequeue);
                cout<<"排队已完成，可通过查看排队情况功能查看队伍！"<<endl;
                break;
            case '2':
                cout<<"\n正在根据当前完成情况更新数据..."<<endl;
                detection(x,y,mixedqueue,singlequeue,mixcomplete,singlecomplete);
                cout<<"检测数据更新完成！"<<endl;
//                cout<<"混管试管号：";
//                mixedqueue.ShowTube();
//                cout<<"单管试管号：";
//                singlequeue.ShowTube();
                break;
            case '3':
                cout<<"\n混检队伍：";
                mixedqueue.Show();
                cout<<"单检队伍：";
                singlequeue.Show();
                break;
            case '4':
                cout<<"\n登记测试管信息"<<endl;
                typein(mixedqueue,singlequeue,mixcomplete,singlecomplete);
//                mixedqueue.showstatus();
//                singlequeue.showstatus();
//                mixcomplete.showstatus();
//                singlecomplete.showstatus();
                cout<<"信息登记已完成！"<<endl;
                break;
            case '5':
                cout<<"\n分类查询"<<endl;
                showscreen(mixedqueue,singlequeue,mixcomplete,singlecomplete);
                break;
            case '6':
                cout<<"\n个人查询"<<endl;
                showperson(mixedqueue,singlequeue,mixcomplete,singlecomplete);
                break;
        }
    }
    return 0;
}
