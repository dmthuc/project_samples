#include <string>
#include <iostream>
#include <log_model.pb.h>
#include <fstream>
#include <sstream>


using namespace std;

int main (int argc, char * argv[]) {
    if (argc !=2)
    {
        cout << "please enter filename\n";
        return 0;
    }
    const string filename = argv[1];
    cout << "gonna read filename" << filename << '\n';

    std::ifstream t(filename);
    std::stringstream buffer;
    buffer << t.rdbuf();
    string value = buffer.str();

    Database::LogMeta log_meta;
    log_meta.ParseFromString(value);
    
    cout << log_meta.log_name() << '\n';
#if 0
  required string log_name = 1;
  required string type = 2;
  required uint64 min_lsn = 3;
#endif

#if 0
    Message::Message proto_message{};
    proto_message.ParseFromString(recv_message);
    if (proto_message.has_type()) {
        cout << "type:" << proto_message.type() << std::endl;
    }

    if (proto_message.has_content()) {
        cout << "content:" << proto_message.content() << std::endl;
    }
#endif
    return 0;
}

