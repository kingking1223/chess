#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <array>
#include <cmath>
#include <algorithm>
#include <cstdint>

std::vector<uint8_t> board = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31};
uint8_t numericalPos;
int8_t KnightLegalMoves[8] = {-17, -15, -6, 10, 17, 15, 6, -10};
uint8_t VerticalEdgePieces[16] = {0, 7, 8, 15, 16, 23, 24, 31, 32, 39, 40, 47, 48, 55, 56, 63};
uint8_t LeftEdgeCells[8] = {0, 8, 16, 24, 32, 40, 48, 56};
uint8_t RightEdgeCells[8] = {7, 15, 23, 31, 39, 47, 55, 63};
int8_t KingLegalMoves[8] = {-9, -8, -7, -1, 1, 7, 8, 9};
sf::Sprite* promotedPawns[16] = {};
bool isWhitesTurnToMove = true;
uint8_t whiteCastleState = 5;
uint8_t blackCastleState = 5;

bool isPawnMoveLegal(uint8_t originalPosition, uint8_t newPosition, bool isWhite) {
    // Assuming white pawns move from bottom (rank 2) to top (rank 7),
    // and black pawns move from top (rank 7) to bottom (rank 2).
    if (originalPosition == newPosition) return false;
    int startRank = std::floor(originalPosition / 8); 
    int endRank = std::floor(newPosition / 8);  
    int startFile = originalPosition % 8; 
    int endFile = newPosition % 8; 

    int rankDiff = endRank - startRank; 
    int fileDiff = abs(endFile - startFile); 

    if (isWhite) {
        // White pawns can move one square forward (rank + 1).
        if (rankDiff == -1 && fileDiff == 0) {
            return true;
        }
        // White pawns can move two squares forward from the initial position (rank + 2).
        if (startRank == 6 && rankDiff == -2 && fileDiff == 0) {
            return true;
        }
        if (board[newPosition] <= 15 && rankDiff == -1 && std::abs(fileDiff) == 1) {
            return true;
        }
        if (startRank == 3 && endRank == 2 && board[newPosition] == 255 && ((endFile-startFile == -1 && board[originalPosition-1] >= 8 && board[originalPosition-1] <= 15) || (endFile-startFile == 1 && board[originalPosition+1] >=8 && board[originalPosition+1] <=15))) {
            return true;
        }
    } else { // Black
        // Black pawns can move one square forward (rank - 1).
        if (rankDiff == 1 && fileDiff == 0) {
            return true;
        }
        // Black pawns can move two squares forward from the initial position (rank - 2).
        if (startRank == 1 && rankDiff == 2 && fileDiff == 0) {
            return true;
        }
        if (board[newPosition] >= 16 && board[newPosition] <= 31 && rankDiff == 1 && std::abs(fileDiff) == 1) {
            return true;
        }
        if (startRank == 4 && endRank == 5 && board[newPosition] == 255 && ((endFile-startFile == -1 && board[originalPosition-1] >=16 && board[originalPosition-1] <=23) || (endFile-startFile == 1 && board[originalPosition+1] >= 16 && board[originalPosition+1] <=23))) {
            return true;
        }
    }

    // Pawns cannot move sideways or capture forward.
    return false;
}

bool isRookMoveLegal(uint8_t originalPosition, uint8_t newPosition) {
    if (originalPosition == newPosition) return false;
    int startRank = originalPosition / 8;
    int endRank = newPosition / 8;
    int startFile = originalPosition % 8;
    int endFile = newPosition % 8;

    // Rooks can move horizontally or vertically.
    return (startRank == endRank) || (startFile == endFile);
}

bool isKnightMoveLegal(uint8_t originalPosition, uint8_t newPosition) {
    if (originalPosition == newPosition) return false;
    int startRank = std::floor(originalPosition / 8);
    int endRank = std::floor(newPosition / 8);
    int startFile = originalPosition % 8;
    int endFile = newPosition % 8;

    int rankDiff = std::abs(endRank - startRank);
    int fileDiff = std::abs(endFile - startFile);

    // Knights move in an L-shape: 2 squares in one direction and 1 square in the other.
    return (rankDiff == 2 && fileDiff == 1) || (rankDiff == 1 && fileDiff == 2);
}

bool isBishopMoveLegal(uint8_t originalPosition, uint8_t newPosition) {
    if (originalPosition == newPosition) return false;
    int startRank = std::floor(originalPosition / 8);
    int endRank = std::floor(newPosition / 8);
    int startFile = originalPosition % 8;
    int endFile = newPosition % 8;

    // Bishops can move diagonally.
    return std::abs(endRank - startRank) == std::abs(endFile - startFile);
}

bool isQueenMoveLegal(uint8_t originalPosition, uint8_t newPosition) {
    return (isRookMoveLegal(originalPosition, newPosition) || isBishopMoveLegal(originalPosition, newPosition));
}

bool isKingMoveLegal(uint8_t originalPosition, uint8_t newPosition, bool isWhite) {
    if (originalPosition == newPosition) return false;
    int startRank = std::floor(originalPosition / 8); 
    int endRank = std::floor(newPosition / 8); 
    int startFile = originalPosition % 8; 
    int endFile = newPosition % 8; 

    int rankDiff = endRank - startRank;  
    int fileDiff = endFile - startFile;

    if (std::abs(fileDiff) == 2 && rankDiff == 0) return true;

    // Kings can move one square in any direction.
    return (std::abs(rankDiff) <= 1 && std::abs(fileDiff) <= 1);
}

