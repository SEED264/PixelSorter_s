#ifndef NOMINMAX
#define NOMINMAX 1
#endif // NOMINMAX

#include <algorithm>
#include <Windows.h>
#include "UtilFunc.h"
#include <algorithm>


float UtilFunc::comp_luminance(Pixel_BGRA *pix) {
    return (0.299f*pix->r + 0.587f*pix->g + 0.114f*pix->b);
}

float UtilFunc::comp_average(Pixel_BGRA *pix) {
    return (pix->r + pix->g + pix->b) / 3.0f;
}

float UtilFunc::comp_multiply(Pixel_BGRA *pix) {
    return (pix->r*1.0f / 255.0f)*(pix->g*1.0f / 255.0f)*(pix->b*1.0f / 255.0f);
}

float UtilFunc::comp_min(Pixel_BGRA *pix) {
    return std::min(pix->r, std::min(pix->g, pix->b));
}

float UtilFunc::comp_max(Pixel_BGRA *pix) {
    return std::max(pix->r, std::max(pix->g, pix->b));
}

float UtilFunc::comp_xor(Pixel_BGRA *pix) {
    return pix->r^pix->g^pix->b;
}


void UtilFunc::calc_stretch(int x, int y, int w, int h, int direction, float length, stretch_pos *out_pos) {
    w -= 1;
    h -= 1;
    float mx = x, my = y;
    switch (direction){
    case 1:
        my = y*(1.0f - length);
        break;
    case 2:
        my = h - (h - y)*(1.0f - length);
        break;
    case 3:
        mx = x*(1.0f - length);
        break;
    case 4:
        mx = w - (w - x)*(1.0f - length);
        break;
    }
    out_pos->colx = mx;
    out_pos->coly = my;
}