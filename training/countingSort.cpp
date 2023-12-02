#include <vector>
#include <iostream>

int main(int argc, char const *argv[])
{
  std::vector<int> A;
  std::vector<int> C;
  std::vector<int> B;
  
  
  int num;
  int k = -1;

  while (std::cin >> num) {
    k = std::max(k, num);
    A.push_back(num);
  }
  int size = A.size();
  B.resize(size);
  
  for (int i = 0; i <= k; i++){
    C.push_back(0);
  }
  for (int i = 0; i < size; i++){
    C[A[i]] = C[A[i]] + 1;
  }
  for (int i = 1; i <= k; i++){
    C[i] = C[i] + C[i-1];
  }
  for (int i = size - 1; i >= 0; i--){
    B[C[A[i]]-1] = A[i];
    C[A[i]] -= 1;
  }
  for (int i = 0; i < size; i++){
    std::cout << B[i] << '\n';
  }

  return 0;
}
