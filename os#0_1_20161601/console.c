#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "bitmap.h"
#include "hash.h"
#include "console.h"

char** tokenize_str(char* str, int* token_cnt);
struct list_elem* n_th_elem(int index, int node_index);
	
struct list List[10];

struct list_node{
	struct list_elem elem;
	int data;
};

static bool list_less(const struct list_elem *a, const struct list_elem *b, void *aux){
	struct list_node* anode =list_entry(a,struct list_node,elem);
	struct list_node* bnode =list_entry(b,struct list_node,elem);
	return anode->data < bnode ->data;
}

int main(){
	int type;
	int token_cnt, obj_cnt=0;
	int i;
	char command_str[256];	//사용자로부터 입력받는 명령어
	char** command;	//command_str을 공백단위로 쪼갠 문자열 배열

	while(1){	

		fgets(command_str,sizeof(command_str),stdin);	
		command=tokenize_str(command_str,&token_cnt);

		//QUIT
		if(!strcmp(command[0],"quit")){
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

		//DELETE
		else if( !strcmp(command[0], "delete") && token_cnt==2){
			if( type==LIST){
				int index = command[1][4]-'0';

				while (!list_empty (&List[index]))
				{
					struct list_elem *e = list_pop_front (&List[index]);
					free(e);
				}
			}
		}

		//DUMPDATA
		else if( !strcmp(command[0], "dumpdata")&& token_cnt==2){
			//LIST
			if(type==LIST){
				int index=command[1][4]-'0';

				if(!list_empty(&List[index])){
					struct list_elem* e;

					for(e= list_begin(&List[index]); e!=list_end(&List[index]); e = list_next(e)){
						struct list_node* node = list_entry(e,struct list_node, elem);
						printf("%d ", node->data);
					}
					printf("\n");
				}
			}
		}

		//LIST_EMPTY
		else if( !strcmp(command[0], "list_empty") && token_cnt==2){
			int index = command[1][4]-'0';
			if( list_empty(&List[index]))
				printf("true\n");
			else
				printf("false\n");
		}

		//LIST_SIZE
		else if( !strcmp(command[0], "list_size") && token_cnt==2){
			int index = command[1][4]-'0';
			printf("%d\n", (int)list_size(&List[index]));
		}

		//LIST_INSERT
		else if( !strcmp(command[0], "list_insert") && token_cnt==4){
			int index= command[1][4]-'0';
			int node_index, node_data;
			sscanf(command[2], "%d", &node_index);
			sscanf(command[3], "%d", &node_data);

			
			//Create new list item
			struct list_elem* new_elem = (struct list_elem*)malloc(sizeof(struct list_elem));
			struct list_node* node = list_entry(new_elem, struct list_node, elem);
			node->data = node_data;
		
			//Push back
			if((unsigned)list_size(&List[index])-1<node_index || list_empty(&List[index])){
				list_push_back(&List[index],new_elem);
				continue;
			}

			//Push front
			if(node_index==0){
				list_push_front(&List[index],new_elem);
				continue;
			}
			
			int cur= 0;
			struct list_elem* e;
			for(e = list_begin(&List[index]); e!=list_end(&List[index]); e = list_next(e)){
				if(cur==node_index){
					list_insert(e, new_elem);		
					
					break;
				}
				cur++;
			}

		}

		//LIST_INSERT_ORDERD
		else if( !strcmp(command[0], "list_insert_ordered") && token_cnt==3){
			int index = command[1][4]-'0';
			int node_data;
			sscanf(command[2], "%d", &node_data);
			
			//Create new list item
			struct list_elem* new_elem = (struct list_elem*)malloc(sizeof(struct list_elem));
			struct list_node* node = list_entry(new_elem, struct list_node, elem);
			node->data = node_data;
		
			list_insert_ordered(&List[index],new_elem, list_less, NULL); 
		
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

		//LIST_PUSH_FRONT
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

		//LIST_POP_BACK
		else if( !strcmp(command[0], "list_pop_back") && token_cnt==2){
			int index = command[1][4]-'0';
			list_pop_back(&List[index]);
		}

		//LIST_POP_FRONT
		else if( !strcmp(command[0], "list_pop_front") && token_cnt==2){
			int index = command[1][4]-'0';
			list_pop_front(&List[index]);
		}

		//LIST_FRONT
		else if( !strcmp(command[0], "list_front") && token_cnt==2){
			int index = command[1][4]-'0';

			struct list_elem* e = list_front(&List[index]);
			struct list_node* node = list_entry(e,struct list_node, elem);

			if( node!=NULL) 
				printf("%d\n", node->data);
		}

		//LIST_BACK
		else if( !strcmp(command[0], "list_back") && token_cnt==2){
			int index = command[1][4]-'0';
			struct list_elem* e = list_back(&List[index]);
			struct list_node* node = list_entry(e, struct list_node, elem);

			if( node!=NULL) 
				printf("%d\n", node->data);
		}

		
		//LIST_MIN
		else if( !strcmp(command[0], "list_min") && token_cnt ==2){
			int index = command[1][4]-'0';
			struct list_elem* e = list_min(&List[index], list_less, NULL);
			struct list_node* node = list_entry(e, struct list_node, elem);
			printf("%d\n", node->data);
		}

		//LIST_MAX
		else if( !strcmp(command[0], "list_max") && token_cnt ==2){
			int index = command[1][4]-'0';
			struct list_elem* e = list_max(&List[index], list_less, NULL);
			struct list_node* node = list_entry(e, struct list_node, elem);
			printf("%d\n", node->data);
	
		}

		//LIST_REMOVE
		else if( !strcmp(command[0], "list_remove") && token_cnt==3){
			int index = command[1][4]-'0';
			int node_index, cur=0;
			sscanf(command[2], "%d", &node_index);

			list_remove(n_th_elem(index, node_index));
		}

		//LIST_REVERSE
		else if( !strcmp(command[0], "list_reverse") && token_cnt==2){
			int index = command[1][4]-'0';
			list_reverse(&List[index]);
		}

		//LIST_SORT
		else if( !strcmp(command[0], "list_sort") && token_cnt==2){
			int index = command[1][4]-'0';
			list_sort(&List[index], list_less, NULL);
		}

		//LIST_SPLICE
		else if( !strcmp( command[0], "list_splice") && token_cnt==6){
			int index1, index2;
			int before, first , last;
			int cur=0;

			index1=command[1][4]-'0';
			index2=command[3][4]-'0';
			sscanf(command[2], "%d", &before);
			sscanf(command[4], "%d", &first);
			sscanf(command[5], "%d", &last);

			struct list_elem* e, *e_before=NULL;
			struct list_elem *e_first=NULL, *e_last=NULL;
			
			e_before = n_th_elem(index1, before);
			e_first = n_th_elem(index2, first);
			e_last = n_th_elem(index2, last);
			list_splice(e_before, e_first, e_last);
		}

		//LIST_SWAP
		else if( !strcmp(command[0], "list_swap") && token_cnt==4){
			int index= command[1][4]-'0';
			int node1, node2;
			sscanf(command[2], "%d", &node1);
			sscanf(command[3], "%d", &node2);
			list_swap(n_th_elem(index, node1), n_th_elem(index, node2));
		}

		//LIST_UNIQUE
		else if( !strcmp(command[0], "list_unique")&& ( token_cnt==3 || token_cnt==2)){
			int index1=command[1][4]-'0';
			int index2;

			if( token_cnt==2)
				list_unique(&List[index1], NULL, list_less, NULL);
			
			else{
				index2=command[2][4]-'0';
				list_unique(&List[index1], &List[index2], list_less, NULL);
			}

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

struct list_elem* n_th_elem(int index, int node_index){
	int cur=0;
	
	struct list_elem* e;
	for( e= list_begin(&List[index]); e!= list_end(&List[index]); e= list_next(e)){
		if(cur==node_index){
			break;
		}
		cur++;
	}
	
	return e;

}
struct list_elem* create_list_node(int data){
	struct list_elem* e= (struct list_elem*)malloc(sizeof(struct list_elem));
	struct list_node* node = list_entry(e,struct list_node, elem);
	node->data;
	return e;
}
