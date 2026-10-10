#include "Filters.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void applyGrayscale(Image& img) {
    for (int y = 0; y < img.height; ++y) {
        for (int x = 0; x < img.width; ++x) {
            int avg = (img(x, y, 0) + img(x, y, 1) + img(x, y, 2)) / 3;
            img(x, y, 0) = avg;
            img(x, y, 1) = avg;
            img(x, y, 2) = avg;
        }
    }
}

void applyBlackAndWhite(Image& img) {
    applyGrayscale(img);
    for (int y = 0; y < img.height; ++y) {
        for (int x = 0; x < img.width; ++x) {
            unsigned char val = img(x, y, 0) >= 128 ? 255 : 0;
            img(x, y, 0) = val;
            img(x, y, 1) = val;
            img(x, y, 2) = val;
        }
    }
}

void applyInvert(Image& img) {
    for (int y = 0; y < img.height; ++y) {
        for (int x = 0; x < img.width; ++x) {
            for (int c = 0; c < img.channels; ++c) {
                img(x, y, c) = 255 - img(x, y, c);
            }
        }
    }
}

void applyFlipHorizontal(Image& img) {
    for (int y = 0; y < img.height; ++y) {
        for (int x = 0; x < img.width / 2; ++x) {
            for (int c = 0; c < img.channels; ++c) {
                std::swap(img(x, y, c), img(img.width - 1 - x, y, c));
            }
        }
    }
}

void applyFlipVertical(Image& img) {
    for (int y = 0; y < img.height / 2; ++y) {
        for (int x = 0; x < img.width; ++x) {
            for (int c = 0; c < img.channels; ++c) {
                std::swap(img(x, y, c), img(x, img.height - 1 - y, c));
            }
        }
    }
}

void applyDarken(Image& img, int percentage) {
    double factor = (100 - percentage) / 100.0;
    for (int y = 0; y < img.height; ++y) {
        for (int x = 0; x < img.width; ++x) {
            for (int c = 0; c < img.channels; ++c) {
                img(x, y, c) = (unsigned char)(img(x, y, c) * factor);
            }
        }
    }
}

void applyLighten(Image& img, int percentage) {
    double factor = (100 + percentage) / 100.0;
    for (int y = 0; y < img.height; ++y) {
        for (int x = 0; x < img.width; ++x) {
            for (int c = 0; c < img.channels; ++c) {
                int val = (int)(img(x, y, c) * factor);
                img(x, y, c) = val > 255 ? 255 : val;
            }
        }
    }
}

Image applyRotate(Image& img, int angle) {
    if (angle == 90) {
        Image newImg(img.height, img.width);
        for (int y = 0; y < img.height; ++y) {
            for (int x = 0; x < img.width; ++x) {
                for (int c = 0; c < 3; ++c) {
                    newImg.setPixel(y, img.width - 1 - x, c, img.getPixel(x, y, c));
                }
            }
        }
        return newImg;
    } else if (angle == 180) {
        Image newImg(img.width, img.height);
        for (int y = 0; y < img.height; ++y) {
            for (int x = 0; x < img.width; ++x) {
                for (int c = 0; c < 3; ++c) {
                    newImg.setPixel(img.width - 1 - x, img.height - 1 - y, c, img.getPixel(x, y, c));
                }
            }
        }
        return newImg;
    } else if (angle == 270) {
        Image newImg(img.height, img.width);
        for (int y = 0; y < img.height; ++y) {
            for (int x = 0; x < img.width; ++x) {
                for (int c = 0; c < 3; ++c) {
                    newImg.setPixel(img.height - 1 - y, x, c, img.getPixel(x, y, c));
                }
            }
        }
        return newImg;
    }
    return img;
}

Image applyResize(Image& img, int newWidth, int newHeight) {
    Image newImg(newWidth, newHeight);
    double scaleW = (double)img.width / newWidth;
    double scaleH = (double)img.height / newHeight;
    for (int y = 0; y < newHeight; ++y) {
        for (int x = 0; x < newWidth; ++x) {
            int oldX = std::min((int)(x * scaleW), img.width - 1);
            int oldY = std::min((int)(y * scaleH), img.height - 1);
            for (int c = 0; c < 3; ++c) {
                newImg.setPixel(x, y, c, img.getPixel(oldX, oldY, c));
            }
        }
    }
    return newImg;
}

Image applyCrop(Image& img, int startX, int startY, int cropWidth, int cropHeight) {
    Image newImg(cropWidth, cropHeight);
    for (int y = 0; y < cropHeight; ++y) {
        for (int x = 0; x < cropWidth; ++x) {
            for (int c = 0; c < 3; ++c) {
                newImg.setPixel(x, y, c, img.getPixel(startX + x, startY + y, c));
            }
        }
    }
    return newImg;
}

