#include "Game.h"

#include "Server.h"

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>


int main()
{
    Server host;
    Server client(host.get_join_code());
    std::cout << host.get_join_code() << " " << host.get_player_id() << std::endl;
    std::cout << client.get_join_code() << " " << client.get_player_id() << std::endl;

    /*sf::RenderWindow window(sf::VideoMode(1024, 512), "UNO");
    
    Game game;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.display();
    }*/

    return 0;
}