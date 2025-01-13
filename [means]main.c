#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
//#include <time.h>

unsigned long
i, j,
//arguments:
tsts,	// 1) the number of tests
rounds,	// 2) the number of rounds in 1 test
stp;    // 3) steps in 1 round

float mn,	//  moves made 1 test
midf, sum;

int main(int argc, char** argv)
{
// Check the number of arguments passed
if(argc<4)
    {
    printf("Error: must be 4 arguments, not %d\n", argc - 1);
    return(1);
    }
	char nmr[300],nmw[500];
tsts=atoi(argv[1]); rounds=atoi(argv[2]); stp=atoi(argv[3]);
sprintf(nmr, "%s\0", argv[4]);
printf("%ld %ld %ld %s\n", tsts, rounds, stp, nmr);
    //time_t seconds; seconds = time(NULL);
	sprintf(nmw, "means_%ldt_%ldr_%lds_%s\0", tsts, rounds, stp, nmr);
	FILE* f1=fopen(nmr,"rb");
	FILE* f2=fopen(nmw,"wb");

unsigned long sz=0L;

sum=0.0;
fseek(f1, 0L, SEEK_END);
sz = ftell(f1);
rewind(f1);
if(4*tsts*rounds > sz) {printf("Error: the file size %ld is less than 4*(product of the first two arguments)\n", sz); return(1);}
else
if(4*tsts*rounds < sz) {printf("Warning: the file size %ld is more than 4*(product of the first two arguments)\n", sz);}
	for(i=0L; i<tsts; i++){
        for(j=0L; j<rounds; j++){
        fread(&mn,4,1,f1);
        sum=sum+mn;
        }
        midf=sum/((float)(rounds*stp));
//        printf("%f\n", sum);
        sum=0.0;
        fwrite(&midf,4,1,f2); // write 4 bytes from the buffer
	}
fclose(f1); fclose(f2);
    return 0;
}
