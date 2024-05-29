#include "specs.h"

int main() {
  key_t client_key = ftok("/bin/rm", getpid());
  int client_msgqid;
  if (client_key == -1) {
    perror("ftok");
    exit(1);
  }
  client_msgqid = msgget(client_key, 0666 | IPC_CREAT);
  if (client_msgqid == -1) {
    perror("msgget");
    exit(1);
  }

  key_t server_key = ftok("/bin/ls", 's');
  int server_msgqid = msgget(server_key, 0666);
  if (server_msgqid == -1) {
    perror("msgget");
  }

  msgbuf msg;
  msg.mtype = INIT;
  sprintf(msg.mtext, "%d", client_key);
  if (msgsnd(server_msgqid, &msg, sizeof(msg.mtext), 0) == -1) {
    perror("msgsnd: failed to send INIT message");
    exit(1);
  }

  if (msgrcv(server_msgqid, &msg, sizeof(msg.mtext), INIT, 0) == -1) {
    perror("msgrcv: failed to receive client_id");
  }
  int client_id = atoi(msg.mtext);

  pid_t pid = fork();
  if (pid == -1) {
    perror("fork");
    exit(1);
  }
  if (pid == 0) { 
    while (1) {
      if (msgrcv(client_msgqid, &msg, sizeof(msg.mtext), 0, 0) == -1) {
        perror("msgrcv");
        continue;
      }
      printf("Client ID: %d Message received: %s\n", client_id, msg.mtext);
    }
  } else { 
    char buffer[MAX_MSG_SIZE];
    while (1) {
      fgets(buffer, sizeof(buffer), stdin);
      buffer[strcspn(buffer, "\n")] = 0;
      if (strcmp(buffer, "exit") == 0) {
        msgctl(client_msgqid, IPC_RMID, NULL);
        kill(pid, SIGKILL); 
        exit(0);
      }
      strcpy(msg.mtext, buffer);
      if (msgsnd(server_msgqid, &msg, sizeof(msg.mtext), 0) == -1) {
        perror("msgsnd");
        exit(1);
      }
    }
  }
  return 0;
}
