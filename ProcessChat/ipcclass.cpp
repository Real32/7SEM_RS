#include "ipcclass.h"

IPCClass::IPCClass()
{
    shm_block = new shm_type;
    msg_block = new msg_type;
    msg_recBL = new msg_type;
    sops = new sembuf;
    //sem_create();
}

IPCClass::~IPCClass()
{

}

void IPCClass::shmemory_create()
{
    sem_create();
    if((shmID = shmget(SHM_KEY, sizeof(struct shm_type), IPC_CREAT|IPC_EXCL|0666)) == -1) /* Open the shared memory segment - create if necessary */
       {
          qDebug()<<"Shared memory segment exists - opening as a client\n";
//          shm_block->cl_count++;
//          shm_block->cl_pid[shm_block->cl_count] = getpid();
          /* Segment probably already exists - try as a client */
          if((shmID = shmget(SHM_KEY, sizeof(struct shm_type), 0)) == -1)
          {
             qDebug()<<"shget error";
          }
       }
       else
       {
           qDebug()<<"Creating new shared memory segment\n";
//           shm_block->cl_count = 0;
//           shm_block->cl_pid[shm_block->cl_count] = getpid();
       }

//       shm_block = (struct shm_type *)shmat(shmID, 0, 0);
       if(shm_block==(struct shm_type*)(-1))
       {
            qDebug()<<"shmat error";
       }

}

void IPCClass::write_toSHM()
{

    sops[0].sem_op = -1;
    sops[1].sem_op = 1;
    semop(semID, (struct sembuf*) &sops[1], 1);
    //semop(semID, sops, 2);
    semop(semID, (struct sembuf*) &sops, 1);
    shm_block = (struct shm_type *)shmat(shmID, 0, 0);

    shm_block->cl_pid[shm_block->cl_index] = getpid();
    shm_block->cl_index++;
    shm_block->cl_count++;
    sops[1].sem_op = 1;
    semop(semID, (struct sembuf*) &sops[1], 1);
}

void IPCClass::read_fromSHM()
{

    sops[0].sem_op = -1;
    sops[1].sem_op = 1;
    semop(semID, (struct sembuf*) &sops[1], 1);

    qDebug()<<"Clients " << shm_block->cl_count;
    qDebug()<<"CURRENT INDX" << shm_block->cl_index;
    for(int i = 0; i < CLCOUNT; i++)
    {
        qDebug()<<"PID_IN_SHM : " << i << shm_block->cl_pid[i] << endl;
    }

}


int IPCClass::get_SHMpid(int index)
{
    return shm_block->cl_pid[index];
}

void IPCClass::set_SHMpid(int index, int value)
{
    shm_block->cl_pid[index] = value;
}

int IPCClass::get_clcount()
{
    return shm_block->cl_count;
}

void IPCClass::set_clcount(int count)
{
    shm_block->cl_count = count;
}

int IPCClass::get_clindex()
{
    return shm_block->cl_index;
}

void IPCClass::close_SHM()
{
    shmdt((void *) shm_block);
    shmctl(shmID, IPC_RMID, 0);
    qDebug()<<"shm destruct";
}

void IPCClass::msgQueu_create()
{
    if((msgID = msgget(MSG_KEY, 0666 | IPC_CREAT|IPC_EXCL))  == -1) /* Open msg queu - create if necessary */
    {
        qDebug()<<"msg queu exists - opening as a client\n";
        /* msg queu probably already exists - try as a client */
        if((msgID = msgget(MSG_KEY, 0666)) == -1)
        {
            qDebug()<<"msg error";
        }
    }
    else
    {
        qDebug()<<"Creating new msg queu\n";
    }
}

void IPCClass::msg_send(int Spid, QString nickN, QString message)
{
    msg_block->mtype = Spid;
    msg_block->snd_pid = Spid;


    strcpy (msg_block->nickname, nickN.toLatin1());
    strcpy (msg_block->message, message.toLatin1());
    qDebug() << Q_FUNC_INFO << msg_block->mtype << msg_block->snd_pid << msg_block->nickname << msg_block->message;

    msgsnd(msgID, msg_block, sizeof(struct msg_type) - sizeof(long), IPC_NOWAIT);

   // qDebug()<<msg_block->snd_pid<<" "<<msg_block->nickname<<" "<<msg_block->message;
}

QString IPCClass::msg_recieveMessage()
{
    QString RECmessage;
//    struct msg_type msg_recBL;
    char empt[512] = {};    // yes, it's fuuuuuuuuuuuuuuuuuuuuuuuuu
    QString RECnickname;
//    struct msg_type msg_recBL;
    strcpy(msg_recBL->message, empt);
    strcpy(msg_recBL->nickname, empt);

    if (msgrcv(msgID, msg_recBL, sizeof(struct msg_type) - sizeof(long), getpid(), MSG_NOERROR | IPC_NOWAIT) != -1)
    {

    }
    RECmessage = msg_recBL->message;
    qDebug () << Q_FUNC_INFO << getpid() << RECmessage;
    RECnickname = msg_recBL->nickname;
    qDebug () << Q_FUNC_INFO << getpid() << RECnickname;


    return RECnickname+RECmessage;
    //qDebug()<<"Server responded: " << msg_block->message;
}

QString IPCClass::msg_recieveNickname()
{
    QString RECnickname;
//    struct msg_type msg_recBL;
    char empt[512] = {};    // yes, it's fuuuuuuuuuuuuuuuuuuuuuuuuu
    strcpy(msg_recBL->nickname, empt);
    if (msgrcv(msgID, msg_recBL, sizeof(struct msg_type) - sizeof(long), getpid(), MSG_NOERROR | IPC_NOWAIT) != -1)
    {

    }
    RECnickname = msg_recBL->nickname;
    qDebug () << Q_FUNC_INFO << getpid() << RECnickname;

    return RECnickname;
    //qDebug()<<"Server responded: " << msg_block->message;
}
void IPCClass::close_msg()
{
    msgctl(msgID, IPC_RMID, 0);  // delete queu
    qDebug()<<"msg destruct";
}

void IPCClass::sem_create()
{

    if((semID = semget(SEM_KEY, 2, IPC_CREAT | IPC_EXCL  | 0660)  == -1))
    {
        qDebug()<<"msg queu exists - opening as a client\n";
        /* msg queu probably already exists - try as a client */
        if((semID = semget(SEM_KEY, 2, 0660)) == -1)
        {
            qDebug()<<"sem error";
        }
    }
    else
    {
        qDebug()<<"Creating new semaphores\n";
    }
    sops[0].sem_num = 0;
    sops[0].sem_flg = SEM_UNDO;
    sops[1].sem_num = 1;
    sops[1].sem_flg = SEM_UNDO;
}

void IPCClass::close_sem()
{
    semctl(semID, 2, IPC_RMID);
    qDebug()<<"sem destruct";
}
