
/*
author: 	iluvgirlswithglasses
github: 	https://github.com/iluvgirlswithglasses
created:	Mon Dec  4 15:06:59 2023
style:  	C-Kernel with custom pointer rule
tab-width:	4 spaces

 /\_/\
( o.o )
 > ^ <

I firmly believe in the supremacy of the Euphonium
FYI I use Debian
*/

#ifndef TRAINER_H
#define TRAINER_H

/** @ docs */
// http://dlib.net/dnn_introduction_ex.cpp.html

/** @ dependencies */
#include <cstdint>
#include <string>
#include <vector>
#include <dlib/dnn.h>

/** @ implementation */
namespace NumberRecog
{

class Trainer
{
public:
	// Now let's define the LeNet. Broadly speaking, there are 3 parts to a network
	// definition.  The loss layer, a bunch of computational layers, and then an input
	// layer.  You can see these components in the network definition below.
	//
	// The input layer here says the network expects to be given matrix<unsigned char>
	// objects as input.  In general, you can use any dlib image or matrix type here, or
	// even define your own types by creating custom input layers.
	//
	// Then the middle layers define the computation the network will do to transform the
	// input into whatever we want.  Here we run the image through multiple convolutions,
	// ReLU units, max pooling operations, and then finally a fully connected layer that
	// converts the whole thing into just 10 numbers.
	//
	// Finally, the loss layer defines the relationship between the network outputs, our 10
	// numbers, and the labels in our dataset.  Since we selected loss_multiclass_log it
	// means we want to do multiclass classification with our network.   Moreover, the
	// number of network outputs (i.e. 10) is the number of possible labels.  Whichever
	// network output is largest is the predicted label.  So for example, if the first
	// network output is largest then the predicted digit is 0, if the last network output
	// is largest then the predicted digit is 9.
	using net_type = dlib::loss_multiclass_log<
						dlib::fc<10,
						dlib::relu<dlib::fc<84,
						dlib::relu<dlib::fc<120,
						dlib::max_pool<2,2,2,2,dlib::relu<dlib::con<16,5,5,1,1,
						dlib::max_pool<2,2,2,2,dlib::relu<dlib::con<6,5,5,1,1,
						dlib::input<dlib::matrix<uint8_t>>
					>>>>>>>>>>>>;
	using labels_type = std::vector<unsigned long>;

	static void train(
		const std::string& fimages,		// mnist training images set
		const std::string& flabels,		// mnist training labels set
		const std::string& fansnet,		// output (answer) network file
		const std::string& fbackup);	// backup file

	static void test(
		const std::string& fimages,		// mnist test images set
		const std::string& flabels,		// mnist test labels set
		const std::string& fansnet);	// the trained (answer) network

private:
	static void announce_test_result(
		const labels_type& labels,
		const labels_type& predictions);

};

}	// namespace NumberRecog

#endif	// TRAIN_H

