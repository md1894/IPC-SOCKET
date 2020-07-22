#include <iostream>
#include "database.h"
#include <bits/stdc++.h>
using namespace std;

// extern struct data_info db_info;

int main(){
	char un [7], pwd [7];
	std::cin >> un >> pwd;
	addUser(un,pwd);
	vector<USER> u = getList();
	cout << u.size() << endl;
	for(int i = 0; i < u.size(); i++) {
		cout << u[i].username << endl;
	}
	cout << "DATABASE DETAILS \n";
	cout << "TOTAL :: " << getDB_DET().total_records << endl;
	return 0;
}