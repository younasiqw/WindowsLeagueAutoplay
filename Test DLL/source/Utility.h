//
//  Utility.h
//  Fluffy Pug
//
//  Created by Matthew French on 5/27/15.
//  Copyright (c) 2015 Matthew French. All rights reserved.
//

#ifndef __Fluffy_Pug__Utility__
#define __Fluffy_Pug__Utility__

/*
#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import <AppKit/AppKit.h>
#include <mach/mach.h>
#include <mach/mach_time.h>
#include <unistd.h>
 */
#include <time.h>
#include <Windows.h>
#include <cstdint>
#include <string>
#include <math.h>
#include "Detection/Objects/Minion.h"
#include "Detection/Objects/Champion.h"
#include "Detection/Objects/SelfHealth.h"
#include "Detection/Objects/Tower.h"
#include "Detection/Objects/GenericObject.h"
#include "Detection/Objects/Position.h"

//#define cimg_display 0
//#define cimg_use_png

//#include "lib/CImg.h"

using namespace std;
//using namespace cimg_library; 


//
//  timer
//
extern inline double read_timer( )
{
    static bool initialized = false;
    static __int64 CounterStart = 0;
	static double PCFreq = 0.0;
    if( !initialized )
    {
		LARGE_INTEGER li;
		QueryPerformanceCounter(&li);
		PCFreq = double(li.QuadPart);
		CounterStart = li.QuadPart;
        initialized = true;
    }
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	return double(li.QuadPart - CounterStart) / PCFreq;
}





struct ImageData {
    //CFDataRef rawData;
    uint8_t * imageData;
    unsigned long imageByteLength;
    int imageWidth; int imageHeight;
};

struct Pixel {
    unsigned char r, g, b;
    bool exist;
};


inline  ImageData makeImageData(uint8_t * data, int imageWidth, int imageHeight);

/*
inline ImageData loadImage(string name) {
    CImg<unsigned char> image(name.c_str());

    //need to make a uint8_t
    uint8_t * data = (uint8_t *)malloc(sizeof(uint8_t) * image.width() * image.height() * 4);

    for (int x = 0; x < image.width(); x++) {
        for (int y = 0; y < image.height(); y++) {
            data[(x + y * image.width())*4 + 0] = image.atXY(x, y, 0);
            data[(x + y * image.width())*4 + 1] = image.atXY(x, y, 1);
            data[(x + y * image.width())*4 + 2] = image.atXY(x, y, 2);
            if (image.spectrum() <= 3) {
                data[(x + y * image.width())*4 + 3] = 255;
            } else {
                data[(x + y * image.width())*4 + 3] = image.atXY(x, y, 3);
            }
        }
    }
    return makeImageData(data, image.width(), image.height());;
}*/
inline Position makePosition(int x, int y);
inline int getRandomInteger(int minimum, int maximum);
inline  Minion* makeMinionBar( Position topLeft,  Position bottomLeft,  Position topRight,  Position bottomRight, double health);
inline  Pixel getPixel( ImageData imageData, int x, int y);
inline  uint8_t* getPixel2( ImageData imageData, int x, int y);
inline  uint8_t* getPixel3( uint8_t *baseAddress, int x, int y, int width);
inline void setPixel( ImageData imageData, int x, int y, int r, int g, int b);
inline void drawRect( ImageData imageData, int left, int top, int width, int height, int r, int g, int b);
inline bool isPixelColor( Pixel pixel, unsigned char r, unsigned char g, unsigned char b, int tolerance);
inline bool isPixelPreciseColor( Pixel pixel, unsigned char r, unsigned char g, unsigned char b);
inline bool isColor(const uint8_t *pixel, unsigned char r, unsigned char g, unsigned char b, int tolerance);
inline bool isColor3(const uint8_t *pixel, unsigned char r, unsigned char g, unsigned char b);
inline bool isColor2(const uint8_t *pixel, const uint8_t *pixel2, int tolerance);
//inline ImageData makeImageDataFrom(string* path);
//inline bool detectImageAtPixel(const uint8_t *pixel, int x, int y, int width, int height, ImageData image, int tolerance);
//inline bool detectImageAtPixelPercentage(const uint8_t *pixel, int x, int y, int width, int height, ImageData image, double percentage);
inline void normalizePoint(int &x, int &y, int length);
//inline Position detectRelativeImageInImage(ImageData smallImage, ImageData largeImage, double percentageMatch, int xStart, int yStart, int xEnd, int yEnd);
//inline Position detectRelativeImageInImagePercentage(ImageData smallImage, ImageData largeImage, double percentageMatch, int xStart, int yStart, int xEnd, int yEnd, double &returnPercentage);
inline double getColorPercentage(const uint8_t *pixel, const uint8_t *pixel2);
inline bool colorInPercentage(const uint8_t *pixel, const uint8_t *pixel2, double percentage);
//inline double getImageAtPixelPercentage(const uint8_t *pixel, int x, int y, int width, int height, ImageData image);
inline uint8_t * copyImageBuffer(uint8_t *baseAddress, int bufferWidth, int bufferHeight);
inline uint8_t * copyImageBufferSection(uint8_t *baseAddress, int bufferWidth, int bufferHeight, int copyX, int copyY, int copyWidth, int copyHeight) ;
inline uint8_t * copyImageBufferFromBGRAtoRGBA(uint8_t *baseAddress, int bufferWidth, int bufferHeight);
//inline NSImage* getImageFromBGRABuffer(uint8_t *baseAddress, int bufferWidth, int bufferHeight);
//inline NSImage* getImageFromRGBABuffer(uint8_t *baseAddress, int bufferWidth, int bufferHeight);
//inline NSImage* getImageFromBGRABufferImageData(ImageData* imageData);
//inline NSImage* getImageFromRGBABufferImageData(ImageData* imageData);
inline void detectSimilarImageToImage(ImageData smallImage, ImageData largeImage, int xStart, int yStart, int xEnd, int yEnd, double &returnPercentage, Position &returnPosition, double minimumPercentage, bool getFirstMatching);
inline int getTimeInMilliseconds(int64_t absoluteTime);
inline double getImageAtPixelPercentageOptimized(const uint8_t *pixel, int x, int y, int width, int height, ImageData image, double minimumPercentage);
inline double getImageAtPixelPercentageOptimizedExact(const uint8_t *pixel, int x, int y, int width, int height, ImageData image, double minimumPercentage);
inline void detectExactImageToImage(ImageData smallImage, ImageData largeImage, int xStart, int yStart, int xEnd, int yEnd, double &returnPercentage, Position &returnPosition, double minimumPercentage, bool getFirstMatching);
//inline void detectExactImageToImageToRectangles(ImageData smallImage, ImageData largeImage, CGRect* rects, size_t num_rects, double &returnPercentage, Position &returnPosition, double minimumPercentage, bool getFirstMatching);
//inline CGRect* getIntersectionRectangles(CGRect baseRect, const CGRect* rects, size_t num_rects, size_t &returnNumRects);

