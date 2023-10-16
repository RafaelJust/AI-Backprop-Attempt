#include <vector>
using namespace std;

vector<double> Substract(vector<double> first, vector<double> second)
{
	vector<double> result;
	//Per-element substraction
	for (int i = 0; i < first.size(); i++) //Both vectors must be the same
	{
		result[i] = first[i] - second[i];
	}

	return result;
}

vector<double> Multiply(vector<double> first, vector<double> second)
{
	vector<double> result;
	if (sizeof(first) == sizeof(second))
	{
		//use Per-element multiplication for faster calculation
		for (int i = 0; i < first.size(); i++)
		{
			result[i] = first[i] * second[i];
		}
	}
	else //vectors are not the same
	{
		vector<vector<double>> operands = { first,second }; //Use for easier handling
		int smaller;
		smaller = (min(sizeof(first), sizeof(second)) == sizeof(second)); //get the smallest vector

		//multiply each value of the larger vector with all the values of the smaller ones
		for (double a : operands[!smaller])
		{
			for (double product : operands[smaller]) // !smaller changes 0 to 1, and 1 to 0
			{
				a *= product;
			}
		}

		result = operands[!smaller]; //make the multiplicated vector the result
	}

	return result;
}