#include <vector>
using namespace std;

typedef struct user{
	char username [7];
	char password [7];
} USER;

void getUsr(char* buffer,USER &us);
vector<USER> getList();
bool findUser(char* usr);
void addUser(char* un, char* pwd);