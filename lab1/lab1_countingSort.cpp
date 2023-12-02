#include <iostream>
#include <vector>

using namespace std;

struct Item{
    int key;
    long long unsigned value;
};

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

    for(int i = 0; i < size; ++i){
        cnt[data[i].key] = cnt[data[i].key] + 1;
    }

    for(int i = 1; i <= maxKey; ++i){
        cnt[i] += cnt[i - 1];
    }

    vector<Item> result(size);

    for(int i = 0; i < size; ++i){
        int index = cnt[data[i].key] - 1;
        
        result[index] = data[i];
        cnt[data[i].key] = cnt[data[i].key] - 1;
        // cout << index << "\n";
    }

    for(int i = 0; i < size; ++i){
        cout << result[i].key << "\t" << result[i].value << '\n';
    }
    return 0;
}

