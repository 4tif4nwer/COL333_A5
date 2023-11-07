#include <algorithm>
#include <random>
#include <iostream>
#include <thread>
#include<bits/stdc++.h>
#include "board.hpp"
#include "engine.hpp"
#include "butils.hpp"
#include "neural.cpp"

void Engine::find_best_move(const Board& b) {

    // pick a random move
    
    auto moveset = b.get_legal_moves();
    if (moveset.size() == 0) {
        std::cout << "Could not get any moves from board!\n";
        std::cout << board_to_str(&b.data);
        this->best_move = 0;
    }
    else {
        std::vector<U16> moves;
        QLearningAgent Qlearn(36);
        std::cout << show_moves(&b.data, moveset) << std::endl;
        for (auto m : moveset) {
            std::cout << move_to_str(m) << " ";
        }
        std::cout << std::endl;
        std::sample(
            moveset.begin(),
            moveset.end(),
            std::back_inserter(moves),
            1,
            std::mt19937{std::random_device{}()}
        );
        auto move = moves[0];
        Board searchboard = Board(b.data);
        double q_val = INT_MIN;
        for(auto &it : moveset){
            auto eval = Qlearn.state_evaluation(searchboard,it) ;
            // auto board_now = all_boards_to_str(b);
            // assert(board_now == initial_board);
            if(q_val < eval){
                move = it;
                q_val = eval;
            }
        }
        this->best_move = move;
        // std::cout<<"here\n";
    }

    // just for debugging, to slow down the moves
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
}
