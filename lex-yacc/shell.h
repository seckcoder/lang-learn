#ifndef _SHELL_H_
#define _SHELL_H_

typedef enum { TypeCmd, TypePipe, TypeRedir, TypePair } NodeEnum;

typedef struct {
  char *cmd;
  struct NodeType *params;
} NodeCmd;

typedef struct {
  struct NodeType *cmd; // TypeCmd
  struct NodeType *pipe; // TypePipe
} NodePipe;

typedef struct {
  struct NodeType *cmd;
  char *file;
} NodeRedir;

typedef struct {
  char *car;
  struct NodeType *cdr;
} NodePair;

typedef struct {
  NodeEnum type;
  union {
    NodeCmd cmd;
    NodePipe pipe;
    NodeRedir redir;
    NodePair pair;
  };
} NodeType;


void freeNode(NodeType *pnode);
NodeType *create_cmd(char* cmd, NodeType *params);
NodeType *create_pipe(NodeType *cmd, NodeType *pipe);
NodeType *create_redir(NodeType *cmd, char *file);
NodeType *create_pair(char *car, NodeType *cdr);

int eval(NodeType *pn);

#endif
