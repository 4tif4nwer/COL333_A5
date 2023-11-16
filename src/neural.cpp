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

std::string board_encode(const Board& b){
    std::string perspective = "";
    perspective += std::to_string(getx(b.data.w_king));
    perspective += std::to_string(gety(b.data.w_king));
    perspective += std::to_string(getx(b.data.w_rook_1));
    perspective += std::to_string(gety(b.data.w_rook_1));
    perspective += std::to_string(getx(b.data.w_rook_2));
    perspective += std::to_string(gety(b.data.w_rook_2));
    perspective += std::to_string(getx(b.data.w_bishop));
    perspective += std::to_string(gety(b.data.w_bishop));
    perspective += std::to_string(getx(b.data.w_knight_1));
    perspective += std::to_string(gety(b.data.w_knight_1));
    perspective += std::to_string(getx(b.data.w_knight_2));
    perspective += std::to_string(gety(b.data.w_knight_2));
    perspective += std::to_string(getx(b.data.w_pawn_1));
    perspective += std::to_string(gety(b.data.w_pawn_1));
    perspective += std::to_string(getx(b.data.w_pawn_2));
    perspective += std::to_string(gety(b.data.w_pawn_2));
    perspective += std::to_string(getx(b.data.w_pawn_3));
    perspective += std::to_string(gety(b.data.w_pawn_3));
    perspective += std::to_string(getx(b.data.w_pawn_4));
    perspective += std::to_string(gety(b.data.w_pawn_4));
    

    perspective += piece_to_char(b.data.w_pawn_1);
    perspective += piece_to_char(b.data.w_pawn_2);
    perspective += piece_to_char(b.data.w_pawn_3);
    perspective += piece_to_char(b.data.w_pawn_4);

    perspective += std::to_string(getx(b.data.b_king));
    perspective += std::to_string(gety(b.data.b_king));
    perspective += std::to_string(getx(b.data.b_rook_1));
    perspective += std::to_string(gety(b.data.b_rook_1));
    perspective += std::to_string(getx(b.data.b_rook_2));
    perspective += std::to_string(gety(b.data.b_rook_2));
    perspective += std::to_string(getx(b.data.b_bishop));
    perspective += std::to_string(gety(b.data.b_bishop));
    perspective += std::to_string(getx(b.data.b_knight_1));
    perspective += std::to_string(gety(b.data.b_knight_1));
    perspective += std::to_string(getx(b.data.b_knight_2));
    perspective += std::to_string(gety(b.data.b_knight_2));
    perspective += std::to_string(getx(b.data.b_pawn_1));
    perspective += std::to_string(gety(b.data.b_pawn_1));
    perspective += std::to_string(getx(b.data.b_pawn_2));
    perspective += std::to_string(gety(b.data.b_pawn_2));
    perspective += std::to_string(getx(b.data.b_pawn_3));
    perspective += std::to_string(gety(b.data.b_pawn_3));
    perspective += std::to_string(getx(b.data.b_pawn_4));
    perspective += std::to_string(gety(b.data.b_pawn_4));

    perspective += piece_to_char(b.data.b_pawn_1);
    perspective += piece_to_char(b.data.b_pawn_2);
    perspective += piece_to_char(b.data.b_pawn_3);
    perspective += piece_to_char(b.data.b_pawn_4);
    
    return perspective;
}

int32_t board_evaluate(Board& b){

    // After move evaluation
    int64_t reward = 0;

    // auto curr_player = b.data.player_to_play ;

    // b.data.player_to_play = BLACK;

    // if(b.under_threat(b.data.b_king)){
    //     reward += 100;
    // }
    // if(b.under_threat(b.data.b_rook_1)){
    //     reward += 5;
    // }
    // if(b.data.b_rook_1 == DEAD){
    //     reward += 20;
    // }
    // if(b.under_threat(b.data.b_rook_2)){
    //     reward += 5;
    // }
    // if(b.data.b_rook_2 == DEAD){
    //     reward += 20;
    // }
    // if(b.under_threat(b.data.b_bishop)){
    //     reward += 3;
    // }
    // if(b.data.b_bishop == DEAD){
    //     reward += 20;
    // }

    // if(b.data.b_pawn_1 == DEAD){
    //     reward += 10;
    // }
    // else if(b.data.b_pawn_1 & PAWN){
    //     if(!b.under_threat(b.data.b_pawn_1)){
    //         reward -= 1;
    //     }
    // }
    // else if(b.data.b_pawn_1 & ROOK){
    //     if(!b.under_threat(b.data.b_pawn_1)){
    //         reward -= 5;
    //     }
    // }
    // else if(b.data.b_pawn_1 & BISHOP){
    //     if(!b.under_threat(b.data.b_pawn_1)){
    //         reward -= 3;
    //     }
    // }

    // if(b.data.b_pawn_2 == DEAD){
    //     reward += 10;
    // }
    // else if(b.data.b_pawn_2 & PAWN){
    //     if(!b.under_threat(b.data.b_pawn_2)){
    //         reward -= 1;
    //     }
    // }
    // else if(b.data.b_pawn_2 & ROOK){
    //     if(!b.under_threat(b.data.b_pawn_2)){
    //         reward -= 5;
    //     }
    // }
    // else if(b.data.b_pawn_2 & BISHOP){
    //     if(!b.under_threat(b.data.b_pawn_2)){
    //         reward -= 3;
    //     }
    // }

    // b.data.player_to_play = WHITE;

    // if(b.under_threat(b.data.w_king)){
    //     reward -= 100;
    // }
    // if(b.under_threat(b.data.w_rook_1)){
    //     reward -= 5;
    // }
    // if(b.data.w_rook_1 == DEAD){
    //     reward -= 20;
    // }
    // if(b.under_threat(b.data.w_rook_2)){
    //     reward -= 5;
    // }
    // if(b.data.w_rook_2 == DEAD){
    //     reward -= 20;
    // }
    // if(b.under_threat(b.data.w_bishop)){
    //     reward -= 3;
    // }
    // if(b.data.w_bishop == DEAD){
    //     reward -= 20;
    // }
    
    // if(b.data.w_pawn_1 == DEAD){
    //         reward -= 10;
    // }
    // else if(b.data.w_pawn_1 & PAWN){
    //     if(!b.under_threat(b.data.w_pawn_1)){
    //         reward += 1;
    //     }
    // }
    // else if(b.data.w_pawn_1 & ROOK){
    //     if(!b.under_threat(b.data.w_pawn_1)){
    //         reward += 5;
    //     }
    // }
    // else if(b.data.w_pawn_1 & BISHOP){
    //     if(!b.under_threat(b.data.w_pawn_1)){
    //         reward += 5;
    //     }
        
    // }

    // if(b.data.w_pawn_2 == DEAD){
    //         reward -= 10;
    // }
    // else if(b.data.w_pawn_2 & PAWN){
    //     if(!b.under_threat(b.data.w_pawn_2)){
    //         reward += 1;
    //     }
    // }
    // else if(b.data.w_pawn_1 & ROOK){
    //     if(!b.under_threat(b.data.w_pawn_2)){
    //         reward += 5;
    //     }
    // }
    // else if(b.data.w_pawn_2 & BISHOP){
    //     if(!b.under_threat(b.data.w_pawn_2)){
    //         reward += 5;
    //     }
        
    // }

    // b.data.player_to_play = curr_player;

    b.flip_player_();
    if(b.get_legal_moves().size() == 0 && b.in_check()){
        reward = 1000;
        b.flip_player_();
        return reward;
    }
    b.flip_player_();
    
    // if(b.data.player_to_play == BLACK){
    //     reward = -reward;
    // }
    // return reward;
    return 0;
}

class function_approximator{

    public:

    std::unordered_set<U16> pseudolegal_moves;

    function_approximator(bool pretrained = false, BoardType board_type = SEVEN_THREE){
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<double> dist(-1.0, 1.0);

        if(board_type == SEVEN_THREE){
            weights.resize(42,0);
        }
        else if(board_type == EIGHT_FOUR){
            //something
            weights.resize(66,0);
        }        
        else{
            //something
            weights.resize(74,0);

        }

        bias.resize(1,0);

        if(pretrained){
            read_weights();
            return;
        }

        for(auto &it : weights){
            it = dist(gen);
        }

        bias[0] = dist(gen);
    }


