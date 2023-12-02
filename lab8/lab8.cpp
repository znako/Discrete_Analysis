#include <string>
#include <iostream>
#include <vector>
#include <stack>
#include <memory>
#include <chrono>
#include <map>
#include <algorithm>

using namespace std;

bool compare(const pair<int, int>& left, const pair<int, int>& right) { 
    return left.first < right.first; 
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
   
    int N, M, cols; 
    vector<pair<int, int> > segments;
    map<pair<int, int>, int> map;

    cin >> N;
    int l, r;
    for (int i = 0; i < N; i++) {
        cin >> l >> r;
        map.insert({ make_pair(l, r), i });
        segments.push_back(make_pair(l, r));
    }
    cin >> M;

    sort(begin(segments), end(segments), compare);

    int curLeft = 0;
    vector<pair<int, int> > answer;
    bool isFindLeft = true;
    while (isFindLeft) {
        
        if (curLeft >= M) {
            break;
        }

        isFindLeft = false;
        
        for (int i = segments.size() - 1; i >= 0; i--) {
            if (segments[i].first <= curLeft && segments[i].second > curLeft) {
                isFindLeft = true;
                int maxRight = segments[i].second;
                int maxInd = i;
                for (int j = i-1; j >= 0; j--) {
                    if (segments[j].second > maxRight) {
                        maxRight = segments[j].second;
                        maxInd = j;
                    }
                }
                answer.push_back(make_pair(segments[maxInd].first, maxRight));
                curLeft = maxRight;
                break;
            }
        }
    }
    if (isFindLeft) {
        cout << answer.size() << '\n';
        vector<pair<int, int> > answerOrdered(segments.size());
        for (int i = 0; i < answer.size(); i++) {
            answerOrdered[map.at(answer[i])] = make_pair(answer[i].first, answer[i].second); 
        }
        for (int i = 0; i < answerOrdered.size(); i++) {
            if (answerOrdered[i].first != 0 || answerOrdered[i].second != 0) {
                cout << answerOrdered[i].first << ' ' << answerOrdered[i].second << '\n';
            }
        }
    }
    else {
        cout << 0;
    }
}
