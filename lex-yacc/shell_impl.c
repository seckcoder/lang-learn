#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
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

char* format_param(bool is_option, char *param) {
  if (is_option) {
    int len = strlen(param) + 1;
    char *dest = (char*)malloc((len+1)*sizeof(char));
    dest[0] = '-';
    strcpy(&dest[1], param);
    return dest;
  } else {
    return param;
  }
}
NodeType *create_param(bool is_option, char *param) {
  /*printf("create_param\n");*/
  NodeType *pn = _create_node(TypeParam);
  NodeParam param_node;
  param_node.param = format_param(is_option, param);
  pn->param = param_node;
  return pn;
}

int print_node_rec(NodeType *pn);

int print_node_cmd(char *cmd, NodeType *params) {
  printf("%s ", cmd);
  if (print_node_rec(params) < 0) {
    return -1;
  }
  return 0;
}

int print_node_redir(NodeType *cmd, NodeType *file) {
  if (print_node_rec(cmd) < 0) {
    return -1;
  }
  printf(" > ");
  if (print_node_rec(file) < 0) {
    return -1;
  }
  return 0;
}

int print_node_pipe(NodeType *cmd, NodeType *pipe) {
  if (print_node_rec(cmd) < 0) return -1;
  if (pipe != NULL) {
    printf(" | ");
    if (print_node_rec(pipe) < 0) return -1;
  }
  return 0;
}

int print_node_pair(NodeType *car, NodeType *cdr) {
  if (print_node_rec(car) < 0) return -1;
  if (print_node_rec(cdr) < 0) return -1;
  return 0;
}

int print_node_param(char* param) {
  printf("%s ", param);
  return 0;
}

int print_node_rec(NodeType *pn) {
  if (pn == NULL) {
    return 0;
  } else {
    int ret = 0;
    switch(pn->type) {
      case TypeCmd:
        ret = print_node_cmd((pn->cmd).cmd, (pn->cmd).params);
        break;
      case TypeRedir:
        ret = print_node_redir((pn->redir).cmd, (pn->redir).file);
        break;
      case TypePipe:
        ret = print_node_pipe((pn->pipe).cmd, (pn->pipe).pipe);
        break;
      case TypePair:
        ret = print_node_pair((pn->pair).car, (pn->pair).cdr);
        break;
      case TypeParam:
        ret = print_node_param((pn->param).param);
        break;
      default:
        err_sys("not handled type");
        break;
    }
    return ret;
  }
}

int print_node(NodeType *pn) {
  int ret = print_node_rec(pn);
  printf("\n");
  return ret;
}



int list_length(NodeType* param_lst) {
  int counter = 0;
  while (param_lst != NULL) {
    counter += 1;
    param_lst = pair_cdr(param_lst);
  }
  return counter;
}

// arr is null terminated
// Deprecated
char **pair_of_str_to_arr(NodeType *param_lst) {
  int len = list_length(param_lst);
  if (len == 0) {
    return NULL;
  } else {
    char **arr = (char**)malloc((len+1)*sizeof(char*));
    int i = 0; 
    for(i = 0; i < len; i++) {
      arr[i+1] = param_str(pair_car(param_lst));
      param_lst = pair_cdr(param_lst);
    }
    arr[len+1] = (char*)0; // cast it to a pointer.
    return arr;
  }
}

int eval_node_cmd1(char *cmd, NodeType *params) {
  pid_t pid;
  if ((pid = fork()) < 0) {
    err_sys("fork error");
    return -1;
  } else if (pid == 0) { // child
    int len = list_length(params);
    char **param_arr = (char**)malloc((len+2) * sizeof(char*));
    int i = 0;
    param_arr[0] = cmd;
    param_arr[len+1] = NULL;
    NodeType *head = params;
    for(i = 0; i < len; i++) {
      param_arr[i+1] = param_str(pair_car(head));
      head = pair_cdr(head);
    }
    if (execvp(cmd, param_arr) < 0) {
      err_sys("execvp failed");
      free(param_arr);
      return -1;
    } else {
      free(param_arr);
      return 0;
    }
  } else { // parent
    if (waitpid(pid, NULL, 0) < 0) {
      err_sys("wait error");
      return -1;
    }
  }
  return 0;
}

int eval_node_cmd(NodeType *pn) {
  return eval_node_cmd1(cmd_cmd_str(pn), cmd_params(pn));
}

int eval_node_redir1(NodeType *cmd, NodeType *file) {
  if (close(1) < 0) {
    err_sys("cannot close stdout");
    return -1;
  } else {
    char *fname = param_str(file);
    int fd = open(fname, O_CREAT|O_WRONLY, 0666);
    if (fd < 0) {
      char err_msg[256];
      sprintf(err_msg, "open file ~s failed", fname);
      err_sys(err_msg);
      return -1;
    } else {
      // fd is 1
      int ret = eval_node_cmd(cmd);
      if (close(fd)) {
        char err_msg[256];
        sprintf(err_msg, "open file ~s failed", fname);
        err_sys(err_msg);
        return -1;
      }
      return 0;
    }
  }
}

int eval_node_redir(NodeType *pn) {
  return eval_node_redir1((pn->redir).cmd, (pn->redir).file);
}

int eval_node_pipe(NodeType *cmd, NodeType *pipe) {
}
int eval_node_pair(NodeType *car, NodeType *cdr) {
}
int eval_node_param(char *param) {

}
int eval(NodeType *pn) {
  if (pn == NULL) {
    return 0;
  } else {
    int ret;
    switch(pn->type) {
      case TypeCmd:
        ret = eval_node_cmd(pn);
        break;
      case TypeRedir:
        ret = eval_node_redir(pn);
        
        break;
      case TypePipe:
        ret = eval_node_pipe((pn->pipe).cmd, (pn->pipe).pipe);
        break;
      case TypePair:
        ret = eval_node_pair((pn->pair).car, (pn->pair).cdr);
        break;
      case TypeParam:
        ret = eval_node_param((pn->param).param);
      default:
        err_sys("not handled type");
        break;
    };
    return ret;
  }
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

void safe_free(void *p) {
  if (p != NULL) free(p);
}
