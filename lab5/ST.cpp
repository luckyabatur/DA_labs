#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <queue>


const int ALPHABET_SIZE = 27;
const int SHIFT = 97;


struct TNode;


struct TEdge{
    int l{};
    int r{};
    TNode* edgeNode{};
};


struct TNode{
    std::array<TEdge, ALPHABET_SIZE> edges{};
    int mark{-1};
};


class TSuffixTree{
    TNode root{};
    std::string text{};


    int LetterToIndex(char ch){
        return ch == '$' ? ALPHABET_SIZE - 1 : ch - SHIFT;
    }

    std::vector<int> DFS(TNode* node){
        std::vector<int> result;
        std::queue<TNode*> q;
        q.push(node);
        while (!q.empty()){
            TNode *currNode = q.front();
            q.pop();
            if (currNode->mark != -1){
                result.push_back(currNode->mark);
                continue;
            }
            for (int i{}; i < ALPHABET_SIZE; i++){
                if (currNode->edges[i].edgeNode != nullptr){
                    q.push(currNode->edges[i].edgeNode);
                }
            }
        }
        return result;
    }


    TEdge* SelectEdge(int textPosition, TNode* currNode, const std::string* str = nullptr){
        if (str == nullptr){
            str = &text;
        }
        for (int j{}; j < ALPHABET_SIZE; j++){
            if (currNode->edges[j].edgeNode != nullptr && text[currNode->edges[j].l] == (*str)[textPosition]){
                return &currNode->edges[j];
            }
        }
        return nullptr;
    }


    std::pair<bool, int> CompareEdge(int textPosition, TEdge* currEdge, const std::string* str = nullptr){
        if (str == nullptr){
            str = &text;
        }
        int result{1};
        while (currEdge->l + result <= currEdge->r && (*str)[textPosition] == text[currEdge->l + result]){
            textPosition++;
            result++;
        }
        if (result + currEdge->l - 1 == currEdge->r){
            return {true, result};
        }
        else{
            return {false, result};
        }
    }


    TNode* CreateNode(int separator, TEdge* sepEdge){
        TNode* newNode = new TNode;
        char startLetter = LetterToIndex(text[sepEdge->l + separator]);
        newNode->edges[startLetter].l = sepEdge->l + separator;
        newNode->edges[startLetter].r = sepEdge->r;
        newNode->edges[startLetter].edgeNode = sepEdge->edgeNode;
        sepEdge->r = sepEdge->l + separator - 1;
        sepEdge->edgeNode = newNode;

        return newNode;
    };


    void CreateLeaf(int textPosition, int mark, TNode* oldNode){
        TNode* newNode = new TNode;
        newNode->mark = mark;
        char startLetter = LetterToIndex(text[textPosition]);
        oldNode->edges[startLetter].l = textPosition;
        oldNode->edges[startLetter].r = text.size() - 1;
        oldNode->edges[startLetter].edgeNode = newNode;
    }


public:
    TSuffixTree(const std::string& str){
        text = str + '$';
        TNode* currNode{};
        TEdge* currEdge{};
        int currPosition{};
        for (int i{}; i < text.size(); i++){
            currNode = &root;
            currPosition = i;
            while (true){
                currEdge = SelectEdge(currPosition, currNode);
                if (currEdge == nullptr){
                    CreateLeaf(currPosition, i, currNode);
                    break;
                }
                std::pair<bool, int> pr = CompareEdge(currPosition + 1, currEdge);
                currPosition += pr.second;
                if (!pr.first){
                    TNode* newNode = CreateNode(pr.second, currEdge);
                    CreateLeaf(currPosition, i, newNode);
                    break;
                }
            }
        }
    }

    std::vector<int> Find(const std::string& str){
        TNode* currNode = &root;
        TEdge* currEdge{};
        int currPosition{};
        while (true){
            currEdge = SelectEdge(currPosition, currNode, &str);
            if (currEdge == nullptr && str.size() == currPosition){
                return DFS(currNode);
            }
            else if (currEdge == nullptr){
                return {};
            }
            std::pair<bool, int> pr = CompareEdge(currPosition + 1, currEdge, &str);
            currPosition += pr.second;
            currNode = currEdge->edgeNode;
            if (currPosition == str.size()){
                return DFS(currNode);
            }
            else if (!pr.first){
                return {};
            }
        }
};


int main(void){
    TSuffixTree tree("abcdabc");
    std::vector<int> res = tree.Find("abce");
    std::string a = "a";
    return 0;
}