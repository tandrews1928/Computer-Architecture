Name: Tyler Andrews
Due Date: 7/12/2020
Proffesor: Dr. Xiao Qin

COMP 4300 Computer Architecture
Project 1: Instruction Set Architectures

Copy and Pase the following to run my code:

gcc stackSim.c -o stack_sim
./stack_sim
gcc accumSim.c -o accum_sim
./accum_sim

Load File:

Both the stack and accummulator machine use the load_file function
This function anaylzes the respective assembly files and sets the values for task, operator, and case number that will be used in the main function
For each task a case number will be assigned so that I can use a switch in the main function to easily iterate.
    PUSH/LOAD = 0
    POP/STO = 1
    ADD = 2
    MUL = 3
    END = 4


Stack Machine:

After loading the souce file the simulator will analyze each task 1 by 1
For each of the following tasks the simulator will perform the following action.
    PUSH x will read the contents of memory at address x and push the value onto the stack.
    POP y will pop one word off the top of the stack and write the value to memory at address y.
    ADD will remove the top two words from the stack, add them, and leave the result on the top of the stack.
    MUL will remove the top two words from the stack, multiply them, and leave the result on the top of the stack.
    END just signals the end of the code.

Accummulator Machine:

After loading the souce file the simulator will analyze each task 1 by 1
For each of the following tasks the simulator will perform the following action.
    LOAD x will read the contents of memory at address x and put the value into the accumulator.
    STO y will write the contents of the accumulator to memory at address y.
    ADD x will read the contents of memory at address x, add the value to the accumulator, and leave the result in the accumulator.
    MULT x will read the contents of memory at address x, multiply the value to the accumulator, and leave the result in the accumulator.
    END just signals the end of the code.