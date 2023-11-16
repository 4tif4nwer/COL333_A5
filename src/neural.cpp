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
    perspective += std::to_string(getx(b.data.w_pawn_1));
    perspective += std::to_string(gety(b.data.w_pawn_1));
    perspective += std::to_string(getx(b.data.w_pawn_2));
    perspective += std::to_string(gety(b.data.w_pawn_2));

    perspective += piece_to_char(b.data.w_pawn_1);
    perspective += piece_to_char(b.data.w_pawn_2);

    perspective += std::to_string(getx(b.data.b_king));
    perspective += std::to_string(gety(b.data.b_king));
    perspective += std::to_string(getx(b.data.b_rook_1));
    perspective += std::to_string(gety(b.data.b_rook_1));
    perspective += std::to_string(getx(b.data.b_rook_2));
    perspective += std::to_string(gety(b.data.b_rook_2));
    perspective += std::to_string(getx(b.data.b_bishop));
    perspective += std::to_string(gety(b.data.b_bishop));
    perspective += std::to_string(getx(b.data.b_pawn_1));
    perspective += std::to_string(gety(b.data.b_pawn_1));
    perspective += std::to_string(getx(b.data.b_pawn_2));
    perspective += std::to_string(gety(b.data.b_pawn_2));

    perspective += piece_to_char(b.data.b_pawn_1);
    perspective += piece_to_char(b.data.b_pawn_2);
    
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

    function_approximator(bool pretrained = false){
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<double> dist(-1.0, 1.0);

        weights.resize(78,0);
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

    double state_evaluation(Board &b, int state_count = 0){
        
        double value = weights[59] * state_count;

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
                    value += (double)(weights[43] * (circular_distance_7_3(getx(b.data.w_pawn_1),gety(b.data.w_pawn_1),4,5) + circular_distance_7_3(getx(b.data.w_pawn_1),gety(b.data.w_pawn_1),4,6)));
                    value += (double)(weights[60] * int(b.get_pseudolegal_moves_for_piece(b.data.w_pawn_1).size()));
                }
                else if(b.data.w_pawn_1 & ROOK){
                    value += weights[6] * !(under_threat(b,b.data.w_pawn_1,curr_player));
                    value += weights[7];
                    value += (double)(weights[44] * circular_distance_7_3(getx(b.data.w_pawn_1),gety(b.data.w_pawn_1),getx(b.data.b_king),gety(b.data.b_king)));
                    value += (double)(weights[61] * int(b.get_pseudolegal_moves_for_piece(b.data.w_pawn_1).size()));
                }
                else if(b.data.w_pawn_1 & BISHOP){
                    value += weights[8] * !(under_threat(b,b.data.w_pawn_1,curr_player));
                    value += weights[9];
                    value += (double)(weights[45] * circular_distance_7_3(getx(b.data.w_pawn_1),gety(b.data.w_pawn_1),getx(b.data.b_king),gety(b.data.b_king)));
                    value += (double)(weights[62] * int(b.get_pseudolegal_moves_for_piece(b.data.w_pawn_1).size()));
                }
            }
            
            if(b.data.w_pawn_2 != DEAD){
                if(b.data.w_pawn_2 & PAWN){
                    value += weights[10] * !(under_threat(b,b.data.w_pawn_2,curr_player));
                    value += weights[11];
                    value += (double)(weights[46] * (circular_distance_7_3(getx(b.data.w_pawn_2),gety(b.data.w_pawn_2),4,5) + circular_distance_7_3(getx(b.data.w_pawn_2),gety(b.data.w_pawn_2),4,6)));
                    value += (double)(weights[63] * int(b.get_pseudolegal_moves_for_piece(b.data.w_pawn_2).size()));
                }
                else if(b.data.w_pawn_2 & ROOK){
                    value += weights[12] * !(under_threat(b,b.data.w_pawn_2,curr_player));
                    value += weights[13];
                    value += (double)(weights[47] * circular_distance_7_3(getx(b.data.w_pawn_2),gety(b.data.w_pawn_2),getx(b.data.b_king),gety(b.data.b_king)));
                    value += (double)(weights[64] * int(b.get_pseudolegal_moves_for_piece(b.data.w_pawn_2).size()));
                }
                else if(b.data.w_pawn_2 & BISHOP){
                    value += weights[14] * !(under_threat(b,b.data.w_pawn_2,curr_player));
                    value += weights[15];
                    value += (double)(weights[48] * circular_distance_7_3(getx(b.data.w_pawn_2),gety(b.data.w_pawn_2),getx(b.data.b_king),gety(b.data.b_king)));
                    value += (double)(weights[65] * int(b.get_pseudolegal_moves_for_piece(b.data.w_pawn_2).size()));
                }
            }
            if(!is_dead(b.data.w_rook_1)){
                value += (double)(weights[40] * circular_distance_7_3(getx(b.data.w_rook_1),gety(b.data.w_rook_1),getx(b.data.b_king),gety(b.data.b_king)));
                value += (double)(weights[66] * int(b.get_pseudolegal_moves_for_piece(b.data.w_rook_1).size()));
            }
            else{
                value += weights[16];
            }
            if(!is_dead(b.data.w_rook_2)){
                value += (double)(weights[41] * circular_distance_7_3(getx(b.data.w_rook_2),gety(b.data.w_rook_2),getx(b.data.b_king),gety(b.data.b_king)));
                value += (double)(weights[67] * int(b.get_pseudolegal_moves_for_piece(b.data.w_rook_2).size()));
            }
            else{
                value += weights[17];
            }
            if(!is_dead(b.data.w_bishop)){
                value += (double)(weights[42] * circular_distance_7_3(getx(b.data.w_bishop),gety(b.data.w_bishop),getx(b.data.b_king),gety(b.data.b_king)));
                value += (double)(weights[68] * int(b.get_pseudolegal_moves_for_piece(b.data.w_bishop).size()));
            }
            else{
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
                    value += (double)(weights[52] * (circular_distance_7_3(getx(b.data.b_pawn_1),gety(b.data.b_pawn_1),2,0) + circular_distance_7_3(getx(b.data.b_pawn_1),gety(b.data.b_pawn_1),2,1)));
                    value += (double)(weights[69] * int(b.get_pseudolegal_moves_for_piece(b.data.b_pawn_1).size()));
                }
                else if(b.data.b_pawn_1 & ROOK){
                    value += weights[25] * !(under_threat(b,b.data.b_pawn_1,curr_player));
                    value += weights[26];
                    value += (double)(weights[53] * circular_distance_7_3(getx(b.data.b_pawn_1),gety(b.data.b_pawn_1),getx(b.data.w_king),gety(b.data.w_king)));
                    value += (double)(weights[70] * int(b.get_pseudolegal_moves_for_piece(b.data.b_pawn_1).size()));
                }
                else if(b.data.b_pawn_1 & BISHOP){
                    value += weights[27] * !(under_threat(b,b.data.b_pawn_1,curr_player));
                    value += weights[28];
                    value += (double)(weights[54] * circular_distance_7_3(getx(b.data.b_pawn_1),gety(b.data.b_pawn_1),getx(b.data.w_king),gety(b.data.w_king)));
                    value += (double)(weights[71] * int(b.get_pseudolegal_moves_for_piece(b.data.b_pawn_1).size()));
                }
            }

            if(b.data.b_pawn_2 != DEAD){
                if(b.data.b_pawn_2 & PAWN){
                    value += weights[29] * !(under_threat(b,b.data.b_pawn_2,curr_player));
                    value += weights[30];
                    value += (double)(weights[55] * (circular_distance_7_3(getx(b.data.b_pawn_2),gety(b.data.b_pawn_2),2,0) + circular_distance_7_3(getx(b.data.b_pawn_2),gety(b.data.b_pawn_2),2,1)));
                    value += (double)(weights[72] * int(b.get_pseudolegal_moves_for_piece(b.data.b_pawn_2).size()));
                }
                else if(b.data.b_pawn_2 & ROOK){
                    value += weights[31] * !(under_threat(b,b.data.b_pawn_2,curr_player));
                    value += weights[32];
                    value += (double)(weights[56] * circular_distance_7_3(getx(b.data.b_pawn_2),gety(b.data.b_pawn_2),getx(b.data.w_king),gety(b.data.w_king)));
                    value += (double)(weights[73] * int(b.get_pseudolegal_moves_for_piece(b.data.b_pawn_2).size()));
                }
                else if(b.data.b_pawn_2 & BISHOP){
                    value += weights[33] * !(under_threat(b,b.data.b_pawn_2,curr_player));
                    value += weights[34];
                    value += (double)(weights[57] * circular_distance_7_3(getx(b.data.b_pawn_2),gety(b.data.b_pawn_2),getx(b.data.w_king),gety(b.data.w_king)));
                    value += (double)(weights[74] * int(b.get_pseudolegal_moves_for_piece(b.data.b_pawn_2).size()));
                }
            }
            if(!is_dead(b.data.b_rook_1)){
                value += (double)(weights[49] * circular_distance_7_3(getx(b.data.b_rook_1),gety(b.data.b_rook_1),getx(b.data.w_king),gety(b.data.w_king)));
                value += (double)(weights[75] * int(b.get_pseudolegal_moves_for_piece(b.data.b_rook_1).size()));
            }
            else{
                value += weights[35];
            }
            if(!is_dead(b.data.b_rook_2)){
                value += (double)(weights[50] * circular_distance_7_3(getx(b.data.b_rook_2),gety(b.data.b_rook_2),getx(b.data.w_king),gety(b.data.w_king)));
                value += (double)(weights[76] * int(b.get_pseudolegal_moves_for_piece(b.data.b_rook_2).size()));
            }
            else{
                value += weights[36];
            }
            if(!is_dead(b.data.b_bishop)){
                value += (double)(weights[51] * circular_distance_7_3(getx(b.data.b_bishop),gety(b.data.b_bishop),getx(b.data.w_king),gety(b.data.w_king)));
                value += (double)(weights[77] * int(b.get_pseudolegal_moves_for_piece(b.data.b_bishop).size()));
            }
            else{
                value += weights[37];
            }

            value += (double)(weights[39] * int(b.get_legal_moves().size()));

            value += (double)(weights[58] * ((b.get_legal_moves().size() == 0) && (!b.in_check())));

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
                    value += (double)(weights[43] * (circular_distance_7_3(getx(b.data.b_pawn_1),gety(b.data.b_pawn_1),2,0) + circular_distance_7_3(getx(b.data.b_pawn_1),gety(b.data.b_pawn_1),2,1)));
                    value += (double)(weights[60] * int(b.get_pseudolegal_moves_for_piece(b.data.b_pawn_1).size()));
                }
                else if(b.data.b_pawn_1 & ROOK){
                    value += weights[6] * !(under_threat(b,b.data.b_pawn_1,curr_player));
                    value += weights[7];
                    value += (double)(weights[44] * circular_distance_7_3(getx(b.data.b_pawn_1),gety(b.data.b_pawn_1),getx(b.data.w_king),gety(b.data.w_king)));
                    value += (double)(weights[61] * int(b.get_pseudolegal_moves_for_piece(b.data.b_pawn_1).size()));
                }
                else if(b.data.b_pawn_1 & BISHOP){
                    value += weights[8] * !(under_threat(b,b.data.b_pawn_1,curr_player));
                    value += weights[9];
                    value += (double)(weights[45] * circular_distance_7_3(getx(b.data.b_pawn_1),gety(b.data.b_pawn_1),getx(b.data.w_king),gety(b.data.w_king)));
                    value += (double)(weights[62] * int(b.get_pseudolegal_moves_for_piece(b.data.b_pawn_1).size()));
                }
            }

            if(b.data.b_pawn_2 != DEAD){
                if(b.data.b_pawn_2 & PAWN){
                    value += weights[10] * !(under_threat(b,b.data.b_pawn_2,curr_player));
                    value += weights[11];
                    value += (double)(weights[46] * (circular_distance_7_3(getx(b.data.b_pawn_2),gety(b.data.b_pawn_2),2,0) + circular_distance_7_3(getx(b.data.b_pawn_2),gety(b.data.b_pawn_2),2,1)));
                    value += (double)(weights[63] * int(b.get_pseudolegal_moves_for_piece(b.data.b_pawn_2).size()));
                }
                else if(b.data.b_pawn_2 & ROOK){
                    value += weights[12] * !(under_threat(b,b.data.b_pawn_2,curr_player));
                    value += weights[13];
                    value += (double)(weights[47] * circular_distance_7_3(getx(b.data.b_pawn_2),gety(b.data.b_pawn_2),getx(b.data.w_king),gety(b.data.w_king)));
                    value += (double)(weights[64] * int(b.get_pseudolegal_moves_for_piece(b.data.b_pawn_2).size()));
                }
                else if(b.data.b_pawn_2 & BISHOP){
                    value += weights[14] * !(under_threat(b,b.data.b_pawn_2,curr_player));
                    value += weights[15];
                    value += (double)(weights[48] * circular_distance_7_3(getx(b.data.b_pawn_2),gety(b.data.b_pawn_2),getx(b.data.w_king),gety(b.data.w_king)));
                    value += (double)(weights[65] * int(b.get_pseudolegal_moves_for_piece(b.data.b_pawn_2).size()));
                }
            }
            if(!is_dead(b.data.b_rook_1)){
                value += (double)(weights[40] * circular_distance_7_3(getx(b.data.b_rook_1),gety(b.data.b_rook_1),getx(b.data.w_king),gety(b.data.w_king)));
                value += (double)(weights[66] * int(b.get_pseudolegal_moves_for_piece(b.data.b_rook_1).size()));
            }
            else{
                value += weights[16];
            }
            if(!is_dead(b.data.b_rook_2)){
                value += (double)(weights[41] * circular_distance_7_3(getx(b.data.b_rook_2),gety(b.data.b_rook_2),getx(b.data.w_king),gety(b.data.w_king)));
                value += (double)(weights[67] * int(b.get_pseudolegal_moves_for_piece(b.data.b_rook_2).size()));
            }
            else{
                value += weights[17];
            }
            if(!is_dead(b.data.b_bishop)){
                value += (double)(weights[42] * circular_distance_7_3(getx(b.data.b_bishop),gety(b.data.b_bishop),getx(b.data.w_king),gety(b.data.w_king)));
                value += (double)(weights[68] * int(b.get_pseudolegal_moves_for_piece(b.data.b_bishop).size()));
            }
            else{
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
                    value += (double)(weights[52] * (circular_distance_7_3(getx(b.data.w_pawn_1),gety(b.data.w_pawn_1),4,5) + circular_distance_7_3(getx(b.data.w_pawn_1),gety(b.data.w_pawn_1),4,6)));
                    value += (double)(weights[69] * int(b.get_pseudolegal_moves_for_piece(b.data.w_pawn_1).size()));
                }
                else if(b.data.w_pawn_1 & ROOK){
                    value += weights[25] * !(under_threat(b,b.data.w_pawn_1,curr_player));
                    value += weights[26];
                    value += (double)(weights[53] * circular_distance_7_3(getx(b.data.w_pawn_1),gety(b.data.w_pawn_1),getx(b.data.b_king),gety(b.data.b_king)));
                    value += (double)(weights[70] * int(b.get_pseudolegal_moves_for_piece(b.data.w_pawn_1).size()));
                }
                else if(b.data.w_pawn_1 & BISHOP){
                    value += weights[27] * !(under_threat(b,b.data.w_pawn_1,curr_player));
                    value += weights[28];
                    value += (double)(weights[54] * circular_distance_7_3(getx(b.data.w_pawn_1),gety(b.data.w_pawn_1),getx(b.data.b_king),gety(b.data.b_king)));
                    value += (double)(weights[71] * int(b.get_pseudolegal_moves_for_piece(b.data.w_pawn_1).size()));
                }
            }

            if(b.data.w_pawn_2 != DEAD){
                if(b.data.w_pawn_2 & PAWN){
                    value += weights[29] * !(under_threat(b,b.data.w_pawn_2,curr_player));
                    value += weights[30];
                    value += (double)(weights[55] * (circular_distance_7_3(getx(b.data.w_pawn_2),gety(b.data.w_pawn_2),4,5) + circular_distance_7_3(getx(b.data.w_pawn_2),gety(b.data.w_pawn_2),4,6)));
                    value += (double)(weights[72] * int(b.get_pseudolegal_moves_for_piece(b.data.w_pawn_2).size()));
                }
                else if(b.data.w_pawn_2 & ROOK){
                    value += weights[31] * !(under_threat(b,b.data.w_pawn_2,curr_player));
                    value += weights[32];
                    value += (double)(weights[56] * circular_distance_7_3(getx(b.data.w_pawn_2),gety(b.data.w_pawn_2),getx(b.data.b_king),gety(b.data.b_king)));
                    value += (double)(weights[73] * int(b.get_pseudolegal_moves_for_piece(b.data.w_pawn_2).size()));
                }
                else if(b.data.w_pawn_2 & BISHOP){
                    value += weights[33] * !(under_threat(b,b.data.w_pawn_2,curr_player));
                    value += weights[34];
                    value += (double)(weights[57] * circular_distance_7_3(getx(b.data.w_pawn_2),gety(b.data.w_pawn_2),getx(b.data.b_king),gety(b.data.b_king)));
                    value += (double)(weights[74] * int(b.get_pseudolegal_moves_for_piece(b.data.w_pawn_2).size()));
                }
            }
            if(!is_dead(b.data.w_rook_1)){
                value += (double)(weights[49] * circular_distance_7_3(getx(b.data.w_rook_1),gety(b.data.w_rook_1),getx(b.data.b_king),gety(b.data.b_king)));
                value += (double)(weights[75] * int(b.get_pseudolegal_moves_for_piece(b.data.w_rook_1).size()));
            }
            else{
                value += weights[35];
            }
            if(!is_dead(b.data.w_rook_2)){
                value += (double)(weights[50] * circular_distance_7_3(getx(b.data.w_rook_2),gety(b.data.w_rook_2),getx(b.data.b_king),gety(b.data.b_king)));
                value += (double)(weights[76] * int(b.get_pseudolegal_moves_for_piece(b.data.w_rook_2).size()));
            }
            else{
                value += weights[36];
            }
            if(!is_dead(b.data.w_bishop)){
                value += (double)(weights[51] * circular_distance_7_3(getx(b.data.w_bishop),gety(b.data.w_bishop),getx(b.data.b_king),gety(b.data.b_king)));
                value += (double)(weights[77] * int(b.get_pseudolegal_moves_for_piece(b.data.w_bishop).size()));
            }
            else{
                value += weights[37];
            }

            value += (double)(weights[39] * int(b.get_legal_moves().size()));

            value += (double)(weights[58] * ((b.get_legal_moves().size() == 0) && (!b.in_check())));
            
            b.flip_player_();

        }

        return value;

    }

    void weight_update(Board &b, double target, double learning_rate, int state_count = 0){
    
        auto curr_player = b.data.player_to_play;

        auto error = target - state_evaluation(b,state_count);

        bias[0] += learning_rate * error;

        weights[59] += learning_rate * error * state_count;

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
                    weights[43] += learning_rate * error * (circular_distance_7_3(getx(b.data.w_pawn_1),gety(b.data.w_pawn_1),4,5) + circular_distance_7_3(getx(b.data.w_pawn_1),gety(b.data.w_pawn_1),4,6));
                    weights[60] += learning_rate * error * int(b.get_pseudolegal_moves_for_piece(b.data.w_pawn_1).size());
                }
                else if(b.data.w_pawn_1 & ROOK){
                    weights[6] += learning_rate * error * !(under_threat(b,b.data.w_pawn_1,curr_player));
                    weights[7] += learning_rate * error;
                    // weights[44] += learning_rate * error * circular_distance_7_3(getx(b.data.w_pawn_1),gety(b.data.w_pawn_1),getx(b.data.b_king),gety(b.data.b_king));
                    weights[61] += learning_rate * error * int(b.get_pseudolegal_moves_for_piece(b.data.w_pawn_1).size());
                }
                else if(b.data.w_pawn_1 & BISHOP){
                    weights[8] += learning_rate * error * !(under_threat(b,b.data.w_pawn_1,curr_player));
                    weights[9] += learning_rate * error;
                    // weights[45] += learning_rate * error * circular_distance_7_3(getx(b.data.w_pawn_1),gety(b.data.w_pawn_1),getx(b.data.b_king),gety(b.data.b_king));
                    weights[62] += learning_rate * error * int(b.get_pseudolegal_moves_for_piece(b.data.w_pawn_1).size());
                }
            }

            if(b.data.w_pawn_2 != DEAD){
                if(b.data.w_pawn_2 & PAWN){
                    weights[10] += learning_rate * error * !(under_threat(b,b.data.w_pawn_2,curr_player));
                    weights[11] += learning_rate * error;
                    weights[46] += learning_rate * error * (circular_distance_7_3(getx(b.data.w_pawn_2),gety(b.data.w_pawn_2),4,5) + circular_distance_7_3(getx(b.data.w_pawn_2),gety(b.data.w_pawn_2),4,6));
                    weights[63] += learning_rate * error * int(b.get_pseudolegal_moves_for_piece(b.data.w_pawn_2).size());
                }
                else if(b.data.w_pawn_2 & ROOK){
                    weights[12] += learning_rate * error * !(under_threat(b,b.data.w_pawn_2,curr_player));
                    weights[13] += learning_rate * error;
                    // weights[47] += learning_rate * error * circular_distance_7_3(getx(b.data.w_pawn_2),gety(b.data.w_pawn_2),getx(b.data.b_king),gety(b.data.b_king));
                    weights[64] += learning_rate * error * int(b.get_pseudolegal_moves_for_piece(b.data.w_pawn_2).size());
                }
                else if(b.data.w_pawn_2 & BISHOP){
                    weights[14] += learning_rate * error * !(under_threat(b,b.data.w_pawn_2,curr_player));
                    weights[15] += learning_rate * error;
                    // weights[48] += learning_rate * error * circular_distance_7_3(getx(b.data.w_pawn_2),gety(b.data.w_pawn_2),getx(b.data.b_king),gety(b.data.b_king));
                    weights[65] += learning_rate * error * int(b.get_pseudolegal_moves_for_piece(b.data.w_pawn_2).size());
                }
            }

            if(!is_dead(b.data.w_rook_1)){
                // weights[40] += learning_rate * error * circular_distance_7_3(getx(b.data.w_rook_1),gety(b.data.w_rook_1),getx(b.data.b_king),gety(b.data.b_king));
                weights[66] += learning_rate * error * int(b.get_pseudolegal_moves_for_piece(b.data.w_rook_1).size());
            }
            else{
                weights[16] += learning_rate * error;
            }
            if(!is_dead(b.data.w_rook_2)){
                // weights[41] += learning_rate * error * circular_distance_7_3(getx(b.data.w_rook_2),gety(b.data.w_rook_2),getx(b.data.b_king),gety(b.data.b_king));
                weights[67] += learning_rate * error * int(b.get_pseudolegal_moves_for_piece(b.data.w_rook_2).size());
            }
            else{
                weights[17] += learning_rate * error;
            }
            if(!is_dead(b.data.w_bishop)){
                // weights[42] += learning_rate * error * circular_distance_7_3(getx(b.data.w_bishop),gety(b.data.w_bishop),getx(b.data.b_king),gety(b.data.b_king));
                weights[68] += learning_rate * error * int(b.get_pseudolegal_moves_for_piece(b.data.w_bishop).size());
            }
            else{
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
                    weights[52] += learning_rate * error * (circular_distance_7_3(getx(b.data.b_pawn_1),gety(b.data.b_pawn_1),2,0) + circular_distance_7_3(getx(b.data.b_pawn_1),gety(b.data.b_pawn_1),2,1));
                    weights[69] += learning_rate * error * int(b.get_pseudolegal_moves_for_piece(b.data.b_pawn_1).size());
                }
                else if(b.data.b_pawn_1 & ROOK){
                    weights[25] += learning_rate * error * !(under_threat(b,b.data.b_pawn_1,curr_player));
                    weights[26] += learning_rate * error;
                    // weights[53] += learning_rate * error * circular_distance_7_3(getx(b.data.b_pawn_1),gety(b.data.b_pawn_1),getx(b.data.w_king),gety(b.data.w_king));
                    weights[70] += learning_rate * error * int(b.get_pseudolegal_moves_for_piece(b.data.b_pawn_1).size());
                }
                else if(b.data.b_pawn_1 & BISHOP){
                    weights[27] += learning_rate * error * !(under_threat(b,b.data.b_pawn_1,curr_player));
                    weights[28] += learning_rate * error;
                    // weights[54] += learning_rate * error * circular_distance_7_3(getx(b.data.b_pawn_1),gety(b.data.b_pawn_1),getx(b.data.w_king),gety(b.data.w_king));
                    weights[71] += learning_rate * error * int(b.get_pseudolegal_moves_for_piece(b.data.b_pawn_1).size());
                }
            }

            if(b.data.b_pawn_2 != DEAD){
                if(b.data.b_pawn_2 & PAWN){
                    weights[29] += learning_rate * error * !(under_threat(b,b.data.b_pawn_2,curr_player));
                    weights[30] += learning_rate * error;
                    weights[55] += learning_rate * error * (circular_distance_7_3(getx(b.data.b_pawn_2),gety(b.data.b_pawn_2),2,0) + circular_distance_7_3(getx(b.data.b_pawn_2),gety(b.data.b_pawn_2),2,1));
                    weights[72] += learning_rate * error * int(b.get_pseudolegal_moves_for_piece(b.data.b_pawn_2).size());
                }
                else if(b.data.b_pawn_2 & ROOK){
                    weights[31] += learning_rate * error * !(under_threat(b,b.data.b_pawn_2,curr_player));
                    weights[32] += learning_rate * error;
                    // weights[56] += learning_rate * error * circular_distance_7_3(getx(b.data.b_pawn_2),gety(b.data.b_pawn_2),getx(b.data.w_king),gety(b.data.w_king));
                    weights[73] += learning_rate * error * int(b.get_pseudolegal_moves_for_piece(b.data.b_pawn_2).size());
                }
                else if(b.data.b_pawn_2 & BISHOP){
                    weights[33] += learning_rate * error * !(under_threat(b,b.data.b_pawn_2,curr_player));
                    weights[34] += learning_rate * error;
                    // weights[57] += learning_rate * error * circular_distance_7_3(getx(b.data.b_pawn_2),gety(b.data.b_pawn_2),getx(b.data.w_king),gety(b.data.w_king));
                    weights[74] += learning_rate * error * int(b.get_pseudolegal_moves_for_piece(b.data.b_pawn_2).size());
                }
            }
            if(!is_dead(b.data.b_rook_1)){
                // weights[49] += learning_rate * error * circular_distance_7_3(getx(b.data.b_rook_1),gety(b.data.b_rook_1),getx(b.data.w_king),gety(b.data.w_king));
                weights[75] += learning_rate * error * int(b.get_pseudolegal_moves_for_piece(b.data.b_rook_1).size());
            }
            else{
                weights[35] += learning_rate * error;
            }
            if(!is_dead(b.data.b_rook_2)){
                // weights[50] += learning_rate * error * circular_distance_7_3(getx(b.data.b_rook_2),gety(b.data.b_rook_2),getx(b.data.w_king),gety(b.data.w_king));
                weights[76] += learning_rate * error * int(b.get_pseudolegal_moves_for_piece(b.data.b_rook_2).size());
            }
            else{
                weights[36] += learning_rate * error;
            }
            if(!is_dead(b.data.b_bishop)){
                // weights[51] += learning_rate * error * circular_distance_7_3(getx(b.data.b_bishop),gety(b.data.b_bishop),getx(b.data.w_king),gety(b.data.w_king));
                weights[77] += learning_rate * error * int(b.get_pseudolegal_moves_for_piece(b.data.b_bishop).size());
            }
            else{
                weights[37] += learning_rate * error;
            }
            
            weights[39] += learning_rate * (double)(error * int(b.get_legal_moves().size()));

            weights[58] += learning_rate * (double)(error * ((b.get_legal_moves().size() == 0) && (!b.in_check())));

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
                    weights[43] += learning_rate * error * circular_distance_7_3(getx(b.data.b_pawn_1),gety(b.data.b_pawn_1),2,0) + circular_distance_7_3(getx(b.data.b_pawn_1),gety(b.data.b_pawn_1),2,1);
                    weights[60] += learning_rate * error * int(b.get_pseudolegal_moves_for_piece(b.data.b_pawn_1).size());
                }
                else if(b.data.b_pawn_1 & ROOK){
                    weights[6] += learning_rate * error * !(under_threat(b,b.data.b_pawn_1,curr_player));
                    weights[7] += learning_rate * error;
                    // weights[44] += learning_rate * error * circular_distance_7_3(getx(b.data.b_pawn_1),gety(b.data.b_pawn_1),getx(b.data.w_king),gety(b.data.w_king));
                    weights[61] += learning_rate * error * int(b.get_pseudolegal_moves_for_piece(b.data.b_pawn_1).size());
                }
                else if(b.data.b_pawn_1 & BISHOP){
                    weights[8] += learning_rate * error * !(under_threat(b,b.data.b_pawn_1,curr_player));
                    weights[9] += learning_rate * error;
                    // weights[45] += learning_rate * error * circular_distance_7_3(getx(b.data.b_pawn_1),gety(b.data.b_pawn_1),getx(b.data.w_king),gety(b.data.w_king));
                    weights[62] += learning_rate * error * int(b.get_pseudolegal_moves_for_piece(b.data.b_pawn_1).size());
                }
            }

            if(b.data.b_pawn_2 != DEAD){
                if(b.data.b_pawn_2 & PAWN){
                    weights[10] += learning_rate * error * !(under_threat(b,b.data.b_pawn_2,curr_player));
                    weights[11] += learning_rate * error;
                    weights[46] += learning_rate * error * circular_distance_7_3(getx(b.data.b_pawn_2),gety(b.data.b_pawn_2),2,0) + circular_distance_7_3(getx(b.data.b_pawn_2),gety(b.data.b_pawn_2),2,1);
                    weights[63] += learning_rate * error * int(b.get_pseudolegal_moves_for_piece(b.data.b_pawn_2).size());
                }
                else if(b.data.b_pawn_2 & ROOK){
                    weights[12] += learning_rate * error * !(under_threat(b,b.data.b_pawn_2,curr_player));
                    weights[13] += learning_rate * error;
                    // weights[47] += learning_rate * error * circular_distance_7_3(getx(b.data.b_pawn_2),gety(b.data.b_pawn_2),getx(b.data.w_king),gety(b.data.w_king));
                    weights[64] += learning_rate * error * int(b.get_pseudolegal_moves_for_piece(b.data.b_pawn_2).size());
                }
                else if(b.data.b_pawn_2 & BISHOP){
                    weights[14] += learning_rate * error * !(under_threat(b,b.data.b_pawn_2,curr_player));
                    weights[15] += learning_rate * error;
                    // weights[48] += learning_rate * error * circular_distance_7_3(getx(b.data.b_pawn_2),gety(b.data.b_pawn_2),getx(b.data.w_king),gety(b.data.w_king));
                    weights[65] += learning_rate * error * int(b.get_pseudolegal_moves_for_piece(b.data.b_pawn_2).size());
                }
            }
            if(!is_dead(b.data.b_rook_1)){
                // weights[40] += learning_rate * error * circular_distance_7_3(getx(b.data.b_rook_1),gety(b.data.b_rook_1),getx(b.data.w_king),gety(b.data.w_king));
                weights[66] += learning_rate * error * int(b.get_pseudolegal_moves_for_piece(b.data.b_rook_1).size());
            }
            else{
                weights[16] += learning_rate * error;
            }
            if(!is_dead(b.data.b_rook_2)){
                // weights[41] += learning_rate * error * circular_distance_7_3(getx(b.data.b_rook_2),gety(b.data.b_rook_2),getx(b.data.w_king),gety(b.data.w_king));
                weights[67] += learning_rate * error * int(b.get_pseudolegal_moves_for_piece(b.data.b_rook_2).size());
            }
            else{
                weights[17] += learning_rate * error;
            }
            if(!is_dead(b.data.b_bishop)){
                // weights[42] += learning_rate * error * circular_distance_7_3(getx(b.data.b_bishop),gety(b.data.b_bishop),getx(b.data.w_king),gety(b.data.w_king));
                weights[68] += learning_rate * error * int(b.get_pseudolegal_moves_for_piece(b.data.b_bishop).size());
            }
            else{
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
                    weights[52] += learning_rate * error * (circular_distance_7_3(getx(b.data.w_pawn_1),gety(b.data.w_pawn_1),4,5) + circular_distance_7_3(getx(b.data.w_pawn_1),gety(b.data.w_pawn_1),4,6));
                    weights[69] += learning_rate * error * int(b.get_pseudolegal_moves_for_piece(b.data.w_pawn_1).size());
                }
                else if(b.data.w_pawn_1 & ROOK){
                    weights[25] += learning_rate * error * !(under_threat(b,b.data.w_pawn_1,curr_player));
                    weights[26] += learning_rate * error;
                    // weights[53] += learning_rate * error * circular_distance_7_3(getx(b.data.w_pawn_1),gety(b.data.w_pawn_1),getx(b.data.b_king),gety(b.data.b_king));
                    weights[70] += learning_rate * error * int(b.get_pseudolegal_moves_for_piece(b.data.w_pawn_1).size());
                }
                else if(b.data.w_pawn_1 & BISHOP){
                    weights[27] += learning_rate * error * !(under_threat(b,b.data.w_pawn_1,curr_player));
                    weights[28] += learning_rate * error;
                    // weights[54] += learning_rate * error * circular_distance_7_3(getx(b.data.w_pawn_1),gety(b.data.w_pawn_1),getx(b.data.b_king),gety(b.data.b_king));
                    weights[71] += learning_rate * error * int(b.get_pseudolegal_moves_for_piece(b.data.w_pawn_1).size());
                }
            }

            if(b.data.w_pawn_2 != DEAD){
                if(b.data.w_pawn_2 & PAWN){
                    weights[29] += learning_rate * error * !(under_threat(b,b.data.w_pawn_2,curr_player));
                    weights[30] += learning_rate * error;
                    weights[55] += learning_rate * error * (circular_distance_7_3(getx(b.data.w_pawn_2),gety(b.data.w_pawn_2),4,5) + circular_distance_7_3(getx(b.data.w_pawn_2),gety(b.data.w_pawn_2),4,6));
                    weights[72] += learning_rate * error * int(b.get_pseudolegal_moves_for_piece(b.data.w_pawn_2).size());
                }
                else if(b.data.w_pawn_2 & ROOK){
                    weights[31] += learning_rate * error * !(under_threat(b,b.data.w_pawn_2,curr_player));
                    weights[32] += learning_rate * error;
                    // weights[56] += learning_rate * error * circular_distance_7_3(getx(b.data.w_pawn_2),gety(b.data.w_pawn_2),getx(b.data.b_king),gety(b.data.b_king));
                    weights[73] += learning_rate * error * int(b.get_pseudolegal_moves_for_piece(b.data.w_pawn_2).size());
                }
                else if(b.data.w_pawn_2 & BISHOP){
                    weights[33] += learning_rate * error * !(under_threat(b,b.data.w_pawn_2,curr_player));
                    weights[34] += learning_rate * error;
                    // weights[57] += learning_rate * error * circular_distance_7_3(getx(b.data.w_pawn_2),gety(b.data.w_pawn_2),getx(b.data.b_king),gety(b.data.b_king));
                    weights[74] += learning_rate * error * int(b.get_pseudolegal_moves_for_piece(b.data.w_pawn_2).size());
                }
            }
            if(!is_dead(b.data.w_rook_1)){
                // weights[49] += learning_rate * error * circular_distance_7_3(getx(b.data.w_rook_1),gety(b.data.w_rook_1),getx(b.data.b_king),gety(b.data.b_king));
                weights[75] += learning_rate * error * int(b.get_pseudolegal_moves_for_piece(b.data.w_rook_1).size());
            }
            else{
                weights[35] += learning_rate * error;
            }
            if(!is_dead(b.data.w_rook_2)){
                // weights[50] += learning_rate * error * circular_distance_7_3(getx(b.data.w_rook_2),gety(b.data.w_rook_2),getx(b.data.b_king),gety(b.data.b_king));
                weights[76] += learning_rate * error * int(b.get_pseudolegal_moves_for_piece(b.data.w_rook_2).size());
            }
            else{
                weights[36] += learning_rate * error;
            }
            if(!is_dead(b.data.w_bishop)){
                // weights[51] += learning_rate * error * circular_distance_7_3(getx(b.data.w_bishop),gety(b.data.w_bishop),getx(b.data.b_king),gety(b.data.b_king));
                weights[77] += learning_rate * error * int(b.get_pseudolegal_moves_for_piece(b.data.w_bishop).size());
            }
            else{
                weights[37] += learning_rate * error;
            }

            weights[39] += learning_rate * (double)(error * int(b.get_legal_moves().size()));

            weights[58] += learning_rate * (double)(error * ((b.get_legal_moves().size() == 0) && (!b.in_check())));

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

    double circular_distance_7_3(int x1, int y1, int x2, int y2){
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
        return 0;
        // return abs(x1-x2) + abs(y1-y2);
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
            learningRate = 0.001;
            discountFactor = 0.9;
            trainstep = 1;

    }

    double state_evaluation(Board& b, U16 move, std::map<std::string,int>& board_count){ // Q(s,a)

        b.do_move_without_flip_(move);
        double score = fn.state_evaluation(b,board_count[board_encode(b)]);
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

        fn.weight_update(state,reward + discountFactor * next_q_val,learningRate/((double)trainstep),board_count[board_encode(state)]);
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
