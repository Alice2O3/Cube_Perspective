#include "stdafx.h"
#include "Pch.h"

int main(int argc, char *argv[])
{
	Err_Code err_code = Task_main(argc, argv);
	if (err_code != Err_Code::NO_ERR) {
		return 1;
	}
	return 0;
}