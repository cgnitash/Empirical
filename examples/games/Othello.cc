//  This file is part of Empirical, https://github.com/devosoft/Empirical
//  Copyright (C) Michigan State University, 2017.
//  Released under the MIT Software license; see doc/LICENSE
//
//  This is an example file demonstrating Manacala.

#include <iostream>

#include "../../games/Othello.h"

int main()
{
  emp::Othello othello;
  size_t boardSize = 8;

  //std::cout << othello.GetSquare(4,4) <<std::endl;
  
  othello.Print();
  size_t moveX = 0;
  size_t moveY = 0;
  othello.TestOver();

  while (othello.IsDone() == false) {
    //size_t player = mancala.GetCurPlayer();
    //char symbol = 'B' + (char) player;i
      if (othello.GetCurrPlayer() == 1) {std::cout << " Black's "; }
      else { std::cout<<" White's "; }
      std::cout<<"Move? " << std::endl;
      emp::vector<std::pair<int, int>> validMoves = othello.GetMoveOptions();
      for (auto el : validMoves) { std::cout<<el.first<< " " << el.second<<std::endl; }
      othello.ClearValidMoves();
      othello.ClearFlips();

      std::cin >> moveX >> moveY;

      std::pair<int, int> move = std::make_pair(moveX, moveY);

    if (moveX < 1 || moveX > boardSize) {
      std::cout << "Invalid move!! (choose an X value 1 to " << boardSize<<")" <<  std::endl;
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      continue;
    }
    if (moveY < 1 || moveY > boardSize) {
      std::cout << "Invalid move!! (choose an Y value 1 to " << boardSize<<")" <<  std::endl;
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      continue;
    }
    

    if (othello.GetSquare(moveX, moveY) != 0) {
      std::cout << "Error: Cannot move to non-empty tile" << std::endl;
      continue;
    }

    if (othello.IsMoveValid(othello.GetCurrPlayer(), move ) == 0) {
        std::cout << "Invalid Move: Must flank at least one opponent disc" <<std::endl;
        continue;
    }

    bool tryMove = othello.DoMove(othello.GetCurrPlayer(), move);
    othello.ClearFlips();

    othello.Print();

  }
  
  const size_t scoreB = othello.GetScore(1);
  const size_t scoreW = othello.GetScore(2);

  std::cout<<"Black: "<<scoreB<<" White: "<<scoreW<<std::endl<<std::endl;

  if (scoreW == scoreB) { std::cout << "TIE GAME!!" << std::endl; }
  else if (scoreW < scoreB) { std::cout << "Black Wins!!" << std::endl; }
  else { std::cout << "White Wins!!" << std::endl; }
}