/*
 * tifffileopener.cpp
 *
 *  Created on: 22 Nov 2016
 *      Author: Bartek
 */

#include "tifffileopener.h"

#include <boost/format.hpp>
#include <fstream>
#include <cstring>
#include "tiffio.h"
#include "Logger/ilogger.h"

namespace
{
//*****************************************************************************
bool CheckIfFileExists(const std::string& name)
//*****************************************************************************
{
	std::ifstream f(name.c_str());
	return f.good();
}

} // namespace

//*****************************************************************************
TiffFileOpener::TiffFileOpener(ILogger& logger) :
	m_Logger(logger)
//*****************************************************************************
{}
//*****************************************************************************
RasterImagePtr TiffFileOpener::OpenFile(const std::string& sFileName)
//*****************************************************************************
{
	if (!CheckIfFileExists(sFileName))
	{
		m_Logger.Log((boost::format("Plik o nazwie %s nie istnieje!") % sFileName).str());
		return RasterImagePtr();
	}
	TIFF* tif = TIFFOpen(sFileName.c_str(), "r");
	if (!tif)
	{
		m_Logger.Log((boost::format("Nie udalo sie otworzyc pliku o nazwie %s!") % sFileName).str());
		return RasterImagePtr();
	}

	RasterImagePtr image(new RasterImage());

	TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, &image->Width);
	TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &image->Height);
	TIFFGetField(tif, TIFFTAG_SAMPLESPERPIXEL, &image->ChannelsPerPixel);
	TIFFGetField(tif, TIFFTAG_BITSPERSAMPLE, &image->DepthPerChannel);
   TIFFGetField(tif, TIFFTAG_PHOTOMETRIC, &image->Photometric);
   TIFFGetField(tif, TIFFTAG_SAMPLEFORMAT, &image->SampleFormat);
   TIFFGetField(tif, TIFFTAG_COMPRESSION, &image->Compression);
   TIFFGetField(tif, TIFFTAG_FILLORDER, &image->FillOrder);

   m_Logger.Log((boost::format("Otworzylem plik o nazwie %s!") % sFileName).str());

   m_Logger.Log((boost::format("Parametry: \n %s") % image->ToString()).str());


   int linesize = TIFFScanlineSize(tif);
   u16* buffer = new u16[linesize * image->Height];
   for (u32 i = 0; i < image->Height; i++)
   {
       TIFFReadScanline(tif, (char*)(&buffer[i * linesize]), i, 0);
   }

   m_Logger.Log("Po czytaniu!");

   for (u32 j=0; j < 10; ++j)
   {
      m_Logger.Log((boost::format("%d    %d    %d    %d    %d    %d     %d     %d     %d     %d")
      % u16(buffer[10*j])
      % u16(buffer[10*j+1])
      % u16(buffer[10*j+2])
      % u16(buffer[10*j+3])
      % u16(buffer[10*j+4])
      % u16(buffer[10*j+5])
      % u16(buffer[10*j+6])
      % u16(buffer[10*j+7])
      % u16(buffer[10*j+8])
      % u16(buffer[10*j+9])).str());
   }


//	size_t npixels = image->GetPixelNumber();
//	const uint32 uSizeOfRasterInBytes = uint32(npixels * sizeof (uint32));
//	uint32* raster = (uint32*) _TIFFmalloc(uSizeOfRasterInBytes);
//	if (raster == NULL)
//	{
//		m_Logger.Log("Raster okazal sie nullem!");
//		return RasterImagePtr();
//	}
//	if (TIFFReadRGBAImage(tif,
//						  image->Width,
//						  image->Height,
//						  raster,
//						  0))
//	{
//		m_Logger.Log((boost::format("Plik ma szerokosc = %d, wysokosc = %d") % image->Width % image->Height).str());
//		image->Raster = new uint32[npixels];
//		std::memcpy(image->Raster, raster, uSizeOfRasterInBytes);
//	}
//	_TIFFfree(raster);
//	TIFFClose(tif);
	return image;
}
