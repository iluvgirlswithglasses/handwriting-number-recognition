
/*
author: 	iluvgirlswithglasses
github: 	https://github.com/iluvgirlswithglasses
created:	Wed Dec  6 14:35:21 2023
style:  	C-Kernel with custom pointer rule
tab-width:	4 spaces

 /\_/\
( o.o )
 > ^ <

I firmly believe in the supremacy of the Euphonium
FYI I use Debian
*/

#ifndef RECOG_H
#define RECOG_H

/** @ docs */

/** @ dependencies */
#include <cstdint>
#include <string>
#include <vector>
#include <dlib/image_io.h>

#include "trainer.h"
#include "../param.h"

/** @ implementation */
namespace NumberRecog
{

class Recog
{
public:
	using ans_type = unsigned long;
	using img_type = dlib::matrix<uint8_t>;

	static ans_type recog(const std::string& fnet, const std::string& fimg)
	{
		Trainer::net_type net;
		dlib::deserialize(fnet) >> net;

		std::vector<img_type> img = { load(fimg) };
		return net(img)[0];
	}

private:
	static img_type load(const std::string& fimg)
	{
		dlib::matrix<uint8_t> img;
		dlib::load_image(img, fimg);
		// maybe pre-process the image here?
		return img;
	}

};

}	// namespace NumberRecog

#endif	// RECOG_H

