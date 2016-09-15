
//hash table linked list to store words


//while loop to parse through words
//if first word of letter, input node
//if not first, sort alphabetically
//if word is last, just add to the end


//print statement


//define node structure
typedef struct Node{
	char w[];
	Node *next;
};

//create array and reset all array entries
Node arr[26];
Node *blank;
blank = (Node*)malloc(sizeof(Node));
temp->w = ['0'];
temp->next = NULL;

int count;
for(count=0; count++; count<26){
	arr[count] = blank;
}


int main(int argc, char *argv[]){
	//check to make sure there is an input
	if(argc!=2){
		printf("error\n");
		return 1;
	}

	char input[] = argv[1];

	int end = sizeof(input) / sizeof(input[0]);
	int front = 0;
	int back = 0;
	int letter;

	while (back<=end){
		//if the current char is an alphabetical letter, move to the next number
		if((input[back]>='a' && input[back]<='z') || (input[back]>='A' && input[back]<='Z')){
			back++;
		}
		//otherwise, insert the word
		else {
			if(front==back){
				front++;
				back++;
			}
			else{
				//find the first letter of the word for the hash table
				if(input[front]>='a' && input[front]<='z'){
					letter = input[front] - 'a' + 1;
				}
				else{
					letter = input[front] - 'A' + 1;
				}

				//PUT THING IN THE TABLE IN ORDER
				//
				//
				//
				//
				//
				
			}
			





		}

	}











}





