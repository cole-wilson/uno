#include "Server.h"

void Server::send(const std::string data) {
    sf::Packet packet;
    const char* data_c = data.c_str();
    socket.send(data_c, strlen(data_c));
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
    this->player_id = -1;
}

void Server::new_game() {
    send("new");
    this->join_code = recv();
    this->player_id = 0;
}

int Server::start_game(std::string drawpilestring)
{
    send("start");
    int n_players = std::stoi(recv());
    send(drawpilestring);
    return n_players;
}

bool Server::join_game(std::string join_code) {
    send(join_code);
    this->join_code = join_code;
    std::string id_s = recv();
    this->player_id = std::stoi(id_s);
    if (this->player_id < 0) {
        return false;
    }
    return true;
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

std::vector<std::string> Server::split_message(std::string data, char delim)
{
    vector<string> tokens;
    string remaining = data;
    while (remaining.size() > 2) {
        int delim_index = remaining.find(delim);
        string token = remaining.substr(0, delim_index);
        tokens.push_back(token);
        remaining = remaining.substr(delim_index + 1);
    }
    if (remaining.size() > 0) {
        tokens.push_back(remaining);
    }
    return tokens;
}
