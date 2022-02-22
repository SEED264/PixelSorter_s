#ifndef NOMINMAX
#define NOMINMAX 1
#endif // NOMINMAX

#include <algorithm>
#include "Trans.h"
#include"UtilFunc.h"
#include <Windows.h>


/*  サイズ縮小  */
void Trans::Shrink(Pixel_BGRA *idata, Pixel_BGRA *odata, isize in_isize, isize out_isize, int mag){
#pragma omp parallel for
    for (long y = 0; y < out_isize.h; y++){
    #pragma omp parallel for
        for (long x = 0; x < out_isize.w; x++){
            unsigned int spos = y*mag*in_isize.w + std::min(UtilFunc::clamp(x, 0, in_isize.w)*mag, (long)in_isize.w);
            Pixel_BGRA t;
            t = idata[spos];
            odata[y*out_isize.w + x] = t;
        }
    }
}

/*  縦版  */
void Trans::Shrink_r(Pixel_BGRA *idata, Pixel_BGRA *odata, isize in_isize, isize out_isize, int mag){
#pragma omp parallel for
    for (long y = 0; y < out_isize.w; y++){
    #pragma omp parallel for
        for (long x = 0; x < out_isize.h; x++){
            unsigned int spos = std::min(y*mag, (long)in_isize.w) + x*mag*in_isize.w;
            Pixel_BGRA t;
            t = idata[spos];
            odata[y*out_isize.h + x] = t;
        }
    }
}

/*  サイズ復元  */
void Trans::Restore(Pixel_BGRA *idata, Pixel_BGRA *odata, isize in_isize, isize out_isize, int mag, int direction, float length, bool bi){
#pragma omp parallel for
    for (long y = 0; y < out_isize.h; y++){
    #pragma omp parallel for
        for (long x = 0; x < out_isize.w; x++){
            stretch_pos sp;
            UtilFunc::calc_stretch(x, y, out_isize.w, out_isize.h, direction, length, &sp);
            Pixel_BGRA p = idata[sp.coly / mag*in_isize.w + sp.colx / mag];
            Pixel_BGRA op = odata[y*out_isize.w + x];
            float as = p.a / 255.0f, ad = op.a / 255.0f;
            float a = as+(1.0f-as)*ad;
            odata[y*out_isize.w + x].a = (byte)(a*255.0f);
            odata[y*out_isize.w + x].r = (p.r*as + op.r*(1.0f - as)*ad) / a;
            odata[y*out_isize.w + x].g = (p.g*as + op.g*(1.0f - as)*ad) / a;
            odata[y*out_isize.w + x].b = (p.b*as + op.b*(1.0f - as)*ad) / a;
        }
    }
}

/*  縦版  */
void Trans::Restore_r(Pixel_BGRA *idata, Pixel_BGRA *odata, isize in_isize, isize out_isize, int mag, int direction, float length, bool bi){
#pragma omp parallel for
    for (long y = 0; y < out_isize.h; y++){
    #pragma omp parallel for
        for (long x = 0; x < out_isize.w; x++){
            stretch_pos sp;
            UtilFunc::calc_stretch(x, y, out_isize.w, out_isize.h, direction, length, &sp);
            Pixel_BGRA p = idata[sp.colx / mag*in_isize.h + std::min(sp.coly / mag, (int)out_isize.h)];
            Pixel_BGRA op = odata[y*out_isize.w + x];
            float as = p.a / 255.0f, ad = op.a / 255.0f;
            float a = as + (1.0f - as)*ad;
            odata[y*out_isize.w + x].a = (byte)(a*255.0f);
            odata[y*out_isize.w + x].r = (p.r*as + op.r*(1.0f - as)*ad) / a;
            odata[y*out_isize.w + x].g = (p.g*as + op.g*(1.0f - as)*ad) / a;
            odata[y*out_isize.w + x].b = (p.b*as + op.b*(1.0f - as)*ad) / a;
        }
    }
}