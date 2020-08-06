Name: Tyler Andrews
ID: TJA0023, 903807885
Due Date: 8/3/2020
Proffesor: Dr. Xiao Qin

COMP 4300 Computer Architecture
Project 3: Pipelined Datapath with Interlocks and Forwarding

Copy and Pase the following to run my code:

gcc pipeSim.c -o pipe_sim
./pipe_sim


To change the input, open pipeSim.C and edit the value on line 196.


Load File:

The machine uses the load_file function (basically the same as my project 1 and 2)
This function anaylzes the assembly file and sets the values for task, operator, and case number that will be used in the main function
For each task a case number will be assigned so that I can use a switch in the main function to easily iterate.
    addi = 1
    b = 2
    beqz = 3
    bge = 4
    bne = 5
    la = 6
    lb = 7
    li = 8
    subi = 9
    syscall = 10
    nop = 11

Main Function:

Fetch Stage: Lines 203 - 212

Decode Stage: Lines 224 - 319

Execute Stage: Lines 340 - 378


Values for C, IC, Speedup, and NOPS
ASSUMING 5 CYCLES PER INSTRUCTION AS STATED IN QUESTION 1 IN PROJECT 3 FAQS

Lab3a.c 
C: 30
IC: 12
Speedup: 3.2
NOPS: 6

Lab3c.s
C: 75
IC: 16
Speedup: 1.707
NOPS: 1


There are detailed comments throughout both files that explain my process.