std::vector<std::string> canTheyGoToThisCell2(bool isWhite, uint8_t cell) {
    std::vector<std::string> validMoves;

    if(isWhite) {
        for (uint8_t i = 16; i < 24; ++i) {
            for (uint8_t k = 0; k < 64; ++k){
                uint8_t start = std::distance(board.begin(), std::find(board.begin(), board.end(), i));
                if (isPawnMoveLegal(start, k, true)) {
                    validMoves.push_back(std::to_string(start) + "-" + std::to_string(k));
                }
            }
        }
        for (uint8_t i = 24; i <= 31; i+=7) {
            for (uint8_t k = 0; k < 64; ++k) {
                uint8_t start = std::distance(board.begin(), std::find(board.begin(), board.end(), i));
                if (isRookMoveLegal(start, k)) {
                    validMoves.push_back(std::to_string(start) + "-" + std::to_string(k));
                }
            }
        }
        for (uint8_t i = 25; i<=30; i+=5) {
            for (uint8_t k = 0; k < 64; ++k) {
                uint8_t start = std::distance(board.begin(), std::find(board.begin(), board.end(), i));
                if (isKnightMoveLegal(start, k)) {
                    validMoves.push_back(std::to_string(start) + "-" + std::to_string(k));
                }
            }
        }
        for (uint8_t i = 26; i<= 29; i+= 3) {
            for (uint8_t k = 0; k<64; ++k) {
                uint8_t start = std::distance(board.begin(), std::find(board.begin(), board.end(), i));
                if (isBishopMoveLegal(start, k)) {
                    validMoves.push_back(std::to_string(start) + "-" + std::to_string(k));
                }
            }
        }
        uint8_t i = 27;
        for (uint8_t k = 0; k< 64; ++k){
            uint8_t start = std::distance(board.begin(), std::find(board.begin(), board.end(), i));
            if (isQueenMoveLegal(start, k)) {
                validMoves.push_back(std::to_string(start) + "-" + std::to_string(k));
            }
        }
        i = 28;
        for (uint8_t k = 0; k< 64; ++k){
            uint8_t start = std::distance(board.begin(), std::find(board.begin(), board.end(), i));
            if (isKingMoveLegal(start, k, true)) {
                validMoves.push_back(std::to_string(start) + "-" + std::to_string(k));
            }
        }
    } 
    else 
    {
        for (uint8_t i = 8; i < 16; ++i) {
            for (uint8_t k = 0; k < 64; ++k){
                uint8_t start = std::distance(board.begin(), std::find(board.begin(), board.end(), i));
                if (isPawnMoveLegal(start, k, false)) {
                    validMoves.push_back(std::to_string(start) + "-" + std::to_string(k));
                }
            }
        }
        for (uint8_t i = 0; i <= 7; i+=7) {
            for (uint8_t k = 0; k < 64; ++k) {
                uint8_t start = std::distance(board.begin(), std::find(board.begin(), board.end(), i));
                if (isRookMoveLegal(start, k)) {
                    validMoves.push_back(std::to_string(start) + "-" + std::to_string(k));
                }
            }
        }
        for (uint8_t i = 1; i<=6; i+=5) {
            for (uint8_t k = 0; k < 64; ++k) {
                uint8_t start = std::distance(board.begin(), std::find(board.begin(), board.end(), i));
                if (isKnightMoveLegal(start, k)) {
                    validMoves.push_back(std::to_string(start) + "-" + std::to_string(k));
                }
            }
        }
        for (uint8_t i = 2; i<= 5; i+= 3) {
            for (uint8_t k = 0; k<64; ++k) {
                uint8_t start = std::distance(board.begin(), std::find(board.begin(), board.end(), i));
                if (isBishopMoveLegal(start, k)) {
                    validMoves.push_back(std::to_string(start) + "-" + std::to_string(k));
                }
            }
        }
        uint8_t i = 11;
        for (uint8_t k = 0; k< 64; ++k){
            uint8_t start = std::distance(board.begin(), std::find(board.begin(), board.end(), 3));
            if (isQueenMoveLegal(start, k)) {
                validMoves.push_back(std::to_string(start) + "-" + std::to_string(k));
            }
        }
        i = 12;
        for (uint8_t k = 0; k< 64; ++k){
            uint8_t start = std::distance(board.begin(), std::find(board.begin(), board.end(), 4));
            if (isKingMoveLegal(start, k, false)) {
                validMoves.push_back(std::to_string(start) + "-" + std::to_string(k) + "k");
            }
        }
    }

    return validMoves;

    // if (std::find(std::begin(validMoves), std::end(validMoves), cell) == std::end(validMoves)) return false; else return true;
}

bool canTheyGoToThisCell(bool isWhite, uint8_t cell) {
    std::vector<uint8_t> validMoves;

    if(isWhite) {
        for (uint8_t i = 16; i < 24; ++i) {
            for (uint8_t k = 0; k < 64; ++k){
                uint8_t start = std::distance(board.begin(), std::find(board.begin(), board.end(), i));
                if (isPawnMoveLegal(start, k, true)) {
                    validMoves.push_back(k);
                }
            }
        }
        for (uint8_t i = 24; i <= 31; i+=7) {
            for (uint8_t k = 0; k < 64; ++k) {
                uint8_t start = std::distance(board.begin(), std::find(board.begin(), board.end(), i));
                if (isRookMoveLegal(start, k)) {
                    validMoves.push_back(k);
                }
            }
        }
        for (uint8_t i = 25; i<=30; i+=5) {
            for (uint8_t k = 0; k < 64; ++k) {
                uint8_t start = std::distance(board.begin(), std::find(board.begin(), board.end(), i));
                if (isKnightMoveLegal(start, k)) {
                    validMoves.push_back(k);
                }
            }
        }
        for (uint8_t i = 26; i<= 29; i+= 3) {
            for (uint8_t k = 0; k<64; ++k) {
                uint8_t start = std::distance(board.begin(), std::find(board.begin(), board.end(), i));
                if (isBishopMoveLegal(start, k)) {
                    validMoves.push_back(k);
                }
            }
        }
        uint8_t i = 27;
        for (uint8_t k = 0; k< 64; ++k){
            uint8_t start = std::distance(board.begin(), std::find(board.begin(), board.end(), i));
            if (isQueenMoveLegal(start, k)) {
                validMoves.push_back(k);
            }
        }
        i = 28;
        for (uint8_t k = 0; k< 64; ++k){
            uint8_t start = std::distance(board.begin(), std::find(board.begin(), board.end(), i));
            if (isKingMoveLegal(start, k, true)) {
                validMoves.push_back(k);
            }
        }
    } 
    else 
    {
        for (uint8_t i = 8; i < 16; ++i) {
            for (uint8_t k = 0; k < 64; ++k){
                uint8_t start = std::distance(board.begin(), std::find(board.begin(), board.end(), i));
                if (isPawnMoveLegal(start, k, false)) {
                    validMoves.push_back(k);
                }
            }
        }
        for (uint8_t i = 0; i <= 7; i+=7) {
            for (uint8_t k = 0; k < 64; ++k) {
                uint8_t start = std::distance(board.begin(), std::find(board.begin(), board.end(), i));
                if (isRookMoveLegal(start, k)) {
                    validMoves.push_back(k);
                }
            }
        }
        for (uint8_t i = 1; i<=6; i+=5) {
            for (uint8_t k = 0; k < 64; ++k) {
                uint8_t start = std::distance(board.begin(), std::find(board.begin(), board.end(), i));
                if (isKnightMoveLegal(start, k)) {
                    validMoves.push_back(k);
                }
            }
        }
        for (uint8_t i = 2; i<= 5; i+= 3) {
            for (uint8_t k = 0; k<64; ++k) {
                uint8_t start = std::distance(board.begin(), std::find(board.begin(), board.end(), i));
                if (isBishopMoveLegal(start, k)) {
                    validMoves.push_back(k);
                }
            }
        }
        uint8_t i = 3;
        for (uint8_t k = 0; k< 64; ++k){
            uint8_t start = std::distance(board.begin(), std::find(board.begin(), board.end(), i));
            if (isQueenMoveLegal(start, k)) {
                validMoves.push_back(k);
            }
        }
        i = 4;
        for (uint8_t k = 0; k< 64; ++k){
            uint8_t start = std::distance(board.begin(), std::find(board.begin(), board.end(), i));
            if (isKingMoveLegal(start, k, false)) {
                validMoves.push_back(k);
            }
        }
    }

    if (std::find(std::begin(validMoves), std::end(validMoves), cell) == std::end(validMoves)) return false; else return true;
}

bool canCastle(bool isWhite, bool isKingside) {
    if (isWhite){
        if (isKingside) {
            if (whiteCastleState != 0 && board[61] == 255 && board[62] == 255 && !(canTheyGoToThisCell(false, 61)) && !(canTheyGoToThisCell(false, 62))) {
                return true;
            }
        } else {
            if (whiteCastleState != 0 && board[57] == 255 && board[58] == 255 && board[59] == 255 && !(canTheyGoToThisCell(false, 57)) && !(canTheyGoToThisCell(false, 58)) & !(canTheyGoToThisCell(false, 59))) {
                return true;
            }
        }
    } else {
        if (isKingside) {
            if (blackCastleState != 0 && board[5] == 255 && board[6] == 255 && !(canTheyGoToThisCell(true, 5)) && !(canTheyGoToThisCell(true, 6))) {
                return true;
            }
        } else {
            if (blackCastleState != 0 && board[1] == 255 && board[2] == 255 && board[3] == 255 && !(canTheyGoToThisCell(true, 1)) && !(canTheyGoToThisCell(true, 2)) && !(canTheyGoToThisCell(true, 3))) {
                return true;
            }
        }
    }

    return false;
}

