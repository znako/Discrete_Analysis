#include <vector>
#include <iostream>
#include <cmath>

int main(int argc, char const *argv[])
{
  std::vector<int> A;
  std::vector<int> C;
  std::vector<int> B;
  
  
  int num;
  int k = -1;

  int d;
  std::cin >> d;

  while (std::cin >> num) {
    A.push_back(num);
  }

  int size = A.size();
  B.resize(size);

  for (int i = 1; i <= d; i++) {
    for (int j = 0; j < size; j++){
       k = std::max(k, A[j] % (int)pow(10, i) / (int)pow(10, i - 1));
    }

    C.resize(k);
    for (int j = 0; j <= k; j++){
     C[j] = 0;
    }
    for (int j = 0; j < size; j++){
      C[A[j]% (int)pow(10, i) / (int)pow(10, i - 1)] = C[A[j]% (int)pow(10, i) / (int)pow(10, i - 1)] + 1;
    }

    for (int j = 1; j <= k; j++){
      C[j] = C[j] + C[j-1];
    }
    
    for (int j = size - 1; j >= 0; j--){
      B[C[A[j] % (int)pow(10, i) / (int)pow(10, i - 1)]-1] = A[j];
      C[A[j]% (int)pow(10, i) / (int)pow(10, i - 1)] -= 1;
    }

    A = B;

  }
  
  
  for (int i = 0; i < size; i++){
    std::cout << A[i] << '\n';
  }

  return 0;
}
