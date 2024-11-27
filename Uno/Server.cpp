#include "Server.h"

void Server::send(const std::string data) {
    sf::Packet packet;
    const char* data_c = data.c_str();
    socket.send(data_c, sizeof(data_c) - 1);
}

std::string Server::recv() {
    char data[1024];
    std::size_t rec;

    socket.receive(data, 1024, rec);
    std::string str(data, rec);
    return str;
}

Server::Server() {
    sf::Socket::Status a = socket.connect(SERVER_ADDRESS, SERVER_PORT);
    send("new");
    this->join_code = recv();
    this->player_id = 0;
}

Server::Server(std::string join_code) {
    socket.connect(SERVER_ADDRESS, SERVER_PORT);
    send(join_code);
    this->join_code = join_code;
    std::string id_s = recv();
    this->player_id = std::stoi(id_s);
}

Server::~Server() {
    socket.disconnect();
}

int Server::get_player_id() const {
    return this->player_id;
}

std::string Server::get_join_code() const {
    return this->join_code;
}
