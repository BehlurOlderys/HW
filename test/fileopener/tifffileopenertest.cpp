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

//*****************************************************************************
TEST(TiffFileOpenerTest, ShouldOpenOKTestPicture_8b)
//*****************************************************************************
{
	StrictMock<MockLogger> mockLogger;
	TiffFileOpener tiffFileOpener(mockLogger);
	EXPECT_CALL(mockLogger, Log(_));
	RasterImagePtr pImage = tiffFileOpener.OpenFile("data//test_8b.tif");
	EXPECT_NE(nullptr, pImage);

	EXPECT_EQ(7u, pImage->Height);
	EXPECT_EQ(7u, pImage->Width);
}

//*****************************************************************************
TEST(TiffFileOpenerTest, ShouldOpenOKTestPicture_16b)
//*****************************************************************************
{
	StrictMock<MockLogger> mockLogger;
	TiffFileOpener tiffFileOpener(mockLogger);
	EXPECT_CALL(mockLogger, Log(_));
	RasterImagePtr pImage = tiffFileOpener.OpenFile("data//test_16b.tif");
	EXPECT_NE(nullptr, pImage);

	EXPECT_EQ(7u, pImage->Height);
	EXPECT_EQ(7u, pImage->Width);
}
