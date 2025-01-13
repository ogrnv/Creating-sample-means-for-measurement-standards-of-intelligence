#include <stdio.h>
#include <stdlib.h>
#include <sys/random.h>
#include <stdint.h>
#include <time.h>

#define tmax 5000	//max number of tests
#define rmax 100000	//max number of rounds in 1 test

//all input as parametres
uint32_t
tsts,	// 1) the number of tests up to tmax
rounds,	// 2) the number of rounds in 1 test up to rmax
stp;	// 3) steps in 1 round
unsigned char
hm,		// 4) size of a side of square board
kcb,	// 5) how many of types of chips are placed on the board
nub,	// 6) number of chips 42
dbg,	// 7) print debug info on console
emb;    // the number of empty sells 22=64-42
unsigned char Csb[16][16], n5x, n5[5], TC[16][16], ina, jna, hmb, iko, jko, kp, ox5=0, bc, ca, uu=0, n=0;

//0-start address 1- finish one:
signed char x0, x1, y00, y01, y2;
uint32_t
icr,
qn=0,			//number of finished lines >4 chips long
l, im1, im2=0, med;
float
mn=0.0,			//moves number
tb_mn[tmax*rmax],	//tb of mn i.e. moves made in every round
tst_mn=0.0,
tb_av[tmax];	//tb of means of tests
//tb_med[tmax];	//tb of medians of tests

