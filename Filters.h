#pragma once
#include "Image_Class.h"
#include <algorithm>
#include <cmath>
#include <vector>
#include <string>

using namespace std;

// Simple filters (modify in place)
void applyGrayscale(Image& img);
void applyBlackAndWhite(Image& img);
void applyInvert(Image& img);
void applyFlipHorizontal(Image& img);
void applyFlipVertical(Image& img);
void applyDarken(Image& img, int percentage);
void applyLighten(Image& img, int percentage);
void applyEdgeDetect(Image& img);
void applyBlur(Image& img, int level); // level: 1=light, 2=medium, 3=strong
void applySunlight(Image& img);
void applyTV(Image& img);
void applyPurple(Image& img);
void applyInfrared(Image& img);
void applyFrame(Image& img, int type); // type: 1=simple, 2=decorated
void applyOilPaint(Image& img);

// Filters that produce a new image (different dimensions)
Image applyRotate(Image& img, int angle); // 90, 180, or 270
Image applyResize(Image& img, int newWidth, int newHeight);
Image applyCrop(Image& img, int startX, int startY, int cropWidth, int cropHeight);
Image applySkew(Image& img, double angleDeg);
Image applyMerge(Image& img1, Image& img2, int mode); // mode: 1=resize to biggest, 2=common area
