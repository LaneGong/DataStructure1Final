//
// Created by Gong chen on 2022/4/16.
//

#ifndef NUCLEIC_ACID_TEST_SYSTEM_LINKQUEUE_H
#define NUCLEIC_ACID_TEST_SYSTEM_LINKQUEUE_H
#include "Assistance.h"			// 辅助软件包
#include "Node.h"				// 结点类
#include <sstream>
#include <iomanip>

class LinkQueue
{
protected:
    Node *front, *rear;
public:
    LinkQueue();
    virtual ~LinkQueue();
    int GetLength() const;
    bool IsEmpty() const;
    void Clear();
    Status DelQueue();
    Status EnQueue(string xmember,string xtube="0",int xstatus=4,int xrelation=0);
    void Show();
    void ShowTube();
    void SetTube(int type);
    void SetComplete(int num,LinkQueue &q);
    void SetRelation(int relation, LinkQueue &mixed_queue, LinkQueue &single_queue,LinkQueue &mix_complete,LinkQueue &single_complete);
    void TypeinSingle(string xtube,int xresult,LinkQueue &mixed_queue,LinkQueue &single_queue,LinkQueue &mix_complete);
    void TypeinMix(string xtube,int xresult,LinkQueue &mixed_queue,LinkQueue &single_queue,LinkQueue &mix_complete);
    void mixtubeShow();
    void LouDong(char a[3],int relation);
    LinkQueue(const LinkQueue &q);
    LinkQueue &operator =(const LinkQueue &q);
    void showstatus();//测试
    void ShowStatus(int type);
    void ShowRelation(int type);
    Status Search(const string xmember);
};



LinkQueue::LinkQueue()
{
    rear = front = new Node;	// 生成链队列头结点
}


LinkQueue::~LinkQueue()
{
    Clear();
    delete front;
}


int LinkQueue::GetLength() const
{
    int count = 0;
    for (Node *p = front->next; p != NULL; p = p->next)
        count++;
    return count;
}

bool LinkQueue::IsEmpty() const
{
    return rear == front;
}

void LinkQueue::Clear()
{
    Node *p = front->next;
    while (p != NULL)	{
        front->next = p->next;
        delete p;
        p = front->next;
    }
    rear = front;
}

Status LinkQueue::DelQueue()
{
    if (!IsEmpty()){
        Node *p = front->next;
        front->next = p->next;
        if (rear == p)
            rear = front;
        delete p;
        return SUCCESS;
    }
    else
        return UNDER_FLOW;
}


Status LinkQueue::EnQueue(string xmember, string xtube, int xstatus, int xrelation)
{
    Node *p;
    p = new Node(xmember,xtube, xstatus,xrelation);
    if (p) {
        rear->next = p;
        rear = rear->next;
        return SUCCESS;
    }
    else
        return OVER_FLOW;
}


LinkQueue::LinkQueue(const LinkQueue &q)
{
    rear = front = new Node;
    for (Node *p = q.front->next; p != NULL; p = p->next)
        EnQueue(p->member,p->tube,p->status,p->relation);
}

LinkQueue &LinkQueue::operator =(const LinkQueue &q)
{
    if (&q != this)	{
        Clear();
        for (Node *p = q.front->next; p != NULL; p = p->next)
            EnQueue(p->member,p->tube,p->status,p->relation);
    }
    return *this;
}

void LinkQueue::Show() {
    if(!IsEmpty()){
        for (Node *p = front->next; p != NULL; p = p->next)
            cout<<p->member<<" ";
        cout<<endl;
    }
    else
        cout<<"无"<<endl;
}

