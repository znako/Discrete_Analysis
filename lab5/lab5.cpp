#include <string>
#include<iostream>
#include <vector>
#include<stack>
#include <memory>


struct TSuffixTree {
    struct TEdge {
        int Left; //Левая граница текста
        std::shared_ptr<int> Right; //Правая граница, не включая последнее, то есть -1
        int IdTo; //В какую вершину ведёт ребро

        TEdge(int l, std::shared_ptr<int> r, int id) : Left(l), Right(r), IdTo(id) {}
    };


    std::string DataString; //Text
    std::vector< std::vector< TEdge > > Data; //Списки смежности
    std::vector<int> SuffixPtr; //Вектор суффиксных ссылок
    std::vector<int> PathSize; // Вектор сколько символов от корня до текущей вершины

    int FindEdgeChar(int id, char c) { //Находит ребро, которе начинается с нужного символа
        for (size_t i = 0; i < Data[id].size(); ++i) {
            if (c == DataString[Data[id][i].Left]) {
                return i;
            }
        }
        return -1;
    }

    TSuffixTree(const std::string & s) : DataString(s), Data(s.size() * 2), SuffixPtr(s.size() * 2), PathSize(s.size() * 2) {
        bool newVertex = false;
        int l = 0;
        std::shared_ptr<int> end(new int);
        *end = 0;
        int passEq = 0;//Количество совпавших символов от корня (без curEq)
        int curEq = 0;// Количество совпавших символов на ребре
        int curVertexId = 0;// Id вершины, в которой мы находимся
        int curEdgeId = -1;//Id текущего рассматриваемого ребра
        int createdVertexId = 0;//Id созданной вершины
        for (size_t i = 0; i < s.size(); ++i) {
            ++*end;
            int lastCreatedVertexId = 0;//последнее созданная внутренняя вершина
            int nextCreatedVertexId = -1;//текущая созданная внутренняя вершина
            while (l < *end) {
                std::cout << "check " << l <<"\n";
                if (curEdgeId == -1) {
                    int nextEdgeId = FindEdgeChar(curVertexId, DataString[l + passEq + curEq]);
                    if (nextEdgeId == -1) {
                        newVertex = true;
                    } else {
                        curEq = 1;
                    }
                    curEdgeId = nextEdgeId;
                } else {
                    if (DataString[Data[curVertexId][curEdgeId].Left + curEq] == DataString[l + curEq + passEq]) {
                        ++curEq;
                    } else {
                        newVertex = true;
                    }
                }
                if (curEq > 0 and Data[curVertexId][curEdgeId].Left + curEq == *Data[curVertexId][curEdgeId].Right) {
                    curVertexId = Data[curVertexId][curEdgeId].IdTo;
                    curEdgeId = -1;
                    passEq = passEq + curEq;
                    curEq = 0;
                }
                if (newVertex) {
                    ++createdVertexId;
                    if (curEq == 0 and curEdgeId == -1) {
                        Data[curVertexId].push_back(TEdge(l + passEq, end, createdVertexId));
                    } else {
                        nextCreatedVertexId = createdVertexId;
                        TEdge curEdge = Data[curVertexId][curEdgeId];

                        std::shared_ptr<int> newRightBorder(new int);
                        *newRightBorder = Data[curVertexId][curEdgeId].Left + curEq;
                        Data[curVertexId][curEdgeId].Right = newRightBorder;
                        Data[curVertexId][curEdgeId].IdTo = createdVertexId;
                        curEdge.Left = *newRightBorder;

                        Data[createdVertexId].push_back(curEdge);
                        ++createdVertexId;
                        Data[createdVertexId - 1].push_back(TEdge(l + curEq + passEq, end, createdVertexId));
                        PathSize[createdVertexId - 1] = PathSize[curVertexId] + *Data[curVertexId][curEdgeId].Right - Data[curVertexId][curEdgeId].Left;

                        if (lastCreatedVertexId > 0) {
                            SuffixPtr[lastCreatedVertexId] = nextCreatedVertexId;
                        }
                        lastCreatedVertexId = nextCreatedVertexId;
                    }
                    int nextVertexId = SuffixPtr[curVertexId];//Id вершины, в которую мы совершим переход по суфф ссылке
                    std::cout << nextVertexId << "\n";
                    int nextEdgeId = -1;
                    int nextPassEq = PathSize[nextVertexId];//Количество совпавших символов от корня (без curEq) до той вершины, куда переходим
                    std::cout << nextPassEq << "\n";
                    int nextCurEq = curEq + passEq - nextPassEq - 1;//Количество символов, которые совпали и предстоит пройти от следующей вершины
                    std::cout << nextCurEq << "\n";
                    while (nextCurEq > 0) {
                        nextEdgeId = FindEdgeChar(nextVertexId, DataString[l + nextPassEq + 1]);
                        int curRight = *Data[nextVertexId][nextEdgeId].Right;
                        int curLeft = Data[nextVertexId][nextEdgeId].Left;
                        if (curRight - curLeft <= nextCurEq) {
                            nextPassEq = nextPassEq + curRight - curLeft;
                            nextCurEq = nextCurEq - curRight + curLeft;
                            nextVertexId = Data[nextVertexId][nextEdgeId].IdTo;
                            nextEdgeId = -1;
                        } else {
                            break;
                        }
                    }
                    if (nextEdgeId != -1) {
                        curEq = nextCurEq;
                    } else {
                        curEq = 0;
                    }
                    passEq = nextPassEq;
                    curVertexId = nextVertexId;
                    curEdgeId = nextEdgeId;
                    ++l;
                    newVertex = false;
                } else {
                    if (i < s.size() - 1) {
                        break;
                    }
                }
            }
        }
    }