//inline void detectExactImageToImageToRectangle(ImageData smallImage, ImageData largeImage, CGRect rect, double &returnPercentage, Position &returnPosition, double minimumPercentage, bool getFirstMatching);
//inline void combineRectangles(NSMutableArray* rectangles, CGRect newRect);
//inline NSMutableArray* getCGRectDifference(CGRect sourceRect, CGRect minusRect);
//inline CGRect fitRectangleInRectangle(CGRect smallRect, CGRect bigRect);
//inline void MyLog(string *format, ...);

/*
extern inline CGRect fitRectangleInRectangle(CGRect smallRect, CGRect bigRect) {
    if (CGRectIntersectsRect(smallRect, bigRect) == false) {
        smallRect.size.width = 0.0;
        return smallRect;
    }
    if (smallRect.origin.x < bigRect.origin.x) {
        double diff = bigRect.origin.x - smallRect.origin.x;
        smallRect.origin.x = bigRect.origin.x;
        smallRect.size.width -= diff;
    }
    if (smallRect.origin.y < bigRect.origin.y) {
        double diff = bigRect.origin.y - smallRect.origin.y;
        smallRect.origin.y = bigRect.origin.y;
        smallRect.size.height -= diff;
    }
    if (smallRect.origin.x + smallRect.size.width > bigRect.origin.x + bigRect.size.width) {
        double diff = (bigRect.origin.x + bigRect.size.width) - (smallRect.origin.x + smallRect.size.width);
        smallRect.size.width += diff;
    }
    if (smallRect.origin.y + smallRect.size.height > bigRect.origin.y + bigRect.size.height) {
        double diff = (bigRect.origin.y + bigRect.size.height) - (smallRect.origin.y + smallRect.size.height);
        smallRect.size.height += diff;
    }
    return smallRect;
}
*/
/*
///Return all rectangles in source rect that don't contain minus rect.
extern inline NSMutableArray* getCGRectDifference(CGRect sourceRect, CGRect minusRect) {
    NSMutableArray* rectArr = [NSMutableArray new];
    CGRect intersectRect = CGRectIntersection(sourceRect, minusRect);
    if (CGRectIsNull(intersectRect)) {
        //Return source rect
        if (sourceRect.size.width > 0 && sourceRect.size.height > 0) [rectArr addObject:[NSValue valueWithRect:sourceRect]];
    } else {
        //Chop source rect up
        //Minus rect could contain source rect, that'd mean return nothing
        if (sourceRect.origin.x >= minusRect.origin.x && sourceRect.origin.x < minusRect.origin.x + minusRect.size.width
            && sourceRect.origin.x + sourceRect.size.width > minusRect.origin.x &&
            sourceRect.origin.x + sourceRect.size.width <= minusRect.origin.x + minusRect.size.width &&
            
            sourceRect.origin.y >= minusRect.origin.y && sourceRect.origin.y < minusRect.origin.y + minusRect.size.height
            && sourceRect.origin.y + sourceRect.size.height > minusRect.origin.y &&
            sourceRect.origin.y + sourceRect.size.height <= minusRect.origin.y + minusRect.size.height) {
            return rectArr; //sourceRect is inside minusRect. Return nothing
        }
        //Can't I just scan from left to right and chop pieces off then from top to bottom?
        if (sourceRect.origin.x < minusRect.origin.x) {
            //Chop off left half
            CGRect newRect = CGRectMake(sourceRect.origin.x, sourceRect.origin.y, minusRect.origin.x - sourceRect.origin.x, sourceRect.size.height);
            sourceRect.size.width -= newRect.size.width;
            sourceRect.origin.x = minusRect.origin.x;
            if (newRect.size.width > 0 && newRect.size.height > 0) [rectArr addObject:[NSValue valueWithRect:newRect]];
        }
        if (sourceRect.origin.x+sourceRect.size.width > minusRect.origin.x+minusRect.size.width) {
            //Chop off right half
            CGRect newRect = CGRectMake(minusRect.origin.x+minusRect.size.width, sourceRect.origin.y, sourceRect.size.width - (minusRect.origin.x+minusRect.size.width - sourceRect.origin.x), sourceRect.size.height);
            sourceRect.size.width -= newRect.size.width;
            if (newRect.size.width > 0 && newRect.size.height > 0) [rectArr addObject:[NSValue valueWithRect:newRect]];
        }
        if (sourceRect.origin.y < minusRect.origin.y) {
            //Chop off top half
            CGRect newRect = CGRectMake(sourceRect.origin.x, sourceRect.origin.y, sourceRect.size.width, minusRect.origin.y - sourceRect.origin.y);
            sourceRect.size.height -= newRect.size.height;
            sourceRect.origin.y = minusRect.origin.y;
            if (newRect.size.width > 0 && newRect.size.height > 0) [rectArr addObject:[NSValue valueWithRect:newRect]];
        }
        if (sourceRect.origin.y+sourceRect.size.height > minusRect.origin.y+minusRect.size.height) {
            //Chop off bottom half
            CGRect newRect = CGRectMake(sourceRect.origin.x, minusRect.origin.y+minusRect.size.height, sourceRect.size.width, sourceRect.size.height - (minusRect.origin.y+minusRect.size.height - sourceRect.origin.y));
            sourceRect.size.height -= newRect.size.height;
            if (newRect.size.width > 0 && newRect.size.height > 0) [rectArr addObject:[NSValue valueWithRect:newRect]];
        }
    }
    return rectArr;
}
*/
/*
///Combine rectangles adds a new rectangle without allowing it to overlap.
extern inline void combineRectangles(NSMutableArray* rectangles, CGRect newRect) {
    if (newRect.size.width <= 0 || newRect.size.height <= 0 || CGRectIsNull(newRect)) return;
    NSMutableArray* addRectangles = [NSMutableArray new];
    [addRectangles addObject: [NSValue valueWithRect: newRect]];
    for (int i = 0; i < [rectangles count]; i++) {
        CGRect rect = [[rectangles objectAtIndex:i] rectValue];
        //Now loop through each added rectangle and break up intersections
        for (int i2 = 0; i2 < [addRectangles count]; i2++) {
            CGRect rect2 = [[addRectangles objectAtIndex:i2] rectValue];
            
            NSMutableArray* rectDifference = getCGRectDifference(rect2, rect);
            [addRectangles removeObjectAtIndex:i2];
            i2--;
            for (NSValue* r : rectDifference) {
                [addRectangles insertObject:r atIndex:0];
            }
            i2 += [rectDifference count];
        }
    }
    [rectangles addObjectsFromArray: addRectangles];
}
*/
extern inline int getTimeInMilliseconds(int64_t absoluteTime)
{
    /*
    const int64_t kOneMillion = 1000 * 1000;
    static mach_timebase_info_data_t s_timebase_info;
    
    if (s_timebase_info.denom == 0) {
        (void) mach_timebase_info(&s_timebase_info);
    }
    
    // mach_absolute_time() returns billionth of seconds,
    // so divide by one million to get milliseconds
    return (int)((absoluteTime * s_timebase_info.numer) / (kOneMillion * s_timebase_info.denom));
*/
    return 0;
}
/*
extern inline CGRect* getIntersectionRectangles(CGRect baseRect, const CGRect* rects, size_t num_rects, size_t &returnNumRects) {
    returnNumRects = 0;
    CGRect* newRects = (CGRect*) calloc (num_rects,sizeof(CGRect));
    for (int i = 0; i < num_rects; i++) {
        CGRect r = CGRectIntersection(baseRect, rects[i]);
        if (!CGRectIsNull(r)) {
            newRects[returnNumRects] = r;
            returnNumRects++;
        }
    }
    return newRects;
}*/

    extern inline uint8_t * copyImageBufferSection(uint8_t *baseAddress, int bufferWidth, int bufferHeight, int copyX, int copyY, int copyWidth, int copyHeight) {
        uint8_t * testImage = (uint8_t*) calloc (copyWidth * copyHeight * 4,sizeof(uint8_t));
        for (int x = copyX; x < copyX+copyWidth; x++) {
            for (int y = copyY; y < copyY+copyHeight; y++) {
                uint8_t *largePixel = getPixel3(baseAddress, x, y, bufferWidth);
                uint8_t *newPixel = getPixel3(testImage, x - copyX, y - copyY, copyWidth);
                newPixel[0] = largePixel[0];
                newPixel[1] = largePixel[1];
                newPixel[2] = largePixel[2];
                newPixel[3] = largePixel[3];
            }
        }
        return testImage;
    }
