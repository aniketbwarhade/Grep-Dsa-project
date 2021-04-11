// structure of node to get fileName
typedef struct node{
    char *fileName;
    struct node *next;
}node;
// Adt data structer of list
typedef struct list {
	node *front;
	node *end;
}list;
void init(list *l);
void insert(list *l, char fileName[]);
char* pop(list*l);
int isempty(list l);
// to create newnode
node *newNode(char *fileName);