#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using std::string;
using std::vector;
using std::cout;
using std::istringstream;

enum class State {kEmpty, kObstacle};

string CellString(State state){
    switch(state) {
        case State::kObstacle: return "⛰️   ";
        default: return "0   "; 
    }
}

void PrintBoard(vector<vector<State>> board){
    //alternatively use `auto`
    for(vector<State> v: board){
        for(State i: v){
            cout << CellString(i) << " ";
        }
        cout << "\n";
    }
}

vector<State> ParseLine(string string){
    istringstream string_stream(string);
    char c;
    int n;
    vector<State> output;
    while(string_stream >> n >> c && c == ',') {
        if (n == 1){
            output.push_back(State::kObstacle);
        } else {
            output.push_back(State::kEmpty);
        }
    }

    return output;
}

vector<vector<State>> ReadBoardFile(string path){
    std::ifstream board_file(path);
    vector<vector<State>> vec_board;
    
    if (board_file) {
        string line;
        int i = 0;
        while(getline(board_file, line)) {
            vec_board.push_back(ParseLine(line));
        }
    }

    return vec_board;
}

int main() {

    vector<vector<State>> vec_board = ReadBoardFile("1.board");
    PrintBoard(vec_board);
    return 0;
}

