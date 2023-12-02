#include <string>
#include <iostream>
#include <vector>
#include <stack>
#include <memory>
#include <chrono>
#include <map>
#include <cmath>
#include <algorithm>
#include <queue>

using namespace std;

long long inf = INT64_MAX;

class Compare {
public:
    bool operator()(pair<int, long long> below, pair<int, long long> above)
    {
        if (below.second > above.second) {
            return true;
        }
        return false;
    }
};

bool BelmanFord(const int N, vector<long long > & belmanFordResult, const vector<vector<pair<int, long long> > > adjacency ) {
    
    vector<vector<long long> > distance(N + 2, vector<long long>(N + 1, inf));
    distance[0][0] = 0;

    int i;
    bool isSame;
    for (i = 1; i <= N; i++) {
        isSame = true;
        for (int v = 0; v <= N; v++) {
            if (distance[i - 1][v] == inf) {
                continue;
            }
            for (int j = 0; j < adjacency[v].size(); j++) {
                int u = adjacency[v][j].first;
                if (distance[i - 1][v] + adjacency[v][j].second < distance[i][u]) {
                    distance[i][u] = distance[i - 1][v] + adjacency[v][j].second;
                    
                }
            }
        }
        for (int u = 0; u <= N; u++) {
            isSame = isSame && distance[i][u] == distance[i - 1][u];
        }
        if (isSame) {
            break;
        }
    }
    if (!isSame) {
        for (int v = 0; v <= N; v++) {
            if (distance[N][v] == inf) {
                continue;
            }
            for (int j = 0; j < adjacency[v].size(); j++) {
                int u = adjacency[v][j].first;
                distance[N + 1][u] = distance[N][u];
                if (distance[N][v] + adjacency[v][j].second < distance[N + 1][u]) {
                    return true;
                }
            }
        }
    }
    
    for (int j = 0; j <= N; j++) {
        belmanFordResult[j] = distance[i][j];
    }
    return false;
}

vector<long long> Deikstra(const int S, const int N, const vector<vector<pair<int, long long> > > adjacency) {
    priority_queue<pair<int, long long>, vector<pair<int, long long> >, Compare> minq;
    minq.push(make_pair(S, 0));

    vector<bool > visited(N + 1, false);
    vector<long long > distance(N + 1, inf);
    distance[S] = 0;

    while (!minq.empty()) {
        int curV = minq.top().first;
        long long curDist = minq.top().second;

        if (visited[curV]) {
            minq.pop();
            continue;
        }

        for (int i = 0; i < adjacency[curV].size(); i++) {
            if (distance[curV] + adjacency[curV][i].second < distance[adjacency[curV][i].first]) {
                distance[adjacency[curV][i].first] = distance[curV] + adjacency[curV][i].second;
                minq.push(make_pair(adjacency[curV][i].first, distance[curV] + adjacency[curV][i].second));
            }
        }

        visited[curV] = true;
        minq.pop();
    }
    return distance;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
   
    int N, M; 
    cin >> N >> M;

    vector<vector<pair<int, long long> > > adjacency(N + 1);

    for (int i = 0; i <= N; i++) {
        adjacency[0].push_back(make_pair(i, 0));
    }

    bool hasNegativeNums = false;
    for (int i = 1; i <= M; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        if (w < 0) {
            hasNegativeNums = true;
        }
        adjacency[u].push_back(make_pair(v, w));
    }

    vector<long long > belmanFordResult(N + 1, 0);

    if (hasNegativeNums) {
        bool hasNegativeCycle = BelmanFord(N, belmanFordResult, adjacency);
        if (hasNegativeCycle) {
            cout << "Negative cycle" << '\n';
            return 0;
        }
        else {
            for (int i = 1; i <= N; i++) {
                for (int j = 0; j < adjacency[i].size(); j++) {
                    adjacency[i][j].second = adjacency[i][j].second + belmanFordResult[i] - belmanFordResult[adjacency[i][j].first];
                }
            }
        }
    }

    for (int i = 1; i <= N; i++) {
        vector<long long> deikstraRes = Deikstra(i, N, adjacency);
        for (int j = 1; j <= N; j++) {
            if ( deikstraRes[j] == inf) {
                if (j == N) {
                    cout << "inf";
                }
                else {
                    cout << "inf" << ' ';
                }
            }
            else {
                if (j == N) {
                    cout << deikstraRes[j] - belmanFordResult[i] + belmanFordResult[j];
                }
                else {
                    cout << deikstraRes[j] - belmanFordResult[i] + belmanFordResult[j] << ' ';
                }
            }
        }
        cout << '\n';
    }

}
