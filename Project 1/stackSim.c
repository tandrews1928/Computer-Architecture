#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

enum {text, data}; //Got this from https://www.studytonight.com/c/typedef.php and also the lecture

typedef char string[20]; //Got this from https://www.studytonight.com/c/typedef.php and also the lecture

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

typedef struct stack { //Got this from https://www.studytonight.com/c/typedef.php and also the lecture
	int values[50];
	int top;
} Stack;

Stack stack;
Memory memory;

Memory load_file(char file_name[]) {
	FILE *assembly_file = fopen(file_name, "r");
	char line_of_text[300];
	char data_or_text;
	Memory memory;
	int t_index = 0;
	int d_index = 0;
	int next_t_index = 0x00000000;
	int next_d_index = 0x00000000;

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

				sscanf(line_of_text, "%s %s", memory.text_segment[t_index].task, memory.text_segment[t_index].operator); // https://www.tutorialspoint.com/c_standard_library/c_function_sscanf.htm

				if (strcmp(memory.text_segment[t_index].task, "PUSH") == 0) { //If push is read set the case number to 0
					memory.text_segment[t_index].case_number = 0;
				}
				else if (strcmp(memory.text_segment[t_index].task, "POP") == 0) { //if pop is read set the case number to 1
					memory.text_segment[t_index].case_number = 1;
				}
				else if (strcmp(memory.text_segment[t_index].task, "ADD") == 0) { //if add is read set the case number to 2
					memory.text_segment[t_index].case_number = 2;
				}
				else if (strcmp(memory.text_segment[t_index].task, "MUL") == 0) { //if mult is read set the case number to 3
					memory.text_segment[t_index].case_number = 3;
				}
				else if (strcmp(memory.text_segment[t_index].task, "END") == 0) { //if end is read set the case number to 4
					memory.text_segment[t_index].case_number = 4;
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

	memory = load_file("stackCode.s"); //this loads in the file stackCode.s, could be changed to where the file is taking as an argument, but I did this for simplicity for the grader

	stack.top = -1;

	int i = 0;
	bool user_mode  = true;

	while (user_mode) {

		int current_case_number = memory.text_segment[i].case_number;
		Data data = memory.data_segment[strtol(memory.text_segment[i].operator, NULL, 0)];
		int sum = 0;
		int product = 0;
		switch (current_case_number) {
			case 0 : //PUSH, will read the contents of memory at address x and push the value onto the stack.
				stack.values[stack.top + 1] = data.content;
				stack.top++;
				break;
			case 1 : //POP, will pop one word off the top of the stack and write the value to memory at address y.
				memory.data_segment[strtol(memory.text_segment[i].operator, NULL, 0)].content = stack.values[stack.top];
				stack.top--;
				break;
			case 2 : //ADD, will remove the top two words from the stack, add them, and leave the result on the top of the stack
				sum = stack.values[stack.top] + stack.values[stack.top - 1];
				stack.top--;
				stack.values[stack.top] = sum;
				break;
			case 3 : //MULT, will remove the top two words from the stack, multiply them, and leave the result on the top of the stack
				product = stack.values[stack.top] * stack.values[stack.top - 1];
				stack.top--;
				stack.values[stack.top] = product;
				break;
			case 4 : //END, just signals the end of the code.
				user_mode = false;
				break;
		}
		i++;
	}

	printf("\nStack Sim\n\nAnswer = %d \n\n", memory.data_segment[4].content);

}