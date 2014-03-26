#ifndef _SHELL_H_
#define _SHELL_H_

typedef enum { TypeCmd, TypePipe, TypeRedir, TypePair, TypeParam } NodeEnum;
typedef char bool;

typedef struct {
  char *cmd;
  struct NodeTypeTag *params;
} NodeCmd;

typedef struct {
  struct NodeTypeTag *cmd; // TypeCmd
  struct NodeTypeTag *pipe; // TypePipe
} NodePipe;

typedef struct {
  struct NodeTypeTag *cmd;
  struct NodeTypeTag *file;
} NodeRedir;

typedef struct {
  struct NodeTypeTag *car;
  struct NodeTypeTag *cdr;
} NodePair;

typedef struct {
  bool is_option;
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

int eval(NodeType *pn);

#endif
