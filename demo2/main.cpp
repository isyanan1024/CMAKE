/*
* @Author: Yan An
* @Date:   2020-07-21 11:28:13
* @Last Modified by:   Yan An
* @Last Modified time: 2020-07-21 11:42:21
*/
#include <iostream>
#include "mymath.hpp"
using namespace std;

int main(int argc, char *argv[])
{
	if(argc < 3)
	{
		cout << "Usage:" << argv[0] << endl;
		return 1;
	}

	double base = atof(argv[1]);
	double exponent = atoi(argv[2]);

	cout << "result = " << power(base, exponent) << endl;
}