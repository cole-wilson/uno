/*
* Uno - CPT_S 122 Final Project
*
* Cole Wilson and Shane Ganz
*
* Game.cpp
*
* Represents the main gane thread logic of Uno, minus the graphics. This runs a method
* in a seperate thread from the main graphics thread, and communicates with the main thread
* using locks, mutexes, and condition variables. It is a friend of GraphicsMain in order to
* share state across threads. Many variables are not technically thread-safe, although extra
* care has been taking to only read and write to the necessary ones.
*/


#include "Game.h"

// construct the draw pile from all uno cards
Game::Game() : drawpile("B0,B1,B1,B2,B2,B3,B3,B4,B4,B5,B5,B6,B6,B7,B7,B8,B8,B9,B9,Bs,Bs,Br,Br,Bd,Bd,G0,G1,G1,G2,G2,G3,G3,G4,G4,G5,G5,G6,G6,G7,G7,G8,G8,G9,G9,Gs,Gs,Gr,Gr,Gd,Gd,R0,R1,R1,R2,R2,R3,R3,R4,R4,R5,R5,R6,R6,R7,R7,R8,R8,R9,R9,Rs,Rs,Rr,Rr,Rd,Rd,Y0,Y1,Y1,Y2,Y2,Y3,Y3,Y4,Y4,Y5,Y5,Y6,Y6,Y7,Y7,Y8,Y8,Y9,Y9,Ys,Ys,Yr,Yr,Yd,Yd,Ww,Ww,Ww,Ww,Wf,Wf,Wf,Wf") {
    this->select_has_selected = false;
    this->n_cards = nullptr;
}

void Game::quit_thread()
{
    this->quit = true;
}

