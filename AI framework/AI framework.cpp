#include <iostream>
#include "Network.h"
using namespace std;

vector<int> layers{ 2,4,2,1 }; //last layer is output layer
const float e = 0.5f; //the learning rate of the network

int main()
{
	cout << "Start\n";
	Network AI(layers, e);
	
	/*
	Trying to learn a XOR - operation:
	| 0 | 0 | 0 |
	| 0 | 1 | 1 |
	| 1 | 0 | 1 |
	| 1 | 1 | 0 |
	*/
}