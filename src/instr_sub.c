#include "common.h"
#include "translate.h"
#include "allinstr.h"
void trans_sub(char *mode, char *argus[], char *suffix)
{
  Log("sub worker");
  if (!strcmp(mode, "rr"))
  {
    trans_sub_rr(argus[0],argus[1]);
  }
  else if(!strcmp(mode, "ir"))
  {
  	trans_sub_ir(argus[0],argus[1]);
  }
  else if(!strcmp(mode, "mr"))
  {
  	trans_sub_mr(argus[0],argus[1],get_size_by_suf_x86(suffix[0]));
  }
   else if(!strcmp(mode, "im"))
  {
  	trans_sub_im(argus[0],argus[1],get_size_by_suf_x86(suffix[0]));
  }
  else if (!strcmp(mode,"rm"))
  {
  	trans_sub_rm(argus[0],argus[1],get_size_by_suf_x86(suffix[0]));
  }
  else 
  {
  	TODO();
  }
  
}
void trans_sub_rr(char * reg1,char * reg2)
{
	 int id1 = get_reg_index(reg1);
	 int id2 = get_reg_index(reg2);
	 tar_sub(mips_regs_name[id2],mips_regs_name[id2],mips_regs_name[id1]);
}
void trans_sub_ir(char * imm,char * reg)
{
	int num;
	char **temp1,temp2[20];
	num=strtol(imm,temp1, 0); 
	num=-num;
	sprintf(temp2,"%d",num);
	tar_movi2r("$t8",temp2);
	int idx = get_reg_index(reg);
	tar_add(mips_regs_name[idx],mips_regs_name[idx],"$t8");
}
void trans_sub_mr(char * addr,char * reg, int size)
{
	char mips_addr_src[5];
	tar_getaddr(addr,mips_addr_src);
	tar_load("$t8", "0", mips_addr_src, size);
	int idx = get_reg_index(reg);
	tar_sub(mips_regs_name[idx],mips_regs_name[idx],"$t8");
}
void trans_sub_im(char * imm,char * addr, int size)
{
	tar_movi2r("$t8",imm);
	char mips_addr_src[5];
	tar_getaddr(addr,mips_addr_src);
	tar_load("$t4", "0", mips_addr_src, size);
	tar_sub("$t8","$t4","$t8");
	tar_store("$t8", "0", mips_addr_src, size);
}
void trans_sub_rm(char * reg,char * addr, int size)
{
	char mips_addr_src[5];
	tar_getaddr(addr,mips_addr_src);
	tar_load("$t8", "0", mips_addr_src, size);
	int idx = get_reg_index(reg);
	tar_sub("$t8","$t8",mips_regs_name[idx]);
	tar_store("$t8", "0", mips_addr_src, size);
}
