bool isMovingPathBlocked(uint8_t originalPosition, uint8_t newPosition) {
    int startRank = std::floor(originalPosition / 8);
    int endRank = std::floor(newPosition / 8);
    int startFile = originalPosition % 8;
    int endFile = newPosition % 8;

    int rankDiff = std::abs(endRank - startRank);
    int fileDiff = std::abs(endFile - startFile);

    // fileDiff == 0 implies a verical move
    if (fileDiff == 0) {
        for (int i = std::max(originalPosition, newPosition); i > std::min(originalPosition, newPosition); i-=8) {
            if (board[i] != 255) return true;
        }
    } else if (rankDiff == 0) { // rankDiff == 0 implies a horizontal move
        for (int i = std::max(originalPosition, newPosition); i > std::min(originalPosition, newPosition); i-=1) {
            if (board[i] != 255) return true;
        }
    } else if (fileDiff * rankDiff != 0) {
        if (std::abs(originalPosition - newPosition) % 7 == 0) {
            for (int i = std::max(originalPosition, newPosition); i > std::min(originalPosition, newPosition); i-= 7) {
                if (board[i] != 255) return true;
            }
        } else {
            for (int i = std::max(originalPosition, newPosition); i > std::min(originalPosition, newPosition); i-= 9) {
                if (board[i] != 255) return true;
            }
        }
    }

    return false;
}

bool isSelectedPieceInListOfPromotedPawns (sf::Sprite* piece) {
    return std::find(std::begin(promotedPawns), std::end(promotedPawns), piece) != std::end(promotedPawns);
}

int handleCapture(uint8_t numericalPieceId, sf::Sprite* targetPiece, const sf::Vector2f& originalPosition, const sf::Vector2f& newPosition, bool isWhite)
{
    // Find the position in the board array of the new position
    numericalPos = ((newPosition.x - 1005) / 100) + ((newPosition.y - 105) / 100 * 8);

    // Check if the new position has an opponent's piece 
    if (((board[numericalPos] < 16 && isWhite) || ((board[numericalPos] > 15 && board[numericalPos] < 32) && !isWhite)) || board[numericalPos] == 255)
    {
        // Check if move is legal
        uint8_t numericalStartPos = ((originalPosition.x - 1005) / 100) + ((originalPosition.y - 105) / 100 * 8);
        int8_t numericalNetMovement = numericalPos - numericalStartPos;
        
        // Determine whether the move is legal
        if ((numericalPieceId == 1 && isPawnMoveLegal(numericalStartPos, numericalPos, isWhite) && !isSelectedPieceInListOfPromotedPawns(targetPiece)) ||
        (numericalPieceId == 1 && isQueenMoveLegal(numericalStartPos, numericalPos) && isSelectedPieceInListOfPromotedPawns(targetPiece)) ||
        (numericalPieceId == 2 && isRookMoveLegal(numericalStartPos, numericalPos)) ||
        (numericalPieceId == 3 && isKnightMoveLegal(numericalStartPos, numericalPos)) ||
        (numericalPieceId == 4 && isBishopMoveLegal(numericalStartPos, numericalPos)) ||
        (numericalPieceId == 5 && isQueenMoveLegal(numericalStartPos, numericalPos)) ||
        (numericalPieceId == 6 && isKingMoveLegal(numericalStartPos, numericalPos, isWhite))) {
            if (numericalPieceId != 3) {
                if (isMovingPathBlocked(numericalStartPos, numericalPos)) return -1;
            }
            // Tell which piece to remove
            if (numericalPieceId == 1) {
                if ((newPosition.y == 105 && isWhite) || (newPosition.y == 805 && !isWhite)) {
                    return board[numericalPos] + 32;
                }
                if (numericalNetMovement != -8 && numericalNetMovement != -16 && numericalNetMovement != 8 && numericalNetMovement != 16) {
                    return board[numericalPos + 8];
                }
            }

            if (numericalPieceId == 6) {
                if (numericalNetMovement == 2) {
                    if (isWhite && canCastle(true, true)) {
                        return 200;
                    } else if (!isWhite && canCastle(false, true)) {
                        return 201;
                    }
                    return -1;
                }
                if (numericalNetMovement == -2) {
                    if (isWhite && canCastle(true, false)) {
                        return 202;
                    } else if (!isWhite && canCastle(false, false)) {
                        return 203;
                    }
                    return -1;
                }
                return board[numericalPos];
            }

            return board[numericalPos];
        }
    }
    
    // No capture happened
    return -1;
}

