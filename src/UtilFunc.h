#ifndef UTILFUNC_H
#define UTILFUNC_H

#ifndef NOMINMAX
#define NOMINMAX 1
#endif // NOMINMAX

#include "PixelSort_struct.h"
#include <Windows.h>

namespace UtilFunc{

    template<typename Xtype, typename Xtype2, typename Xtype3>
    inline Xtype clamp(Xtype Value, Xtype2 Min, Xtype3 Max){
        return std::max(Min, (Xtype2)std::min(Value, (Xtype)Max));
    }

    float comp_luminance(Pixel_BGRA *pix);

    float comp_average(Pixel_BGRA *pix);

    float comp_multiply(Pixel_BGRA *pix);

    float comp_min(Pixel_BGRA *pix);

    float comp_max(Pixel_BGRA *pix);

    float comp_xor(Pixel_BGRA *pix);

    stretch_pos& calc_stretch(int x, int y, int w, int h, int direction, float length);

}

#endif