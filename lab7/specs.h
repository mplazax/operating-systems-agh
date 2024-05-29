#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <sys/stat.h>

#define MAX_MSG_SIZE 128

#define MAX_CLIENTS 10

#define INIT 1
#define STANDARD 2
typedef struct {
  long mtype;
  char mtext[MAX_MSG_SIZE];
} msgbuf;

typedef struct {
  long id;
  int msgqid;
} client;
