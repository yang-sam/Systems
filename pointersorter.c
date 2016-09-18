#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_{
	struct node * next;
	char * w[];
}node;

// // create array and reset all array entries
node arr[26];
node * blank;
int count;

int setup(){
	blank =(node *)malloc(sizeof(node));
	//perform check to see if space is available
	if(blank == NULL){
		return 1;
	}
	blank->w[1] = '0';
	blank->next = NULL;
	for(count=0; count<26; count++){
		arr[count] = *blank;
	}

}
// // node *blank = NULL;
// // blank = (node*)malloc(sizeof(node));
// // // blank->w[1] = '0';
// // // blank->next = NULL;

// int count;
// for(count=0; count<26; count++){
// 	// arr[count] = blank;
// }



int main(int argc, char *argv[]){
	//check to make sure there is an input
	if(argc!=2){
		printf("error\n");
		return 1;
	}

	char input[10];
	// printf("The argument taken in is %s\n", argv[1]);
	// char input[] = argv[1];

	int end = sizeof(input) / sizeof(input[0]);
	int front = 0;
	int back = 0;
	int letter;
	node *head = (node *)malloc(sizeof(node));
	node *temp = (node *)malloc(sizeof(node));
	node *prev = (node *)malloc(sizeof(node));
	node *newword = (node*)malloc(sizeof(
		));

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
				int sub = back-front+1;
				char substring[sub];
				strncpy(substring, input + front, back-front+1);
				// newword->w = substring;
				strcpy(newword->w, substring);

				*head = arr[letter];
				temp = head;
				//if the head is null or if the newword < current head
				if(temp->w[1] =='0' || strcmp(temp->w, newword->w>0)){
					arr[letter] = *newword;
					newword->next = temp;
				}
				else{
					//find the alphabetical location of the node
					prev = temp;
					temp = temp->next;
					//while the current node < newword or stop when the end node is found
					while(strcmp(temp->w, newword->w)<0 || temp->w != '0'){
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
	node *temp2;
	for(count=0; count < 26; count++){
		if(arr[count].w != '0'){
			*temp2 = arr[count];
			while(temp->w != '0'){
				printf("%s\n", temp->w);
				temp2 = temp->next;
			}
		}
	}
	free(blank);
	free(newword);
	free(head);
	free(prev);
	free(temp);
	free(temp2);
	return;


}





