#include <iostream>
#include <fstream>
#include "sudoku.h"
#include "filedeal.h"
#include "cmdline.h"
using namespace std;

// 解析命令行参数并根据参数执行相应的操作。 
int main(int argc, char* argv[]){
    // 创建一个parser，用于解析命令行参数。
    cmdline::parser a;

    // 补充对应的参数，通过a.add方法添加了各个参数的定义
    a.add<int>("create", 'c', "The number of Sudoku finals required", false, 0, cmdline::range(1, 1000000));
    a.add<string>("solve", 's', "The path to the Sudoku board file that needs to be solved", false, "");
    a.add<int>("number", 'n', "The number of Sudoku games needed", false, 0, cmdline::range(1, 10000));
    a.add<int>("manage", 'm', "The difficulty of generating a Sudoku game", false, 0, cmdline::range(1, 3));
    a.add<int>("range", 'r', "The range of the number of knockouts in the game", false, 0, cmdline::range(20, 55));
    a.add("unique", 'u', "The solution unique to the game");

    a.parse_check(argc, argv);

    // 判断输入的命令，开始测试

    // 如果create参数不为0 sudoku.exe -c 20 [表示生成20个数独终盘]
    if (a.get<int>("create") != 0) {
        // 测试生成数独终盘到文件之中
        create_sudoku(a.get<int>("create"));
    }
    // 参数s  sudoku.exe -s game.txt [表示从game.txt读取若干个数独游戏，并给出其解答，生成到sudoku.txt中] 
    if (a.get<string>("solve") != "") {
        solve_sudoku(a.get<string>("solve"));
    }
    // 参数n sudoku.exe -n 1000 [表示生成1000个数独游戏]
    if (a.get<int>("number") != 0 && a.get<int>("manage") == 0 && a.get<int>("range") == 0 && !a.exist("unique")) {
        create_game(a.get<int>("number"));
    }
    // 特殊情况，同时输入了m，n，r，报错
    if (a.get<int>("number") != 0 && a.get<int>("manage") != 0 && a.get<int>("range") != 0) {
        cout << "Error : "
             << "Too many parameters. Have the parameter n, m, r"
             << endl;
    }
    // 参数m  sudoku.exe -n 1000 -m 1[表示生成1000个简单数游戏，只有m和n一起使用才认为参数无误，否则请报错]
    if (a.get<int>("manage") != 0) {
        if (a.get<int>("number") != 0) {
            create_game(a.get<int>("number"), a.get<int>("manage"));
        }
        else {
            cout << "Error : "
                 << "Have the parameter m, but don't have the parameter n!!!"
                 << endl;
        }
    }
    // 参数r  sudoku.exe -n 20 -r 20~55[表示生成20个控空数在20到55之间的数独游戏，只有r和n一起使用才认为参数无误，否则请报错]
    if (a.get<int>("range") != 0) {
        if (a.get<int>("number") != 0) {
            create_game_range(a.get<int>("number"), a.get<int>("range"));
        }
        else {
            cout << "Error : "
                 << "Have the parameter r, but don't have the parameter n!!!"
                 << endl;
        }
    }
    // 参数u sudoku.exe -n 20 -u[表示生成20个解唯一的数独游戏，只有u和n一起使用才认为参数无误，否则请报错]
    if (a.exist("unique")) {
        if (a.get<int>("number") != 0) {
            create_game_unique(a.get<int>("number"));
        }
        else {
            cout << "Error : "
                 << "Have the parameter u, but don't have the parameter n!!!"
                 << endl;
        }
    }
    // 没有参数的时候会给出数独的example
    if (argc == 1) {
        cout << " ----- Show the sudoku example ----- " << endl;

        // 创建一个9*9的空二维数组
        vector<vector<char>>blank(9, vector<char>(9, '$'));
        sudoku s(blank);
        s.create(50, blank);  // 创建50个空格的数独
        if (s.active){
            cout << endl << " ----- The Gen of the sudoku ----- " << endl;
            s.printBoard(blank);
        }
        else{
            cout << endl << " ----- The sudoku is invalid -----" << endl;
        }

        // 解数独函数
        s.dfs(blank, 0);
        if (s.active){
            cout << endl <<  " ----- The solution of the sudoku ----- " << endl;
            s.printBoard(blank);
        }
        else{
            cout << endl << " ----- The sudoku is invalid -----" << endl;
        }
    }

    system("pause");
    return 0;
}