/*
extern inline void detectExactImageToImageToRectangle(ImageData smallImage, ImageData largeImage, CGRect rect, double &returnPercentage, Position &returnPosition, double minimumPercentage, bool getFirstMatching) {
    Position position;
    double highestPercentage;
    returnPercentage = 0.0;
        detectExactImageToImage(smallImage, largeImage, rect.origin.x, rect.origin.y, rect.origin.x+rect.size.width, rect.origin.y+rect.size.height, highestPercentage, position, minimumPercentage, getFirstMatching);
        if (highestPercentage > returnPercentage) {
            returnPercentage = highestPercentage;
            returnPosition = position;
            if (getFirstMatching && highestPercentage >= minimumPercentage) {
                return;
            }
        }
}*/
/*
extern inline void detectExactImageToImageToRectangles(ImageData smallImage, ImageData largeImage, CGRect* rects, size_t num_rects, double &returnPercentage, Position &returnPosition, double minimumPercentage, bool getFirstMatching) {
    Position position;
    double highestPercentage;
    returnPercentage = 0.0;
    for (int i = 0; i < num_rects; i++) {
        CGRect rect = rects[i];
        detectExactImageToImage(smallImage, largeImage, rect.origin.x, rect.origin.y, rect.origin.x+rect.size.width, rect.origin.y+rect.size.height, highestPercentage, position, minimumPercentage, getFirstMatching);
        if (highestPercentage > returnPercentage) {
            returnPercentage = highestPercentage;
            returnPosition = position;
            if (getFirstMatching && highestPercentage >= minimumPercentage) {
                return;
            }
        }
    }
}*/
    extern inline void detectExactImageToImage(ImageData smallImage, ImageData largeImage, int xStart, int yStart, int xEnd, int yEnd, double &returnPercentage, Position &returnPosition, double minimumPercentage, bool getFirstMatching) {
    //Minimum percentage is so it matches faster
        double highestPercent = 0.0;
        Position location;
        location.x = -1; location.y = -1;
    //Stop image search from putting the width and height past the end
        yEnd -= smallImage.imageHeight;
        xEnd -= smallImage.imageWidth;

        for (int y = yStart; y < yEnd; y++) {
            uint8_t *pixel = getPixel2(largeImage, xStart, y);
            for (int x = xStart; x < xEnd; x++) {
                double percent = getImageAtPixelPercentageOptimizedExact(pixel, x, y, largeImage.imageWidth, largeImage.imageHeight, smallImage, minimumPercentage);
                if (percent > highestPercent) {
                    location.x = x; location.y = y;
                    highestPercent = percent;
                    if (percent >= minimumPercentage && getFirstMatching) {
                        x = xEnd; y = yEnd;
                    }
                }
                pixel += 4;
            }
        }
        returnPercentage = highestPercent;
        returnPosition = location;
    }
    extern inline double getImageAtPixelPercentageOptimizedExact(const uint8_t *pixel, int x, int y, int width, int height, ImageData image, double minimumPercentage) {
        int pixels = 0;
        int maxPixelCount = image.imageWidth * image.imageHeight;
        int skipPixels = 4 * (width - image.imageWidth);
        double percentage = 0.0;
        uint8_t *pixel2 = image.imageData;
    //int xLimit = image.imageWidth;
    //int yLimit = image.imageHeight;
        if (x + image.imageWidth > width || y + image.imageHeight > height) {
            return 0.0;
        //xLimit = width - x;
        //NSLog(@"%d vs %d", x + image.imageWidth, width);
        //NSLog(@"Add amount pixels: %d", (image.imageWidth - xLimit));
        //NSLog(@"Old limit: %d vs new limit: %d", image.imageWidth, xLimit);
        }
    //if (y + image.imageHeight > height) yLimit = height - y;
    //int addAmountPixels = (image.imageWidth - xLimit);
    //int addAmount = addAmountPixels * 4;
        int perfectPixels = 0;
        int nonPerfectPixels = 0;
        for (int y1 = 0; y1 < image.imageHeight; y1++) {
        //const uint8_t *pixel1 = pixel + y1 * width * 4;
            for (int x1 = 0; x1 < image.imageWidth; x1++) {
                if (pixel2[3] != 0) {
                    pixels++;
                    double p = getColorPercentage(pixel, pixel2);

                    percentage += p;
                    if (p < minimumPercentage) {
                        return percentage / maxPixelCount;
                    }
                    if (p == 1.0) {
                        perfectPixels++;
                    } else {
                        nonPerfectPixels++;
                    }
                } else {maxPixelCount--;}
                pixel2 += 4;
                pixel += 4;
            }
        //pixel2 += addAmount;
        //pixels += addAmountPixels;
            pixel += skipPixels;
        }
        return percentage / pixels;
    }
    extern inline void detectSimilarImageToImage(ImageData smallImage, ImageData largeImage, int xStart, int yStart, int xEnd, int yEnd, double &returnPercentage, Position &returnPosition, double minimumPercentage, bool getFirstMatching) {
    //Minimum percentage is so it matches faster
        double highestPercent = 0.0;
        Position location;
        location.x = -1; location.y = -1;
    //Stop image search from putting the width and height past the end
        yEnd -= smallImage.imageHeight;
        xEnd -= smallImage.imageWidth;

        for (int y = yStart; y < yEnd; y++) {
            uint8_t *pixel = getPixel2(largeImage, xStart, y);
            for (int x = xStart; x < xEnd; x++) {
                double percent = getImageAtPixelPercentageOptimized(pixel, x, y, largeImage.imageWidth, largeImage.imageHeight, smallImage, minimumPercentage);
                if (percent > highestPercent) {
                    location.x = x; location.y = y;
                    highestPercent = percent;
                    if (percent >= minimumPercentage && getFirstMatching) {
                        x = xEnd; y = yEnd;
                    }
                }
                pixel += 4;
            }
        }
        returnPercentage = highestPercent;
        returnPosition = location;
    }
    extern inline double getImageAtPixelPercentageOptimized(const uint8_t *pixel, int x, int y, int width, int height, ImageData image, double minimumPercentage) {
        int pixels = 0;
        int maxPixelCount = image.imageWidth * image.imageHeight;
        int skipPixels = 4 * (width - image.imageWidth);
        double percentage = 0.0;
        uint8_t *pixel2 = image.imageData;
        for (int y1 = 0; y1 < image.imageHeight; y1++) {
        //const uint8_t *pixel1 = pixel + y1 * width * 4;
            for (int x1 = 0; x1 < image.imageWidth; x1++) {
                if (pixel2[3] != 0) {
                    pixels++;
                    percentage += getColorPercentage(pixel, pixel2);
                } else {maxPixelCount--;}
                pixel2 += 4;
                pixel += 4;
            }
            if ((percentage + (maxPixelCount - pixels)) / maxPixelCount < minimumPercentage) {
                break;
            }
            pixel += skipPixels;
        }
        return percentage / pixels;
    }

