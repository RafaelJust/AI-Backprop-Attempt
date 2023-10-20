#include <iostream>
#include "Network.h"
using namespace std;

vector<int> layers{ 2,4,2,1 }; //last layer is output layer
const double e = 0.5; //the learning rate of the network

int main()
{
	int correct = 0;
	cout << "Start\n";
	Network AI(layers, e);
	
	/*
	Trying to learn a XOR - operation:
	| 0 | 0 | 0 |
	| 0 | 1 | 1 |
	| 1 | 0 | 1 |
	| 1 | 1 | 0 |
	*/

	//training
	do
	{
		//Generae a random input 1 or 0
		bool b1 = (rand() <= RAND_MAX / 2);
		bool b2 = (rand() <= RAND_MAX / 2);

		//turn bools into doubles fot the AI to interpret
		double in1 = b1 ? 1.0 : 0.0;
		double in2 = b2 ? 1.0 : 0.0;

		bool expected = b1 != b2;
		bool Calculated = AI.GetOutput(vector<double>{in1, in2})[0] != 0;

		if (expected == Calculated)
		{
			correct++;
			cout << "Calculated correct: " << correct << "\n";
		}
		else
		{
			cout << "wrong ;-;\n";
			correct = 0;
			AI.Learn(vector<double>{in1, in2}, (vector<double>)expected);
		}

	} while (correct < 10);

	cout << "YAY IT WORKS! \n enter two values: ";
	while (true)
	{
		double in1;
		cin >> in1;
		double in2;
		cin >> in2;
		cout << "Answer: " << AI.GetOutput(vector<double>{in1, in2})[0] << "!\n";
	}

}