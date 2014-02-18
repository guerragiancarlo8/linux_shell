/*SHELL PROJECT*/
/*Author: Giancarlo M. Guerra-Salvá*/
/*This project is part of my operating systems course. The final project will be a fully-funcitoning OS */
/*To start, open a linux terminal and compile the program. then execute. A "-->" should appear. Begin entering Commands*/
 
 
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
 
#define MAXSIZE	100
 
int string_id(char s[]); /*Taking user input, returns an int which determines what instruction the shell will execute */
 
 
 
main()
{
	int active = 1;
 
	char NAME_OF_INSTRUCTION[MAXSIZE];
	char NAME_OF_FILE[MAXSIZE];
 
	char *args[] = {NAME_OF_INSTRUCTION,NULL};
 
	int status = 0;
 
	
	
 
	while(active)
	{
		printf("--->  ");
 
		scanf("%s",NAME_OF_INSTRUCTION);    /*Instruction is stored*/
 
		int state;
 
		
 
		int id = string_id(NAME_OF_INSTRUCTION);    /*ID of instruction is returned*/
 
		
 
 
		if(id == 1)                     /*procedure for "ext" instruction*/
		{
			printf("Thank you!\n");
			active = 0;
		}
		else if(id == 2)                /*procedure for the "typ" instruction*/
		{
			int active2 = 1;	
			while(active2)
			{
				FILE *fp;
				char str[MAXSIZE];
				printf("filename to print: ");
				scanf("%s",NAME_OF_FILE);
				fp = fopen(NAME_OF_FILE,"r");
 
 
				if(fp == NULL)
				{
					printf("Error opening file or file does not exist\n");
					break;
				}
				else if(fgets(str, MAXSIZE, fp) != NULL)
				{
					puts(str);
				}
				fclose(fp);
				active2 = 0;
			}
 
		}
		else if(id == 3)                  /*Procedure for the "cop" instruction*/
		{
			int active3 = 1;
			while(active3)
			{
				FILE *fp, *dp;
				char str1[MAXSIZE], str2[MAXSIZE];
				char ch;
				printf("filename to copy: ");
				scanf("%s",NAME_OF_FILE);
				gets(str1);
				fp = fopen(NAME_OF_FILE,"r");
				if(fp == NULL)
				{
					printf("Error opening original file or file does not exist\n");
					break;
					
				}
 
				printf("What would you like to name the new file?: ");
				scanf("%s",str2);
				dp = fopen(str2,"w");
				gets(str2);
				if(dp == NULL)
				{
					perror("Error copying to new file\n");
					exit(0);
				}
				while((ch=getc(fp))!=EOF)
				{
					putc(ch,dp);
				}
				printf("SUCCESS!\n");
				fclose(fp);
				fclose(dp);
				active3 = 0;
			}
 
		}
		else if(id == 4)                        /*Procedure for the "rem" instruction*/
		{
			printf("filename to delete: ");
			scanf("%s",NAME_OF_FILE);
			state = remove(NAME_OF_FILE);
			if(state == 0)
			{
				printf("File deleted succesfully!\n");
			}
			else
			{
				printf("Error. Unable to delete file\n");
			}
			
		}
		else if(id == 5)                          /*If none of the instructions are written by the user, shell assumes input is the name of a program and executes it*/
		{                                         /*If a program is succesfully executed, the shell will wait until that program closes and then prompt again*/
			pid_t child_PID;  
 
			child_PID = fork();
 
			if(child_PID >= 0)
			{
				if(child_PID == 0)
				{
					if((execvp(args[0],args)) < 0)                    /*Attempt to launch program is made. If not possible, error message displays */
					{
						printf("Error:Program does not exist or not an .exe\n");
						exit(1);
					}
					else
					{
						execvp(args[0],args);                           /*If execution sucessful, program opens and will remain open*/
						exit(0);
					}
 
				}
				
				
				if(wait(&status) != -1)                     /*Ensures that the program executed remains open until the user terminates it*/
				{
					;                           
 
				}
					
					
				
			}
			else
			{
				printf("Fork failed\n");      /*fork failure exit clause*/
				exit(1);
			}
		}
					
	}
	return 0;
}
 
 
int string_id(char s[])
{
 
	char temp1[3];      /*the "ext" command allows the user to exit from the shell*/
	char temp2[3];      /*the "typ" command allows user to enter the name of a file, and display it on the screen */
	char temp3[3];      /*the "cop" command allows user to enter the name of a file and copy the contents to another newly-created file*/
	char temp4[3];      /*the "rem" instruction deletes the file specified. 
 
	temp1[0] = 'e';
	temp1[1] = 'x';
	temp1[2] = 't';
 
	temp2[0] = 't';
	temp2[1] = 'y';
	temp2[2] = 'p';
 
	temp3[0] = 'c';
	temp3[1] = 'o';
	temp3[2] = 'p';
 
	temp4[0] = 'r';
	temp4[1] = 'e';
	temp4[2] = 'm';
 
 
	
	
	if(s[0] == temp1[0])
	{
		if(s[1] == temp1[1])
		{
			if(s[2] == temp1[2])
			{
				return 1;
			}
		}
		
	}
	else if(s[0] == temp2[0])
	{
		if(s[1] == temp2[1])
		{
			if(s[2] == temp2[2])
			{
				return 2;
			}
		}
	}
	else if(s[0] == temp3[0])
	{
		if(s[1] == temp3[1])
		{
			if(s[2] == temp3[2])
			{
				return 3;
			}
		}
	}
	else if(s[0] == temp4[0])
	{
		if(s[1] == temp4[1])
		{
			if(s[2] == temp4[2])
			{
				return 4;
			}
		}
 
	}
	else
	{
		return 5;
	}
}
