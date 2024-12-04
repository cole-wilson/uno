#include "GraphicsMain.h"

GraphicsMain::GraphicsMain() {
    uno_sound = new SoundPlayer("sounds/uno.wav");
    click_sound = new SoundPlayer("sounds/click.wav");
    card_sound = new SoundPlayer("sounds/card.wav");
    uno_sound->play();


    if (!cardback_texture.loadFromFile("cards/back.png")) {}
    drawpile_sprite = sf::Sprite(cardback_texture);

    if (!helvetica.loadFromFile("helvetica.ttf")) {
        std::cerr << "Font error..." << std::endl;
    }

    mainmessage.setFont(helvetica);
    mainmessage.setFillColor(sf::Color::Yellow);
    mainmessage.setCharacterSize(60);
    mainmessage.setPosition(0, 470);
    mainmessage.setStyle(sf::Text::Bold);

    otherplayers.setFont(helvetica);
    otherplayers.setFillColor(sf::Color::Black);
    otherplayers.setPosition(500, 0);
    otherplayers.setStyle(sf::Text::Bold);

    background_color = sf::Color(222, 113, 17);
}

void GraphicsMain::run()
{
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "UNO");
    Menu menu(window.getSize().x, window.getSize().y);
    sf::Event event;

    while (window.isOpen()) {
        if (game.drawpile.size() == 1) {
            game.drawpile.clear_from_string(game.discardpile.to_string());
            game.discardpile.clear_from_string("B0,B0");
            game.discardpile.put_face_up(game.drawpile.draw_one_card());
        }

        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::TextEntered && game.mode == MENU && menu.menu_state == JOIN_STATE)
            {
                click_sound->play();

                char c = event.text.unicode;
                if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')) {
                    if ((c >= 'a' && c <= 'z')) {
                        c = (c - 'a') + 'A';
                    }
                    codeInput += c;
                    menu.CodeStore(game, codeInput);
                }
            }
            else if (event.type == sf::Event::KeyPressed && game.mode == MENU)
            {
                click_sound->play();

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
                        menu.CodeStore(game, codeInput);
                        break;
                    case 2:
                        window.close();
                        exit(0);
                        break;
                    }
                }
                else if (event.key.code == sf::Keyboard::Return && menu.menu_state == HOST_STATE)
                {
                    game.drawpile.shuffle();
                    game.n_players = game.serv.start_game(game.drawpile.to_string());
                    gamethread = std::thread(&Game::mainloop, &game);
                }
                else if (event.key.code == sf::Keyboard::Return && menu.menu_state == JOIN_STATE)
                {
                    bool success = game.serv.join_game(codeInput); // should be the thingy the user typed
                    if (success)
                    {
                        gamethread = std::thread(&Game::mainloop, &game);
                        menu.menu_state = WAITING_STATE;
                    }
                    else
                    {
                        menu.CodeStore(game, "Wrong code, please restart the game!");
                    }

                }
                else if (event.key.code == sf::Keyboard::Backspace && menu.menu_state == JOIN_STATE)
                {
                    codeInput = codeInput.substr(0, codeInput.size() - 1);
                    menu.CodeStore(game, codeInput);
                }

            }
            else if (event.type == sf::Event::KeyPressed)
            {
                card_sound->play();

                if (event.key.scancode == sf::Keyboard::Scan::Left && game.mode == SELECTING_CARD) {
                    game.handindex = std::max(0, game.handindex - 1);
                }
                else if (event.key.scancode == sf::Keyboard::Scan::Right && game.mode == SELECTING_CARD) {
                    game.handindex = std::min(game.hand.size() - 1, game.handindex + 1);
                }
                else if ((event.key.scancode == sf::Keyboard::Scan::Space || event.key.scancode == sf::Keyboard::Scan::Enter) && game.mode == SELECTING_CARD) {
                    game.release_select();
                }
                else if ((event.key.scancode == sf::Keyboard::Scan::D) && game.mode == SELECTING_CARD) {
                    game.handindex = -1;
                    game.release_select();
                }
                /*else if ((event.key.scancode == sf::Keyboard::Scan::P) && game.mode == SELECTING_CARD) {
                    game.handindex = -2;
                    game.release_select();
                }*/
                else if (event.key.scancode == sf::Keyboard::Scan::Left && game.mode == SELECTING_WILD_COLOR) {
                    game.chosen_color = std::max(0, game.chosen_color - 1);
                }
                else if (event.key.scancode == sf::Keyboard::Scan::Right && game.mode == SELECTING_WILD_COLOR) {
                    game.chosen_color = std::min(3, game.chosen_color + 1);
                }
                else if ((event.key.scancode == sf::Keyboard::Scan::Space || event.key.scancode == sf::Keyboard::Scan::Enter) && game.mode == SELECTING_WILD_COLOR) {
                    game.release_select();
                }
            }
            else if (event.type == sf::Event::MouseMoved || event.type == sf::Event::MouseButtonPressed)
            {
                int mx = event.type == sf::Event::MouseMoved ? event.mouseMove.x : event.mouseButton.x;
                int my = event.type == sf::Event::MouseMoved ? event.mouseMove.y : event.mouseButton.y;

                for (int i = -1; i < (int)game.hand.get_all_cards().size(); i++) {
                    sf::FloatRect cardbox;

                    if (i < 0) {
                        cardbox = drawpile_sprite.getGlobalBounds();
                    }
                    else {
                        Card* card = game.hand.get_all_cards().at(i);
                        cardbox = card->getGlobalBounds();
                    }

                    int rightbound = cardbox.left + 70;
                    if (i == game.handindex || i == game.hand.get_all_cards().size() - 1 || i == -1) {
                        rightbound = cardbox.left + cardbox.width;
                        ;
                    }

                    bool in_x = mx > cardbox.left && mx < rightbound;
                    bool in_y = my > cardbox.top && my < cardbox.top + cardbox.height;

                    if (in_x && in_y) {
                        if (game.handindex != i) {
                            card_sound->play();
                        }
                        game.handindex = i;
                        if (event.type == sf::Event::MouseButtonPressed && game.mode == SELECTING_CARD && event.mouseButton.button == sf::Mouse::Left) {
                            game.release_select();
                        }
                        break;
                    }
                }
            }
        }

        if (game.mode == MENU)
        {
            window.clear(sf::Color::Black);
            menu.draw(window);
            mainmessage.setString("");
        }
        else if (game.mode == WIN) {
            window.clear(sf::Color::Black);
            menu.draw(window);
            if (game.turn == game.serv.get_player_id()) {
                mainmessage.setString("You WON!!!");
            }
            else {
                mainmessage.setString("You LOST...\nPlayer " + std::to_string(game.turn) + " won!");
            }
        }
        else
        {
            // main game screen
            window.clear(sf::Color::Red);

            std::string oplayer_text;
            for (int i = 0; i < game.n_players; i++) {
                std::string arrow = game.turn == i ? (game.direction == 1 ? ">>> " : "<<< ") : "    ";
                oplayer_text += arrow + "Player " + std::to_string(i + 1) + ": " + std::to_string(game.n_cards[i]) + " cards\n";
            }
            otherplayers.setString(oplayer_text);
            window.draw(otherplayers);


            Card discard_card = *game.discardpile.read_face_up();
            discard_card.setPosition(240, 0);
            window.draw(discard_card);
            window.draw(drawpile_sprite);

            for (int i = 0; i < game.hand.size(); i++) {
                if (i != game.handindex || game.mode != SELECTING_CARD) {
                    Card* card = game.hand.get_all_cards().at(i);
                    card->setPosition(i * 70, window.getSize().y - 360);
                    window.draw(*card);
                }
            }
            if (game.mode == SELECTING_CARD || game.mode == WAITING_FOR_OTHER_PLAYERS) {
                mainmessage.setString("Select a Card To Play:\n(D to Draw)");
                int cardindex = std::max(0, game.handindex);
                Card* selectedcard = game.hand.get_all_cards().at(cardindex);
                selectedcard->setPosition(cardindex * 70, window.getSize().y - 400);
                window.draw(*selectedcard);
            }
            if (game.mode == WAITING_FOR_OTHER_PLAYERS) {
                mainmessage.setString("Waiting for Player " + std::to_string(game.turn + 1) + "...");
            }

            if (game.mode == SELECTING_WILD_COLOR) {
                mainmessage.setString("Choose Wild Color: (arrow keys)");
                sf::Color colors[] = { sf::Color::Red, sf::Color::Green, sf::Color::Blue, sf::Color::Yellow };

                sf::RectangleShape m_color(sf::Vector2f(1000, 400));
                m_color.setFillColor(colors[game.chosen_color]);
                m_color.setPosition(0, 600);
                window.draw(m_color);

                if (game.chosen_color > 0) {
                    sf::RectangleShape l_color(sf::Vector2f(20, 400));
                    l_color.setFillColor(colors[game.chosen_color - 1]);
                    l_color.setPosition(0, 600);
                    window.draw(l_color);
                }

                if (game.chosen_color < 3) {
                    sf::RectangleShape r_color(sf::Vector2f(20, 400));
                    r_color.setFillColor(colors[game.chosen_color + 1]);
                    r_color.setPosition(980, 600);
                    window.draw(r_color);
                }
            }
        }

        window.draw(mainmessage);

        // end the current frame
        window.display();
    }
    
    gamethread.join();
}
