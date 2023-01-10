#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <algorithm>

#include <unordered_map>
#include <deque>

#include "huffman.h"
#include "Arithmetic.h"

#include <time.h>

int main (){

	int number;
	cout<<"Enter the number of data you want to do:";
	cin >> number;

	char data[number];
	cout << "\nEnter the character:";
	for (int i=0;i<number;i++){
            cin>>data[i];
	}
	cout<<endl;

	cout << "\nEnter the frequency:";
	double prob[number];
	for (int i=0;i<number;i++){
            cin>>prob[i];
	}
	cout<<endl;

	cout << "---------- Huffman coding ----------" << endl;
	double START_huffman,END_huffman;
	START_huffman = clock();
	huffman(data,number);
	END_huffman = clock();

	cout << endl << "---------- Arithmetic coding ----------" << endl;
	double  Arithmetic_time;
    Arithmetic_time = Arithmetic(data,prob,number);


    cout << endl << endl <<"---------- Comparison of execution results ----------"<<endl;
	cout <<"1. Time spent executing the Huffman encoding :"<<(END_huffman - START_huffman) / CLOCKS_PER_SEC<<endl;
	cout <<"2. Time spent executing the Arithmetic encoding :"<<Arithmetic_time / CLOCKS_PER_SEC<<endl;
	return 0;
}

