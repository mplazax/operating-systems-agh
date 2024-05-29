#include "specs.h"

client clients[MAX_CLIENTS];

int main() {
  for (int i = 0; i < MAX_CLIENTS; i++) {
    clients[i].id = -1;
    clients[i].msgqid = -1;
  }

  int clients_active = 0;

  key_t server_key = ftok("/bin/ls", 's');
  if (server_key == -1) {
    perror("ftok");
    exit(1);
  }

  int server_msgqid = msgget(server_key, 0666 | IPC_CREAT);
  if (server_msgqid == -1) {
    perror("msgget");
    exit(1);
  }

  printf("Server queue created successfully\n");

  msgbuf msg;

  while (1) {
    printf("Starting\n");
    if (msgrcv(server_msgqid, &msg, sizeof(msg.mtext), INIT, 0) == -1) {
      perror("msgrcv");
      continue;
    }

    printf("Server received message: %s\n", msg.mtext);
    printf("msg type: %ld\n", msg.mtype);

    if (msg.mtype == INIT) {
      if (clients_active < MAX_CLIENTS) {
        clients[clients_active].id = clients_active;
        int client_msgqid = msgget(atoi(msg.mtext), 0666);
        if (client_msgqid == -1) {
          perror("msgget: error adding new client");
        } else {
          clients[clients_active].msgqid = client_msgqid;
          printf("Client %d added successfully\n", clients_active);
          sprintf(msg.mtext, "%d", clients_active);
          msgsnd(clients[clients_active].msgqid, &msg, sizeof(msg.mtext), 0);
          clients_active++;
        }
      } else {
        fprintf(stderr, "Maximum number of clients reached.\n");
      }
    } else if (msg.mtype == STANDARD) {
      for (int i = 0; i < clients_active; i++) {
        if (msgsnd(clients[i].msgqid, &msg, sizeof(msg.mtext), 0) == -1) {
          perror("msgsnd: error sending message to client");
        }
      }
    } else {
      fprintf(stderr, "msgrcv: wrong message type\n");
    }
  }
  return 0;
}
