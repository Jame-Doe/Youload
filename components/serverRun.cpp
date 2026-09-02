#include "server.hpp"

void Server::run() {
    this->app.port(18080).multithreaded().run();
}
