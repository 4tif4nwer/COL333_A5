#include <algorithm>
#include <random>
#include <iostream>
#include <thread>
#include<bits/stdc++.h>
#include "board.hpp"
#include "engine.hpp"
#include "butils.hpp"
#include "neural.cpp"
QLearningAgent Qlearn(true);
std::map<std::string,int> board_count;

int16_t maxDepth=3;


std::pair<double,U16> minimax(Board &b,int16_t depth,
            bool maximizingPlayer, double alpha, double beta,
            std::pair<U8,int> last_killed_data)
{


    auto moves = b.get_legal_moves();

    if (depth == maxDepth) {
        double eval = -DBL_MAX;
        U16 move = 0;
        for(auto &it : moves){
            auto value = Qlearn.state_evaluation(b,it,board_count);
            b.data.last_killed_piece = last_killed_data.first;
            b.data.last_killed_piece_idx = last_killed_data.second;
            if(value > eval){
                eval = value;
                move = it;
            }
        }
        if(depth % 2 == 0){
            eval = -eval;
        }
        return std::make_pair(eval, move);
    }

    if(moves.size() == 0 && !b.in_check()){ 
        return std::make_pair(0, 0);
    }
 

    if (maximizingPlayer)
    {
        std::pair<double, U16>  best = {-DBL_MAX, 0};
 
        // Recur for left and
        // right children
        for (auto m : moves) {
            b.do_move_(m);
            std::pair<double, U16> val;
            board_count[board_encode(b)]++;
            val = minimax(b, depth + 1,
                    false,alpha,beta,std::make_pair(b.data.last_killed_piece, b.data.last_killed_piece_idx));
            board_count[board_encode(b)]--;
            b.flip_player_();
            b.undo_last_move_without_flip_(m);
            b.data.last_killed_piece = last_killed_data.first;
            b.data.last_killed_piece_idx = last_killed_data.second;
            
            if(val.first >= best.first) {
                best.first = val.first;
                best.second = m;
            }

            alpha = std::max(alpha, best.first);

            // Alpha Beta Pruning
            if (beta <= alpha)
                break;
        }
        
        return best;
    }
    else
    {
        std::pair<double, U16>  best = {DBL_MAX, 0};

        for (auto m : moves) {
            b.do_move_(m);
            std::pair<double, U16> val;
            board_count[board_encode(b)]++;
            val = minimax(b, depth + 1,
                    true,alpha,beta, std::make_pair(b.data.last_killed_piece, b.data.last_killed_piece_idx));
            board_count[board_encode(b)]--;

            b.flip_player_();
            b.undo_last_move_without_flip_(m);

            b.data.last_killed_piece = last_killed_data.first;
            b.data.last_killed_piece_idx = last_killed_data.second;
            

            if(best.first >= val.first) {
                best.first = val.first;
                best.second = m;
            }

            beta = std::min(beta, best.first);

            // Alpha Beta Pruning
            if (beta <= alpha)
                break;
        }
        return best;
    }
    
}

void Engine::find_best_move(const Board& b) {

    // pick a random move
    auto moveset = b.get_legal_moves();
    if (moveset.size() == 0) {
        this->best_move = 0;
    }
    else {
        Board search_board(b.data);
        board_count[board_encode(search_board)]++;
        std::vector<U16> moves;

        std::cout << std::endl;
        std::sample(
            moveset.begin(),
            moveset.end(),
            std::back_inserter(moves),
            1,
            std::mt19937{std::random_device{}()}
        );

        this->best_move = moves[0];

        // store time
        auto search_result = minimax(search_board, 1, true,DBL_MIN,DBL_MAX, std::make_pair(b.data.last_killed_piece, b.data.last_killed_piece_idx));
        
        if(board_encode(search_board) != board_encode(b)){
            std::cout<<board_to_str(&b.data)<<std::endl;
            std::cout<<board_to_str(&search_board.data)<<std::endl;
        }

        assert(board_encode(search_board) == board_encode(b));

        this->best_move = search_result.second;

        if(this->best_move != 0){
            search_board.do_move_(this->best_move);
            
            board_count[board_encode(search_board)]++;
        }
    }
    // std::this_thread::sleep_for(std::chrono::milliseconds(500));
    return;
}
