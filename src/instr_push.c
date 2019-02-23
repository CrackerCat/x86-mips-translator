#include "common.h"
#include "translate.h"
#include "allinstr.h"

void trans_push(char *mode, char *argus[], char *suffix)
{
  Log("push worker");
  if (!strcmp(mode, "r"))
  {
    trans_push_r(argus[0]);
  }
  else if (!strcmp(mode, "i"))
  {
    trans_push_i(argus[0]);
  }
  else if (!strcmp(mode, "m"))
  	{
  		trans_push_m(argus[0], get_size_by_suf_x86(suffix[0]));
  	}
  else
  	{
  		TODO();
  	}
}
void trans_push_i(char *imm)
{
	 tar_addi("$sp", "$sp", "-4");
	 tar_movi2r("$t8",imm);
	 tar_store("$t8", "0", "$sp",4);
}

void trans_push_r(char *reg)
{
  int idx = get_reg_index(reg);
  //fprintf(fp_out, "  addi $sp,$sp,-4\n");
  //fprintf(fp_out, "  sw %s,$sp\n", mips_regs_name[idx]);
  tar_addi("$sp", "$sp", "-4");
  tar_store(mips_regs_name[idx], "0", "$sp",4);
}
void trans_push_m(char *addr,int size)
{
	tar_addi("$sp", "$sp", "-4");
	char mips_addr_dest[5];
	tar_getaddr(addr, mips_addr_dest);
	tar_load("$t8", "0", mips_addr_dest, size);
	tar_store("$t8", "0", "$sp",4);
}


