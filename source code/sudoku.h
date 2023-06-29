#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <Windows.h>
using namespace std;

// N 改成用户自己输入？
const int N = 9;


// 生成随机数
int randEx(){
    LARGE_INTEGER seed; //存储性能计数器的频率和当前计数值。
    QueryPerformanceFrequency(&seed); //将当前计算机的性能计数器的频率存储到seed变量中
    QueryPerformanceCounter(&seed);// 将当前的计数值存储到seed变量中
    srand(unsigned int(seed.QuadPart));//使用seed的计数值作为随机数生成器的种子，通过调用srand函数进行初始化。

    return rand(); //调用rand函数生成一个随机数，并将其作为函数的返回值
}



class sudoku{
public:
    bool active = false;

    sudoku() {
        active = false;
    }

    sudoku(vector<vector<char>>& board){
        // printBoard(board);
        active = dfs(board, 0);
    }


    // 打印二维字符向量（数独表）的内容
    void printBoard(vector<vector<char>>& board){
        // 分割数独表的每一行
        cout << " |---|---|---|---|---|---|---|---|---| " << endl;
        for (int i = 0; i < int(board.size()); i++){
            for (int j = 0; j < int(board.size()); j++){
                cout << " | " << board[i][j];
            }
            cout << " | " << endl;
            // 输出一个水平分隔线，用于分割数独表的每一行
            cout << " |---|---|---|---|---|---|---|---|---| " << endl;
        }
    }

    // 将数独表的内容输出到给定的文件流（ofstream）中
    void outputBoard(vector<vector<char>>& board, ofstream& f){
        f << " |---|---|---|---|---|---|---|---|---| " << endl;
        for (int i = 0; i < int(board.size()); i++) {
            for (int j = 0; j < int(board.size()); j++) {
                f << " | " << board[i][j];
            }
            f << " | " << endl;
            f << " |---|---|---|---|---|---|---|---|---| " << endl;
        }
        f << endl;
    }


    // 检查在给定的数独棋盘中，某个位置放置某个数字是否有效
    bool isValid(int row, int col, int num, vector<vector<char>>& board){
        // 检查行有没有重复的，如果有返回false
        for (int i = 0; i < int(board.size()); i++){
            if (num == board[row][i] - '0'){
                return false;
            }
        }
        // 检查列有没有重复的，如果有返回false
        for (int i = 0; i < int(board.size()); i++)
        {
            if (num == board[i][col] - '0')
                return false;
        }
        // 检查数字所在的方块有没有重复的，如果有返回false
        // 在数独游戏中，除了每一行和每一列都不能出现重复数字外，还有一个限制条件是每个小的3x3方块内不能有重复的数字
        int startrow = row / 3 * 3;
        int startcol = col / 3 * 3;
        int endrow = startrow + 3;
        int endcol = startcol + 3;
        for (int i = startrow; i < endrow; i++){
            for (int j = startcol; j < endcol; j++){
                if (num == board[i][j] - '0')
                    return false;
            }
        }
        return true;

    }

    // 用于生成不用终局的求解函数，需要shuffle
    // 不用终局是啥意思
    // 实现了一个递归的数独生成算法，用于生成一个完整且有效的数独棋盘。
    bool solveSudoku_Gen(std::vector<std::vector<char>>& board) {
        // 遍历数独棋盘的每个位置
        for (int row = 0; row < N; row++) {
            for (int col = 0; col < N; col++) {
                // 如果当前位置是空白的，则进行数字的填充。
                if (board[row][col] == '$') {
                    std::vector<int> candidates = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
                    // 对候选数字进行随机打乱，以确保生成不同的数字顺序
                    std::random_device rd;
                    std::mt19937 g(rd());
                    std::shuffle(candidates.begin(), candidates.end(), g);
                    // 遍历打乱后的候选数字
                    for (char num : candidates) {
                    //  调用isValid函数，检查是否满足数独规则
                        if (isValid(row, col, num, board)) {
                        // 满足数独规则，则将当前数字转换为字符并赋值给当前位置board[row][col]
                            board[row][col] = num + '0';
                        // 递归调用solveSudoku_Gen函数，尝试填充下一个空白位置
                        // 如果递归调用返回true，表示成功填充数独，直接返回true
                            if (solveSudoku_Gen(board)) {
                                return true;
                            }
                        // 如果递归调用返回false，表示无法成功填充数独，进行回溯操作，将当前位置重新置为空白'$'，继续尝试下一个候选数字
                            board[row][col] = '$';  // 回溯
                        }
                    }
                    // 如果所有候选数字都尝试过后，仍然无法填充数独，返回false，表示无解。
                    return false;
                }
            }
        }
        // 如果遍历完整个数独棋盘，没有找到空白位置，说明数独已经填满，返回true，表示成功生成数独。
        return true;  // 数独已经填满
    }

    // 这里用于生成互不相同的数独终局
    
