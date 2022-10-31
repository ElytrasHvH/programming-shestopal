int main()
{
	int x = -1634;
	int y = 648;
	int z;
	do {
		if (x == 0) {
			if (y > 0) {
				x = y;
			} else {
				x = -y;
			}
		} else if (y == 0) { //This all made for calculating gcd while one or both numbers are 0
			if (x > 0) { //Also GCD is always >0 so made inverses to fix when one of numbers is 0 and other is negative
				y = x;
			} else {
				x = -x;
			}
		} else if (x == 0 && y == 0) {
			z = 0;
		} else if (x > y) // check if first number is bigger then second
		{
			if (y > 0) { //check if second number is positive
				x -= y;
			} else // inversing number coz GCD will be same for them being positive
			{
				y = -y;
			}
		} else // we know that y>x and that x!=0 && y!=0 so this then
		{
			if (x > 0) //check if x positive
			{
				y -= x;
			} else //same as in line 15
			{
				x = -x;
			}
		}
	}

	while (x != y);

	z = x; //set z to x (could've been y but i want x) and then will return it as an answer
	return z;
}
