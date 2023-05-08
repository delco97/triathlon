//Andrea Del Corto - Gabriele Giovannelli - 3IA guruppo5 - Triathlon
#include <stdio.h>
#include <stdlib.h>
#include <string.h>//per confrontare due stringhe.
#define MAXP 3
#define MAXC 25
//Prototype funzioni:
void stampVet(char *vet);
void stampMat(char mat[][MAXC]);
int simpleSerch(char name[MAXP][MAXC],char *sSerch,int *repet);
void puliziaVet(char *vet,int n);
void menu(int tip, int specTip);
int controlInsStr(char *str,char matNomi[][MAXC],int i,int tip,char *prova);
void puntProva(char *prova,char name[][MAXC],int nProva);
void insPart(char name[][MAXC]);
void puntToT(char *p1,char *p2,char *p3,char *pTot);
int posMax(char *v);
void stampClas(char *pTot,char nomi[][MAXC],char *p1,char *p2,char *p3);
//-------------------------------------------------------------------------
void stampVet(char *vet){
  int i;
  for(i=0;i<MAXP;i++){
    printf("%d ",vet[i]);
  }
  printf("\n\n");
}
void stampMat(char mat[][MAXC]){
  int i,j;
  for(i=0;i<MAXP;i++){
    printf("\nmat[%d]= %s",i,mat[i]);
  }
}
int simpleSerch(char name[MAXP][MAXC],char *sSerch,int *repet){
  int pos=-1;
  int i=0;
  while(i<MAXP){
    if(strcmp(name[i],sSerch)==0){
      if(*repet<=1)pos=i;//Modifica pos(posizione della stringa da cercare) solamente la prima volta che la incontra.
      *repet = *repet+1;
      //printf("\n\ntrovato!\n\n");
    }
    i++;
  }
  return pos;
}
void puliziaVet(char *vet,int n){
  int i;
  for(i=0;i<MAXP;i++){
    vet[i]= n;
  }
  //printf("\n\nvet=%s\n\n",vet);
}
void menu(int tip, int specTip){
  switch(tip){
    case 1://Main menu'
      printf("                      ************************************\n");
      printf("                      *                                  *\n");
      printf("                      *        Gara di Triathlon         *\n");
      printf("                      *                                  *\n");
      printf("                      ************************************\n");
    break;
    case 2:
      printf("\n\n");
      printf("                          Inserimento punteggi - Prova %d\n\n",specTip);
    break;
  }
}
int controlInsStr(char *str,char matNomi[][MAXC],int i,int tip,char *prova){//tip 1= insPart , tipo=2 InsPunt
  char ch,ap[MAXC];
  int nCaratTast,repet,l,pos,cont=0;
  do{
    if(cont>0)printf("| %s | non e' presente nell'elenco dei partecipanti\n",ap);
    cont=0;
    nCaratTast=0;
    repet=0;
    pos=0;
    if(tip==1)printf("\nInserisci partecipante %d (max %d carat): ",i+1,MAXC-1);
    else printf("\nInserisci %d classificato (max %d carat): ",i+1,MAXC-1);
    scanf("%c",&ch);
    nCaratTast++;
    l=0;//carattere iesimo.
    while(ch!='\n'){//Fa inserire carratteri fino all'inserimento di un invio.
      if(l<MAXC){
        ap[l]=ch;
        l++;
      }
      scanf("%c",&ch);
      nCaratTast++;//Conta i carratteri inseriti dall'utente
    }
    ap[l] = '\0';
    if(nCaratTast>MAXC || ap[0]=='\0'){
      if(nCaratTast>MAXC)printf("Nome troppo lungo.\n");
      if(ap[0]=='\0')printf("Nessun nome inserito.\n");
    }
    else{
      //printf("\n\nap = %s  l=%d\n\n",ap,l);
      if(tip==1){//Inserimento partecipanti.
        simpleSerch(matNomi,ap,&repet);
        if(repet>=1 && l>0)printf("Nome gia' presente nell'elenco dei partecipanti.\n");
      }
      else{//tip=2
        pos = simpleSerch(matNomi,ap,&repet);
        //printf("pos = %d  ap= %s\n",pos,ap);
        if(pos==-1){
          cont++;
        }
        else{
          if(prova[pos]!= -1)printf("Il concorrente | %s | e' gia' stato classificato.\n",ap);
          else return pos;
        }
      }
      //printf("\n\nap=%s  repet=%d  nCaratTast=%d\n\n",ap,repet,nCaratTast);
    }
  }while( (nCaratTast>MAXC || ap[0]=='\0' || ap[0]=='\n' || repet>=1 || pos==-1));
  strcpy(str,ap);//str = ap solo dopo aver controllato che la stringa sia valida.
  //printf("\nnomeIns= %s   nomePrec=%s   nomeDaIns= %s\nl=%d  nCaratTast=%d   repet=%d",name[i],name[i-1],name[i+1],l,nCaratTast,repet);
}
void puntProva(char *prova,char name[][MAXC],int nProva){
  int i,pos,cont;
  char ap[MAXC];
  menu(2,nProva);//Stampa il menu' di inserimento punteggi (2) per la prova "nProva".
  for(i=0;i<MAXP;i++){
    pos = controlInsStr(prova,name,i,2,prova);
    if(i>=10){//Tutti i partecipanti arrivati dalla 10 posizione in poi totalizzano 1 punto.
      prova[pos]=1;
      //stampVet(prova);
    }
    else{//Il primo totalizza 10 punti, il secondo 9...
      prova[pos]= 10-i;
      //stampVet(prova);
    }
  }

}
void insPart(char name[][MAXC]){
  int i;
  //puliziaMat(name);
  for(i=0;i<MAXP;i++){//Inserimento dei partecipanti
    controlInsStr(name[i],name,i,1,NULL);
  }
}
void puntToT(char *p1,char *p2,char *p3,char *pTot){
  int i;
  //printf("\n\n");
  for(i=0;i<MAXP;i++){
    pTot[i] += p1[i] + p2[i] + p3[i];
    //printf("%d  ",pTot[i]);
  }
}
int posMax(char *v){
  int i,pos;
  char mass;
  mass = v[0];
  pos=0;
  for(i=1;i<MAXP;i++){
    if(v[i]>mass){
      mass = v[i];
      pos=i;
    }
  }
  //printf("pos= %d",pos);
  return pos;
}
void stampClas(char *pTot,char nomi[][MAXC],char *p1,char *p2,char *p3){
  int pos,i;
  FILE *f;
  f = fopen("classifica.txt","w");
  fprintf(f,"Classifica:\n\n");
  if(f == NULL)printf("\nFile 'classifica.txt' non trovato!\n");
  else {
    //system("pause");
    for(i=0;i<MAXP;i++){
      pos = posMax(pTot);
      //printf("pos = %d",pos);
      fprintf(f,"%d - %s)  %d  %d  %d  %d\n\n",i+1,nomi[pos],p1[pos],p2[pos],p3[pos],pTot[pos]);
      pTot[pos]=0;
    }
    printf("\nClassifica stampata su file");
    fclose(f);
  }
}
int main()
{
    int i;
    char name[MAXP][MAXC];
    char prova1[MAXP];
    char prova2[MAXP];
    char prova3[MAXP];
    char tot[MAXP]; //contiene la somma delle tre prove precedenti.

    menu(1,0);
    //stampMat(name);
    printf("\n*** Inserimento partecipanti ***\n");
    insPart(name);//Inserimento dei nomi dei concorrenti.
    //stampMat(name);
    printf("\n\n");
    puliziaVet(prova1,-1);
    puliziaVet(prova2,-1);
    puliziaVet(prova3,-1);
    puliziaVet(tot,0);
    puntProva(prova1,name,1);//Assegna i punteggi della prima prova.
    puntProva(prova2,name,2);//Assegna i punteggi della seconda prova.
    puntProva(prova3,name,3);//Assegna i punteggi della terza prova.
    //printf("\nVal ins:\n");
    //stampVet(prova1);
    //stampVet(prova2);
    //stampVet(prova3);

    //stampVet(tot);
    puntToT(prova1,prova2,prova3,tot);//Calcola i punteggi finali  inserendoli nel vet tot.
    //stampVet(tot);


    stampClas(tot,name,prova1,prova2,prova3);


    printf("\n\n                      FINE PROGRAMMA\n\n");
    return 0;
}
