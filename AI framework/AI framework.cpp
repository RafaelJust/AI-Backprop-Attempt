#include <iostream>
#include "AI.h"
using namespace std;

//Network properties
const int InputSize = 2;
const vector<int> layers{ 2,4,2,1 }; //last layer is output layer
double lr = 0.01; //the learning rate

int main()
{
	int correct = 0;
	cout << "Start!\n";
	Network AI(layers, InputSize, lr);

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
		bool Calculated = round(AI.GetOutput(vector<double>{in1, in2})[0]) != 0;
		double expected_d = expected ? 1.0 : 0.0; //Make a double from the 'expected' bool to use as input for AI

		if (expected == Calculated)
		{
			correct++;
			cout << "Calculated correct: " << correct << "\n\n\n";
			AI.Learn(vector<double>{in1, in2}, vector<double>{expected_d});
		}
		else
		{
			cout << "wrong ;-;\n\n\n";
			correct = 0;
			AI.Learn(vector<double>{in1, in2}, vector<double>{expected_d});
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