Image applySkew(Image& img, double angleDeg) {
    double angleRad = angleDeg * M_PI / 180.0;
    double skewOffsetMax = img.height * std::tan(angleRad);
    int newWidth = img.width + std::abs(skewOffsetMax);
    Image newImg(newWidth, img.height);
    
    for (int y = 0; y < img.height; ++y) {
        for (int x = 0; x < newWidth; ++x) {
            for (int c = 0; c < 3; ++c) {
                newImg.setPixel(x, y, c, 255);
            }
        }
    }
    
    for (int y = 0; y < img.height; ++y) {
        double shift = (img.height - 1 - y) * std::tan(angleRad);
        if (angleDeg < 0) {
            shift = y * std::tan(-angleRad);
        }
        int shiftInt = std::round(shift);
        for (int x = 0; x < img.width; ++x) {
            int nx = x + shiftInt;
            if (nx >= 0 && nx < newWidth) {
                for (int c = 0; c < 3; ++c) {
                    newImg.setPixel(nx, y, c, img.getPixel(x, y, c));
                }
            }
        }
    }
    
    return newImg;
}

Image applyMerge(Image& img1, Image& img2, int mode) {
    if (mode == 1) {
        int w = std::max(img1.width, img2.width);
        int h = std::max(img1.height, img2.height);
        Image r1 = applyResize(img1, w, h);
        Image r2 = applyResize(img2, w, h);
        Image newImg(w, h);
        for (int y = 0; y < h; ++y) {
            for (int x = 0; x < w; ++x) {
                for (int c = 0; c < 3; ++c) {
                    newImg.setPixel(x, y, c, (r1.getPixel(x, y, c) + r2.getPixel(x, y, c)) / 2);
                }
            }
        }
        return newImg;
    } else {
        int w = std::min(img1.width, img2.width);
        int h = std::min(img1.height, img2.height);
        Image newImg(w, h);
        for (int y = 0; y < h; ++y) {
            for (int x = 0; x < w; ++x) {
                for (int c = 0; c < 3; ++c) {
                    newImg.setPixel(x, y, c, (img1.getPixel(x, y, c) + img2.getPixel(x, y, c)) / 2);
                }
            }
        }
        return newImg;
    }
}

void applyEdgeDetect(Image& img) {
    std::vector<std::vector<int>> gray(img.height, std::vector<int>(img.width));
    for(int y=0; y<img.height; ++y){
        for(int x=0; x<img.width; ++x){
            gray[y][x] = (img(x,y,0) + img(x,y,1) + img(x,y,2))/3;
        }
    }
    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    
    std::vector<std::vector<unsigned char>> res(img.height, std::vector<unsigned char>(img.width));
    for(int y=1; y<img.height-1; ++y){
        for(int x=1; x<img.width-1; ++x){
            int sumX = 0, sumY = 0;
            for(int i=-1; i<=1; ++i){
                for(int j=-1; j<=1; ++j){
                    sumX += gray[y+i][x+j] * gx[i+1][j+1];
                    sumY += gray[y+i][x+j] * gy[i+1][j+1];
                }
            }
            int mag = std::sqrt(sumX*sumX + sumY*sumY);
            res[y][x] = mag > 100 ? 0 : 255;
        }
    }
    
    for(int y=0; y<img.height; ++y){
        for(int x=0; x<img.width; ++x){
            unsigned char v = (y>0 && y<img.height-1 && x>0 && x<img.width-1) ? res[y][x] : 255;
            img(x,y,0) = v;
            img(x,y,1) = v;
            img(x,y,2) = v;
        }
    }
}

void applyBlur(Image& img, int level) {
    int radius = 8;
    if (level == 2) radius = 18;
    else if (level == 3) radius = 35;
    
    Image temp(img.width, img.height);
    #pragma omp parallel for collapse(2)
    for (int y = 0; y < img.height; ++y) {
        for (int x = 0; x < img.width; ++x) {
            int sum[3] = {0,0,0};
            int count = 0;
            for (int dx = -radius; dx <= radius; ++dx) {
                int nx = x + dx;
                if (nx >= 0 && nx < img.width) {
                    sum[0] += img(nx, y, 0);
                    sum[1] += img(nx, y, 1);
                    sum[2] += img(nx, y, 2);
                    count++;
                }
            }
            temp(x, y, 0) = sum[0] / count;
            temp(x, y, 1) = sum[1] / count;
            temp(x, y, 2) = sum[2] / count;
        }
    }
    
    #pragma omp parallel for collapse(2)
    for (int x = 0; x < img.width; ++x) {
        for (int y = 0; y < img.height; ++y) {
            int sum[3] = {0,0,0};
            int count = 0;
            for (int dy = -radius; dy <= radius; ++dy) {
                int ny = y + dy;
                if (ny >= 0 && ny < img.height) {
                    sum[0] += temp(x, ny, 0);
                    sum[1] += temp(x, ny, 1);
                    sum[2] += temp(x, ny, 2);
                    count++;
                }
            }
            img(x, y, 0) = sum[0] / count;
            img(x, y, 1) = sum[1] / count;
            img(x, y, 2) = sum[2] / count;
        }
    }
}

