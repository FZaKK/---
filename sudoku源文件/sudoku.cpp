#include <iostream>
#include "sudoku.h"
using namespace std;


int main()
{
    /*vector<vector<char>>board = { vector<char>{'5','3','.','.','7','.','.','.','.'},
                                  vector<char>{'6','.','.','1','9','5','.','.','.'},
                                  vector<char>{'.','9','8','.','.','.','.','6','.'},
                                  vector<char>{'8','.','.','.','6','.','.','.','3'},
                                  vector<char>{'4','.','.','8','.','3','.','.','1'},
                                  vector<char>{'7','.','.','.','2','.','.','.','6'},
                                  vector<char>{'.','6','.','.','.','.','2','8','.'},
                                  vector<char>{'.','.','.','4','1','9','.','.','5'},
                                  vector<char>{'.','.','.','.','8','.','.','7','9'}, };*/

    vector<vector<char>>blank(9, vector<char>(9, '$'));//创建一个9*9的空二维数组

    sudoku s(blank);
    s.create(50, blank);//创建50个空格的数独
    if (s.active){
        cout << "创建的数独为：" << endl;
        s.printBoard(blank);
    }
    else {
        cout << "数独表不合法，没有解！" << endl;
    }
    s.dfs(blank, 0);//解数独函数
    if (s.active){
        cout << "此数独的解是：" << endl;
        s.printBoard(blank);
    }
    else {
        cout << "解题失败！" << endl;
    }

    return 0;
}
