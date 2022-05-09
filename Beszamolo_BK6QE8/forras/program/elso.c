

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHMKEY 60001L 

int main()
{
	int shmid;		
	key_t key;		
	int size=512;		
	int shmflg;		
    int rtn;		
	key = SHMKEY;
    struct shmid_ds shmid_ds, *buf; 
	buf = &shmid_ds;	
    struct vmi {
		int oldal1, oldal2, oldal3;
		} *segm;                
	shmflg = 0;
	if ((shmid=shmget(key, size, shmflg)) < 0) {
	   printf("Nincs meg szegmens! Keszitsuk el!\n");
	   shmflg = 00666 | IPC_CREAT;
	   if ((shmid=shmget(key, size, shmflg)) < 0) {
	      perror("Az shmget() system-call sikertelen!\n");
	      exit(-1);
	   }
	} else printf("Van mar ilyen shm szegmens!\n");

	printf("\nAz shm szegmens azonositoja %d: \n", shmid);
                                        
	shmflg = 00666 | SHM_RND;	
	segm = (struct vmi *)shmat(shmid, NULL, shmflg); 
	if (segm == (void *)-1) {
		perror("Sikertelen attach!\n");
		exit(-1);
	}
	int cmd; 
	do
	{
		printf("\nAdd meg a parancs szamat:\n");
		printf("0. IPC_STAT (status)\n");
		printf("1. IPC_RMID (torles)\n> ");
		scanf("%d",&cmd);
	} while (cmd < 0 || cmd > 1);

	switch (cmd)
	{
	    case 0:
		rtn = shmctl(shmid, IPC_STAT, buf);
		printf("\nAz shm szegmens azonositoja %d: \n", shmid);
		printf("Szegmens merete: %d\n",buf->shm_segsz);
		printf("Utolso shmop()-os processz pid-je: %d\n",buf->shm_lpid);
		break;

	    case 1:
	    shmdt(segm);
		rtn = shmctl(shmid, IPC_RMID, NULL);
		printf("Szegmens torolve. Hibakod: %d\n", rtn);
	}

	exit(0);
}
