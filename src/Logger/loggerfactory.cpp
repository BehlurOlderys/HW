/*
 * loggerfactory.cpp
 *
 *  Created on: 22 Nov 2016
 *      Author: Bartek
 */

#include "loggerfactory.h"

#include <iostream>

#include "stdoutlogger.h"
#include "filelogger.h"

//*****************************************************************************
LoggerFactory::LoggerFactory()
//*****************************************************************************
{}

//*****************************************************************************
ILoggerPtr LoggerFactory::GetLogger(const std::string& type)
//*****************************************************************************
{
	std::cout << "LoggerFactory::GetLogger:" << std::endl;
	if (type == "stdout")
	{
		std::cout << "Creating stdout logger!" << std::endl;
		return ILoggerPtr(new StdOutLogger());
	}
	else if(type == "file")
	{
		std::string fileLoggerPath = "filelogger.log";
		std::cout << "Creating file logger! File name = "<< fileLoggerPath << std::endl;
		return ILoggerPtr(new FileLogger(fileLoggerPath));
	}
	return ILoggerPtr(new NullLogger());
}
