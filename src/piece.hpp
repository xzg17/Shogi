#ifndef _PIECE_HPP_
#define _PIECE_HPP_

#define EMPTY 0
#define B_PAWN 1
#define B_LANCE 2
#define B_KNIGHT 3
#define B_SILVER 4
#define B_BISHOP 5
#define B_ROOK 6
#define B_GOLD 7
#define B_KING 8 
#define BP_PAWN 9
#define BP_LANCE 10
#define BP_KNIGHT 11
#define BP_SILVER 12
#define BP_BISHOP 13
#define BP_ROOK 14
#define W_PAWN 17 
#define W_LANCE 18
#define W_KNIGHT 19
#define W_SILVER 20
#define W_BISHOP 21
#define W_ROOK 22
#define W_GOLD 23
#define W_KING 24
#define WP_PAWN 25
#define WP_LANCE 26
#define WP_KNIGHT 27
#define WP_SILVER 28
#define WP_BISHOP 29
#define WP_ROOK 30
#define WALL 33
#define IS_B(n) (B_PAWN <= n <= BP_ROOK)
#define IS_W(n) (W_PAWN <= n <= WP_ROOK)
#define IS_BP(n) (BP_PAWN <= n <= BP_ROOK)
#define IS_WP(n) (WP_PAWN <= n <= WP_ROOK)

int init_board[100] = {
    WALL, WALL   , WALL    , WALL    , WALL  , WALL  , WALL  , WALL    , WALL    , WALL   ,
    WALL, W_LANCE, W_KNIGHT, W_SILVER, W_GOLD, W_KING, W_GOLD, W_SILVER, W_KNIGHT, W_LANCE,
    WALL, EMPTY  , W_ROOK  , EMPTY   , EMPTY , EMPTY , EMPTY , EMPTY   , W_BISHOP, EMPTY  ,
    WALL, W_PAWN , W_PAWN  , W_PAWN  , W_PAWN, W_PAWN, W_PAWN, W_PAWN  , W_PAWN  , W_PAWN ,
    WALL, EMPTY  , EMPTY   , EMPTY   , EMPTY , EMPTY , EMPTY , EMPTY   , EMPTY   , EMPTY  ,
    WALL, EMPTY  , EMPTY   , EMPTY   , EMPTY , EMPTY , EMPTY , EMPTY   , EMPTY   , EMPTY  ,
    WALL, EMPTY  , EMPTY   , EMPTY   , EMPTY , EMPTY , EMPTY , EMPTY   , EMPTY   , EMPTY  ,
    WALL, B_PAWN , B_PAWN  , B_PAWN  , B_PAWN, B_PAWN, B_PAWN, B_PAWN  , B_PAWN  , B_PAWN ,
    WALL, EMPTY  , B_BISHOP, EMPTY   , EMPTY , EMPTY , EMPTY , EMPTY   , B_ROOK  , EMPTY  ,
    WALL, B_LANCE, B_KNIGHT, B_SILVER, B_GOLD, B_KING, B_GOLD, B_SILVER, B_KNIGHT, B_LANCE
};

#endif
