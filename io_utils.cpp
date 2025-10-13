#include "io_utils.h"
#include <cstdlib>
#include<iostream>

void setup_io() {
#ifdef _MSC_VER
	system("chcp 65001 > nul");
#endif
	std::ios_base::sync_with_stdio(false);
}