    double state_evaluation_8_2(Board &b, int state_count = 0){
        
        double value = weights[41] * state_count;

        value += bias[0];

        auto curr_player = b.data.player_to_play;

        if(curr_player == WHITE){

            pseudolegal_moves = b.get_pseudolegal_moves_for_side(b.data.player_to_play ^ (WHITE | BLACK));

            value += weights[0] * b.in_check();
            value += weights[1] * under_threat(b,b.data.w_rook_1,curr_player);
            value += weights[2] * under_threat(b,b.data.w_rook_2,curr_player);
            value += weights[3] * under_threat(b,b.data.w_bishop,curr_player);
            value += weights[66] * under_threat(b,b.data.b_knight_1,curr_player);
            value += weights[67] * under_threat(b,b.data.b_knight_2,curr_player);

            if(b.data.w_pawn_1 != DEAD){
                if(b.data.w_pawn_1 & PAWN){
                    value += weights[4] * !(under_threat(b,b.data.w_pawn_1,curr_player));
                    value += weights[5];
                    value += (double)(-0.00001 * (manhattan_distance(getx(b.data.w_pawn_1),gety(b.data.w_pawn_1),4,5) + manhattan_distance(getx(b.data.w_pawn_1),gety(b.data.w_pawn_1),4,6)));
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
                    value += (double)(-0.00001 * (manhattan_distance(getx(b.data.w_pawn_2),gety(b.data.w_pawn_2),4,5) + manhattan_distance(getx(b.data.w_pawn_2),gety(b.data.w_pawn_2),4,6)));
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

            if(b.data.w_pawn_3 != DEAD){
                if(b.data.w_pawn_3 & PAWN){
                    value += weights[42] * !(under_threat(b,b.data.w_pawn_3,curr_player));
                    value += weights[43];
                    value += (double)(-0.00001 * (manhattan_distance(getx(b.data.w_pawn_3),gety(b.data.w_pawn_3),5,6) + manhattan_distance(getx(b.data.w_pawn_3),gety(b.data.w_pawn_3),5,7)));
                }
                else if(b.data.w_pawn_3 & ROOK){
                    value += weights[44] * !(under_threat(b,b.data.w_pawn_3,curr_player));
                    value += weights[45];
                }
                else if(b.data.w_pawn_3 & BISHOP){
                    value += weights[46] * !(under_threat(b,b.data.w_pawn_3,curr_player));
                    value += weights[47];
                }
            }

            if(b.data.w_pawn_4 != DEAD){
                if(b.data.w_pawn_4 & PAWN){
                    value += weights[54] * !(under_threat(b,b.data.w_pawn_4,curr_player));
                    value += weights[55];
                    value += (double)(-0.00001 * (manhattan_distance(getx(b.data.w_pawn_4),gety(b.data.w_pawn_4),5,6) + manhattan_distance(getx(b.data.w_pawn_4),gety(b.data.w_pawn_4),5,7)));
                }
                else if(b.data.w_pawn_4 & ROOK){
                    value += weights[56] * !(under_threat(b,b.data.w_pawn_4,curr_player));
                    value += weights[57];
                }
                else if(b.data.w_pawn_4 & BISHOP){
                    value += weights[58] * !(under_threat(b,b.data.w_pawn_4,curr_player));
                    value += weights[59];
                }
            }

            if(is_dead(b.data.w_rook_1)){
                value += weights[16];
            }
            if(is_dead(b.data.w_rook_2)){
                value += weights[17];
            }
            if(is_dead(b.data.w_bishop)){
                value += weights[18];
            }
            if(is_dead(b.data.b_knight_1)){
                value += weights[68];
            }
            if(is_dead(b.data.b_knight_2)){
                value += weights[69];
            }

            value += (double)(weights[38] * int(b.get_legal_moves().size()));

            curr_player = (PlayerColor)(curr_player ^ (WHITE | BLACK));
            b.flip_player_();

            pseudolegal_moves = b.get_pseudolegal_moves_for_side(b.data.player_to_play ^ (WHITE | BLACK));

            value += weights[19] * b.in_check();
            value += weights[20] * under_threat(b,b.data.b_rook_1,curr_player);
            value += weights[21] * under_threat(b,b.data.b_rook_2,curr_player);
            value += weights[22] * under_threat(b,b.data.b_bishop,curr_player);
            value += weights[70] * under_threat(b,b.data.w_knight_1,curr_player);
            value += weights[71] * under_threat(b,b.data.w_knight_2,curr_player);

            if(b.data.b_pawn_1 != DEAD){
                if(b.data.b_pawn_1 & PAWN){
                    value += weights[23] * !(under_threat(b,b.data.b_pawn_1,curr_player));
                    value += weights[24];
                    value += (double)(0.00001 * (manhattan_distance(getx(b.data.b_pawn_1),gety(b.data.b_pawn_1),2,1) + manhattan_distance(getx(b.data.b_pawn_1),gety(b.data.b_pawn_1),2,0)));
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
                    value += (double)(0.00001 * (manhattan_distance(getx(b.data.b_pawn_2),gety(b.data.b_pawn_2),2,1) + manhattan_distance(getx(b.data.b_pawn_2),gety(b.data.b_pawn_2),2,0)));
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

            if(b.data.b_pawn_3 != DEAD){
                if(b.data.b_pawn_3 & PAWN){
                    value += weights[48] * !(under_threat(b,b.data.b_pawn_3,curr_player));
                    value += weights[49];
                    value += (double)(0.00001 * (manhattan_distance(getx(b.data.b_pawn_3),gety(b.data.b_pawn_3),2,1) + manhattan_distance(getx(b.data.b_pawn_3),gety(b.data.b_pawn_3),2,0)));
                }
                else if(b.data.b_pawn_3 & ROOK){
                    value += weights[50] * !(under_threat(b,b.data.b_pawn_3,curr_player));
                    value += weights[51];
                }
                else if(b.data.b_pawn_3 & BISHOP){
                    value += weights[52] * !(under_threat(b,b.data.b_pawn_3,curr_player));
                    value += weights[53];
                }
            }

            if(b.data.b_pawn_4 != DEAD){
                if(b.data.b_pawn_4 & PAWN){
                    value += weights[60] * !(under_threat(b,b.data.b_pawn_4,curr_player));
                    value += weights[61];
                    value += (double)(0.00001 * (manhattan_distance(getx(b.data.b_pawn_4),gety(b.data.b_pawn_4),2,1) + manhattan_distance(getx(b.data.b_pawn_4),gety(b.data.b_pawn_4),2,0)));
                }
                else if(b.data.b_pawn_4 & ROOK){
                    value += weights[62] * !(under_threat(b,b.data.b_pawn_4,curr_player));
                    value += weights[63];
                }
                else if(b.data.b_pawn_4 & BISHOP){
                    value += weights[64] * !(under_threat(b,b.data.b_pawn_4,curr_player));
                    value += weights[65];
                }
            }

            if(is_dead(b.data.b_rook_1)){
                value += weights[35];
            }
            if(is_dead(b.data.b_rook_2)){
                value += weights[36];
            }
            if(is_dead(b.data.b_bishop)){
                value += weights[37];
            }
            if(is_dead(b.data.w_knight_1)){
                value += weights[72];
            }
            if(is_dead(b.data.w_knight_2)){
                value += weights[73];
            }

            value += (double)(weights[39] * int(b.get_legal_moves().size()));

            value += (double)(weights[40] * ((b.get_legal_moves().size() == 0) && (!b.in_check())));

            b.flip_player_();
            

        }
        else{

            pseudolegal_moves = b.get_pseudolegal_moves_for_side(b.data.player_to_play ^ (WHITE | BLACK));
            
            value += weights[0] * b.in_check();
            value += weights[1] * under_threat(b,b.data.b_rook_1,curr_player);
            value += weights[2] * under_threat(b,b.data.b_rook_2,curr_player);
            value += weights[3] * under_threat(b,b.data.b_bishop,curr_player);
            value += weights[66] * under_threat(b,b.data.w_knight_1,curr_player);
            value += weights[67] * under_threat(b,b.data.w_knight_2,curr_player);

            if(b.data.b_pawn_1 != DEAD){
                if(b.data.b_pawn_1 & PAWN){
                    value += weights[4] * !(under_threat(b,b.data.b_pawn_1,curr_player));
                    value += weights[5];
                    value += (double)(-0.00001 * (manhattan_distance(getx(b.data.b_pawn_1),gety(b.data.b_pawn_1),2,1) + manhattan_distance(getx(b.data.b_pawn_1),gety(b.data.b_pawn_1),2,0)));
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
                    value += (double)(-0.00001 * (manhattan_distance(getx(b.data.b_pawn_2),gety(b.data.b_pawn_2),2,1) + manhattan_distance(getx(b.data.b_pawn_2),gety(b.data.b_pawn_2),2,0)));
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

            if(b.data.b_pawn_3 != DEAD){
                if(b.data.b_pawn_3 & PAWN){
                    value += weights[42] * !(under_threat(b,b.data.b_pawn_3,curr_player));
                    value += weights[43];
                    value += (double)(-0.00001 * (manhattan_distance(getx(b.data.b_pawn_3),gety(b.data.b_pawn_3),2,1) + manhattan_distance(getx(b.data.b_pawn_3),gety(b.data.b_pawn_3),2,0)));
                }
                else if(b.data.b_pawn_3 & ROOK){
                    value += weights[44] * !(under_threat(b,b.data.b_pawn_3,curr_player));
                    value += weights[45];
                }
                else if(b.data.b_pawn_3 & BISHOP){
                    value += weights[46] * !(under_threat(b,b.data.b_pawn_3,curr_player));
                    value += weights[47];
                }
            }

            if(b.data.b_pawn_4 != DEAD){
                if(b.data.b_pawn_4 & PAWN){
                    value += weights[54] * !(under_threat(b,b.data.b_pawn_4,curr_player));
                    value += weights[55];
                    value += (double)(-0.00001 * (manhattan_distance(getx(b.data.b_pawn_4),gety(b.data.b_pawn_4),2,1) + manhattan_distance(getx(b.data.b_pawn_4),gety(b.data.b_pawn_4),2,0)));
                }
                else if(b.data.b_pawn_4 & ROOK){
                    value += weights[56] * !(under_threat(b,b.data.b_pawn_4,curr_player));
                    value += weights[57];
                }
                else if(b.data.b_pawn_4 & BISHOP){
                    value += weights[58] * !(under_threat(b,b.data.b_pawn_4,curr_player));
                    value += weights[59];
                }
            }

            if(is_dead(b.data.b_rook_1)){
                value += weights[16];
            }
            if(is_dead(b.data.b_rook_2)){
                value += weights[17];
            }
            if(is_dead(b.data.b_bishop)){
                value += weights[18];
            }
            if(is_dead(b.data.w_knight_1)){
                value += weights[68];
            }
            if(is_dead(b.data.w_knight_2)){
                value += weights[69];
            }

            value += (double)(weights[38] * int(b.get_legal_moves().size()));

            curr_player = (PlayerColor)(curr_player ^ (WHITE | BLACK));
            b.flip_player_();

            pseudolegal_moves = b.get_pseudolegal_moves_for_side(b.data.player_to_play ^ (WHITE | BLACK));

            value += weights[19] * b.in_check();
            value += weights[20] * under_threat(b,b.data.w_rook_1,curr_player);
            value += weights[21] * under_threat(b,b.data.w_rook_2,curr_player);
            value += weights[22] * under_threat(b,b.data.w_bishop,curr_player);
            value += weights[70] * under_threat(b,b.data.b_knight_1,curr_player);
            value += weights[71] * under_threat(b,b.data.b_knight_2,curr_player);

            if(b.data.w_pawn_1 != DEAD){
                if(b.data.w_pawn_1 & PAWN){
                    value += weights[23] * !(under_threat(b,b.data.w_pawn_1,curr_player));
                    value += weights[24];
                    value += (double)(0.00001 * (manhattan_distance(getx(b.data.w_pawn_1),gety(b.data.w_pawn_1),4,5) + manhattan_distance(getx(b.data.w_pawn_1),gety(b.data.w_pawn_1),4,6)));
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
                    value += (double)(0.00001 * (manhattan_distance(getx(b.data.w_pawn_2),gety(b.data.w_pawn_2),4,5) + manhattan_distance(getx(b.data.w_pawn_2),gety(b.data.w_pawn_2),4,6)));
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

            if(b.data.w_pawn_3 != DEAD){
                if(b.data.w_pawn_3 & PAWN){
                    value += weights[48] * !(under_threat(b,b.data.w_pawn_3,curr_player));
                    value += weights[49];
                    value += (double)(0.00001 * (manhattan_distance(getx(b.data.w_pawn_3),gety(b.data.w_pawn_3),5,6) + manhattan_distance(getx(b.data.w_pawn_3),gety(b.data.w_pawn_3),5,7)));
                }
                else if(b.data.w_pawn_3 & ROOK){
                    value += weights[50] * !(under_threat(b,b.data.w_pawn_3,curr_player));
                    value += weights[51];
                }
                else if(b.data.w_pawn_3 & BISHOP){
                    value += weights[52] * !(under_threat(b,b.data.w_pawn_3,curr_player));
                    value += weights[53];
                }
            }

            if(b.data.w_pawn_4 != DEAD){
                if(b.data.w_pawn_4 & PAWN){
                    value += weights[60] * !(under_threat(b,b.data.w_pawn_4,curr_player));
                    value += weights[61];
                    value += (double)(0.00001 * (manhattan_distance(getx(b.data.w_pawn_4),gety(b.data.w_pawn_4),5,6) + manhattan_distance(getx(b.data.w_pawn_4),gety(b.data.w_pawn_4),5,7)));
                }
                else if(b.data.w_pawn_4 & ROOK){
                    value += weights[62] * !(under_threat(b,b.data.w_pawn_4,curr_player));
                    value += weights[63];
                }
                else if(b.data.w_pawn_4 & BISHOP){
                    value += weights[64] * !(under_threat(b,b.data.w_pawn_4,curr_player));
                    value += weights[65];
                }
            }

            if(is_dead(b.data.w_rook_1)){
                value += weights[35];
            }
            if(is_dead(b.data.w_rook_2)){
                value += weights[36];
            }
            if(is_dead(b.data.w_bishop)){
                value += weights[37];
            }
            if(is_dead(b.data.b_knight_1)){
                value += weights[72];
            }
            if(is_dead(b.data.b_knight_2)){
                value += weights[73];
            }

            value += (double)(weights[39] * int(b.get_legal_moves().size()));

            value += (double)(weights[40] * ((b.get_legal_moves().size() == 0) && (!b.in_check())));
            
            b.flip_player_();

        }

        return value;
    }

    void weight_update_8_2(Board &b, double target, double learning_rate, int state_count = 0){
    
        auto curr_player = b.data.player_to_play;

        auto error = target - state_evaluation_7_3(b,state_count);

        bias[0] += learning_rate * error;

        weights[41] += learning_rate * error * state_count;

        if(curr_player == WHITE){

            pseudolegal_moves = b.get_pseudolegal_moves_for_side(b.data.player_to_play ^ (WHITE | BLACK));
            
            weights[0] += learning_rate * error * b.in_check();
            weights[1] += learning_rate * error * under_threat(b,b.data.w_rook_1,curr_player);
            weights[2] += learning_rate * error * under_threat(b,b.data.w_rook_2,curr_player);
            weights[3] += learning_rate * error * under_threat(b,b.data.w_bishop,curr_player);
            weights[66] += learning_rate * error * under_threat(b,b.data.b_knight_1,curr_player);
            weights[67] += learning_rate * error * under_threat(b,b.data.b_knight_2,curr_player);

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

            if(b.data.w_pawn_3 != DEAD){
                if(b.data.w_pawn_3 & PAWN){
                    weights[42] += learning_rate * error * !(under_threat(b,b.data.w_pawn_3,curr_player));
                    weights[43] += learning_rate * error;
                }
                else if(b.data.w_pawn_3 & ROOK){
                    weights[44] += learning_rate * error * !(under_threat(b,b.data.w_pawn_3,curr_player));
                    weights[45] += learning_rate * error;
                }
                else if(b.data.w_pawn_3 & BISHOP){
                    weights[46] += learning_rate * error * !(under_threat(b,b.data.w_pawn_3,curr_player));
                    weights[47] += learning_rate * error;
                }
            }

            if(b.data.w_pawn_4 != DEAD){
                if(b.data.w_pawn_4 & PAWN){
                    weights[54] += learning_rate * error * !(under_threat(b,b.data.w_pawn_4,curr_player));
                    weights[55] += learning_rate * error;
                }
                else if(b.data.w_pawn_4 & ROOK){
                    weights[56] += learning_rate * error * !(under_threat(b,b.data.w_pawn_4,curr_player));
                    weights[57] += learning_rate * error;
                }
                else if(b.data.w_pawn_4 & BISHOP){
                    weights[58] += learning_rate * error * !(under_threat(b,b.data.w_pawn_4,curr_player));
                    weights[59] += learning_rate * error;
                }
            }

            if(is_dead(b.data.w_rook_1)){
                weights[16] += learning_rate * error;
            }
            if(is_dead(b.data.w_rook_2)){
                weights[17] += learning_rate * error;
            }
            if(is_dead(b.data.w_bishop)){
                weights[18] += learning_rate * error;
            }
            if(is_dead(b.data.b_knight_1)){
                weights[68] += learning_rate * error;
            }
            if(is_dead(b.data.b_knight_2)){
                weights[69] += learning_rate * error;
            }
            weights[38] += learning_rate * (double)(error * int(b.get_legal_moves().size()));

            curr_player = (PlayerColor)(curr_player ^ (WHITE | BLACK));
            b.flip_player_();

            pseudolegal_moves = b.get_pseudolegal_moves_for_side(b.data.player_to_play ^ (WHITE | BLACK));

            weights[19] += learning_rate * error * b.in_check();
            weights[20] += learning_rate * error * under_threat(b,b.data.b_rook_1,curr_player);
            weights[21] += learning_rate * error * under_threat(b,b.data.b_rook_2,curr_player);
            weights[22] += learning_rate * error * under_threat(b,b.data.b_bishop,curr_player);
            weights[70] += learning_rate * error * under_threat(b,b.data.w_knight_1,curr_player);
            weights[71] += learning_rate * error * under_threat(b,b.data.w_knight_2,curr_player);

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

            if(b.data.b_pawn_3 != DEAD){
                if(b.data.b_pawn_3 & PAWN){
                    weights[48] += learning_rate * error * !(under_threat(b,b.data.b_pawn_3,curr_player));
                    weights[49] += learning_rate * error;
                }
                else if(b.data.b_pawn_3 & ROOK){
                    weights[50] += learning_rate * error * !(under_threat(b,b.data.b_pawn_3,curr_player));
                    weights[51] += learning_rate * error;
                }
                else if(b.data.b_pawn_3 & BISHOP){
                    weights[52] += learning_rate * error * !(under_threat(b,b.data.b_pawn_3,curr_player));
                    weights[53] += learning_rate * error;
                }
            }

            if(b.data.b_pawn_4 != DEAD){
                if(b.data.b_pawn_4 & PAWN){
                    weights[60] += learning_rate * error * !(under_threat(b,b.data.b_pawn_4,curr_player));
                    weights[61] += learning_rate * error;
                }
                else if(b.data.b_pawn_4 & ROOK){
                    weights[62] += learning_rate * error * !(under_threat(b,b.data.b_pawn_4,curr_player));
                    weights[63] += learning_rate * error;
                }
                else if(b.data.b_pawn_4 & BISHOP){
                    weights[64] += learning_rate * error * !(under_threat(b,b.data.b_pawn_4,curr_player));
                    weights[65] += learning_rate * error;
                }
            }

            if(is_dead(b.data.b_rook_1)){
                weights[35] += learning_rate * error;
            }
            if(is_dead(b.data.b_rook_2)){
                weights[36] += learning_rate * error;
            }
            if(is_dead(b.data.b_bishop)){
                weights[37] += learning_rate * error;
            }
            if(is_dead(b.data.w_knight_1)){
                weights[72] += learning_rate * error;
            }
            if(is_dead(b.data.w_knight_2)){
                weights[73] += learning_rate * error;
            }
            
            weights[39] += learning_rate * (double)(error * int(b.get_legal_moves().size()));

            weights[40] += learning_rate * (double)(error * ((b.get_legal_moves().size() == 0) && (!b.in_check())));

            b.flip_player_();

        }
        else{

            pseudolegal_moves = b.get_pseudolegal_moves_for_side(b.data.player_to_play ^ (WHITE | BLACK));
            
            weights[0] += learning_rate * error * b.in_check();
            weights[1] += learning_rate * error * under_threat(b,b.data.b_rook_1,curr_player);
            weights[2] += learning_rate * error * under_threat(b,b.data.b_rook_2,curr_player);
            weights[3] += learning_rate * error * under_threat(b,b.data.b_bishop,curr_player);
            weights[66] += learning_rate * error * under_threat(b,b.data.w_knight_1,curr_player);
            weights[67] += learning_rate * error * under_threat(b,b.data.w_knight_2,curr_player);

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

            if(b.data.b_pawn_3 != DEAD){
                if(b.data.b_pawn_3 & PAWN){
                    weights[42] += learning_rate * error * !(under_threat(b,b.data.b_pawn_3,curr_player));
                    weights[43] += learning_rate * error;
                }
                else if(b.data.b_pawn_3 & ROOK){
                    weights[44] += learning_rate * error * !(under_threat(b,b.data.b_pawn_3,curr_player));
                    weights[45] += learning_rate * error;
                }
                else if(b.data.b_pawn_3 & BISHOP){
                    weights[46] += learning_rate * error * !(under_threat(b,b.data.b_pawn_3,curr_player));
                    weights[47] += learning_rate * error;
                }
            }

            if(b.data.b_pawn_4 != DEAD){
                if(b.data.b_pawn_2 & PAWN){
                    weights[54] += learning_rate * error * !(under_threat(b,b.data.b_pawn_4,curr_player));
                    weights[55] += learning_rate * error;
                }
                else if(b.data.b_pawn_4 & ROOK){
                    weights[56] += learning_rate * error * !(under_threat(b,b.data.b_pawn_4,curr_player));
                    weights[57] += learning_rate * error;
                }
                else if(b.data.b_pawn_4 & BISHOP){
                    weights[58] += learning_rate * error * !(under_threat(b,b.data.b_pawn_4,curr_player));
                    weights[59] += learning_rate * error;
                }
            }

            if(is_dead(b.data.b_rook_1)){
                weights[16] += learning_rate * error;
            }
            if(is_dead(b.data.b_rook_2)){
                weights[17] += learning_rate * error;
            }
            if(is_dead(b.data.b_bishop)){
                weights[18] += learning_rate * error;
            }
            if(is_dead(b.data.w_knight_1)){
                weights[68] += learning_rate * error;
            }
            if(is_dead(b.data.w_knight_2)){
                weights[69] += learning_rate * error;
            }
            weights[38] += learning_rate * (double)(error * int(b.get_legal_moves().size()));

            curr_player = (PlayerColor)(curr_player ^ (WHITE | BLACK));
            b.flip_player_();

            pseudolegal_moves = b.get_pseudolegal_moves_for_side(b.data.player_to_play ^ (WHITE | BLACK));

            weights[19] += learning_rate * error * b.in_check();
            weights[20] += learning_rate * error * under_threat(b,b.data.w_rook_1,curr_player);
            weights[21] += learning_rate * error * under_threat(b,b.data.w_rook_2,curr_player);
            weights[22] += learning_rate * error * under_threat(b,b.data.w_bishop,curr_player);
            weights[70] += learning_rate * error * under_threat(b,b.data.b_knight_1,curr_player);
            weights[71] += learning_rate * error * under_threat(b,b.data.b_knight_2,curr_player);

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

            if(b.data.w_pawn_3 != DEAD){
                if(b.data.w_pawn_3 & PAWN){
                    weights[48] += learning_rate * error * !(under_threat(b,b.data.w_pawn_3,curr_player));
                    weights[49] += learning_rate * error;
                }
                else if(b.data.w_pawn_3 & ROOK){
                    weights[50] += learning_rate * error * !(under_threat(b,b.data.w_pawn_3,curr_player));
                    weights[51] += learning_rate * error;
                }
                else if(b.data.w_pawn_3 & BISHOP){
                    weights[52] += learning_rate * error * !(under_threat(b,b.data.w_pawn_3,curr_player));
                    weights[53] += learning_rate * error;
                }
            }

            if(b.data.w_pawn_4 != DEAD){
                if(b.data.w_pawn_4 & PAWN){
                    weights[60] += learning_rate * error * !(under_threat(b,b.data.w_pawn_4,curr_player));
                    weights[61] += learning_rate * error;
                }
                else if(b.data.w_pawn_4 & ROOK){
                    weights[62] += learning_rate * error * !(under_threat(b,b.data.w_pawn_4,curr_player));
                    weights[63] += learning_rate * error;
                }
                else if(b.data.w_pawn_4 & BISHOP){
                    weights[64] += learning_rate * error * !(under_threat(b,b.data.w_pawn_4,curr_player));
                    weights[65] += learning_rate * error;
                }
            }

            if(is_dead(b.data.w_rook_1)){
                weights[35] += learning_rate * error;
            }
            if(is_dead(b.data.w_rook_2)){
                weights[36] += learning_rate * error;
            }
            if(is_dead(b.data.w_bishop)){
                weights[37] += learning_rate * error;
            }
            if(is_dead(b.data.b_knight_1)){
                weights[72] += learning_rate * error;
            }
            if(is_dead(b.data.b_knight_2)){
                weights[73] += learning_rate * error;
            }

            weights[39] += learning_rate * (double)(error * int(b.get_legal_moves().size()));

            weights[40] += learning_rate * (double)(error * ((b.get_legal_moves().size() == 0) && (!b.in_check())));

            b.flip_player_();
        }
        write_weights();
    }

    double state_evaluation_8_4(Board &b, int state_count = 0){
        
        double value = weights[41] * state_count;

        value += bias[0];

        auto curr_player = b.data.player_to_play;

        if(curr_player == WHITE){

            pseudolegal_moves = b.get_pseudolegal_moves_for_side(b.data.player_to_play ^ (WHITE | BLACK));

            value += weights[0] * b.in_check();
            value += weights[1] * under_threat(b,b.data.w_rook_1,curr_player);
            value += weights[2] * under_threat(b,b.data.w_rook_2,curr_player);
            value += weights[3] * under_threat(b,b.data.w_bishop,curr_player);

            if(b.data.w_pawn_1 != DEAD){
                if(b.data.w_pawn_1 & PAWN){
                    value += weights[4] * !(under_threat(b,b.data.w_pawn_1,curr_player));
                    value += weights[5];
                    value += (double)(-0.00001 * (manhattan_distance(getx(b.data.w_pawn_1),gety(b.data.w_pawn_1),4,5) + manhattan_distance(getx(b.data.w_pawn_1),gety(b.data.w_pawn_1),4,6)));
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
                    value += (double)(-0.00001 * (manhattan_distance(getx(b.data.w_pawn_2),gety(b.data.w_pawn_2),4,5) + manhattan_distance(getx(b.data.w_pawn_2),gety(b.data.w_pawn_2),4,6)));
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

            if(b.data.w_pawn_3 != DEAD){
                if(b.data.w_pawn_3 & PAWN){
                    value += weights[42] * !(under_threat(b,b.data.w_pawn_3,curr_player));
                    value += weights[43];
                    value += (double)(-0.00001 * (manhattan_distance(getx(b.data.w_pawn_3),gety(b.data.w_pawn_3),5,6) + manhattan_distance(getx(b.data.w_pawn_3),gety(b.data.w_pawn_3),5,7)));
                }
                else if(b.data.w_pawn_3 & ROOK){
                    value += weights[44] * !(under_threat(b,b.data.w_pawn_3,curr_player));
                    value += weights[45];
                }
                else if(b.data.w_pawn_3 & BISHOP){
                    value += weights[46] * !(under_threat(b,b.data.w_pawn_3,curr_player));
                    value += weights[47];
                }
            }

            if(b.data.w_pawn_4 != DEAD){
                if(b.data.w_pawn_4 & PAWN){
                    value += weights[54] * !(under_threat(b,b.data.w_pawn_4,curr_player));
                    value += weights[55];
                    value += (double)(-0.00001 * (manhattan_distance(getx(b.data.w_pawn_4),gety(b.data.w_pawn_4),5,6) + manhattan_distance(getx(b.data.w_pawn_4),gety(b.data.w_pawn_4),5,7)));
                }
                else if(b.data.w_pawn_4 & ROOK){
                    value += weights[56] * !(under_threat(b,b.data.w_pawn_4,curr_player));
                    value += weights[57];
                }
                else if(b.data.w_pawn_4 & BISHOP){
                    value += weights[58] * !(under_threat(b,b.data.w_pawn_4,curr_player));
                    value += weights[59];
                }
            }

            if(is_dead(b.data.w_rook_1)){
                value += weights[16];
            }
            if(is_dead(b.data.w_rook_2)){
                value += weights[17];
            }
            if(is_dead(b.data.w_bishop)){
                value += weights[18];
            }

            value += (double)(weights[38] * int(b.get_legal_moves().size()));

            curr_player = (PlayerColor)(curr_player ^ (WHITE | BLACK));
            b.flip_player_();

            pseudolegal_moves = b.get_pseudolegal_moves_for_side(b.data.player_to_play ^ (WHITE | BLACK));

            value += weights[19] * b.in_check();
            value += weights[20] * under_threat(b,b.data.b_rook_1,curr_player);
            value += weights[21] * under_threat(b,b.data.b_rook_2,curr_player);
            value += weights[22] * under_threat(b,b.data.b_bishop,curr_player);

            if(b.data.b_pawn_1 != DEAD){
                if(b.data.b_pawn_1 & PAWN){
                    value += weights[23] * !(under_threat(b,b.data.b_pawn_1,curr_player));
                    value += weights[24];
                    value += (double)(0.00001 * (manhattan_distance(getx(b.data.b_pawn_1),gety(b.data.b_pawn_1),2,1) + manhattan_distance(getx(b.data.b_pawn_1),gety(b.data.b_pawn_1),2,0)));
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
                    value += (double)(0.00001 * (manhattan_distance(getx(b.data.b_pawn_2),gety(b.data.b_pawn_2),2,1) + manhattan_distance(getx(b.data.b_pawn_2),gety(b.data.b_pawn_2),2,0)));
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

            if(b.data.b_pawn_3 != DEAD){
                if(b.data.b_pawn_3 & PAWN){
                    value += weights[48] * !(under_threat(b,b.data.b_pawn_3,curr_player));
                    value += weights[49];
                    value += (double)(0.00001 * (manhattan_distance(getx(b.data.b_pawn_3),gety(b.data.b_pawn_3),2,1) + manhattan_distance(getx(b.data.b_pawn_3),gety(b.data.b_pawn_3),2,0)));
                }
                else if(b.data.b_pawn_3 & ROOK){
                    value += weights[50] * !(under_threat(b,b.data.b_pawn_3,curr_player));
                    value += weights[51];
                }
                else if(b.data.b_pawn_3 & BISHOP){
                    value += weights[52] * !(under_threat(b,b.data.b_pawn_3,curr_player));
                    value += weights[53];
                }
            }

            if(b.data.b_pawn_4 != DEAD){
                if(b.data.b_pawn_4 & PAWN){
                    value += weights[60] * !(under_threat(b,b.data.b_pawn_4,curr_player));
                    value += weights[61];
                    value += (double)(0.00001 * (manhattan_distance(getx(b.data.b_pawn_4),gety(b.data.b_pawn_4),2,1) + manhattan_distance(getx(b.data.b_pawn_4),gety(b.data.b_pawn_4),2,0)));
                }
                else if(b.data.b_pawn_4 & ROOK){
                    value += weights[62] * !(under_threat(b,b.data.b_pawn_4,curr_player));
                    value += weights[63];
                }
                else if(b.data.b_pawn_4 & BISHOP){
                    value += weights[64] * !(under_threat(b,b.data.b_pawn_4,curr_player));
                    value += weights[65];
                }
            }

            if(is_dead(b.data.b_rook_1)){
                value += weights[35];
            }
            if(is_dead(b.data.b_rook_2)){
                value += weights[36];
            }
            if(is_dead(b.data.b_bishop)){
                value += weights[37];
            }

            value += (double)(weights[39] * int(b.get_legal_moves().size()));

            value += (double)(weights[40] * ((b.get_legal_moves().size() == 0) && (!b.in_check())));

            b.flip_player_();
            

        }
        else{

            pseudolegal_moves = b.get_pseudolegal_moves_for_side(b.data.player_to_play ^ (WHITE | BLACK));
            
            value += weights[0] * b.in_check();
            value += weights[1] * under_threat(b,b.data.b_rook_1,curr_player);
            value += weights[2] * under_threat(b,b.data.b_rook_2,curr_player);
            value += weights[3] * under_threat(b,b.data.b_bishop,curr_player);

            if(b.data.b_pawn_1 != DEAD){
                if(b.data.b_pawn_1 & PAWN){
                    value += weights[4] * !(under_threat(b,b.data.b_pawn_1,curr_player));
                    value += weights[5];
                    value += (double)(-0.00001 * (manhattan_distance(getx(b.data.b_pawn_1),gety(b.data.b_pawn_1),2,1) + manhattan_distance(getx(b.data.b_pawn_1),gety(b.data.b_pawn_1),2,0)));
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
                    value += (double)(-0.00001 * (manhattan_distance(getx(b.data.b_pawn_2),gety(b.data.b_pawn_2),2,1) + manhattan_distance(getx(b.data.b_pawn_2),gety(b.data.b_pawn_2),2,0)));
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

            if(b.data.b_pawn_3 != DEAD){
                if(b.data.b_pawn_3 & PAWN){
                    value += weights[42] * !(under_threat(b,b.data.b_pawn_3,curr_player));
                    value += weights[43];
                    value += (double)(-0.00001 * (manhattan_distance(getx(b.data.b_pawn_3),gety(b.data.b_pawn_3),2,1) + manhattan_distance(getx(b.data.b_pawn_3),gety(b.data.b_pawn_3),2,0)));
                }
                else if(b.data.b_pawn_3 & ROOK){
                    value += weights[44] * !(under_threat(b,b.data.b_pawn_3,curr_player));
                    value += weights[45];
                }
                else if(b.data.b_pawn_3 & BISHOP){
                    value += weights[46] * !(under_threat(b,b.data.b_pawn_3,curr_player));
                    value += weights[47];
                }
            }

            if(b.data.b_pawn_4 != DEAD){
                if(b.data.b_pawn_4 & PAWN){
                    value += weights[54] * !(under_threat(b,b.data.b_pawn_4,curr_player));
                    value += weights[55];
                    value += (double)(-0.00001 * (manhattan_distance(getx(b.data.b_pawn_4),gety(b.data.b_pawn_4),2,1) + manhattan_distance(getx(b.data.b_pawn_4),gety(b.data.b_pawn_4),2,0)));
                }
                else if(b.data.b_pawn_4 & ROOK){
                    value += weights[56] * !(under_threat(b,b.data.b_pawn_4,curr_player));
                    value += weights[57];
                }
                else if(b.data.b_pawn_4 & BISHOP){
                    value += weights[58] * !(under_threat(b,b.data.b_pawn_4,curr_player));
                    value += weights[59];
                }
            }

            if(is_dead(b.data.b_rook_1)){
                value += weights[16];
            }
            if(is_dead(b.data.b_rook_2)){
                value += weights[17];
            }
            if(is_dead(b.data.b_bishop)){
                value += weights[18];
            }

            value += (double)(weights[38] * int(b.get_legal_moves().size()));

            curr_player = (PlayerColor)(curr_player ^ (WHITE | BLACK));
            b.flip_player_();

            pseudolegal_moves = b.get_pseudolegal_moves_for_side(b.data.player_to_play ^ (WHITE | BLACK));

            value += weights[19] * b.in_check();
            value += weights[20] * under_threat(b,b.data.w_rook_1,curr_player);
            value += weights[21] * under_threat(b,b.data.w_rook_2,curr_player);
            value += weights[22] * under_threat(b,b.data.w_bishop,curr_player);

            if(b.data.w_pawn_1 != DEAD){
                if(b.data.w_pawn_1 & PAWN){
                    value += weights[23] * !(under_threat(b,b.data.w_pawn_1,curr_player));
                    value += weights[24];
                    value += (double)(0.00001 * (manhattan_distance(getx(b.data.w_pawn_1),gety(b.data.w_pawn_1),4,5) + manhattan_distance(getx(b.data.w_pawn_1),gety(b.data.w_pawn_1),4,6)));
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
                    value += (double)(0.00001 * (manhattan_distance(getx(b.data.w_pawn_2),gety(b.data.w_pawn_2),4,5) + manhattan_distance(getx(b.data.w_pawn_2),gety(b.data.w_pawn_2),4,6)));
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

            if(b.data.w_pawn_3 != DEAD){
                if(b.data.w_pawn_3 & PAWN){
                    value += weights[48] * !(under_threat(b,b.data.w_pawn_3,curr_player));
                    value += weights[49];
                    value += (double)(0.00001 * (manhattan_distance(getx(b.data.w_pawn_3),gety(b.data.w_pawn_3),5,6) + manhattan_distance(getx(b.data.w_pawn_3),gety(b.data.w_pawn_3),5,7)));
                }
                else if(b.data.w_pawn_3 & ROOK){
                    value += weights[50] * !(under_threat(b,b.data.w_pawn_3,curr_player));
                    value += weights[51];
                }
                else if(b.data.w_pawn_3 & BISHOP){
                    value += weights[52] * !(under_threat(b,b.data.w_pawn_3,curr_player));
                    value += weights[53];
                }
            }

            if(b.data.w_pawn_4 != DEAD){
                if(b.data.w_pawn_4 & PAWN){
                    value += weights[60] * !(under_threat(b,b.data.w_pawn_4,curr_player));
                    value += weights[61];
                    value += (double)(0.00001 * (manhattan_distance(getx(b.data.w_pawn_4),gety(b.data.w_pawn_4),5,6) + manhattan_distance(getx(b.data.w_pawn_4),gety(b.data.w_pawn_4),5,7)));
                }
                else if(b.data.w_pawn_4 & ROOK){
                    value += weights[62] * !(under_threat(b,b.data.w_pawn_4,curr_player));
                    value += weights[63];
                }
                else if(b.data.w_pawn_4 & BISHOP){
                    value += weights[64] * !(under_threat(b,b.data.w_pawn_4,curr_player));
                    value += weights[65];
                }
            }

            if(is_dead(b.data.w_rook_1)){
                value += weights[35];
            }
            if(is_dead(b.data.w_rook_2)){
                value += weights[36];
            }
            if(is_dead(b.data.w_bishop)){
                value += weights[37];
            }

            value += (double)(weights[39] * int(b.get_legal_moves().size()));

            value += (double)(weights[40] * ((b.get_legal_moves().size() == 0) && (!b.in_check())));
            
            b.flip_player_();

        }

        return value;

    }

    void weight_update_8_4(Board &b, double target, double learning_rate, int state_count = 0){
    
        auto curr_player = b.data.player_to_play;

        auto error = target - state_evaluation_7_3(b,state_count);

        bias[0] += learning_rate * error;

        weights[41] += learning_rate * error * state_count;

        if(curr_player == WHITE){

            pseudolegal_moves = b.get_pseudolegal_moves_for_side(b.data.player_to_play ^ (WHITE | BLACK));
            
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

            if(b.data.w_pawn_3 != DEAD){
                if(b.data.w_pawn_3 & PAWN){
                    weights[42] += learning_rate * error * !(under_threat(b,b.data.w_pawn_3,curr_player));
                    weights[43] += learning_rate * error;
                }
                else if(b.data.w_pawn_3 & ROOK){
                    weights[44] += learning_rate * error * !(under_threat(b,b.data.w_pawn_3,curr_player));
                    weights[45] += learning_rate * error;
                }
                else if(b.data.w_pawn_3 & BISHOP){
                    weights[46] += learning_rate * error * !(under_threat(b,b.data.w_pawn_3,curr_player));
                    weights[47] += learning_rate * error;
                }
            }

            if(b.data.w_pawn_4 != DEAD){
                if(b.data.w_pawn_4 & PAWN){
                    weights[54] += learning_rate * error * !(under_threat(b,b.data.w_pawn_4,curr_player));
                    weights[55] += learning_rate * error;
                }
                else if(b.data.w_pawn_4 & ROOK){
                    weights[56] += learning_rate * error * !(under_threat(b,b.data.w_pawn_4,curr_player));
                    weights[57] += learning_rate * error;
                }
                else if(b.data.w_pawn_4 & BISHOP){
                    weights[58] += learning_rate * error * !(under_threat(b,b.data.w_pawn_4,curr_player));
                    weights[59] += learning_rate * error;
                }
            }

            if(is_dead(b.data.w_rook_1)){
                weights[16] += learning_rate * error;
            }
            if(is_dead(b.data.w_rook_2)){
                weights[17] += learning_rate * error;
            }
            if(is_dead(b.data.w_bishop)){
                weights[18] += learning_rate * error;
            }
            weights[38] += learning_rate * (double)(error * int(b.get_legal_moves().size()));

            curr_player = (PlayerColor)(curr_player ^ (WHITE | BLACK));
            b.flip_player_();

            pseudolegal_moves = b.get_pseudolegal_moves_for_side(b.data.player_to_play ^ (WHITE | BLACK));

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

            if(b.data.b_pawn_3 != DEAD){
                if(b.data.b_pawn_3 & PAWN){
                    weights[48] += learning_rate * error * !(under_threat(b,b.data.b_pawn_3,curr_player));
                    weights[49] += learning_rate * error;
                }
                else if(b.data.b_pawn_3 & ROOK){
                    weights[50] += learning_rate * error * !(under_threat(b,b.data.b_pawn_3,curr_player));
                    weights[51] += learning_rate * error;
                }
                else if(b.data.b_pawn_3 & BISHOP){
                    weights[52] += learning_rate * error * !(under_threat(b,b.data.b_pawn_3,curr_player));
                    weights[53] += learning_rate * error;
                }
            }

            if(b.data.b_pawn_4 != DEAD){
                if(b.data.b_pawn_4 & PAWN){
                    weights[60] += learning_rate * error * !(under_threat(b,b.data.b_pawn_4,curr_player));
                    weights[61] += learning_rate * error;
                }
                else if(b.data.b_pawn_4 & ROOK){
                    weights[62] += learning_rate * error * !(under_threat(b,b.data.b_pawn_4,curr_player));
                    weights[63] += learning_rate * error;
                }
                else if(b.data.b_pawn_4 & BISHOP){
                    weights[64] += learning_rate * error * !(under_threat(b,b.data.b_pawn_4,curr_player));
                    weights[65] += learning_rate * error;
                }
            }

            if(is_dead(b.data.b_rook_1)){
                weights[35] += learning_rate * error;
            }
            if(is_dead(b.data.b_rook_2)){
                weights[36] += learning_rate * error;
            }
            if(is_dead(b.data.b_bishop)){
                weights[37] += learning_rate * error;
            }
            
            weights[39] += learning_rate * (double)(error * int(b.get_legal_moves().size()));

            weights[40] += learning_rate * (double)(error * ((b.get_legal_moves().size() == 0) && (!b.in_check())));

            b.flip_player_();

        }
        else{

            pseudolegal_moves = b.get_pseudolegal_moves_for_side(b.data.player_to_play ^ (WHITE | BLACK));
            
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

            if(b.data.b_pawn_3 != DEAD){
                if(b.data.b_pawn_3 & PAWN){
                    weights[42] += learning_rate * error * !(under_threat(b,b.data.b_pawn_3,curr_player));
                    weights[43] += learning_rate * error;
                }
                else if(b.data.b_pawn_3 & ROOK){
                    weights[44] += learning_rate * error * !(under_threat(b,b.data.b_pawn_3,curr_player));
                    weights[45] += learning_rate * error;
                }
                else if(b.data.b_pawn_3 & BISHOP){
                    weights[46] += learning_rate * error * !(under_threat(b,b.data.b_pawn_3,curr_player));
                    weights[47] += learning_rate * error;
                }
            }

            if(b.data.b_pawn_4 != DEAD){
                if(b.data.b_pawn_2 & PAWN){
                    weights[54] += learning_rate * error * !(under_threat(b,b.data.b_pawn_4,curr_player));
                    weights[55] += learning_rate * error;
                }
                else if(b.data.b_pawn_4 & ROOK){
                    weights[56] += learning_rate * error * !(under_threat(b,b.data.b_pawn_4,curr_player));
                    weights[57] += learning_rate * error;
                }
                else if(b.data.b_pawn_4 & BISHOP){
                    weights[58] += learning_rate * error * !(under_threat(b,b.data.b_pawn_4,curr_player));
                    weights[59] += learning_rate * error;
                }
            }

            if(is_dead(b.data.b_rook_1)){
                weights[16] += learning_rate * error;
            }
            if(is_dead(b.data.b_rook_2)){
                weights[17] += learning_rate * error;
            }
            if(is_dead(b.data.b_bishop)){
                weights[18] += learning_rate * error;
            }

            weights[38] += learning_rate * (double)(error * int(b.get_legal_moves().size()));

            curr_player = (PlayerColor)(curr_player ^ (WHITE | BLACK));
            b.flip_player_();

            pseudolegal_moves = b.get_pseudolegal_moves_for_side(b.data.player_to_play ^ (WHITE | BLACK));

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

            if(b.data.w_pawn_3 != DEAD){
                if(b.data.w_pawn_3 & PAWN){
                    weights[48] += learning_rate * error * !(under_threat(b,b.data.w_pawn_3,curr_player));
                    weights[49] += learning_rate * error;
                }
                else if(b.data.w_pawn_3 & ROOK){
                    weights[50] += learning_rate * error * !(under_threat(b,b.data.w_pawn_3,curr_player));
                    weights[51] += learning_rate * error;
                }
                else if(b.data.w_pawn_3 & BISHOP){
                    weights[52] += learning_rate * error * !(under_threat(b,b.data.w_pawn_3,curr_player));
                    weights[53] += learning_rate * error;
                }
            }

            if(b.data.w_pawn_4 != DEAD){
                if(b.data.w_pawn_4 & PAWN){
                    weights[60] += learning_rate * error * !(under_threat(b,b.data.w_pawn_4,curr_player));
                    weights[61] += learning_rate * error;
                }
                else if(b.data.w_pawn_4 & ROOK){
                    weights[62] += learning_rate * error * !(under_threat(b,b.data.w_pawn_4,curr_player));
                    weights[63] += learning_rate * error;
                }
                else if(b.data.w_pawn_4 & BISHOP){
                    weights[64] += learning_rate * error * !(under_threat(b,b.data.w_pawn_4,curr_player));
                    weights[65] += learning_rate * error;
                }
            }

            if(is_dead(b.data.w_rook_1)){
                weights[35] += learning_rate * error;
            }
            if(is_dead(b.data.w_rook_2)){
                weights[36] += learning_rate * error;
            }
            if(is_dead(b.data.w_bishop)){
                weights[37] += learning_rate * error;
            }

            weights[39] += learning_rate * (double)(error * int(b.get_legal_moves().size()));

            weights[40] += learning_rate * (double)(error * ((b.get_legal_moves().size() == 0) && (!b.in_check())));

            b.flip_player_();
        }
        write_weights();
    }

    double state_evaluation_7_3(Board &b, int state_count = 0){
        
        double value = weights[41] * state_count;

        value += bias[0];

        auto curr_player = b.data.player_to_play;

        if(curr_player == WHITE){

            pseudolegal_moves = b.get_pseudolegal_moves_for_side(b.data.player_to_play ^ (WHITE | BLACK));

            value += weights[0] * b.in_check();
            value += weights[1] * under_threat(b,b.data.w_rook_1,curr_player);
            value += weights[2] * under_threat(b,b.data.w_rook_2,curr_player);
            value += weights[3] * under_threat(b,b.data.w_bishop,curr_player);

            if(b.data.w_pawn_1 != DEAD){
                if(b.data.w_pawn_1 & PAWN){
                    value += weights[4] * !(under_threat(b,b.data.w_pawn_1,curr_player));
                    value += weights[5];
                    value += (double)(-0.00001 * (manhattan_distance(getx(b.data.w_pawn_1),gety(b.data.w_pawn_1),4,5) + manhattan_distance(getx(b.data.w_pawn_1),gety(b.data.w_pawn_1),4,6)));
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
                    value += (double)(-0.00001 * (manhattan_distance(getx(b.data.w_pawn_2),gety(b.data.w_pawn_2),4,5) + manhattan_distance(getx(b.data.w_pawn_2),gety(b.data.w_pawn_2),4,6)));
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
            if(is_dead(b.data.w_rook_1)){
                value += weights[16];
            }
            if(is_dead(b.data.w_rook_2)){
                value += weights[17];
            }
            if(is_dead(b.data.w_bishop)){
                value += weights[18];
            }

            value += (double)(weights[38] * int(b.get_legal_moves().size()));

            curr_player = (PlayerColor)(curr_player ^ (WHITE | BLACK));
            b.flip_player_();

            pseudolegal_moves = b.get_pseudolegal_moves_for_side(b.data.player_to_play ^ (WHITE | BLACK));

            value += weights[19] * b.in_check();
            value += weights[20] * under_threat(b,b.data.b_rook_1,curr_player);
            value += weights[21] * under_threat(b,b.data.b_rook_2,curr_player);
            value += weights[22] * under_threat(b,b.data.b_bishop,curr_player);

            if(b.data.b_pawn_1 != DEAD){
                if(b.data.b_pawn_1 & PAWN){
                    value += weights[23] * !(under_threat(b,b.data.b_pawn_1,curr_player));
                    value += weights[24];
                    value += (double)(0.00001 * (manhattan_distance(getx(b.data.b_pawn_1),gety(b.data.b_pawn_1),2,1) + manhattan_distance(getx(b.data.b_pawn_1),gety(b.data.b_pawn_1),2,0)));
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
                    value += (double)(0.00001 * (manhattan_distance(getx(b.data.b_pawn_2),gety(b.data.b_pawn_2),2,1) + manhattan_distance(getx(b.data.b_pawn_2),gety(b.data.b_pawn_2),2,0)));
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
            if(is_dead(b.data.b_rook_1)){
                value += weights[35];
            }
            if(is_dead(b.data.b_rook_2)){
                value += weights[36];
            }
            if(is_dead(b.data.b_bishop)){
                value += weights[37];
            }

            value += (double)(weights[39] * int(b.get_legal_moves().size()));

            value += (double)(weights[40] * ((b.get_legal_moves().size() == 0) && (!b.in_check())));

            b.flip_player_();
            

        }
        else{

            pseudolegal_moves = b.get_pseudolegal_moves_for_side(b.data.player_to_play ^ (WHITE | BLACK));
            
            value += weights[0] * b.in_check();
            value += weights[1] * under_threat(b,b.data.b_rook_1,curr_player);
            value += weights[2] * under_threat(b,b.data.b_rook_2,curr_player);
            value += weights[3] * under_threat(b,b.data.b_bishop,curr_player);

            if(b.data.b_pawn_1 != DEAD){
                if(b.data.b_pawn_1 & PAWN){
                    value += weights[4] * !(under_threat(b,b.data.b_pawn_1,curr_player));
                    value += weights[5];
                    value += (double)(-0.00001 * (manhattan_distance(getx(b.data.b_pawn_1),gety(b.data.b_pawn_1),2,1) + manhattan_distance(getx(b.data.b_pawn_1),gety(b.data.b_pawn_1),2,0)));
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
                    value += (double)(-0.00001 * (manhattan_distance(getx(b.data.b_pawn_2),gety(b.data.b_pawn_2),2,1) + manhattan_distance(getx(b.data.b_pawn_2),gety(b.data.b_pawn_2),2,0)));
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
            if(is_dead(b.data.b_rook_1)){
                value += weights[16];
            }
            if(is_dead(b.data.b_rook_2)){
                value += weights[17];
            }
            if(is_dead(b.data.b_bishop)){
                value += weights[18];
            }

            value += (double)(weights[38] * int(b.get_legal_moves().size()));

            curr_player = (PlayerColor)(curr_player ^ (WHITE | BLACK));
            b.flip_player_();

            pseudolegal_moves = b.get_pseudolegal_moves_for_side(b.data.player_to_play ^ (WHITE | BLACK));

            value += weights[19] * b.in_check();
            value += weights[20] * under_threat(b,b.data.w_rook_1,curr_player);
            value += weights[21] * under_threat(b,b.data.w_rook_2,curr_player);
            value += weights[22] * under_threat(b,b.data.w_bishop,curr_player);

            if(b.data.w_pawn_1 != DEAD){
                if(b.data.w_pawn_1 & PAWN){
                    value += weights[23] * !(under_threat(b,b.data.w_pawn_1,curr_player));
                    value += weights[24];
                    value += (double)(0.00001 * (manhattan_distance(getx(b.data.w_pawn_1),gety(b.data.w_pawn_1),4,5) + manhattan_distance(getx(b.data.w_pawn_1),gety(b.data.w_pawn_1),4,6)));
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
                    value += (double)(0.00001 * (manhattan_distance(getx(b.data.w_pawn_2),gety(b.data.w_pawn_2),4,5) + manhattan_distance(getx(b.data.w_pawn_2),gety(b.data.w_pawn_2),4,6)));
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
            if(is_dead(b.data.w_rook_1)){
                value += weights[35];
            }
            if(is_dead(b.data.w_rook_2)){
                value += weights[36];
            }
            if(is_dead(b.data.w_bishop)){
                value += weights[37];
            }

            value += (double)(weights[39] * int(b.get_legal_moves().size()));

            value += (double)(weights[40] * ((b.get_legal_moves().size() == 0) && (!b.in_check())));
            
            b.flip_player_();

        }

        return value;

    }

    void weight_update_7_3(Board &b, double target, double learning_rate, int state_count = 0){
    
        auto curr_player = b.data.player_to_play;

        auto error = target - state_evaluation_7_3(b,state_count);

        bias[0] += learning_rate * error;

        weights[41] += learning_rate * error * state_count;

        if(curr_player == WHITE){

            pseudolegal_moves = b.get_pseudolegal_moves_for_side(b.data.player_to_play ^ (WHITE | BLACK));
            
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

            if(is_dead(b.data.w_rook_1)){
                weights[16] += learning_rate * error;
            }
            if(is_dead(b.data.w_rook_2)){
                weights[17] += learning_rate * error;
            }
            if(is_dead(b.data.w_bishop)){
                weights[18] += learning_rate * error;
            }
            weights[38] += learning_rate * (double)(error * int(b.get_legal_moves().size()));

            curr_player = (PlayerColor)(curr_player ^ (WHITE | BLACK));
            b.flip_player_();

            pseudolegal_moves = b.get_pseudolegal_moves_for_side(b.data.player_to_play ^ (WHITE | BLACK));

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
            if(is_dead(b.data.b_rook_1)){
                weights[35] += learning_rate * error;
            }
            if(is_dead(b.data.b_rook_2)){
                weights[36] += learning_rate * error;
            }
            if(is_dead(b.data.b_bishop)){
                weights[37] += learning_rate * error;
            }
            
            weights[39] += learning_rate * (double)(error * int(b.get_legal_moves().size()));

            weights[40] += learning_rate * (double)(error * ((b.get_legal_moves().size() == 0) && (!b.in_check())));

            b.flip_player_();

        }
        else{

            pseudolegal_moves = b.get_pseudolegal_moves_for_side(b.data.player_to_play ^ (WHITE | BLACK));
            
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
            if(is_dead(b.data.b_rook_1)){
                weights[16] += learning_rate * error;
            }
            if(is_dead(b.data.b_rook_2)){
                weights[17] += learning_rate * error;
            }
            if(is_dead(b.data.b_bishop)){
                weights[18] += learning_rate * error;
            }

            weights[38] += learning_rate * (double)(error * int(b.get_legal_moves().size()));

            curr_player = (PlayerColor)(curr_player ^ (WHITE | BLACK));
            b.flip_player_();

            pseudolegal_moves = b.get_pseudolegal_moves_for_side(b.data.player_to_play ^ (WHITE | BLACK));

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
            if(is_dead(b.data.w_rook_1)){
                weights[35] += learning_rate * error;
            }
            if(is_dead(b.data.w_rook_2)){
                weights[36] += learning_rate * error;
            }
            if(is_dead(b.data.w_bishop)){
                weights[37] += learning_rate * error;
            }

            weights[39] += learning_rate * (double)(error * int(b.get_legal_moves().size()));

            weights[40] += learning_rate * (double)(error * ((b.get_legal_moves().size() == 0) && (!b.in_check())));

            b.flip_player_();
        }
        write_weights();
    }


    std::vector<double> weights;

    std::vector<double> bias;

    // features

    bool under_threat(Board &b, U8 piece, PlayerColor player){

        for (auto move : pseudolegal_moves) {
            // std::cout << move_to_str(move) << " ";
            if (getp1(move) == piece) {
                // std::cout << "<- causes check\n";
                return true;
            }
        }
        return false;    
    }

    bool is_dead(U8 piece){
        return piece == DEAD;
    }

    double manhattan_distance(int x1, int y1, int x2, int y2){
        // int dist = 0;
        
        // if(x1 == 0 && x2 == 0 && y1 <= y2){
        //     return (y2 - y1);
        // }
        // else if(y1 == 0 && y2 == 0 && x1 >= x2){
        //     return (x1 - x2);
        // }
        // else if(x1 == 6 && x2 == 6 && y1 >= y2){
        //     return (y1 - y2);
        // }
        // else if(y1 == 6 && y2 == 6 && x2 >= x1){
        //     return (x2 - x1);
        // }

        // if(x1 == 0 || x1 == 6){
        //     if(x1 == 0)
        //         x1 = 1;
        //     else
        //         x1 = 5;

        //     dist++;
        // }
        // if(y1 == 0 || y1 == 6){
        //     if(y1 == 0)
        //         y1 = 1;
        //     else
        //         y1 = 5;
            
        //     dist++;
        // }

        // if(x2 == 0 || x2 == 6){
        //     if(x2 == 0)
        //         x2 = 1;
        //     else
        //         x2 = 5;
            
        //     dist++;
        // }
        // if(y2 == 0 || y2 == 6){
        //     if(y2 == 0)
        //         y2 = 1;
        //     else
        //         y2 = 5;
            
        //     dist++;
        // }

        // int p1,p2;
        
        // assert(x1 == 1 || x1 == 5 || y1 == 1 || y1 == 5);

        // if(x1 == 1)
        //     p1 = y1-1;
        // else if(x1 == 5){
        //     p1 = 13 - y1;
        // }
        // else if(y1 == 1){
        //     p1 = 17 - x1;
        // }
        // else{
        //     p1 = 3 + x1;
        // }

        // p1 %= 16;

        // assert(x2 == 1 || x2 == 5 || y2 == 1 || y2 == 5);

        // if(x2 == 1)
        //     p2 = y2-1;
        // else if(x2 == 5){
        //     p2 = 13 - y2;
        // }
        // else if(y2 == 1){
        //     p2 = 17 - x2;
        // }
        // else{
        //     p2 = 3 + x2;
        // }

        // p2 %= 16;

        // if(p1>p2)
        //     return  (dist + (16 - (p1 - p2)));

        // return (dist + (p2 - p1));
        // return 0;
        return (x1-x2) * (x1-x2) + (y1-y2) * (y1-y2);
    }

    void write_weights(){
        std::ofstream output_file("src/weights.txt");

        output_file<< std::hexfloat;

        for(auto &it : weights){
            output_file<<it<<"\n";
        }

        output_file<<bias[0]<<"\n";

        output_file.close();
    }

    void read_weights(){
        std::ifstream input_file("src/weights.txt");
        std::string line;

        for(auto &it : weights){
            std::getline(input_file,line);
            it = std::stod(line);
        }

        std::getline(input_file,line);
        bias[0] = std::stod(line);

        input_file.close();
    }

};


class QLearningAgent {
public:
    QLearningAgent(bool pretrained = false)
        : fn(pretrained) {
            learningRate = 0.0001;
            discountFactor = 0.9;
            trainstep = 1;

    }

    double state_evaluation(Board& b, U16 move, std::map<std::string,int>& board_count){ // Q(s,a)

        b.do_move_without_flip_(move);
        double score;
        if(b.data.board_type == SEVEN_THREE)
            score = fn.state_evaluation_7_3(b,board_count[board_encode(b)]);
        else if(b.data.board_type == EIGHT_TWO)
            score = fn.state_evaluation_8_4(b,board_count[board_encode(b)]);
        else
            score = fn.state_evaluation_8_2(b,board_count[board_encode(b)]);
        b.undo_last_move_without_flip_(move);
        return score;
    }

    // Q-learning update
    void qLearningUpdate(Board& state, U16 move,std::map<std::string,int>& board_count, bool isdraw = false) {
        auto curr_score = board_evaluate(state);
        state.do_move_without_flip_(move);
        auto last_killed = state.data.last_killed_piece;
        auto last_killed_idx = state.data.last_killed_piece_idx;
        auto next_score = board_evaluate(state);

        double reward = double(next_score - curr_score);
        double next_q_val = -DBL_MAX;
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
                next_q_val = std::max(next_q_val,state_evaluation(state,it,board_count));
            }
            state.flip_player_();

            next_q_val = -next_q_val;

        }
        if(state.data.board_type == SEVEN_THREE)
            fn.weight_update_7_3(state,reward + discountFactor * next_q_val,learningRate/((double)trainstep),board_count[board_encode(state)]);
        else if(state.data.board_type == EIGHT_TWO)
            fn.weight_update_8_2(state,reward + discountFactor * next_q_val,learningRate/((double)trainstep),board_count[board_encode(state)]);
        else
            fn.weight_update_8_4(state,reward + discountFactor * next_q_val,learningRate/((double)trainstep),board_count[board_encode(state)]);
        
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