    void generateSudokuGrids(vector<vector<vector<char>>>& grids, int count) {
        /*
        grids：存储数独棋盘的三维字符向量
        count：要生成的数独棋盘数量
        */

       // 创建一个随机数生成器
        random_device rd;
        mt19937 g(rd());
       // 当grids中的数独棋盘数量小于count时
        while (int(grids.size()) < count) {
            // temp_sudoku，大小为N*N，初始值为'$'，表示空白位置
            vector<vector<char>> temp_sudoku(N, vector<char>(N, '$'));
            solveSudoku_Gen(temp_sudoku);// 调用solveSudoku_Gen函数，生成一个有效的数独棋盘

            // 检查生成的数独表是否已经存在于 grids 中
            if (std::find(grids.begin(), grids.end(), temp_sudoku) == grids.end()) {
            //  生成的数独棋盘不存在于grids中，则将其添加到grids中
                grids.push_back(temp_sudoku);
            }
        }
    }

    // 交换数独棋盘的两列
    void swapCol(int m, int n, vector<vector<char>>& board){
        vector<char>temp(board.size(), ' ');
        for (int i = 0; i < int(board.size()); i++){
            temp[i] = board[i][m];
            board[i][m] = board[i][n];
            board[i][n] = temp[i];
        }
    }

    // 随机选择数独棋盘中的空白位置，并将指定数量的空白位置标记为'$'
    void selectBlank(int nums, vector<vector<char>>& board){
        // srand(time(NULL));
        while (nums){
            int row = randEx() % 9;
            int col = randEx() % 9;
            //检查选择的位置(row, col)是否已经是空白位置（值为'$'）
            if (board[row][col] != '$'){
                board[row][col] = '$';
                nums--;
            }
        }
    }

    // 创建一个数独棋盘，包括了随机交换行和列以及选择空白位置的操作
    void create(int blank, vector<vector<char>>& board){
        /*
        blank：要创建的数独棋盘中空白位置的数量
        board：存储数独棋盘的二维字符向量
        
        */
        // 小九宫格中的行和列交换，有以下９种交换方式
        // 为啥是这9种
        int choice[9][2] = { {0,1},{0,2},{1,2},{3,4},{3,5},{4,5},{6,7},{6,8},{7,8} };
        // srand(time(NULL));
        // 根据随机生成的数选择交换方式
        for (int j = 0; j < 10; j++){
            int i = randEx() % 9;
            board[choice[i][0]].swap(board[choice[i][1]]);   // 随机交换两行
            swapCol(choice[i][0], choice[i][1], board);      // 随机交换两列
        }
        // 交换完行列之后再选择空白位置
        selectBlank(blank, board);    // 根据难度可以选择不同数量的空格
    }

    // 从０开始依次遍历81个格子，计算此数独
    /*解决数独谜题的深度优先搜索（DFS）算法*/
    bool dfs(vector<vector<char>>& board, int start){
        /*
        board：数独谜题
        start：需要填充的当前位置，表示当前递归调用中要处理的单元格位置，可以看作是一个线性的索引值
        start的计算方式是 row * 9 + col，其中row表示行号（0到8），col表示列号（0到8）
        */

        // 81全部遍历成功说明已经成功解出数独
        // 当start达到81时，这意味着数独谜题中的所有单元格都已成功填充
        // 函数返回true表示找到了一个成功的解
        if (start == 81){
            return true;
        }
        else{
            bool nextvalid = false;
            int row = start / 9;
            int col = start % 9;
            if (board[row][col] == '$'){
                for (int i = 1; i <= 9; i++){
                    // 从１－９依次放入空格，并判断是否合法
                    if (isValid(row, col, i, board)){
                        // 找到一个有效的数字，将其放置在当前单元格中
                        board[row][col] = i + '0';
                        // 判断此方格的下一个方格是否成功写入
                        nextvalid = dfs(board, start + 1);
                        if (!nextvalid){
                            board[row][col] = '$';  // 回溯
                        }
                    }
                }
            }
            else{
                // 如果当前单元格不为空（包含除"$"以外的数字）
                // 函数只是继续到下一个单元格，而不进行任何更改。
                nextvalid = dfs(board, start + 1);
            }
            //最后的返回语句返回nextvalid的值，它指示是否在后续单元格中找到了有效的解决方案。
            return nextvalid;
        }
    }

    // 这里用于来检查是否有唯一解，回溯法
    int solveSudoku(vector<vector<char>>& board) {
        for (int row = 0; row < N; row++) {
            for (int col = 0; col < N; col++) {
                if (board[row][col] == '$') {
                    int count = 0;
                    for (int i = 1; i <= 9; i++) {
                        if (isValid(row, col, i, board)) {
                            board[row][col] = i + '0';
                            count += solveSudoku(board);
                            //在递归调用之后，通过将当前单元格重新设置为"$"进行回溯，以便在后续迭代中探索其他数字选择
                            board[row][col] = '$';  // 回溯
                        }
                    }
                    // 函数返回累积的计数
                    return count;
                }
            }
        }

        return 1;  // 数独已经填满，返回 1
    }

    // 需要创建一个数独的副本，返回数独的解数量
    int countSudokuSolutions(vector<vector<char>>& board) {
        vector<vector<char>> copy = board;  
        return solveSudoku(copy);
    }
};
