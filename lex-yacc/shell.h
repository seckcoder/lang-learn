#ifndef _SHELL_H_
#define _SHELL_H_

typedef enum { TypeCmd, TypePipe, TypeRedir, TypePair, TypeParam} NodeEnum;
typedef char bool;


#define cmd_cmd_str(n) (((n)->cmd).cmd)
#define cmd_params(n) (((n)->cmd).params)

typedef struct {
  char *cmd;
  struct NodeTypeTag *params;
} NodeCmd;


#define pipe_cmd(n) (((n)->pipe).cmd)
#define pipe_pipe(n) (((n)->pipe).pipe)
typedef struct {
  struct NodeTypeTag *cmd; // TypeCmd
  struct NodeTypeTag *pipe; // TypePipe
} NodePipe;

typedef struct {
  struct NodeTypeTag *cmd;
  struct NodeTypeTag *file;
} NodeRedir;


#define pair_car(n) (((n)->pair).car)
#define pair_cdr(n) (((n)->pair).cdr)

typedef struct {
  struct NodeTypeTag *car;
  struct NodeTypeTag *cdr;
} NodePair;


#define param_str(n) (((n)->param).param)

typedef struct {
  char *param;
} NodeParam;


typedef struct NodeTypeTag {
  NodeEnum type;
  union {
    NodeCmd cmd;
    NodePipe pipe;
    NodeRedir redir;
    NodePair pair;
    NodeParam param;
  };
} NodeType;


void freeNode(NodeType *pnode);
NodeType *create_cmd(char* cmd, NodeType *params);
NodeType *create_pipe(NodeType *cmd, NodeType *pipe);
NodeType *create_redir(NodeType *cmd, NodeType *file);
NodeType *create_pair(NodeType *car, NodeType *cdr);
NodeType *create_param(bool is_param, char *param);

char* strclone(char *src, int len);
void err_sys(char *msg);

int print_node(NodeType *pn);
int eval(NodeType *pn);
void safe_free(void *p);

#endif
