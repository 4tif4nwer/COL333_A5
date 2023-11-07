#include <iostream>
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

    b.data.player_to_play = WHITE;

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
    if(b.data.b_pawn_1 & PAWN){
        if(!b.under_threat(b.data.b_pawn_1)){
            reward -= 1;
        }
        if(b.data.b_pawn_1 != DEAD){
            reward -= 10;
        }
    }
    else if(b.data.b_pawn_1 & ROOK){
        if(!b.under_threat(b.data.b_pawn_1)){
            reward -= 5;
        }
        if(b.data.b_pawn_1 != DEAD){
            reward -= 20;
        }
    }
    else if(b.data.b_pawn_1 & BISHOP){
        if(!b.under_threat(b.data.b_pawn_1)){
            reward -= 3;
        }
        if(b.data.b_pawn_1 != DEAD){
            reward -= 20;
        }
    }

    if(b.data.b_pawn_2 & PAWN){
        if(!b.under_threat(b.data.b_pawn_2)){
            reward -= 1;
        }
        if(b.data.b_pawn_2 != DEAD){
            reward -= 10;
        }
    }
    else if(b.data.b_pawn_2 & ROOK){
        if(!b.under_threat(b.data.b_pawn_2)){
            reward -= 5;
        }
        if(b.data.b_pawn_2 != DEAD){
            reward -= 20;
        }
    }
    else if(b.data.b_pawn_2 & BISHOP){
        if(!b.under_threat(b.data.b_pawn_2)){
            reward -= 3;
        }
        if(b.data.b_pawn_2 != DEAD){
            reward -= 20;
        }
    }
    b.data.player_to_play = BLACK;

    if(b.under_threat(b.data.w_king)){
        reward -= 100;
    }
    if(b.under_threat(b.data.w_rook_1)){
        reward -= 20;
    }
    if(b.data.w_rook_1 == DEAD){
        reward -= 5;
    }
    if(b.under_threat(b.data.w_rook_2)){
        reward -= 20;
    }
    if(b.data.w_rook_2 == DEAD){
        reward -= 5;
    }
    if(b.under_threat(b.data.w_bishop)){
        reward -= 20;
    }
    if(b.data.w_bishop == DEAD){
        reward -= 3;
    }
    if(b.data.w_pawn_1 & PAWN){
        if(!b.under_threat(b.data.w_pawn_1)){
            reward += 10;
        }
        if(b.data.w_pawn_1 != DEAD){
            reward += 1;
        }
    }
    else if(b.data.w_pawn_1 & ROOK){
        if(!b.under_threat(b.data.w_pawn_1)){
            reward += 20;
        }
        if(b.data.w_pawn_1 != DEAD){
            reward += 5;
        }
    }
    else if(b.data.w_pawn_1 & BISHOP){
        if(!b.under_threat(b.data.w_pawn_1)){
            reward += 20;
        }
        if(b.data.w_pawn_1 != DEAD){
            reward += 3;
        }
    }

    if(b.data.w_pawn_2 & PAWN){
        if(!b.under_threat(b.data.w_pawn_2)){
            reward += 10;
        }
        if(b.data.w_pawn_2 != DEAD){
            reward += 1;
        }
    }
    else if(b.data.w_pawn_2 & ROOK){
        if(!b.under_threat(b.data.w_pawn_2)){
            reward += 20;
        }
        if(b.data.w_pawn_2 != DEAD){
            reward += 5;
        }
    }
    else if(b.data.w_pawn_2 & BISHOP){
        if(!b.under_threat(b.data.w_pawn_2)){
            reward += 20;
        }
        if(b.data.w_pawn_2 != DEAD){
            reward += 3;
        }
    }

    b.data.player_to_play = curr_player;

    b.flip_player_();
    if(b.get_legal_moves().size() == 0 && b.in_check()){
        reward = 10000;
        b.flip_player_();
        return reward;
    }
    b.flip_player_();
    
    if(b.data.player_to_play == BLACK){
        reward = -reward;
    }

    return reward;
}


class NeuralNetwork {
public:
    NeuralNetwork(int inputSize, int hiddenSize, int outputSize,bool pretrained = false)
        : inputSize(inputSize), hiddenSize(hiddenSize), outputSize(outputSize) {
        // Initialize weights and biases for the hidden and output layers
        hiddenWeights.resize(inputSize, std::vector<double>(hiddenSize));
        outputWeights.resize(hiddenSize, std::vector<double>(outputSize));
        hiddenBiases.resize(hiddenSize);
        outputBiases.resize(outputSize);

        // Initialize weights and biases with random values
        initializeRandomWeightsAndBiases(pretrained);
    }