void Game::mainloop() {
    // get sound for when it's Uno time!
    SoundPlayer uno_sound("uno.wav");

    if (serv.get_player_id() != 0) {
        // finish setup if this isn't host computer
        // this is only in game mainloop thread because it's blocking
        n_players = std::stoi(serv.recv());
        drawpile.clear_from_string(serv.recv());
    }

    // set up draw pile
    discardpile.put_face_up(drawpile.draw_one_card());
    while (discardpile.read_face_up()->get_type() == ACTION) {
        discardpile.put_face_up(drawpile.draw_one_card());
    }


    // discard cards "drawn" by other networked players earlier in line
    for (int pid = 0; pid < serv.get_player_id(); pid++) {
        for (int cardi = 0; cardi < 7; cardi++) {
            drawpile.burn_one_card();
        }
    }
    // draw 7 cards for self
    for (int i = 0; i < 7; i++) {
        hand.put_face_up(drawpile.draw_one_card());
    }

    // initialize n_cards
    n_cards = new int[n_players];
    for (int i = 0; i < n_players; i++) {
        n_cards[i] = 7;
    }

    // mainloop
    while (!quit) {
        // the card to match (top of discard pile)
        Card* tomatch = discardpile.read_face_up();

        // for when direction is -1 and it goes below 0, then
        // roll over
        if (turn < 0) turn += n_players;

        if (turn == serv.get_player_id()) {
            // do my turn
            int cards_drawn = 0; // number of cards self drew
            Card* card_played = nullptr; // the card i played
            int next_player; // placeholder for the next player

            // if the faceup card is a draw card, then draw those cards
            if (tomatch->get_type() == ACTION) {
                ActionCard* tomatch_action = dynamic_cast<ActionCard*>(tomatch);
                if (tomatch_action->get_action() == DRAW) {
                    cards_drawn = 1;
                }
                else if (tomatch_action->get_action() == WILD_DRAW_FOUR) {
                    cards_drawn = 4;
                }
                else {
                    // don't need to worry about skip or reverse because handled during prev. turn!
                }
                // actually draw said cards from pile
                for (int i = 0; i < cards_drawn; i++) {
                    hand.put_face_up(drawpile.draw_one_card());
                }
            }

            // set mode to SELECTING_CARD
            mode = SELECTING_CARD;
            int n_draws = 0; // number of times the player has drawn a card from deck (after discard pile draw cards)
            while (true) {
                // update display of # of cards:
                this->n_cards[0] = hand.size();

                // wait and block for main graphics thread to select the card
                // (waits until condition variable set)
                wait_select();

                // update display of # of cards again:
                this->n_cards[0] = hand.size();

                // the potential card to play
                Card* potential_card;

                if (handindex == -1) {
                    // if handindex == -1 then user clicked draw pile
                    if (++n_draws == 2) {
                        // if they have drawn twice then break out
                        break;
                    }

                    // draw that card
                    potential_card = drawpile.draw_one_card();
                    // put it in the hand
                    hand.put_face_up(potential_card);

                    // and select it
                    handindex = hand.size() - 1;
                }
                else {
                    // get the card from handindex
                    potential_card = hand.get_all_cards().at(handindex);
                }

                // check if card is okay

                // if color matches: (or wild)
                bool color_okay = potential_card->get_color() == tomatch->get_color() || potential_card->get_color() == WILD_CARD;
                
                // if action == action or num == num
                bool type_num_okay = false;
                if (potential_card->get_type() == ACTION && tomatch->get_type() == ACTION) {
                    CARD_ACTION pot_action = dynamic_cast<ActionCard*>(potential_card)->get_action();
                    CARD_ACTION match_action = dynamic_cast<ActionCard*>(tomatch)->get_action();
                    type_num_okay = pot_action == match_action;
                }
                else if (potential_card->get_type() == NUMBER && tomatch->get_type() == NUMBER) {
                    int pot_num = dynamic_cast<NumberCard*>(potential_card)->get_number();
                    int match_num = dynamic_cast<NumberCard*>(tomatch)->get_number();
                    type_num_okay = pot_num == match_num;
                }

                // if it's all okay then break out of selection loop
                if (color_okay || type_num_okay) {
                    break;
                }
            }

            // if we have card to play, do that otherwise set card_played to nullptr
            card_played = handindex < 0 ? nullptr : hand.draw_one_card(handindex--);

            // start the potential new player
            next_player = (turn + direction) % n_players;

            // handle the next player logic if skip or reverse played
            // and also choose wild color if wild played
            if (card_played != nullptr && card_played->get_type() == ACTION) {
                // dynamic cast Card* to ActionCard*
                CARD_ACTION action_type = dynamic_cast<ActionCard*>(card_played)->get_action();
                if (card_played->get_color() == WILD_CARD) {
                    // block for graphicsmain to choose a wild card color
                    mode = SELECTING_WILD_COLOR;
                    wait_select(); // block...
                    CARD_COLOR colors[] = { RED, GREEN, BLUE, YELLOW };
                    CARD_COLOR chosen_color_enum = colors[chosen_color];
                    // replace card played with the associated wild COLOR card for that wild card...
                    card_played = new ActionCard(chosen_color_enum, action_type);
                }
                if (action_type == SKIP) {
                    // skip past the next player
                    next_player = (turn + (direction * 2)) % n_players;
                }
                else if (action_type == REVERSE) {
                    // reverse direction and change the next player
                    direction *= -1;
                    next_player = (turn + direction) % n_players;
                }
            }

            // display the played card on discard pile
            if (card_played != nullptr) {
                discardpile.put_face_up(card_played);
                handindex = std::min(handindex, hand.size() - 1);
            }

            // construct the turndata object to send over the server from data
            TurnData turndata(cards_drawn, hand.size(), next_player, direction, card_played);
            
            // send it
            serv.send(turndata.to_string());

            // update hand count text
            this->n_cards[0] = hand.size();

            // reset handindex to 0 if drew
            if (handindex < 0) handindex = 0;

            // play uno sound effect!!
            if (hand.size() < 2) {
                uno_sound.play();
            }

            // you won!
            if (hand.size() == 0) {
                mode = WIN;
                return;
            }

            // update local turn variable
            turn = next_player;

        }
        else {
            // wait for someone elses turn

            // display message...
            mode = WAITING_FOR_OTHER_PLAYERS;

            // get other turn data (blocking)
            TurnData turndata(serv.recv());

            // discard top n cards from draw pile because other player drew them
            for (int i = 0; i < turndata.get_cards_drawn(); i++) {
                drawpile.burn_one_card();
            }

            // get the card played
            Card* card = turndata.get_card();

            // show the card on the discard pile if there actually was a card
            if (card != nullptr && card->get_type() != NONE && card->to_string() != "no") {
                discardpile.put_face_up(card);
            }

            // update local variables from turndata
            turn = turndata.get_next_player();
            direction = turndata.get_direction();

            // update card count display
            n_cards[turn] = turndata.get_cards_in_hand();

            // play sound effects or lose
            if (turndata.get_cards_in_hand() == 1) uno_sound.play();
            if (turndata.get_cards_in_hand() == 0) {mode = WIN; return; }
        }
    }
}

// https://stackoverflow.com/questions/26903602/an-enclosing-function-local-variable-cannot-be-referenced-in-a-lambda-body-unles
// https://medium.com/@billchen2k/using-c-conditional-variables-for-thread-synchronization-87fb1ac3601c
void Game::release_select() {
    // unblock waiting thread...
    std::unique_lock<std::mutex> lck(select_mtx);
    select_has_selected = true;
    select_cv.notify_one();
}
void Game::wait_select() {
    // wait for another thread to call release_select()
    std::unique_lock<std::mutex> lck(select_mtx);
    select_cv.wait(lck, [&] {
        return select_has_selected;
        });
    select_has_selected = false;
}