#include "Image.h"

void Image::lighten() {
    lighten(0.1);
}

void Image::lighten(double amount) {
    for (unsigned i = 0; i < width(); i++) {
        for (unsigned j = 0; j < height(); j++) {
            cs225::HSLAPixel& cnm = getPixel(i, j);
            cnm.l += amount;
            if (cnm.l > 1.0) {
                cnm.l = 1.0;
            }
        }
    }
}

void Image::darken() {
    darken(0.1);
}

void Image::darken(double amount) {
    for (unsigned i = 0; i < width(); i++) {
        for (unsigned j = 0; j < height(); j++) {
            cs225::HSLAPixel& cnm = getPixel(i, j);
            cnm.l -= amount;
            if (cnm.l < 0.0) {
                cnm.l = 0.0;
            }
        }
    }
}

void Image::saturate() {
    saturate(0.1);
}

void Image::saturate(double amount) {
    for (unsigned i = 0; i < width(); i++) {
        for (unsigned j = 0; j < height(); j++) {
            cs225::HSLAPixel& cnm = getPixel(i, j);
            cnm.s += amount;
            if (cnm.s > 1.0) {
                cnm.s = 1.0;
            }
        }
    }
}

void Image::desaturate() {
    desaturate(0.1);
}

void Image::desaturate(double amount) {
    for (unsigned i = 0; i < width(); i++) {
        for (unsigned j = 0; j < height(); j++) {
            cs225::HSLAPixel& cnm = getPixel(i, j);
            cnm.s -= amount;
            if (cnm.s < 0.0) {
                cnm.s = 0.0;
            }
        }
    }
}

void Image::grayscale() {
    for (unsigned i = 0; i < width(); i++) {
        for (unsigned j = 0; j < height(); j++) {
            cs225::HSLAPixel& cnm = getPixel(i, j);
            cnm.s = 0;
        }
    }
}

void Image::rotateColor(double degrees) {
    for (unsigned i = 0; i < width(); i++) {
        for (unsigned j = 0; j < height(); j++) {
            cs225::HSLAPixel& cnm = getPixel(i, j);
            cnm.h += degrees;
            if (cnm.h > 360.0) {
                cnm.h = cnm.h - 360.0;
            } else if (cnm.h < 0.0) {
                cnm.h = cnm.h + 360.0;
            }
        }
    }
}

void Image::invert() {
    for (unsigned i = 0; i < width(); i++) {
        for (unsigned j = 0; j < height();j++) {
            cs225::HSLAPixel& cnm = getPixel(i, j);
            cnm.h += 180.0;
            if (cnm.h > 360.0) {
                cnm.h = cnm.h - 360.0;
            }
            cnm.s = 1.0 - cnm.s;
            cnm.l = 1.0 - cnm.l;
        }
    }
}

void Image::scale(double factor) {
    if (factor <= 0) {
        return;
    }
    unsigned originalWidth = width();
    unsigned originalHeight = height();
    unsigned newWidth = width() * factor;
    unsigned newHeight = height() * factor;
    cs225::HSLAPixel* nmsl = new cs225::HSLAPixel[width() * height()];
    for (unsigned i = 0; i < width(); i++) {
        for (unsigned j = 0; j < height(); j++) {
            nmsl[i + j * width()] = getPixel(i, j);
        }
    }
    resize(newWidth, newHeight);
    for (unsigned i = 0; i < newWidth; i++) {
        for (unsigned j = 0; j < newHeight; j++) {
            getPixel(i, j) = nmsl[static_cast<unsigned>(i / factor) + static_cast<unsigned>(j / factor) * originalWidth];
        }
    }
    delete[] nmsl;
}


void Image::scale(unsigned w, unsigned h) {
    double factorW = static_cast<double>(w) / width();
    double factorH = static_cast<double>(h) / height();
    double factor = std::min(factorW, factorH);
    scale(factor);
}