#include<stdio.h>
#include<string.h>

void write_lines(){
	FILE* fp = fopen("myText.txt", "w+");
	int i;
	for(i = 0; i < 5; i++){
		char buffer [200];
		sprintf(buffer, "line %d\n", i+1);
		fwrite(buffer , 1 , strlen(buffer)*sizeof(char) , fp);
	}
	if(fp)
		fclose(fp);
}


int main()
{
	FILE* fp;
	char replacement [500] = "abc   \n";
	char read_buffer [500];
	int input_line_number, line_number = 1;
	fpos_t position;
	/*
	write 5 lines into file
	whatever line number user will enter , that line will get replaced with "abc"
	*/
	write_lines();
	scanf("%d",&input_line_number);
	fp = fopen("myText.txt", "r+");
	while(fgets(read_buffer, 500, fp)){
		if(input_line_number == 1){
			/* stream is pointing to 2nd line, so get that position */
			fgetpos(fp, &position);
			/* as user wants to replace 1st line therefore use rewind function */
			/* now stream is pointing to the start of file */
			rewind(fp);
			fwrite(replacement , 1 , strlen(replacement)*sizeof(char) , fp);
			/* again set stream point on 2nd line once write is completed */
			fsetpos(fp, &position);
		}
		else if(line_number == (input_line_number-1)){
			fwrite(replacement , 1 , strlen(replacement)*sizeof(char) , fp);
		}
		line_number++;
	}
	fclose(fp);
	return 0;
}
