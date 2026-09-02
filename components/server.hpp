#include <string>
#include <crow.h>


class Server {
    crow::SimpleApp app;
public:
    Server();
    void run();
    std::string downloadFile(std::string link, std::string format);
};
