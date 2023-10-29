#include <iostream>
#include <string>
#include <random>
#include "AI.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

//Create random range for files
int test_set_start = 11500; //when the test set starts.
uniform_real_distribution<int> randfile(0,test_set_start - 1);
uniform_real_distribution<int> coinflip(0, 1);


using namespace std;

//Network properties
const int InputSize = 2;
const vector<int> layers{ 1,1 }; //last layer is output layer
double lr = 0.01; //the learning rate

//image loading properties
string dataset_path = "C:/Users/justr/Desktop/School/PWS/Datasets/Cats n dogs";
const int img_amount = 12498;
const vector<string> second_path = { "dog (", "cat (" };

vector<int> GetImage(bool cat, int filenum)
{
	int width, height, bpp; //Unused, but required for the stb to work (acts as output)
	string img_path = dataset_path + (cat ? "/Cat/cat (" : "/Dog/dog (") + to_string(filenum) + ").jpg";
	unsigned char* data = stbi_load(dataset_path, &width, &height, 3);
	// Need to change string to char here ^
}

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
		double in1 = b1 ? 1.0 : 0.0;
		double in2 = b2 ? 1.0 : 0.0;

		bool expected = b1 == b2;
		bool Calculated = AI.GetOutput(vector<double>{in1, in2})[0] < 0;
		double expected_d = expected ? 1.0 : 0.0; //Make a double from the 'expected' bool to use as input for AI

		cout << "expected: " << expected << ", calculated: " << Calculated << "\n";
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
			cout << "Now it is " << (AI.GetOutput(vector<double>{in1, in2})[0] < 0) << "\n";
		}

	} while (correct < 10);

	cout << "YAY IT WORKS! \n enter two values: ";
	while (true)
	{
		double in1;
		cin >> in1;
		double in2;
		cin >> in2;
		cout << "Answer: " << (AI.GetOutput(vector<double>{in1, in2})[0] < 0) << "!\n";
	}

}