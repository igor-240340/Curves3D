#include <iostream>

#include "Curves.h"

#ifdef _DEBUG
#include "Test.h"
#endif

int main() {
#ifdef _DEBUG
	Test::run_all();
#endif

	return 0;
}