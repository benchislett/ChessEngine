#include "interface.h"
#include <iostream>
#include <string>
#include <vector>
#include <array>

void identifyEngine()
{
  std::cout << "id name " << ENGINE_NAME << std::endl;
  std::cout << "id author " << ENGINE_AUTHOR << std::endl;
}

void listSupportedOptions()
{
  std::cout << "uciok" << std::endl;
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
  while (1)
  {
    std::vector<std::string> tokens = tokenizeLine(getLine());
    if (tokens.size() == 0)
      continue;

    if (tokens[0].compare("uci") == 0)
    {
      identifyEngine();
      listSupportedOptions();
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
