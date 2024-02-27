#ifndef _BOARD_HPP_
#define _BOARD_HPP_
#include "piece.hpp"
#include <set>
#include <stack>

class Board{
    private:
    int board[100];
    int hand[14];
    std::stack<int*> history;
    std::stack<int> get_pieces;
    public:
    int turn;
    Board(){
        //board[0～10] 空欄
        //board[11～99] 盤面
        //turn 手番
        //hand[0~6] 先手持駒
        //hand[7~13] 後手持駒
        int i;
        for(i = 0;i < 100;i++){
            this->board[i] = init_board[i];
            if(i < 14){
                this->hand[i] = 0;
            };
        };
    };

    int ply(){
        return this->history.size();
    };
    
    int push(int *move){
        if(move[2] != 2){
            int move_from = move[0];
            int move_to = move[1];
            this->get_pieces.push(this->board[move_to]);
            if(this->board[move_to] != EMPTY){
                if(this->board[move_to] == W_ROOK || this->board[move_to] == WP_ROOK){
                    this->hand[0] += 1;
                }else if(this->board[move_to] == W_BISHOP || this->board[move_to] == WP_BISHOP){
                    this->hand[1] += 1;
                }else if(this->board[move_to] == W_GOLD){
                    this->hand[2] += 1;
                }else if(this->board[move_to] == W_SILVER || this->board[move_to] == WP_SILVER){
                    this->hand[3] += 1;
                }else if(this->board[move_to] == W_KNIGHT || this->board[move_to] == WP_KNIGHT){
                    this->hand[4] += 1;
                }else if(this->board[move_to] == W_LANCE || this->board[move_to] == WP_LANCE){
                    this->hand[5] += 1;
                }else if(this->board[move_to] == W_PAWN || this->board[move_to] == WP_PAWN){
                    this->hand[6] += 1;
                }else if(this->board[move_to] == B_ROOK || this->board[move_to] == BP_ROOK){
                    this->hand[7] += 1;
                }else if(this->board[move_to] == B_BISHOP || this->board[move_to] == BP_BISHOP){
                    this->hand[8] += 1;
                }else if(this->board[move_to] == B_GOLD){
                    this->hand[9] += 1;
                }else if(this->board[move_to] == B_SILVER || this->board[move_to] == BP_SILVER){
                    this->hand[10] += 1;
                }else if(this->board[move_to] == B_KNIGHT || this->board[move_to] == BP_KNIGHT){
                    this->hand[11] += 1;
                }else if(this->board[move_to] == B_LANCE|| this->board[move_to] == BP_LANCE){
                    this->hand[12] += 1;
                }else if(this->board[move_to] == B_PAWN || this->board[move_to] == BP_PAWN){
                    this->hand[13] += 1;
                };
            };
            if(move[2] == 1){
                this->board[move_to] += 8;
            }else{
                this->board[move_to] = this->board[move_from];
            };
            this->board[move_from] = EMPTY;
        }else{
            int move_to = move[1];
            if(this->turn == 1){
                if(move[0] == B_ROOK){
                    this->hand[0] -= 1;
                }else if(move[0] == B_BISHOP){
                    this->hand[1] -= 1;
                }else if(move[0] == B_GOLD){
                    this->hand[2] -= 1;
                }else if(move[0] == B_SILVER){
                    this->hand[3] -= 1;
                }else if(move[0] == B_KNIGHT){
                    this->hand[4] -= 1;
                }else if(move[0] == B_LANCE){
                    this->hand[5] -= 1;
                }else if(move[0] == B_PAWN){
                    this->hand[6] -= 1;
                };
                this->board[move_to] = move[0];
            }else if(this->turn == -1){
                if(move[0] == B_ROOK){
                    this->hand[7] -= 1;
                }else if(move[0] == B_BISHOP){
                    this->hand[8] -= 1;
                }else if(move[0] == B_GOLD){
                    this->hand[9] -= 1;
                }else if(move[0] == B_SILVER){
                    this->hand[10] -= 1;
                }else if(move[0] == B_KNIGHT){
                    this->hand[11] -= 1;
                }else if(move[0] == B_LANCE){
                    this->hand[12] -= 1;
                }else if(move[0] == B_PAWN){
                    this->hand[13] -= 1;
                };
                this->board[move_to] = move[0] + 16;
            };
        };
        this->history.push(move);
        this->turn *= -1;
    };
    int *pop(){
        int emp[3] = {-1, -1, -1};
        if(this->history.size() == 0){
            return emp;
        }else{
            int piece = this->get_pieces.top();
            int *move = this->history.top();
            this->get_pieces.pop();
            this->history.pop();
            int move_from = move[0]; //or piece
            int move_to = move[1];
            int move_type = move[2];
            if(move_type == 0){
                this->board[move_from] = this->board[move_to];
                this->board[move_to] = piece;
            }else if(move_type == 1){
                this->board[move_from] = this->board[move_to] - 8;
                this->board[move_to] = piece;
            }else if(move_type == 2){
                this->board[move_to] = EMPTY;
                if(move_from == B_ROOK){
                    hand[0] += 1;
                }else if(move_from == B_BISHOP){
                    hand[1] += 1;
                }else if(move_from == B_GOLD){
                    hand[2] += 1;
                }else if(move_from == B_SILVER){
                    hand[3] += 1;
                }else if(move_from == B_KNIGHT){
                    hand[4] += 1;
                }else if(move_from == B_LANCE){
                    hand[5] += 1;
                }else if(move_from == B_PAWN){
                    hand[6] += 1;
                }else if(move_from == W_ROOK){
                    hand[7] += 1;
                }else if(move_from == W_BISHOP){
                    hand[8] += 1;
                }else if(move_from == W_GOLD){
                    hand[9] += 1;
                }else if(move_from == W_SILVER){
                    hand[10] += 1;
                }else if(move_from == W_KNIGHT){
                    hand[11] += 1;
                }else if(move_from == W_LANCE){
                    hand[12] += 1;
                }else if(move_from == W_PAWN){
                    hand[13] += 1;
                };
            }else{
                return emp;
            };
            return move;
        };
    };

