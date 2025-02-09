#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int zeiTabLen = 16;
int _gridsize = 5;

int zeichenTabelle[] = {32, 32, 32, 32, 32, 179, 180, 191, 192, 193, 194, 195, 196, 197, 217, 218};
                      /*     │    ┤    ┐    └    ┴    ┬    ├    ─    ┼    ┘    ┌ */

                /*   │  ┤  ┐  └  ┴  ┬  ├  ─  ┼  ┘  ┌ */
int nordMit[] =  {0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 1};
int nordOhne[] = {1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0};
                /*   │  ┤  ┐  └  ┴  ┬  ├  ─  ┼  ┘  ┌ */
int ostMit[] =   {0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0};
int ostOhne[] =  {1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1};
                /*   │  ┤  ┐  └  ┴  ┬  ├  ─  ┼  ┘  ┌ */
int suedMit[] =  {0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0};
int suedOhne[] = {1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1};
                /*   │  ┤  ┐  └  ┴  ┬  ├  ─  ┼  ┘  ┌ */
int westMit[] =  {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1};
int westOhne[] = {1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0};
                /*   │  ┤  ┐  └  ┴  ┬  ├  ─  ┼  ┘  ┌ */
				
struct kachel {
	int zeichen;
	int *optionNord;
	int *optionOst;
	int *optionSued;
	int *optionWest;
};

struct zelle {
	int colapsed;
	int zeichen;
	int optionen[16];
	int entropy;
};

typedef struct koordinaten {
	int r;
	int s;
} koor ;

void gitterFuellen(struct zelle *, int i);
void drawGitter(struct zelle gitter[]);
void initZelle(struct zelle *z);
void nachbarnReduzieren(struct zelle gitter[], int reihe, int spalte, struct kachel k[]);
koor niedrigsteEntropy(struct zelle gitter[]);

void kachelFuellen(struct kachel *k)
{
	switch (k->zeichen) {
		case 0: /*   */
		case 1:
		case 2:
		case 3:
		case 4:
			k->optionNord = &nordOhne[0];
			k->optionOst = &ostOhne[0];
			k->optionSued = &suedOhne[0];
			k->optionWest = &westOhne[0];
			break;
		case 5: /* │ */
			k->optionNord = &nordMit[0];
			k->optionOst = &ostOhne[0];
			k->optionSued = &suedMit[0];
			k->optionWest = &westOhne[0];
			break;
		case 6: /* ┤ */
			k->optionNord = &nordMit[0];
			k->optionOst = &ostOhne[0];
			k->optionSued = &suedMit[0];
			k->optionWest = &westMit[0];
			break;
		case 7: /* ┐ */
			k->optionNord = &nordOhne[0];
			k->optionOst = &ostOhne[0];
			k->optionSued = &suedMit[0];
			k->optionWest = &westMit[0];
			break;
		case 8: /* └ */
			k->optionNord = &nordMit[0];
			k->optionOst = &ostMit[0];
			k->optionSued = &suedOhne[0];
			k->optionWest = &westOhne[0];
			break;
		case 9: /* ┴ */
			k->optionNord = &nordMit[0];
			k->optionOst = &ostMit[0];
			k->optionSued = &suedOhne[0];
			k->optionWest = &westMit[0];
			break;
		case 10: /* ┬ */
			k->optionNord = &nordOhne[0];
			k->optionOst = &ostMit[0];
			k->optionSued = &suedMit[0];
			k->optionWest = &westMit[0];
			break;
		case 11: /* ├ */
			k->optionNord = &nordMit[0];
			k->optionOst = &ostMit[0];
			k->optionSued = &suedMit[0];
			k->optionWest = &westOhne[0];
			break;
		case 12: /* ─ */
			k->optionNord = &nordOhne[0];
			k->optionOst = &ostMit[0];
			k->optionSued = &suedOhne[0];
			k->optionWest = &westMit[0];
			break;
		case 13: /* ┼ */
			k->optionNord = &nordMit[0];
			k->optionOst = &ostMit[0];
			k->optionSued = &suedMit[0];
			k->optionWest = &westMit[0];
			break;
		case 14: /* ┘ */
			k->optionNord = &nordMit[0];
			k->optionOst = &ostOhne[0];
			k->optionSued = &suedOhne[0];
			k->optionWest = &westMit[0];
			break;
		case 15: /* ┌ */
			k->optionNord = &nordOhne[0];
			k->optionOst = &ostMit[0];
			k->optionSued = &suedMit[0];
			k->optionWest = &westOhne[0];
			break;
		default:
			break;
	}
}

