#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using std::string;
using std::vector;
using std::cout;
using std::istringstream;

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
    while(string_stream >> n >> c) {
        output.push_back(n);
    }

    return output;
}

void ReadBoardFile(string path){
    std::ifstream board_file(path);
    
    if (board_file) {
        string line;
        int i = 0;
        vector<vector<int>> vec_board;
        while(getline(board_file, line)) {
            cout << line << "\n";
            vec_board.push_back(ParseLine(line));
        }
    }
}

int main() {

    
    ReadBoardFile("1.board");
    return 0;
}

