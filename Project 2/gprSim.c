/**
Project 2
Created by Tyler Andrews
Due: 7/25/2020
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

Memory memory;


Memory load_file(char file_name[]) {
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


int main() {
	memory = load_file("palindrome.s"); //this loads in the file palindrome.s, could be changed to where the file is taking as an argument, but I did this for simplicity for the grader
	
	string input = "level"; //THIS IS THE INPUT CHANGE THIS TO WHATEVER STRING YOU WANT TESTED!!

	int c = 0; //number of cycles spent in execution
	int ic = 0; //total number of instructions executed
	int registers[32]; //32 general purpose registers
	string messages[2];
  	strcpy(messages[1], "is");
 	strcpy(messages[2], "is not");
	  
	int rdest; //specify one of the general-purpose registers ($0 through $31).
	int rsrc1; //specify one of the general-purpose registers ($0 through $31).
	int rsrc2; //specify one of the general-purpose registers ($0 through $31).
	int imm; //denotes a signed immediate (an integer).
	int label; //denotes the address associated with a label in the .text or .data segment.
	int offset; //denotes a signed offset (an immediate in the instruction) which is to be added to the value in the base registerv

	int i = 0;
	bool user_mode  = true;
	
	while (user_mode) {

		int current_case_number = memory.text_segment[i].case_number;


		switch (current_case_number) {


			case 1 : //ADDI
				sscanf(memory.text_segment[i].operator, "%*c%d %*c%d %d", &rdest, &rsrc1, &imm); //set appropriate values
				registers[rdest] = registers[rsrc1] + imm; //additon operation
				c += 6;  //increment number of cycles spent in execution
				ic++; //increment number of instructions executed
				break;
		
			case 2 : //B
				sscanf(memory.text_segment[i].operator, "%d", &label); //set appropriate values
				i -= label;  //move down i number of steps
				c += 4; //increment number of cycles spent in execution
				ic++; //increment number of instructions executed
				break;

			case 3 : //BEQZ
				sscanf(memory.text_segment[i].operator, "%*c%d %d", &rsrc1, &label); //set appropriate values
				if(registers[rsrc1] == 0) {  
					i += label;  //move up i number of steps
				}
			    c += 5; //increment number of cycles spent in execution
  				ic++; //increment number of instructions executed
				break;

			case 4 : //BGE
				sscanf(memory.text_segment[i].operator, "%*c%d %*c%d %d", &rsrc1, &rsrc2, &label); //set appropriate values
				if(registers[rsrc1] >= registers[rsrc2]) { 
					i += label; //move up i number of steps
				}
				c += 5; //increment number of cycles spent in execution
				ic++; //increment number of instructions executed
				break;

			case 5 : //BNE
				sscanf(memory.text_segment[i].operator, "%*c%d %*c%d %d", &rsrc1, &rsrc2, &label); //set appropriate values
				if(registers[rsrc1] != registers[rsrc2]) {
					i += label; //move up i number of steps
				}
				c += 5; //increment number of cycles spent in execution
				ic++; //increment number of instructions executed
				break;

			case 6 : //LA
				sscanf(memory.text_segment[i].operator, "%*c%d %d", &rdest, &label); //set appropriate values
				registers[rdest] = memory.data_segment[label].content;
				c += 5; //increment number of cycles spent in execution
				ic++; //increment number of instructions executed
				break;

			case 7 : //LB
				sscanf(memory.text_segment[i].operator, "%*c%d %*c%d", &rdest, &offset); //set appropriate values
				registers[rdest] = input[registers[offset]];
				c += 6; //increment number of cycles spent in execution
				ic++; //increment number of instructions executed
				break;

			case 8 : //LI
				sscanf(memory.text_segment[i].operator, "%*c%d %d", &rdest, &imm); //set appropriate values
				registers[rdest] = imm;
				c += 3; //increment number of cycles spent in execution
				ic++; //increment number of instructions executed
				break;

			case 9 : //SUBI
				sscanf(memory.text_segment[i].operator, "%*c%d %*c%d %d", &rdest, &rsrc1, &imm); //set appropriate values
				registers[rdest] = registers[rsrc1] - imm; //subtract by imm
				c += 6; //increment number of cycles spent in execution
				ic++; //increment number of instructions executed
				break;
		
			case 10 :  //SYSCALL
				if (registers[4] == 1) {
					printf("\n%s %s a palindrome\n", input, messages[registers[6]]);	
				}
				else if (registers[4] == 2) { 
					user_mode = false;		
				}
				c += 8; //increment number of cycles spent in execution
				ic++; //increment number of instructions executed
				break;

			
			default:
				user_mode = false;
			
		}
		i++;
	}


	double speedup = (8 * (double)ic) / (double)c; //calculate speedup


	printf("\n\nC = %d\nIC = %d\nSpeedup = %f\n\n", c, ic, speedup); //print values for C, IC, and speedup
	
    
}