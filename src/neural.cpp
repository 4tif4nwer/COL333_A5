#include <bits/stdc++.h>
#include <vector>
#include <cmath>
#include <iterator>
#include <fstream>
#include <random>
#include "board.hpp"
#include "butils.hpp"
#include "cassert"
#include <iomanip>

int32_t board_evaluate(Board& b){

    // After move evaluation
    int64_t reward = 0;

    auto curr_player = b.data.player_to_play ;

    b.data.player_to_play = BLACK;

    if(b.under_threat(b.data.b_king)){
        reward += 100;
    }
    if(b.under_threat(b.data.b_rook_1)){
        reward += 5;
    }
    if(b.data.b_rook_1 == DEAD){
        reward += 20;
    }
    if(b.under_threat(b.data.b_rook_2)){
        reward += 5;
    }
    if(b.data.b_rook_2 == DEAD){
        reward += 20;
    }
    if(b.under_threat(b.data.b_bishop)){
        reward += 3;
    }
    if(b.data.b_bishop == DEAD){
        reward += 20;
    }

    if(b.data.b_pawn_1 != DEAD){
        reward -= 10;
    }
    else if(b.data.b_pawn_1 & PAWN){
        if(!b.under_threat(b.data.b_pawn_1)){
            reward -= 1;
        }
    }
    else if(b.data.b_pawn_1 & ROOK){
        if(!b.under_threat(b.data.b_pawn_1)){
            reward -= 5;
        }
    }
    else if(b.data.b_pawn_1 & BISHOP){
        if(!b.under_threat(b.data.b_pawn_1)){
            reward -= 3;
        }
    }

    if(b.data.b_pawn_2 != DEAD){
        reward -= 10;
    }
    else
    if(b.data.b_pawn_2 & PAWN){
        if(!b.under_threat(b.data.b_pawn_2)){
            reward -= 1;
        }
    }
    else if(b.data.b_pawn_2 & ROOK){
        if(!b.under_threat(b.data.b_pawn_2)){
            reward -= 5;
        }
    }
    else if(b.data.b_pawn_2 & BISHOP){
        if(!b.under_threat(b.data.b_pawn_2)){
            reward -= 3;
        }
    }

    b.data.player_to_play = WHITE;

    if(b.under_threat(b.data.w_king)){
        reward -= 100;
    }
    if(b.under_threat(b.data.w_rook_1)){
        reward -= 5;
    }
    if(b.data.w_rook_1 == DEAD){
        reward -= 20;
    }
    if(b.under_threat(b.data.w_rook_2)){
        reward -= 5;
    }
    if(b.data.w_rook_2 == DEAD){
        reward -= 20;
    }
    if(b.under_threat(b.data.w_bishop)){
        reward -= 3;
    }
    if(b.data.w_bishop == DEAD){
        reward -= 20;
    }
    
    if(b.data.w_pawn_1 != DEAD){
            reward += 10;
    }
    else if(b.data.w_pawn_1 & PAWN){
        if(!b.under_threat(b.data.w_pawn_1)){
            reward += 1;
        }
    }
    else if(b.data.w_pawn_1 & ROOK){
        if(!b.under_threat(b.data.w_pawn_1)){
            reward += 5;
        }
    }
    else if(b.data.w_pawn_1 & BISHOP){
        if(!b.under_threat(b.data.w_pawn_1)){
            reward += 5;
        }
        
    }

    if(b.data.w_pawn_2 != DEAD){
            reward += 10;
    }
    else if(b.data.w_pawn_2 & PAWN){
        if(!b.under_threat(b.data.w_pawn_2)){
            reward += 1;
        }
    }
    else if(b.data.w_pawn_1 & ROOK){
        if(!b.under_threat(b.data.w_pawn_2)){
            reward += 5;
        }
    }
    else if(b.data.w_pawn_2 & BISHOP){
        if(!b.under_threat(b.data.w_pawn_2)){
            reward += 5;
        }
        
    }

    b.data.player_to_play = curr_player;

    b.flip_player_();
    if(b.get_legal_moves().size() == 0 && b.in_check()){
        reward = 1000;
        b.flip_player_();
        return reward;
    }
    b.flip_player_();
    
    if(b.data.player_to_play == BLACK){
        reward = -reward;
    }

    return reward;
}

