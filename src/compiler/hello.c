#define elif else if

#include "hello.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* source;
int source_pos;



enum Token returnToken(char* token){
    if(token[0] == 'f' && token[1] == 'n')
	    return function_keyword;
    elif(token[0] == 'i' && token[1] == 'f')
	    return if_keyword;
    elif(token[0] == 'e' && token[1] == 'l' && token[2] == 's' && token[3] == 'e')
	    return else_keyword;
    elif(token[0] == 'l' && token[1] == 'o' && token[2] == 'o' && token[3] == 'p')
	    return loop_keyword;
    elif(token[0] == 'm' && token[1] == 'o' && token[2] == 'd' && token[3] == 'u' && token[4] == 'l' && token[5] == 'e')
	    return module_keyword;
    elif(token[0] == 't' && token[1] == 'y' && token[2] == 'p' && token[3] == 'e')
	    return type_keyword;
    elif(token[0] == 'a' && token[1] == 'n' && token[2] == 'd')
	    return and_operator;
    elif(token[0] == 'o' && token[1] == 'r')
    	    return or_operator;
    elif(token[0] == 'n' && token[1] == 'o' && token[2] == 't')
    	    return not_operator;
    elif(token[0] == '=')
    	    return assign_operator;
    elif(token[0] == '=' && token[1] == '=')
    	    return eq_operator;
    elif(token[0] == '>')
    	    return gt_operator;
    elif(token[0] == '<')
    	    return lt_operator;
    elif(token[0] == '>' && token[1] == '=')
	    return gteq_operator;
    elif(token[0] == '<' && token[1] == '=')
	    return lteq_operator;   
    else
	    return identifier;
}

struct node {
   enum Token token;
   enum Scope scope;
   struct node* next;
};

struct node table;
enum Token currentToken;


enum Scope getScope(enum Scope current) {
}

int next(enum Scope scope) {
   if(scope == Module)
     module_statement();
   elif(scope == Function)
     function_statement();
   elif(scope == If)
     if_statement();
   elif(scope == Loop)
     loop_statement();
   elif(scope == Block)
     block_statement();
   return 0;
}

int insert(enum Token token) {
   struct node *temp = NULL;
   temp = &table;
   if (temp->token == None) {
      temp->token = token;
      return 0;
   }

   while(temp->next != NULL)
      temp = temp->next;
   
   if(temp->next == NULL) {
      temp->next = malloc(sizeof(struct node));
      if(next(temp->scope)) {
        temp->next->token = token;
        temp->next->scope = getScope(token);
      } else {
        printf("Parsing failed");
        exit(0);
      }
   }

}



enum Token parse(char *source) {
    char buffer[1024];
    char seperator;
    int pos = 0;
    while(source[source_pos] != '\0'){
    	printf("%c",source[source_pos]);
	buffer[pos] = source[source_pos];
	pos = pos + 1;
	source_pos = source_pos + 1;
	seperator = source[source_pos];
	if (seperator = ' ' || seperator == '\n' || seperator == '{' || seperator == '}' || seperator == '(' || seperator  == ')' || seperator == ',' || seperator == ':') {
	   enum Token token = returnToken(buffer);
	   return token;
	}
    }
}

int initParser(char* s) {
    source = s;
}

int parseFile(FILE* f) {
    char buffer[1024];
    fread(buffer,sizeof(char),1024,f);
    initParser(buffer);
}

int main(int argc, char** argv){
    FILE* f;
    f = fopen(argv[1], "r");
    if(f == NULL) {
    	printf("Couldnt open file");
	return 0;
    }
    parseFile(f);
}