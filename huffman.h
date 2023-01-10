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

unordered_map<char, int> freq;  // �Á�yӋ������Ԫ�ĳ��F�Δ�
deque<Node*> forest;            // �Á탦��������cָ֮��

// �ṩ�osort����ʹ��
bool comp(Node* a, Node* b) {
    return a->freq < b->freq;
}

// ӡ��Huffman Tree���YӍ
void printCode(Node* ptr, string s) {
    if(ptr->lchild == nullptr || ptr->rchild == nullptr) {
        printf("'%c' (freq = %d) --> %s\n", ptr->val, freq[ptr->val], s.c_str());
        return;
    }
    if(ptr->lchild) printCode(ptr->lchild, string(s + "0"));
    if(ptr->rchild) printCode(ptr->rchild, string(s + "1"));
}

void huffman(char data[],int num){
    // ��stdin�x�������a֮�Y�ϣ��K�yӋ����Ԫ�ĳ��F�l��
    char c;
    int i=0;
    while(i<num) {
        c = data[i++];
        if(c == '\n') continue;
        if(freq.count(c)) freq[c]++;
        else freq[c] = 1;
    }

    // �u�����c���K���浽forest֮��
    for(auto it = freq.begin(); it != freq.end(); it++)
        forest.push_back(new Node((*it).first, (*it).second, nullptr, nullptr));

    // ������Ԫ���F�l������forest�еĹ��c��ȡ�����F�l����С�ăɂ����c������ρ㣬
    // �ك����forest֮��
    for(int i = 0; i < freq.size()-1; i++) {
        sort(forest.begin(), forest.end(), comp);
        Node* ptr1 = forest.front(); forest.pop_front();
        Node* ptr2 = forest.front(); forest.pop_front();
        Node* parentNode = new Node(-1, ptr1->freq + ptr2->freq, ptr1, ptr2);
        forest.push_back(parentNode);
    }
    printCode(forest.front(), string(""));
}

