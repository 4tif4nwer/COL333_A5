#include<bits/stdc++.h>
#include<random>
#include "board.hpp"
#include "butils.hpp"
#include "neural.cpp"
#include<time.h>

using namespace std;

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
    
    return perspective;
}

int main(){
    bool f = 0;

    Board test;

    auto pure_board = all_boards_to_str(test);

    QLearningAgent Qlearn(36);

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
            playedmoves++;
            auto initial_board = all_boards_to_str(b);

            board_count[board_encode(b)]++;
            if(board_count[board_encode(b)] == 3){
                cout<<"Draw"<<endl;
                break;
            }
            
        

            auto moveset = b.get_legal_moves();

            if(moveset.size() == 0 && b.in_check()){
                if(f)
                    cout<<"Game Over, player 1 wins in "<<(playedmoves+1)/2<< "moves" <<endl;
                else
                    cout<<"Game Over, player 2 wins in "<<(playedmoves+1)/2<< "moves" <<endl;
                break;
            }
            else if(moveset.size() == 0){
                cout<<"Draw"<<endl;
                break;
            }
            
            // sample an integer from 1 to 100
            int r = rand() % 100;
            auto move = *moveset.begin();
            if(r<50){
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
                double q_val = INT_MIN;
                for(auto &it : moveset){
                    auto eval = Qlearn.state_evaluation(b,it) ;
                    // auto board_now = all_boards_to_str(b);
                    // assert(board_now == initial_board);
                    if(q_val < eval){
                        move = it;
                        q_val = eval;
                    }
                }
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
            Qlearn.qLearningUpdate(b,move,isdraw);
            auto board_now = all_boards_to_str(b);
            b.do_move_(move);
            // cout<<move_to_str(move)<<endl;
            // cout<<all_boards_to_str(b)<<"\n";
            // if(board_now != initial_board){
            //     std::cout<<board_now<<"\n"<<initial_board<<"\n";
            // }
            // assert(board_now == initial_board);
            f = !f;
        }  
        
    }

}