sf::Vector2f getClosestGridPosition(const sf::Vector2f& position)
{
    int xIndex = static_cast<int>((position.x - 1000) / 100);
    int yIndex = static_cast<int>((position.y - 100) / 100);

    float newX = 1005 + xIndex * 100;
    float newY = 105 + yIndex * 100;

    return sf::Vector2f(newX, newY);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Chess & Algorithms");
    sf::View view = window.getDefaultView();
    
    sf::RectangleShape a8(sf::Vector2f(100, 100));
    a8.setFillColor(sf::Color(255, 206, 158));
    a8.setPosition(1000,100);

    sf::RectangleShape b8(sf::Vector2f(100, 100));
    b8.setFillColor(sf::Color(209, 137, 71));
    b8.setPosition(1100,100);

    sf::RectangleShape c8(sf::Vector2f(100, 100));
    c8.setFillColor(sf::Color(255, 206, 158));
    c8.setPosition(1200,100);

    sf::RectangleShape d8(sf::Vector2f(100, 100));
    d8.setFillColor(sf::Color(209, 137, 71));
    d8.setPosition(1300,100);

    sf::RectangleShape e8(sf::Vector2f(100, 100));
    e8.setFillColor(sf::Color(255, 206, 158));
    e8.setPosition(1400,100);

    sf::RectangleShape f8(sf::Vector2f(100, 100));
    f8.setFillColor(sf::Color(209, 137, 71));
    f8.setPosition(1500,100);

    sf::RectangleShape g8(sf::Vector2f(100, 100));
    g8.setFillColor(sf::Color(255, 206, 158));
    g8.setPosition(1600,100);

    sf::RectangleShape h8(sf::Vector2f(100, 100));
    h8.setFillColor(sf::Color(209, 137, 71));
    h8.setPosition(1700,100);

    sf::RectangleShape a7(sf::Vector2f(100, 100));
    a7.setFillColor(sf::Color(209, 137, 71));
    a7.setPosition(1000,200);

    sf::RectangleShape b7(sf::Vector2f(100, 100));
    b7.setFillColor(sf::Color(255, 206, 158));
    b7.setPosition(1100,200);

    sf::RectangleShape c7(sf::Vector2f(100, 100));
    c7.setFillColor(sf::Color(209, 137, 71));
    c7.setPosition(1200,200);

    sf::RectangleShape d7(sf::Vector2f(100, 100));
    d7.setFillColor(sf::Color(255, 206, 158));
    d7.setPosition(1300,200);

    sf::RectangleShape e7(sf::Vector2f(100, 100));
    e7.setFillColor(sf::Color(209, 137, 71));
    e7.setPosition(1400,200);

    sf::RectangleShape f7(sf::Vector2f(100, 100));
    f7.setFillColor(sf::Color(255, 206, 158));
    f7.setPosition(1500,200);

    sf::RectangleShape g7(sf::Vector2f(100, 100));
    g7.setFillColor(sf::Color(209, 137, 71));
    g7.setPosition(1600,200);

    sf::RectangleShape h7(sf::Vector2f(100, 100));
    h7.setFillColor(sf::Color(255, 206, 158));
    h7.setPosition(1700,200);

    sf::RectangleShape a6(sf::Vector2f(100, 100));
    a6.setFillColor(sf::Color(255, 206, 158));
    a6.setPosition(1000,300);

    sf::RectangleShape b6(sf::Vector2f(100, 100));
    b6.setFillColor(sf::Color(209, 137, 71));
    b6.setPosition(1100,300);

    sf::RectangleShape c6(sf::Vector2f(100, 100));
    c6.setFillColor(sf::Color(255, 206, 158));
    c6.setPosition(1200,300);

    sf::RectangleShape d6(sf::Vector2f(100, 100));
    d6.setFillColor(sf::Color(209, 137, 71));
    d6.setPosition(1300,300);

    sf::RectangleShape e6(sf::Vector2f(100, 100));
    e6.setFillColor(sf::Color(255, 206, 158));
    e6.setPosition(1400,300);

    sf::RectangleShape f6(sf::Vector2f(100, 100));
    f6.setFillColor(sf::Color(209, 137, 71));
    f6.setPosition(1500,300);

    sf::RectangleShape g6(sf::Vector2f(100, 100));
    g6.setFillColor(sf::Color(255, 206, 158));
    g6.setPosition(1600,300);

    sf::RectangleShape h6(sf::Vector2f(100, 100));
    h6.setFillColor(sf::Color(209, 137, 71));
    h6.setPosition(1700,300);

    sf::RectangleShape a5(sf::Vector2f(100, 100));
    a5.setFillColor(sf::Color(209, 137, 71));
    a5.setPosition(1000,400);

    sf::RectangleShape b5(sf::Vector2f(100, 100));
    b5.setFillColor(sf::Color(255, 206, 158));
    b5.setPosition(1100,400);

    sf::RectangleShape c5(sf::Vector2f(100, 100));
    c5.setFillColor(sf::Color(209, 137, 71));
    c5.setPosition(1200,400);

    sf::RectangleShape d5(sf::Vector2f(100, 100));
    d5.setFillColor(sf::Color(255, 206, 158));
    d5.setPosition(1300,400);

    sf::RectangleShape e5(sf::Vector2f(100, 100));
    e5.setFillColor(sf::Color(209, 137, 71));
    e5.setPosition(1400,400);

    sf::RectangleShape f5(sf::Vector2f(100, 100));
    f5.setFillColor(sf::Color(255, 206, 158));
    f5.setPosition(1500,400);

    sf::RectangleShape g5(sf::Vector2f(100, 100));
    g5.setFillColor(sf::Color(209, 137, 71));
    g5.setPosition(1600,400);

    sf::RectangleShape h5(sf::Vector2f(100, 100));
    h5.setFillColor(sf::Color(255, 206, 158));
    h5.setPosition(1700,400);

    sf::RectangleShape a4(sf::Vector2f(100, 100));
    a4.setFillColor(sf::Color(255, 206, 158));
    a4.setPosition(1000,500);

    sf::RectangleShape b4(sf::Vector2f(100, 100));
    b4.setFillColor(sf::Color(209, 137, 71));
    b4.setPosition(1100,500);

    sf::RectangleShape c4(sf::Vector2f(100, 100));
    c4.setFillColor(sf::Color(255, 206, 158));
    c4.setPosition(1200,500);

    sf::RectangleShape d4(sf::Vector2f(100, 100));
    d4.setFillColor(sf::Color(209, 137, 71));
    d4.setPosition(1300,500);

    sf::RectangleShape e4(sf::Vector2f(100, 100));
    e4.setFillColor(sf::Color(255, 206, 158));
    e4.setPosition(1400,500);

    sf::RectangleShape f4(sf::Vector2f(100, 100));
    f4.setFillColor(sf::Color(209, 137, 71));
    f4.setPosition(1500,500);

    sf::RectangleShape g4(sf::Vector2f(100, 100));
    g4.setFillColor(sf::Color(255, 206, 158));
    g4.setPosition(1600,500);

    sf::RectangleShape h4(sf::Vector2f(100, 100));
    h4.setFillColor(sf::Color(209, 137, 71));
    h4.setPosition(1700,500);

    sf::RectangleShape a3(sf::Vector2f(100, 100));
    a3.setFillColor(sf::Color(209, 137, 71));
    a3.setPosition(1000,600);

    sf::RectangleShape b3(sf::Vector2f(100, 100));
    b3.setFillColor(sf::Color(255, 206, 158));
    b3.setPosition(1100,600);

    sf::RectangleShape c3(sf::Vector2f(100, 100));
    c3.setFillColor(sf::Color(209, 137, 71));
    c3.setPosition(1200,600);

    sf::RectangleShape d3(sf::Vector2f(100, 100));
    d3.setFillColor(sf::Color(255, 206, 158));
    d3.setPosition(1300,600);

    sf::RectangleShape e3(sf::Vector2f(100, 100));
    e3.setFillColor(sf::Color(209, 137, 71));
    e3.setPosition(1400,600);

    sf::RectangleShape f3(sf::Vector2f(100, 100));
    f3.setFillColor(sf::Color(255, 206, 158));
    f3.setPosition(1500,600);

    sf::RectangleShape g3(sf::Vector2f(100, 100));
    g3.setFillColor(sf::Color(209, 137, 71));
    g3.setPosition(1600,600);

    sf::RectangleShape h3(sf::Vector2f(100, 100));
    h3.setFillColor(sf::Color(255, 206, 158));
    h3.setPosition(1700,600);

    sf::RectangleShape a2(sf::Vector2f(100, 100));
    a2.setFillColor(sf::Color(255, 206, 158));
    a2.setPosition(1000,700);

    sf::RectangleShape b2(sf::Vector2f(100, 100));
    b2.setFillColor(sf::Color(209, 137, 71));
    b2.setPosition(1100,700);

    sf::RectangleShape c2(sf::Vector2f(100, 100));
    c2.setFillColor(sf::Color(255, 206, 158));
    c2.setPosition(1200,700);

    sf::RectangleShape d2(sf::Vector2f(100, 100));
    d2.setFillColor(sf::Color(209, 137, 71));
    d2.setPosition(1300,700);

    sf::RectangleShape e2(sf::Vector2f(100, 100));
    e2.setFillColor(sf::Color(255, 206, 158));
    e2.setPosition(1400,700);

    sf::RectangleShape f2(sf::Vector2f(100, 100));
    f2.setFillColor(sf::Color(209, 137, 71));
    f2.setPosition(1500,700);

    sf::RectangleShape g2(sf::Vector2f(100, 100));
    g2.setFillColor(sf::Color(255, 206, 158));
    g2.setPosition(1600,700);

    sf::RectangleShape h2(sf::Vector2f(100, 100));
    h2.setFillColor(sf::Color(209, 137, 71));
    h2.setPosition(1700,700);

    sf::RectangleShape a1(sf::Vector2f(100, 100));
    a1.setFillColor(sf::Color(209, 137, 71));
    a1.setPosition(1000,800);

    sf::RectangleShape b1(sf::Vector2f(100, 100));
    b1.setFillColor(sf::Color(255, 206, 158));
    b1.setPosition(1100,800);

    sf::RectangleShape c1(sf::Vector2f(100, 100));
    c1.setFillColor(sf::Color(209, 137, 71));
    c1.setPosition(1200,800);

    sf::RectangleShape d1(sf::Vector2f(100, 100));
    d1.setFillColor(sf::Color(255, 206, 158));
    d1.setPosition(1300,800);

    sf::RectangleShape e1(sf::Vector2f(100, 100));
    e1.setFillColor(sf::Color(209, 137, 71));
    e1.setPosition(1400,800);

    sf::RectangleShape f1(sf::Vector2f(100, 100));
    f1.setFillColor(sf::Color(255, 206, 158));
    f1.setPosition(1500,800);

    sf::RectangleShape g1(sf::Vector2f(100, 100));
    g1.setFillColor(sf::Color(209, 137, 71));
    g1.setPosition(1600,800);

    sf::RectangleShape h1(sf::Vector2f(100, 100));
    h1.setFillColor(sf::Color(255, 206, 158));
    h1.setPosition(1700,800);

    sf::Texture B, b, K, k, N, n, P, p, Q, q, R, r;

    B.loadFromFile("../assets/pieces/B.png");
    b.loadFromFile("../assets/pieces/b.png");
    K.loadFromFile("../assets/pieces/K.png");
    k.loadFromFile("../assets/pieces/k.png");
    N.loadFromFile("../assets/pieces/N.png");
    n.loadFromFile("../assets/pieces/n.png");
    P.loadFromFile("../assets/pieces/P.png");
    p.loadFromFile("../assets/pieces/p.png");
    Q.loadFromFile("../assets/pieces/Q.png");
    q.loadFromFile("../assets/pieces/q.png");
    R.loadFromFile("../assets/pieces/R.png");
    r.loadFromFile("../assets/pieces/r.png");


    sf::Sprite a8s(r);
    sf::Sprite b8s(n);
    sf::Sprite c8s(b);
    sf::Sprite d8s(q);
    sf::Sprite e8s(k);
    sf::Sprite f8s(b);
    sf::Sprite g8s(n);
    sf::Sprite h8s(r);
    sf::Sprite a7s(p);
    sf::Sprite b7s(p);
    sf::Sprite c7s(p);
    sf::Sprite d7s(p);
    sf::Sprite e7s(p);
    sf::Sprite f7s(p);
    sf::Sprite g7s(p);
    sf::Sprite h7s(p);
    sf::Sprite a7sp(q);
    sf::Sprite b7sp(q);
    sf::Sprite c7sp(q);
    sf::Sprite d7sp(q);
    sf::Sprite e7sp(q);
    sf::Sprite f7sp(q);
    sf::Sprite g7sp(q);
    sf::Sprite h7sp(q);
    sf::Sprite a2s(P);
    sf::Sprite b2s(P);
    sf::Sprite c2s(P);
    sf::Sprite d2s(P);
    sf::Sprite e2s(P);
    sf::Sprite f2s(P);
    sf::Sprite g2s(P);
    sf::Sprite h2s(P);
    sf::Sprite a2sp(Q);
    sf::Sprite b2sp(Q);
    sf::Sprite c2sp(Q);
    sf::Sprite d2sp(Q);
    sf::Sprite e2sp(Q);
    sf::Sprite f2sp(Q);
    sf::Sprite g2sp(Q);
    sf::Sprite h2sp(Q);
    sf::Sprite a1s(R);
    sf::Sprite b1s(N);
    sf::Sprite c1s(B);
    sf::Sprite d1s(Q);
    sf::Sprite e1s(K);
    sf::Sprite f1s(B);
    sf::Sprite g1s(N);
    sf::Sprite h1s(R);

    a8s.setPosition(1005, 105);
    b8s.setPosition(1105, 105);
    c8s.setPosition(1205, 105);
    d8s.setPosition(1305, 105);
    e8s.setPosition(1405, 105);
    f8s.setPosition(1505, 105);
    g8s.setPosition(1605, 105);
    h8s.setPosition(1705, 105);
    a7s.setPosition(1005, 205);
    b7s.setPosition(1105, 205);
    c7s.setPosition(1205, 205);
    d7s.setPosition(1305, 205);
    e7s.setPosition(1405, 205);
    f7s.setPosition(1505, 205);
    g7s.setPosition(1605, 205);
    h7s.setPosition(1705, 205);

    a2s.setPosition(1005, 705);
    b2s.setPosition(1105, 705);
    c2s.setPosition(1205, 705);
    d2s.setPosition(1305, 705);
    e2s.setPosition(1405, 705);
    f2s.setPosition(1505, 705);
    g2s.setPosition(1605, 705);
    h2s.setPosition(1705, 705);
    a1s.setPosition(1005, 805);
    b1s.setPosition(1105, 805);
    c1s.setPosition(1205, 805);
    d1s.setPosition(1305, 805);
    e1s.setPosition(1405, 805);
    f1s.setPosition(1505, 805);
    g1s.setPosition(1605, 805);
    h1s.setPosition(1705, 805);

    sf::Sprite* blackPieces[16] = {&a8s, &b8s, &c8s, &d8s, &e8s, &f8s, &g8s, &h8s, &a7s, &b7s, &c7s, &d7s, &e7s, &f7s, &g7s, &h7s};
    sf::Sprite* whitePieces[16] = {&a2s, &b2s, &c2s, &d2s, &e2s, &f2s, &g2s, &h2s, &a1s, &b1s, &c1s, &d1s, &e1s, &f1s, &g1s, &h1s};
    
    sf::Sprite* pawnList[16] = {&a7s, &b7s, &c7s, &d7s, &e7s, &f7s, &g7s, &h7s, &a2s, &b2s, &c2s, &d2s, &e2s, &f2s, &g2s, &h2s};

    bool isPieceSelected = false;
    sf::Sprite* selectedPiece = nullptr;
    sf::Vector2f originalPosition;




    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            // else if (event.type == sf::Event::Resized) {
            //     // resize view
            //     view.setSize({
            //         static_cast<float>(event.size.width),
            //         static_cast<float>(event.size.height)
            //     });
            //     window.setView(view);
            //     // and align shape
            //     a8.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     b8.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     c8.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     d8.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     e8.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     f8.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     g8.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     h8.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     a7.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     b7.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     c7.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     d7.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     e7.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     f7.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     g7.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     h7.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     a6.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     b6.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     c6.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     d6.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     e6.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     f6.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     g6.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     h6.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     a5.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     b5.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     c5.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     d5.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     e5.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     f5.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     g5.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     h5.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     a4.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     b4.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     c4.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     d4.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     e4.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     f4.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     g4.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     h4.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     a3.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     b3.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     c3.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     d3.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     e3.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     f3.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     g3.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     h3.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     a2.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     b2.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     c2.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     d2.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     e2.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     f2.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     g2.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     h2.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     a1.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     b1.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     c1.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     d1.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     e1.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     f1.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     g1.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     h1.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     a8s.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     b8s.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     c8s.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     d8s.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     e8s.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     f8s.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     g8s.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     h8s.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     a7s.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     b7s.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     c7s.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     d7s.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     e7s.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     f7s.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     g7s.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     h7s.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     a2s.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     b2s.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     c2s.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     d2s.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     e2s.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     f2s.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     g2s.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     h2s.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     a1s.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     b1s.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     c1s.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     d1s.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     e1s.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     f1s.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     g1s.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            //     h1s.setPosition(window.mapPixelToCoords(sf::Vector2i{window.getSize() / 2u}));
            // }
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                
                if (!isPieceSelected)
                {
                    if (a8s.getGlobalBounds().contains(mousePosition) && !isWhitesTurnToMove)
                    {
                        isPieceSelected = true;
                        selectedPiece = &a8s;
                        originalPosition = a8s.getPosition();
                    }
                    if (b8s.getGlobalBounds().contains(mousePosition) && !isWhitesTurnToMove)
                    {
                        isPieceSelected = true;
                        selectedPiece = &b8s;
                        originalPosition = b8s.getPosition();
                    }
                    if (c8s.getGlobalBounds().contains(mousePosition) && !isWhitesTurnToMove)
                    {
                        isPieceSelected = true;
                        selectedPiece = &c8s;
                        originalPosition = c8s.getPosition();
                    }
                    if (d8s.getGlobalBounds().contains(mousePosition) && !isWhitesTurnToMove)
                    {
                        isPieceSelected = true;
                        selectedPiece = &d8s;
                        originalPosition = d8s.getPosition();
                    }
                    if (e8s.getGlobalBounds().contains(mousePosition) && !isWhitesTurnToMove)
                    {
                        isPieceSelected = true;
                        selectedPiece = &e8s;
                        originalPosition = e8s.getPosition();
                    }
                    if (f8s.getGlobalBounds().contains(mousePosition) && !isWhitesTurnToMove)
                    {
                        isPieceSelected = true;
                        selectedPiece = &f8s;
                        originalPosition = f8s.getPosition();
                    }
                    if (g8s.getGlobalBounds().contains(mousePosition) && !isWhitesTurnToMove)
                    {
                        isPieceSelected = true;
                        selectedPiece = &g8s;
                        originalPosition = g8s.getPosition();
                    }
                    if (h8s.getGlobalBounds().contains(mousePosition) && !isWhitesTurnToMove)
                    {
                        isPieceSelected = true;
                        selectedPiece = &h8s;
                        originalPosition = h8s.getPosition();
                    }
                    if (a7s.getGlobalBounds().contains(mousePosition) && !isWhitesTurnToMove)
                    {
                        isPieceSelected = true;
                        selectedPiece = &a7s;
                        originalPosition = a7s.getPosition();
                    }
                    if (b7s.getGlobalBounds().contains(mousePosition) && !isWhitesTurnToMove)
                    {
                        isPieceSelected = true;
                        selectedPiece = &b7s;
                        originalPosition = b7s.getPosition();
                    }
                    if (c7s.getGlobalBounds().contains(mousePosition) && !isWhitesTurnToMove)
                    {
                        isPieceSelected = true;
                        selectedPiece = &c7s;
                        originalPosition = c7s.getPosition();
                    }
                    if (d7s.getGlobalBounds().contains(mousePosition) && !isWhitesTurnToMove)
                    {
                        isPieceSelected = true;
                        selectedPiece = &d7s;
                        originalPosition = d7s.getPosition();
                    }
                    if (e7s.getGlobalBounds().contains(mousePosition) && !isWhitesTurnToMove)
                    {
                        isPieceSelected = true;
                        selectedPiece = &e7s;
                        originalPosition = e7s.getPosition();
                    }
                    if (f7s.getGlobalBounds().contains(mousePosition) && !isWhitesTurnToMove)
                    {
                        isPieceSelected = true;
                        selectedPiece = &f7s;
                        originalPosition = f7s.getPosition();
                    }
                    if (g7s.getGlobalBounds().contains(mousePosition) && !isWhitesTurnToMove)
                    {
                        isPieceSelected = true;
                        selectedPiece = &g7s;
                        originalPosition = g7s.getPosition();
                    }
                    if (h7s.getGlobalBounds().contains(mousePosition) && !isWhitesTurnToMove)
                    {
                        isPieceSelected = true;
                        selectedPiece = &h7s;
                        originalPosition = h7s.getPosition();
                    }
                    if (a2s.getGlobalBounds().contains(mousePosition) && isWhitesTurnToMove)
                    {
                        isPieceSelected = true;
                        selectedPiece = &a2s;
                        originalPosition = a2s.getPosition();
                    }
                    if (b2s.getGlobalBounds().contains(mousePosition) && isWhitesTurnToMove)
                    {
                        isPieceSelected = true;
                        selectedPiece = &b2s;
                        originalPosition = b2s.getPosition();
                    }
                    if (c2s.getGlobalBounds().contains(mousePosition) && isWhitesTurnToMove)
                    {
                        isPieceSelected = true;
                        selectedPiece = &c2s;
                        originalPosition = c2s.getPosition();
                    }
                    if (d2s.getGlobalBounds().contains(mousePosition) && isWhitesTurnToMove)
                    {
                        isPieceSelected = true;
                        selectedPiece = &d2s;
                        originalPosition = d2s.getPosition();
                    }
                    if (e2s.getGlobalBounds().contains(mousePosition) && isWhitesTurnToMove)
                    {
                        isPieceSelected = true;
                        selectedPiece = &e2s;
                        originalPosition = e2s.getPosition();
                    }
                    if (f2s.getGlobalBounds().contains(mousePosition) && isWhitesTurnToMove)
                    {
                        isPieceSelected = true;
                        selectedPiece = &f2s;
                        originalPosition = f2s.getPosition();
                    }
                    if (g2s.getGlobalBounds().contains(mousePosition) && isWhitesTurnToMove)
                    {
                        isPieceSelected = true;
                        selectedPiece = &g2s;
                        originalPosition = g2s.getPosition();
                    }
                    if (h2s.getGlobalBounds().contains(mousePosition) && isWhitesTurnToMove)
                    {
                        isPieceSelected = true;
                        selectedPiece = &h2s;
                        originalPosition = h2s.getPosition();
                    }
                    if (a1s.getGlobalBounds().contains(mousePosition) && isWhitesTurnToMove)
                    {
                        isPieceSelected = true;
                        selectedPiece = &a1s;
                        originalPosition = a1s.getPosition();
                    }
                    if (b1s.getGlobalBounds().contains(mousePosition) && isWhitesTurnToMove)
                    {
                        isPieceSelected = true;
                        selectedPiece = &b1s;
                        originalPosition = b1s.getPosition();
                    }
                    if (c1s.getGlobalBounds().contains(mousePosition) && isWhitesTurnToMove)
                    {
                        isPieceSelected = true;
                        selectedPiece = &c1s;
                        originalPosition = c1s.getPosition();
                    }
                    if (d1s.getGlobalBounds().contains(mousePosition) && isWhitesTurnToMove)
                    {
                        isPieceSelected = true;
                        selectedPiece = &d1s;
                        originalPosition = d1s.getPosition();
                    }
                    if (e1s.getGlobalBounds().contains(mousePosition) && isWhitesTurnToMove)
                    {
                        isPieceSelected = true;
                        selectedPiece = &e1s;
                        originalPosition = e1s.getPosition();
                    }
                    if (f1s.getGlobalBounds().contains(mousePosition) && isWhitesTurnToMove)
                    {
                        isPieceSelected = true;
                        selectedPiece = &f1s;
                        originalPosition = f1s.getPosition();
                    }
                    if (g1s.getGlobalBounds().contains(mousePosition) && isWhitesTurnToMove)
                    {
                        isPieceSelected = true;
                        selectedPiece = &g1s;
                        originalPosition = g1s.getPosition();
                    }
                    if (h1s.getGlobalBounds().contains(mousePosition) && isWhitesTurnToMove)
                    {
                        isPieceSelected = true;
                        selectedPiece = &h1s;
                        originalPosition = h1s.getPosition();
                    }
                    numericalPos = ((originalPosition.x - 1005) / 100) + ((originalPosition.y - 105) / 100 * 8);
                    board[numericalPos] = 255;
                
                }
                else
                {
                    sf::Vector2f newPosition = getClosestGridPosition(mousePosition);
                    int moveWhom = -1;
                    uint8_t numericalPieceId;
                    
                    if ((selectedPiece == &a8s) || (selectedPiece == &h8s) || (selectedPiece == &a1s) || (selectedPiece == &h1s)) numericalPieceId = 2;
                    if ((selectedPiece == &b8s) || (selectedPiece == &g8s) || (selectedPiece == &b1s) || (selectedPiece == &g1s)) numericalPieceId = 3;
                    if ((selectedPiece == &c8s) || (selectedPiece == &f8s) || (selectedPiece == &c1s) || (selectedPiece == &f1s)) numericalPieceId = 4;
                    if ((selectedPiece == &d8s) || (selectedPiece == &d1s)) numericalPieceId = 5;
                    if ((selectedPiece == &e8s) || (selectedPiece == &e1s)) numericalPieceId = 6;
                    if (std::find(std::begin(pawnList), std::end(pawnList), selectedPiece) != std::end(pawnList)) numericalPieceId = 1;
                    
                    moveWhom = handleCapture(numericalPieceId, selectedPiece, originalPosition, newPosition, (std::find(std::begin(blackPieces), std::end(blackPieces), selectedPiece)) == std::end(blackPieces));

                    // std::cout << unsigned(whiteCastleState) << std::endl;
                    // std::cout << unsigned(board[61]) << std::endl;
                    // std::cout << unsigned(board[62]) << std::endl;
                    // std::cout << unsigned(canTheyGoToThisCell(false, 61)) << std::endl;
                    // std::cout << unsigned(canTheyGoToThisCell(false, 62)) << std::endl;
                    // // for (std::string i: canTheyGoToThisCell2(false, 62)) std::cout << i << ' ' << std::endl;
                    // std::cout << canCastle(true, true) << std::endl;
                    // std::cout << moveWhom << std::endl;

                    if (moveWhom >= 200 && moveWhom <= 203) {
                        switch (moveWhom) {
                            case 200:
                                h1s.setPosition(1505, 805);
                                break;
                            case 201:
                                h8s.setPosition(1505, 105);
                                break;
                            case 202:
                                a1s.setPosition(1305, 805);
                                break;
                            case 203:
                                a8s.setPosition(1305, 105);
                                break;
                        }

                        selectedPiece->setPosition(newPosition);
                        isPieceSelected = false;
                        selectedPiece = nullptr;
                        isWhitesTurnToMove = !isWhitesTurnToMove;
                    }

                    if (selectedPiece == &e8s) blackCastleState = 0;
                    if (selectedPiece == &a8s) blackCastleState &= 0x1100;
                    if (selectedPiece == &h8s) blackCastleState &= 0x0011;
                    if (selectedPiece == &e1s) whiteCastleState = 0;
                    if (selectedPiece == &a1s) whiteCastleState &= 0x1100;
                    if (selectedPiece == &h1s) whiteCastleState &= 0x0011;

                    if (moveWhom > 31 && moveWhom < 200) {
                        numericalPos = ((newPosition.x - 1005) / 100) + ((newPosition.y - 105) / 100 * 8);
                        if (selectedPiece == &a7s) {a7s.setTexture(q);promotedPawns[0]=&a7s;}
                        if (selectedPiece == &b7s) {b7s.setTexture(q);promotedPawns[1]=&b7s;}
                        if (selectedPiece == &c7s) {c7s.setTexture(q);promotedPawns[2]=&c7s;}
                        if (selectedPiece == &d7s) {d7s.setTexture(q);promotedPawns[3]=&d7s;}
                        if (selectedPiece == &e7s) {e7s.setTexture(q);promotedPawns[4]=&e7s;}
                        if (selectedPiece == &f7s) {f7s.setTexture(q);promotedPawns[5]=&f7s;}
                        if (selectedPiece == &g7s) {g7s.setTexture(q);promotedPawns[6]=&g7s;}
                        if (selectedPiece == &h7s) {h7s.setTexture(q);promotedPawns[7]=&h7s;}
                        if (selectedPiece == &a2s) {a2s.setTexture(Q);promotedPawns[8]=&a2s;}
                        if (selectedPiece == &b2s) {b2s.setTexture(Q);promotedPawns[9]=&b2s;}
                        if (selectedPiece == &c2s) {c2s.setTexture(Q);promotedPawns[10]=&c2s;}
                        if (selectedPiece == &d2s) {d2s.setTexture(Q);promotedPawns[11]=&d2s;}
                        if (selectedPiece == &e2s) {e2s.setTexture(Q);promotedPawns[12]=&e2s;}
                        if (selectedPiece == &f2s) {f2s.setTexture(Q);promotedPawns[13]=&f2s;}
                        if (selectedPiece == &g2s) {g2s.setTexture(Q);promotedPawns[14]=&g2s;}
                        if (selectedPiece == &h2s) {h2s.setTexture(Q);promotedPawns[15]=&h2s;}

                        switch (moveWhom) {
                            case 32:
                                a8s.setPosition(-100, -100);
                                break;
                            case 33:
                                b8s.setPosition(-100, -100);
                                break;
                            case 34:
                                c8s.setPosition(-100, -100);
                                break;
                            case 35:
                                d8s.setPosition(-100, -100);
                                break;
                            case 36:
                                e8s.setPosition(-100, -100);
                                break;
                            case 37:
                                f8s.setPosition(-100, -100);
                                break;
                            case 38:
                                g8s.setPosition(-100, -100);
                                break;
                            case 39:
                                h8s.setPosition(-100, -100);
                                break;
                            case 40:
                                a7s.setPosition(-100, -100);
                                break;
                            case 41:
                                b7s.setPosition(-100, -100);
                                break;
                            case 42:
                                c7s.setPosition(-100, -100);
                                break;
                            case 43:
                                d7s.setPosition(-100, -100);
                                break;
                            case 44:
                                e7s.setPosition(-100, -100);
                                break;
                            case 45:
                                f7s.setPosition(-100, -100);
                                break;
                            case 46:
                                g7s.setPosition(-100, -100);
                                break;
                            case 47:
                                h7s.setPosition(-100, -100);
                                break;
                            case 48:
                                a2s.setPosition(-100, -100);
                                break;
                            case 49:
                                b2s.setPosition(-100, -100);
                                break;
                            case 50:
                                c2s.setPosition(-100, -100);
                                break;
                            case 51:
                                d2s.setPosition(-100, -100);
                                break;
                            case 52:
                                e2s.setPosition(-100, -100);
                                break;
                            case 53:
                                f2s.setPosition(-100, -100);
                                break;
                            case 54:
                                g2s.setPosition(-100, -100);
                                break;
                            case 55:
                                h2s.setPosition(-100, -100);
                                break;
                            case 56:
                                a1s.setPosition(-100, -100);
                                break;
                            case 57:
                                b1s.setPosition(-100, -100);
                                break;
                            case 58:
                                c1s.setPosition(-100, -100);
                                break;
                            case 59:
                               d1s.setPosition(-100, -100);
                                break;
                            case 60:
                                e1s.setPosition(-100, -100);
                                break;
                            case 61:
                                f1s.setPosition(-100, -100);
                                break;
                            case 62:
                                g1s.setPosition(-100, -100);
                                 break;
                            case 63:
                                h1s.setPosition(-100, -100);
                                 break;
                            case 287:
                                break;
                        } 

                        // selectedPiece->setPosition(newPosition);
                        isPieceSelected = false;
                        selectedPiece = nullptr;
                        isWhitesTurnToMove = !isWhitesTurnToMove;
                    }


                    if ((moveWhom >= 0 && moveWhom <= 31) || moveWhom == 255) {

                        numericalPos = ((newPosition.x - 1005) / 100) + ((newPosition.y - 105) / 100 * 8);
                        if (selectedPiece == &a8s) board[numericalPos] = 0;
                        if (selectedPiece == &b8s) board[numericalPos] = 1;
                        if (selectedPiece == &c8s) board[numericalPos] = 2;
                        if (selectedPiece == &d8s) board[numericalPos] = 3;
                        if (selectedPiece == &e8s) board[numericalPos] = 4;
                        if (selectedPiece == &f8s) board[numericalPos] = 5;
                        if (selectedPiece == &g8s) board[numericalPos] = 6;
                        if (selectedPiece == &h8s) board[numericalPos] = 7;
                        if (selectedPiece == &a7s) board[numericalPos] = 8;
                        if (selectedPiece == &b7s) board[numericalPos] = 9;
                        if (selectedPiece == &c7s) board[numericalPos] = 10;
                        if (selectedPiece == &d7s) board[numericalPos] = 11;
                        if (selectedPiece == &e7s) board[numericalPos] = 12;
                        if (selectedPiece == &f7s) board[numericalPos] = 13;
                        if (selectedPiece == &g7s) board[numericalPos] = 14;
                        if (selectedPiece == &h7s) board[numericalPos] = 15;
                        if (selectedPiece == &a2s) board[numericalPos] = 16;
                        if (selectedPiece == &b2s) board[numericalPos] = 17;
                        if (selectedPiece == &c2s) board[numericalPos] = 18;
                        if (selectedPiece == &d2s) board[numericalPos] = 19;
                        if (selectedPiece == &e2s) board[numericalPos] = 20;
                        if (selectedPiece == &f2s) board[numericalPos] = 21;
                        if (selectedPiece == &g2s) board[numericalPos] = 22;
                        if (selectedPiece == &h2s) board[numericalPos] = 23;
                        if (selectedPiece == &a1s) board[numericalPos] = 24;
                        if (selectedPiece == &b1s) board[numericalPos] = 25;
                        if (selectedPiece == &c1s) board[numericalPos] = 26;
                        if (selectedPiece == &d1s) board[numericalPos] = 27;
                        if (selectedPiece == &e1s) board[numericalPos] = 28;
                        if (selectedPiece == &f1s) board[numericalPos] = 29;
                        if (selectedPiece == &g1s) board[numericalPos] = 30;
                        if (selectedPiece == &h1s) board[numericalPos] = 31;

                        switch(moveWhom) {
                            case 0:
                                a8s.setPosition(-100, -100);
                                break;
                            case 1:
                                b8s.setPosition(-100, -100);
                                break;
                            case 2:
                                c8s.setPosition(-100, -100);
                                break;
                            case 3:
                                d8s.setPosition(-100, -100);
                                break;
                            case 4:
                                e8s.setPosition(-100, -100);
                                break;
                            case 5:
                                f8s.setPosition(-100, -100);
                                break;
                            case 6:
                                g8s.setPosition(-100, -100);
                                break;
                            case 7:
                                h8s.setPosition(-100, -100);
                                break;
                            case 8:
                                a7s.setPosition(-100, -100);
                                break;
                            case 9:
                                b7s.setPosition(-100, -100);
                                break;
                            case 10:
                                c7s.setPosition(-100, -100);
                                break;
                            case 11:
                                d7s.setPosition(-100, -100);
                                break;
                            case 12:
                                e7s.setPosition(-100, -100);
                                break;
                            case 13:
                                f7s.setPosition(-100, -100);
                                break;
                            case 14:
                                g7s.setPosition(-100, -100);
                                break;
                            case 15:
                                h7s.setPosition(-100, -100);
                                break;
                            case 16:
                                a2s.setPosition(-100, -100);
                                break;
                            case 17:
                                b2s.setPosition(-100, -100);
                                break;
                            case 18:
                                c2s.setPosition(-100, -100);
                                break;
                            case 19:
                                d2s.setPosition(-100, -100);
                                break;
                            case 20:
                                e2s.setPosition(-100, -100);
                                break;
                            case 21:
                                f2s.setPosition(-100, -100);
                                break;
                            case 22:
                                g2s.setPosition(-100, -100);
                                break;
                            case 23:
                                h2s.setPosition(-100, -100);
                                break;
                            case 24:
                                a1s.setPosition(-100, -100);
                                break;
                            case 25:
                                b1s.setPosition(-100, -100);
                                break;
                            case 26:
                                c1s.setPosition(-100, -100);
                                break;
                            case 27:
                               d1s.setPosition(-100, -100);
                                break;
                            case 28:
                                e1s.setPosition(-100, -100);
                                break;
                            case 29:
                                f1s.setPosition(-100, -100);
                                break;
                            case 30:
                                g1s.setPosition(-100, -100);
                                 break;
                            case 31:
                                h1s.setPosition(-100, -100);
                                 break;
                            case 255:
                                break;
                        }
                        

                        selectedPiece->setPosition(newPosition);
                        isPieceSelected = false;
                        selectedPiece = nullptr;
                        isWhitesTurnToMove = !isWhitesTurnToMove;
                        
                    }
                }
            }
        }

        window.clear();

        if (isPieceSelected && selectedPiece)
        {
            sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            selectedPiece->setPosition(mousePosition.x - 45,
                                    mousePosition.y - 45);
            window.draw(*selectedPiece);
        }
        
        window.draw(a1);
        window.draw(a2);
        window.draw(a3);
        window.draw(a4);
        window.draw(a5);
        window.draw(a6);
        window.draw(a7);
        window.draw(a8);
        window.draw(b1);
        window.draw(b2);
        window.draw(b3);
        window.draw(b4);
        window.draw(b5);
        window.draw(b6);
        window.draw(b7);
        window.draw(b8);
        window.draw(c1);
        window.draw(c2);
        window.draw(c3);
        window.draw(c4);
        window.draw(c5);
        window.draw(c6);
        window.draw(c7);
        window.draw(c8);
        window.draw(d1);
        window.draw(d2);
        window.draw(d3);
        window.draw(d4);
        window.draw(d5);
        window.draw(d6);
        window.draw(d7);
        window.draw(d8);
        window.draw(e1);
        window.draw(e2);
        window.draw(e3);
        window.draw(e4);
        window.draw(e5);
        window.draw(e6);
        window.draw(e7);
        window.draw(e8);
        window.draw(f1);
        window.draw(f2);
        window.draw(f3);
        window.draw(f4);
        window.draw(f5);
        window.draw(f6);
        window.draw(f7);
        window.draw(f8);
        window.draw(g1);
        window.draw(g2);
        window.draw(g3);
        window.draw(g4);
        window.draw(g5);
        window.draw(g6);
        window.draw(g7);
        window.draw(g8);
        window.draw(h1);
        window.draw(h2);
        window.draw(h3);
        window.draw(h4);
        window.draw(h5);
        window.draw(h6);
        window.draw(h7);
        window.draw(h8);
        window.draw(a8s);
        window.draw(b8s);
        window.draw(c8s);
        window.draw(d8s);
        window.draw(e8s);
        window.draw(f8s);
        window.draw(g8s);
        window.draw(h8s);
        window.draw(a7s);
        window.draw(b7s);
        window.draw(c7s);
        window.draw(d7s);
        window.draw(e7s);
        window.draw(f7s);
        window.draw(g7s);
        window.draw(h7s);

        window.draw(a2s);
        window.draw(b2s);
        window.draw(c2s);
        window.draw(d2s);
        window.draw(e2s);
        window.draw(f2s);
        window.draw(g2s);
        window.draw(h2s);
        window.draw(a1s);
        window.draw(b1s);
        window.draw(c1s);
        window.draw(d1s);
        window.draw(e1s);
        window.draw(f1s);
        window.draw(g1s);
        window.draw(h1s);
        window.display();
    }

    return 0;
}
