#include <bits/stdc++.h>
#include <cstring>
#define ELLEN 7
#include "database.h"
using namespace std;


void getUsr(char* buffer,USER &us){
	memmove(us.username,buffer+2,6);
	us.username [6] = 0;
	memmove(us.password,buffer+11,6);
	us.password [6] = 0;
}

//void *memmove(void *dest, const void *src, size_t n)
bool findUser(char* u){
	char buffer [500];
	FILE* fp = fopen("user.txt","r");
	while(fgets(buffer,20,fp)){
		if(strncmp(buffer+2,u,6) == 0){
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
	FILE* fp = fopen("user.txt","r");
	while(fgets(buffer,500,fp)){
		USER s;
		getUsr(buffer,s);
		us_list.push_back(s);
	}
	fclose(fp);
	return us_list;
}


void addUser(char* user_name, char* password){
	if(findUser(user_name) == true){
		cout << "USER ALREADY EXISTS !!!" << endl;
		return;
	}else{
		FILE* fp = fopen("user.txt","a+");
		char buffer [500];
		sprintf(buffer, "| %s | %s |\n",user_name,password);
		fwrite(buffer , 1 , strlen(buffer)*sizeof(char) , fp );
		fclose(fp);
	}
}