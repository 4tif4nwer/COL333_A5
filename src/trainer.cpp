#include<bits/stdc++.h>
#include<random>
#include "board.hpp"
#include "butils.hpp"
#include "neural.cpp"
#include<time.h>

using namespace std;

const double MIN = -1000;
const double MAX = 1000;

QLearningAgent Qlearn(true);
int16_t maxDepth=3;


bool ge_operator(const std::pair<double,int16_t> & a, const std::pair<double,int16_t> & b){
    if(a.first != b.first){
        return (a.first > b.first);
    }
    else if(a.first < 0){
        return (a.second >= b.second);
    }
    return (a.second <= b.second);
}

std::pair<double,U16> minimax(Board &b,int16_t depth,
            bool maximizingPlayer, double alpha, double beta,
            std::pair<U8,int> last_killed_data, map<string,int> &board_count)
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
                    false,alpha,beta,std::make_pair(b.data.last_killed_piece, b.data.last_killed_piece_idx),board_count);
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
                    true,alpha,beta, std::make_pair(b.data.last_killed_piece, b.data.last_killed_piece_idx),board_count);
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

// double exploration_constant = 0.0;
// std::map<string,int> seen_boards;
// std::map<pair<string,int>,int> seen_board_moves;

// double explore(string board,int move){
//     if(seen_boards[board] == 0){
//         seen_boards[board] = 1;
//     }

//     if(seen_board_moves[{board,move}] == 0){
//         seen_board_moves[{board,move}] = 1;
//     }

//     double exp = sqrt(log(seen_boards[board])/seen_board_moves[{board,move}]);

//     seen_boards[board]++;
//     seen_board_moves[{board,move}]++;

//     return exp * exploration_constant;
// }

int main(){

    Board test(SEVEN_THREE);
    auto pure_board = all_boards_to_str(test);
    std::cout<<pure_board<<"\n";
    std::cout<<"Training\n";


    for(int games = 1; games <= 1000000 ; ++games){
        std::cout<<"Game : "<<games<<"\n";
        Board b = Board(SEVEN_THREE);
        // if(all_boards_to_str(b)!= pure_board){
        //     std::cout<<all_boards_to_str(b)<<"\n"<<pure_board<<"\n";
        // }
        assert(all_boards_to_str(b) == pure_board);        
        bool f = true;

        srand(time(0));
        map<string,int> board_count;


        int playedmoves = 0;
        while(1){
            f = !f;
            playedmoves++;
            // auto initial_board = all_boards_to_str(b);

            board_count[board_encode(b)]++;
            if(board_count[board_encode(b)] == 3){
                cout<<"Threefold Repetition in "<<(playedmoves + 1)/2<<" moves"<<endl;

                std::cout<<all_boards_to_str(b)<<"\n";
                break;
            }
            
        

            auto moveset = b.get_legal_moves();

            if(moveset.size() == 0 && b.in_check()){
                if(f)
                    cout<<"Game Over, player 1 wins in "<<(playedmoves+1)/2<< " moves" <<endl;
                else
                    cout<<"Game Over, player 2 wins in "<<(playedmoves+1)/2<< " moves" <<endl;
                break;
            }
            else if(moveset.size() == 0){
                cout<<"Stalemate in "<<(playedmoves+1)/2<< " moves" <<endl;
                break;
            }
            
            // sample an integer from 1 to 100
            int r = rand() % 100;
            auto move = *moveset.begin();
            if(r<30){
                std::vector<U16> moves;
                std::sample(
                    moveset.begin(),
                    moveset.end(),
                    std::back_inserter(moves),
                    1,
                    std::mt19937{std::random_device{}()}
                );
                move = moves[0];
                
            }
            else{
                std::vector<U16> moves;
                std::sample(
                    moveset.begin(),
                    moveset.end(),
                    std::back_inserter(moves),
                    1,
                    std::mt19937{std::random_device{}()}
                );
                move = moves[0];
                auto initial_board = all_boards_to_str(b);
                auto search_result = minimax(b, 1, true,DBL_MIN,DBL_MAX, std::make_pair(b.data.last_killed_piece, b.data.last_killed_piece_idx),board_count);

                assert(initial_board == all_boards_to_str(b));
                if(search_result.second != 0){
                    move = search_result.second;
                }
                else{
                    std::cout<<"not ok\n";
                }
                // std::cout<<q_val<<endl;
            }

            b.do_move_without_flip_(move);
            bool isdraw = false;
            if(board_count[board_encode(b)] == 2){
                isdraw = true;
            }
            b.flip_player_();
            if(b.get_legal_moves().size() == 0 && !b.in_check()){
                isdraw = true;
            }
            b.flip_player_();
            b.undo_last_move_without_flip_(move);

            Qlearn.qLearningUpdate(b,move,board_count,isdraw);

            // auto board_now = all_boards_to_str(b);
            b.do_move_(move);
            // cout<<move_to_str(move)<<endl;
            // cout<<all_boards_to_str(b)<<"\n";
            // if(board_now != initial_board){
            //     std::cout<<board_now<<"\n"<<initial_board<<"\n";
            // }
            // assert(board_now == initial_board);
        }  
        
    }

}