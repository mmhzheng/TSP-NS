#include "Link.h"
#include "Core.h"
#include "Simulator.h"

namespace TSP_NS {

    Link::Link( Time delay, UINT64_T dataRate )
        :_delay(delay), _sendRate(dataRate),
         _interframeGap(Second, (double)96.0/dataRate),
         _nodeL(std::make_pair(nullptr, Device())),
         _nodeR(std::make_pair(nullptr, Device()))
    {
        // Track Min Time Slice
        if(_delay < EventManager::MIN_LINK_DELAY) // This is bigger //
            EventManager::MIN_LINK_DELAY = _delay;
        if(Simulator::getEventCount() > 0)
            throw std::runtime_error("Do not setup links after insert an event!");
    }

    int Link::connect(std::shared_ptr<Node> node){
        if(_nodeL.first != nullptr && _nodeR.first != nullptr)
            return -1;
        if(_nodeL.first == nullptr)
            _nodeL.first = node;
        else
            _nodeR.first = node;
        return 0;
    }
    
  
    int Link::sendToDevice(shared_ptr<Node> srcNode, shared_ptr<Packet> pkt){
        Device& dev = getDevice(srcNode);
        dev.pushTxQueue(pkt);
        if(dev.getTxState() == IDLE)
            transmitStart(srcNode);
        return 0;
    }

    /* Event */
    void Link::transmitStart(shared_ptr<Node> srcNode){
        Device& dev = getDevice(srcNode);
        dev.setTxState(WORKING); // 开始工作
        shared_ptr<Packet> pkt = dev.peekTxQueue();
        Time transDelay(Second, pkt->getPktSize() * 8 / _sendRate); //seconds
        shared_ptr<Node> dstNode =  getAnother(srcNode);

        Simulator::schedule(srcNode->getNodeId(), 
                            Simulator::getTimestamp(srcNode->getNodeId(), transDelay + _interframeGap), 
                            "Packet TransComplete.", 
                            &Link::transmitComplete, this, dstNode, pkt);

    }

    /* Event */
    void Link::transmitComplete(shared_ptr<Node> dstNode, shared_ptr<Packet> pkt){
        shared_ptr<Node> srcNode =  getAnother(dstNode);

        Simulator::schedule(dstNode->getNodeId(),  
                            Simulator::getTimestamp(srcNode->getNodeId(),_delay),
                            "Packet Receive.", 
                            &Node::receiveBase, dstNode, shared_from_this(), pkt);     

        Device& dev = getDevice(srcNode);
        if(dev.isTxEmpty())
            dev.setTxState(IDLE);
        else 
            transmitStart(srcNode);
    }

    void Device::pushTxQueue(shared_ptr<Packet> pkt){
        _txQueue.push_back(pkt);
        _txSize += pkt->getPktSize();
    }

    shared_ptr<Packet> Device::peekTxQueue(){
        if(_txQueue.empty())
            return nullptr;
        shared_ptr<Packet> pkt = _txQueue.back();
        _txQueue.pop_front();
        _txSize -= pkt->getPktSize();
        return pkt;
    }

    bool Device::isTxEmpty()const{
        return _txQueue.empty();
    }

    void Device::setTxState(DEVICE_STATE state){
        _txState = state;
    }

    DEVICE_STATE Device::getTxState()const{
        return _txState;
    }
}