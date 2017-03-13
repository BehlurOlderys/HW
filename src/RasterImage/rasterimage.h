// Copyright Bart³omiej Miko³aj Hnatio 2016
#ifndef RASTERIMAGE_RASTERIMAGE_H_
#define RASTERIMAGE_RASTERIMAGE_H_

#include <cstring>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/format.hpp>
#include "common.h"
#include <iostream>
#include "tiffutils.h"

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
		Photometric(0),
		SampleFormat(0){}

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
	u32 GetPixelNumber()
	//*****************************************************************************
	{
		return u32(Width*Height);
	}
	u32 GetRPixel(const u32 index){ return GetRedFromPixel  (Raster[index]); }
	u32 GetGPixel(const u32 index){ return GetGreenFromPixel(Raster[index]); }
	u32 GetBPixel(const u32 index){ return GetBlueFromPixel (Raster[index]); }
	u32 GetLum	(const u32 index){ return GetLumFromPixel  (Raster[index]); }

	u32 GetMaxValue();

	//*****************************************************************************
	void CopySizeOnlyFrom(const boost::shared_ptr<RasterImage> pImage)
	//*****************************************************************************
	{
		Raster = new u32[pImage->GetPixelNumber()];
		Width = pImage->Width;
		Height = pImage->Height;
		std::memset(Raster, 0, pImage->GetPixelNumber()* sizeof(u32));
	}

   //*****************************************************************************
   std::string ToString()
   //*****************************************************************************
   {
      return (boost::format("Width = %d\n"
            "Height  = %d\n"
            "Depth per channel = %d\n"
            "Channels per pixel = %d\n"
            "Photometric interpretation = %d (%s)\n"
            "Sample format = %d (%s)")
      % Width
      % Height
      % DepthPerChannel
      % ChannelsPerPixel
      % Photometric
      % PhotometricToString(Photometric)
      % SampleFormat
      % SampleFormatToString(SampleFormat)).str();
   }

	u32* Raster;
	u32  Width;
	u32  Height;
	u32  DepthPerChannel;
	u32  ChannelsPerPixel;
	u32  Photometric;
	u32  SampleFormat;
};

typedef boost::shared_ptr<RasterImage> RasterImagePtr;

RasterImagePtr ConvertToGreyscale(const RasterImagePtr pImage);

#endif // RASTERIMAGE_RASTERIMAGE_H_ 
