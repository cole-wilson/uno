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
#include <math.h>


int main() {
    Game game;

    game.drawpile.shuffle();

    // create the window
    sf::RenderWindow window(sf::VideoMode(2000, 1500), "UNO");
        
    Menu menu(window.getSize().x, window.getSize().y);

    game.discardpile.put_face_up(game.drawpile.draw_one_card());

    for (int pid = 0; pid < game.serv.get_player_id(); pid++) {
        for (int cardi = 0; cardi < 7; cardi++) {
            game.drawpile.burn_one_card();
        }
    }
    for (int i = 0; i < 7; i++) {
        game.hand.put_face_up(game.drawpile.draw_one_card());
    }

    //https://stackoverflow.com/questions/49509687/passing-an-entire-class-as-argument-to-a-thread-c-as-in-c-sharp
    std::thread gamethread;

    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::TextEntered && game.mode == JOIN_MENU && JOIN_STATE)
            {

            }
            else if (event.type == sf::Event::KeyPressed && game.mode == JOIN_MENU)
            {
                if (event.key.code == sf::Keyboard::Up && menu.menu_state == INITIAL_STATE)
                {
                    menu.MoveUp();
                }
                else if (event.key.code == sf::Keyboard::Down && menu.menu_state == INITIAL_STATE)
                {
                    menu.MoveDown();
                }
                else if (event.key.code == sf::Keyboard::Return && menu.menu_state == INITIAL_STATE)
                {
                    switch (menu.PressedItem())
                    {
                    case 0:
                        menu.HostPressed(game);
                        break;
                    case 1:
                       menu.menu_state = JOIN_STATE;
                       break;
                    case 2:
                        window.close();
                        exit(0);
                        break;
                    }
                }
                else if (event.key.code == sf::Keyboard::Return && menu.menu_state == HOST_STATE)
                {
                    game.serv.send("start");
                    game.n_players = std::stoi(game.serv.recv());
                    game.serv.send(game.drawpile.to_string());
                    gamethread = std::thread(&Game::mainloop, &game);
                }
                else if (event.key.code == sf::Keyboard::Return && menu.menu_state == JOIN_STATE)
                {
                    game.serv.join_game("DEBUG"); // should be the thingy the user typed
                    gamethread = std::thread(&Game::mainloop, &game);
                }
            
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.scancode == sf::Keyboard::Scan::Left && game.mode == SELECTING_CARD) {
                    game.handindex = std::max(0, game.handindex - 1);
                }
                else if (event.key.scancode == sf::Keyboard::Scan::Right && game.mode == SELECTING_CARD) {
                    game.handindex = std::min(game.hand.size() - 1, game.handindex + 1);
                }
                else if (event.key.scancode == sf::Keyboard::Scan::Space && game.mode == SELECTING_CARD) {
                    game.release_select();
                }
                else if (event.key.scancode == sf::Keyboard::Scan::Left && game.mode == SELECTING_WILD_COLOR) {
                    game.chosen_color = std::max(0, game.chosen_color - 1);
                }
                else if (event.key.scancode == sf::Keyboard::Scan::Right && game.mode == SELECTING_WILD_COLOR) {
                    game.chosen_color = std::min(3, game.chosen_color + 1);
                }
                else if (event.key.scancode == sf::Keyboard::Scan::Space && game.mode == SELECTING_WILD_COLOR) {
                    game.release_select();
                }
            }
        }

        // clear the window with black color
        window.clear(sf::Color::Black);
        if (game.mode == JOIN_MENU) {
            menu.draw(window);
        }
        else {
            Card discard_card = *game.discardpile.read_face_up();
            discard_card.setPosition(200 + (window.getSize().x / 2), window.getSize().y / 2)
            window.draw();

            for (int i = 0; i <= game.handindex; i++) {
                if (i != game.handindex && game.mode == SELECTING_CARD) {
                    Card card = *game.hand.get_all_cards().at(i);
                    card.setPosition(i * 70, 500);
                    window.draw(card);
                }
            }
            for (int i = game.hand.size() - 1; i > game.handindex; i--) {
                if (i != game.handindex && game.mode == SELECTING_CARD) {
                    Card card = *game.hand.get_all_cards().at(i);
                    card.setPosition(i * 70, 500);
                    window.draw(card);
                }
            }

        }
        if (game.mode == SELECTING_CARD) {
            Card selectedcard = *game.hand.get_all_cards().at(game.handindex);
            selectedcard.setPosition(game.handindex * 70, 470);
            window.draw(selectedcard);
        }

        if (game.mode == SELECTING_WILD_COLOR) {
            sf::RectangleShape color(sf::Vector2f(500, 500));
            sf::Color colors[] = { sf::Color::Red, sf::Color::Green, sf::Color::Blue, sf::Color::Yellow };
            color.setFillColor(colors[game.chosen_color]);
            color.setPosition(250, 250);
            window.draw(color);
        }


        // end the current frame
        window.display();
    }
    gamethread.join();

    return 0;
}