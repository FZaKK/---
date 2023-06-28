#pragma once
#include <iostream>
#include <fstream>
#include <map>
#include "sudoku.h"
using namespace std;


// 难度等级与空格数目的键值对
map<int, int> diff_map = {
        {1, 20},
        {2, 40},
        {3, 55}
};
// 解数独文件得到的结果路径
string output_path = "sudoku.txt";


// 对应c参数，生成sudo终局文件
// 生成数独棋盘并将其写入名为"board.txt"的文件
void create_sudoku(int num){
    // 先将曾经生成的内容清空
    ofstream f("board.txt", ios_base::out);

    cout << "Begin to create the sudoku board ..." << endl;
    vector<vector<vector<char>>> Grids;//三维向量Grids，用于存储生成的数独棋盘。每个棋盘都以二维字符向量的形式表示
    sudoku temp;
    temp.generateSudokuGrids(Grids, num);//该函数会生成指定数量的数独棋盘，并将它们存储在Grids向量中
    for (auto grid : Grids) {
        temp.outputBoard(grid, f);//该函数将棋盘的内容写入文件中
    }
    cout << "Finish to create the sudoku board !!!" << endl;
    f.close();
}

// 对应s参数，解数独文件
void solve_sudoku(string filepath) {
    // 读取文件
    ofstream fout("sudoku.txt", ios_base::out);

    ifstream fin;
    fin.open(filepath, ios::in);
    string s;
    int index = 0;  // 标记index，如果index为9则进行求解
    vector<vector<char>>temp_vec;

    cout << "Begin to solve the sudoku game ..." << endl;
    // 逐行读取数据并存于s中，直至数据全部读取
    while(getline(fin, s)){
        // cout << s.c_str() << endl;
        vector<char> extractedChars;
        for (char c : s) {
            // c 是数独表中的元素
            if (c >= '1' && c <= '9' || c == '$') {
                extractedChars.push_back(c);
            }
        }
        //如果extractedChars向量非空，说明成功提取了有效的数独游戏数据。
        if (!extractedChars.empty()) {
            index++;
            temp_vec.push_back(extractedChars);
        }
        // 放到外层的vector之中
        // 当index等于9时表示读取到了一个完整的数独游戏。
        if (index == 9) {
            sudoku solution(temp_vec);
            solution.dfs(temp_vec, 0);//调用solution.dfs函数以求解数独游戏
            solution.outputBoard(temp_vec, fout);//调用solution.outputBoard函数，将解答写入输出文件流fout中
            
            //清空temp_vec向量和index的值，以准备读取下一个数独游戏。
            temp_vec.clear();
            index = 0;
            temp_vec.clear();
        }
    }

    cout << "Finish to solve the sudoku game !!!" << endl;
    fin.close();
    fout.close();
}

// 对应n参数，生成game数独游戏
//生成数独游戏，并将生成的游戏写入名为"game.txt"的文件中
// 默认难度为简单
void create_game(int num, int m = 1){
    // 先将曾经生成的内容清空
    ofstream f("game.txt", ios_base::out);

    cout << "Begin to create the game board ..." << endl;
    for (int i = 0; i < num; i++){
        vector<vector<char>>blank(9, vector<char>(9, '$'));
        sudoku temp(blank);
        temp.create(diff_map[m], blank);
        temp.outputBoard(blank, f);
    }
    cout << "Finish to create the game board !!!" << endl;
    f.close();
}

// 对应r参数，生成game数独游戏
void create_game_range(int num, int r) {
    // 先将曾经生成的内容清空
    ofstream f("game.txt", ios_base::out);

    cout << "Begin to create the game board ..." << endl;
    for (int i = 0; i < num; i++) {
        vector<vector<char>>blank(9, vector<char>(9, '$'));
        sudoku temp(blank);
        temp.create(r, blank);
        temp.outputBoard(blank, f);
    }
    cout << "Finish to create the game board !!!" << endl;
    f.close();
}

// 对应u参数，生成唯一解的函数，默认生成20个空
void create_game_unique(int num) {
    // 先将曾经生成的内容清空
    ofstream f("unique_game.txt", ios_base::out);

    cout << "Begin to create the game board having the unique answer ..." << endl;
    /*
    for (int i = 0; i < num; i++) {
        vector<vector<char>>blank(9, vector<char>(9, '$'));
        sudoku temp(blank);
        temp.create(20, blank);
        temp.outputBoard(blank, f);
    }
    */
    int index = 0;
    while (index < num) {
        vector<vector<char>>blank(9, vector<char>(9, '$'));
        sudoku temp(blank);
        temp.create(50, blank);
        int n = temp.countSudokuSolutions(blank);
        if (n == 1) {
        /*
        如果解的数量n等于1，表示生成的数独游戏具有唯一解，执行以下操作：
        递增计数器index，用于跟踪生成的游戏数量。
        调用temp.outputBoard函数，将生成的数独游戏写入输出文件流f中。
        打印一条消息表示生成的数独游戏解的数量以及游戏是否被接受。
        */
            index++;
            temp.outputBoard(blank, f);
            cout << "The Gen sudoku solution number: " << n << "    (Accepted)" << endl;
        }
        else {
            cout << "The Gen sudoku solution number: " << n << "    (Rejected)" << endl;
        }
    }
    cout << "Finish to create the game board having the unique answer !!!" << endl;
    f.close();
}
