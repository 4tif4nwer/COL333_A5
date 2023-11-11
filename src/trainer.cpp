#include<bits/stdc++.h>
#include<random>
#include "board.hpp"
#include "butils.hpp"
#include "neural.cpp"
#include<time.h>

using namespace std;


double exploration_constant = 0.0;
std::map<string,int> seen_boards;
std::map<pair<string,int>,int> seen_board_moves;

double explore(string board,int move){
    if(seen_boards[board] == 0){
        seen_boards[board] = 1;
    }

    if(seen_board_moves[{board,move}] == 0){
        seen_board_moves[{board,move}] = 1;
    }

    double exp = sqrt(log(seen_boards[board])/seen_board_moves[{board,move}]);

    seen_boards[board]++;
    seen_board_moves[{board,move}]++;

    return exp * exploration_constant;
}
int main(){

    Board test;

    auto pure_board = all_boards_to_str(test);

    QLearningAgent Qlearn(true);
    std::cout<<"Training\n";

    bool f = true;

    for(int games = 1; games <= 1000000 ; ++games){
        std::cout<<"Game : "<<games<<"\n";
        Board b = Board(test.data);
        if(all_boards_to_str(b)!= pure_board){
            std::cout<<all_boards_to_str(b)<<"\n"<<pure_board<<"\n";
        }

        srand(time(0));
        map<string,int> board_count;

        assert(all_boards_to_str(b) == pure_board);

        int playedmoves = 0;
        while(1){
            f = !f;
            playedmoves++;
            auto initial_board = all_boards_to_str(b);

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
            if(f){
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

                auto q_val = Qlearn.state_evaluation(b,move,board_count);
                for(auto &it : moveset){
                    auto eval = Qlearn.state_evaluation(b,it,board_count);
                    if(q_val < (eval)){
                        move = it;
                        q_val = eval;
                    }
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
            auto board_now = all_boards_to_str(b);
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