/*
extern inline NSImage* getImageFromRGBABuffer(uint8_t *baseAddress, int bufferWidth, int bufferHeight) {
    CGContextRef context = CGBitmapContextCreate(baseAddress, bufferWidth, bufferHeight, 8,  bufferWidth * 4, CGColorSpaceCreateWithName(kCGColorSpaceGenericRGB), kCGImageAlphaPremultipliedLast);
    CGImageRef imageRef = CGBitmapContextCreateImage(context);
    
    return [[NSImage alloc] initWithCGImage:imageRef size:NSMakeSize(bufferWidth, bufferHeight)];
}

extern inline NSImage* getImageFromRGBABufferImageData(ImageData* imageData) {
    uint8_t *baseAddress = imageData->imageData; int bufferWidth = imageData->imageWidth; int bufferHeight = imageData->imageHeight;
    CGContextRef context = CGBitmapContextCreate(baseAddress, bufferWidth, bufferHeight, 8,  bufferWidth * 4, CGColorSpaceCreateWithName(kCGColorSpaceGenericRGB), kCGImageAlphaPremultipliedLast);
    CGImageRef imageRef = CGBitmapContextCreateImage(context);
    
    return [[NSImage alloc] initWithCGImage:imageRef size:NSMakeSize(bufferWidth, bufferHeight)];
}

extern inline NSImage* getImageFromBGRABuffer(uint8_t *baseAddress, int bufferWidth, int bufferHeight) {
    uint8_t *rgbaTestImage = copyImageBufferFromBGRAtoRGBA(baseAddress, bufferWidth, bufferHeight);
    CGContextRef context = CGBitmapContextCreate(rgbaTestImage, bufferWidth, bufferHeight, 8,  bufferWidth * 4, CGColorSpaceCreateWithName(kCGColorSpaceGenericRGB), kCGImageAlphaPremultipliedLast);
    CGImageRef imageRef = CGBitmapContextCreateImage(context);
    free(rgbaTestImage);
    
    return [[NSImage alloc] initWithCGImage:imageRef size:NSMakeSize(bufferWidth, bufferHeight)];
}

extern inline NSImage* getImageFromBGRABufferImageData(ImageData* imageData) {
    uint8_t *baseAddress = imageData->imageData; int bufferWidth = imageData->imageWidth; int bufferHeight = imageData->imageHeight;
    uint8_t *rgbaTestImage = copyImageBufferFromBGRAtoRGBA(baseAddress, bufferWidth, bufferHeight);
    CGContextRef context = CGBitmapContextCreate(rgbaTestImage, bufferWidth, bufferHeight, 8,  bufferWidth * 4, CGColorSpaceCreateWithName(kCGColorSpaceGenericRGB), kCGImageAlphaPremultipliedLast);
    CGImageRef imageRef = CGBitmapContextCreateImage(context);
    free(rgbaTestImage);
    
    return [[NSImage alloc] initWithCGImage:imageRef size:NSMakeSize(bufferWidth, bufferHeight)];
}
*/
extern inline uint8_t * copyImageBufferFromBGRAtoRGBA(uint8_t *baseAddress, int bufferWidth, int bufferHeight) {
    uint8_t * testImage = (uint8_t*) calloc (bufferWidth * bufferHeight * 4,sizeof(uint8_t));
    for (int i = 0; i < bufferWidth * bufferHeight * 4; i+=4) {
        testImage[i] = baseAddress[i+2];
        testImage[i+1] = baseAddress[i+1];
        testImage[i+2] = baseAddress[i];
        testImage[i+3] = baseAddress[i+3];
    }
    return testImage;
}
extern inline uint8_t * copyImageBuffer(uint8_t *baseAddress, int bufferWidth, int bufferHeight) {
    uint8_t * testImage = (uint8_t*) calloc (bufferWidth * bufferHeight * 4,sizeof(uint8_t));
    for (int i = 0; i < bufferWidth * bufferHeight * 4; i+=4) {
        testImage[i] = baseAddress[i];
        testImage[i+1] = baseAddress[i+1];
        testImage[i+2] = baseAddress[i+2];
        testImage[i+3] = baseAddress[i+3];
    }
    return testImage;
}
/*
extern inline Position detectRelativeImageInImage(ImageData smallImage, ImageData largeImage, double percentageMatch, int xStart, int yStart, int xEnd, int yEnd) {
    bool found = false;
    double highestPercent = 0.0;
    Position location;
    location.x = -1; location.y = -1;
    
    for (int y = yStart; y < yEnd; y++) {
        uint8_t *pixel = getPixel2(largeImage, xStart, y);
        for (int x = xStart; x < xEnd; x++) {
            double percent = getImageAtPixelPercentage(pixel, x, y, largeImage.imageWidth, largeImage.imageHeight, smallImage);
            if (percent > highestPercent) {
                location.x = x; location.y = y;
                highestPercent = percent;
                if (highestPercent > percentageMatch) {
                    found = true;
                }
            } else if (percent < highestPercent) { //Skip ahead if not even a close match
                int skip = floor(smallImage.imageWidth*(1.0-percent)/2);
                //NSLog(@"Skipping %d", skipyy);
                x += skip;
                pixel += skip*4;
            }
            pixel += 4;
        }
    }
    //NSLog(@"Highest match: %f at position %d %d", highestPercent, location.x, location.y);
    if (found) {
        return location;
    }
    return makePosition(-1,-1);
}
*/
/*
extern inline Position detectRelativeImageInImagePercentage(ImageData smallImage, ImageData largeImage, double percentageMatch, int xStart, int yStart, int xEnd, int yEnd, double &returnPercentage) {
    bool found = false;
    double highestPercent = 0.0;
    Position location;
    location.x = -1; location.y = -1;
    
    for (int y = yStart; y < yEnd; y++) {
        uint8_t *pixel = getPixel2(largeImage, xStart, y);
        for (int x = xStart; x < xEnd; x++) {
            double percent = getImageAtPixelPercentage(pixel, x, y, largeImage.imageWidth, largeImage.imageHeight, smallImage);
            if (percent > highestPercent) {
                location.x = x; location.y = y;
                highestPercent = percent;
                if (highestPercent > percentageMatch) {
                    found = true;
                }
            } else if (percent < highestPercent) { //Skip ahead if not even a close match
                int skip = floor(smallImage.imageWidth*(1.0-percent)/2);
                //NSLog(@"Skipping %d", skipyy);
                x += skip;
                pixel += skip*4;
            }
            pixel += 4;
        }
    }
    //NSLog(@"Highest match: %f at position %d %d", highestPercent, location.x, location.y);
    returnPercentage = 0;
    if (found) {
        returnPercentage = highestPercent;
    }
    if (found) {
        return location;
    }
    return makePosition(-1,-1);
}*/
/*
extern inline double getImageAtPixelPercentage(const uint8_t *pixel, int x, int y, int width, int height, ImageData image) {
    int pixels = 0;
    if (width - x > image.imageWidth &&
        height - y > image.imageHeight) {
        double percentage = 0.0;
        uint8_t *pixel2 = image.imageData;
        for (int y1 = 0; y1 < image.imageHeight; y1++) {
            const uint8_t *pixel1 = pixel + (y1 * width)*4;
            for (int x1 = 0; x1 < image.imageWidth; x1++) {
                if (pixel2[3] != 0) {
                    pixels++;
                    percentage += getColorPercentage(pixel1, pixel2);
                }
                pixel2 += 4;
                pixel1 += 4;
            }
        }
        return percentage / pixels;
    }
    return 0.0;
}*/


    extern inline double getColorPercentage(const uint8_t *pixel,const uint8_t *pixel2) {
    //pixel 1 is 255, 255, 255
    //pixel 2 is 0, 0, 0
    //match is 0

    //pixel 1 and 2 is 255, 255, 255
    //match is 1.0
    const double scale = 1.0 / (255.0 * 255.0 * 255.0); // compile-time constant
    int m0 = 255 - abs(pixel[0] - pixel2[0]); // NB: use std::abs rather than fabs
    int m1 = 255 - abs(pixel[1] - pixel2[1]); // and keep all of this part
    int m2 = 255 - abs(pixel[2] - pixel2[2]); // in the integer domain
    int m = m0 * m1 * m2;
    return (double)m * scale;
}

