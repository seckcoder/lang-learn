#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"
#include "y.tab.h"


void freeNode(NodeType *pnode) {
  if (pnode == NULL) {
    return;
  } else {
    switch(pnode->type) {
      case TypeCmd:
        free((pnode->cmd).cmd);
        freeNode((pnode->cmd).params);
        break;
      case TypePair:
        freeNode((pnode->pair).car);
        freeNode((pnode->pair).cdr);
        break;
      case TypeRedir:
        freeNode((pnode->redir).cmd);
        freeNode((pnode->redir).file);
        break;
      case TypePipe:
        freeNode((pnode->pipe).cmd);
        freeNode((pnode->pipe).pipe);
        break;
      case TypeParam:
        free((pnode->param).param);
        break;
      default:
        err_sys("not handled type");
    }
    free(pnode);
  }
}

NodeType *_create_node(NodeEnum type) {
  NodeType *pn = (NodeType *)malloc(sizeof(NodeType));
  pn->type = type;
  return pn;
}
NodeType *create_cmd(char* cmd, NodeType *params) {
  /*printf("create_cmd\n");*/
  NodeType *pn = _create_node(TypeCmd);
  NodeCmd cmd_node;
  cmd_node.cmd = cmd;
  cmd_node.params = params;
  pn->cmd = cmd_node;
  return pn;
}
NodeType *create_pipe(NodeType *cmd, NodeType *pipe) {
  /*printf("create_pipe\n");*/
  NodeType *pn = _create_node(TypePipe);
  NodePipe pipe_node;
  pipe_node.cmd = cmd;
  pipe_node.pipe = pipe;
  pn->pipe = pipe_node;
  return pn;
}

NodeType *create_redir(NodeType *cmd, NodeType *file) {
  /*printf("create_redir\n");*/
  NodeType *pn = _create_node(TypeRedir);
  NodeRedir redir_node;
  redir_node.cmd = cmd;
  redir_node.file = file;
  pn->redir = redir_node;
  return pn;
}
NodeType *create_pair(NodeType *car, NodeType *cdr) {
  /*printf("create_pair\n");*/
  NodeType *pn = _create_node(TypePair);
  NodePair pair_node;
  pair_node.car = car;
  pair_node.cdr = cdr;
  pn->pair = pair_node;
  return pn;
}

NodeType *create_param(bool is_option, char *param) {
  /*printf("create_param\n");*/
  NodeType *pn = _create_node(TypeParam);
  NodeParam param_node;
  param_node.param = param;
  param_node.is_option = is_option;
  pn->param = param_node;
  return pn;
}

int eval_rec(NodeType *pn);

int eval_cmd(char *cmd, NodeType *params) {
  printf("%s ", cmd);
  if (eval_rec(params) < 0) {
    return -1;
  }
  return 0;
}

int eval_redir(NodeType *cmd, NodeType *file) {
  if (eval_rec(cmd) < 0) {
    return -1;
  }
  printf(" > ");
  if (eval_rec(file) < 0) {
    return -1;
  }
  return 0;
}

int eval_pipe(NodeType *cmd, NodeType *pipe) {
  if (eval_rec(cmd) < 0) return -1;
  printf(" | ");
  if (eval_rec(pipe) < 0) return -1;
  return 0;
}

int eval_pair(NodeType *car, NodeType *cdr) {
  if (eval_rec(car) < 0) return -1;
  if (eval_rec(cdr) < 0) return -1;
  return 0;
}

int eval_param(bool is_option, char *param) {
  if (is_option) {
    printf("-");
  }
  printf("%s ", param);
  return 0;
}

int eval_rec(NodeType *pn) {
  if (pn == NULL) {
    return 0;
  } else {
    int ret = 0;
    switch(pn->type) {
      case TypeCmd:
        ret = eval_cmd((pn->cmd).cmd, (pn->cmd).params);
        break;
      case TypeRedir:
        ret = eval_redir((pn->redir).cmd, (pn->redir).file);
        break;
      case TypePipe:
        ret = eval_pipe((pn->pipe).cmd, (pn->pipe).pipe);
        break;
      case TypePair:
        ret = eval_pair((pn->pair).car, (pn->pair).cdr);
        break;
      case TypeParam:
        ret = eval_param((pn->param).is_option, (pn->param).param);
        break;
      default:
        err_sys("not handled type");
    }
    return ret;
  }
}

int eval(NodeType *pn) {
  int ret = eval_rec(pn);
  printf("\n");
  return ret;
}

void err_sys(char *msg) {
  fprintf(stderr, "%s", msg);
  exit(-1);
}

char* strclone(char *src, int len) {
  char* dst = (char*)malloc((len+1)*sizeof(char));
  memcpy(dst, src, len);
  dst[len] = '\0';
  return dst;
}
