
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
#include "../src/mnist.h"
using namespace std;
using namespace NumberRecog;

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0);
	Mnist::read("./dat/train-images.idx3-ubyte");
	return 0;
}

