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


// 对应c参数，生成sudo终局文件
void create_sudo(int num){
    // 先将曾经生成的内容清空
    ofstream f("board.txt", ios_base::out);

    cout << "Begin to create the sudo board ..." << endl;
    for (int i = 0; i < num; i++){
        vector<vector<char>>blank(9, vector<char>(9, '$'));
        sudoku temp(blank);
        temp.create(0, blank);
        temp.outputBoard(blank, f);
    }
    cout << "Finish to create the sudo board !!!" << endl;
    f.close();
}

// 对应n参数，生成game数独游戏
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