inline bool colorInPercentage(const uint8_t *pixel,const uint8_t *pixel2, double percentage) {
    double r = (255-abs(pixel[2] - pixel2[2])) / 255.0;
    if (r < percentage) return false;
	double g = (255-abs(pixel[1] - pixel2[1])) / 255.0 * r;
    if (g < percentage) return false;
	double b = (255-abs(pixel[0] - pixel2[0])) / 255.0 * g;
    if (b < percentage) return false;
    return true;
}



extern inline void normalizePoint(int &x, int &y, int length) {
    double h = hypot(x, y);
    if(length != 0 && h != 0){
        x = (int)( x * (length/h) );
        y = (int)(y * (length/h));
    }
}

extern inline bool detectImageAtPixel(const uint8_t *pixel, int x, int y, int width, int height, ImageData image, int tolerance) {
    if (isColor2(pixel, image.imageData, tolerance) || image.imageData[3] == 0) {
        if (width - x > image.imageWidth &&
            height - y > image.imageHeight) {
            uint8_t *pixel2 = image.imageData;
        for (int y1 = 0; y1 < image.imageHeight; y1++) {
            const uint8_t *pixel1 = pixel + (y1 * width)*4;
            for (int x1 = 0; x1 < image.imageWidth; x1++) {
                if (!isColor2(pixel1, pixel2, tolerance) && pixel2[3] > 0) {
                    return false;
                }
                pixel2 += 4;
                pixel1 += 4;
            }
        }
        return true;
    }
}
return false;
}

