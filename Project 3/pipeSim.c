/**
Project 3
Created by Tyler Andrews
Due: 7/29/2020
**/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

enum {text, data}; //Got this from https://www.studytonight.com/c/typedef.php and also the lecture

typedef char string[300]; //Got this from https://www.studytonight.com/c/typedef.php and also the lecture

typedef struct text { //Got this from https://www.studytonight.com/c/typedef.php and also the lecture
	int location;
	string operator;
	string task;
	int case_number ;

} Text;

typedef struct data { //Got this from https://www.studytonight.com/c/typedef.php and also the lecture
	int location;
	string operator;
	int content;
} Data;
 
typedef struct memory { //Got this from https://www.studytonight.com/c/typedef.php and also the lecture
	Text text_segment[200];
	Data data_segment[200];
} Memory;

//need to change

typedef struct if_id { //From Lecture 25-Project 3-3 Data Sturctures for Latches
	int ir;
  string operator;
} if_id;


typedef struct id_exe { //From Lecture 25-Project 3-3 Data Sturctures for Latches
	int op_code;
	int rs;
  int rt;
  int rd;
	int op_A;
  int op_B;
} id_exe;

typedef struct mem_exe { //From Lecture 25-Project 3-3 Data Sturctures for Latches
	int op_code;
	int alu_out;
	int op_B;
	int rd;
} mem_exe;

typedef struct mem_wb { //From Lecture 25-Project 3-3 Data Sturctures for Latches
	int op_code;
	int mdr;
	int op_B;
	int alu_out;
	int rd;
} mem_wb;

//Latches
if_id if_id_old;
if_id if_id_next;
id_exe id_exe_old;
id_exe id_exe_next;
mem_exe mem_exe_old;
mem_exe mem_exe_next;
mem_wb mem_wb_old;
mem_wb mem_wb_next;

Memory memory;


Memory load_file(char file_name[]) { //This function is basically the same from Project 1 and 2
	FILE *assembly_file = fopen(file_name, "r");
	char line_of_text[300];
	char data_or_text;
	Memory memory;
	int t_index = 0;
	int d_index = 0;
	int next_t_index = 0;
	int next_d_index = 0;
  
	while(fgets(line_of_text, 300, assembly_file) != NULL) { //https://www.tutorialspoint.com/c_standard_library/c_function_fgets.htm

		if(line_of_text[0] == '.') { //This means that we are at either .text or .data
		
			if (line_of_text[1] == 't') { //this means that we are at .text
			data_or_text = text;
			}
			else { //this means that we are at .main
			data_or_text = data;
			}
		}

		else {
		
			if(data_or_text == text) {  //Text

				memory.text_segment[t_index].location = next_t_index;

				next_t_index++;

				//Sets the values for task, operator, and case number that will be used in the main function
				//I am setting the different tasks to different case numbers so that I can use a switch in the main fucntion

				sscanf(line_of_text, "%s %[^\n]", memory.text_segment[t_index].task, memory.text_segment[t_index].operator); // https://www.tutorialspoint.com/c_standard_library/c_function_sscanf.htm
							    
				if (strcmp(memory.text_segment[t_index].task, "add") == 0) { //if ADDI is read set the case number to 5
					memory.text_segment[t_index].case_number = 1;
				}
        if (strcmp(memory.text_segment[t_index].task, "addi") == 0) { //if ADDI is read set the case number to 5
					memory.text_segment[t_index].case_number = 1;
				}
				else if (strcmp(memory.text_segment[t_index].task, "b") == 0) { //if B is read set the case number to 6
					memory.text_segment[t_index].case_number = 2;
				}
				else if (strcmp(memory.text_segment[t_index].task, "beqz") == 0) { //if BEQZ is read set the case number to 7
					memory.text_segment[t_index].case_number = 3;
				}
				else if (strcmp(memory.text_segment[t_index].task, "bge") == 0) { //if BGE is read set the case number to 8
					memory.text_segment[t_index].case_number = 4;
				}
				else if (strcmp(memory.text_segment[t_index].task, "bne") == 0) { //if BNE is read set the case number to 9
					memory.text_segment[t_index].case_number = 5;
					}
				else if (strcmp(memory.text_segment[t_index].task, "la") == 0) { //if LA is read set the case number to 10
					memory.text_segment[t_index].case_number = 6;
				}
				else if (strcmp(memory.text_segment[t_index].task, "lb") == 0) { //if LB is read set the case number to 11
					memory.text_segment[t_index].case_number = 7;
				}
				else if (strcmp(memory.text_segment[t_index].task, "li") == 0) { //if LI is read set the case number to 12
					memory.text_segment[t_index].case_number = 8;
				}
				else if (strcmp(memory.text_segment[t_index].task, "subi") == 0) { //if SUBI is read set the case number to 13
					memory.text_segment[t_index].case_number = 9;
				}
				else if (strcmp(memory.text_segment[t_index].task, "syscall") == 0) { //if SYSCALL is read set the case number to 14
					memory.text_segment[t_index].case_number = 10;
				}	
					else if (strcmp(memory.text_segment[t_index].task, "nop") == 0) { //if SYSCALL is read set the case number to 14
					memory.text_segment[t_index].case_number = 11;
				}		


				
				t_index++;
			}
			else { //Data

				memory.data_segment[d_index].location = next_d_index;

				next_d_index++;
				
				sscanf(line_of_text, "%s %d", memory.data_segment[d_index].operator, &memory.data_segment[d_index].content); // https://www.tutorialspoint.com/c_standard_library/c_function_sscanf.htm

				d_index++;
			}
		}

		if (line_of_text[0] == 'E') {
			break;
		}
	}
	fclose(assembly_file);
	return memory;
}