    // Forward pass
    std::vector<double> forward(const std::vector<double>& input) {
        // Input to hidden layer
        assert(input.size() == inputSize);
        std::vector<double> hiddenOutput(hiddenSize);
        for (int i = 0; i < hiddenSize; ++i) {
            hiddenOutput[i] = 0;
            for (int j = 0; j < inputSize; ++j) {
                hiddenOutput[i] += input[j] * hiddenWeights[j][i];
            }
            hiddenOutput[i] += hiddenBiases[i];
            hiddenOutput[i] = sigmoid(hiddenOutput[i]);
        }

        // Hidden to output layer
        std::vector<double> output(outputSize);
        for (int i = 0; i < outputSize; ++i) {
            output[i] = 0;
            for (int j = 0; j < hiddenSize; ++j) {
                output[i] += hiddenOutput[j] * outputWeights[j][i];
            }
            output[i] += outputBiases[i];
        }

        return output;
    }

    // Training using backpropagation
    void train(const std::vector<std::vector<double>>& inputs, const std::vector<std::vector<double>>& targets, double learningRate, int epochs) {
        // for(auto &it : inputs[0]){
        //     std::cout<<it<<" ";
        // }
        // std::cout<<targets[0][0]<<std::endl;
        for (int epoch = 0; epoch < epochs; ++epoch) {
            for (size_t i = 0; i < inputs.size(); ++i) {
                assert(inputs[i].size() == inputSize);
                // Forward pass
                std::vector<double> input = inputs[i];
                std::vector<double> target = targets[i];

                // Compute hidden layer output
                std::vector<double> hiddenOutput(hiddenSize);
                for (int j = 0; j < hiddenSize; ++j) {
                    hiddenOutput[j] = 0;
                    for (int k = 0; k < inputSize; ++k) {
                        hiddenOutput[j] += input[k] * hiddenWeights[k][j];
                    }
                    hiddenOutput[j] += hiddenBiases[j];
                    hiddenOutput[j] = sigmoid(hiddenOutput[j]);
                }

                // Compute output layer output
                std::vector<double> output(outputSize);
                for (int j = 0; j < outputSize; ++j) {
                    output[j] = 0;
                    for (int k = 0; k < hiddenSize; ++k) {
                        output[j] += hiddenOutput[k] * outputWeights[k][j];
                    }
                    output[j] += outputBiases[j];
                }

                // Compute output layer error
                std::vector<double> outputError(outputSize);
                for (int j = 0; j < outputSize; ++j) {
                    outputError[j] = target[j] - output[j];
                }

                // Backpropagation
                for (int j = 0; j < outputSize; ++j) {
                    for (int k = 0; k < hiddenSize; ++k) {
                        outputWeights[k][j] += learningRate * outputError[j] * hiddenOutput[k];
                    }
                    outputBiases[j] += learningRate * outputError[j];
                }

                // Update hidden layer error
                std::vector<double> hiddenError(hiddenSize);
                for (int j = 0; j < hiddenSize; ++j) {
                    hiddenError[j] = 0;
                    for (int k = 0; k < outputSize; ++k) {
                        hiddenError[j] += outputError[k] * outputWeights[j][k];
                    }
                }

                // Update hidden layer weights and biases
                for (int j = 0; j < hiddenSize; ++j) {
                    for (int k = 0; k < inputSize; ++k) {
                        hiddenWeights[k][j] += learningRate * hiddenError[j] * input[k];
                    }
                    hiddenBiases[j] += learningRate * hiddenError[j];
                }
            }
        }
        std::ofstream output_file("src/weights.txt");

        // std::ostream_iterator<std::string> output_iterator(output_file, "\n");
        for(auto &it : hiddenWeights){
            for(auto &it2 : it){
                output_file<< std::fixed << std::setprecision(10)<<it2<<"\n";
            }
        }
        for(auto &it : hiddenBiases){
            output_file<<it<<"\n";
        }
        for(auto &it : outputWeights){
            for(auto &it2 : it){
                output_file<<it2<<"\n";
            }
        }
        for(auto &it : outputBiases){
            output_file<<it<<"\n";
        }

        output_file.close();
                
    }

private:
    int inputSize;
    int hiddenSize;
    int outputSize;
    std::vector<std::vector<double>> hiddenWeights;
    std::vector<std::vector<double>> outputWeights;
    std::vector<double> hiddenBiases;
    std::vector<double> outputBiases;

