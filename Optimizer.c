/*
 *********************************************
 *  314 Principles of Programming Languages  *
 *********************************************
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "InstrUtils.h"
#include "Utils.h"

int findNumberOfInstructions(Instruction *head);
int findNumberOfInstructions(Instruction *head){
	int count =0;
	Instruction *ptr = head;
	while(ptr!=NULL){
		ptr=ptr->next;
		count+=1;
	}
	return count;
}
int checkCritical(int val, int arr[]);
int checkCritical(int val, int arr[]) {
    int len = sizeof(arr)/sizeof(int);
	int i =0;
    for(i = 0;i<len;++i){
        if(arr[i]==val){
            return 1;
        }
    }
    return -1;
}
Instruction * deleteDeadCode(Instruction *head){
	Instruction *ptr = head;
	while(ptr!=NULL){
		if(ptr->critical=='n'){
			ptr->prev = ptr->next;
			Instruction *temp = ptr;
			ptr = ptr->next;
			free(temp);
		}else{
			ptr=ptr->next;
		}
	}
	return head;
}

int main()
{
	Instruction *head;

	head = ReadInstructionList(stdin);
	if (!head) {
		WARNING("No instructions\n");
		exit(EXIT_FAILURE);
	}
	/* YOUR CODE GOES HERE */
	if (head) {
		//get tail of instructions
		Instruction *tail = LastInstruction(head);
		//get the number of instructions present in the linked list
		int numInstructions = findNumberOfInstructions(head);
		//set an index for inserting into an array
		int arrayIndex = 0;
		//create an array to represent the critical registers
		int critical[numInstructions];
		//set a pointer to the tail to iterate backwards
		Instruction *ptr = tail;
		while(ptr!=NULL){
			switch(ptr->opcode){
				//if the opcode is WRITE then we push field1 into the arrary of criticals
				case WRITE: //WRITE
					ptr->critical='y';
					//subtract by 200 to make the value of the variable negative
					critical[arrayIndex]=(ptr->field1)-200;
					arrayIndex+=1;
					break;
				case READ: //READ
					ptr->critical='y';
					break;
				case STORE: //STORE
					if(checkCritical((ptr->field1)-200,critical)==1){
						critical[arrayIndex]=ptr->field2;
						arrayIndex+=1;
						ptr->critical='y';
					}
					else{
						ptr->critical='n';
					}
					break;
				case LOADI:
				case LOAD:
					if(checkCritical(ptr->field1,critical)==1){
						critical[arrayIndex]=ptr->field1;
						arrayIndex+=1;
						ptr->critical='y';
					}else{
						ptr->critical='n';
					}
				case ADD:
				case MUL:
				case SUB:
					if(checkCritical(ptr->field1,critical)==1){
						critical[arrayIndex]=ptr->field2;
						arrayIndex+=1;
						critical[arrayIndex]=ptr->field3;
						arrayIndex+=1;
						ptr->critical='y';
					}else{
						ptr->critical='n';
					}
			}
			ptr=ptr->prev;
		}

		//loop through the linked list and delete all of the nodes that are not critical
		head = deleteDeadCode(head);

		PrintInstructionList(stdout, head);
		DestroyInstructionList(head);
	}
	return EXIT_SUCCESS;
}

