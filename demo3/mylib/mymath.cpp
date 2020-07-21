/*
* @Author: Yan An
* @Date:   2020-07-21 12:01:59
* @Last Modified by:   Yan An
* @Last Modified time: 2020-07-21 12:04:01
*/
#include "mymath.hpp"

double power(double base, double exponent)
{	
	int res = base;
	for(int i = 1; i < exponent; i++)
	{
		res *= base;
	}
	return res;
}