#ifndef SHRINK_H
#define SHRINK_H

#include "PixelSort_struct.h"
namespace Trans{

    void Shrink(Pixel_BGRA *idata, Pixel_BGRA *odata, isize in_isize, isize out_isize, int mag);

    void Shrink_r(Pixel_BGRA *idata, Pixel_BGRA *odata, isize in_isize, isize out_isize, int mag);

    void Restore(Pixel_BGRA *idata, Pixel_BGRA *odata, isize in_isize, isize out_isize, int mag, int direction, float length, bool bi);

    void Restore_r(Pixel_BGRA *idata, Pixel_BGRA *odata, isize in_isize, isize out_isize, int mag, int direction, float length, bool bi);

}
#endif