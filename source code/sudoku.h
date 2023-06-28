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

// N �ĳ��û��Լ����룿
const int N = 9;


// ���������
int randEx(){
    LARGE_INTEGER seed; //�洢���ܼ�������Ƶ�ʺ͵�ǰ����ֵ��
    QueryPerformanceFrequency(&seed); //����ǰ����������ܼ�������Ƶ�ʴ洢��seed������
    QueryPerformanceCounter(&seed);// ����ǰ�ļ���ֵ�洢��seed������
    srand(unsigned int(seed.QuadPart));//ʹ��seed�ļ���ֵ��Ϊ����������������ӣ�ͨ������srand�������г�ʼ����

    return rand(); //����rand��������һ�����������������Ϊ�����ķ���ֵ
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


    // ��ӡ��ά�ַ�������������������
    void printBoard(vector<vector<char>>& board){
        // �ָ��������ÿһ��
        cout << " |---|---|---|---|---|---|---|---|---| " << endl;
        for (int i = 0; i < int(board.size()); i++){
            for (int j = 0; j < int(board.size()); j++){
                cout << " | " << board[i][j];
            }
            cout << " | " << endl;
            // ���һ��ˮƽ�ָ��ߣ����ڷָ��������ÿһ��
            cout << " |---|---|---|---|---|---|---|---|---| " << endl;
        }
    }

    // �������������������������ļ�����ofstream����
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


    // ����ڸ��������������У�ĳ��λ�÷���ĳ�������Ƿ���Ч
    bool isValid(int row, int col, int num, vector<vector<char>>& board){
        // �������û���ظ��ģ�����з���false
        for (int i = 0; i < int(board.size()); i++){
            if (num == board[row][i] - '0'){
                return false;
            }
        }
        // �������û���ظ��ģ�����з���false
        for (int i = 0; i < int(board.size()); i++)
        {
            if (num == board[i][col] - '0')
                return false;
        }
        // ����������ڵķ�����û���ظ��ģ�����з���false
        // ��������Ϸ�У�����ÿһ�к�ÿһ�ж����ܳ����ظ������⣬����һ������������ÿ��С��3x3�����ڲ������ظ�������
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

    // �������ɲ����վֵ���⺯������Ҫshuffle
    // �����վ���ɶ��˼
    // ʵ����һ���ݹ�����������㷨����������һ����������Ч���������̡�
    bool solveSudoku_Gen(std::vector<std::vector<char>>& board) {
        // �����������̵�ÿ��λ��
        for (int row = 0; row < N; row++) {
            for (int col = 0; col < N; col++) {
                // �����ǰλ���ǿհ׵ģ���������ֵ���䡣
                if (board[row][col] == '$') {
                    std::vector<int> candidates = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
                    // �Ժ�ѡ���ֽ���������ң���ȷ�����ɲ�ͬ������˳��
                    std::random_device rd;
                    std::mt19937 g(rd());
                    std::shuffle(candidates.begin(), candidates.end(), g);
                    // �������Һ�ĺ�ѡ����
                    for (char num : candidates) {
                    //  ����isValid����������Ƿ�������������
                        if (isValid(row, col, num, board)) {
                        // �������������򽫵�ǰ����ת��Ϊ�ַ�����ֵ����ǰλ��board[row][col]
                            board[row][col] = num + '0';
                        // �ݹ����solveSudoku_Gen���������������һ���հ�λ��
                        // ����ݹ���÷���true����ʾ�ɹ����������ֱ�ӷ���true
                            if (solveSudoku_Gen(board)) {
                                return true;
                            }
                        // ����ݹ���÷���false����ʾ�޷��ɹ�������������л��ݲ���������ǰλ��������Ϊ�հ�'$'������������һ����ѡ����
                            board[row][col] = '$';  // ����
                        }
                    }
                    // ������к�ѡ���ֶ����Թ�����Ȼ�޷��������������false����ʾ�޽⡣
                    return false;
                }
            }
        }
        // ��������������������̣�û���ҵ��հ�λ�ã�˵�������Ѿ�����������true����ʾ�ɹ�����������
        return true;  // �����Ѿ�����
    }

    // �����������ɻ�����ͬ�������վ�
    
    void generateSudokuGrids(vector<vector<vector<char>>>& grids, int count) {
        /*
        grids���洢�������̵���ά�ַ�����
        count��Ҫ���ɵ�������������
        */

       // ����һ�������������
        random_device rd;
        mt19937 g(rd());
       // ��grids�е�������������С��countʱ
        while (int(grids.size()) < count) {
            // temp_sudoku����СΪN*N����ʼֵΪ'$'����ʾ�հ�λ��
            vector<vector<char>> temp_sudoku(N, vector<char>(N, '$'));
            solveSudoku_Gen(temp_sudoku);// ����solveSudoku_Gen����������һ����Ч����������

            // ������ɵ��������Ƿ��Ѿ������� grids ��
            if (std::find(grids.begin(), grids.end(), temp_sudoku) == grids.end()) {
            //  ���ɵ��������̲�������grids�У�������ӵ�grids��
                grids.push_back(temp_sudoku);
            }
        }
    }

    // �����������̵�����
    void swapCol(int m, int n, vector<vector<char>>& board){
        vector<char>temp(board.size(), ' ');
        for (int i = 0; i < int(board.size()); i++){
            temp[i] = board[i][m];
            board[i][m] = board[i][n];
            board[i][n] = temp[i];
        }
    }

    // ���ѡ�����������еĿհ�λ�ã�����ָ�������Ŀհ�λ�ñ��Ϊ'$'
    void selectBlank(int nums, vector<vector<char>>& board){
        // srand(time(NULL));
        while (nums){
            int row = randEx() % 9;
            int col = randEx() % 9;
            //���ѡ���λ��(row, col)�Ƿ��Ѿ��ǿհ�λ�ã�ֵΪ'$'��
            if (board[row][col] != '$'){
                board[row][col] = '$';
                nums--;
            }
        }
    }

    // ����һ���������̣���������������к����Լ�ѡ��հ�λ�õĲ���
    void create(int blank, vector<vector<char>>& board){
        /*
        blank��Ҫ���������������пհ�λ�õ�����
        board���洢�������̵Ķ�ά�ַ�����
        
        */
        // С�Ź����е��к��н����������£��ֽ�����ʽ
        // Ϊɶ����9��
        int choice[9][2] = { {0,1},{0,2},{1,2},{3,4},{3,5},{4,5},{6,7},{6,8},{7,8} };
        // srand(time(NULL));
        // ����������ɵ���ѡ�񽻻���ʽ
        for (int j = 0; j < 10; j++){
            int i = randEx() % 9;
            board[choice[i][0]].swap(board[choice[i][1]]);   // �����������
            swapCol(choice[i][0], choice[i][1], board);      // �����������
        }
        // ����������֮����ѡ��հ�λ��
        selectBlank(blank, board);    // �����Ѷȿ���ѡ��ͬ�����Ŀո�
    }

    // �ӣ���ʼ���α���81�����ӣ����������
    /*�������������������������DFS���㷨*/
    bool dfs(vector<vector<char>>& board, int start){
        /*
        board����������
        start����Ҫ���ĵ�ǰλ�ã���ʾ��ǰ�ݹ������Ҫ����ĵ�Ԫ��λ�ã����Կ�����һ�����Ե�����ֵ
        start�ļ��㷽ʽ�� row * 9 + col������row��ʾ�кţ�0��8����col��ʾ�кţ�0��8��
        */

        // 81ȫ�������ɹ�˵���Ѿ��ɹ��������
        // ��start�ﵽ81ʱ������ζ�����������е����е�Ԫ���ѳɹ����
        // ��������true��ʾ�ҵ���һ���ɹ��Ľ�
        if (start == 81){
            return true;
        }
        else{
            bool nextvalid = false;
            int row = start / 9;
            int col = start % 9;
            if (board[row][col] == '$'){
                for (int i = 1; i <= 9; i++){
                    // �ӣ��������η���ո񣬲��ж��Ƿ�Ϸ�
                    if (isValid(row, col, i, board)){
                        // �ҵ�һ����Ч�����֣���������ڵ�ǰ��Ԫ����
                        board[row][col] = i + '0';
                        // �жϴ˷������һ�������Ƿ�ɹ�д��
                        nextvalid = dfs(board, start + 1);
                        if (!nextvalid){
                            board[row][col] = '$';  // ����
                        }
                    }
                }
            }
            else{
                // �����ǰ��Ԫ��Ϊ�գ�������"$"��������֣�
                // ����ֻ�Ǽ�������һ����Ԫ�񣬶��������κθ��ġ�
                nextvalid = dfs(board, start + 1);
            }
            //���ķ�����䷵��nextvalid��ֵ����ָʾ�Ƿ��ں�����Ԫ�����ҵ�����Ч�Ľ��������
            return nextvalid;
        }
    }

    // ��������������Ƿ���Ψһ�⣬���ݷ�
    int solveSudoku(vector<vector<char>>& board) {
        for (int row = 0; row < N; row++) {
            for (int col = 0; col < N; col++) {
                if (board[row][col] == '$') {
                    int count = 0;
                    for (int i = 1; i <= 9; i++) {
                        if (isValid(row, col, i, board)) {
                            board[row][col] = i + '0';
                            count += solveSudoku(board);
                            //�ڵݹ����֮��ͨ������ǰ��Ԫ����������Ϊ"$"���л��ݣ��Ա��ں���������̽����������ѡ��
                            board[row][col] = '$';  // ����
                        }
                    }
                    // ���������ۻ��ļ���
                    return count;
                }
            }
        }

        return 1;  // �����Ѿ����������� 1
    }

    // ��Ҫ����һ�������ĸ��������������Ľ�����
    int countSudokuSolutions(vector<vector<char>>& board) {
        vector<vector<char>> copy = board;  
        return solveSudoku(copy);
    }
};