class function_approximator{

    public:

    function_approximator(bool pretrained = false){
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<double> dist(-1.0, 1.0);

        weights.resize(40,0);

        if(pretrained){
            read_weights();
            return;
        }

        for(auto &it : weights){
            it = dist(gen);
        }
    }

    double state_evaluation(Board &b){
        
        double value = 0.0;

        auto curr_player = b.data.player_to_play;

        if(curr_player == WHITE){

            value += weights[0] * b.in_check();
            value += weights[1] * under_threat(b,b.data.w_rook_1,curr_player);
            value += weights[2] * under_threat(b,b.data.w_rook_2,curr_player);
            value += weights[3] * under_threat(b,b.data.w_bishop,curr_player);

            if(b.data.w_pawn_1 != DEAD){
                if(b.data.w_pawn_1 & PAWN){
                    value += weights[4] * !(under_threat(b,b.data.w_pawn_1,curr_player));
                    value += weights[5];
                }
                else if(b.data.w_pawn_1 & ROOK){
                    value += weights[6] * !(under_threat(b,b.data.w_pawn_1,curr_player));
                    value += weights[7];
                }
                else if(b.data.w_pawn_1 & BISHOP){
                    value += weights[8] * !(under_threat(b,b.data.w_pawn_1,curr_player));
                    value += weights[9];
                }
            }
            
            if(b.data.w_pawn_2 != DEAD){
                if(b.data.w_pawn_2 & PAWN){
                    value += weights[10] * !(under_threat(b,b.data.w_pawn_2,curr_player));
                    value += weights[11];
                }
                else if(b.data.w_pawn_2 & ROOK){
                    value += weights[12] * !(under_threat(b,b.data.w_pawn_2,curr_player));
                    value += weights[13];
                }
                else if(b.data.w_pawn_2 & BISHOP){
                    value += weights[14] * !(under_threat(b,b.data.w_pawn_2,curr_player));
                    value += weights[15];
                }
            }

            value += weights[16] * is_dead(b.data.w_rook_1);
            value += weights[17] * is_dead(b.data.w_rook_2);
            value += weights[18] * is_dead(b.data.w_bishop);

            value += (double)(weights[38] * int(b.get_legal_moves().size()));

            curr_player = (PlayerColor)(curr_player ^ (WHITE | BLACK));
            b.flip_player_();

            value += weights[19] * b.in_check();
            value += weights[20] * under_threat(b,b.data.b_rook_1,curr_player);
            value += weights[21] * under_threat(b,b.data.b_rook_2,curr_player);
            value += weights[22] * under_threat(b,b.data.b_bishop,curr_player);

            if(b.data.b_pawn_1 != DEAD){
                if(b.data.b_pawn_1 & PAWN){
                    value += weights[23] * !(under_threat(b,b.data.b_pawn_1,curr_player));
                    value += weights[24];
                }
                else if(b.data.b_pawn_1 & ROOK){
                    value += weights[25] * !(under_threat(b,b.data.b_pawn_1,curr_player));
                    value += weights[26];
                }
                else if(b.data.b_pawn_1 & BISHOP){
                    value += weights[27] * !(under_threat(b,b.data.b_pawn_1,curr_player));
                    value += weights[28];
                }
            }

            if(b.data.b_pawn_2 != DEAD){
                if(b.data.b_pawn_2 & PAWN){
                    value += weights[29] * !(under_threat(b,b.data.b_pawn_2,curr_player));
                    value += weights[30];
                }
                else if(b.data.b_pawn_2 & ROOK){
                    value += weights[31] * !(under_threat(b,b.data.b_pawn_2,curr_player));
                    value += weights[32];
                }
                else if(b.data.b_pawn_2 & BISHOP){
                    value += weights[33] * !(under_threat(b,b.data.b_pawn_2,curr_player));
                    value += weights[34];
                }
            }

            value += weights[35] * is_dead(b.data.b_rook_1);
            value += weights[36] * is_dead(b.data.b_rook_2);
            value += weights[37] * is_dead(b.data.b_bishop);

            value += (double)(weights[39] * int(b.get_legal_moves().size()));

            b.flip_player_();
            

        }
        else{
            
            value += weights[0] * b.in_check();
            value += weights[1] * under_threat(b,b.data.b_rook_1,curr_player);
            value += weights[2] * under_threat(b,b.data.b_rook_2,curr_player);
            value += weights[3] * under_threat(b,b.data.b_bishop,curr_player);

            if(b.data.b_pawn_1 != DEAD){
                if(b.data.b_pawn_1 & PAWN){
                    value += weights[4] * !(under_threat(b,b.data.b_pawn_1,curr_player));
                    value += weights[5];
                }
                else if(b.data.b_pawn_1 & ROOK){
                    value += weights[6] * !(under_threat(b,b.data.b_pawn_1,curr_player));
                    value += weights[7];
                }
                else if(b.data.b_pawn_1 & BISHOP){
                    value += weights[8] * !(under_threat(b,b.data.b_pawn_1,curr_player));
                    value += weights[9];
                }
            }

            if(b.data.b_pawn_2 != DEAD){
                if(b.data.b_pawn_2 & PAWN){
                    value += weights[10] * !(under_threat(b,b.data.b_pawn_2,curr_player));
                    value += weights[11];
                }
                else if(b.data.b_pawn_2 & ROOK){
                    value += weights[12] * !(under_threat(b,b.data.b_pawn_2,curr_player));
                    value += weights[13];
                }
                else if(b.data.b_pawn_2 & BISHOP){
                    value += weights[14] * !(under_threat(b,b.data.b_pawn_2,curr_player));
                    value += weights[15];
                }
            }

            value += weights[16] * is_dead(b.data.b_rook_1);
            value += weights[17] * is_dead(b.data.b_rook_2);
            value += weights[18] * is_dead(b.data.b_bishop);

            value += (double)(weights[38] * int(b.get_legal_moves().size()));

            curr_player = (PlayerColor)(curr_player ^ (WHITE | BLACK));
            b.flip_player_();

            value += weights[19] * b.in_check();
            value += weights[20] * under_threat(b,b.data.w_rook_1,curr_player);
            value += weights[21] * under_threat(b,b.data.w_rook_2,curr_player);
            value += weights[22] * under_threat(b,b.data.w_bishop,curr_player);

            if(b.data.w_pawn_1 != DEAD){
                if(b.data.w_pawn_1 & PAWN){
                    value += weights[23] * !(under_threat(b,b.data.w_pawn_1,curr_player));
                    value += weights[24];
                }
                else if(b.data.w_pawn_1 & ROOK){
                    value += weights[25] * !(under_threat(b,b.data.w_pawn_1,curr_player));
                    value += weights[26];
                }
                else if(b.data.w_pawn_1 & BISHOP){
                    value += weights[27] * !(under_threat(b,b.data.w_pawn_1,curr_player));
                    value += weights[28];
                }
            }

            if(b.data.w_pawn_2 != DEAD){
                if(b.data.w_pawn_2 & PAWN){
                    value += weights[29] * !(under_threat(b,b.data.w_pawn_2,curr_player));
                    value += weights[30];
                }
                else if(b.data.w_pawn_2 & ROOK){
                    value += weights[31] * !(under_threat(b,b.data.w_pawn_2,curr_player));
                    value += weights[32];
                }
                else if(b.data.w_pawn_2 & BISHOP){
                    value += weights[33] * !(under_threat(b,b.data.w_pawn_2,curr_player));
                    value += weights[34];
                }
            }

            value += weights[35] * is_dead(b.data.w_rook_1);
            value += weights[36] * is_dead(b.data.w_rook_2);
            value += weights[37] * is_dead(b.data.w_bishop);

            value += (double)(weights[39] * int(b.get_legal_moves().size()));

            b.flip_player_();

            // value += (double)(weights[40] * (b.get_legal_moves().size() == 0 && (!b.in_check())));


        }

        return value;

    }

