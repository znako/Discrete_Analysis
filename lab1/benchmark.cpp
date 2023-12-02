#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>

using namespace std;
using duration_t = std::chrono::microseconds;

struct Item{
    int key;
    long long unsigned value;
};


bool cmp(const Item& a, const Item& b)
{
    return a.key < b.key;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    vector<Item> data;
    Item el;
    int maxKey = 0;

    while(cin >> el.key >> el.value){
        maxKey = max(maxKey, el.key);
        data.push_back(el);
    }
	int size = data.size();

    vector<int> cnt(maxKey + 1);

    std::chrono::time_point<std::chrono::system_clock> start_ts = std::chrono::system_clock::now();

    for(int i = 0; i < size; ++i){
        cnt[data[i].key] = cnt[data[i].key] + 1;
    }

    for(int i = 1; i <= maxKey; ++i){
        cnt[i] += cnt[i - 1];
    }

    vector<Item> result(size);

    for(int i = size - 1; i >= 0; --i){
        int index = cnt[data[i].key] - 1;
        result[index] = data[i];
        cnt[data[i].key] = cnt[data[i].key] - 1;
    }

    for(int i = 0; i < size; ++i){
        cout << result[i].key << "\t" << result[i].value << '\n';
    }
    auto end_ts = std::chrono::system_clock::now();

    uint64_t counting_sort_ts = std::chrono::duration_cast<duration_t>( end_ts - start_ts ).count();

    start_ts = std::chrono::system_clock::now();
    auto stl_input = data;
    sort(stl_input.begin(), stl_input.end(), cmp);
    for (auto el : stl_input){
        cout << el.key << '\t' << el.value << '\n';
    }
    end_ts = std::chrono::system_clock::now();
    uint64_t stl_sort_ts = std::chrono::duration_cast<duration_t>( end_ts - start_ts ).count();
    std::cout << "Counting sort time: " << counting_sort_ts <<std::endl;
    std::cout << "STL stable sort time: " << stl_sort_ts << std::endl;

    return 0;
}