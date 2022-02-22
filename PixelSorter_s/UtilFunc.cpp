#include <Windows.h>
#include "UtilFunc.h"
#include <algorithm>


float UtilFunc::comp_luminance(Pixel_BGRA *pix) {
    return (0.299*pix->r + 0.587*pix->g + 0.114*pix->b);
}

float UtilFunc::comp_average(Pixel_BGRA *pix) {
    return (pix->r + pix->g + pix->b) / 3.0;
}

float UtilFunc::comp_multiply(Pixel_BGRA *pix) {
    return (pix->r*1.0 / 255.0)*(pix->g*1.0 / 255.0)*(pix->b*1.0 / 255.0);
}

float UtilFunc::comp_min(Pixel_BGRA *pix) {
    return min(pix->r, min(pix->g, pix->b));
}

float UtilFunc::comp_max(Pixel_BGRA *pix) {
    return max(pix->r, max(pix->g, pix->b));
}

float UtilFunc::comp_xor(Pixel_BGRA *pix) {
    return pix->r^pix->g^pix->b;
}


stretch_pos UtilFunc::calc_stretch(int x, int y, int w, int h, int direction, float length){
    w -= 1;
    h -= 1;
    float mx = x, my = y;
    switch (direction){
    case 1:
        my = y*(1.0 - length);
        break;
    case 2:
        my = h - (h - y)*(1.0 - length);
        break;
    case 3:
        mx = x*(1.0 - length);
        break;
    case 4:
        mx = w - (w - x)*(1.0 - length);
        break;
    }
    stretch_pos p;
    p.colx = mx;
    p.coly = my;
    return p;
}