extern inline bool detectImageAtPixelPercentage(const uint8_t *pixel, int x, int y, int width, int height, ImageData image, double percentage) {
    if (getColorPercentage(pixel, image.imageData) >= percentage || image.imageData[3] == 0) {
        if (width - x > image.imageWidth &&
            height - y > image.imageHeight) {
            uint8_t *pixel2 = image.imageData;
        for (int y1 = 0; y1 < image.imageHeight; y1++) {
            const uint8_t *pixel1 = pixel + (y1 * width)*4;
            for (int x1 = 0; x1 < image.imageWidth; x1++) {
                if (getColorPercentage(pixel1, pixel2) < percentage && pixel2[3] > 0) {
                    return false;
                }
                pixel2 += 4;
                pixel1 += 4;
            }
        }
        return true;
    }
}
return false;
}

//Uses insane CPU for whatever reason
extern inline Position makePosition(int x, int y) {
    Position p;
    p.x = x;
    p.y = y;
    return p;
}
extern int getRandomInteger(int minimum, int maximum) {
	static bool randomSeeded = false;
	if (!randomSeeded) {
		srand((unsigned)time(NULL));
		randomSeeded = true;
	}
	return rand() / (RAND_MAX + 1) * (maximum - minimum)+ minimum;
    //return arc4random_uniform((maximum - minimum) + 1) + minimum;
}

