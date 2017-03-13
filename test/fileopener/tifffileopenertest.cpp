#include "gtest/gtest.h"
#include "tiff.h"
#include "FileOpener/tifffileopener.h"
#include "mocks/mock_ILogger.h"

using namespace testing;

const u32 DEFAULT_BACKGROUND_R = 77u;
const u32 DEFAULT_BACKGROUND_G = 88;
const u32 DEFAULT_BACKGROUND_B = 99;

TEST(TEST_SIZES, ints)
{
   EXPECT_EQ(1u, sizeof(byte));
	EXPECT_EQ(4u, sizeof(u32));
	EXPECT_EQ(4u, sizeof(uint32));
	EXPECT_EQ(4u, sizeof(uint32));
}

//*****************************************************************************
class TiffFileOpenerTest : public testing::Test
{
public:
	TiffFileOpenerTest(){}
	//*****************************************************************************
	bool CheckIfBackgroundTestPixel(u32 pixel)
	//*****************************************************************************
	{
      EXPECT_EQ(DEFAULT_BACKGROUND_R, GetRedFromPixel(pixel));
      EXPECT_EQ(DEFAULT_BACKGROUND_G, GetGreenFromPixel(pixel));
      EXPECT_EQ(DEFAULT_BACKGROUND_B, GetBlueFromPixel(pixel));

		return   DEFAULT_BACKGROUND_R == GetRedFromPixel(pixel) &&
				 DEFAULT_BACKGROUND_G == GetGreenFromPixel(pixel) &&
				 DEFAULT_BACKGROUND_B == GetBlueFromPixel(pixel);
	}
};

//*****************************************************************************
TEST_F(TiffFileOpenerTest, ShouldReturnNullWhenOpeningNotExistingFile)
//*****************************************************************************
{
	StrictMock<MockLogger> mockLogger;
	TiffFileOpener tiffFileOpener(mockLogger);
	EXPECT_CALL(mockLogger, Log(_));
	RasterImagePtr pImage = tiffFileOpener.OpenFile("any_path_that_should_not_exist");
	EXPECT_EQ(nullptr, pImage);
}

//*****************************************************************************
TEST_F(TiffFileOpenerTest, ShouldCorrectlyReadDepthAndChannelInfo_8b_BW)
//*****************************************************************************
{
	StrictMock<MockLogger> mockLogger;
	TiffFileOpener tiffFileOpener(mockLogger);
	RasterImagePtr pImage = tiffFileOpener.OpenFile("data/images/8b_BW.tif");
	EXPECT_NE(nullptr, pImage);
	EXPECT_EQ(5092u, pImage->Width);
	EXPECT_EQ(3328u, pImage->Height);
	EXPECT_EQ(1u, pImage->ChannelsPerPixel);
	EXPECT_EQ(8u, pImage->DepthPerChannel);
   EXPECT_EQ(static_cast<uint32>(PHOTOMETRIC_MINISBLACK), pImage->Photometric);
}

//*****************************************************************************
TEST_F(TiffFileOpenerTest, ShouldCorrectlyReadDepthAndChannelInfo_16b_BW)
//*****************************************************************************
{
	StrictMock<MockLogger> mockLogger;
	TiffFileOpener tiffFileOpener(mockLogger);
	RasterImagePtr pImage = tiffFileOpener.OpenFile("data/images/16b_BW.tif");
	EXPECT_NE(nullptr, pImage);
	EXPECT_EQ(5092u, pImage->Width);
	EXPECT_EQ(3328u, pImage->Height);
	EXPECT_EQ(1u, pImage->ChannelsPerPixel);
	EXPECT_EQ(16u, pImage->DepthPerChannel);
	EXPECT_EQ(static_cast<uint32>(PHOTOMETRIC_MINISBLACK), pImage->Photometric);
}

