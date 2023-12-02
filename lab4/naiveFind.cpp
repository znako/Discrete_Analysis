#include <string.h>
#include <map>
#include <vector>
#include <iostream>
#include <algorithm>
#include <chrono>
using namespace std;
using duration_t = std::chrono::microseconds;

void readPattern (std::vector<unsigned int>& pattern) {
  std::string number;
  char c = ' ';

  while (true) {
    c = getchar();

    if (c == ' ') {
      if(number.size() != 0){
        pattern.push_back(std::stoul(number));
        number.clear();
      }
    }
    else if (c == '\n'){
      if(number.size() != 0){
        pattern.push_back(std::stoul(number));
        number.clear();
      }
      break;
    }
    else if (c >= '0' && c <= '9') {
      number.push_back(c);
    }
  }
}

void readText (std::vector<unsigned int>& text, std::vector<std::pair<unsigned int, unsigned int> >& positionsInText) {
  std::string number;
  unsigned int rowNumber = 1;
  unsigned int wordNumber = 0;
  char c = ' ';

  while (true) {
    c = getchar();

    if (c == ' ') {
      if(number.size() != 0){
        wordNumber++;
        positionsInText.emplace_back(rowNumber, wordNumber);
        text.push_back(std::stoul(number));
        number.clear();
      }
    }
    else if (c == '\n'){
      if(number.size() != 0){
        wordNumber++;
        positionsInText.emplace_back(rowNumber, wordNumber);
        text.push_back(std::stoul(number));
        number.clear();
      }
      wordNumber = 0;
      rowNumber++;
    }
    else if (c == EOF){
      if(number.size() != 0){
        wordNumber++;
        positionsInText.emplace_back(rowNumber, wordNumber);
        text.push_back(std::stoul(number));
      }
      break;
    }
    else if (c >= '0' && c <= '9') {
      number.push_back(c);
    }
  }
}

int main(int argc, char const *argv[])
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::vector<unsigned int> pattern;
  readPattern(pattern);
  std::vector<unsigned int> text;
  std::vector<std::pair<unsigned int, unsigned int> > positionsInText;
  readText(text, positionsInText);

  long long m = pattern.size();
  long long textPosition = 0;

  std::chrono::time_point<std::chrono::system_clock> start_ts = std::chrono::system_clock::now();
  while (textPosition < text.size()){
    long long i = textPosition;
    long long j = 0;

    while (j < m && pattern[j] == text[i]){
      j++;
      i++;
    }

    if (j == m ){
      std::cout << positionsInText[textPosition].first << ", " << positionsInText[textPosition].second << '\n';
    }
    textPosition += 1;
  }
  auto end_ts = std::chrono::system_clock::now();

  uint64_t ms_ts = std::chrono::duration_cast<duration_t>( end_ts - start_ts ).count();
  std::cout << ms_ts << "\n";
  return 0;
}
