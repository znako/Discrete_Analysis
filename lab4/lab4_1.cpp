#include <string.h>
#include <map>
#include <vector>
#include <iostream>
#include <algorithm>

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

void badChar(std::map<unsigned int, unsigned int>& badCharMap ,std::vector<unsigned int>& pattern){
  for (int i = 0; i < pattern.size(); i++){
    badCharMap[pattern[i]] = i;
  }
}

long long badCharShift(std::map<unsigned int, unsigned int>& badCharMap, unsigned int number, long long position){
  if (badCharMap.find(number) == badCharMap.end()){
    return position + 1;
  }
  return position - badCharMap[number];
}

std::vector<int> zFunction(std::vector<unsigned int>& pattern){
  std::vector<int> z(pattern.size());

  for (int i = 1, l = 0, r = 0; i < pattern.size(); i++){
    if (i <= r){
      z[i] = std::min(r-i+1, z[i-l]);
    }
    while (i + z[i] < pattern.size() && pattern[i + z[i]] == pattern[z[i]]){
      ++z[i];
    }
    if (i + z[i] - 1 > r){
      l = i;
      r = i + z[i] - 1;
    }
  }

  return z;
}

std::vector<int> nFunction(std::vector<unsigned int>& pattern){
  std::vector<unsigned int> reversedPattern = pattern;
  std::reverse(reversedPattern.begin(), reversedPattern.end());
  std::vector<int> n(pattern.size());
  std::vector<int> z  = zFunction(reversedPattern);
  std::reverse(z.begin(), z.end());
  
  n = z;

  return n;
}

std::vector<int> LFunction(std::vector<unsigned int>& pattern){
  std::vector<int> L(pattern.size());
  std::vector<int> n = nFunction(pattern);
  
  for (int i = 0; i < pattern.size() - 1; i++){
    int j = pattern.size() - n[i];
    if (j < pattern.size()) {
      L[j] = i;
    }
  }  
  return L;
}

std::vector<int> lFunction(std::vector<unsigned int>& pattern){
  std::vector<int> l(pattern.size() + 1);
  std::vector<int> n = nFunction(pattern);
  
  for (int i = pattern.size() - 1; i >= 0; i--){
    int j = pattern.size() - i;

    if (n[j - 1] == j) {
      l[i] = j;
    }
    else {
      l[i] = l[i + 1];
    }
  }  
  return l;
}

long long goodSufShift(long long position, std::vector<int>& L, std::vector<int>& l, size_t size){
  if (position == size - 1){
    return 1;
  }
  if (L[position + 1] != 0) {
    return size - L[position + 1] - 1;
  }
  return size - l[position + 1];
}

long long successShift(size_t size, std::vector<int>& l){
  return size - l[1];
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
  std::map<unsigned int, unsigned int> badCharMap;
  badChar(badCharMap, pattern);
  std::vector<int> L = LFunction(pattern);
  std::vector<int> l = lFunction(pattern);

  long long curPosInText = pattern.size() - 1;

  while (curPosInText < text.size()) {
    long long textIterator = curPosInText;
    long long patternIterator = pattern.size() - 1;

    while (patternIterator >= 0 && pattern[patternIterator] == text[textIterator]){
      patternIterator--;
      textIterator--;
    }
    if (patternIterator == -1) {
      std::cout << positionsInText[curPosInText - pattern.size() + 1].first << ", " << positionsInText[curPosInText - pattern.size() + 1].second << '\n';
      curPosInText += successShift(pattern.size(), l);
    }
    if (patternIterator != -1){
      curPosInText += std::max(badCharShift(badCharMap, text[textIterator], patternIterator), goodSufShift(patternIterator, L, l, pattern.size()));
    }
  }

  return 0;
}
