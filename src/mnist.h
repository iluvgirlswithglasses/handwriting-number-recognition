
/*
author: 	iluvgirlswithglasses
github: 	https://github.com/iluvgirlswithglasses
created:	Mon Dec  4 09:27:37 2023
style:  	C-Kernel with custom pointer rule
tab-width:	4 spaces

 /\_/\
( o.o )
 > ^ <

I firmly believe in the supremacy of the Euphonium
FYI I use Debian
*/

#ifndef MNIST_H
#define MNIST_H

/** @ docs */

/** @ dependencies */
#include <string>

/** @ implementation */
namespace NumberRecog
{

class Mnist
{
public:
	static void read(const std::string& path);

private:
	static int reverse(int x);

};

}	// namespace NumberRecog

#endif	// MNIST_H