int main(int argc, char** argv)
{
// Check the number of arguments passed
if(argc<8)
    {
    printf("Error: must be 7 arguments, not %d\n", argc - 1);
    return(1);
    }
tsts=atoi(argv[1]); rounds=atoi(argv[2]); stp=atoi(argv[3]);
hm=atoi(argv[4]); kcb=atoi(argv[5]); nub=atoi(argv[6]);
dbg=atoi(argv[7]);
printf("%d %d %d %d %d %d %d\n", tsts, rounds, stp, hm, kcb, nub, dbg);

emb=hm*hm - nub;

    time_t seconds; seconds = time(NULL);

	char nmf[100];
	sprintf(nmf, "raw_%dx%d_%d-%dx%d-%d-%d_%ld\0", tsts, rounds, stp, hm,hm,kcb,nub,seconds);
	FILE* f=fopen(nmf,"wb");
//the number of moves in each round is written to this file,
//i.e. the total moves of the steps,
//example 1step-2moves, 2step-3moves will be written 5 (in 4 bytes)
//this is NOT a mean file, it's data with a long right tail
// IMPORTANT!!! in the merged files, the parts of the names stp, hm, kcb, nub must match!
	int sizd = sizeof(float);

uint32_t random(uint32_t min, uint32_t max) {
    return arc4random_uniform(max - min + 1) + min;
}
void dbgp(){
int8_t i, j;
for (i = 0; i < hm; i += 1){
	for (j = 0; j < hm; j += 1)	printf("%d", Csb[i][j]);
printf("\n");
}
}
void fz(int8_t fzx, int8_t fzy){
 if((fzx>0)&&(Csb[fzx-1][fzy]==0)&&(TC[fzx-1][fzy]==0))
   {TC[fzx-1][fzy]=1; fz((fzx-1),fzy);}
 if((fzx<hm-1)&&(Csb[fzx+1][fzy]==0)&&(TC[fzx+1][fzy]==0))
   {TC[fzx+1][fzy]=1; fz((fzx+1),fzy);}
 if((fzy>0)&&(Csb[fzx][fzy-1]==0)&&(TC[fzx][fzy-1]==0))
   {TC[fzx][fzy-1]=1; fz(fzx,(fzy-1));}
 if((fzy<hm-1)&&(Csb[fzx][fzy+1]==0)&&(TC[fzx][fzy+1]==0))
   {TC[fzx][fzy+1]=1; fz(fzx,(fzy+1));}
}

void ver(int8_t colr, int8_t i, int8_t j){
ina=i; jna=j;
while((ina-1) >= 0){
ina--;
if(colr != Csb[ina][j]){ina++; break;}
}
iko=i;
while((iko+1) < hm){
iko++;
if(colr != Csb[iko][j]){iko--; break;}
}
hmb=iko-ina+1; // line length
if (hmb>4) {ox5=1;}
}
//-----------------------------------------
void hor(int8_t colr, int8_t i, int8_t j){
jna=j; ina=i;
while((jna-1) >= 0){
jna--;
if(colr != Csb[i][jna]){jna++; break;}
}
jko=j;
while((jko+1) < hm){
jko++;
if(colr != Csb[i][jko]){jko--; break;}
}
hmb=jko-jna+1;
if (hmb>4) {ox5=1;}
}
//-----------------------------------------
void nak(int8_t colr, int8_t i, int8_t j){
ina=i; jna=j;
while((ina-1) >= 0 && (jna-1) >= 0){
ina--; jna--;
if(colr != Csb[ina][jna]){ina++; jna++; break;}
}
iko=i; jko=j;
while((iko+1) < hm && (jko+1) < hm){
iko++; jko++;
if(colr != Csb[iko][jko]){iko--; jko--; break;}
}
hmb=jko-jna+1;
if (hmb>4) {ox5=1;}
}
//-----------------------------------------
void nkl(int8_t colr, int8_t i, int8_t j){
ina=i; jna=j;
while((ina+1) < hm && (jna-1) >= 0){
ina++; jna--;
if(colr != Csb[ina][jna]){ina--; jna++; break;}
}
iko=i; jko=j;
while((iko-1) >= 0 && (jko+1) < hm){
iko--; jko++;
if(colr != Csb[iko][jko]){iko++; jko--; break;}
}
hmb=ina-iko+1;
if (hmb>4) {ox5=1;}
}
void ValuX(int8_t colr, int8_t i, int8_t j)
{

int b, e, n;

int32_t an;
int tt[4];
for (e = 0; e < 4; e++) tt[e] = -1;
    e = 0;
while (e < 4) {
		an=arc4random();
        n = 0;
        while (n < 16) {
            b = 3 & an;  //select 2 bits from the right
            if (tt[b] == -1) {
                tt[b] = e;
                e++;
                if (e == 4) break;
            }
            an = an >> 2;  //shift 2 bits to the right
            n++;
}
}
//trying to find a line in the order defined in tt
for (e=0; e<4; e++){ // e - order number
b=1;
n=0;
while(n<4){
/*looking for order number e
n - type number | - \ /
look for a certain type n 5 in a line*/
	if(tt[n]==e) {
	switch (n) {
  	case 0: ver(colr, i, j); break;
	case 1: hor(colr, i, j); break;
	case 2: nak(colr, i, j); break;
	case 3: nkl(colr, i, j); break;
	}
	}
	if(ox5>0 && (qn+1)<stp) {// not needed before newdesk
	if(hmb>4){//how many options for removal from a point with a min value of x
		if(hmb==5){bc=0;}
		else{
		bc=random(0, hmb - 5); //offset from point with min value of x
		}
	// delete 5 then add 5
	if(dbg==1) {printf("the number {0,1,2,3} of del type | - \\ / is %d\nbefore del:\n", n); dbgp(); printf("\n");}
	int8_t k=0;
	while(k<5){
	// zeroes 5 cells
	if(n==0){Csb[ina+bc+k][jna]=0;}
	if(n==1){Csb[ina][jna+bc+k]=0;}
	if(n==2){Csb[ina+bc+k][jna+bc+k]=0;}
	if(n==3){Csb[ina-bc-k][jna+bc+k]=0;}
	k=k+1;
	}
int hmze=0, fri[hm*hm], frj[hm*hm];
for (i = 0; i < hm; i += 1){
	for (j = 0; j < hm; j += 1){
		if(Csb[i][j] == 0) {fri[hmze]=i; frj[hmze]=j; hmze++;}
	}
}
// add 5 chips
for (i = 0; i < 5; i++){
		bc=random(0, hmze - 1); // take an empty cell
		int ic, jc;
		ic=fri[bc]; jc=frj[bc];
		Csb[ic][jc]=n5[i];
//change table of free cells last--> in place of bc and hmze--
		fri[bc]=fri[hmze-1]; frj[bc]=frj[hmze-1]; hmze = hmze - 1;
}
		} //if(hmb>4
		n=4; // was found > 4
	}
	else {if(ox5>0) n=4; else n++;}
}
if(ox5==1) e=4;
}
}//ValuX  end
void newdesk(){
int8_t i, j;
for (i = 0; i < hm; i += 1){
	for (j = 0; j < hm; j += 1){
		TC[i][j] = 0;
		Csb[i][j]=random(1, kcb);
	}
}
//empty emb cells
n=0;
while(n<emb){
	i=random(0, hm - 1);
	j=random(0, hm - 1);
	if(Csb[i][j]>0){Csb[i][j] = 0; n++;}
}
for (i = 0; i < 5; i++){
	n5[i]=random(1, kcb);
}
if(dbg==1) {printf("new\n"); dbgp();}
}
void vals(){
for (l = 0; l < rounds; l++) tb_mn[l]=0.0;
l=0;
}
newdesk();

uint32_t tsg, tst;
for(tsg=0; tsg<tsts; tsg++){
	vals();	mn=0.0;
for(tst=0; tst<rounds; tst++){
while(qn<stp){
uu=0, n=0; ox5=0;
while(uu==0){//get the right move
x0=random(0, hm-1);y00=random(0, hm-1);x1=random(0, hm-1);y01=random(0, hm-1);
if(Csb[x0][y00]>0&&Csb[x1][y01]==0){
//check accessibility FA from SA
for (int8_t aa = 0; aa < hm; aa += 1)
    for (int8_t bb = 0; bb < hm; bb += 1)TC[aa][bb] = 0;
fz(x0,y00);
if(TC[x1][y01]==1){uu=1;}
}
}
Csb[x1][y01]=Csb[x0][y00]; Csb[x0][y00]=0;
ValuX(Csb[x1][y01],x1,y01);
mn++; tst_mn++;
if(dbg==1) printf("%d %d %d %d %f\n",x0,y00,x1,y01,mn);
if(ox5>0)
{
	qn++;
	if(qn<stp) {
		n=0;
		while(n<5){n5[n]=random(1, kcb);n++;}
		}
}
if(dbg==1) dbgp();
}//here a round ends
qn=0; newdesk();
tb_mn[l]=tst_mn; l++;
tst_mn=0.0;
} //rounds

fwrite(tb_mn,rounds,sizd,f); // write rounds*sizd bytes from the buffer

tb_av[tsg]=mn/((float)(rounds*stp));

} //tsts
printf("%f", tb_av[0]);
for (uint32_t i = 1; i < tsts; i++){ printf(",%f", tb_av[i]);}
printf("\n");
fclose(f);
    return 0;
}