    std::set<int> direction_N(int board_num){
        std::set<int> s;
        if(board_num > 20){
            s.insert(board_num - 10);
        };
        return s;
    };
    std::set<int> direction_S(int board_num){
        std::set<int> s;
        if(board_num < 90){
            s.insert(board_num + 10);
        };
        return s;
    };
    std::set<int> direction_EW(int board_num){
        std::set<int> s;
        if(board_num % 10 != 1){
            s.insert(board_num - 1);
        };
        if(board_num % 10 != 9){
            s.insert(board_num + 1);
        };
        return s;
    };
    std::set<int> direction_NEW(int board_num){
        std::set<int> s;
        if(board_num > 20 && board_num % 10 != 1){
            s.insert(board_num - 11);
        };
        if(board_num > 20 && board_num % 10 != 9){
            s.insert(board_num - 9);
        };
        return s;
    };
    std::set<int> direction_SEW(int board_num){
        std::set<int> s;
        if(board_num < 90 && board_num % 10 != 1){
            s.insert(board_num + 9);
        };
        if(board_num < 90 && board_num % 10 != 9){
            s.insert(board_num + 11);
        };
        return s;
    };
    std::set<int> direction_KN(int board_num){
        std::set<int> s;
        if(board_num > 30 && board_num % 10 != 1){
            s.insert(board_num - 21);
        };
        if(board_num > 30 && board_num % 10 != 9){
            s.insert(board_num - 19);
        };
        return s;
    };
    std::set<int> direction_KS(int board_num){
        std::set<int> s;
        if(board_num < 80 && board_num % 10 != 1){
            s.insert(board_num + 19);
        };
        if(board_num < 80 && board_num % 10 != 9){
            s.insert(board_num + 21);
        };
        return s;
    };
    std::set<int> direction_PN(int board_num){
        std::set<int> s;
        int num = board_num;
        while(num > 20){
            num -= 10;
            s.insert(num);
            if(this->board[num] != EMPTY){
                break;
            };
        };
        return s;
    };
    std::set<int> direction_PS(int board_num){
        std::set<int> s;
        int num = board_num;
        while(num < 90){
            num += 10;
            s.insert(num);
            if(this->board[num] != EMPTY){
                break;
            };
        };
        return s;
    };
    std::set<int> direction_PEW(int board_num){
        std::set<int> s;
        int num;
        num = board_num;
        while(num % 10 != 1){
            num -= 1;
            s.insert(num);
            if(this->board[num] != EMPTY){
                break;
            };
        };
        num = board_num;
        while(num % 10 != 9){
            num += 1;
            s.insert(num);
            if(this->board[num] != EMPTY){
                break;
            };
        };
        return s;
    };
    std::set<int> direction_PB(int board_num){
        std::set<int> s;
        int num;
        num = board_num;
        while(num > 20 && num % 10 != 1){
            num -= 11;
            s.insert(num);
            if(this->board[num] != EMPTY){
                break;
            };
        };
        num = board_num;
        while(num > 20 && num % 10 != 9){
            num -= 9;
            s.insert(num);
            if(this->board[num] != EMPTY){
                break;
            };
        };
        num = board_num;
        while(num < 90 && num % 10 != 1){
            num += 9;
            s.insert(num);
            if(this->board[num] != EMPTY){
                break;
            };
        };
        num = board_num;
        while(num < 90 && num % 10 != 9){
            num += 11;
            s.insert(num);
            if(this->board[num] != EMPTY){
                break;
            };
        };
        return s;
    };
    std::set<int*> black_move(){
        std::set<int*> s;
        int n = 11;
        while(n != 100){
            int p = this->board[n];
            if(p == B_PAWN){
                for(auto i:this->direction_N(n)){
                    if(i > 20){
                        int q[3] = {n, i, 0};
                        s.insert(q);
                    };
                    if(i < 40){
                        int q[3] = {n, i, 1};
                        s.insert(q);
                    };
                };
            }else if(p == B_LANCE){
                for(auto i:this->direction_PN(n)){
                    if(i > 20){
                        int q[3] = {n, i, 0};
                        s.insert(q);
                    };
                    if(i < 40){
                        int q[3] = {n, i, 1};
                        s.insert(q);
                    };
                };
            }else if(p == B_KNIGHT){
                for(auto i:this->direction_KN(n)){
                    if(i > 30){
                        int q[3] = {n, i, 0};
                        s.insert(q);
                    };
                    if(i < 40){
                        int q[3] = {n, i, 1};
                        s.insert(q);
                    };
                };
            }else if(p == B_SILVER){
                for(auto i:this->direction_N(n)){
                    int q[3] = {n, i, 0};
                    s.insert(q);
                    if(i < 40 || n < 40){
                        int q[3] = {n, i, 1};
                        s.insert(q);
                    };
                };
                for(auto i:this->direction_NEW(n)){
                    int q[3] = {n, i, 0};
                    s.insert(q);
                    if(i < 40 || n < 40){
                        int q[3] = {n, i, 1};
                        s.insert(q);
                    };
                };
                for(auto i:this->direction_SEW(n)){
                    int q[3] = {n, i, 0};
                    s.insert(q);
                    if(i < 40 || n < 40){
                        int q[3] = {n, i, 1};
                        s.insert(q);
                    };
                };
            }else if(p == B_GOLD || p == BP_PAWN || p == BP_LANCE || p == BP_KNIGHT || p ==BP_SILVER){
                for(auto i:this->direction_N(n)){
                    int q[3] = {n, i, 0};
                    s.insert(q);
                };
                for(auto i:this->direction_S(n)){
                    int q[3] = {n, i, 0};
                    s.insert(q);
                };
                for(auto i:this->direction_EW(n)){
                    int q[3] = {n, i, 0};
                    s.insert(q);
                };
                for(auto i:this->direction_NEW(n)){
                    int q[3] = {n, i, 0};
                    s.insert(q);
                };
            }else if(p == B_KING){
                for(auto i:this->direction_N(n)){
                    int q[3] = {n, i, 0};
                    s.insert(q);
                };
                for(auto i:this->direction_S(n)){
                    int q[3] = {n, i, 0};
                    s.insert(q);
                };
                for(auto i:this->direction_EW(n)){
                    int q[3] = {n, i, 0};
                    s.insert(q);
                };
                for(auto i:this->direction_NEW(n)){
                    int q[3] = {n, i, 0};
                    s.insert(q);
                };
                for(auto i:this->direction_SEW(n)){
                    int q[3] = {n, i, 0};
                    s.insert(q);
                };
            }else if(p == B_BISHOP){
                for(auto i:this->direction_PB(n)){
                    int q[3] = {n, i, 0};
                    s.insert(q);
                    if(i < 40 || n < 40){
                        int q[3] = {n, i, 1};
                        s.insert(q);
                    };
                };
            }else if(p == BP_BISHOP){
                for(auto i:this->direction_PB(n)){
                    int q[3] = {n, i, 0};
                    s.insert(q);
                };
                for(auto i:this->direction_N(n)){
                    int q[3] = {n, i, 0};
                    s.insert(q);
                };
                for(auto i:this->direction_S(n)){
                    int q[3] = {n, i, 0};
                    s.insert(q);
                };
                for(auto i:this->direction_EW(n)){
                    int q[3] = {n, i, 0};
                    s.insert(q);
                };
            }else if(p == B_ROOK){
                for(auto i:this->direction_PN(n)){
                    int q[3] = {n, i, 0};
                    s.insert(q);
                    if(i < 40){
                        int q[3] = {n, i, 1};
                        s.insert(q);
                    };
                };
                for(auto i:this->direction_PS(n)){
                    int q[3] = {n, i, 0};
                    s.insert(q);
                    if(n < 40){
                        int q[3] = {n, i, 1};
                        s.insert(q);
                    };
                };
                for(auto i:this->direction_PEW(n)){
                    int q[3] = {n, i, 0};
                    s.insert(q);
                    if(i < 40 || n < 40){
                        int q[3] = {n, i, 1};
                        s.insert(q);
                    };
                };
            }else if(p == BP_ROOK){
                for(auto i:this->direction_PN(n)){
                    int q[3] = {n, i, 0};
                    s.insert(q);
                };
                for(auto i:this->direction_PS(n)){
                    int q[3] = {n, i, 0};
                    s.insert(q);
                };
                for(auto i:this->direction_PEW(n)){
                    int q[3] = {n, i, 0};
                    s.insert(q);
                };
                for(auto i:this->direction_NEW(n)){
                    int q[3] = {n, i, 0};
                    s.insert(q);
                };
                for(auto i:this->direction_SEW(n)){
                    int q[3] = {n, i, 0};
                    s.insert(q);
                };
            };
            n += 1;
        };
        return s;
    };
    std::set<int*> white_move(){
        std::set<int*> s;
        int n = 11;
        while(n != 100){
            int p = this->board[n];
            if(p == W_PAWN){
                for(auto i:this->direction_S(n)){
                    if(i < 90){
                        int q[3] = {n, i, 0};
                        s.insert(q);
                    };
                    if(i > 70){
                        int q[3] = {n, i, 1};
                        s.insert(q);
                    };
                };
            }else if(p == W_LANCE){
                for(auto i:this->direction_PS(n)){
                    if(i < 90){
                        int q[3] = {n, i, 0};
                        s.insert(q);
                    };
                    if(i > 70){
                        int q[3] = {n, i, 1};
                        s.insert(q);
                    };
                };
            }else if(p == W_KNIGHT){
                for(auto i:this->direction_KS(n)){
                    if(i < 80){
                        int q[3] = {n, i, 0};
                        s.insert(q);
                    };
                    if(i > 70){
                        int q[3] = {n, i, 1};
                        s.insert(q);
                    };
                };
            }else if(p == W_SILVER){
                for(auto i: this->direction_S(n)){
                    int q[3] = {n, i, 0};
                    s.insert(q);
                    if(i > 70 || n > 70){
                        int q[3] = {n, i, 1};
                        s.insert(q);
                    };
                };
                for(auto i: this->direction_NEW(n)){
                    int q[3] = {n, i, 0};
                    s.insert(q);
                    if(i > 70 || n > 70){
                        int q[3] = {n, i, 1};
                        s.insert(q);
                    };
                };
                for(auto i: this->direction_SEW(n)){
                    int q[3] = {n, i, 0};
                    s.insert(q);
                    if(i > 70 || n > 70){
                        int q[3] = {n, i, 1};
                        s.insert(q);
                    };
                };
            }else if(p == W_GOLD || p == WP_PAWN || p == WP_LANCE || p == WP_KNIGHT || p == WP_SILVER){
                for(auto i:this->direction_N(n)){
                    int q[3] = {n, i, 0};
                    s.insert(q);
                };
                for(auto i:this->direction_S(n)){
                    int q[3] = {n, i, 0};
                    s.insert(q);
                };
                for(auto i:this->direction_EW(n)){
                    int q[3] = {n, i, 0};
                    s.insert(q);
                };
                for(auto i:this->direction_SEW(n)){
                    int q[3] = {n, i, 0};
                    s.insert(q);
                };
            }else if(p == W_KING){
                for(auto i:this->direction_N(n)){
                    int q[3] = {n, i, 0};
                    s.insert(q);
                };
                for(auto i:this->direction_S(n)){
                    int q[3] = {n, i, 0};
                    s.insert(q);
                };
                for(auto i:this->direction_EW(n)){
                    int q[3] = {n, i, 0};
                    s.insert(q);
                };
                for(auto i:this->direction_NEW(n)){
                    int q[3] = {n, i, 0};
                    s.insert(q);
                };
                for(auto i:this->direction_SEW(n)){
                    int q[3] = {n, i, 0};
                    s.insert(q);
                };
            }else if(p == W_BISHOP){
                for(auto i:this->direction_PB(n)){
                    int q[3] = {n, i, 0};
                    s.insert(q);
                    if(i > 70 || n > 70){
                        int q[3] = {n, i, 1};
                        s.insert(q);
                    };
                };
            }else if(p == WP_BISHOP){
                for(auto i:this->direction_PB(n)){
                    int q[3] = {n, i, 0};
                    s.insert(q);
                };
                for(auto i:this->direction_N(n)){
                    int q[3] = {n, i, 0};
                    s.insert(q);
                };
                for(auto i:this->direction_S(n)){
                    int q[3] = {n, i, 0};
                    s.insert(q);
                };
                for(auto i:this->direction_EW(n)){
                    int q[3] = {n, i, 0};
                    s.insert(q);
                };
            }else if(p == W_ROOK){
                for(auto i:this->direction_PN(n)){
                    int q[3] = {n, i, 0};
                    s.insert(q);
                    if(n > 70){
                        int q[3] = {n, i, 1};
                        s.insert(q);
                    };
                };
                for(auto i:this->direction_PS(n)){
                    int q[3] = {n, i, 0};
                    s.insert(q);
                    if(i > 70){
                        int q[3] = {n, i, 1};
                        s.insert(q);
                    };
                };
                for(auto i:this->direction_PEW(n)){
                    int q[3] = {n, i, 0};
                    s.insert(q);
                    if(i > 70){
                        int q[3] = {n, i, 1};
                        s.insert(q);
                    };
                };
            }else if(p == WP_ROOK){
                for(auto i:this->direction_PN(n)){
                    int q[3] = {n, i, 0};
                    s.insert(q);
                };
                for(auto i:this->direction_PS(n)){
                    int q[3] = {n, i, 0};
                    s.insert(q);
                };
                for(auto i:this->direction_PEW(n)){
                    int q[3] = {n, i, 0};
                    s.insert(q);
                };
                for(auto i:this->direction_NEW(n)){
                    int q[3] = {n, i, 0};
                    s.insert(q);
                };
                for(auto i:this->direction_SEW(n)){
                    int q[3] = {n, i, 0};
                    s.insert(q);
                };
            };
            n += 1;
        };
        return s;
    };
    int is_check_bking(){
        int i, n, a;
        for(i = 11;i < 100;i++){
            if(this->board[i] == B_KING){
                n = i;
                break;
            };
        };
        if(i == 100){
            return 0;
        };
        for(auto i:this->direction_N(n)){
            a = this->board[i];
            if(IS_WP(a) || a == W_PAWN || a == W_LANCE || a == W_SILVER || a == W_GOLD || a == W_ROOK || a == W_KING){
                return 1;
            };
        };
        for(auto i:this->direction_NEW(n)){
            a = this->board[i];
            if(IS_WP(a) || a == W_SILVER || a == W_GOLD || a == W_BISHOP || a == W_KING){
                return 1;
            };
        };
        for(auto i:this->direction_S(n)){
            a = this->board[i];
            if(IS_WP(a) || a == W_GOLD || a == W_ROOK || a == W_KING){
                return 1;
            };
        };
        for(auto i:this->direction_EW(n)){
            a = this->board[i];
            if(IS_WP(a) || a == W_GOLD || a == W_ROOK || a == W_KING){
                return 1;
            };
        };
        for(auto i:this->direction_SEW(n)){
            a = this->board[i];
            if(a == W_SILVER || a == W_BISHOP || a == WP_BISHOP || a == WP_ROOK || a == W_KING){
                return 1;
            };
        };
        for(auto i:this->direction_KN(n)){
            a = this->board[i];
            if(a == W_KNIGHT){
                return 1;
            };
        };
        for(auto i:this->direction_PN(n)){
            a = this->board[i];
            if(a == W_LANCE || a == W_ROOK || a == WP_ROOK){
                return 1;
            };
        };
        for(auto i:this->direction_PS(n)){
            a = this->board[i];
            if(a == W_ROOK || a == WP_ROOK){
                return 1;
            };
        };
        for(auto i:this->direction_PEW(n)){
            a = this->board[i];
            if(a == W_ROOK || a == WP_ROOK){
                return 1;
            };
        };
        for(auto i:this->direction_PB(n)){
            a = this->board[i];
            if(a == W_BISHOP || a == WP_BISHOP){
                return 1;
            };
        };
        return 0;
    };
    int is_check_wking(){
        int i, n, a;
        for(i = 11;i < 100;i++){
            if(this->board[i] == W_KING){
                n = i;
                break;
            };
        };
        if(i == 100){
            return 0;
        };
        for(auto i:this->direction_S(n)){
            a = this->board[i];
            if(IS_BP(a) || a == B_PAWN || a == B_LANCE || a == B_SILVER || a == B_GOLD || a == B_ROOK || a == B_KING){
                return 1;
            };
        };
        for(auto i:this->direction_SEW(n)){
            a = this->board[i];
            if(IS_BP(a) || a == B_SILVER || a == B_GOLD || a == B_BISHOP || a == B_KING){
                return 1;
            };
        };
        for(auto i:this->direction_N(n)){
            a = this->board[i];
            if(IS_BP(a) || a == B_GOLD || a == B_ROOK || a == B_KING){
                return 1;
            };
        };
        for(auto i:this->direction_EW(n)){
            a = this->board[i];
            if(IS_BP(a) || a == B_GOLD || a == B_ROOK || a == B_KING){
                return 1;
            };
        };
        for(auto i:this->direction_NEW(n)){
            a = this->board[i];
            if(a == B_SILVER || a == B_BISHOP || a == BP_BISHOP || a == BP_ROOK || a == B_KING){
                return 1;
            };
        };
        for(auto i:this->direction_KS(n)){
            a = this->board[i];
            if(a == B_KNIGHT){
                return 1;
            };
        };
        for(auto i:this->direction_PS(n)){
            a = this->board[i];
            if(a == B_LANCE || a == B_ROOK || a == BP_ROOK){
                return 1;
            };
        };
        for(auto i:this->direction_PN(n)){
            a = this->board[i];
            if(a == B_ROOK || a == BP_ROOK){
                return 1;
            };
        };
        for(auto i:this->direction_PEW(n)){
            a = this->board[i];
            if(a == B_ROOK || a == BP_ROOK){
                return 1;
            };
        };
        for(auto i:this->direction_PB(n)){
            a = this->board[i];
            if(a == B_BISHOP || a == BP_BISHOP){
                return 1;
            };
        };
        return 0;
    };
            
