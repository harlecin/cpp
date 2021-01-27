#include <iostream>
#include <vector>

using std::vector;
using std::cout;

int main() {
    vector<int> vec_1{0, 1, 2};
    vector<int> vec_2 = {3,4,5};
    vector<int> vec_3;
    vec_3 = {6};

    cout << "Vectors rock XD \n";
    vector<vector<int>> vec_nested {{1,2}, {3,4}};

    return 0;
}
