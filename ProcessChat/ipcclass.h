#ifndef IPCCLASS_H
#define IPCCLASS_H
#include <sys/types.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <QObject>
#include <QString>
#include <QDebug>

#define SHM_KEY 1911
#define MSG_KEY 2900
#define SEM_KEY 2548
#define CLCOUNT 32

struct shm_type{
    int cl_pid[CLCOUNT];
    int cl_count;
    int cl_index;
};

struct msg_type{
    long mtype;
    int snd_pid;
    char nickname[32];
    char message[512];
};

class IPCClass
{
public:
    IPCClass();
    ~IPCClass();
    void shmemory_create();
    void write_toSHM();
    void read_fromSHM();
    void close_SHM();
    int get_SHMpid(int index);
    void set_SHMpid(int index, int value);
    int get_clcount();
    void set_clcount(int count);
    int get_clindex();

    void msgQueu_create();
    void msg_send(int Spid, QString nickN, QString message);
    QString msg_recieveMessage();
    QString msg_recieveNickname();

    void close_msg();

    void sem_create();

    void close_sem();

private:
    int shmID;
    int msgID;
    int semID;
    struct shm_type *shm_block;
    struct msg_type *msg_block;
    struct msg_type *msg_recBL;
    struct sembuf *sops;
};

#endif // IPCCLASS_H
