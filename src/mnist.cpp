
/*
author: 	iluvgirlswithglasses
github: 	https://github.com/iluvgirlswithglasses
created:	Mon Dec  4 09:50:12 2023
style:  	C-Kernel with custom pointer rule
tab-width:	4 spaces

 /\_/\
( o.o )
 > ^ <

I firmly believe in the supremacy of the Euphonium
FYI I use Debian
*/

#include "mnist.h"
#include <fstream>

namespace NumberRecog
{

std::vector<Mnist::img_t> Mnist::read_images(const std::string& path)
{
	std::ifstream file(path);
	const auto read = [&](auto& x) {
		file.read((char*)& x, sizeof(x));
		x = reverse(x);
	};

	// mod(magic) number, image count, height, width
	int mod; read(mod);
	int cnt; read(cnt);
	int row; read(row);
	int col; read(col);

	// read images
	std::vector<img_t> ans;
	ans.reserve(cnt);

	while (cnt--) {
		ans.emplace_back(row, col);
		for (int y = 0; y < row; y++)
		for (int x = 0; x < col; x++) {
			uint8_t byte;
			file.read((char*)& byte, sizeof(byte));
			ans.back()(y, x) = byte;
		}
	}

	return ans;
}

Mnist::labels_type Mnist::read_labels(const std::string& path)
{
	std::ifstream file(path);
	const auto read = [&](auto& x) {
		file.read((char*)& x, sizeof(x));
		x = reverse(x);
	};

	int mod; read(mod);
	int cnt; read(cnt);
	labels_type ans(cnt);
	for (auto& i: ans) {
		uint8_t tmp;
		file.read((char*)& tmp, sizeof(tmp));
		i = tmp;
	}
	return ans;
}

int Mnist::reverse(int x)
{
	constexpr int msk = (1 << 8) - 1;
	uint8_t
		a = (x      ) & msk,
		b = (x >>  8) & msk,
		c = (x >> 16) & msk,
		d = (x >> 24) & msk;
	return (a << 24) + (b << 16) + (c << 8) + d;
}

}	// namespace NumberRecog

