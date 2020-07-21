/*
* @Author: Yan An
* @Date:   2020-07-21 14:12:59
* @Last Modified by:   Yan An
* @Last Modified time: 2020-07-21 15:22:24
*/
#include <iostream>
#include "../mylib/mymath.hpp"
using namespace std;

int main(int argc, char *argv[])
{
	double base = atof(argv[1]);
	double exponent = atoi(argv[2]);

	cout << "result = " << power(base, exponent) << endl;
}