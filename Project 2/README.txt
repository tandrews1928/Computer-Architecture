Name: Tyler Andrews
ID: TJA0023, 903807885
Due Date: 7/26/2020
Proffesor: Dr. Xiao Qin

COMP 4300 Computer Architecture
Project 2: Single vs Multi-cycle Machines

Copy and Pase the following to run my code:

gcc gprSim.c -o gpr_sim
./gpr_sim


To change the input, open gprSim.C and edit the value on line 130.


Load File:

The machine uses the load_file function (basically the same as my project 1)
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

palindrome.s:

My palindrome.s file is slightly different than the lab2.s file we were provided.
Instead of having a placeholder for my loop, I solely use b to loop.
In my .data section I do not read in a string, instead I define the strings in my gprSim.s file





There are detailed comments throughout both files that explain my process.