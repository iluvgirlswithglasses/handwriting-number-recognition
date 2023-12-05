
/*
author: 	iluvgirlswithglasses
github: 	https://github.com/iluvgirlswithglasses
created:	Tue Dec  5 16:22:52 2023
style:  	C-Kernel with custom pointer rule
tab-width:	4 spaces

 /\_/\
( o.o )
 > ^ <

I firmly believe in the supremacy of the Euphonium
FYI I use Debian
*/

#include "trainer.h"
#include "mnist.h"
#include <iostream>

namespace NumberRecog
{

void Trainer::train(
	const std::string& fimages,	// mnist training images set
	const std::string& flabels,	// mnist training labels set
	const std::string& fansnet,	// output (answer) network file
	const std::string& fbackup)	// backup file
{
	auto imgs = Mnist::read_images(fimages);
	auto lbls = Mnist::read_labels(flabels);
	net_type net;

	dlib::dnn_trainer<net_type> trainer(net);
	trainer.set_learning_rate(1e-2);
	trainer.set_min_learning_rate(1e-5);
	trainer.set_mini_batch_size(128);
	trainer.be_verbose();

	trainer.set_synchronization_file(fbackup, std::chrono::seconds(20));
	trainer.train(imgs, lbls);

	net.clean();
	dlib::serialize(fansnet) << net;

	// review the net using training data
	std::clog << "Training completed.\n";
	std::clog << "Result of the trained network on training data:\n";
	labels_type predictions = net(imgs);
	announce_test_result(lbls, predictions);
}

void Trainer::test(
	const std::string& fimages,	// mnist training images set
	const std::string& flabels,	// mnist training labels set
	const std::string& fansnet)	// output (answer) network file
{
	auto imgs = Mnist::read_images(fimages);
	auto lbls = Mnist::read_labels(flabels);
	net_type net;
	dlib::deserialize(fansnet) >> net;

	std::clog << "Result of the trained network on test data:\n";
	labels_type predictions = net(imgs);
	announce_test_result(lbls, predictions);
}

void Trainer::announce_test_result(
	const labels_type& labels,
	const labels_type& predictions)
{
	int right_guesses = 0, wrong_guesses = 0;
	for (size_t i = 0; i < predictions.size(); i++) {
		if (predictions[i] == labels[i])
			right_guesses++;
		else
			wrong_guesses++;
	}
	std::clog << "    Right guesses: " << right_guesses << "\n";
	std::clog << "    Wrong guesses: " << wrong_guesses << "\n";
	std::cout << "    Accuracy:      " << right_guesses / static_cast<double>(right_guesses + wrong_guesses) << "\n";
}

}	// namespace NumberRecog

