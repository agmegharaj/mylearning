/* The C-code will run "repo sync <project_name>" rather "repo sync". When Internet speed is an issue we have faced                     *
 * so many times repo hung and it started back all from begining.													                        *
 * This C code will read the manifest.xml file and create the project name list and then do repo sync on each		                *
 * project name and once downloaded marked them as DONE.															                *
 * place the binary under same android repository folder, do repo init and then run this application with arguments                     *
 * example:																											*
 *			./repo-sync all/create/sync <filename>														                *
 *				 - filename is optional for all but mandatory for create and sync. In this file project names will	*
 *				 be stored																							*
 *				 - create is for creating filename with project names												*
 *				 - sync is for syncing projects one by one and mark downloaded one as DONE in filename		        *
 *				 - all is for doing both back to back (filename is optional, default name is projects.txt		*
 *******************************************************************************************************************/


#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_FILE ".repo/manifest.xml"
#define PROJECT_FILE "projects.txt"
#define VALID_STRING "  <project"
#define CHECK_STRING "name="
#define LINE_SIZE 1000
#define COMPARELIMIT 10
#define COMMAND "repo sync "
#define TEMP_FILE "other.txt"

int create_list(char *filename)
{
	char *linebuffer;
	FILE *input,*output;
	int flag=0;
	linebuffer= (char *) malloc(sizeof(char) * LINE_SIZE);	
	
	input=fopen(INPUT_FILE, "r");
	if(input == NULL)
	{
 		printf("file open failed please check the path and file name\n");
 		return -2;
	}
	output=fopen(filename, "w");
	if(output == NULL) {
		printf("error creating outputfile\n");
		return -1; 
	}
	
	
 	while (fgets(linebuffer, LINE_SIZE, input) != NULL ) /* read a line */
 	{
		if (flag == 0)
			flag=1;
		if(!strncmp(linebuffer, VALID_STRING, COMPARELIMIT))
		{
			char *start=NULL; 
			char *end=NULL; 
			int no_byte=0;
			start=strstr(linebuffer, CHECK_STRING);
			start=start+6;
			//printf("LINEBUFFER:DEBUG=%s\n",start);
			end=strchr(start, '\"');
			//printf("TEMP_DEBUG=%s\n", end);
			no_byte=strlen(start) - strlen(end);
			//printf("NO_BYTE:%d\n",no_byte);	
			fwrite(start, 1, no_byte, output);
			fputs("     ",output);
			fputc('\n', output);
			if (flag == 1)			
				flag=2;
		}
		
	}
	fclose(input);
	fclose(output);
	free(linebuffer);
	if(flag==0) {
		printf("File contains nothing\n");
		return -1;
	}
	if(flag==1) {
		printf("No valid string found in the file\n");
		return -1;
	}
	return 0;
}

int repo_sync(char *filename)
{
	FILE *fp;
	char *proj;
	int status, len;
	char command[210];
	char temp[] = ":DONE";
	proj = (char *)malloc(sizeof(char) * 200);
	fp = fopen(filename, "r+");
	
	if(fp == NULL)
	{
 		printf("file open failed please check the path and file name\n");
 		return -2;
	}
	while (fgets(proj, 200, fp) != NULL ) /* read a line */ {
		len = strlen(proj);
		strcpy(command, COMMAND);
		strcat(command, proj);
		printf("COMMAND: %s\n", command);
		if (strstr(proj, temp) == NULL) {
			if (command != NULL)
				status = system(command);
			if (status) {
				printf("Repo sync error while syncing %s project\n", proj);
				return -11;
			}
			
			fseek(fp, -6, SEEK_CUR);
			fputs(temp,fp);
			fseek(fp, 1, SEEK_CUR);
		}
		else
			continue;	
	}
	fclose(fp);
	return 0;
}	

void print_usage(char *file)
{
	printf("ERROR: Wrong usage\n");
	printf("USAGE: %s <option> <filename>\n", file);
	printf("Options:\n \t\tcreate = creating project name list, pass the filename\n\t\tsync = repo syncing projects for filename\n\t\tall(or no arg)=do the both (no need to pass file name used the default)\n");
}

int main(int argc, const char *argv[])
{
	printf(" Developed by A G Megharaj (agmegharaj@gmail.com) and Tirtha Gosh. \n");
	int err=0;
	
	if(argc < 1 || argc > 3 ) {
		print_usage((char *)argv[0]);
		return -1;
	}
	if (!strcmp(argv[1], "create")) {
		if (argc != 3) {
			print_usage((char *)argv[0]);
			return -1;
		}
 		err=create_list((char *)argv[2]);
		return err;
	}
	if (!strcmp(argv[1], "sync")) {
		if (argc != 3) {
			print_usage((char *)argv[0]);
			return -1;
		}		
		err = repo_sync((char *)argv[2]);
		return err;
	}
	if (argc != 3) {
		err = create_list(PROJECT_FILE);
		err |= repo_sync(PROJECT_FILE);
	} else {
		err = create_list((char *)argv[2]);
		err |= repo_sync((char *)argv[2]);
	}
	return err;
}  










