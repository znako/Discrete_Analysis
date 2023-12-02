#include <vector>
#include <iostream>

void insertionSort(std::vector<float>& b){
  for (int j = 1; j < b.size(); j++){
    float key = b[j];
    int i = j - 1;
    while (i > 0 && b[i] > key){
      b[i+1] = b[i];
      i = i - 1;
    }
    b[i+1] = key;
  }
  
}

void bucketSort(std::vector<float>& arr, int n){
  std::vector<float> b[n];

  for (int i = 0; i < n; i++){
    int bi = (int)n*arr[i];
    b[bi].push_back(arr[i]);
  }

  for (int i = 0; i < n; i++){
    insertionSort(b[i]);
  }
  int ind = 0;
  for (int i = 0; i < n; i++){
    for (int j = 0; j < b[i].size(); j++){
      arr[ind] = b[i][j];
      ind++;
    }
  }
}

int main(int argc, char const *argv[])
{
  std::vector<float> arr = {0.45, 0.315, 0.315, 0.624, 0.362, 0.462, 0.111, 0.23, 0.87, 0.64};
  int n = arr.size();
  bucketSort(arr, n);

  for (int i = 0; i < n; i++){
    std::cout << arr[i] << "==";
  }
  return 0;
}
