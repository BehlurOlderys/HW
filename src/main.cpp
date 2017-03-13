/*
 * main.cpp
 *
 *  Created on: 22 Dec 2016
 *      Author: Bartek
 */

#include <iostream>
#include <boost/format.hpp>
#include "Logger/stdoutlogger.h"
#include "FileOpener/tifffileopener.h"
#include "RasterImage/rasterimage.h"


//*****************************************************************************
int main(int argc, char *argv[])
//*****************************************************************************
{
   std::cout << "HW Astrometry v1.0" << std::endl;

   StdOutLogger logger;
   TiffFileOpener fileOpener(logger);

   logger.Log((boost::format("Argument count = %d") % argc).str());

   if (argc < 2)
   {
      return -1;
   }

   std::string sFileName(argv[1]);

   logger.Log((boost::format("Argument value = %s") % sFileName).str());

   RasterImagePtr pImage = fileOpener.OpenFile(sFileName);

   return 0;
}