    // Sigmoid activation function
    double sigmoid(double x) {
        return 1.0 / (1.0 + exp(-x));
    }

    // Initialize weights and biases with random values
    void initializeRandomWeightsAndBiases(bool pretrained = false) {
        if(pretrained){
            std::ifstream input_file("src/weights.txt");
            std::string line;
            int i = 0;
            while(std::getline(input_file, line)){
                if(i < inputSize * hiddenSize){
                    hiddenWeights[i/hiddenSize][i%hiddenSize] = std::stod(line);
                }
                else if(i < inputSize * hiddenSize + hiddenSize){
                    hiddenBiases[i - inputSize * hiddenSize] = std::stod(line);
                }
                else if(i < inputSize * hiddenSize + hiddenSize + hiddenSize * outputSize){
                    outputWeights[(i - inputSize * hiddenSize - hiddenSize)/outputSize][(i - inputSize * hiddenSize - hiddenSize)%outputSize] = std::stod(line);
                }
                else{
                    outputBiases[i - inputSize * hiddenSize - hiddenSize - hiddenSize * outputSize] = std::stod(line);
                }
                i++;
            }
            input_file.close();
            return;
        }
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<double> dist(-1.0, 1.0);

        for (int i = 0; i < inputSize; ++i) {
            for (int j = 0; j < hiddenSize; ++j) {
                hiddenWeights[i][j] = dist(gen);
            }
        }

        for (int i = 0; i < hiddenSize; ++i) {
            for (int j = 0; j < outputSize; ++j) {
                outputWeights[i][j] = dist(gen);
            }
        }

        for (int i = 0; i < hiddenSize; ++i) {
            hiddenBiases[i] = dist(gen);
        }

        for (int i = 0; i < outputSize; ++i) {
            outputBiases[i] = dist(gen);
        }
        std::ofstream output_file("src/weights.txt");

        // std::ostream_iterator<std::string> output_iterator(output_file, "\n");
        for(auto &it : hiddenWeights){
            for(auto &it2 : it){
                output_file<< std::fixed << std::setprecision(8)<<it2<<" ";
            }
        }
        for(auto &it : hiddenBiases){
            output_file<<it<<" ";
        }
        for(auto &it : outputWeights){
            for(auto &it2 : it){
                output_file<<it2<<" ";
            }
        }
        for(auto &it : outputBiases){
            output_file<<it<<" ";
        }

        output_file.close();
    }
};

class QLearningAgent {
public:
    QLearningAgent(int inputSize, int hiddenSize = 100, int outputSize = 1)
        : nn(inputSize, hiddenSize, outputSize,true) {
            learningRate = 0.01;
            discountFactor = 0.7;
            trainstep = 1;

    }

