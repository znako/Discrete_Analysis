#include <string>
#include <iostream>
#include <vector>
#include <stack>
#include <memory>

struct SuffixTree {
    struct Edge {
        int left;
        std::shared_ptr<int> right;
        int nodeTarget;

        Edge(int left, std::shared_ptr<int> right, int node): left(left), right(right), nodeTarget(node) {}
    };

    std::vector< std::vector<Edge> > Tree;
    std::string Text;
    std::vector<int> VSuffix;
    std::vector<int> LenToNode;

    int FindEdge(int node, char ch) {
        for (int i = 0; i < Tree[node].size(); ++i) {
            if (Text[Tree[node][i].left] == ch) {
                return i;
            }
        }
        return -1;
    };

    SuffixTree(const std::string & str): Text(str),
        Tree(str.size() * 2),
        VSuffix(str.size() * 2),
        LenToNode(str.size() * 2)  {
            int left = 0;
            std::shared_ptr<int> end(new int);
            *end = 0;
            bool newNode = false;
            int eqFromRoot = 0;
            int eqCur = 0;
            int curNode = 0;
            int curEdge = -1;
            int newNodeNumber = 0;
            for (int i = 0; i < str.size(); ++i) {
                ++*end;
                int curNewNode = -1;
                int lastNewNode = 0;
                while (*end > left) {
                    if (curEdge == -1) {
                        int nextEdge = FindEdge(curNode, Text[left + eqFromRoot + eqCur]);

                        if (nextEdge == -1) {
                            newNode = true;
                        }
                        else {
                            eqCur = 1;
                        }

                        curEdge = nextEdge;
                    }
                    else if (
                            Text[Tree[curNode][curEdge].left + eqCur] == 
                            Text[left + eqFromRoot + eqCur ]
                        ) {
                            ++eqCur;
                    }
                    else {
                        newNode = true; 
                    }

                    if (eqCur > 0 and Tree[curNode][curEdge].left + eqCur == *Tree[curNode][curEdge].right) {
                        curNode = Tree[curNode][curEdge].nodeTarget;
                        curEdge = -1;
                        eqFromRoot += eqCur;
                        eqCur = 0;
                    }
                    if (newNode) {
                        ++newNodeNumber;

                        if (eqCur == 0 and curEdge == -1) {
                            Tree[curNode].push_back(Edge(left + eqFromRoot, end, newNodeNumber));
                        }
                        else {
                            curNewNode = newNodeNumber;
                            Edge tempCurEdge = Tree[curNode][curEdge];

                            std::shared_ptr<int> newRight(new int);
                            *newRight = Tree[curNode][curEdge].left + eqCur;
                            Tree[curNode][curEdge].right = newRight;

                            Tree[curNode][curEdge].nodeTarget = newNodeNumber;
                            tempCurEdge.left = *newRight;
                            Tree[newNodeNumber].push_back(tempCurEdge);

                            ++newNodeNumber;
                            Tree[newNodeNumber - 1].push_back(Edge(left + eqCur + eqFromRoot, end, newNodeNumber));

                            LenToNode[newNodeNumber - 1] = LenToNode[curNode] + *Tree[curNode][curEdge].right - Tree[curNode][curEdge].left;

                            if (lastNewNode > 0) {
                                VSuffix[lastNewNode] = curNewNode;
                            }
                            lastNewNode = curNewNode;
                        }
                        
                        int nextNode = VSuffix[curNode];
                        int nextEdge = -1;
                        int nextEqFromRoot = LenToNode[nextNode];
                        int nextEqCur = eqCur + eqFromRoot - nextEqFromRoot - 1;

                        while (nextEqCur > 0) {
                            nextEdge = FindEdge(nextNode, Text[left + nextEqFromRoot + 1]);
                            int r = *Tree[nextNode][nextEdge].right;
                            int l = Tree[nextNode][nextEdge].left;

                            if (r - l <= nextEqCur) {
                                nextEqFromRoot += r - l;
                                nextEqCur -= r + l;
                                nextNode = Tree[nextNode][nextEdge].nodeTarget;
                                nextEdge = -1;
                            }
                            else {
                                break;
                            }
                        }

                        if (nextEdge != -1) {
                            eqCur = nextEqCur;
                        }
                        else {
                            eqCur = 0;
                        }

                        eqFromRoot = nextEqFromRoot;
                        curNode = nextNode;
                        curEdge = nextEdge;
                        left++;
                        newNode = false;
                    }
                    
                }
            }
    }

    std::vector<size_t> MatchStatistics(const std::string &text) {
        size_t len = text.size();
        std::vector<size_t> ms(len);

        int curNode = 0;
        int curEdge = FindEdge(curNode, text[0]);
        int eqFromRoot = 0;
        int eqCur = 0;

        std::stack<int> path;
        path.push(0);

        for (int i = 0; i < len; i++) {
            int nextNode = curNode;

            while(VSuffix[nextNode] == 0 and !path.empty()) {
                nextNode = path.top();
                path.pop();
            }
            curNode = VSuffix[nextNode];
            
            // while (!path.empty()) {
            //     path.pop();
            // }

            path.push(curNode);
            eqCur = std::max(0, eqFromRoot + eqCur - 1 - LenToNode[curNode]);
            eqFromRoot = LenToNode[curNode];
            curEdge = -1;
            
            while (eqCur >= 0) {
                int nextEdge = FindEdge(curNode, text[i + eqFromRoot]);
                
                if(nextEdge != -1) {
                    int edgeLen = *Tree[curNode][nextEdge].right - Tree[curNode][nextEdge].left;

                    if (eqCur >= edgeLen) {
                        eqCur -= edgeLen;
                        eqFromRoot += edgeLen;
                        curNode = Tree[curNode][nextEdge].nodeTarget;
                        nextEdge = -1;
                    }
                    else{
                        curEdge = nextEdge;
                        break;;
                    }
                }
                else break;
            }
            while (
                curEdge != -1 and i + eqFromRoot + eqCur < len and text[i + eqCur + eqFromRoot]
                == 
                Text[Tree[curNode][curEdge].left + eqCur]
             ) {
                ++eqCur;
                if (Tree[curNode][curEdge].left + eqCur == *Tree[curNode][curEdge].right) {
                    int nextNode = Tree[curNode][curEdge].nodeTarget;
                    int nextEdge = FindEdge(nextNode, text[i + eqFromRoot + eqCur]);
                    int edgeLen = eqCur;
                    eqFromRoot += edgeLen;
                    eqCur = 0;
                    curNode = nextNode;
                    path.push(curNode);
                    curEdge = nextEdge;
                }
            }
            ms[i] = eqFromRoot + eqCur;
        }
        return ms;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::string pattern, text;
    std::cin >> pattern >> text;
    pattern += "$";
    SuffixTree tree(pattern);
    std::vector<long unsigned int> ms(text.size());
    ms = tree.MatchStatistics(text);
    for (int i = 0; i < ms.size(); ++i) {
        if (ms[i] == pattern.size() - 1) {
           std::cout << i + 1 << "\n";
        }
    }
}