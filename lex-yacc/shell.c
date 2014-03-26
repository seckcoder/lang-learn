#include <stdio.h>
#include <stdlib.h>
#include "shell.h"
#include "y.tab.h"


void freeNode(NodeType *pnode) {
  switch(pnode->type) {
    case TypeCmd:
      freeNode((pnode->cmd).params);
      break;
    case TypePair:
      freeNode((pnode->pair).cdr);
      break;
    case TypeRedir:
      freeNode((pnode->redir).cmd);
      break;
    case TypePipe:
      freeNode((pnode->pipe).cmd);
      freeNode((pnode->pipe).pipe);
      break;
  }
  free(pnode);
}

NodeType *_create_node(NodeEnum type) {
  NodeType *pn = (NodeType *)malloc(sizeof(NodeType));
  pn->type = type;
  return pn;
}
NodeType *create_cmd(char* cmd, NodeType *params) {
  NodeType *pn = _create_node(TypeCmd);
  NodeCmd cmd_node;
  cmd_node.cmd = cmd;
  cmd_node.params = params;
  pn->cmd = cmd_node;
  return pn;
}
NodeType *create_pipe(NodeType *cmd, NodeType *pipe) {
  NodeType *pn = _create_node(TypePipe);
  NodePipe pipe_node;
  pipe_node.cmd = cmd;
  pipe_node.pipe = pipe;
  pn->pipe = pipe_node;
  return pn;
}

NodeType *create_redir(NodeType *cmd, char *file) {
  NodeType *pn = _create_node(TypeRedir);
  NodeRedir redir_node;
  redir_node.cmd = cmd;
  redir_node.file = file;
  pn->redir = redir_node;
  return pn;
}
NodeType *create_pair(char *car, NodeType *cdr) {
  NodeType *pn = _create_node(TypePair);
  NodePair pair_node;
  pair_node.car = car;
  pair_node.cdr = cdr;
  pn->pair = pair_node;
  return pn;
}

int eval_cmd(char *cmd, NodeType *params) {
  printf("%s", cmd);
  if (eval(params) < 0) {
    return -1;
  }
  return 0;
}

int eval_redir(NodeType *cmd, char *file) {
  if (eval(cmd) < 0) {
    return -1;
  }
  printf(" > %s", file);
  return 0;
}

int eval_pipe(NodeType *cmd, NodeType *pipe) {
  if (eval(cmd) < 0) return -1;
  printf(" | ");
  if (eval(pipe) < 0) return -1;
  return 0;
}

int eval_pair(char *car, NodeType *cdr) {
  printf("%s", car);
  if (eval(cdr) < 0) return -1;
  return 0;
}

int eval(NodeType *pn) {
  if (pn == NULL) {
    return 0;
  } else {
    switch(pn->type) {
      case TypeCmd:
        return eval_cmd((pn->cmd).cmd, (pn->cmd).params);
      case TypeRedir:
        return eval_redir((pn->redir).cmd, (pn->redir).file);
      case TypePipe:
        return eval_pipe((pn->pipe).cmd, (pn->pipe).pipe);
      case TypePair:
        return eval_pair((pn->pair).car, (pn->pair).cdr);
    }
    printf("\n");
    return 0;
  }
}