    double state_evaluation(Board& b, U16 move){ // Q(s,a)
        double score = 0;
        std::vector<double> input;
        b.do_move_without_flip_(move);

        if(b.data.player_to_play == WHITE){
            input = {
                static_cast<double>(piece_to_char(b.data.w_king)),
                static_cast<double>(getx(b.data.w_king)),
                static_cast<double>(gety(b.data.w_king)),
                static_cast<double>(piece_to_char(b.data.w_rook_1)),
                static_cast<double>(getx(b.data.w_rook_1)),
                static_cast<double>(gety(b.data.w_rook_1)),
                static_cast<double>(piece_to_char(b.data.w_rook_2)),
                static_cast<double>(getx(b.data.w_rook_2)),
                static_cast<double>(gety(b.data.w_rook_2)),
                static_cast<double>(piece_to_char(b.data.w_bishop)),
                static_cast<double>(getx(b.data.w_bishop)),
                static_cast<double>(gety(b.data.w_bishop)),
                static_cast<double>(piece_to_char(b.data.w_pawn_1)),
                static_cast<double>(getx(b.data.w_pawn_1)),
                static_cast<double>(gety(b.data.w_pawn_1)),
                static_cast<double>(piece_to_char(b.data.w_pawn_2)),
                static_cast<double>(getx(b.data.w_pawn_2)),
                static_cast<double>(gety(b.data.w_pawn_2)),
                static_cast<double>(piece_to_char(b.data.b_king)),
                static_cast<double>(getx(b.data.b_king)),
                static_cast<double>(gety(b.data.b_king)),
                static_cast<double>(piece_to_char(b.data.b_rook_1)),
                static_cast<double>(getx(b.data.b_rook_1)),
                static_cast<double>(gety(b.data.b_rook_1)),
                static_cast<double>(piece_to_char(b.data.b_rook_2)),
                static_cast<double>(getx(b.data.b_rook_2)),
                static_cast<double>(gety(b.data.b_rook_2)),
                static_cast<double>(piece_to_char(b.data.b_bishop)),
                static_cast<double>(getx(b.data.b_bishop)),
                static_cast<double>(gety(b.data.b_bishop)),
                static_cast<double>(piece_to_char(b.data.b_pawn_1)),
                static_cast<double>(getx(b.data.b_pawn_1)),
                static_cast<double>(gety(b.data.b_pawn_1)),
                static_cast<double>(piece_to_char(b.data.b_pawn_2)),
                static_cast<double>(getx(b.data.b_pawn_2)),
                static_cast<double>(gety(b.data.b_pawn_2))
                

            };

        }
        else{
            input = {
                static_cast<double>(piece_to_char(b.data.b_king)),
                static_cast<double>(getx(b.data.b_king)),
                static_cast<double>(gety(b.data.b_king)),
                static_cast<double>(piece_to_char(b.data.b_rook_1)),
                static_cast<double>(getx(b.data.b_rook_1)),
                static_cast<double>(gety(b.data.b_rook_1)),
                static_cast<double>(piece_to_char(b.data.b_rook_2)),
                static_cast<double>(getx(b.data.b_rook_2)),
                static_cast<double>(gety(b.data.b_rook_2)),
                static_cast<double>(piece_to_char(b.data.b_bishop)),
                static_cast<double>(getx(b.data.b_bishop)),
                static_cast<double>(gety(b.data.b_bishop)),
                static_cast<double>(piece_to_char(b.data.b_pawn_1)),
                static_cast<double>(getx(b.data.b_pawn_1)),
                static_cast<double>(gety(b.data.b_pawn_1)),
                static_cast<double>(piece_to_char(b.data.b_pawn_2)),
                static_cast<double>(getx(b.data.b_pawn_2)),
                static_cast<double>(gety(b.data.b_pawn_2)),
                static_cast<double>(piece_to_char(b.data.w_king)),
                static_cast<double>(getx(b.data.w_king)),
                static_cast<double>(gety(b.data.w_king)),
                static_cast<double>(piece_to_char(b.data.w_rook_1)),
                static_cast<double>(getx(b.data.w_rook_1)),
                static_cast<double>(gety(b.data.w_rook_1)),
                static_cast<double>(piece_to_char(b.data.w_rook_2)),
                static_cast<double>(getx(b.data.w_rook_2)),
                static_cast<double>(gety(b.data.w_rook_2)),
                static_cast<double>(piece_to_char(b.data.w_bishop)),
                static_cast<double>(getx(b.data.w_bishop)),
                static_cast<double>(gety(b.data.w_bishop)),
                static_cast<double>(piece_to_char(b.data.w_pawn_1)),
                static_cast<double>(getx(b.data.w_pawn_1)),
                static_cast<double>(gety(b.data.w_pawn_1)),
                static_cast<double>(piece_to_char(b.data.w_pawn_2)),
                static_cast<double>(getx(b.data.w_pawn_2)),
                static_cast<double>(gety(b.data.w_pawn_2))
            };

        }
        b.undo_last_move_without_flip_(move);
        std::vector<double> output = nn.forward(input);
        score = output[0];
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
        double next_q_val = INT32_MIN;
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
                next_q_val = std::max(next_q_val,-state_evaluation(state,it));
            }
            state.flip_player_();

        }

        
        std::vector<double> input;

        if(state.data.player_to_play == WHITE){
            input = {
                static_cast<double>(piece_to_char(state.data.w_king)),
                static_cast<double>(getx(state.data.w_king)),
                static_cast<double>(gety(state.data.w_king)),
                static_cast<double>(piece_to_char(state.data.w_rook_1)),
                static_cast<double>(getx(state.data.w_rook_1)),
                static_cast<double>(gety(state.data.w_rook_1)),
                static_cast<double>(piece_to_char(state.data.w_rook_2)),
                static_cast<double>(getx(state.data.w_rook_2)),
                static_cast<double>(gety(state.data.w_rook_2)),
                static_cast<double>(piece_to_char(state.data.w_bishop)),
                static_cast<double>(getx(state.data.w_bishop)),
                static_cast<double>(gety(state.data.w_bishop)),
                static_cast<double>(piece_to_char(state.data.w_pawn_1)),
                static_cast<double>(getx(state.data.w_pawn_1)),
                static_cast<double>(gety(state.data.w_pawn_1)),
                static_cast<double>(piece_to_char(state.data.w_pawn_2)),
                static_cast<double>(getx(state.data.w_pawn_2)),
                static_cast<double>(gety(state.data.w_pawn_2)),
                static_cast<double>(piece_to_char(state.data.b_king)),
                static_cast<double>(getx(state.data.b_king)),
                static_cast<double>(gety(state.data.b_king)),
                static_cast<double>(piece_to_char(state.data.b_rook_1)),
                static_cast<double>(getx(state.data.b_rook_1)),
                static_cast<double>(gety(state.data.b_rook_1)),
                static_cast<double>(piece_to_char(state.data.b_rook_2)),
                static_cast<double>(getx(state.data.b_rook_2)),
                static_cast<double>(gety(state.data.b_rook_2)),
                static_cast<double>(piece_to_char(state.data.b_bishop)),
                static_cast<double>(getx(state.data.b_bishop)),
                static_cast<double>(gety(state.data.b_bishop)),
                static_cast<double>(piece_to_char(state.data.b_pawn_1)),
                static_cast<double>(getx(state.data.b_pawn_1)),
                static_cast<double>(gety(state.data.b_pawn_1)),
                static_cast<double>(piece_to_char(state.data.b_pawn_2)),
                static_cast<double>(getx(state.data.b_pawn_2)),
                static_cast<double>(gety(state.data.b_pawn_2))

            };

        }
        else{
            input = {
                static_cast<double>(piece_to_char(state.data.b_king)),
                static_cast<double>(getx(state.data.b_king)),
                static_cast<double>(gety(state.data.b_king)),
                static_cast<double>(piece_to_char(state.data.b_rook_1)),
                static_cast<double>(getx(state.data.b_rook_1)),
                static_cast<double>(gety(state.data.b_rook_1)),
                static_cast<double>(piece_to_char(state.data.b_rook_2)),
                static_cast<double>(getx(state.data.b_rook_2)),
                static_cast<double>(gety(state.data.b_rook_2)),
                static_cast<double>(piece_to_char(state.data.b_bishop)),
                static_cast<double>(getx(state.data.b_bishop)),
                static_cast<double>(gety(state.data.b_bishop)),
                static_cast<double>(piece_to_char(state.data.b_pawn_1)),
                static_cast<double>(getx(state.data.b_pawn_1)),
                static_cast<double>(gety(state.data.b_pawn_1)),
                static_cast<double>(piece_to_char(state.data.b_pawn_2)),
                static_cast<double>(getx(state.data.b_pawn_2)),
                static_cast<double>(gety(state.data.b_pawn_2)),
                static_cast<double>(piece_to_char(state.data.w_king)),
                static_cast<double>(getx(state.data.w_king)),
                static_cast<double>(gety(state.data.w_king)),
                static_cast<double>(piece_to_char(state.data.w_rook_1)),
                static_cast<double>(getx(state.data.w_rook_1)),
                static_cast<double>(gety(state.data.w_rook_1)),
                static_cast<double>(piece_to_char(state.data.w_rook_2)),
                static_cast<double>(getx(state.data.w_rook_2)),
                static_cast<double>(gety(state.data.w_rook_2)),
                static_cast<double>(piece_to_char(state.data.w_bishop)),
                static_cast<double>(getx(state.data.w_bishop)),
                static_cast<double>(gety(state.data.w_bishop)),
                static_cast<double>(piece_to_char(state.data.w_pawn_1)),
                static_cast<double>(getx(state.data.w_pawn_1)),
                static_cast<double>(gety(state.data.w_pawn_1)),
                static_cast<double>(piece_to_char(state.data.w_pawn_2)),
                static_cast<double>(getx(state.data.w_pawn_2)),
                static_cast<double>(gety(state.data.w_pawn_2))
            };

        }
        nn.train(std::vector<std::vector<double>>({input}),std::vector<std::vector<double>>({{reward + discountFactor * next_q_val}}),learningRate/trainstep,1);
        trainstep += 1;
        state.data.last_killed_piece = last_killed;
        state.data.last_killed_piece_idx = last_killed_idx;
        state.undo_last_move_without_flip_(move);
        
    }

private:
    NeuralNetwork nn;
    double trainstep;
    double learningRate;
    double discountFactor;
};
