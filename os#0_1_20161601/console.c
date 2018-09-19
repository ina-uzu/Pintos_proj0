#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "bitmap.h"
#include "hash.h"

char** tokenize_str(char* str, int* token_cnt);

int main(){
	int token_cnt;
	int i;
	char command_str[256];	//사용자로부터 입력받는 명령어
	char** command;	//command_str을 공백단위로 쪼갠 문자열 배열

	printf("hello ina!\n");

	while(1){	

		fgets(command_str,sizeof(command_str),stdin);	
		
		if( strcmp(command_str,"quit")==0){
			printf("Bye~ ina!\n");
			break;
		}
		
		command=tokenize_str(command_str,&token_cnt);

		for(i=0; i<token_cnt; i++){
			printf("%s\n", command[i]);
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