void LinkQueue::SetTube(int type) {//0表示混管，1表示单管
    stringstream buf;
    string xtube;
    int num=0;
    if(type==0){
        int count=1;
        buf<<"0"<<setfill('0')<<setw(4)<<num;
        buf>>xtube;
        for(Node *p=front->next;p!=NULL;p=p->next){
            p->tube=xtube;
            count++;
            if(count==11){
                count=1;
                buf.clear();
                num+=1;
                buf<<"0"<<setfill('0')<<setw(4)<<num;
                buf>>xtube;
            }
        }
    }
    else{
        buf<<"1"<<setfill('0')<<setw(4)<<num;
        buf>>xtube;
        for(Node *p=front->next;p!=NULL;p=p->next){
            p->tube=xtube;
            buf.clear();
            num+=1;
            buf<<"1"<<setfill('0')<<setw(4)<<num;
            buf>>xtube;
        }
    }
}

void LinkQueue::ShowTube() {
    if(!IsEmpty()){
        for (Node *p = front->next; p != NULL; p = p->next)
            cout<<p->tube<<" ";
        cout<<endl;
    }
    else
        cout<<"无"<<endl;
}

void LinkQueue::SetComplete(int num, LinkQueue &q) {
    if(!IsEmpty()){
        Node *p1;
        for(int i=0;i<num;i++){
            p1=front->next;
            p1->status=3;
            q.EnQueue(p1->member,p1->tube,p1->status,p1->relation);
            DelQueue();
        }
    }
    else{
        cout<<"对列为空！ERROR！"<<endl;
    }

}

void LinkQueue::mixtubeShow() {
    if(GetLength()<10)
        cout<<"无"<<endl;
    else{
        int num=GetLength()/10,count=1;
        Node *p=front->next;
        for(int i=0;i<num;i++){
            cout<<p->tube<<" ";
            while(count<=10&&p!=NULL){
                p=p->next;
                count++;
            }
        }
        cout<<endl;
    }
}

void LinkQueue::TypeinSingle(string xtube, int xresult, LinkQueue &mixed_queue, LinkQueue &single_queue,
                             LinkQueue &mix_complete) {
    Node *p=front->next,*q;
    char a[3],b[3];
    int count=0,i=1,j;
    if(xresult==2){//单管阴性
        while(p->tube!=xtube)
            p=p->next;
        p->status=2;
    }
    else if(xresult==1){//单管阳性
        while(p->tube!=xtube){
            p=p->next;
            count++;
        }
        p->status=1;
        a[0]=p->member[0];
        a[1]=p->member[1];
        a[2]=p->member[2];
        mixed_queue.LouDong(a,5);//同楼栋设置为密接
        mix_complete.LouDong(a,5);//同楼栋设置为密接
        for(p=p->next;p!=NULL;p=p->next){//队伍后面设置为密接
            p->relation=5;
            b[0]=p->member[0];
            b[1]=p->member[1];
            b[2]=p->member[2];
            mix_complete.LouDong(b,6);
            mixed_queue.LouDong(b,6);
            for(j=1,q=front->next;j<=count-10;j++){
                if(q->member[0]==b[0]&&q->member[1]==b[1]&&q->member[2]==b[2]){
                    if(q->relation!=5&&q->status!=1)
                        q->relation=6;
                }
                q=q->next;
            }
        }
        single_queue.SetRelation(5,mixed_queue,single_queue,mix_complete,*this);//队伍后面设置为密接
        //前十个设置为密接且同楼栋密接,密接同楼栋次密接
        if(count<=10){
            for(p=front->next;p->tube!=xtube;p=p->next){
                p->relation=5;
                b[0]=p->member[0];
                b[1]=p->member[1];
                b[2]=p->member[2];
                mix_complete.LouDong(b,6);
                mixed_queue.LouDong(b,6);
            }
        }
        else{
            for(p=front->next;p->tube!=xtube;p=p->next,i++){
                if(i<=count-10){
                    if(p->member[0]==a[0]&&p->member[1]==a[1]&&p->member[2]==a[2]){
                        p->relation=5;
                        b[0]=p->member[0];
                        b[1]=p->member[1];
                        b[2]=p->member[2];
                        mix_complete.LouDong(b,6);
                        mixed_queue.LouDong(b,6);
                        for(j=1,q=front->next;j<=count-10;j++){
                            if(q->member[0]==b[0]&&q->member[1]==b[1]&&q->member[2]==b[2]){
                                if(q->relation!=5&&q->status!=1)
                                    q->relation=6;
                            }
                             q=q->next;
                        }
                    }
                }
                else{
                    p->relation=5;
                    b[0]=p->member[0];
                    b[1]=p->member[1];
                    b[2]=p->member[2];
                    mix_complete.LouDong(b,6);
                    mixed_queue.LouDong(b,6);
                    for(j=1,q=front->next;j<=count-10;j++){
                        if(q->member[0]==b[0]&&q->member[1]==b[1]&&q->member[2]==b[2]){
                            if(q->relation!=5&&q->status!=1)
                                q->relation=6;
                        }
                        q=q->next;
                    }
                }
            }
        }
    }
    else{//可疑管
        while(p->tube!=xtube)
            p=p->next;
        p->status=7;
    }
}