void applySunlight(Image& img) {
    for (int y = 0; y < img.height; ++y) {
        for (int x = 0; x < img.width; ++x) {
            for (int c = 0; c < 3; ++c) {
                int val = img(x, y, c) + 40;
                img(x, y, c) = val > 255 ? 255 : val;
            }
        }
    }
}

void applyTV(Image& img) {
    for (int y = 0; y < img.height; ++y) {
        if ((y % 20) < 10) {
            for (int x = 0; x < img.width; ++x) {
                for (int c = 0; c < 3; ++c) {
                    img(x, y, c) = (unsigned char)(img(x, y, c) * 0.3);
                }
            }
        }
    }
}

void applyPurple(Image& img) {
    for (int y = 0; y < img.height; ++y) {
        for (int x = 0; x < img.width; ++x) {
            int r = img(x, y, 0) * 1.2;
            int g = img(x, y, 1) * 0.8;
            int b = img(x, y, 2) * 1.2;
            img(x, y, 0) = r > 255 ? 255 : r;
            img(x, y, 1) = g;
            img(x, y, 2) = b > 255 ? 255 : b;
        }
    }
}

void applyInfrared(Image& img) {
    for (int y = 0; y < img.height; ++y) {
        for (int x = 0; x < img.width; ++x) {
            img(x, y, 0) = 255;
            img(x, y, 1) = 255 - img(x, y, 1);
            img(x, y, 2) = 255 - img(x, y, 2);
        }
    }
}

void applyFrame(Image& img, int type) {
    int frameSize = std::min(img.width, img.height) / 20;
    int smallFrameSize = std::max(1, frameSize / 3);
    
    for (int y = 0; y < img.height; ++y) {
        for (int x = 0; x < img.width; ++x) {
            if (x < frameSize || x >= img.width - frameSize || 
                y < frameSize || y >= img.height - frameSize) {
                img(x, y, 0) = 30;
                img(x, y, 1) = 30;
                img(x, y, 2) = 30;
            } else if (x < frameSize + smallFrameSize || x >= img.width - frameSize - smallFrameSize || 
                       y < frameSize + smallFrameSize || y >= img.height - frameSize - smallFrameSize) {
                img(x, y, 0) = 212;
                img(x, y, 1) = 175;
                img(x, y, 2) = 55;
            }
        }
    }
    
    if (type == 2) {
        int cornerSize = frameSize * 3;
        for (int y = 0; y < img.height; ++y) {
            for (int x = 0; x < img.width; ++x) {
                if ((x < cornerSize && y < cornerSize) ||
                    (x >= img.width - cornerSize && y < cornerSize) ||
                    (x < cornerSize && y >= img.height - cornerSize) ||
                    (x >= img.width - cornerSize && y >= img.height - cornerSize)) {
                    if (x < frameSize || x >= img.width - frameSize || 
                        y < frameSize || y >= img.height - frameSize) {
                        img(x, y, 0) = 92;
                        img(x, y, 1) = 64;
                        img(x, y, 2) = 51;
                    }
                }
            }
        }
    }
}

void applyOilPaint(Image& img) {
    int radius = 5;
    int levels = 20;
    Image temp(img.width, img.height);
    
    #pragma omp parallel for collapse(2)
    for (int y = 0; y < img.height; ++y) {
        for (int x = 0; x < img.width; ++x) {
            std::vector<int> intensityCount(levels, 0);
            std::vector<int> sumR(levels, 0);
            std::vector<int> sumG(levels, 0);
            std::vector<int> sumB(levels, 0);
            
            for (int dy = -radius; dy <= radius; ++dy) {
                for (int dx = -radius; dx <= radius; ++dx) {
                    int nx = x + dx;
                    int ny = y + dy;
                    if (nx >= 0 && nx < img.width && ny >= 0 && ny < img.height) {
                        int r = img(nx, ny, 0);
                        int g = img(nx, ny, 1);
                        int b = img(nx, ny, 2);
                        int curIntensity = (((r + g + b) / 3) * levels) / 256;
                        if (curIntensity > levels - 1) curIntensity = levels - 1;
                        
                        intensityCount[curIntensity]++;
                        sumR[curIntensity] += r;
                        sumG[curIntensity] += g;
                        sumB[curIntensity] += b;
                    }
                }
            }
            
            int maxIntensity = 0;
            int maxCount = 0;
            for (int i = 0; i < levels; ++i) {
                if (intensityCount[i] > maxCount) {
                    maxCount = intensityCount[i];
                    maxIntensity = i;
                }
            }
            
            temp(x, y, 0) = sumR[maxIntensity] / maxCount;
            temp(x, y, 1) = sumG[maxIntensity] / maxCount;
            temp(x, y, 2) = sumB[maxIntensity] / maxCount;
        }
    }
    
    for (int y = 0; y < img.height; ++y) {
        for (int x = 0; x < img.width; ++x) {
            for (int c = 0; c < 3; ++c) {
                img(x, y, c) = temp(x, y, c);
            }
        }
    }
}
