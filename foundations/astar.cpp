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

void PrintBoard(vector<vector<int>> board){
    //alternatively use `auto`
    for(vector<int> v: board){
        for(int i: v){
            cout << i << " ";
        }
        cout << "\n";
    }
}

vector<int> ParseLine(string string){
    istringstream string_stream(string);
    char c;
    int n;
    vector<int> output;
    while(string_stream >> n >> c && c == ',') {
        output.push_back(n);
    }

    return output;
}

vector<vector<int>> ReadBoardFile(string path){
    std::ifstream board_file(path);
    vector<vector<int>> vec_board;
    
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

    vector<vector<int>> vec_board = ReadBoardFile("1.board");
    PrintBoard(vec_board);
    return 0;
}

