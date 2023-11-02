#include <iostream>
#include <string>
#include <random>
#include "AI.h"

using namespace std;

//Network properties
const int InputSize = 2;
const vector<int> layers{ 2,4,4,2,1 }; //last layer is output layer
double lr = 0.1; //the learning rate

int main()
{
	int correct = 0;
	cout << "Start!/n";
	Network AI(layers, lr);

	// prepare XOR training data
	double data[][4] = {
		//    I  XOR  I  XOR  I   =   O
		//--------------------------------
			  0,      0,      0,      0,
			  0,      0,      1,      1,
			  0,      1,      0,      1,
			  0,      1,      1,      0,
			  1,      0,      0,      1,
			  1,      0,      1,      0,
			  1,      1,      0,      0,
			  1,      1,      1,      1 };

	//training
}