#include <iostream>
#include <string>
#include <random>
#include "AI.h"

using namespace std;

//random generator setup
uniform_real_distribution<double> xorSelection(0, 7);

//Network properties
const int InputSize = 2;
const vector<int> layers{ 2,4,2,1 }; //last layer is output layer
double lr = 1; //the learning rate

int main()
{
	int correct = 0;
	cout << "Start!\n";
	Network AI(layers, lr);

	// prepare XOR training data
	vector<vector<double>> data = {
		//    I  XOR  I  XOR  I   =   O
		//--------------------------------
			  {0,      0,      0,      0},
			  {0,      0,      1,      1},
			  {0,      1,      0,      1},
			  {0,      1,      1,      0},
			  {1,      0,      0,      1},
			  {1,      0,      1,      0},
			  {1,      1,      0,      0},
			  {1,      1,      1,      1 } };

	//training
	cout << "Starting training!";
	for (int epoch = 0; epoch < 5000; epoch++)
	{
		int chosenproblem = round(xorSelection(generator)); //get a random number between 0 and 7
		vector<double> in;
		for (int i = 0; i < 3; i++)
		{
			in.push_back(data[chosenproblem][i]);
		}

		vector<double> out = { data[chosenproblem][3] };

		AI.GetOutput(in); //Feed forward

		AI.Learn(in, out);
		if (epoch % 500 == 0)
		{
			cout << "Completed epoch " << epoch << " \n";
		}
	}
	for (int i = 0; i < 8; i++)
	{
		double result = AI.GetOutput(vector<double>(data[i].begin(), data[i].begin() + 3))[0];
		cout << data[i][0] << " xor " << data[i][1] << " xor " << data[i][3] << " gives " << result << "\n";
	}
}