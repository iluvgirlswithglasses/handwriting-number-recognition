
/*
author: 	iluvgirlswithglasses
github: 	https://github.com/iluvgirlswithglasses
created:	Mon Dec  4 09:35:12 2023
style:  	C-Kernel with custom pointer rule
tab-width:	4 spaces

 /\_/\
( o.o )
 > ^ <

I firmly believe in the supremacy of the Euphonium
FYI I use Debian
*/

#include <iostream>
#include <string>
#include "../src/trainer.h"
using namespace std;
using namespace NumberRecog;

int main(int argc, const char* argv[])
{
	ios_base::sync_with_stdio(false); cin.tie(0);
	string fansnet = argv[1];	// final (answer) network
	string fbackup = argv[2];	// training backup file
	string fdatdir = argv[3];	// training/test data

	Trainer::train(
		fdatdir + "/train-images.idx3-ubyte",
		fdatdir + "/train-labels.idx1-ubyte",
		fansnet,
		fbackup);
	Trainer::test(
		fdatdir + "/t10k-images.idx3-ubyte",
		fdatdir + "/t10k-labels.idx1-ubyte",
		fansnet);
	return 0;
}

