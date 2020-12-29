#include <iostream>
#include "Network.h"
#include <memory>
#include "Core.h"
#include "Logger.h"
using namespace TSP_NS;
using namespace std;
using std::shared_ptr;

int main(int argc, char **argv){
    // Init logger
    Logger::initLogger("network_test", "./log");

    // Logger::shutdown();
    // add two nodes.
    shared_ptr<Node> n1 = make_shared<Node>(1);
    shared_ptr<Node> n2 = make_shared<Node>(2);
    // delay and bandwidth (1 ms, 1GB)
    shared_ptr<Link> link = make_shared<Link>(Time(MilliSecond, 1), 1000*1024*1024);  

    //将n1,n2通过link连接
    n1->addLink(Ipv4Address("10.0.0.1"), link);
    n2->addLink(Ipv4Address("10.0.0.2"), link);

    // //给节点设置路由
    // n1->addRouteItem(Ipv4Address("10.0.0.0"), Ipv4Address("255.255.255.0"), 0);
    // n2->addRouteItem(Ipv4Address("10.0.0.0"), Ipv4Address("255.255.255.0"), 0);

    //生成一个从n1到n2的数据包
    shared_ptr<Packet> pkt = make_shared<Packet>("10.0.0.1", "10.0.0.2", 64, "test");

    //插入事件: n1 在 1 second的时候，将 pkt 发送出去.
    Simulator::schedule(n1->getNodeId(), Time(Second,1), "Send packet",  &Node::sendDefault, n1, pkt);  
    Simulator::run(3);  // Num of threads
    Simulator::destroy();
}