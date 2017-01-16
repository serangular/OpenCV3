/*
 * Acid Cam v2 - OpenCV Edition
 * written by Jared Bruni ( http://lostsidedead.com )
 * (C) 2016 GPL
 */
#include "fractal.h"

namespace frac {
    double paramA = 1.0;//0.519;
    double paramB = 0.688;
    float zoom = 0.5;
    double red_color = 3.3;
    double green_color = 3.3;
    float mod_x = 0.5;
    float mod_y = 0.5;
    double color_r = 0;
    double color_g = 100;
    double color_base = 0.0;
    float radius = 180.0f;
    int dir = 1;
    unsigned int max_iter = 100;
    
}

void frac::FractalLogic() {
    if(dir == 1) {
        paramA -= 0.01f;
        if(paramA <= 0.2f) {
            dir = 0;
            radius -= rand()%50;
            if(radius > 60) radius = 180;
        }
        
    } else {
        paramA += 0.01f;
        if(paramA >= 1.0f) dir = 1;
    }
}


void frac::DrawFractal(cv::Mat &frame, bool neg)
{
    float x1=mod_x-1.0f*zoom;
    float x2=mod_x+1.0f*zoom;
    float y1=mod_y-1.0f*zoom;
    float y2=mod_y+1.0f*zoom;
    int Width=frame.cols, Height=frame.rows;
    std::complex<double> C ((double)paramA, (double)+paramB);
    std::complex<double> Z;
    int i = 0;
    bool Finished;
    for (int x=0; x<Width;++x)
    {
        for (int y=0; y<Height; ++y)
        {
            Z=std::complex<double>((double)(x*(x2-x1)/Width+x1), (double)(y*(y2-y1)/Height+y1));
            Finished=false;
            //C=std::complex<double>(x,y);
            for (i=0; i<max_iter && !Finished; i++)
            {
                Z=Z*Z+C;
                //Zt=Z-Z0;
                if(std::abs(Z) > 4) Finished = true;
            }
            
            cv::Vec3b &cf = frame.at<cv::Vec3b>(y, x);
            if(Finished) {
                cf[0] = sin(i*red_color/100)*255-color_r;
                cf[1] = sin(i*green_color/100)*200-color_g;
                cf[2] = (255-i*2-color_base);
            } else {
                cf[0] = 0;
                cf[1] = 0;
                cf[2] = 0;
            }
        }
        if(x > frame.size().width) break;
    }
    
    std::cout << i << ": paramA: " << paramA << " paramB: " << paramB << ": " << radius << "\n";
    
}

