#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_{
	struct node * next;
	char * w[];
}node;

// // create array and reset all array entries
node *arr[26];
node *blank;
int count;
int bleh = 0;

void setup(){
	blank =(node *)malloc(sizeof(node));
	//perform check to see if space is available
	if(blank == NULL){
		return 1;
	}
	blank->w[0] = '0';
	blank->next = NULL;
	for(count=0; count<26; count++){
		arr[count] = blank;
	}

}

// void freeArr(node *destroy){
// 	while(destroy->next != NULL){
// 		printf("count value %d\n", bleh);
// 		freeArr(destroy->next);
// 	}
// 	bleh++;
// 	free(destroy);
// 	return;
// }


int main(int argc, char *argv[]){
	//check to make sure there is an input
	setup();

	if(argc!=2){
		printf("error\n");
		return 1;
	}

	char input[strlen(argv[1])+1];
	strcpy(input, argv[1]);
	// printf("input array - %s\n", input);
// 	put in for testing purposes ^^
	int end = sizeof(input) / sizeof(input[0]);
	int front = 0;
	int back = 0;
	int letter;
	node *head;
	node *temp;
	node *prev;
	// node *head = (node *)malloc(sizeof(node));
	// node *temp = (node *)malloc(sizeof(node));
	// node *prev = (node *)malloc(sizeof(node));
	node *newword;

	int sub;
	char substring[100];

	// seg fault good up to here

	while (back<=end){
		//if the current char is an alphabetical letter, move to the next number
		if((input[back]>='a' && input[back]<='z') || (input[back]>='A' && input[back]<='Z')){
			back++;
		}
		//if the current char is not an alphabetical letter
		else {
			//if there is no word, skip the symbol
			if(front==back){
				front++;
				back++;
			}
			//if there is a word found
			else{
				//find the first letter of the word for the hash table
				if(input[front]>='a' && input[front]<='z'){
					letter = input[front] - 'a' + 1;
				}
				else{
					letter = input[front] - 'A' + 1;
				}
				//made a node for the word
				sub = back-front;
				// char substring[sub];
				newword = (node*)malloc(sizeof(node));
				strncpy(newword->w, input + front, back-front);
				// strcpy(newword->w, substring);
				strcpy(substring, "");
				head = arr[letter];
				temp = head;				
				//if the head is null or if the newword < current head

				//new word
				if(strcmp(temp->w, "0") == 0){
					newword->next = temp;
					arr[letter] = newword;

				}
				//earlier alphabetically
				else if(strcmp(temp->w, newword->w)>0){
					newword->next = temp;
					arr[letter] = newword;					
				}
				//later alphabetically
				else{
					//find the alphabetical location of the node

					while(strcmp(temp->w, newword->w)>0 || temp->next != NULL){
						prev = temp;
						temp = temp->next;
					}
					prev->next = newword;
					newword->next = temp;
				}

				back++;
				front = back;

			}
		}
	}

	//printing the words in alphabetical order
	for(count=0; count < 26; count++){
		temp = arr[count];	
		while(strcmp(temp->w, "0") != 0 ){
			printf("%s\n", temp->w);
			prev = temp;
			temp = temp->next;
			free(prev);
		}
	}

	// for(count=0; count <26; count++){
	// 	temp = arr[count];
	// // 	freeArr(temp);
	// // }
	// free(arr);
	return;

}

//space issue
//capitalization issue
