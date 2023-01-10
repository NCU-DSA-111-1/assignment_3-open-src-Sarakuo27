//c++ for Arithmetic Coding
//source code from https://gist.github.com/mohitbansal964/3a40d80be9c78f1ac267ac329391c545

#include<iostream>
#include<unordered_map>
#include<string>
#include<vector>
#include <time.h>

using namespace std;

struct node{
	double prob, range_from, range_to;
};

double encoding(unordered_map<char, node> arr, string s){
	cout<<"\nEncoding\n";
	double low_v=0.0, high_v=1.0, diff= 1.0;
	cout<<"Symbol\tLow_v\tHigh_v\tdiff\n";
	for(int i=0; i<s.size(); i++){
		high_v= low_v+ diff* arr[s[i]].range_to;
		low_v= low_v+ diff* arr[s[i]].range_from;
		diff= high_v- low_v;
		cout<<s[i]<<"\t"<<low_v<<"\t"<<high_v<<"\t"<<diff<<endl;
	}
	return low_v;
}

string decoding(unordered_map<char, node> arr, double code_word, int len){
	cout<<"\nDecoding: \n";
	char ch;
	string text= "";
	int j=0;
	unordered_map<char, node>:: iterator it;
	cout<<"Code\tOutput\tRange_from\tRange_to\n";
	while(j<len){
		//cout<<code_word<<"\t";
		for(it= arr.begin(); it!=arr.end(); it++){
			char i= (*it).first;
			if(arr[i].range_from<= code_word && code_word< arr[i].range_to){
				ch= i;
				code_word= (code_word-arr[i].range_from)/(arr[i].range_to- arr[i].range_from);
				break;
			}
		}
		cout<<ch<<"\t"<<arr[ch].range_from<<"\t\t"<<arr[ch].range_to<<endl;
		text+= ch;
		j++;
	}
	return text;
}

int Arithmetic(char data[],double prob[],int n){
	cout<<"Number of characters: "<< n <<endl;
	unordered_map<char, node> arr;
	vector<char> ar;
	double range_from= 0;
	cout<<"Probability of each character:\n";
	for(int i=0; i<n; i++){
		char ch;
		ch = data[i];
		ar.push_back(ch);
		arr[ch].prob = prob[i] ;
		arr[ch].range_from= range_from;
		arr[ch].range_to= range_from+ arr[ch].prob;
		range_from= arr[ch].range_to;
	}
	cout<<"Symbol\tProbability\tRange_from\tRange_to\n";
	cout<<"----------------------------------------------------\n";
	for(int i=0; i<ar.size(); i++){
		cout<<ar[i]<<"\t"<<arr[ar[i]].prob<<"\t\t"<<arr[ar[i]].range_from<<"\t\t"<<arr[ar[i]].range_to<<endl;
	}
	cout<<endl;
	string s = "A";
	double START_Arithmetic,END_Arithmetic;
	START_Arithmetic = clock();
	double code_word = encoding(arr,s);
	END_Arithmetic = clock();
	//cout<<"Code word for "<<"A"<<" is: "<<code_word<<endl;

	string text= decoding(arr, code_word, s.size());

	//cout<<"Text for "<<code_word<<" is: "<<text<<endl;

	return (END_Arithmetic-START_Arithmetic);
}

