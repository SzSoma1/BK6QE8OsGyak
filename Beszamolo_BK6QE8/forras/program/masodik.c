

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <math.h>

#define SHMKEY 60001L

int main()
{
	int shmid;		
	key_t key;		
	int size=512;		
	int shmflg;		
    FILE *in_file;
	FILE *out_file;
    struct vmi {
		int oldal1, oldal2, oldal3;
	} *segm;		

	key = SHMKEY;

	shmflg = 0;	

	if ((shmid=shmget(key, size, shmflg)) < 0) {
	    perror("Az shmget system-call sikertelen!\n");
	    exit(-1);
	}

	shmflg = 00666 | SHM_RND;	
	segm = (struct vmi *)shmat(shmid, NULL, shmflg); 
	if (segm == (void *)-1) {
		perror("Sikertelen attach!\n");
		exit(-1);
	}

    in_file = fopen("oldalak", "r");
    out_file = fopen("haromszog","w");
    int kerulet = 0;
    double terulet = 0;

    if (in_file == NULL)
    {
        printf("Can't open file for reading.\n");
    }

    else
    {
        fscanf(in_file, "%d", &segm->oldal1);
        fscanf(in_file, "%d", &segm->oldal2);
        fscanf(in_file, "%d", &segm->oldal3);

	if(segm->oldal1 < (segm->oldal2+segm->oldal3) && segm->oldal2 < (segm->oldal1+segm->oldal3)  && segm->oldal3 < (segm->oldal1+segm->oldal2) )
	{
		printf("Szerkeztheto 3szog \n");
		kerulet = segm->oldal1+ segm->oldal2 + segm->oldal3;
		int s = kerulet / 2;
		int teruletResz = s*(s-segm->oldal1)*(s-segm->oldal2)*(s-segm->oldal3); 
		terulet = sqrt(teruletResz);

		if (out_file == NULL)
		{
			printf("Can't open file for writing.\n");
		}else
		{
   			fprintf(out_file,"A kapott adatokbol: %d %d %d lehet haromszoget alkotni! \n Kerulete: %d \n Terulete: %f \n",segm->oldal1, segm->oldal2, segm->oldal3,kerulet,terulet);
   			fclose(out_file);
		}
	}

	else{
		if (out_file == NULL)
		{
			printf("Can't open file for writing.\n");
		}else
		{
			fprintf(out_file,"-1");
			fclose(out_file);
			}
		}
        fclose(in_file);
    }

	
	shmdt(segm);

	exit(0);
}