    std::set<int*> legal_moves(){
        std::set<int*> s;
        int piece, i, j, k, n, a;
        if(this->turn == 1){
            for(auto move:this->black_move()){
                if(!IS_B(this->board[move[1]])){
                    piece = this->board[move[1]];
                    this->board[move[1]] = this->board[move[0]];
                    this->board[move[0]] = EMPTY;
                    if(this->is_check_bking()){
                        this->board[move[0]] = this->board[move[1]];
                        this->board[move[1]] = piece;
                    };
                    this->board[move[0]] = this->board[move[1]];
                    this->board[move[1]] = piece;
                    s.insert(move);
                };
            };
            std::set<int> p;
            for(i = 0;i < 100;i++){
                if(this->board[i] == EMPTY){
                    p.insert(i);
                };
            };
            if(this->hand[0] != 0){
                for(auto i:p){
                    this->board[i] = WALL;
                    if(this->is_check_bking()){
                        this->board[i] = EMPTY;
                        continue;
                    };
                    this->board[i] = EMPTY;
                    int q[3] = {B_ROOK, i, 2}; 
                    s.insert(q);
                };
            };
            if(this->hand[1] != 0){
                for(auto i:p){
                    this->board[i] = WALL;
                    if(this->is_check_bking()){
                        this->board[i] = EMPTY;
                        continue;
                    };
                    this->board[i] = EMPTY;
                    int q[3] = {B_BISHOP, i, 2}; 
                    s.insert(q);
                };
            };
            if(this->hand[2] != 0){
                for(auto i:p){
                    this->board[i] = WALL;
                    if(this->is_check_bking()){
                        this->board[i] = EMPTY;
                        continue;
                    };
                    this->board[i] = EMPTY;
                    int q[3] = {B_GOLD, i, 2}; 
                    s.insert(q);
                };
            };
            if(this->hand[3] != 0){
                for(auto i:p){
                    this->board[i] = WALL;
                    if(this->is_check_bking()){
                        this->board[i] = EMPTY;
                        continue;
                    };
                    this->board[i] = EMPTY;
                    int q[3] = {B_SILVER, i, 2}; 
                    s.insert(q);
                };
            };
            if(this->hand[4] != 0){
                for(auto i:p){
                    if(i > 30){
                        this->board[i] = WALL;
                        if(this->is_check_bking()){
                            this->board[i] = EMPTY;
                            continue;
                        };
                        this->board[i] = EMPTY;
                        int q[3] = {B_KNIGHT, i, 2}; 
                        s.insert(q);
                    };
                };
            };
            if(this->hand[5] != 0){
                for(auto i:p){
                    if(i > 20){
                        this->board[i] = WALL;
                        if(this->is_check_bking()){
                            this->board[i] = EMPTY;
                            continue;
                        };
                        this->board[i] = EMPTY;
                        int q[3] = {B_LANCE, i, 2}; 
                        s.insert(q);
                    };
                };
            };
            if(this->hand[6] != 0){
                a = -1;
                for(i = 11;i < 100;i++){
                    if(this->board[i] == B_PAWN){
                        n = i % 10;
                        for(j = 0;j < 10;j++){
                            n += 10;
                            p.erase(n);
                        };
                    };
                    if(this->board[i] == W_KING){
                        a = i;
                    };
                };
                //打ち歩詰め処理
                if(a != -1){
                    a += 10;
                    if(p.count(a)){
                        this->board[a] = B_PAWN;
                        this->turn *= -1;
                        std::set<int*> s2 = this->legal_moves();
                        if(s2.size() == 0){
                            p.erase(a);
                        };
                        this->board[a] = EMPTY;
                        this->turn *= -1;
                    }; 
                };
                for(auto i:p){
                    if(i > 20){
                        this->board[i] = WALL;
                        if(this->is_check_bking()){
                            this->board[i] = EMPTY;
                            continue;
                        };
                        this->board[i] = EMPTY;
                        int q[3] = {B_PAWN, i, 2};
                        s.insert(q);
                    };
                };
            };
        }else if(this->turn == -1){
            for(auto move:this->white_move()){
                if(!IS_W(this->board[move[1]])){
                    piece = this->board[move[1]];
                    this->board[move[1]] = this->board[move[0]];
                    this->board[move[0]] = EMPTY;
                    if(this->is_check_wking()){
                        this->board[0] = this->board[1];
                        this->board[1] = piece;
                        continue;
                    };
                    this->board[0] = this->board[1];
                    this->board[1] = piece;
                    s.insert(move);
                }
            };
            std::set<int> p;
            for(i = 11;i < 100;i++){
                if(this->board[i] == EMPTY){
                    p.insert(i);
                };
            };
            if(this->hand[7] != 0){
                for(auto i:p){
                    this->board[i] = WALL;
                    if(this->is_check_wking()){
                        this->board[i] = EMPTY;
                        continue;
                    };
                    this->board[i] = EMPTY;
                    int q[3] = {W_ROOK, i, 2};
                    s.insert(q);
                };
            };
            if(this->hand[8] != 0){
                for(auto i:p){
                    this->board[i] = WALL;
                    if(this->is_check_wking()){
                        this->board[i] = EMPTY;
                        continue;
                    };
                    this->board[i] = EMPTY;
                    int q[3] = {W_BISHOP, i, 2};
                    s.insert(q);
                };
            };
            if(this->hand[9] != 0){
                for(auto i:p){
                    this->board[i] = WALL;
                    if(this->is_check_wking()){
                        this->board[i] = EMPTY;
                        continue;
                    };
                    this->board[i] = EMPTY;
                    int q[3] = {W_GOLD, i, 2};
                    s.insert(q);
                };
            };
            if(this->hand[10] != 0){
                for(auto i:p){
                    this->board[i] = WALL;
                    if(this->is_check_wking()){
                        this->board[i] = EMPTY;
                        continue;
                    };
                    this->board[i] = EMPTY;
                    int q[3] = {W_SILVER, i, 2};
                    s.insert(q);
                };
            };
            if(this->hand[9] != 0){
                for(auto i:p){
                    this->board[i] = WALL;
                    if(this->is_check_wking()){
                        this->board[i] = EMPTY;
                        continue;
                    };
                    this->board[i] = EMPTY;
                    int q[3] = {W_GOLD, i, 2};
                    s.insert(q);
                };
            };
            if(this->hand[11] != 0){
                for(auto i:p){
                    if(i < 80){
                        this->board[i] = WALL;
                        if(this->is_check_wking()){
                            this->board[i] = EMPTY;
                            continue;
                        };
                        this->board[i] = EMPTY;
                        int q[3] = {W_KNIGHT, i, 2};
                        s.insert(q);
                    };
                };
            };
            if(this->hand[12] != 0){
                for(auto i:p){
                    if(i < 90){
                        this->board[i] = WALL;
                        if(this->is_check_wking()){
                            this->board[i] = EMPTY;
                            continue;
                        };
                        this->board[i] = EMPTY;
                        int q[3] = {W_KNIGHT, i, 2};
                        s.insert(q);
                    };
                };
            };
            if(this->hand[13] != 0){
                a = -1;
                for(i = 11;i < 100;i++){
                    if(this->board[i] == W_PAWN){
                        n = i % 10;
                        for(j = 0;j < 10;j++){
                            n += 10;
                            p.erase(n);
                        };
                    };
                    if(this->board[i] == B_KING){
                        a = i;
                    };
                };
                //打ち歩詰め処理
                if(a != -1){
                    a -= 10;
                    if(p.count(a)){
                        this->board[a] = W_PAWN;
                        this->turn *= -1;
                        std::set<int*> s2 = this->legal_moves();
                        if(s2.size() == 0){
                            p.erase(a);
                        };
                        this->board[a] = EMPTY;
                        this->turn *= -1;
                    }; 
                };
                for(auto i:p){
                    if(i < 90){
                        this->board[i] = WALL;
                        if(this->is_check_wking()){
                            this->board[i] = EMPTY;
                            continue;
                        };
                        this->board[i] = EMPTY;
                        int q[3] = {W_PAWN, i, 2};
                        s.insert(q);
                    };
                };
            };
        };
        return s;
    };
};

#endif
