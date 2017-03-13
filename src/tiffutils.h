#ifndef SRC_FILEOPENER_TIFFUTILS_H_
#define SRC_FILEOPENER_TIFFUTILS_H_

#include <string>
#include "common.h"

std::string PhotometricToString(const u32 photometric);
std::string SampleFormatToString(const u32 sampleFormat);

#endif /* SRC_FILEOPENER_TIFFUTILS_H_ */
