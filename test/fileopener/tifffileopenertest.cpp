#include "gtest/gtest.h"
#include "FileOpener/tifffileopener.h"
#include "mocks/mock_ILogger.h"

using namespace testing;

//*****************************************************************************
TEST(TiffFileOpenerTest, ShouldReturnNullWhenOpeningNotExistingFile)
//*****************************************************************************
{
	StrictMock<MockLogger> mockLogger;
	TiffFileOpener tiffFileOpener(mockLogger);
	EXPECT_CALL(mockLogger, Log(_));
	RasterImagePtr pImage = tiffFileOpener.OpenFile("any_path_that_should_not_exist");
	EXPECT_EQ(nullptr, pImage);
}

