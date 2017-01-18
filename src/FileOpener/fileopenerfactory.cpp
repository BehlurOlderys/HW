/*
 * fileopenerfactory.cpp
 *
 *  Created on: 22 Nov 2016
 *      Author: Bartek
 */

#include "fileopenerfactory.h"
#include "Logger/ilogger.h"
#include "tifffileopener.h"

//*****************************************************************************
FileOpenerFactory::FileOpenerFactory(ILogger& logger) :
	m_Logger(logger)
//*****************************************************************************
{}

//*****************************************************************************
IFileOpenerPtr FileOpenerFactory::GetFileOpener(std::string& type)
//*****************************************************************************
{
	if (type == "tiff")
	{
		return IFileOpenerPtr(new TiffFileOpener(m_Logger));
	}
	return IFileOpenerPtr(new NullFileOpener());
}



