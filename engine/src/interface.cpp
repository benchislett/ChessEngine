#include "interface.h"

#include "board.h"

#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <algorithm>

void identifyEngine()
{
  std::cout << "id name " << ENGINE_NAME << std::endl;
  std::cout << "id author " << ENGINE_AUTHOR << std::endl;
}

void listSupportedOptions()
{
  std::cout << "uciok" << std::endl;
}

void printDebugInfo(const Board board)
{
  std::cout << "[debug] board state: " << std::endl;
  std::cout << board << std::endl;
  std::cout << "[debug] white king: " << board.kingSquares[0][0] << std::endl;
  std::cout << "[debug] black king: " << board.kingSquares[0][1] << std::endl;
}

void setupFinished()
{
  std::cout << "readyok" << std::endl;
}

std::string getLine()
{
  std::string line;
  std::getline(std::cin, line);
  return line + "\n";
}

std::vector<std::string> tokenizeLine(const std::string line)
{
  std::vector<std::string> tokens;

  std::string word = "";
  for (const unsigned char c : line)
  {
    if (std::isspace(c))
    {
      if (!word.empty())
      {
        tokens.push_back(word);
      }

      word = "";
    }
    else
    {
      word.push_back(c);
    }
  }

  return tokens;
}

int main()
{
  bool debug = false;
  std::array<std::string, 4> acceptedTokens = {"uci", "debug", "isready", "quit"};
  Board board;
  while (1)
  {
    std::vector<std::string> tokens = tokenizeLine(getLine());
    while (tokens.size() && !std::any_of(acceptedTokens.begin(), acceptedTokens.end(), [&](std::string a) { return tokens[0].compare(a) == 0; }))
    {
      tokens.erase(tokens.begin());
    }
    if (tokens.size() == 0)
    {
      continue;
    }

    if (tokens[0].compare("uci") == 0)
    {
      identifyEngine();
      listSupportedOptions();
      continue;
    }
    if (tokens[0].compare("debug") == 0)
    {
      debug = tokens[1].compare("on") == 0;
      continue;
    }
    if (tokens[0].compare("isready") == 0)
    {
      board.resetBoard();
      if (debug)
      {
        printDebugInfo(board);
      }
      setupFinished();
      continue;
    }
    if (tokens[0].compare("quit") == 0)
    {
      break;
    }

    tokens.clear();
  }
  return 0;
}
