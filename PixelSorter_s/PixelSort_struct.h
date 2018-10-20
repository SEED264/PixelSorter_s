#ifndef PIXELSORT_STRUCT_H
#define PIXELSORT_STRUCT_H
struct Pixel_BGRA{
	unsigned char b = 0;
	unsigned char g = 0;
	unsigned char r = 0;
	unsigned char a = 0;
};

struct isize{
	unsigned int w;
	unsigned int h;
	isize(unsigned int w, unsigned int h){
		this->w = w;
		this->h = h;
	}

};

struct Pixel_map{
	float sort_key;
	Pixel_BGRA pix;
	bool operator<(const Pixel_map& right) const {
		return this->sort_key < right.sort_key;
	}
	bool operator>(const Pixel_map& right) const {
		return this->sort_key > right.sort_key;
	}
};

struct stretch_pos{
	int colx;
	int coly;
};

#endif