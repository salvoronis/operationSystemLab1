void initFlag(int argc,char *argv[]);
void flag_string(char **destination, char *flag);
void flag_int(int *destination, char *flag);
void flag_float(float *destination, char *flag);
void flag_bool(int *destination, char *flag);
struct Node {
	char *name;
	char *value;
	struct Node *next;
} Node;
