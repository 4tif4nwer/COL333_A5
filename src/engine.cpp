#include "engine.hpp"
#include <map>
#include<unordered_set>
#include <float.h>
#include "board.hpp"
#include "butils.hpp"

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

    b.flip_player_();
    if(b.get_legal_moves().size() == 0 && b.in_check()){
        reward = 1000;
        b.flip_player_();
        return reward;
    }
    b.flip_player_();
    return 0;
}

class function_approximator{

    public:

    std::unordered_set<U16> pseudolegal_moves;

    function_approximator(){}

    function_approximator(BoardType board_type){
        
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

        read_weights(board_type);

        return;

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
            value += weights[66] * under_threat(b,b.data.w_knight_1,curr_player);
            value += weights[67] * under_threat(b,b.data.w_knight_2,curr_player);

            if(b.data.w_pawn_1 != DEAD){
                if(b.data.w_pawn_1 & PAWN){
                    value += weights[4] * !(under_threat(b,b.data.w_pawn_1,curr_player));
                    value += weights[5];
                    value += (double)(-0.00001 * (manhattan_distance(getx(b.data.w_pawn_1),gety(b.data.w_pawn_1),4,5) + manhattan_distance(getx(b.data.w_pawn_1),gety(b.data.w_pawn_1),4,6) + manhattan_distance(getx(b.data.w_pawn_1),gety(b.data.w_pawn_1),4,7)));
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
                    value += (double)(-0.00001 * (manhattan_distance(getx(b.data.w_pawn_2),gety(b.data.w_pawn_2),4,5) + manhattan_distance(getx(b.data.w_pawn_2),gety(b.data.w_pawn_2),4,6) + manhattan_distance(getx(b.data.w_pawn_2),gety(b.data.w_pawn_2),4,7)));
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
                    value += (double)(-0.00001 * (manhattan_distance(getx(b.data.w_pawn_3),gety(b.data.w_pawn_3),4,5) + manhattan_distance(getx(b.data.w_pawn_3),gety(b.data.w_pawn_3),4,6) + manhattan_distance(getx(b.data.w_pawn_3),gety(b.data.w_pawn_3),4,7)));
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
                    value += (double)(-0.00001 * (manhattan_distance(getx(b.data.w_pawn_4),gety(b.data.w_pawn_4),4,5) + manhattan_distance(getx(b.data.w_pawn_4),gety(b.data.w_pawn_4),4,6) + manhattan_distance(getx(b.data.w_pawn_4),gety(b.data.w_pawn_4),4,7)));
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
            value += weights[20] * under_threat(b,b.data.b_rook_1,curr_player);
            value += weights[21] * under_threat(b,b.data.b_rook_2,curr_player);
            value += weights[22] * under_threat(b,b.data.b_bishop,curr_player);
            value += weights[70] * under_threat(b,b.data.b_knight_1,curr_player);
            value += weights[71] * under_threat(b,b.data.b_knight_2,curr_player);

            if(b.data.b_pawn_1 != DEAD){
                if(b.data.b_pawn_1 & PAWN){
                    value += weights[23] * !(under_threat(b,b.data.b_pawn_1,curr_player));
                    value += weights[24];
                    value += (double)(0.00001 * (manhattan_distance(getx(b.data.b_pawn_1),gety(b.data.b_pawn_1),3,0) + manhattan_distance(getx(b.data.b_pawn_1),gety(b.data.b_pawn_1),3,1) + manhattan_distance(getx(b.data.b_pawn_1),gety(b.data.b_pawn_1),3,2)));
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
                    value += (double)(0.00001 * (manhattan_distance(getx(b.data.b_pawn_2),gety(b.data.b_pawn_2),3,0) + manhattan_distance(getx(b.data.b_pawn_2),gety(b.data.b_pawn_2),3,1) + manhattan_distance(getx(b.data.b_pawn_2),gety(b.data.b_pawn_2),3,2)));
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
                    value += (double)(0.00001 * (manhattan_distance(getx(b.data.b_pawn_3),gety(b.data.b_pawn_3),3,0) + manhattan_distance(getx(b.data.b_pawn_3),gety(b.data.b_pawn_3),3,1) + manhattan_distance(getx(b.data.b_pawn_3),gety(b.data.b_pawn_3),3,2)));
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
                    value += (double)(0.00001 * (manhattan_distance(getx(b.data.b_pawn_4),gety(b.data.b_pawn_4),3,0) + manhattan_distance(getx(b.data.b_pawn_4),gety(b.data.b_pawn_4),3,1) + manhattan_distance(getx(b.data.b_pawn_4),gety(b.data.b_pawn_4),3,2)));
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
        else{

            pseudolegal_moves = b.get_pseudolegal_moves_for_side(b.data.player_to_play ^ (WHITE | BLACK));
            
            value += weights[0] * b.in_check();
            value += weights[1] * under_threat(b,b.data.b_rook_1,curr_player);
            value += weights[2] * under_threat(b,b.data.b_rook_2,curr_player);
            value += weights[3] * under_threat(b,b.data.b_bishop,curr_player);
            value += weights[66] * under_threat(b,b.data.b_knight_1,curr_player);
            value += weights[67] * under_threat(b,b.data.b_knight_2,curr_player);

            if(b.data.b_pawn_1 != DEAD){
                if(b.data.b_pawn_1 & PAWN){
                    value += weights[4] * !(under_threat(b,b.data.b_pawn_1,curr_player));
                    value += weights[5];
                    value += (double)(-0.00001 * (manhattan_distance(getx(b.data.b_pawn_1),gety(b.data.b_pawn_1),3,0) + manhattan_distance(getx(b.data.b_pawn_1),gety(b.data.b_pawn_1),3,1) + manhattan_distance(getx(b.data.b_pawn_1),gety(b.data.b_pawn_1),3,2)));
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
                    value += (double)(-0.00001 * (manhattan_distance(getx(b.data.b_pawn_2),gety(b.data.b_pawn_2),3,0) + manhattan_distance(getx(b.data.b_pawn_2),gety(b.data.b_pawn_2),3,1) + manhattan_distance(getx(b.data.b_pawn_2),gety(b.data.b_pawn_2),3,2)));
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
                    value += (double)(-0.00001 * (manhattan_distance(getx(b.data.b_pawn_3),gety(b.data.b_pawn_3),3,0) + manhattan_distance(getx(b.data.b_pawn_3),gety(b.data.b_pawn_3),3,1) + manhattan_distance(getx(b.data.b_pawn_3),gety(b.data.b_pawn_3),3,2)));
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
                    value += (double)(-0.00001 * (manhattan_distance(getx(b.data.b_pawn_4),gety(b.data.b_pawn_4),3,0) + manhattan_distance(getx(b.data.b_pawn_4),gety(b.data.b_pawn_4),3,1) + manhattan_distance(getx(b.data.b_pawn_4),gety(b.data.b_pawn_4),3,2)));
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
            value += weights[20] * under_threat(b,b.data.w_rook_1,curr_player);
            value += weights[21] * under_threat(b,b.data.w_rook_2,curr_player);
            value += weights[22] * under_threat(b,b.data.w_bishop,curr_player);
            value += weights[70] * under_threat(b,b.data.w_knight_1,curr_player);
            value += weights[71] * under_threat(b,b.data.w_knight_2,curr_player);

            if(b.data.w_pawn_1 != DEAD){
                if(b.data.w_pawn_1 & PAWN){
                    value += weights[23] * !(under_threat(b,b.data.w_pawn_1,curr_player));
                    value += weights[24];
                    value += (double)(0.00001 * (manhattan_distance(getx(b.data.w_pawn_1),gety(b.data.w_pawn_1),4,5) + manhattan_distance(getx(b.data.w_pawn_1),gety(b.data.w_pawn_1),4,6) + manhattan_distance(getx(b.data.w_pawn_1),gety(b.data.w_pawn_1),4,7)));
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
                    value += (double)(0.00001 * (manhattan_distance(getx(b.data.w_pawn_2),gety(b.data.w_pawn_2),4,5) + manhattan_distance(getx(b.data.w_pawn_2),gety(b.data.w_pawn_2),4,6) + manhattan_distance(getx(b.data.w_pawn_2),gety(b.data.w_pawn_2),4,7)));
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
                    value += (double)(0.00001 * (manhattan_distance(getx(b.data.w_pawn_3),gety(b.data.w_pawn_3),4,5) + manhattan_distance(getx(b.data.w_pawn_3),gety(b.data.w_pawn_3),4,6) + manhattan_distance(getx(b.data.w_pawn_3),gety(b.data.w_pawn_3),4,7)));
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
                    value += (double)(0.00001 * (manhattan_distance(getx(b.data.w_pawn_4),gety(b.data.w_pawn_4),4,5) + manhattan_distance(getx(b.data.w_pawn_4),gety(b.data.w_pawn_4),4,6) + manhattan_distance(getx(b.data.w_pawn_4),gety(b.data.w_pawn_4),4,7)));
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
            weights[66] += learning_rate * error * under_threat(b,b.data.w_knight_1,curr_player);
            weights[67] += learning_rate * error * under_threat(b,b.data.w_knight_2,curr_player);

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
            weights[20] += learning_rate * error * under_threat(b,b.data.b_rook_1,curr_player);
            weights[21] += learning_rate * error * under_threat(b,b.data.b_rook_2,curr_player);
            weights[22] += learning_rate * error * under_threat(b,b.data.b_bishop,curr_player);
            weights[70] += learning_rate * error * under_threat(b,b.data.b_knight_1,curr_player);
            weights[71] += learning_rate * error * under_threat(b,b.data.b_knight_2,curr_player);

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
        else{

            pseudolegal_moves = b.get_pseudolegal_moves_for_side(b.data.player_to_play ^ (WHITE | BLACK));
            
            weights[0] += learning_rate * error * b.in_check();
            weights[1] += learning_rate * error * under_threat(b,b.data.b_rook_1,curr_player);
            weights[2] += learning_rate * error * under_threat(b,b.data.b_rook_2,curr_player);
            weights[3] += learning_rate * error * under_threat(b,b.data.b_bishop,curr_player);
            weights[66] += learning_rate * error * under_threat(b,b.data.b_knight_1,curr_player);
            weights[67] += learning_rate * error * under_threat(b,b.data.b_knight_2,curr_player);

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
                if(b.data.b_pawn_4 & PAWN){
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
            weights[20] += learning_rate * error * under_threat(b,b.data.w_rook_1,curr_player);
            weights[21] += learning_rate * error * under_threat(b,b.data.w_rook_2,curr_player);
            weights[22] += learning_rate * error * under_threat(b,b.data.w_bishop,curr_player);
            weights[70] += learning_rate * error * under_threat(b,b.data.w_knight_1,curr_player);
            weights[71] += learning_rate * error * under_threat(b,b.data.w_knight_2,curr_player);

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
                    value += (double)(-0.00001 * (manhattan_distance(getx(b.data.w_pawn_1),gety(b.data.w_pawn_1),5,6) + manhattan_distance(getx(b.data.w_pawn_1),gety(b.data.w_pawn_1),5,7)));
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
                    value += (double)(-0.00001 * (manhattan_distance(getx(b.data.w_pawn_2),gety(b.data.w_pawn_2),5,6) + manhattan_distance(getx(b.data.w_pawn_2),gety(b.data.w_pawn_2),5,7)));
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
                    value += (double)(0.00001 * (manhattan_distance(getx(b.data.w_pawn_1),gety(b.data.w_pawn_1),5,6) + manhattan_distance(getx(b.data.w_pawn_1),gety(b.data.w_pawn_1),5,7)));
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
                    value += (double)(0.00001 * (manhattan_distance(getx(b.data.w_pawn_2),gety(b.data.w_pawn_2),5,6) + manhattan_distance(getx(b.data.w_pawn_2),gety(b.data.w_pawn_2),5,7)));
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
                if(b.data.b_pawn_4 & PAWN){
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
        return (x1-x2) * (x1-x2) + (y1-y2) * (y1-y2);
    }

    void read_weights(BoardType board_type){

        if(board_type == SEVEN_THREE){
            weights[0] = std::stod("-0x1.691e16ddf74bp+1");
            weights[1] = std::stod("-0x1.97d25b7862081p+2");
            weights[2] = std::stod("-0x1.6c4607bc3a31cp+2");
            weights[3] = std::stod("-0x1.3b3793b7b4045p+2");
            weights[4] = std::stod("0x1.828a2aff95b7p-1");
            weights[5] = std::stod("0x1.f83ad5f308ca1p-2");
            weights[6] = std::stod("0x1.1cfa1c7462188p+2");
            weights[7] = std::stod("0x1.174dee739f14ep+1");
            weights[8] = std::stod("0x1.52c677806f607p+1");
            weights[9] = std::stod("0x1.9126afedc27e7p+1");
            weights[10] = std::stod("0x1.1bb29cbbc792dp+0");
            weights[11] = std::stod("0x1.1939b3a3b1cc2p+0");
            weights[12] = std::stod("0x1.6d239ab1a875dp+2");
            weights[13] = std::stod("0x1.18ad0466ddbp+2");
            weights[14] = std::stod("0x1.0372db613073fp+2");
            weights[15] = std::stod("0x1.9100cf88be44p+1");
            weights[16] = std::stod("-0x1.dd77b5f719bb8p+1");
            weights[17] = std::stod("-0x1.beba0a7a6cb54p+1");
            weights[18] = std::stod("-0x1.ee89bb0867734p-2");
            weights[19] = std::stod("0x1.128025fbbf276p+3");
            weights[20] = std::stod("0x1.76de0f9e8b908p+1");
            weights[21] = std::stod("0x1.02897ff707db5p+0");
            weights[22] = std::stod("0x1.dac037f1cdad3p+1");
            weights[23] = std::stod("-0x1.40bdaa54137aep+1");
            weights[24] = std::stod("-0x1.ce30abd9137c6p+0");
            weights[25] = std::stod("-0x1.86eb21e43cc75p+2");
            weights[26] = std::stod("-0x1.b8d75cc4f7f21p+2");
            weights[27] = std::stod("-0x1.51f97cbab6a66p+1");
            weights[28] = std::stod("-0x1.81a55b68b63cap+0");
            weights[29] = std::stod("-0x1.16050c1929152p+1");
            weights[30] = std::stod("-0x1.31b7a3117483fp+0");
            weights[31] = std::stod("-0x1.9337459d22fd6p+2");
            weights[32] = std::stod("-0x1.8910a109b126cp+2");
            weights[33] = std::stod("-0x1.b0dc79147128fp+1");
            weights[34] = std::stod("-0x1.95e6fb2c56bcap+1");
            weights[35] = std::stod("0x1.a19479e845a1ap+2");
            weights[36] = std::stod("0x1.072f7b7b179c7p+1");
            weights[37] = std::stod("0x1.55e82b9a4ca1dp+0");
            weights[38] = std::stod("0x1.1c236b6fe2feep+3");
            weights[39] = std::stod("-0x1.0099a48c45e77p+4");
            weights[40] = std::stod("-0x1.eb3c3c07aeaa6p+5");
            weights[41] = std::stod("-0x1.1969a02acad86p+7");
            bias[0] = std::stod("0x1.0d3947c0237bep+6");
            
        }
        else if(board_type == EIGHT_TWO){
            weights[0] = std::stod("-0x1.691e16ddf74bp+1");
            weights[1] = std::stod("-0x1.9640246f95f64p+2");
            weights[2] = std::stod("-0x1.6d765e4a89837p+2");
            weights[3] = std::stod("-0x1.305a626776a86p+2");
            weights[4] = std::stod("0x1.a324fd81b9116p-3");
            weights[5] = std::stod("-0x1.42ac83c49ab57p-5");
            weights[6] = std::stod("0x1.2afb42a03e064p+2");
            weights[7] = std::stod("0x1.351270993ca9bp+1");
            weights[8] = std::stod("0x1.590c7332b48f4p+1");
            weights[9] = std::stod("0x1.9791b9991867p+1");
            weights[10] = std::stod("0x1.25bb4ca36e8edp-1");
            weights[11] = std::stod("0x1.2d4077a4d0867p-1");
            weights[12] = std::stod("0x1.804966a978909p+2");
            weights[13] = std::stod("0x1.2d32bbf91dbf7p+2");
            weights[14] = std::stod("0x1.02415328835dp+2");
            weights[15] = std::stod("0x1.8f4e35df56b0cp+1");
            weights[16] = std::stod("-0x1.c0a5499ddd5dfp+1");
            weights[17] = std::stod("-0x1.a10720e56965bp+1");
            weights[18] = std::stod("-0x1.2416606ab650cp-2");
            weights[19] = std::stod("0x1.0544f18a20aa8p+3");
            weights[20] = std::stod("0x1.675a9a601ec0dp+1");
            weights[21] = std::stod("0x1.0210af54b34cdp+0");
            weights[22] = std::stod("0x1.b1c9b8a437f39p+1");
            weights[23] = std::stod("-0x1.16c344021ca5cp+1");
            weights[24] = std::stod("-0x1.815bd31bd5767p+0");
            weights[25] = std::stod("-0x1.aa0d9d78bd8ap+2");
            weights[26] = std::stod("-0x1.d9bbcd692dd97p+2");
            weights[27] = std::stod("-0x1.502655d6abbeep+1");
            weights[28] = std::stod("-0x1.7e40a26d5ce6p+0");
            weights[29] = std::stod("-0x1.d6558c8209552p+0");
            weights[30] = std::stod("-0x1.a3f0c719ac681p-1");
            weights[31] = std::stod("-0x1.bb6baf1da2514p+2");
            weights[32] = std::stod("-0x1.af7b1162fc702p+2");
            weights[33] = std::stod("-0x1.acd873eb52f46p+1");
            weights[34] = std::stod("-0x1.926f879403214p+1");
            weights[35] = std::stod("0x1.abfe16c12087ap+2");
            weights[36] = std::stod("0x1.147e240f37f77p+1");
            weights[37] = std::stod("0x1.7e186bc0db322p+0");
            weights[38] = std::stod("0x1.6e1a518ef0169p+1");
            weights[39] = std::stod("-0x1.6323a1f7b9657p+2");
            weights[40] = std::stod("-0x1.eb3df718d6efep+5");
            weights[41] = std::stod("-0x1.19403eff7415ap+7");
            weights[42] = std::stod("0x1.020451cb67d44p-1");
            weights[43] = std::stod("0x1.900d89ba2bb34p-3");
            weights[44] = std::stod("0x1.214ca4b3c897dp+2");
            weights[45] = std::stod("0x1.1ff67a2111e57p+1");
            weights[46] = std::stod("0x1.4f4a3d4d92b46p+1");
            weights[47] = std::stod("0x1.8ed7a52d1ab5dp+1");
            weights[48] = std::stod("-0x1.07a3c7cab0747p+0");
            weights[49] = std::stod("-0x1.8507061a44e1ep-1");
            weights[50] = std::stod("-0x1.1937b83893e99p+2");
            weights[51] = std::stod("-0x1.0eeb9c8ff503dp+1");
            weights[52] = std::stod("-0x1.4f7cdd1880e15p+1");
            weights[53] = std::stod("-0x1.8dc49c8fd04b1p+1");
            weights[54] = std::stod("0x1.802b0ffebdf05p-1");
            weights[55] = std::stod("0x1.f8aca82b731cbp-2");
            weights[56] = std::stod("0x1.10f02543c764ap+2");
            weights[57] = std::stod("0x1.fde60ffbf0e5p+0");
            weights[58] = std::stod("0x1.519fc609de399p+1");
            weights[59] = std::stod("0x1.8ff5be663ebe8p+1");
            weights[60] = std::stod("-0x1.6189d7cc01d3cp-1");
            weights[61] = std::stod("-0x1.a7d9871870eeep-2");
            weights[62] = std::stod("-0x1.2e1baa29c376p+2");
            weights[63] = std::stod("-0x1.388aaa0d6a74p+1");
            weights[64] = std::stod("-0x1.515fd9c3ad049p+1");
            weights[65] = std::stod("-0x1.8fbb644706d9cp+1");
            weights[66] = std::stod("-0x1.db51e5edec98dp+1");
            weights[67] = std::stod("-0x1.ebb415cf630a4p+1");
            weights[68] = std::stod("-0x1.cc595bd61cab1p+1");
            weights[69] = std::stod("-0x1.c9bdad6f5a71fp+1");
            weights[70] = std::stod("0x1.da539b4ea657cp+1");
            weights[71] = std::stod("0x1.c9ab9d60ee4c7p+1");
            weights[72] = std::stod("0x1.ee06112ce2754p+1");
            weights[73] = std::stod("0x1.003f651e1e41dp+2");
            bias[0] = std::stod("0x1.e3bfe4122fdb4p+4");


        }
        else{
            weights[0] = std::stod("-0x1.691e16ddf74bp+1");
            weights[1] = std::stod("-0x1.9a95dbb5f3d31p+2");
            weights[2] = std::stod("-0x1.71987f60505bfp+2");
            weights[3] = std::stod("-0x1.3e52cd382eca4p+2");
            weights[4] = std::stod("0x1.a33bdab3b66e3p-1");
            weights[5] = std::stod("0x1.f701bc0b25c85p-2");
            weights[6] = std::stod("0x1.1df90df306bb1p+2");
            weights[7] = std::stod("0x1.18f3d5bf08303p+1");
            weights[8] = std::stod("0x1.4a227c7ae9f01p+1");
            weights[9] = std::stod("0x1.8888d012c43d2p+1");
            weights[10] = std::stod("0x1.1849f59293b28p+0");
            weights[11] = std::stod("0x1.1981328fe265ep+0");
            weights[12] = std::stod("0x1.6e03c89dc7193p+2");
            weights[13] = std::stod("0x1.19738aecccd9fp+2");
            weights[14] = std::stod("0x1.069bc46cd70cdp+2");
            weights[15] = std::stod("0x1.9725747173b79p+1");
            weights[16] = std::stod("-0x1.c60c29e1b9b94p+1");
            weights[17] = std::stod("-0x1.a74a5cd6358e9p+1");
            weights[18] = std::stod("-0x1.32035366e03bfp-2");
            weights[19] = std::stod("0x1.115ab12c1212dp+3");
            weights[20] = std::stod("0x1.737eda79be272p+1");
            weights[21] = std::stod("0x1.eadb2734d7184p-1");
            weights[22] = std::stod("0x1.db50e7375942fp+1");
            weights[23] = std::stod("-0x1.3c29a42b1f2abp+1");
            weights[24] = std::stod("-0x1.d0719c5e71508p+0");
            weights[25] = std::stod("-0x1.872d59e966e19p+2");
            weights[26] = std::stod("-0x1.b93ffdbd5e6bp+2");
            weights[27] = std::stod("-0x1.5609a182ac73fp+1");
            weights[28] = std::stod("-0x1.89fe0ab8ebe29p+0");
            weights[29] = std::stod("-0x1.156a2e91fd9f3p+1");
            weights[30] = std::stod("-0x1.2f4343f44ef6bp+0");
            weights[31] = std::stod("-0x1.9292060e2292ep+2");
            weights[32] = std::stod("-0x1.886e5cdadb987p+2");
            weights[33] = std::stod("-0x1.ae0398b7353c5p+1");
            weights[34] = std::stod("-0x1.93f5e0d5798d4p+1");
            weights[35] = std::stod("0x1.ae49e29e5ab8p+2");
            weights[36] = std::stod("0x1.1f4efe8969c11p+1");
            weights[37] = std::stod("0x1.78b15e294a11bp+0");
            weights[38] = std::stod("0x1.048fa5ee5764cp+3");
            weights[39] = std::stod("-0x1.85eba57e95676p+3");
            weights[40] = std::stod("-0x1.eb3c4f3436352p+5");
            weights[41] = std::stod("-0x1.194c753c78178p+7");
            weights[42] = std::stod("0x1.7e6b8ae74d825p-1");
            weights[43] = std::stod("0x1.d8702938a01cep-2");
            weights[44] = std::stod("0x1.226021fd269c3p+2");
            weights[45] = std::stod("0x1.171de8318f4fdp+1");
            weights[46] = std::stod("0x1.51f4ffd6eb36p+1");
            weights[47] = std::stod("0x1.90301ccf73dd9p+1");
            weights[48] = std::stod("-0x1.87e015413a69ep-1");
            weights[49] = std::stod("-0x1.0583613b2bbedp-1");
            weights[50] = std::stod("-0x1.1e78657d6753cp+2");
            weights[51] = std::stod("-0x1.1c2ff2dc41965p+1");
            weights[52] = std::stod("-0x1.5165349cd216bp+1");
            weights[53] = std::stod("-0x1.8fbead91aa667p+1");
            weights[54] = std::stod("0x1.926b5d6420e7p-1");
            weights[55] = std::stod("0x1.ee489eede6a73p-2");
            weights[56] = std::stod("0x1.1e179acb50877p+2");
            weights[57] = std::stod("0x1.17949192055afp+1");
            weights[58] = std::stod("0x1.522fd254ca8cp+1");
            weights[59] = std::stod("0x1.908a6875b583p+1");
            weights[60] = std::stod("-0x1.6fb48fec0beaap-1");
            weights[61] = std::stod("-0x1.d2f623bdbe1adp-2");
            weights[62] = std::stod("-0x1.1db4206f33076p+2");
            weights[63] = std::stod("-0x1.1d1e18c0a59d5p+1");
            weights[64] = std::stod("-0x1.51645bcc12a39p+1");
            weights[65] = std::stod("-0x1.8fbe0aa975e2p+1");
            bias[0] = std::stod("0x1.89b1e639e82dcp+4");
        }

    }

};


class QLearningAgent {
public:
    QLearningAgent(BoardType board_type)
        : fn(board_type) {
            learningRate = 0.001;
            discountFactor = 0.9;
            trainstep = 1;
            board_type_set = true;
    }

    QLearningAgent(){
        board_type_set = false;
    }


    double state_evaluation(Board& b, U16 move, std::map<std::string,int>& board_count){ // Q(s,a)

        b.do_move_without_flip_(move);
        double score;
        if(b.data.board_type == SEVEN_THREE)
            score = fn.state_evaluation_7_3(b,board_count[board_encode(b)]);
        else if(b.data.board_type == EIGHT_FOUR)
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

    bool board_type_set;
private:
    function_approximator fn;
    double trainstep;
    double learningRate;
    double discountFactor;
};

QLearningAgent Qlearn;
std::map<std::string,int> board_count;

int16_t maxDepth=3;


std::pair<double,U16> minimax(Board &b,int16_t depth,
            bool maximizingPlayer, double alpha, double beta,
            std::pair<U8,int> last_killed_data, QLearningAgent &Qlearn)
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
                    false,alpha,beta,std::make_pair(b.data.last_killed_piece, b.data.last_killed_piece_idx),Qlearn);
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
                    true,alpha,beta, std::make_pair(b.data.last_killed_piece, b.data.last_killed_piece_idx),Qlearn);
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

    if(!Qlearn.board_type_set){
        Qlearn = QLearningAgent(b.data.board_type);
    }

    // pick a random move
    auto moveset = b.get_legal_moves();
    if (moveset.size() == 0) {
        this->best_move = 0;
    }
    else {
        Board search_board(b.data);
        board_count[board_encode(search_board)]++;

        this->best_move = *moveset.begin();

        // store time
        auto search_result = minimax(search_board, 1, true,DBL_MIN,DBL_MAX, std::make_pair(b.data.last_killed_piece, b.data.last_killed_piece_idx),Qlearn);
        
        this->best_move = search_result.second;

        if(this->best_move != 0){
            search_board.do_move_(this->best_move);
            
            board_count[board_encode(search_board)]++;
        }
    }
    // std::this_thread::sleep_for(std::chrono::milliseconds(500));
    return;
}
