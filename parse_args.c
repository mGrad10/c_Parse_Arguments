/*
 * Implementation file for parse_args library.
 *
 * Author:Melinda Grad (mgrad@sandiego.edu)
 * The purpose of this library is to parse
 * command line arguments.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "parse_args.h"

// for parseArguments: a copy of the command line to make argv parm point to
// a static global variable means private to code in this file
static char cmdline_copy[MAXLINE];

/* Parses arguments
 * @param cmdline the commandline to be parsed
 * @param array to hold each command line arguments
 * @return indicates running in the background
 */
int parseArguments(const char *cmdline, char **argv) {
	//Cpy command line string into the buffer
	strcpy(cmdline_copy,cmdline);

	int i=0; 
	int ret = 0;

	//Tokenize the buffer and assign to argv array	
	char *token = strtok(cmdline_copy, " \n");
		
	for(i=0;token!= NULL;i++){
		argv[i] = token;
		if((strchr(token, '&'))!= NULL){
			ret = 1;
			break;	
		}
		else{
			token = strtok(NULL," \n");
		}
	}
	argv[i] = '\0';
	return ret;
}
/* Dynamically parses arguments
 * @param cmdline the commandline to be parsed
 * @param bg to signal running in the backgound
 * @return string containing each cmdline argument
 */
char **parseArgumentsDynamic(const char *cmdline, int *bg){
	// Make a duplicate of cmdline (to be tokenized)
	char *copy = strdup(cmdline);
	char *num_cpy = strdup(cmdline);
	
	//Get number of cmdline args
	int num_args = 0;	
	char *tok = strtok(num_cpy, " &\n");
	while(tok!=NULL){
		num_args++;
		tok = strtok(NULL, " &\n");
	}

	// Malloc space for arguments in array containing char*
	char **argv = malloc((num_args+1)*sizeof(char *));	//Return this
	if(argv == NULL){
		printf("Error allocating memory");
		exit(1);
	}
	// Tokenize the copy of the cmdline string
	char *token = strtok(copy," \n");

	//Loop through cmdline args and assign to argv	
	int i= 0;
	for(i = 0; token!=NULL; i++){
		argv[i] = strdup(token);
		// If background truncate
		if((strchr(token, '&'))!= NULL){
			*bg = 1;
			free(argv[i]);
			break;	
		}
		else{
			token = strtok(NULL," \n");
		}
	}
	argv[i] = '\0';
	free(copy);
	free(num_cpy);
	return argv;
}
