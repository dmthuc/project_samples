//
//  Binds REP socket to tcp://*:5555
//
#include <zmq.hpp>
#include <string>
#include <iostream>
#include <message.pb.h>
#ifndef _WIN32
#include <unistd.h>
#else
#include <windows.h>

#define sleep(n)    Sleep(n)
#endif
using namespace std;
int main () {
    //  Prepare our context and socket
    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_REP);
    socket.bind ("tcp://*:5555");

    while (true) {
        zmq::message_t request;

        //  Wait for next request from client
        socket.recv (&request);
        string recv_message(static_cast<char*>(request.data()), request.size());
        Message::Message proto_message{};
        proto_message.ParseFromString(recv_message);
        if (proto_message.has_type()) {
            cout << "type:" << proto_message.type() << std::endl;
        }

        if (proto_message.has_content()) {
            cout << "content:" << proto_message.content() << std::endl;
        }

        //  Do some 'work'
        sleep(1);
        proto_message.set_type(Message::Message_Mesage_type_REP);
        proto_message.set_content("This is reply!");
        string wire_data;
        if (!proto_message.SerializeToString(&wire_data)) {
            cerr<<"Fail to serialize\n";
            continue;
        }

        //  Send reply back to client
        zmq::message_t reply (wire_data.begin(), wire_data.end());
        socket.send (reply);
    }

    return 0;
}

