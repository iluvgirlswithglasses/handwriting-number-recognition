
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
#include <vector>
#include <string>
#include <cstdint>
#include <dlib/matrix.h>

/** @ implementation */
namespace NumberRecog
{

class Mnist
{
public:
	using img_t = dlib::matrix<uint8_t>;
	using labels_type = std::vector<unsigned long>;

	static std::vector<img_t>   read_images(const std::string& path_to_mnist_file);
	static labels_type          read_labels(const std::string& path_to_mnist_file);

private:
	static int reverse(int x);

};

}	// namespace NumberRecog

#endif	// MNIST_H

