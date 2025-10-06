#include <stdio.h>
#include "add.h"
#include "ans.h"

int main(int argc, char* argv[]) 
{
	setSum(5);

	printf("5 + 7 = %d\n", add(7));
	printf("And the answer is: %d\n", answer());

	return 0;
}
