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

class NeuralNetwork {
public:
    NeuralNetwork(int inputSize, int outputSize, int numHiddenLayers, int hiddenLayerSize, bool pretrained = false)
        : inputSize(inputSize), outputSize(outputSize) {
        // Initialize layers
        layers.push_back(inputSize);
        for (int i = 0; i < numHiddenLayers; ++i) {
            layers.push_back(hiddenLayerSize);
        }
        layers.push_back(outputSize);

        // Initialize weights and biases for all layers
        initializeWeightsAndBiases(pretrained);
    }

    // Forward pass
    std::vector<double> forward(const std::vector<double>& input) {
        std::vector<double> output = input;

        for (int i = 0; i < int(layers.size()) - 1; ++i) {
            int inputSize = layers[i];
            int outputSize = layers[i + 1];

            // Compute the output of the current layer
            std::vector<double> layerOutput(outputSize, 0.0);
            for (int j = 0; j < outputSize; ++j) {
                for (int k = 0; k < inputSize; ++k) {
                    layerOutput[j] += output[k] * weights[i][k][j];
                }
                layerOutput[j] += biases[i][j];
                if(i != (int(layers.size()) - 2))
                    layerOutput[j] = sigmoid(layerOutput[j]);
            }

            output = layerOutput;
        }

        return output;
    }

    // Training using backpropagation
    void train(const std::vector<std::vector<double>>& inputs, const std::vector<std::vector<double>>& targets, double learningRate, int epochs) {
        for (int epoch = 0; epoch < epochs; ++epoch) {
            for (size_t i = 0; i < inputs.size(); ++i) {
                const std::vector<double>& input = inputs[i];
                const std::vector<double>& target = targets[i];

                // Forward pass
                std::vector<std::vector<double>> layerOutputs;
                layerOutputs.push_back(input);
                std::vector<double> output = input;

                for (int j = 0; j < int(layers.size()) - 1; ++j) {
                    int inputSize = layers[j];
                    int outputSize = layers[j + 1];

                    // Compute the output of the current layer
                    std::vector<double> layerOutput(outputSize, 0.0);
                    for (int k = 0; k < outputSize; ++k) {
                        for (int l = 0; l < inputSize; ++l) {
                            layerOutput[k] += output[l] * weights[j][l][k];
                        }
                        layerOutput[k] += biases[j][k];
                        if(j != (int(layers.size()) - 2))
                            layerOutput[k] = sigmoid(layerOutput[k]);
                    }

                    output = layerOutput;
                    layerOutputs.push_back(output);
                }

                // Backpropagation
                std::vector<std::vector<double>> errors(int(layers.size()) - 1);

                // Compute the error of the output layer
                std::vector<double> outputErrors(outputSize, 0.0);
                for (int j = 0; j < outputSize; ++j) {
                    outputErrors[j] = target[j] - output[j];
                }
                std::cout<<outputErrors[0]<<"\n";
                errors[int(layers.size()) - 2] = outputErrors;

                // Compute the error of the hidden layers
                for (int j = int(layers.size()) - 3; j >= 0; --j) {
                    int inputSize = layers[j + 1];
                    int outputSize = layers[j + 2];

                    std::vector<double> error(inputSize, 0.0);
                    for (int k = 0; k < inputSize; ++k) {
                        for (int l = 0; l < outputSize; ++l) {
                            error[k] += errors[j + 1][l] * weights[j + 1][k][l] * layerOutputs[j + 1][l] * (1 - layerOutputs[j + 1][l]);
                        }
                    }

                    errors[j] = error;
                }

                // Update weights and biases
                for (int j = 0; j < int(layers.size()) - 1; ++j) {
                    int inputSize = layers[j];
                    int outputSize = layers[j + 1];

                    for (int k = 0; k < inputSize; ++k) {
                        for (int l = 0; l < outputSize; ++l) {
                            weights[j][k][l] += learningRate * errors[j][l] * layerOutputs[j][k];
                        }
                    }

                    for (int k = 0; k < outputSize; ++k) {
                        biases[j][k] += learningRate * errors[j][k];
                    }
                }

            }
        }
        // Write to text file
        std::ofstream output_file("src/weights.txt");

        output_file<< std::hexfloat;

        for(auto &it : weights){
            for(auto &it2 : it){
                for(auto &it3 : it2){
                    output_file<<it3<<"\n";
                }
            }
        }
        for(auto &it : biases){
            for(auto &it2 : it){
                output_file<<it2<<"\n";
            }
        }

        output_file.close();
    }

private:
    int inputSize;
    int outputSize;
    std::vector<int> layers; // Number of neurons in each layer
    std::vector<std::vector<std::vector<double>>> weights; // Weights for each connection
    std::vector<std::vector<double>> biases; // Biases for each neuron

    // Sigmoid activation function
    double sigmoid(double x) {
        return 1.0 / (1.0 + exp(-x));
    }

    // Initialize weights and biases for all layers
    void initializeWeightsAndBiases(bool pretrained = false) {

        if(pretrained){
            std::ifstream input_file("src/weights.txt");
            std::string line;
            weights.resize(int(layers.size()) - 1);
            biases.resize(int(layers.size()) - 1);

            for (int i = 0; i < int(layers.size()) - 1; ++i) {
                int inputSize = layers[i];
                int outputSize = layers[i + 1];

                weights[i].resize(inputSize, std::vector<double>(outputSize));
                biases[i].resize(outputSize);
            }    

            for(auto &it : weights){
                for(auto &it2 : it){
                    for(auto &it3 : it2){
                        std::getline(input_file,line);
                        it3 = std::stod(line);
                    }
                }
            }
            for(auto &it : biases){
                for(auto &it2 : it){
                    std::getline(input_file,line);
                    it2 = std::stod(line);
                }
            }
            input_file.close();
            return;
            
        }
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<double> dist(-1.0, 1.0);

        weights.resize(int(layers.size()) - 1);
        biases.resize(int(layers.size()) - 1);

        for (int i = 0; i < int(layers.size()) - 1; ++i) {
            int inputSize = layers[i];
            int outputSize = layers[i + 1];

            weights[i].resize(inputSize, std::vector<double>(outputSize));
            biases[i].resize(outputSize);

            for (int j = 0; j < inputSize; ++j) {
                for (int k = 0; k < outputSize; ++k) {
                    weights[i][j][k] = dist(gen);
                }
            }

            for (int j = 0; j < outputSize; ++j) {
                biases[i][j] = dist(gen);
            }
        }

        std::ofstream output_file("src/weights.txt");

        output_file<< std::hexfloat;

        for(auto &it : weights){
            for(auto &it2 : it){
                for(auto &it3 : it2){
                    output_file<<it3<<"\n";
                }
            }
        }
        for(auto &it : biases){
            for(auto &it2 : it){
                output_file<<it2<<"\n";
            }
        }

        output_file.close();

        return;
    }
};


class QLearningAgent {
public:
    QLearningAgent(int inputSize,int numHiddenLayers = 1, int hiddenSize = 36, int outputSize = 1)
        : nn(inputSize, outputSize,numHiddenLayers, hiddenSize,true) {
            learningRate = 0.01;
            discountFactor = 0.8;
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
        nn.train(std::vector<std::vector<double>>({input}),std::vector<std::vector<double>>({{reward/1000 - discountFactor * next_q_val}}),learningRate,1);
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
