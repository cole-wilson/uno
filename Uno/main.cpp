#include "Deck.h"
#include "Game.h"
#include "NumberCard.h"
#include "ActionCard.h"
#include "Menu.h"
#include <iostream>

#include "Server.h"

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include <thread>


int main() {
    Game game;


    //drawpile.shuffle();


        // create the window
        sf::RenderWindow window(sf::VideoMode(1000, 1000), "Start Game");
        
        Menu menu(window.getSize().x, window.getSize().y);

        // run the program as long as the window is open
        while (window.isOpen())
        {
            // check all the window's events that were triggered since the last iteration of the loop
            sf::Event event;
            while (window.pollEvent(event))
            {
                // "close requested" event: we close the window
                if (event.type == sf::Event::Closed)
                    window.close();

                switch (event.type)
                {
                case sf::Event::KeyReleased:
                    switch (event.key.code)
                    {
                    case sf::Keyboard::Up:
                        menu.MoveUp();
                        break;
                    case sf::Keyboard::Down:
                        menu.MoveDown();
                        break;
                    case sf::Keyboard::Return:
                        switch (menu.PressedItem())
                        {
                        case 0:
                            std::cout << "Host" << std::endl;
                            break;
                        case 1:
                            std::cout << "Join" << std::endl;
                            break;
                        case 2:
                            window.close();
                            break;
                        }
                        break;
                    }
                    break;
                }
            }

            // clear the window with black color
            //window.clear(sf::Color::Black);

            
            window.clear();
            menu.draw(window);
            window.display();
        }

    // host or join
    std::string host = "";
    std::cout << "y to host:";
    std::cin >> host;

    if (host== "y") {
        game.serv.new_game();
        std::cout << game.serv.get_join_code() << std::endl;
        std::cout << "enter to start...";
        std::cin >> host;
        game.serv.send("start");
        game.n_players = std::stoi(game.serv.recv());
        std::cout << game.n_players << std::endl;
        game.serv.send(game.drawpile.to_string());
    }
    else {
        std::string code;
        std::cout << "join code: ";
        std::cin >> code;
        game.serv.join_game(code);
        int id = game.serv.get_player_id();
        std::cout << "player id: " << id << std::endl;
        game.n_players = std::stoi(game.serv.recv());
        std::cout << game.n_players << std::endl;
        game.drawpile.clear_from_string(game.serv.recv());
    }

    game.discardpile.put_face_up(game.drawpile.draw_one_card());

    for (int pid = 0; pid < game.serv.get_player_id(); pid++) {
        for (int cardi = 0; cardi < 7; cardi++) {
            game.drawpile.burn_one_card();
        }
    }
    for (int i = 0; i < 7; i++) {
        game.hand.put_face_up(game.drawpile.draw_one_card());
    }

    // create the window


    //https://stackoverflow.com/questions/49509687/passing-an-entire-class-as-argument-to-a-thread-c-as-in-c-sharp
    std::thread gamethread(&Game::mainloop, &game);

    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // clear the window with black color
        window.clear(sf::Color::Black);
        window.draw(*game.discardpile.read_face_up());

        // end the current frame
        window.display();
    }
    gamethread.join();

    return 0;
}