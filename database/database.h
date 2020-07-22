#include <vector>
using namespace std;

struct data_info
{
	int total_records;
	int new_rcd_index;
};

typedef struct user{
	char username [7];
	char password [7];
} USER;

void init_db();
void getDbDetails();
void getUsr(char* buffer,USER &us);
vector<USER> getList();
bool findUser(char* usr);
void addUser(char* un, char* pwd);