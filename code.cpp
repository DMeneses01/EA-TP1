/* Duarte Emanuel Ramos Meneses - 2019216949
   Patricia Beatriz Silva Costa - 2019213995
   EA - Trabalho1 - 2021/2022 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct piece
{
    vector<pair<int, int>> vetor;
    int used = 0;
    int top = 1;
};

vector<piece> pieces;
vector<piece> board;
vector<vector<vector<pair<int, int>>>> map;
vector<int> count_numbers;
int num_tests = 0;
int rows = 0, columns = 0, num_pieces = 0;
int x=0, p=0, t=0, o=0;
vector<pair<int, int>> vec_pair_m;
int corners = 0;
int aux_print = 0;
vector<pair<int, int>> vec_pair;
int c = 0, r = 0, res = 0;

int check_sides(int pos) {
    int aux_vet_check = 0;
  
    if (pieces[pos].top > 2)    aux_vet_check = pieces[pos].top - 2;
    else  aux_vet_check = pieces[pos].top + 2;
    vec_pair = map[pieces[pos].vetor[aux_vet_check-1].second][pieces[pos].vetor[aux_vet_check-1].first];
    if (vec_pair.size() == 0)   return 0;
    return 1;
}

int check(int pos, int row, int col) {

    board[row*columns+col] = pieces[pos];

    if ((col == columns - 1) && (row == rows - 1)) return 1;
    
    else if (row < rows - 1) {
        if (check_sides(pos) == 0)    return 0; 
    }

    if (col < columns - 1) col++;
    else {
        col = 0;
        row++;
    }

    if (col == 0) {

        vector<pair<int, int>> vec_pair;
        int aux_vet = 0;

        if (board[(row-1)*columns+col].top > 2)    aux_vet = board[(row-1)*columns+col].top - 2;
        else  aux_vet = board[(row-1)*columns+col].top + 2;
        vec_pair = map[board[(row-1)*columns+col].vetor[aux_vet-1].second][board[(row-1)*columns+col].vetor[aux_vet-1].first];

        for (long unsigned int z = 0; z < vec_pair.size(); z++) {
            if (pieces[vec_pair[z].first].used == 0) {
                pieces[vec_pair[z].first].used = 1;

                pieces[vec_pair[z].first].top = vec_pair[z].second; 
                if (check(vec_pair[z].first, row, col)) return 1;
                pieces[vec_pair[z].first].used = 0;
            } 
        }
    }

    else if (row == 0) {

        vector<pair<int, int>> vec_pair;
        int aux_vet = 0;

        if (pieces[pos].top == 4)    aux_vet = 1;
        else  aux_vet = pieces[pos].top + 1;
        vec_pair = map[board[row*columns+(col-1)].vetor[aux_vet-1].second][board[row*columns+(col-1)].vetor[aux_vet-1].first];

        for (long unsigned int z = 0; z < vec_pair.size(); z++) {
            if (pieces[vec_pair[z].first].used == 0) {
                pieces[vec_pair[z].first].used = 1;

                if (vec_pair[z].second != 4) 
                    pieces[vec_pair[z].first].top = vec_pair[z].second + 1;
                else
                    pieces[vec_pair[z].first].top = 1;

                if (check(vec_pair[z].first, row, col)) return 1;
                pieces[vec_pair[z].first].used = 0;
            } 
        }
    }

    else  {
        vector<pair<int, int>> vec_pair;
        int aux_vet = 0;
        int aux_vet_2 = 0;

        if (pieces[pos].top == 4)    aux_vet = 1;
        else  aux_vet = pieces[pos].top + 1;
        vec_pair = map[pieces[pos].vetor[aux_vet-1].second][pieces[pos].vetor[aux_vet-1].first];
        
        if (board[(row-1)*columns+col].top > 2)    aux_vet_2 = board[(row-1)*columns+col].top - 2;
        else  aux_vet_2 = board[(row-1)*columns+col].top + 2;

        int top = 0;

        for (long unsigned int z = 0; z < vec_pair.size(); z++) {
            if (pieces[vec_pair[z].first].used == 0) {

                if (vec_pair[z].second != 4) {
                    pieces[vec_pair[z].first].top = vec_pair[z].second + 1;
                    top = vec_pair[z].second + 1;
                }
                    
                else {
                    pieces[vec_pair[z].first].top = 1;
                    top = 1;
                }

                if (((pieces[vec_pair[z].first].vetor[top - 1].second) == board[(row-1)*columns+col].vetor[aux_vet_2-1].first) && ((pieces[vec_pair[z].first].vetor[top - 1].first) == board[(row-1)*columns+col].vetor[aux_vet_2-1].second)) {
                    
                    pieces[vec_pair[z].first].used = 1;
                    if (check(vec_pair[z].first, row, col)) return 1;
                    pieces[vec_pair[z].first].used = 0;
                }   
            }
        } 
    }

    return 0;
}


int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> num_tests;

    for (int i=0; i<num_tests; i++) {

        cin >> num_pieces >> rows >> columns;

        pieces = vector<piece>(num_pieces);
        board = vector<piece>(num_pieces);
        count_numbers = vector<int>(1000);
        map = vector<vector<vector<pair<int, int>>>> (1000, vector<vector<pair<int, int>>>(1000));


        for (int k=0; k<num_pieces; k++) {
            piece pi = {};

            cin >> x >> p >> t >> o;

            count_numbers[x]++;
            count_numbers[p]++;
            count_numbers[t]++;
            count_numbers[o]++;

            map[x][p].emplace_back(k, 1);
            map[p][t].emplace_back(k, 2);
            map[t][o].emplace_back(k, 3);
            map[o][x].emplace_back(k, 4);

            pi.vetor.emplace_back(x, p);
            pi.vetor.emplace_back(p, t);
            pi.vetor.emplace_back(t, o);
            pi.vetor.emplace_back(o, x);

            pieces[k] = pi;
        }

        if (num_pieces != 1) {
            corners = 0;
            c = 0, r = 0, res = 0;

            for (int j=0; j<1000; j++) {
                if ((count_numbers[j] % 2) != 0)
                    corners++;
            }
            if (corners > 4) {
                cout << "impossible puzzle!" << "\n";
                continue;
            }

            board[0] = pieces[0];
            pieces[0].used = 1;

            if (columns == 1)  r++;
            else c++;

            if (r > 0) vec_pair_m = map[pieces[0].vetor[2].second][pieces[0].vetor[2].first];
            else vec_pair_m = map[pieces[0].vetor[1].second][pieces[0].vetor[1].first];


            for (long unsigned int z = 0; z < vec_pair_m.size(); z++) {

                pieces[vec_pair_m[z].first].used = 1;
                if (r == 0) {
                    if (vec_pair_m[z].second != 4) 
                        pieces[vec_pair_m[z].first].top = vec_pair_m[z].second + 1;
                    else
                        pieces[vec_pair_m[z].first].top = 1;
                }  
                else
                    pieces[vec_pair_m[z].first].top = vec_pair_m[z].second;  
                res = check(vec_pair_m[z].first, r, c);
                if (res == 1) break; 
                else pieces[vec_pair_m[z].first].used = 0;
            }
            
            if (res == 0)
                cout << "impossible puzzle!" << "\n";

            else {     
                for (int z = 0; z < rows; z++) {
                    for (int j = 0; j < columns; j++) {
                        cout << board[z*columns+j].vetor[board[z*columns+j].top - 1].first << " ";
                        cout << board[z*columns+j].vetor[board[z*columns+j].top - 1].second;
                        if (j < columns - 1) cout  << "  ";
                    }
                    cout << "\n";
                    for (int j = 0; j < columns; j++) {
                        if (board[z*columns+j].top > 2)    aux_print = board[z*columns+j].top - 2;
                        else  aux_print = board[z*columns+j].top + 2;
                        cout << board[z*columns+j].vetor[aux_print - 1].second << " ";
                        cout << board[z*columns+j].vetor[aux_print - 1].first;
                        if (j < columns - 1) cout  << "  ";
                    }
                    cout << "\n";
                    if (z < rows - 1)   cout << "\n";
                }
            }
        }

        else {
            cout << x << " ";
            cout << p << "\n";
            cout << o << " ";
            cout << t << "\n";
        }
    } 
        
    return 0;
}