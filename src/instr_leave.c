#include "common.h"
#include "translate.h"
#include "allinstr.h"

void trans_leave(char *mode, char *argus[], char *suffix)
{
	tar_movr2r("$sp","$s5");// mov ebp,esp
	tar_load("$s5", "0", "$sp",4);
	tar_addi("$sp", "$sp", "4");//pop ebp
}

