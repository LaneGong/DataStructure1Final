//
// Created by Gong chen on 2022/4/16.
//

#ifndef NUCLEIC_ACID_TEST_SYSTEM_NODE_H
#define NUCLEIC_ACID_TEST_SYSTEM_NODE_H
#include <string>
struct Node
{

    string member;//人员编号
    string tube;//试管号
    //0代表空
    int status;//状态：1.确诊 2.阴性 3.待上传结果 4.在排队 7.可疑
    int relation;//关系：5.密接 6.次密接
    Node *next;

    Node();
    Node(string xmember,string xtube="0",int xstatus=4,int xrelation=0,Node *link = NULL);
};


Node::Node()
{
    next = NULL;
}

Node::Node(string xmember, string xtube, int xstatus, int xrelation, Node *link) {
    member=xmember;
    tube=xtube;
    status=xstatus;
    relation=xrelation;
    next=link;
}



#endif //NUCLEIC_ACID_TEST_SYSTEM_NODE_H