int main(int argc, char** argv)
{
	if (argc > 1) {
		int temp = atoi(argv[1]);
		if (temp > 0)
			_gridsize = temp;
	}
	
	printf("%c", zeichenTabelle[0]);
	for (int i = 1; i < zeiTabLen; i++) {
		printf(" %c", zeichenTabelle[i]);
	}
	printf("\n\n");
	struct kachel k[16];
	for (int i = 0; i < zeiTabLen; i++) {
		k[i].zeichen = i;
		kachelFuellen(&k[i]);
	}
	
	struct zelle *gitter = malloc (_gridsize * _gridsize * sizeof(struct zelle));
	for (int i = 0; i < _gridsize * _gridsize; i++) {
		initZelle(&gitter[i]);
	}
	
	/* fuelle eine zufaellige zelle mit einem zufaelligen zeichen */
	srand(time(NULL));
	int r_r = rand() % (_gridsize);
	int r_s = rand() % (_gridsize);
	int r_val = rand() % zeiTabLen;
	
	gitterFuellen(&gitter[r_s + r_r * _gridsize], r_val);
	nachbarnReduzieren(gitter, r_r, r_s, k);
	/* drawGitter(gitter); */
	
	int fertig  = 0;
	koor aktOrt;
	while (!fertig) {
		aktOrt = niedrigsteEntropy(gitter);
		if (aktOrt.s == -1) break;
		if (gitter[aktOrt.s + aktOrt.r * _gridsize].colapsed)
			printf("Ins Leere gelaufen!\n");
		int gewOpt = rand() % gitter[aktOrt.s + aktOrt.r * _gridsize].entropy;
		
		int i, ka = -1;
		for (i = 0; i < zeiTabLen; i++) {
			if (gitter[aktOrt.s + aktOrt.r * _gridsize].optionen[i]) {
				ka++;
			}
			if (ka == gewOpt)
				break;
		}
		gitterFuellen(&gitter[aktOrt.s + aktOrt.r * _gridsize], i);
		nachbarnReduzieren(gitter, aktOrt.r, aktOrt.s, k);
		/* drawGitter(gitter); */
	}
	drawGitter(gitter);
	
	free(gitter);
	
	
	/* for (int i = 0; i < 12; i++) {
		printf("Zeichen %c\n", zeichenTabelle[k[i].zeichen]);
		printf("Nord:\n");
		for (int j = 0; j< 12; j++) {
			if (k[i].optionNord[j] == 1)
				printf(" %c", zeichenTabelle[j]);
		}
		printf("\nOst:\n");
		for (int j = 0; j< 12; j++) {
			if (k[i].optionOst[j] == 1)
				printf(" %c", zeichenTabelle[j]);
		}
		printf("\nSued:\n");
		for (int j = 0; j< 12; j++) {
			if (k[i].optionSued[j] == 1)
				printf(" %c", zeichenTabelle[j]);
		}
		printf("\nWest:\n");
		for (int j = 0; j< 12; j++) {
			if (k[i].optionWest[j] == 1)
				printf(" %c", zeichenTabelle[j]);
		}
		printf("\n\n");
	} */

	return 0;
}

void gitterFuellen(struct zelle *z, int i)
{
	z->colapsed = 1;
	z->zeichen = i;
	z->entropy = zeiTabLen + 1;
	return;
}

void drawGitter(struct zelle gitter[])
{
	int c;
	for (int re = 0; re < _gridsize; re++) {
		for (int sp = 0; sp < _gridsize; sp++) {
			if (gitter[re * _gridsize + sp].colapsed == 1) {
				if ((c = gitter[re * _gridsize + sp].zeichen) < 0 || c > zeiTabLen - 1)
					printf("*");
				else
				printf("%c", zeichenTabelle[gitter[re * _gridsize + sp].zeichen]);
			} else {
				printf(".");
			}
		}
		printf("\n");
	}
	return;	
}

void initZelle(struct zelle *z)
{
	z->colapsed = 0;
	z->zeichen = -1;
	for (int i = 0; i < zeiTabLen; i++)
		z->optionen[i] = 1;
	z->entropy = zeiTabLen;
}

void nachbarnReduzieren(struct zelle gitter[], int reihe, int spalte, struct kachel k[])
{
	int aktZ = gitter[spalte + reihe * _gridsize].zeichen;
	int aktOrt;
	if(!(aktZ >= 0 && aktZ < zeiTabLen))
		return;
	if (!((reihe - 1) < 0)) {
		aktOrt = (reihe - 1) * _gridsize + spalte;
		if (!gitter[aktOrt].colapsed) {
			gitter[aktOrt].entropy = 0;
			for (int i = 0; i < zeiTabLen; i++) {
				gitter[aktOrt].optionen[i] *= k[aktZ].optionNord[i];
				gitter[aktOrt].entropy += gitter[aktOrt].optionen[i];
			}
		}
	}
	if (!((reihe + 1) >= _gridsize)) {
		aktOrt = (reihe + 1) * _gridsize + spalte;
		if (!gitter[aktOrt].colapsed) {
			gitter[aktOrt].entropy = 0;
			for (int i = 0; i < zeiTabLen; i++) {
				gitter[aktOrt].optionen[i] *= k[aktZ].optionSued[i];
				gitter[aktOrt].entropy += gitter[aktOrt].optionen[i];
			}
		}
	}
	if (!((spalte - 1) < 0)) {
		aktOrt = reihe * _gridsize + spalte - 1;
		if (!gitter[aktOrt].colapsed) {
			gitter[aktOrt].entropy = 0;
			for (int i = 0; i < zeiTabLen; i++) {
				gitter[aktOrt].optionen[i] *= k[aktZ].optionWest[i];
				gitter[aktOrt].entropy += gitter[aktOrt].optionen[i];
			}
		}
	}
	if (!((spalte + 1) >= _gridsize)) {
		aktOrt = reihe * _gridsize + spalte + 1;
		if (!gitter[aktOrt].colapsed) {
			gitter[aktOrt].entropy = 0;
			for (int i = 0; i < zeiTabLen; i++) {
				gitter[aktOrt].optionen[i] *= k[aktZ].optionOst[i];
				gitter[aktOrt].entropy += gitter[aktOrt].optionen[i];
			}
		}
	}
	return;
}

koor niedrigsteEntropy(struct zelle gitter[])
{
	koor ort;
	ort.s = -1;
	ort.r = -1;
	int minEntropy = zeiTabLen + 1;
	for (int reihe = 0; reihe < _gridsize; reihe++) {
		for (int spalte = 0; spalte < _gridsize; spalte++) {
			if (gitter[spalte + reihe * _gridsize].colapsed == 0) {
				if (gitter[spalte + reihe * _gridsize].entropy < minEntropy) {
					minEntropy = gitter[spalte + reihe * _gridsize].entropy;
					ort.r = reihe;
					ort.s = spalte;
				}
			}
		}
	}
	return ort;
}