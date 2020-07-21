/*
* @Author: Yan An
* @Date:   2020-07-21 14:12:59
* @Last Modified by:   Yan An
* @Last Modified time: 2020-07-21 17:17:51
*/
#include <iostream>


#ifdef USE_MYMATH
	#include "../mylib/mymath.hpp"
#else
	#include <math.h>
#endif
using namespace std;

int main(int argc, char *argv[])
{
	double base = atof(argv[1]);
	double exponent = atoi(argv[2]);


	#ifdef USE_MYMATH
		cout << "MYMATH" << endl;
		cout << "result = " << power(base, exponent) << endl;
	#else
		cout << "OTHERMATH" << endl;
		cout << "result = " << pow(base, exponent) << endl;

	#endif
}