extern Minion* makeMinionBar( Position topLeft,  Position bottomLeft,  Position topRight,  Position bottomRight, double health) {
    Minion* mb = new Minion();
    mb->topLeft = topLeft; mb->bottomLeft = bottomLeft; mb->topRight = topRight; mb->bottomRight = bottomRight;
    mb->health = health;
    return mb;
}

extern ImageData makeImageData(uint8_t * data, int width, int height) {
    ImageData imageData;
    imageData.imageData = data;
    imageData.imageByteLength = width*height*4;
    imageData.imageWidth = width;
    imageData.imageHeight = height;
    return imageData;
}
/*
extern ImageData makeImageDataFrom(string* path) {
    NSImage *image = [[NSImage alloc] initWithContentsOfFile:path];
    NSBitmapImageRep* raw_img = [NSBitmapImageRep imageRepWithData:[image TIFFRepresentation]];
    uint8_t* data = (uint8_t*) calloc (image.size.width* image.size.height*4,sizeof(uint8_t));
    uint8_t* dataPointer = data;
    uint8_t* originalData = [raw_img bitmapData];
    for (int i = 0; i < image.size.width * image.size.height; i++) {
        dataPointer[0] = originalData[2];
        dataPointer[1] = originalData[1];
        dataPointer[2] = originalData[0];
        dataPointer[3] = originalData[3];
        dataPointer += 4;
        originalData += 4;
    }
    ImageData imageData;
    imageData.imageData = data;
    imageData.imageByteLength = image.size.width* image.size.height*4;
    imageData.imageWidth = image.size.width;
    imageData.imageHeight = image.size.height;
    return imageData;
}*/

    extern bool isColor2(const uint8_t *pixel, const uint8_t *pixel2, int tolerance) {
        if (abs(pixel[0] - pixel2[0]) > tolerance) return false;
        if (abs(pixel[1] - pixel2[1]) > tolerance) return false;
        if (abs(pixel[2] - pixel2[2]) > tolerance) return false;
        return true;
    }

    extern bool isColor3(const uint8_t *pixel, unsigned char r, unsigned char g, unsigned char b) {
        if (pixel[0] != b) return false;
        if (pixel[1] != g) return false;
        if (pixel[2] != r) return false;
        return true;
    }

    extern bool isColor(const uint8_t *pixel, unsigned char r, unsigned char g, unsigned char b, int tolerance) {
        if (abs(pixel[0] - b) > tolerance) return false;
        if (abs(pixel[1] - g) > tolerance) return false;
        if (abs(pixel[2] - r) > tolerance) return false;
        return true;
    }

    extern bool isPixelColor( Pixel pixel, unsigned char r, unsigned char g, unsigned char b, int tolerance) {
        if (abs(pixel.r - r) > tolerance) return false;
        if (abs(pixel.g - g) > tolerance) return false;
        if (abs(pixel.b - b) > tolerance) return false;
        return true;
    }

    extern bool isPixelPreciseColor( Pixel pixel, unsigned char r, unsigned char g, unsigned char b) {
        if (pixel.r != r) return false;
        if (pixel.g != g) return false;
        if (pixel.b != b) return false;
        return true;
    }
    extern Pixel getPixel(struct ImageData imageData, int x, int y) {
        uint8_t *pixel = imageData.imageData + (y * imageData.imageWidth + x)*4;
    //int position = (y * imageData.imageWidth + x) * 4;
        Pixel p;
        if ((unsigned)((y * imageData.imageWidth + x) * 4+3) < imageData.imageByteLength) {
        //p.r = imageData.imageData[position + 2];
        //p.g = imageData.imageData[position + 1];
        //p.b = imageData.imageData[position + 0];
            p.r = pixel[2];
            p.g = pixel[1];
            p.b = pixel[0];
            p.exist = true;
        } else {
            p.exist = false;
        }
        return p;
    }

    extern uint8_t* getPixel2(struct ImageData imageData, int x, int y) {
        return imageData.imageData + (y * imageData.imageWidth + x)*4;
    }

    extern uint8_t* getPixel3(uint8_t *baseAddress, int x, int y, int width) {
        return baseAddress + (y * width + x)*4;
    }


    extern void setPixel( ImageData imageData, int x, int y, int r, int g, int b) {
        uint8_t *pixel = imageData.imageData + (y * imageData.imageWidth + x)*4;
        if ((unsigned)((y * imageData.imageWidth + x) * 4+3) < imageData.imageByteLength) {
            pixel[2] = r;
            pixel[1] = g;
            pixel[0] = b;
        }
    }

    extern void drawRect( ImageData imageData, int left, int top, int width, int height, int r, int g, int b) {
    //Top and bottom
        for (int i = left; i < left+width; i++) {
            setPixel(imageData, i, top, r, g, b);
            setPixel(imageData, i, top+height, r, g, b);
        }
    //Left and right
        for (int i = top+1; i < top+height-1; i++) {
            setPixel(imageData, left, i, r, g, b);
            setPixel(imageData, left+width, i, r, g, b);
        }
    }
/*
extern void MyLog(string *format, ...) {
    va_list args;
    va_start(args, format);
    string *formattedString = [[string alloc] initWithFormat: format
                                                       arguments: args];
    va_end(args);
    [[NSFileHandle fileHandleWithStandardOutput] writeData: [formattedString dataUsingEncoding: NSNEXTSTEPStringEncoding]];
     //[formattedString release];
}*/

#endif /* defined(__Fluffy_Pug__Utility__) */