void LinkQueue::LouDong(char *a, int relation) {
    for (Node *p = front->next; p != NULL; p = p->next){
        if(p->member[0]==a[0]&&p->member[1]==a[1]&&p->member[2]==a[2])
            if(p->relation!=5&&p->status!=1)
                p->relation=relation;
    }
}

void LinkQueue::SetRelation(int relation,LinkQueue &mixed_queue, LinkQueue &single_queue,LinkQueue &mix_complete,LinkQueue &single_complete) {
    char b[3];
    for (Node *p = front->next; p != NULL; p = p->next){
        p->relation=relation;
        b[0]=p->member[0];
        b[1]=p->member[1];
        b[2]=p->member[2];
        mix_complete.LouDong(b,6);
        mixed_queue.LouDong(b,6);
        single_complete.LouDong(b,6);
        single_queue.LouDong(b,6);
    }
}

void LinkQueue::showstatus() {
    if(!IsEmpty()){
        for (Node *p = front->next; p != NULL; p = p->next)
            cout<<p->status<<" "<<p->relation<<endl;
        cout<<endl;
    }
    else
        cout<<"无"<<endl;
}

void LinkQueue::ShowStatus(int type) {
    if(!IsEmpty()){
        for (Node *p = front->next; p != NULL; p = p->next){
            if(p->status==type)
                cout<<p->member<<" ";
        }
    }
}

void LinkQueue::ShowRelation(int type) {
    if(!IsEmpty()){
        for (Node *p = front->next; p != NULL; p = p->next){
            if(p->relation==type)
                cout<<p->member<<" ";
        }
    }
}

Status LinkQueue::Search(const string xmember) {
    if(!IsEmpty()){
        for (Node *p = front->next; p != NULL; p = p->next){
            if(p->member==xmember){
                if(p->status==1)
                    cout<<"确诊"<<" ";
                else{
                    switch (p->status){
                        case 2:
                            cout<<"阴性"<<" ";
                            break;
                        case 3:
                            cout<<"待上传结果"<<" ";
                            break;
                        case 4:
                            cout<<"在排队"<<" ";
                            break;
                        case 7:
                            cout<<"可疑"<<" ";
                            break;
                    }
                    switch (p->relation){
                        case 5:
                            cout<<"密接"<<" ";
                            break;
                        case 6:
                            cout<<"次密接"<<" ";
                            break;
                    }
                }
                cout<<endl;
                return SUCCESS;
            }
        }
        return FAIL;
    }
    else{
        return UNDER_FLOW;
    }
}

void LinkQueue::TypeinMix(string xtube, int xresult, LinkQueue &mixed_queue, LinkQueue &single_queue,
                          LinkQueue &mix_complete) {
    Node *p=front->next;
    if(xresult==2){//混管阴性
        while(p->tube!=xtube)
            p=p->next;
        for(;p->tube==xtube;p=p->next){
            p->status=2;
        }
    }
    else{//阳性混合管或可疑管均标记可疑
        while(p->tube!=xtube)
            p=p->next;
        for(;p->tube==xtube;p=p->next){
            p->status=7;
        }
    }
}

#endif //NUCLEIC_ACID_TEST_SYSTEM_LINKQUEUE_H
