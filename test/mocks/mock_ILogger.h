/*
 * mock_ILogger.h
 *
 *  Created on: 18 Jan 2017
 *      Author: Bartek
 */

#ifndef TEST_MOCKS_MOCK_ILOGGER_H_
#define TEST_MOCKS_MOCK_ILOGGER_H_

#include "gmock/gmock.h"
#include "Logger/ilogger.h"

class MockLogger : public ILogger
{
public:
	MOCK_METHOD1(Log, void(const std::string&));
};

#endif /* TEST_MOCKS_MOCK_ILOGGER_H_ */
