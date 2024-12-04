/*
* Uno - CPT_S 122 Final Project
*
* Cole Wilson and Shane Ganz
*
* Server.cpp
*
* Handles communication with the Uno server hosted on an Oracle Ubuntu VPS instance.
* This handles interactions with other clients through the server, and uses sockets to
* communicate and serialize data.
*/

#include "Server.h"

void Server::send(const std::string data) {
    // constructo a packet from a string to send
    sf::Packet packet;
    const char* data_c = data.c_str();
    socket.send(data_c, strlen(data_c));
}

std::string Server::recv() {
    // recieve packet of up to 1024 bytes blocking
    char data[1024];
    std::size_t rec;

    // block
    socket.receive(data, 1024, rec);

    // read # of recieved bytes to a new string and return it
    std::string str(data, rec);
    return str;
}

Server::Server() {
    // connect to remote server in constructor
    sf::Socket::Status a = socket.connect(SERVER_ADDRESS, SERVER_PORT);
    this->player_id = -1;
}

void Server::new_game() {
    // send the 'new' command to get a random join code
    send("new");
    this->join_code = recv(); // wait for code
    this->player_id = 0; // host is id = 0
}

int Server::start_game(std::string drawpilestring)
{
    // ready to start after all players joined
    send("start");
    // get n_players
    int n_players = std::stoi(recv());
    send(drawpilestring); // send the deck
    return n_players;
}

bool Server::join_game(std::string join_code) {
    // send the join code and wait for player id
    send(join_code);
    this->join_code = join_code;
    std::string id_s = recv(); // get the id of player
    this->player_id = std::stoi(id_s); // make int
    if (this->player_id < 0) {
        // the code was expired or invalid...
        return false;
    }
    return true;
}

Server::~Server() {
    // disconnect from server in destructor
    socket.disconnect();
}

int Server::get_player_id() const {
    // getter
    return this->player_id;
}

std::string Server::get_join_code() const {
    // getter
    return this->join_code;
}

std::vector<std::string> Server::split_message(std::string data, char delim)
{
    // split string into series of tokens
    vector<string> tokens; // the vector of the spplit tokens
    string remaining = data;
    while (remaining.size() > 2) {
        // find next delim and split
        int delim_index = remaining.find(delim);
        string token = remaining.substr(0, delim_index);
        tokens.push_back(token);
        // get new remaining
        remaining = remaining.substr(delim_index + 1);
    }
    // push remaining tokens
    if (remaining.size() > 0) {
        tokens.push_back(remaining);
    }
    return tokens;
}
