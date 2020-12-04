#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "giochi.h"

int main () {
  char campo_pos_PL1[N][N],campo_pos_PL2[N][N],coordY;
  char campo_act_PL1[N][N],campo_act_PL2[N][N],scelta;
  int navi[5],a,i,celle,coordX,turno=1,err=0;
  int in_campo,pos_occupata,navi_finite;
  int navi_rimaste_PL1=0,navi_rimaste_PL2=0;
  for (i=0;i<5;i++) navi[i]=0;
  navi[4]=0,navi[3]=1,navi[2]=0,navi[1]=1,navi[0]=0;
  for (i=0;i<5;i++) navi_rimaste_PL1=navi_rimaste_PL1+navi[i];
  navi_rimaste_PL2=navi_rimaste_PL1;
  azzeramento_campo(campo_pos_PL1);
  azzeramento_campo(campo_pos_PL2);
  azzeramento_campo(campo_act_PL1);
  azzeramento_campo(campo_act_PL2);
  printf("\t\tBATTAGLIA NAVALE\n");
  printf("\n\tPlayer 1, schierale le tue navi!\n\n");
  stampa_campo(campo_pos_PL1);
  do {
    stampa_nave_vert(navi[4],4);
    stampa_nave_oriz(navi[3],3);
    stampa_nave_oriz(navi[0],2);
    stampa_nave_vert(navi[2],2);
    stampa_nave_vert(navi[1],1);
    do {
      if (navi_finite==1) printf("\n\tHai gia utilizzato quella nave, piazzane un'altra!\n");
      else printf("\n\n\tQuale nave vuoi inserire?\n");
      scelta=input_vert_oriz();
      celle=input_caselle(scelta);
      navi_finite=scelta_nave(navi,celle,scelta);
    } while (navi_finite==1);
    do {
      if (pos_occupata==1) printf("\n\tPosizione gia occupata, reinserisci la coordinata: ");
      else if (in_campo==1) printf("\n\tCosi uscirai dal campo, reinserisci la coordinata: ");
      else printf("\n\tInserisci la coordinata: ");
      coordY=inserimento_coordY();
      coordX=inserimento_coordX();
      posizionamento_navi(coordY,coordX,scelta,celle,&in_campo,&pos_occupata,campo_pos_PL1);
    } while (pos_occupata==1 || in_campo==1);
    stampa_campo(campo_pos_PL1);
  } while (navi[0]>0 || navi[1]>0 || navi[2]>0 || navi[3]>0 || navi[4]>0);
  printf("\n\n");
  sleep(T);
  system("cls");
  printf("\n\tPlayer 2, ora tocca a te!\n\n");
  stampa_campo(campo_pos_PL2);
  navi[4]=0,navi[3]=1,navi[2]=0,navi[1]=1,navi[0]=0;
  do {
    stampa_nave_vert(navi[4],4);
    stampa_nave_oriz(navi[3],3);
    stampa_nave_oriz(navi[0],2);
    stampa_nave_vert(navi[2],2);
    stampa_nave_vert(navi[1],1);
    do {
      if (navi_finite==1) printf("\n\tHai gia utilizzato quella nave, piazzane un'altra!\n");
      else printf("\n\n\tQuale nave vuoi inserire?\n");
      scelta=input_vert_oriz();
      celle=input_caselle(scelta);
      navi_finite=scelta_nave(navi,celle,scelta);
    } while (navi_finite==1);
    do {
      if (pos_occupata==1) printf("\n\tPosizione gia occupata, reinserisci la coordinata: ");
      else if (in_campo==1) printf("\n\tCosi uscirai dal campo, reinserisci la coordinata: ");
      else printf("\n\tInserisci la coordinata: ");
      coordY=inserimento_coordY();
      coordX=inserimento_coordX();
      posizionamento_navi(coordY,coordX,scelta,celle,&in_campo,&pos_occupata,campo_pos_PL2);
    } while (pos_occupata==1 || in_campo==1);
    stampa_campo(campo_pos_PL2);
  } while (navi[0]>0 || navi[1]>0 || navi[2]>0 || navi[3]>0 || navi[4]>0);
  do {
    sleep(T);
    system("cls");
    printf("\n\tCampo dove visualizzi le tue navi\n");
    if (turno==1) stampa_campo(campo_pos_PL1);
    else stampa_campo(campo_pos_PL2);
    printf("\n\tCampo dove vengono visualizzati i tuoi colpi\n");
    if (turno==1) stampa_campo(campo_act_PL1);
    else stampa_campo(campo_act_PL2);
    printf("\n\tTurno player %d --> sferra il tuo colpo! coord: ",turno);
    if (turno==1) {
      do {
        if (err==1) printf("\tPos occupata, reinseriscila: \n");
        coordY=inserimento_coordY();
        coordX=inserimento_coordX();
        if (campo_act_PL1[coordY][coordX]!=0) err=1;
        else err=0;
      } while (err==1);
      if (campo_pos_PL2[coordY][coordX]!=0) {
        printf("\n\tBersaglio colpito ");
        if (affondato(coordY,coordX,campo_pos_PL2,campo_act_PL1)==4
          || affondato(coordY,coordX,campo_pos_PL2,campo_act_PL1)==2
          || affondato(coordY,coordX,campo_pos_PL2,campo_act_PL1)==3
          || affondato(coordY,coordX,campo_pos_PL2,campo_act_PL1)==5
          || affondato(coordY,coordX,campo_pos_PL2,campo_act_PL1)==1) {
          printf("e affondato\n");
          navi_rimaste_PL2-=1;
        } else printf("\n");
      } else {
        printf("\n\tBersaglio mancato\n");
        campo_act_PL1[coordY][coordX]=NAVE;
        campo_pos_PL2[coordY][coordX]=MANCATO;
      }
      stampa_campo(campo_pos_PL1);
      stampa_campo(campo_act_PL1);
      turno=2;
    } else {
      do {
        if (err==1) printf("\tPos occupata, reinseriscila: \n");
        coordY=inserimento_coordY();
        coordX=inserimento_coordX();
        if (campo_act_PL2[coordY][coordX]!=0) err=1;
        else err=0;
      } while (err==1);
      if (campo_pos_PL1[coordY][coordX]!=0) {
        printf("\n\tBersaglio colpito ");
        if (affondato(coordY,coordX,campo_pos_PL1,campo_act_PL2)==4
        || affondato(coordY,coordX,campo_pos_PL1,campo_act_PL2)==3
        || affondato(coordY,coordX,campo_pos_PL1,campo_act_PL2)==2
        || affondato(coordY,coordX,campo_pos_PL1,campo_act_PL2)==5
        || affondato(coordY,coordX,campo_pos_PL1,campo_act_PL2)==1) {
          printf("e affondato\n");
          navi_rimaste_PL1-=1;
        } else printf("\n");
      } else {
        printf("\n\tBersaglio mancato\n");
        campo_act_PL2[coordY][coordX]=NAVE;
        campo_pos_PL1[coordY][coordX]=MANCATO;
      }
      stampa_campo(campo_pos_PL2);
      stampa_campo(campo_act_PL2);
      turno=1;
    }
  } while (navi_rimaste_PL2>0 && navi_rimaste_PL1>0);
  if (navi_rimaste_PL1<0) printf("\n\tIl vincitore e' il Player 2\n");
  else printf("\n\tIl vincitore e' il Player 1\n");
  return 0;
}
