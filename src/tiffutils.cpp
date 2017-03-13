/*
 * tiffutils.cpp
 *
 *  Created on: 13 Mar 2017
 *      Author: Bartek
 */

#include "tiffutils.h"
#include "tiff.h"
#include <boost/format.hpp>

//*****************************************************************************
std::string PhotometricToString(const u32 photometric)
//*****************************************************************************
{
   switch (photometric)
   {
   case PHOTOMETRIC_MINISWHITE:
      return "PHOTOMETRIC_MINISWHITE";
   case PHOTOMETRIC_MINISBLACK :
      return "PHOTOMETRIC_MINISBLACK";
   case PHOTOMETRIC_RGB :
      return "PHOTOMETRIC_RGB";
   case PHOTOMETRIC_PALETTE:
      return "PHOTOMETRIC_PALETTE";
   default:
      return "OTHER INTERPRETATION";
   }
}

//*****************************************************************************
std::string SampleFormatToString(const u32 sampleFormat)
//*****************************************************************************
{
   switch (sampleFormat)
   {
   case 0:
      return "ZERO FORMAT";
   case SAMPLEFORMAT_UINT :
      return "SAMPLEFORMAT_UINT";
   case SAMPLEFORMAT_INT :
      return "SAMPLEFORMAT_INT";
   case SAMPLEFORMAT_IEEEFP  :
      return "SAMPLEFORMAT_IEEEFP";
   case SAMPLEFORMAT_VOID :
      return "SAMPLEFORMAT_VOID";
   default:
      return "OTHER SAMPLE FORMAT";
   }
}
