/*
* @Author: Yan An
* @Date:   2020-07-21 11:30:54
* @Last Modified by:   Yan An
* @Last Modified time: 2020-07-21 11:36:55
*/
#include "mymath.hpp"

double power(double base, double exponent)
{
	int res = base;
	if(base == 1){
		return 1;
	}
	for(int i = 1; i < exponent; i++)
	{
		res *= base;
	}
	return res;
}