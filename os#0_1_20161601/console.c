#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "bitmap.h"
#include "hash.h"
#include "console.h"

char** tokenize_str(char* str, int* token_cnt);

struct list List[10];

struct list_node{
	struct list_elem elem;
	int data;
};

int main(){
	int type;
	int token_cnt, obj_cnt=0;
	int i;
	char command_str[256];	//사용자로부터 입력받는 명령어
	char** command;	//command_str을 공백단위로 쪼갠 문자열 배열

	printf("hello ina!\n");

	while(1){	

		fgets(command_str,sizeof(command_str),stdin);	
		command=tokenize_str(command_str,&token_cnt);

		//QUIT
		if(!strcmp(command[0],"quit")){
			printf("Bye~ ina!\n");
			break;
		}
		
		//CREATE
		if( !strcmp(command[0], "create")&& token_cnt==3 ){
			if( !strcmp(command[1], "list")){
				if(obj_cnt<=10){
					type=LIST;
					list_init(&List[obj_cnt]);	
					obj_cnt++;
				}
				else{
					printf("Maximum Number of List is 10\n");
				}
			}
		}

		//DUMPDATA
		else if( !strcmp(command[0], "dumpdata")&& token_cnt==2){
			//LIST
			if(type==LIST){
				int index=command[1][4]-'0';
				struct list_elem* e;
				
				for(e= list_begin(&List[index]); e!=list_end(&List[index]); e = list_next(e)){
					struct list_node* node = list_entry(e,struct list_node, elem);
					printf("%d ", node->data);
				}
				printf("\n");
			}
		}

		//LIST_PUSH_BACK
		else if( !strcmp(command[0], "list_push_back") && token_cnt==3){
			int index = command[1][4]-'0';
			int node_data;
			sscanf(command[2], "%d", &node_data);

			//create new list item
			struct list_elem* back = (struct list_elem*)malloc(sizeof(struct list_elem));;
			struct list_node* node = list_entry(back, struct list_node, elem);
			node->data = node_data;

			list_push_back(&List[index],back);
		}

		else if( !strcmp(command[0], "list_push_front") && token_cnt==3){
			int index = command[1][4]-'0';
			int node_data;
			sscanf(command[2], "%d", &node_data);

			//create new list item
			struct list_elem* front = (struct list_elem*)malloc(sizeof(struct list_elem));
			struct list_node* node = list_entry(front, struct list_node, elem);
			node->data = node_data;
			
			list_push_front(&List[index], front);
		}

		else if( !strcmp(command[0], "list_max") && token_cnt ==2){
			int index = command[1][4]-'0';
		}

		else if( !strcmp(command[0], "list_max") && token_cnt ==2){
			int index = command[1][4]-'0';
		}
	
	}
	
	return 0;

}

char** tokenize_str(char* str, int* token_cnt){
	int i=0,cnt=0;
	char copy[100];
	char* tmp=NULL;
	char** tokens=NULL;

	if(!str)
		return NULL;
	
	//token 개수 구하기
	strcpy(copy, str);
	tmp = strtok(copy, " \n\r\t");

	while(1){	
		cnt++;
		tmp = strtok(NULL, " \n\t\r");
		if(!tmp)
			break;
	}
	
	//token 개수 만큼 문자열 배열 할당
	*token_cnt=cnt;
	tokens = (char**)malloc(cnt*sizeof(char*));	
	for(i=0; i<cnt; i++)
		tokens[i] = (char*)malloc(100*sizeof(char));

	//배열 채우기
	strcpy(copy, str);
	
	tmp = strtok(copy, " \n\r\t");
	strcpy(tokens[0], tmp);
	
	for(i=1; i<cnt; i++){
		tmp = strtok(NULL, " \n\r\t");
		strcpy(tokens[i], tmp);
	}

	return tokens;
}


