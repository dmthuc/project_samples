//
//  Hello World client in C++
//  Connects REQ socket to tcp://localhost:5555
//  Sends "Hello" to server, expects "World" back
//
#include <zmq.hpp>
#include <string>
#include <iostream>
#include <message.pb.h>
using namespace std;

int main ()
{
    //  Prepare our context and socket
    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_REQ);

    std::cout << "Connecting to hello world server" << std::endl;
    socket.connect ("tcp://localhost:5555");

    //  Do 10 requests, waiting each time for a response
    for (int i = 0; i != 10; ++i) {
        Message::Message proto_message{};
        proto_message.set_type(Message::Message_Mesage_type_REQ); 
        proto_message.set_content("Hello");
        std::string message{};
        if (!proto_message.SerializeToString(&message)) {
            std::cerr<<"Fail to serialize"<<std::endl;
            continue;
        }

        zmq::message_t request (message.begin(), message.end());

        std::cout << "Sending " << i << "..." << std::endl;
        socket.send(request);

        //  Get the reply.
        zmq::message_t reply;
        socket.recv (&reply);
        std::cout << "Received reply:" << i << std::endl;

        string recv_message(static_cast<char*>(reply.data()), reply.size());
        proto_message.ParseFromString(recv_message);
        if (proto_message.has_type()) {
            cout << "type:" << proto_message.type() << std::endl;
        }

        if (proto_message.has_content()) {
            cout << "content:" << proto_message.content() << std::endl;
        }
    }
    return 0;
}

