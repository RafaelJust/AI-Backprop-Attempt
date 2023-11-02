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
		double in1 = b1 ? 1.0 : -1.0;
		double in2 = b2 ? 1.0 : -1.0;

		bool expected = b1 != b2;
		double Calculated_d = AI.GetOutput(vector<double>{in1, in2})[0];
		bool Calculated = Calculated_d > 0;
		double expected_d = expected ? 1.0 : -1.0; //Make a double from the 'expected' bool to use as input for AI

		cout << "expected: " << expected_d << ", calculated: " << Calculated_d << "\nCorrect: " << correct << "\n";
		AI.Learn(vector<double>{in1, in2}, vector<double>{expected_d}); //make the ai learn to get a better answer
		if (expected = Calculated) { correct += 1; }
		else {
			correct = 0;
		}
		cout << "After learning: " << AI.GetOutput(vector<double>{in1, in2})[0] << "\n";

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