/**
________________________
THE MAIN FUNCTION BELOW
________________________
**/

int main() {

  int registers[32]; //32 general purpose registers
  int c = 0; //number of cycles spent in execution
  int ic = 0; //total number of instructions executed
  int i = 0;
  bool user_mode  = true;

  int nops = 0; //Count for number of NOPS

  int rdest; //specify one of the general-purpose registers ($0 through $31).
  int rsrc1; //specify one of the general-purpose registers ($0 through $31).
  int rsrc2; //specify one of the general-purpose registers ($0 through $31).
  int imm; //denotes a signed immediate (an integer).
  int label; //denotes the address associated with a label in the .text or .data segment.
  int offset; //denotes a signed offset (an immediate in the instruction) which is to be added to the value in the base register

	memory = load_file("lab3c.s"); //this loads in the file lab3c.s, could be changed to where the file is taking as an argument, but I did this for simplicity for the grader
	
	
	while (user_mode) {

		int current_case_number = memory.text_segment[i].case_number;

    //FETCH STAGE

		if_id_old = if_id_next;

    if_id fetch;
    fetch.ir = current_case_number; //Set to current case number from load file
    
    if_id_next = fetch; 
		
		id_exe_old = id_exe_next;
    
    id_exe decode;

    //Initialize Variables
    rdest = 0; 
    rsrc1 = 0;
    rsrc2 = 0;
    imm = 0;
    label = 0;

    decode.op_code = if_id_old.ir;

    switch (decode.op_code) {   //DECODE INSTRUCTIONS
      case 1 : //ADD
        sscanf(if_id_old.operator, "%*c%d %*c%d %d",  &rdest,  &rsrc1, &imm); //https://www.tutorialspoint.com/c_standard_library/c_function_sscanf.htm
        decode.rd = rdest; //set rd
        decode.rs = rsrc1; //set rs
        decode.op_A = registers[rsrc1]; //set op_A
        decode.op_B = imm; //set op_B
        c += 5; //Increment C
        ic++; //Increment IC
        printf("add decoded\n");
        break;

      case 2 : //B
        sscanf(if_id_old.operator, "%d", &label); //https://www.tutorialspoint.com/c_standard_library/c_function_sscanf.htm
        c += 5; //Increment C
        ic++; //Increment IC
        printf("b decoded\n");
        break;

      case 3 : //BEQZ
        sscanf(if_id_old.operator, "%*c%d %d",  &rsrc1, &label); //https://www.tutorialspoint.com/c_standard_library/c_function_sscanf.htm
        decode.rs = rsrc1;
        decode.op_A = registers[rsrc1];
        c += 5; //Increment C
        ic++; //Increment IC
        printf("beqz decoded\n");
        break;

      case 4 : //BGE
        sscanf(if_id_old.operator, "%*c%d %*c%d %d",  &rsrc1,  &rsrc2, &label); //https://www.tutorialspoint.com/c_standard_library/c_function_sscanf.htm
        decode.rs = rsrc1;
        decode.rt = rsrc2;
        decode.op_A = registers[rsrc1];
        decode.op_B = registers[rsrc2];
        c += 5; //Increment C
        ic++; //Increment IC
        printf("bge decoded\n");
        break;

      case 5 : //BNE
        sscanf(if_id_old.operator, "%*c%d %*c%d %d",  &rsrc1,  &rsrc2, &label); //https://www.tutorialspoint.com/c_standard_library/c_function_sscanf.htm
        decode.rs = rsrc1;
        decode.rt = rsrc2;
        decode.op_A = registers[rsrc1];
        decode.op_B = registers[rsrc2];
        c += 5; //Increment C
        ic++; //Increment IC
        printf("bne decoded\n");
        break;

      case 6 : //LA
        sscanf(if_id_old.operator, "%*c%d %d",  &rdest, &label); //https://www.tutorialspoint.com/c_standard_library/c_function_sscanf.htm
        decode.rd =rdest; //Set rd
        decode.rs = label;// set rs
        decode.op_A = memory.data_segment[label].content; //set op A
        c += 5; //Increment C
        ic++; //Increment IC
        printf("la decoded\n");
        break;

      case 7 : //LB
        sscanf(if_id_old.operator, "%*c%d %*c%d",  &rdest, &offset); //https://www.tutorialspoint.com/c_standard_library/c_function_sscanf.htm
        decode.rd =rdest; //set rd
        c += 5; //Increment C
        ic++; //Increment IC
        printf("lb decoded\n");
        break;

      case 8 : //LI
        sscanf(if_id_old.operator, "%*c%d %d",  &rdest, &imm); //https://www.tutorialspoint.com/c_standard_library/c_function_sscanf.htm
        decode.rd =rdest; //set rd
        decode.op_A = imm; //set op A
        c += 5; //Increment C
        ic++; //Increment IC
        printf("li decoded\n");
        break;

      case 9 : //SUBI
        sscanf(if_id_old.operator, "%*c%d %*c%d %d",  &rdest,  &rsrc1, &imm); //https://www.tutorialspoint.com/c_standard_library/c_function_sscanf.htm
        decode.rd =rdest; //set rd
        decode.rs = rsrc1; //set rs
        decode.op_A = registers[rsrc1]; //set op A
        decode.op_B = imm; //set op B
        c += 5; //Increment C
        ic++; //Increment IC
        printf("subi decoded\n");
        break;

      case 10 : //SYSCALL
        c += 5; //Increment C
        ic++; //Increment IC
        printf("syscall decoded\n");
        break;

      case 11 : //NOP
        nops++; //increment NOPS
        ic ++; //Increment IC
        printf("NOP decoded\n"); 
        break;
    }

    id_exe_next = decode;

		mem_exe_old = mem_exe_next;

    mem_exe_old.alu_out = 0; //Initialize, FIXED my segmentation fault error

		mem_wb_old = mem_wb_next;

		mem_exe execute;

     // Forwarding 
    if (id_exe_old.rs == mem_exe_old.rd) {
      id_exe_old.op_A = mem_exe_old.alu_out; //set op A
    }

    if (id_exe_old.rt == mem_exe_old.rd) {
      id_exe_old.op_B = mem_exe_old.alu_out; //set op B
    }

    // Memory hazards
    if (mem_wb_next.rd == id_exe_old.rs) { 
      id_exe_old.op_A = mem_wb_next.alu_out; //set opA
    }
    if (mem_wb_next.rd == id_exe_old.rt) {
      id_exe_old.op_B = mem_wb_next.alu_out;v //set opB
    }

    switch (id_exe_old.op_code) { //EXECUTE INSTRUCTIONS

      case 1 : //ADD
        execute.alu_out = id_exe_old.op_A + id_exe_old.op_B; //Addition Operation
        printf("add executed\n\n");
        break;

      case 6 : //LA
        execute.alu_out = id_exe_old.op_A; //set ALU OUT
        printf("la executed\n\n");
        break;

      case 7 : //LB
        execute.alu_out = id_exe_old.op_A; //set ALU OUT
        printf("lb executed\n\n");
        break;

      case 8 : //LI
        execute.alu_out = id_exe_old.op_A; //set ALU OUT
        printf("li executed\n\n");
        break;

      case 9 : //SUBI
        execute.alu_out = id_exe_old.op_A - id_exe_old.op_B; //Subtraction Operation
        printf("subi executed\n\n");
        break;

      case 10 : //SYSCALL 
        c += 5;
        ic++;
        if (id_exe_old.op_A = 10) {
          double speedup = (8 * (double)ic) / (double)c; //calculate speedup
          printf("\n\nC = %d\nIC = %d\nSpeedup = %f\nNOPs = %d\n\n", c, ic, speedup, nops); //print values for C, IC, and speedup
          user_mode = false; //STOP
        }
        printf("syscall executed\n\n");
        break;

    }

    execute.op_code = id_exe_old.op_code;
    execute.op_B = id_exe_old.op_B;
    execute.rd = id_exe_old.rd;

    mem_exe_next = execute;


		i++;

	}
}