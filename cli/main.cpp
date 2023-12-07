
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
#include "../src/recog.h"
using namespace std;
using namespace NumberRecog;

void train(const char* argv[])
{
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
}

void recog(const char* argv[])
{
	string fnet = argv[1];	// pre-trained network file
	string fimg = argv[2];	// the image's path
	cout << Recog::recog(fnet, fimg) << "\n";
}

void help()
{
	cout
		<< "To train a network:\n"
		<< "  number-recog <ansnet> <backup> <mnist>\n"
		<< "    <ansnet>    Where to store the final network\n"
		<< "    <backup>    Where to backup the network; so that if the program is\n"
		<< "                terminated during training, the program wouldn't be lost\n"
		<< "    <mnist>     Where all 4 uncompressed *-ubyte files from MNIST is located\n\n"

		<< "To recognize a digit on an image:\n"
		<< "  number-recog <ansnet> <img>\n"
		<< "    <ansnet>    Where the pre-trained network is\n"
		<< "    <img>       The path of the input image; The image should be 28x28 pixels,\n"
		<< "                white foreground black background\n\n";
}

int main(int argc, const char* argv[])
{
	ios_base::sync_with_stdio(false); cin.tie(0);
	if (argc == 3)
		recog(argv);
	else if (argc == 4)
		train(argv);
	else
		help();
	return 0;
}

