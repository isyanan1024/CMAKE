/*
* @Author: Yan An
* @Date:   2020-07-21 12:05:31
* @Last Modified by:   Yan An
* @Last Modified time: 2020-07-21 13:49:32
*/
#include <iostream>
#include "./mylib/mymath.cpp"
using namespace std;


int main(int argc, char *argv[])
{
	if(argc < 3)
	{
		cout << "Usage: " << argv[0] << endl;
		return 1;
	}
	double base = atof(argv[1]);
	double exponent = atoi(argv[2]);
	cout << "result = " << power(base, exponent) << endl;
}