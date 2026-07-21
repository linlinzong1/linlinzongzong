#include <iostream>

#include "model/Transaction.h"

int main()
{
	
	Transaction lunch(
		1,
		2,
		35.5,
		3,
		"2026-07-21",
		"午饭"
	);

	lunch.print();

	return 0;
}