    std::vector<size_t> Search(const std::string & s) {
        size_t n = s.size();
        std::vector<size_t> ms(n);
        int curVertex = 0;
        int curEdgeId = FindEdgeChar(0, s[0]);
        int passEq = 0;
        int curEq = 0;
        std::stack<int> path;
        path.push(0);
        for (size_t i = 0; i < n; ++i) {
            int nextVertex = curVertex;
            while (SuffixPtr[nextVertex] == 0 and !path.empty()) {
                nextVertex = path.top();
                path.pop();
            }
            curVertex = SuffixPtr[nextVertex];
            while (!path.empty()) {
                path.pop();
            }
            path.push(curVertex);
            curEq = std::max(0, passEq + curEq - 1 - PathSize[curVertex]);
            passEq = PathSize[curVertex];
            curEdgeId = -1;
            while (curEq >= 0) {
                int nextEdgeId = FindEdgeChar(curVertex, s[i + passEq]);
                if (nextEdgeId != -1) {
                    int edgeLen = *Data[curVertex][nextEdgeId].Right - Data[curVertex][nextEdgeId].Left;
                    if (curEq >= edgeLen) {
                        curEq = curEq - edgeLen;
                        passEq = passEq + edgeLen;
                        curVertex = Data[curVertex][nextEdgeId].IdTo;
                        nextEdgeId = -1;
                    } else {
                        curEdgeId = nextEdgeId;
                        break;
                    }
                } else {
                    break;
                }
            }
            while (curEdgeId != -1 and i + passEq + curEq < n and s[i + passEq + curEq] == DataString[Data[curVertex][curEdgeId].Left + curEq]) {
                ++curEq; 
                if (Data[curVertex][curEdgeId].Left + curEq == *Data[curVertex][curEdgeId].Right) {
                    int nextVertex = Data[curVertex][curEdgeId].IdTo;
                    int nextEdgeId = FindEdgeChar(nextVertex, s[i + passEq + curEq]);
                    int edgeLen = curEq;
                    passEq = passEq + edgeLen;
                    curEq = 0;
                    curVertex = nextVertex;
                    path.push(curVertex);
                    curEdgeId = nextEdgeId;
                }
            }
            ms[i] = passEq + curEq;
        }
        return ms;
    }
};


int main() {
    std::string pattern, text;
    std::cin >> pattern >> text;
    pattern += "$";
    TSuffixTree tree(pattern);
    std::vector<long unsigned int> ms(text.size());
    ms = tree.Search(text);
    for (int i = 0; i < ms.size(); ++i) {
        if (ms[i] == pattern.size() - 1) {
           std::cout << i + 1 << "\n";
        }
    }
} 