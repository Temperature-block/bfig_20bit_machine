from PIL import Image
import sys
image = Image.open(sys.argv[1])
from numpy import asarray
data = asarray(image)
#print(data)
funcs = ['''vmem0({0},{1});''',
'''vmem1({0},{1});''',
'''vmem2({0},{1});''',
'''vmem3({0},{1});''']
print('#include "./pasm20.h"')
print('#include "./instr_exec.h"')
main = "void main(){{    {0}  }}"
curno =-1
a = ""
for i in range(0,480):
    for j in range(0,640):
        curno = curno + 1
        if(curno>>16==0):
            if(data[i][j]==True):
                a=a+funcs[0].format(curno,curno)
        elif(curno>>16==1):
            if(data[i][j]==True):
                a=a+funcs[1].format(curno,curno)
        elif(curno>>16==2):
            if(data[i][j]==True):
                a=a+funcs[2].format(curno,curno)
        elif(curno>>16==3):
            if(data[i][j]==True):
                a=a+funcs[3].format(curno,curno)
curno = curno +1
a=a+'''

jmp({0},{1});
m();
'''.format(curno,0)
print(main.format(a))
