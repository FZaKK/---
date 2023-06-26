#include <iostream>
#include <fstream>
#include "sudoku.h"
#include "filedeal.h"
#include "cmdline.h"
using namespace std;


int main(int argc, char* argv[]){
    // 创建一个parser
    cmdline::parser a;

    // 补充对应的参数
    a.add<int>("create", 'c', "The number of Sudoku finals required", false, 0, cmdline::range(1, 1000000));
    a.add<string>("solve", 's', "The path to the Sudoku board file that needs to be solved", false, "game.txt");
    a.add<int>("number", 'n', "The number of Sudoku games needed", false, 0, cmdline::range(1, 10000));
    a.add<int>("manage", 'm', "The difficulty of generating a Sudoku game", false, 0, cmdline::range(1, 3));
    a.add<int>("range", 'r', "The range of the number of knockouts in the game", false, 0, cmdline::range(20, 55));
    a.add("unique", 'u', "The solution unique to the game");

    a.parse_check(argc, argv);

    cout << a.get<int>("create") << endl;
    if (a.exist("unique")) cout << "unique" << endl;


    vector<vector<char>>board = { vector<char>{'5','3','$','$','7','$','$','$','$'},
                                  vector<char>{'6','$','$','1','9','5','$','$','$'},
                                  vector<char>{'$','9','8','$','$','$','$','6','$'},
                                  vector<char>{'8','$','$','$','6','$','$','$','3'},
                                  vector<char>{'4','$','$','8','$','3','$','$','1'},
                                  vector<char>{'7','$','$','$','2','$','$','$','6'},
                                  vector<char>{'$','6','$','$','$','$','2','8','$'},
                                  vector<char>{'$','$','$','4','1','9','$','$','5'},
                                  vector<char>{'$','$','$','$','8','$','$','7','9'}, };
    sudoku temp(board);
    temp.dfs(board, 0);
    temp.printBoard(board);

    // 创建一个9*9的空二维数组
    vector<vector<char>>blank(9, vector<char>(9, '$'));
    sudoku s(blank);
    s.create(50, blank);  // 创建50个空格的数独
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

    // 测试生成数独终盘到文件之中
    create_sudo(2);

    return 0;
}