//*****************************************************************************
TEST_F(TiffFileOpenerTest, ShouldCorrectlyReadDepthAndChannelInfo_8b_RGB)
//*****************************************************************************
{
	StrictMock<MockLogger> mockLogger;
	TiffFileOpener tiffFileOpener(mockLogger);
	RasterImagePtr pImage = tiffFileOpener.OpenFile("data/images/8b_RGB.tif");
	EXPECT_NE(nullptr, pImage);
	EXPECT_EQ(5092u, pImage->Width);
	EXPECT_EQ(3328u, pImage->Height);
	EXPECT_EQ(3u, pImage->ChannelsPerPixel);
	EXPECT_EQ(8u, pImage->DepthPerChannel);
	EXPECT_EQ(static_cast<uint32>(PHOTOMETRIC_RGB), pImage->Photometric);
}

//*****************************************************************************
TEST_F(TiffFileOpenerTest, ShouldCorrectlyReadDepthAndChannelInfo_16b_RGB)
//*****************************************************************************
{
	StrictMock<MockLogger> mockLogger;
	TiffFileOpener tiffFileOpener(mockLogger);
	RasterImagePtr pImage = tiffFileOpener.OpenFile("data/images/16b_RGB.tif");
	EXPECT_NE(nullptr, pImage);
	EXPECT_EQ(5092u, pImage->Width);
	EXPECT_EQ(3328u, pImage->Height);
	EXPECT_EQ(3u, pImage->ChannelsPerPixel);
	EXPECT_EQ(16u, pImage->DepthPerChannel);
	EXPECT_EQ(static_cast<uint32>(PHOTOMETRIC_RGB), pImage->Photometric);
}
//*****************************************************************************
TEST_F(TiffFileOpenerTest, DISABLED_ShouldOpenOKTestPicture_BW_16b)
//*****************************************************************************
{
	StrictMock<MockLogger> mockLogger;
	TiffFileOpener tiffFileOpener(mockLogger);
	RasterImagePtr pImage = tiffFileOpener.OpenFile("data/test_BW.tif");
	EXPECT_NE(nullptr, pImage);

	EXPECT_EQ(40u, pImage->Height);
	EXPECT_EQ(36u, pImage->Width);

	u32 pRandomCenter = pImage->GetPixelValue(20, 15);

	for (byte i = 0; i < 40; ++i)
	{
		for (byte j = 0; j < 36; ++j)
		{
			std::cout << pImage->GetPixelValue(j, i) << ' ';
		}
		std::cout << std::endl;
	}

	EXPECT_EQ(5u, pRandomCenter);
	EXPECT_TRUE(CheckIfBackgroundTestPixel(pRandomCenter));
}

//*****************************************************************************
TEST_F(TiffFileOpenerTest, DISABLED_ShouldOpenOKTestPicture_test3)
//*****************************************************************************
{
	StrictMock<MockLogger> mockLogger;
	TiffFileOpener tiffFileOpener(mockLogger);
	EXPECT_CALL(mockLogger, Log(_));
	RasterImagePtr pImage = tiffFileOpener.OpenFile("data/test3.tif");
	EXPECT_NE(nullptr, pImage);

	EXPECT_EQ(40u, pImage->Height);
	EXPECT_EQ(36u, pImage->Width);

	u32 pRandomCenter = pImage->GetPixelValue(20, 15);

	for (byte i = 0; i < 40; ++i)
	{
		for (byte j = 0; j < 36; ++j)
		{
			std::cout << pImage->GetPixelValue(j, i) << ' ';
		}
		std::cout << std::endl;
	}

	EXPECT_EQ(5u, pRandomCenter);
	EXPECT_TRUE(CheckIfBackgroundTestPixel(pRandomCenter));
}

//*****************************************************************************
TEST_F(TiffFileOpenerTest, DISABLED_ShouldOpenOKTestPicture_16b)
//*****************************************************************************
{
	StrictMock<MockLogger> mockLogger;
	TiffFileOpener tiffFileOpener(mockLogger);
	EXPECT_CALL(mockLogger, Log(_));
	RasterImagePtr pImage = tiffFileOpener.OpenFile("data//test_16b.tif");
	EXPECT_NE(nullptr, pImage);

	EXPECT_EQ(7u, pImage->Height);
	EXPECT_EQ(7u, pImage->Width);

	u32 p00 = pImage->GetPixelValue(0, 0);
	EXPECT_TRUE(CheckIfBackgroundTestPixel(p00));
}
