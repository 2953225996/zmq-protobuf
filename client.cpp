#include<iostream>
#include<zmq.hpp>
#include"stu.pb.h"
using namespace std;
using namespace zmq;
using namespace proto;
int main(){
    context_t context(1);
    socket_t socket(context, ZMQ_REQ);
    socket.connect("tcp://localhost:5555");
    
    stu sendstu;
    sendstu.set_id(0);
    sendstu.set_name("Jerry");
    sendstu.set_gender(stu::female);
    stu::subject *sub1=sendstu.add_subjects();
    sub1->set_name("语文");
    sub1->set_score(90);
    stu::subject *sub2=sendstu.add_subjects();
    sub2->set_name("数学");
    sub2->set_score(95);
    stu::subject *sub3=sendstu.add_subjects();
    sub3->set_name("英语");
    sub3->set_score(85);
    (*sendstu.mutable_teacher())["语文"]="张三";
    (*sendstu.mutable_teacher())["数学"]="李四";
    (*sendstu.mutable_teacher())["英语"]="王五";
    char sendarr[sendstu.ByteSize()]; 
    sendstu.SerializeToArray(sendarr,sendstu.ByteSize());
    socket.send(sendarr,sendstu.ByteSize());

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
    return 0;
}