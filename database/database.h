#include <vector>
using namespace std;

struct data_info
{
	char total_records [7];
	char new_rcd_index [7];
};

typedef struct user{
	char username [7];
	char password [7];
} USER;

void init_db();
void getDbDetails();
void getUsr(char* buffer,USER &us);
vector<USER> getList();
void update_mapping();
void close_db();
bool findUser(char* usr);
void addUser(char* un, char* pwd);