#include <bits/stdc++.h>
#include <cstring>
#define ELLEN 7
#include "database.h"
using namespace std;

struct data_info db_info;

void init_db(){
	FILE* fp = fopen("mapping.txt", "r+");
	char buffer [200];
	if(fp){
		while(fgets(buffer, 500, fp)){
			memmove(db_info.total_records, buffer + 2, 6);
			db_info.total_records [6] = 0;
			memmove(db_info.new_rcd_index, buffer + 11 ,6);
			db_info.new_rcd_index [6] = 0;
		}
	}else{
		getDbDetails();
		FILE* mapping_file = fopen("mapping.txt", "w+");
		if(mapping_file){
			/* add logic to write data in mapping file */
			sprintf(buffer, "| %s | %s |", db_info.total_records, db_info.new_rcd_index);
			fwrite(buffer , 1 , strlen(buffer)*sizeof(char) , mapping_file);
			fclose(mapping_file);
		}
		return;
	}
	fclose(fp);
}


void getDbDetails(){
	FILE* fp = fopen("user.txt", "r+");
	char buffer [500];
	int total_rcd = 0;
	if(fp){
		while(fgets(buffer, 500, fp)){
			total_rcd++;
		}
		sprintf(db_info.total_records, "%6d", total_rcd);
		sprintf(db_info.new_rcd_index, "%6d", total_rcd);
	}else
		return;
}

void getUsr(char* buffer, USER &us){
	memmove(us.username, buffer + 2, 6);
	us.username [6] = 0;
	memmove(us.password, buffer + 11 ,6);
	us.password [6] = 0;
}

//void *memmove(void *dest, const void *src, size_t n)
bool findUser(char* u){
	char buffer [500];
	FILE* fp = fopen("user.txt", "r");
	if(!fp)
		return false;
	while(fgets(buffer, 500, fp)){
		if(strncmp(buffer + 2, u, 6) == 0){
			fclose(fp);
			return true;
		}
	}
	fclose(fp);
	return false;
}

vector<USER> getList(){
	vector<USER> us_list;
	char buffer [500];
	FILE* fp = fopen("user.txt", "r");
	while(fgets(buffer, 500, fp)){
		USER s;
		getUsr(buffer, s);
		us_list.push_back(s);
	}
	if(fp)
		fclose(fp);
	return us_list;
}

void close_db(){
	FILE* fp = fopen("mapping.txt", "w+");
	char buffer [500];
	if(fp){
		/* add logic to write data in mapping file */
		sprintf(buffer, "| %s | %s |", db_info.total_records, db_info.new_rcd_index);
		fwrite(buffer , 1 , strlen(buffer)*sizeof(char) , fp);
		fclose(fp);
	}
}

void addUser(char* user_name, char* password){
	if(findUser(user_name) == true){
		cout << "USER NAME ALREADY EXISTS !!!" << endl;
		return;
	}else{
		FILE* fp = fopen("user.txt", "a+");
		char buffer [500];
		sprintf(buffer, "| %s | %s |\n", user_name, password);
		fwrite(buffer , 1 , strlen(buffer)*sizeof(char) , fp);
		sprintf(db_info.total_records, "%6d", atoi(db_info.total_records) + 1);
		fclose(fp);
	}
}