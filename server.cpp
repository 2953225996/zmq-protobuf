#include<iostream>
#include<zmq.hpp>
#include"stu.pb.h"
using namespace std;
using namespace zmq;
using namespace proto;
int main(){
    context_t   context(1);
    socket_t socket(context, ZMQ_REP);
    socket.bind("tcp://*:5555");
    
    stu sendstu;
    message_t recv_msg;
    socket.recv(&recv_msg);
    char recvarr[recv_msg.size()];
    memcpy(recvarr,recv_msg.data(),recv_msg.size());
    stu recvstu;
    recvstu.ParseFromArray(recvarr,recv_msg.size());
    cout<<"学生id : "<<recvstu.id()<<endl;
    cout<<"学生姓名 : "<<recvstu.name()<<endl;
    cout<<"学生性别 : "<<(recvstu.gender()==stu::male?"男":"女")<<endl;
    cout<<"成绩表 :"<<endl;
    for(int i=0;i<recvstu.subjects_size();i++){
        cout<<"科目 : "<<recvstu.subjects(i).name()<<"    分数 : "<<recvstu.subjects(i).score()<<endl;
    }
    cout<<"老师表 :"<<endl;
    for(auto it=recvstu.teacher().begin();it!=recvstu.teacher().end();it++){
        cout<<"科目 : "<<it->first<<"    老师 : "<<it->second<<endl;
    }

    sendstu.set_id(1);
    sendstu.set_name("Tom");
    sendstu.set_gender(stu::male);
    stu::subject *sub1=sendstu.add_subjects();
    sub1->set_name("Computer Network");
    sub1->set_score(90);
    stu::subject *sub2=sendstu.add_subjects();
    sub2->set_name("Operating System");
    sub2->set_score(95);
    stu::subject *sub3=sendstu.add_subjects();
    sub3->set_name("Database");
    sub3->set_score(85);
    stu::subject *sub4=sendstu.add_subjects();
    sub4->set_name("Data Structure");
    sub4->set_score(95);
    (*sendstu.mutable_teacher())["Computer Network"]="John";
    (*sendstu.mutable_teacher())["Operating System"]="Mike";
    (*sendstu.mutable_teacher())["Database"]="Alice";
    (*sendstu.mutable_teacher())["Data Structure"]="Bob";
    char sendarr[sendstu.ByteSize()]; 
    sendstu.SerializeToArray(sendarr,sendstu.ByteSize());
    socket.send(sendarr,sendstu.ByteSize());
}