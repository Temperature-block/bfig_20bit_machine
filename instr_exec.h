#ifndef hypomachine
#define hypomachine
#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <pthread.h>
#include <stdlib.h>
Display *dis;
int screen;
Window win;
GC gc;
/*
INSTRCTION SET 
word size 20 bit 
von neuman style  
first 4 bits mnemonic
registers alu op 
reg : { alu 00 | op 01 | a | b}
instructions
0000 ld reg mem
0001 sto reg mem
0010 jmp mem
0011 add 
0100 sub 
0101 xor 
0110 EQ mem
0111 lt mem
1000 gt mem
1001 vaddr
1010 vaddr
1011 vaddr
1100 vaddr


*/




struct eighteen{
     unsigned int eighteen:18;
}eighteen;

typedef struct  vram{
  unsigned int bit:1;
}vmem;

typedef struct inst{
    unsigned int inst:4;
    unsigned int rest:16;
}inst;

typedef struct mem{
    unsigned int cell:20;

}mem;

struct reg{
    unsigned int acu:20;
    unsigned int op:20;

} regs;

 mem cells[1048576]= {{ 0 }};

vmem vcell[307200]= {{ 0 }};

void* render(void* arg)
{
     
     //fflush(stdout);
     unsigned long black,white;
     dis=XOpenDisplay((char *)0);
     black=BlackPixel(dis,screen),	/* get color black */
	white=WhitePixel(dis, screen);
     win=XCreateSimpleWindow(dis,DefaultRootWindow(dis),0,0,640, 480, 5, white, black);
     XSetStandardProperties(dis,win,"VGA","VGA!",None,NULL,0,NULL);
     XSelectInput(dis, win, ExposureMask|ButtonPressMask|KeyPressMask);
     gc=XCreateGC(dis, win, 0,0);        
     XSetBackground(dis,gc,black);
	XSetForeground(dis,gc,white);
     XMapRaised(dis, win);
     int val = -1;
     while(1){
          for(int i = 0;i<480;i++){
               
                    for(int j = 0;j<640;j++){
                         val = val + 1;
                         if(vcell[val].bit == 1){
                              //printf("%d x %d\n",j,i);
                              //int XDrawPoint(Display *display, Drawable d, GC gc, int x, int y); 
                              XDrawPoint(dis,win,gc,j,i);
                              
                         }
                         else{
                             // XDrawPoint(dis,win,gc,j,i);
                              //printf("%d x %d\n",j,i);
                              //XDrawPoint(dis,win,gc,j,i);
                         }
                         
                         //XFlush(dis);
          }
     }
     
     val = -1;
     }


}

void exec(){
     pthread_t ptid;
     pthread_create(&ptid, NULL, &render, NULL);

     unsigned int PC = 0;
     regs.acu =0;
     regs.op =0;
     unsigned int addr;
     int reg;
     inst curinst;
     while(PC< 1048576){
     if(PC == 1048576){
          PC=0;
          continue;
     }
     else{
          curinst.inst = cells[PC].cell >> 16;
          //printf("%u\n",curinst.inst);
          //fflush(stdout);
          curinst.rest = (cells[PC].cell << 4)>>4 ;
          switch(curinst.inst ){
               case 0:
                    reg = curinst.rest >> 14 ;
                    if(reg == 0){
                         regs.acu = (unsigned int) cells[(curinst.rest<<2)>>2].cell;
                    }
                    else{
                         regs.op = (unsigned int) cells[(curinst.rest<<2)>>2].cell;
                    }
                    break;
                    

               case 1:
                    reg = curinst.rest>> 14 ;
                    if(reg == 0){
                    cells[(curinst.rest<<2)>>2].cell  = (unsigned int) regs.acu ;
                    }
                    else{
                    cells[(curinst.rest<<2)>>2].cell  = (unsigned int) regs.op ;
                    }
                    break;
               case 2:
                    PC = curinst.rest;
                    break;
               case 3:
                    regs.acu = regs.acu + regs.op;
                    break;
               case 4:
                    regs.acu = regs.acu - regs.op;
                    break;  
               case 5:
                    regs.acu = regs.acu ^ regs.op;
                    break;
               case 6:
                    if( regs.acu == regs.op ){
                         PC = curinst.rest;
                    }
                    break;
               case 7:
                    if( regs.acu < regs.op ){
                         PC = curinst.rest;
                    }
                    break;
               case 8:
                    if( regs.acu > regs.op ){
                         PC = curinst.rest;
                    }
                    break;
               case 9:
                     addr = (cells[PC].cell<<2)>>2;
                     eighteen.eighteen = addr;
                     vcell[eighteen.eighteen].bit = vcell[eighteen.eighteen].bit^1;
                    break;
               case 10:
                     addr = (cells[PC].cell<<2)>>2;
                     eighteen.eighteen = addr;
                     vcell[eighteen.eighteen].bit = vcell[eighteen.eighteen].bit^1;

                    break;  
               case 11:
                     addr = (cells[PC].cell<<2)>>2;
                     eighteen.eighteen = addr;
                     vcell[eighteen.eighteen].bit = vcell[eighteen.eighteen].bit^1;

                    
                    break;     
               case 12:
                     addr = (cells[PC].cell<<2)>>2;
                     eighteen.eighteen = addr;
                     vcell[eighteen.eighteen].bit = vcell[eighteen.eighteen].bit^1;

                    break; 
               case 13:
               while(1){

               }
               }                                                    
          } PC =PC +1;
        }
     }

#endif