    void weight_update(Board &b, double target, double learning_rate){
    
        auto curr_player = b.data.player_to_play;

        auto error = target - state_evaluation(b);

        if(curr_player == WHITE){
            
            weights[0] += learning_rate * error * b.in_check();
            weights[1] += learning_rate * error * under_threat(b,b.data.w_rook_1,curr_player);
            weights[2] += learning_rate * error * under_threat(b,b.data.w_rook_2,curr_player);
            weights[3] += learning_rate * error * under_threat(b,b.data.w_bishop,curr_player);

            if(b.data.w_pawn_1 != DEAD){
                if(b.data.w_pawn_1 & PAWN){
                    weights[4] += learning_rate * error * !(under_threat(b,b.data.w_pawn_1,curr_player));
                    weights[5] += learning_rate * error;
                }
                else if(b.data.w_pawn_1 & ROOK){
                    weights[6] += learning_rate * error * !(under_threat(b,b.data.w_pawn_1,curr_player));
                    weights[7] += learning_rate * error;
                }
                else if(b.data.w_pawn_1 & BISHOP){
                    weights[8] += learning_rate * error * !(under_threat(b,b.data.w_pawn_1,curr_player));
                    weights[9] += learning_rate * error;
                }
            }

            if(b.data.w_pawn_2 != DEAD){
                if(b.data.w_pawn_2 & PAWN){
                    weights[10] += learning_rate * error * !(under_threat(b,b.data.w_pawn_2,curr_player));
                    weights[11] += learning_rate * error;
                }
                else if(b.data.w_pawn_2 & ROOK){
                    weights[12] += learning_rate * error * !(under_threat(b,b.data.w_pawn_2,curr_player));
                    weights[13] += learning_rate * error;
                }
                else if(b.data.w_pawn_2 & BISHOP){
                    weights[14] += learning_rate * error * !(under_threat(b,b.data.w_pawn_2,curr_player));
                    weights[15] += learning_rate * error;
                }
            }

            weights[16] += learning_rate * error * is_dead(b.data.w_rook_1);
            weights[17] += learning_rate * error * is_dead(b.data.w_rook_2);
            weights[18] += learning_rate * error * is_dead(b.data.w_bishop);

            weights[38] += learning_rate * (double)(error * int(b.get_legal_moves().size()));

            curr_player = (PlayerColor)(curr_player ^ (WHITE | BLACK));
            b.flip_player_();

            weights[19] += learning_rate * error * b.in_check();
            weights[20] += learning_rate * error * under_threat(b,b.data.b_rook_1,curr_player);
            weights[21] += learning_rate * error * under_threat(b,b.data.b_rook_2,curr_player);
            weights[22] += learning_rate * error * under_threat(b,b.data.b_bishop,curr_player);

            if(b.data.b_pawn_1 != DEAD){
                if(b.data.b_pawn_1 & PAWN){
                    weights[23] += learning_rate * error * !(under_threat(b,b.data.b_pawn_1,curr_player));
                    weights[24] += learning_rate * error;
                }
                else if(b.data.b_pawn_1 & ROOK){
                    weights[25] += learning_rate * error * !(under_threat(b,b.data.b_pawn_1,curr_player));
                    weights[26] += learning_rate * error;
                }
                else if(b.data.b_pawn_1 & BISHOP){
                    weights[27] += learning_rate * error * !(under_threat(b,b.data.b_pawn_1,curr_player));
                    weights[28] += learning_rate * error;
                }
            }

            if(b.data.b_pawn_2 != DEAD){
                if(b.data.b_pawn_2 & PAWN){
                    weights[29] += learning_rate * error * !(under_threat(b,b.data.b_pawn_2,curr_player));
                    weights[30] += learning_rate * error;
                }
                else if(b.data.b_pawn_2 & ROOK){
                    weights[31] += learning_rate * error * !(under_threat(b,b.data.b_pawn_2,curr_player));
                    weights[32] += learning_rate * error;
                }
                else if(b.data.b_pawn_2 & BISHOP){
                    weights[33] += learning_rate * error * !(under_threat(b,b.data.b_pawn_2,curr_player));
                    weights[34] += learning_rate * error;
                }
            }

            weights[35] += learning_rate * error * is_dead(b.data.b_rook_1);
            weights[36] += learning_rate * error * is_dead(b.data.b_rook_2);
            weights[37] += learning_rate * error * is_dead(b.data.b_bishop);

            weights[39] += learning_rate * (double)(error * int(b.get_legal_moves().size()));
            b.flip_player_();

        }
        else{
            
            weights[0] += learning_rate * error * b.in_check();
            weights[1] += learning_rate * error * under_threat(b,b.data.b_rook_1,curr_player);
            weights[2] += learning_rate * error * under_threat(b,b.data.b_rook_2,curr_player);
            weights[3] += learning_rate * error * under_threat(b,b.data.b_bishop,curr_player);

            if(b.data.b_pawn_1 != DEAD){
                if(b.data.b_pawn_1 & PAWN){
                    weights[4] += learning_rate * error * !(under_threat(b,b.data.b_pawn_1,curr_player));
                    weights[5] += learning_rate * error;
                }
                else if(b.data.b_pawn_1 & ROOK){
                    weights[6] += learning_rate * error * !(under_threat(b,b.data.b_pawn_1,curr_player));
                    weights[7] += learning_rate * error;
                }
                else if(b.data.b_pawn_1 & BISHOP){
                    weights[8] += learning_rate * error * !(under_threat(b,b.data.b_pawn_1,curr_player));
                    weights[9] += learning_rate * error;
                }
            }

            if(b.data.b_pawn_2 != DEAD){
                if(b.data.b_pawn_2 & PAWN){
                    weights[10] += learning_rate * error * !(under_threat(b,b.data.b_pawn_2,curr_player));
                    weights[11] += learning_rate * error;
                }
                else if(b.data.b_pawn_2 & ROOK){
                    weights[12] += learning_rate * error * !(under_threat(b,b.data.b_pawn_2,curr_player));
                    weights[13] += learning_rate * error;
                }
                else if(b.data.b_pawn_2 & BISHOP){
                    weights[14] += learning_rate * error * !(under_threat(b,b.data.b_pawn_2,curr_player));
                    weights[15] += learning_rate * error;
                }
            }

            weights[16] += learning_rate * error * is_dead(b.data.b_rook_1);
            weights[17] += learning_rate * error * is_dead(b.data.b_rook_2);
            weights[18] += learning_rate * error * is_dead(b.data.b_bishop);

            weights[38] += learning_rate * (double)(error * int(b.get_legal_moves().size()));

            curr_player = (PlayerColor)(curr_player ^ (WHITE | BLACK));
            b.flip_player_();

            weights[19] += learning_rate * error * b.in_check();
            weights[20] += learning_rate * error * under_threat(b,b.data.w_rook_1,curr_player);
            weights[21] += learning_rate * error * under_threat(b,b.data.w_rook_2,curr_player);
            weights[22] += learning_rate * error * under_threat(b,b.data.w_bishop,curr_player);

            if(b.data.w_pawn_1 != DEAD){
                if(b.data.w_pawn_1 & PAWN){
                    weights[23] += learning_rate * error * !(under_threat(b,b.data.w_pawn_1,curr_player));
                    weights[24] += learning_rate * error;
                }
                else if(b.data.w_pawn_1 & ROOK){
                    weights[25] += learning_rate * error * !(under_threat(b,b.data.w_pawn_1,curr_player));
                    weights[26] += learning_rate * error;
                }
                else if(b.data.w_pawn_1 & BISHOP){
                    weights[27] += learning_rate * error * !(under_threat(b,b.data.w_pawn_1,curr_player));
                    weights[28] += learning_rate * error;
                }
            }

            if(b.data.w_pawn_2 != DEAD){
                if(b.data.w_pawn_2 & PAWN){
                    weights[29] += learning_rate * error * !(under_threat(b,b.data.w_pawn_2,curr_player));
                    weights[30] += learning_rate * error;
                }
                else if(b.data.w_pawn_2 & ROOK){
                    weights[31] += learning_rate * error * !(under_threat(b,b.data.w_pawn_2,curr_player));
                    weights[32] += learning_rate * error;
                }
                else if(b.data.w_pawn_2 & BISHOP){
                    weights[33] += learning_rate * error * !(under_threat(b,b.data.w_pawn_2,curr_player));
                    weights[34] += learning_rate * error;
                }
            }

            weights[35] += learning_rate * error * is_dead(b.data.w_rook_1);
            weights[36] += learning_rate * error * is_dead(b.data.w_rook_2);
            weights[37] += learning_rate * error * is_dead(b.data.w_bishop);

            weights[39] += learning_rate * (double)(error * int(b.get_legal_moves().size()));

            b.flip_player_();
        }
        write_weights();
    }

