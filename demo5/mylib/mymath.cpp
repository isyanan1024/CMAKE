/*
* @Author: Yan An
* @Date:   2020-07-21 14:19:05
* @Last Modified by:   Yan An
* @Last Modified time: 2020-07-21 16:54:57
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