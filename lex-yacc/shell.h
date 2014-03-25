typedef enum { TypeId } NodeEnum;


typedef struct {
  char *cmd;
  struct NodeType *params;
} TypeCmd;

typedef struct {
  TypeCmd *cmds;
  int cmd_num;
} TypePipe;

typedef struct {
  struct NodeType *left;
  struct NodeType *right;
} TypeRedir;

typedef struct {
  NodeEnum type;
  union {
    TypeCmd cmd;
    TypePipe pipe;
    TypeRedir redir;
  };
} NodeType;

typedef struct {
  NodeType *car;
  NodeType *cdr;
} NodePair;

void freeNode(NodeType *pnode);

NodeType *create_cmd(char* cmd, NodeType *params);
NodeType *create_pipe(NodeType *cmd, NodeType *pipe);
NodeType *create_redir(NodeType *cmd, NodeType *file);
NodeType *create_pair(NodeType *car, NodeType *cdr);

int eval(NodeType *pn);
