#ifndef pasm20
#define pasm20

#include "./instr_exec.h"
extern mem cells[1048576];

void ld(unsigned int reg,unsigned int add,unsigned int loc){
    cells[add].cell=((0<<2|reg)<<14)|loc;
}
void sto(unsigned int reg,unsigned int add,unsigned int loc){
    cells[add].cell=((0b0001<<2|reg)<<14)|loc;
}
void jmp(unsigned int add,unsigned int loc){
    cells[add].cell=(0b0010<<16)|loc;
}
void add(unsigned int add){
    cells[add].cell=(0b0011<<16)|0;
}
void sub(unsigned int add){
    cells[add].cell=(0b0100<<16)|0;
}
void xore(unsigned int add){
    cells[add].cell=(0b0101<<16)|0;
}
void EQ(unsigned int add,unsigned int loc){
    cells[add].cell=(0b0110<<16)|loc;
}
void lt(unsigned int add,unsigned int loc){
    cells[add].cell=(0b0111<<16)|loc;
}
void gt(unsigned int add,unsigned int loc){
    cells[add].cell=(0b1000<<16)|loc;
}
void vmem0(unsigned int add,unsigned int loc){
    cells[add].cell=(0b11<<18)|(loc);
}
void vmem1(unsigned int add,unsigned int loc){
    cells[add].cell=(0b10<<18)|(loc);
}
void vmem2(unsigned int add,unsigned int loc){
    cells[add].cell=(0b10<<18)|(loc);
}
void vmem3(unsigned int add,unsigned int loc){
    cells[add].cell=(0b10<<18)|(loc);
}
void defnum(unsigned int add,unsigned int num){
    cells[add].cell=num;
}
void HLT(unsigned int add){
    cells[add].cell=0b11010000000000000000;
}

void m(){
    exec();
}
#endif
