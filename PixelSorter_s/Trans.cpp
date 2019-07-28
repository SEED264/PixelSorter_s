#include "Trans.h"
#include"UtilFunc.h"
#include <Windows.h>


/*  サイズ縮小  */
void Trans::Shrink(Pixel_BGRA *idata, Pixel_BGRA *odata, isize in_isize, isize out_isize, int mag){
#pragma omp parallel for
    for (unsigned long y = 0; y < out_isize.h; y++){
        for (unsigned long x = 0; x < out_isize.w; x++){
            unsigned int spos = y*mag*in_isize.w + min(UtilFunc::clamp(x, 0, in_isize.w)*mag,in_isize.w);
            Pixel_BGRA t;
            t = idata[spos];
            //t.a = (alp * 255 > t.a) ? 0 : 255;
            odata[y*out_isize.w + x] = t;
        }
    }
}

/*  縦版  */
void Trans::Shrink_r(Pixel_BGRA *idata, Pixel_BGRA *odata, isize in_isize, isize out_isize, int mag){
#pragma omp parallel for
    for (unsigned long y = 0; y < out_isize.w; y++){
        for (unsigned long x = 0; x < out_isize.h; x++){
            unsigned int spos = min(y*mag, in_isize.w) + x*mag*in_isize.w;
            Pixel_BGRA t;
            t = idata[spos];
            //t.a = (alp * 255 > t.a) ? 0 : 255;
            odata[y*out_isize.h + x] = t;
        }
    }
}

/*  サイズ復元  */
void Trans::Restore(Pixel_BGRA *idata, Pixel_BGRA *odata, isize in_isize, isize out_isize, int mag, int direction, float length, bool bi){
#pragma omp parallel for
    for (unsigned long y = 0; y < out_isize.h; y++){
        for (unsigned long x = 0; x < out_isize.w; x++){
            stretch_pos sp = UtilFunc::calc_stretch(x, y, out_isize.w, out_isize.h, direction, length);
            Pixel_BGRA p = idata[sp.coly / mag*in_isize.w + sp.colx / mag];
            Pixel_BGRA op = odata[y*out_isize.w + x];
            float as = p.a / 255.0, ad = op.a / 255.0;
            float a = as+(1.0-as)*ad;
            odata[y*out_isize.w + x].a = (byte)(a*255.0);
            odata[y*out_isize.w + x].r = (p.r*as + op.r*(1.0 - as)*ad) / a;
            odata[y*out_isize.w + x].g = (p.g*as + op.g*(1.0 - as)*ad) / a;
            odata[y*out_isize.w + x].b = (p.b*as + op.b*(1.0 - as)*ad) / a;
        }
    }
}

/*  縦版  */
void Trans::Restore_r(Pixel_BGRA *idata, Pixel_BGRA *odata, isize in_isize, isize out_isize, int mag, int direction, float length, bool bi){
#pragma omp parallel for
    for (unsigned long y = 0; y < out_isize.h; y++){
        for (unsigned long x = 0; x < out_isize.w; x++){
            stretch_pos sp = UtilFunc::calc_stretch(x, y, out_isize.w, out_isize.h, direction, length);
            Pixel_BGRA p = idata[sp.colx / mag*in_isize.h + min(sp.coly / mag, out_isize.h)];
            Pixel_BGRA op = odata[y*out_isize.w + x];
            float as = p.a / 255.0, ad = op.a / 255.0;
            float a = as + (1.0 - as)*ad;
            odata[y*out_isize.w + x].a = (byte)(a*255.0);
            odata[y*out_isize.w + x].r = (p.r*as + op.r*(1.0 - as)*ad) / a;
            odata[y*out_isize.w + x].g = (p.g*as + op.g*(1.0 - as)*ad) / a;
            odata[y*out_isize.w + x].b = (p.b*as + op.b*(1.0 - as)*ad) / a;
        }
    }
}