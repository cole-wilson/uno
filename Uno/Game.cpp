#include "Game.h"

Game::Game() : drawpile("B0,B1,B1,B2,B2,B3,B3,B4,B4,B5,B5,B6,B6,B7,B7,B8,B8,B9,B9,Bs,Bs,Br,Br,Bd,Bd,G0,G1,G1,G2,G2,G3,G3,G4,G4,G5,G5,G6,G6,G7,G7,G8,G8,G9,G9,Gs,Gs,Gr,Gr,Gd,Gd,R0,R1,R1,R2,R2,R3,R3,R4,R4,R5,R5,R6,R6,R7,R7,R8,R8,R9,R9,Rs,Rs,Rr,Rr,Rd,Rd,Y0,Y1,Y1,Y2,Y2,Y3,Y3,Y4,Y4,Y5,Y5,Y6,Y6,Y7,Y7,Y8,Y8,Y9,Y9,Ys,Ys,Yr,Yr,Yd,Yd,Ww,Ww,Ww,Ww,Wf,Wf,Wf,Wf") {
}

void Game::mainloop() {
    while (true) {
        Card* tomatch = discardpile.read_face_up();

        if (turn < 0) turn += n_players;

        std::cout << "turn: " << turn << "\tdirection: " << direction << std::endl;
        std::cout << "TO MATCH: " << tomatch->to_string() << std::endl;

        if (turn == serv.get_player_id()) {
            // do my turn
            int cards_drawn = 0;
            Card* card_played = nullptr;
            int next_player;

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
                for (int i = 0; i < cards_drawn; i++) {
                    hand.put_face_up(drawpile.draw_one_card());
                }
            }
            std::cout << "HAND: " << hand.to_string() << std::endl;
            //std::cout << "\tchoose index to play: ";

            mode = SELECTING_CARD;
            wait_select();

            card_played = hand.draw_one_card(handindex);
            next_player = (turn + direction) % n_players;

            if (card_played->get_type() == ACTION) {
                CARD_ACTION action_type = dynamic_cast<ActionCard*>(card_played)->get_action();
                if (card_played->get_color() == WILD_CARD) {
                    std::cout << "\tchoose wild card color: ";
                    mode = SELECTING_WILD_COLOR;
                    wait_select();
                    CARD_COLOR colors[] = { RED, GREEN, BLUE, YELLOW };
                    CARD_COLOR chosen_color_enum = colors[chosen_color];
                    card_played = new ActionCard(chosen_color_enum, action_type);
                }
                if (action_type == SKIP) {
                    next_player = (turn + (direction * 2)) % n_players;
                }
                else if (action_type == REVERSE) {
                    direction *= -1;
                    next_player = (turn + direction) % n_players;
                }
            }

            discardpile.put_face_up(card_played);

            TurnData turndata(cards_drawn, hand.size(), next_player, direction, card_played);
            serv.send(turndata.to_string());

            turn = next_player;

        }
        else {
            // wait for someone elses turn
            mode = WAITING_FOR_OTHER_PLAYER;
            bool win = false;
            TurnData turndata(serv.recv());

            for (int i = 0; i < turndata.get_cards_drawn(); i++) {
                drawpile.burn_one_card();
            }

            Card* card = turndata.get_card();
            if (card != nullptr) {
                //std::cout << "player " << turn << " played " << card->to_string() << std::endl;
                discardpile.put_face_up(card);
            }
            else {
                //std::cout << "player " << turn << " didn't play a card" << std::endl;
            }

            //std::cout << "player " << turn << " has " << turndata.get_cards_in_hand() << " cards" << std::endl;

            turn = turndata.get_next_player();
            direction = turndata.get_direction();

            if (turndata.get_cards_in_hand() == 0) return;
        }
        std::cout << std::endl << std::endl << std::endl;
    }
}

// https://stackoverflow.com/questions/26903602/an-enclosing-function-local-variable-cannot-be-referenced-in-a-lambda-body-unles
// https://medium.com/@billchen2k/using-c-conditional-variables-for-thread-synchronization-87fb1ac3601c
void Game::release_select() {
    std::unique_lock<std::mutex> lck(select_mtx);
    select_has_selected = true;
    select_cv.notify_one();
}
void Game::wait_select() {
    std::cout << "waiting..." << std::endl;
    std::unique_lock<std::mutex> lck(select_mtx);
    select_cv.wait(lck, [&] {
        return select_has_selected;
        });
    select_has_selected = false;
}
