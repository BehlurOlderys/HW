// Copyright Bart³omiej Miko³aj Hnatio 2016
#ifndef RASTERIMAGE_RASTERIMAGE_H_
#define RASTERIMAGE_RASTERIMAGE_H_

#include <cstring>
#include <vector>
#include <boost/shared_ptr.hpp>
#include "common.h"
#include <iostream>

typedef unsigned int uint32;


u32 GetRedFromPixel(const u32 pixel);
u32 GetGreenFromPixel(const u32 pixel);
u32 GetBlueFromPixel(const u32 pixel);
u32 GetLumFromPixel(const u32 pixel);
u32 CombineRGBToPixel(const u32 red, const u32 green, const u32 blue);

//*****************************************************************************
struct RasterImage
{
	RasterImage() :
		Raster(),
		Width(0),
		Height(0),
		DepthPerChannel(0),
		ChannelsPerPixel(0),
		Photometric(0){}

	//*****************************************************************************
	virtual ~RasterImage()
	//*****************************************************************************
	{
		delete[] Raster;
	}

	//*****************************************************************************
	u32 GetPixelValue(const i32 x, const i32 y) const
	//*****************************************************************************
	{
		static const i32 minX = 0;
		static const i32 minY = 0;
		static const i32 maxX = Width - 1;
		static const i32 maxY = Height - 1;

		const i32 xx = std::min(std::max(x, minX), maxX);
		const i32 yy = std::min(std::max(y, minY), maxY);
		return Raster[xx + yy*Width];
	}

	//*****************************************************************************
	uint32 GetPixelNumber()
	//*****************************************************************************
	{
		return uint32(Width*Height);
	}
	uint32 GetRPixel(const u32 index){ return GetRedFromPixel  (Raster[index]); }
	uint32 GetGPixel(const u32 index){ return GetGreenFromPixel(Raster[index]); }
	uint32 GetBPixel(const u32 index){ return GetBlueFromPixel (Raster[index]); }
	uint32 GetLum	(const u32 index){ return GetLumFromPixel  (Raster[index]); }

	u32 GetMaxValue();

	//*****************************************************************************
	void CopySizeOnlyFrom(const boost::shared_ptr<RasterImage> pImage)
	//*****************************************************************************
	{
		Raster = new uint32[pImage->GetPixelNumber()];
		Width = pImage->Width;
		Height = pImage->Height;
		std::memset(Raster, 0, pImage->GetPixelNumber()* sizeof(uint32));
	}
	uint32* Raster;
	uint32  Width;
	uint32  Height;
	uint32  DepthPerChannel;
	uint32  ChannelsPerPixel;
	uint32  Photometric;
};

typedef boost::shared_ptr<RasterImage> RasterImagePtr;

RasterImagePtr ConvertToGreyscale(const RasterImagePtr pImage);

#endif // RASTERIMAGE_RASTERIMAGE_H_ 
