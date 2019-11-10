#include <iostream>

using namespace std;

struct X
{
	int x : 13;
	int y : 12;
};

const unsigned short mask_exponent = 0xF000;
const unsigned short mask_mantissa_exponent0 = 0x0FFF;
const unsigned short mask_mantissa_1 = 0x07FF;
//const unsigned short mask_signbit = 0x0800;
//const unsigned short mask_bit1213 = 0x1800;

float div2(float& mantissa_float, unsigned short& exponant)
{
	if(exponant > 0)
	{
		mantissa_float = mantissa_float / 2.0;
		exponant = exponant - 1;
		div2(mantissa_float, exponant);
	}
	
	return mantissa_float;
}

// Function takes unsigned short and return float
float converter(unsigned short value)
{
	unsigned short exponant = (value & mask_exponent) >> 12;
	X mantissa;
	if (exponant == 0)
	{
		mantissa.y = (value & mask_mantissa_exponent0);
		float mantissa_float = mantissa.y;
		return div2(mantissa_float,24);
	}
	else
	{
		X sign;
		unsigned short signValue = 0x0800;
		if((value & signValue) != 0)
		{
			signValue = 0x1000;
		}
		
		sign.x = signValue;
		
		mantissa.x = (value & mask_mantissa_1);
		float mantissa_float = sign.x | mantissa.x;
		unsigned short exponant1 = 25 - exponant;
		return div2(mantissa_float, exponant1);
	}
}



int main()
{
	
}