//c++ for huffman coding
//source code from https://medium.com/@bhch3n/huffman-coding-%E9%9C%8D%E5%A4%AB%E6%9B%BC%E7%B7%A8%E7%A2%BC-3879df5ecddc
#include <deque>
#include <string>
#include <algorithm>
#include <iostream>
#include <unordered_map>
using namespace std;

class Node {
public:
    int val;
    int freq;
    Node* lchild;
    Node* rchild;

    Node(char _val, int _freq, Node* _lchild, Node* _rchild) {
        val = _val;
        freq = _freq;
        lchild = _lchild;
        rchild = _rchild;
    }
};

unordered_map<char, int> freq;  // 用來統計各個字元的出現次數
deque<Node*> forest;            // 用來儲存各個節點之指標

// 提供給sort函數使用
bool comp(Node* a, Node* b) {
    return a->freq < b->freq;
}

// 印出Huffman Tree的資訊
void printCode(Node* ptr, string s) {
    if(ptr->lchild == nullptr || ptr->rchild == nullptr) {
        printf("'%c' (freq = %d) --> %s\n", ptr->val, freq[ptr->val], s.c_str());
        return;
    }
    if(ptr->lchild) printCode(ptr->lchild, string(s + "0"));
    if(ptr->rchild) printCode(ptr->rchild, string(s + "1"));
}

void huffman(char data[],int num){
    // 從stdin讀入欲編碼之資料，並統計各字元的出現頻率
    char c;
    int i=0;
    while(i<num) {
        c = data[i++];
        if(c == '\n') continue;
        if(freq.count(c)) freq[c]++;
        else freq[c] = 1;
    }

    // 製作節點，並儲存到forest之中
    for(auto it = freq.begin(); it != freq.end(); it++)
        forest.push_back(new Node((*it).first, (*it).second, nullptr, nullptr));

    // 按照字元出現頻率排序forest中的節點，取出出現頻率最小的兩個節點，將其合併，
    // 再儲存回forest之中
    for(int i = 0; i < freq.size()-1; i++) {
        sort(forest.begin(), forest.end(), comp);
        Node* ptr1 = forest.front(); forest.pop_front();
        Node* ptr2 = forest.front(); forest.pop_front();
        Node* parentNode = new Node(-1, ptr1->freq + ptr2->freq, ptr1, ptr2);
        forest.push_back(parentNode);
    }
    printCode(forest.front(), string(""));
}

