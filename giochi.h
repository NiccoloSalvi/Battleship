#define N 10
#define NAVE 2
#define MANCATO 3
#define T 1

void stampa_campo (char matrice[N][N]) {
  int a,i;
  printf("   ");
  for (i=0;i<N;i++) printf("_____");
  printf("\n");
  for (a=0;a<N;a++) {
    printf("%c ",a+65);
    for (i=0;i<N;i++) {
      if (matrice[a][i]==0) printf("|____");
      if (matrice[a][i]==1) printf("|__C_");
      if (matrice[a][i]==2) printf("|__O_");
      if (matrice[a][i]==3) printf("|__M_");
    }
    printf("|\n");
  }
  printf("    1");
  for (i=2;i<=N;i++) printf("    %d",i);
  printf("\n");
}

void azzeramento_campo (char matrice[N][N]) {
  for (int a=0;a<N;a++) for (int i=0;i<N;i++) matrice[a][i]=0;
}

void stampa_nave_vert (int b,int a) {
  int c,i;
  for (c=0;c<b;c++) {
    if (c!=0) printf("\t\t\t ___\n");
    else printf("\n\tVert. %d caselle  ___\n",a);
    printf("\t\t\t|_*_|\n");
    for (i=0;i<a-1;i++) printf("\t\t\t|___|\n");
  }
}

void stampa_nave_oriz (int b,int a) {
  int i,c;
  for (c=0;c<b;c++) {
    if (c!=0) printf("\t\t\t ");
    else printf("\n\tOriz. %d caselle\t ",a);
    for (i=0;i<a;i++) printf("____");
    printf("\n\t\t\t|_*_|");
    for (i=0;i<a-1;i++) printf("___|");
    printf("\n");
  }
  printf("\n");
}

int input_vert_oriz () {
  char a;
  do {
    printf("\n\tVert/Oriz?: ");
    scanf(" %c",&a);
  } while (a!='O' && a!='V');
  return a;
}

int input_caselle (char b) {
  int a;
  if (b=='V') {
    do {
      printf("\tCaselle: ");
      scanf("%d",&a);
    } while (a!=4 && a!=2 && a!=1);
  } else {
    do {
      printf("\tCaselle: ");
      scanf("%d",&a);
    } while (a!=2 && a!=3);
  }
  return a;
}

int scelta_nave (int navi[5],int celle,int scelta) {
  if (scelta=='O' && celle==2) celle=0;
  if (navi[celle]<1) return 1;
  else {
    navi[celle]=navi[celle]-1;
    return 0;
  }
}

int inserimento_coordX() {
  int a;
  do {
    scanf("%d",&a);
  } while (a<0 || a>10);
  return a-1;
}

char inserimento_coordY() {
  char a;
  do {
    scanf(" %c",&a);
  } while (a<65 || a>74);
  return a-65;
}

int posizionamento_navi (char coordY,int coordX,char scelta,int celle,int *in_campo,int *pos_occupata,char campo[N][N]) {
  int i;
  if (scelta=='V') {
    i=-1,*pos_occupata=0,*in_campo=0;
    if (celle+coordY>N) *in_campo=1;
    while (i<=celle && *pos_occupata==0) {
      if (coordX!=0) if (campo[coordY+i][coordX-1]!=0 && coordY+i<N && coordY+i>=0) *pos_occupata=1;
      if (coordX!=9) if (campo[coordY+i][coordX+1]!=0 && coordY+i<N && coordY+i>=0) *pos_occupata=1;
      if (campo[coordY+i][coordX]!=0 && coordY+i<N && coordY+i>=0) *pos_occupata=1;
      i++;
    }
    if (*pos_occupata==0 && *in_campo==0) for (i=0;i<celle;i++) campo[coordY+i][coordX]=NAVE;
  } else {
    i=-1,*pos_occupata=0,*in_campo=0;
    if (celle+coordX>N) *in_campo=1;
    while (i<=celle && *pos_occupata==0) {
      if (coordY!=0) if (campo[coordY-1][coordX+i]!=0 && coordX+i<N && coordX+i>=0) *pos_occupata=1;
      if (coordY!=9) if (campo[coordY+1][coordX+i]!=0 && coordX+i<N && coordX+i>=0) *pos_occupata=1;
      if (campo[coordY][coordX+i]!=0 && coordX+i<N && coordX+i>=0) *pos_occupata=1;
      i++;
    }
    if (*pos_occupata==0 && *in_campo==0) for (i=0;i<celle;i++) campo[coordY][coordX+i]=NAVE;
  }
}

int affondato (char coordY,int coordX,char campo_pos[N][N],char campo_act[N][N]) {
    int celle_vert=1,celle_oriz=1,i;
    campo_act[coordY][coordX]=NAVE;
    campo_pos[coordY][coordX]=1;
    i=1;
    while (campo_pos[coordY-i][coordX]!=0 && campo_pos[coordY-i][coordX]!=3 && 0<coordY-i<N) {
      if (campo_pos[coordY-i][coordX]==1) celle_vert++;
      else celle_vert=0;
      i++;
    }
    i=1;
    while (campo_pos[coordY+i][coordX]!=0 && campo_pos[coordY+i][coordX]!=3 && 0<coordY+i<N) {
      if (campo_pos[coordY+i][coordX]==1) celle_vert++;
      else celle_vert=0;
      i++;
    }
    i=1;
    while (campo_pos[coordY][coordX-i]!=0 && campo_pos[coordY][coordX-i]!=3 && 0<coordX-i<N) {
      if (campo_pos[coordY][coordX-i]==1) celle_oriz++;
      else celle_oriz=0;
      i++;
    }
    i=1;
    while (campo_pos[coordY][coordX+i]!=0 && campo_pos[coordY][coordX+i]!=3 && 0<coordX+i<N) {
      if (campo_pos[coordY][coordX+i]==1) celle_oriz++;
      else celle_oriz=0;
      i++;
    }
    if (celle_vert==4) return 4;
    if (celle_oriz==3) return 3;
    if (celle_vert==2) return 2;
    if (celle_oriz==2) return 5;
    if (celle_vert==1 && celle_oriz==1) return 1;
}
