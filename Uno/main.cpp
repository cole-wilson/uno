#include "Deck.h"
#include "NumberCard.h"
#include "ActionCard.h"

#include "Server.h"

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>


int main()
{
    Deck drawpile("B0,B1,B1,B2,B2,B3,B3,B4,B4,B5,B5,B6,B6,B7,B7,B8,B8,B9,B9,Bs,Bs,Br,Br,Bd,Bd,G0,G1,G1,G2,G2,G3,G3,G4,G4,G5,G5,G6,G6,G7,G7,G8,G8,G9,G9,Gs,Gs,Gr,Gr,Gd,Gd,R0,R1,R1,R2,R2,R3,R3,R4,R4,R5,R5,R6,R6,R7,R7,R8,R8,R9,R9,Rs,Rs,Rr,Rr,Rd,Rd,Y0,Y1,Y1,Y2,Y2,Y3,Y3,Y4,Y4,Y5,Y5,Y6,Y6,Y7,Y7,Y8,Y8,Y9,Y9,Ys,Ys,Yr,Yr,Yd,Yd,Ww,Ww,Ww,Ww,Wd,Wd,Wd,Wd");
    Deck discardpile;
    Deck hand;
    int n_players = -1;

    drawpile.shuffle();

    discardpile.put_face_up(drawpile.draw_one_card());

    // host or join
    std::string host = "";
    std::cout << "y to host:";
    std::cin >> host;
    Server serv;

    if (host== "y") {
        serv.new_game();
        std::cout << serv.get_join_code() << std::endl;
        std::cout << "enter to start...";
        std::cin >> host;
        serv.send("start");
        n_players = std::stoi(serv.recv());
        std::cout << n_players << std::endl;
        serv.send(drawpile.to_string());
        serv.send(discardpile.to_string());
    }
    else {
        std::string code;
        std::cout << "join code: ";
        std::cin >> code;
        serv.join_game(code);
        int id = serv.get_player_id();
        std::cout << "player id: " << id << std::endl;
        n_players = std::stoi(serv.recv());
        std::cout << n_players << std::endl;
        drawpile.clear_from_string(serv.recv());
        discardpile.clear_from_string(serv.recv());
    }

    std::cout << "draw:" << std::endl << drawpile.to_string() << std::endl;
    std::cout << std::endl << "discard:" << std::endl << discardpile.to_string() << std::endl;

    return 0;
}