    private:

    std::vector<double> weights;

    // features

    bool under_threat(Board &b, U8 piece, PlayerColor player){
        auto curr_player = b.data.player_to_play;

        b.data.player_to_play = player;

        if(b.under_threat(piece)){
            b.data.player_to_play = curr_player;
            return true;
        }

        b.data.player_to_play = curr_player;

        return false;

    }

    bool is_dead(U8 piece){
        if(piece == DEAD){
            return true;
        }
        return false;
    }

    void write_weights(){
        std::ofstream output_file("src/weights.txt");

        output_file<< std::hexfloat;

        for(auto &it : weights){
            output_file<<it<<"\n";
        }

        output_file.close();
    }

    void read_weights(){
        std::ifstream input_file("src/weights.txt");
        std::string line;

        for(auto &it : weights){
            std::getline(input_file,line);
            it = std::stod(line);
        }

        input_file.close();
    }

};


class QLearningAgent {
public:
    QLearningAgent(bool pretrained = false)
        : fn(pretrained) {
            learningRate = 0.001;
            discountFactor = 0.8;
            trainstep = 1;

    }

    double state_evaluation(Board& b, U16 move){ // Q(s,a)

        b.do_move_without_flip_(move);
        double score = fn.state_evaluation(b);
        b.undo_last_move_without_flip_(move);
        return score;
    }

    // Q-learning update
    void qLearningUpdate(Board& state, U16 move, bool isdraw = false) {
        auto curr_score = board_evaluate(state);
        state.do_move_without_flip_(move);
        auto last_killed = state.data.last_killed_piece;
        auto last_killed_idx = state.data.last_killed_piece_idx;
        auto next_score = board_evaluate(state);

        double reward = double(next_score - curr_score);
        double next_q_val = DBL_MIN;
        if(isdraw){
            reward = 0;
            next_q_val = 0;
        }
        else{
            state.flip_player_();

            auto moveset = state.get_legal_moves();

            if(moveset.size() == 0)
                next_q_val = 0;

            for(auto &it : moveset){
                next_q_val = std::max(next_q_val,state_evaluation(state,it));
            }
            state.flip_player_();

        }

        fn.weight_update(state,reward - discountFactor * next_q_val,learningRate/((double)trainstep));
        trainstep += 1;
        state.data.last_killed_piece = last_killed;
        state.data.last_killed_piece_idx = last_killed_idx;
        state.undo_last_move_without_flip_(move);
        
    }

private:
    function_approximator fn;
    double trainstep;
    double learningRate;
    double discountFactor;
};
