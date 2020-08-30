#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_DAN 12
#define MAX_DATUM 7
#define MAX_NIZ 100

/// Format ulaz fajla: dan koliko_sati

typedef struct sati_st{
  char datum[MAX_DATUM];                                           /// Struktura kojom se ucitava ulazni fajl.
  double sati;
}SATI;

typedef struct plata_st{
  char datum[MAX_DATUM];
  char dan[MAX_DAN];                                               /// Struktura koja se ispisuje u izlazni fajl.
  double plata;
}PLATA;

int koji_je_dan(int dan, int mesec, int godina){
  int a,b,c,d,e;
  a = (godina + (godina / 4))%7;
  // printf("%d\n",a);
  if(mesec == 1) b = 0;
  else if(mesec == 2) b = 3;                                      /// Rezultati dobijeni sa interneta.
  else if(mesec == 3) b = 3;
  else if(mesec == 4) b = 6;
  else if(mesec == 5) b = 1;
  else if(mesec == 6) b = 4;
  else if(mesec == 7) b = 6;
  else if(mesec == 8) b = 2;
  else if(mesec == 9) b = 5;
  else if(mesec == 10) b = 0;
  else if(mesec == 11) b = 3;
  else if(mesec == 12) b = 5;
  if(godina%4 == 0){
    d = -1;
  }
  else d = 0;

  c = 6;                                                        /// Koji je vek, posto je sad 21 vek stavljam 6.

  int rez = a+b+c+dan+d;
  return rez%7;
}

FILE* safeopen(char *ulaz, char* mod, int error){
  FILE* fulaz = fopen(ulaz,mod);
  if(fulaz == NULL){
    printf("Fajl nije otvoren.\n");
    exit(error);
  }
  return fulaz;
}

void ucitaj_fajl(FILE* fajl, SATI sat[MAX_NIZ], int* n){
  *n = 0;
  while(fscanf(fajl,"%s %lf",sat[*n].datum, &sat[*n].sati) != EOF){
    (*n)++;
  }
}

void upisi(FILE* fajl, PLATA plata[MAX_NIZ], int n,int godina,int mesec){
  int i;
  for(i=0; i<n; i++){
    fprintf(fajl,"Vasa plata %2s.%d.20%d - %-10s iznosi %6.2lf evra.\n",                            /// Upisuje u izlazni fajl.
      plata[i].datum, mesec, godina, plata[i].dan, plata[i].plata);
  }
}

char* odredi(int koji_dan){
  char *day;
  char *d;
  if(koji_dan == 0) day = "Nedelja";
  else if(koji_dan == 1) day = "Ponedeljak";
  else if(koji_dan == 2) day = "Utorak";
  else if(koji_dan == 3) day = "Sreda";
  else if(koji_dan == 4) day = "Cetvrtak";
  else if(koji_dan == 5) day = "Petak";
  else if(koji_dan == 6) day = "Subota";

  return day;
}

void napravi_st(SATI sat[MAX_NIZ], PLATA plata[MAX_NIZ],
              int godina,int n,float cena_sata, int mesec){
  int i;
  // printf("%d\n",n);
  int dan;
  float a;
  int koji_dan;
  char day[MAX_DAN];
  char tmp[MAX_DAN];
  for(i=0; i<n; i++){
    dan = atoi(sat[i].datum);
    koji_dan = koji_je_dan(dan,mesec,godina);                           /// Odredjuje koji je dan u nedelji.
    // printf("%d\n",koji_dan);
    // tmp = odredi(koji_dan);
    strcpy(plata[i].dan,odredi(koji_dan));
    // printf("%s\n",plata[i].dan);
    strcpy(plata[i].datum,sat[i].datum);
    // printf("%s\n",plata[i].datum);
    plata[i].plata = sat[i].sati * cena_sata;
    //printf("%lf",plata[i].plata);
  }
}

int ucitaj1(){
  int godina;
  do{
    printf("Unesite koja je godina u formatu YY (npr. 2019 = 19): ");
    scanf("%d",&godina);
  }while(godina < 0 || godina > 99);
    return godina;
}

float ucitaj2(int n){
  float bonus1;
  do{
    printf("Koliko vam iznosi bonus preko %d sati: ",n);
    scanf("%f",&bonus1);
  }while(bonus1 <= 0 || bonus1 >= 100);
  return bonus1;
}

float ucitaj3(){
  float bonus1;
  do{
    printf("Koliko vam iznosi plata po satu u evrima: ");
    scanf("%f",&bonus1);
  }while(bonus1 <= 0);
  return bonus1;
}

double predpostavka_plate(PLATA plata[MAX_NIZ],int n){
    int i;
    double pl = 0;
    for(i=0; i<n; i++){
        pl += plata[i].plata;
    }
    return pl/n;
}

int radnih_dana(SATI k[MAX_NIZ],int i,int j,int n);

double koliko_fali(SATI sat[MAX_NIZ],PLATA plata[MAX_NIZ], int n,
                int koliko_dana,int h,int mesec,int godina){
    int n2 = radnih_dana(sat,mesec,godina,n);
    int br = koliko_dana - n2;
    int i;
    double hour = 0;
    for(i=0; i<n; i++){
        hour += sat[i].sati;
    }
   // printf("1. %lf\n",hour);
    double koliko = h - hour;
    double rez = koliko/br;
 //   printf("1. %lf\n",rez);
  //      printf("3. %d\n",n2);


    if(koliko <=0){
        return 0;
    }
    else if(koliko_dana <= n2){
        return -1;
    }
    else{
        return rez;
    }
}

int izracunaj_minute(double n){
    n -= floor(n);
    n *= 100;
    int x = ceil((n*60)/100);
    return x;
}

int ucitaj4(){
  int mesec;
  do{
    printf("Unesite koji je mesec u formatu MM (npr. Jun = 06): ");         /// Ucitaj koji je mesec
    scanf("%d",&mesec);
  }while(mesec < 0 || mesec > 12);
    return mesec;
}

int koliko_dana_u_mesecu(int mesec, int godina){
    int br;
    if(mesec == 1) br = 31;
    else if(mesec == 2) br = 28;
    else if(mesec == 3) br = 31;
    else if(mesec == 4) br = 30;
    else if(mesec == 5) br = 31;
    else if(mesec == 6) br = 30;                               /// Koliko ima dana u mesecu
    else if(mesec == 7) br = 31;
    else if(mesec == 8) br = 31;
    else if(mesec == 9) br = 30;
    else if(mesec == 10) br = 31;
    else if(mesec == 11) br = 30;
    else if(mesec == 12) br = 31;

    if(godina%4 == 0){
        if(mesec == 2){
            br = 29;
        }
    }
   // printf("%d\n",br);
    return br;
}

int radnih_dana(SATI sat[MAX_NIZ],int mesec, int godina, int koliko){
    int i;
    int br = 0;                                                     /// Koliko ima radnih dana u meseca
    for(i=0; i<koliko; i++){
        if(koji_je_dan(atoi(sat[i].datum),mesec,godina) != 0 && koji_je_dan(atoi(sat[i].datum),mesec,godina) != 6){
                //printf("Koliko : %d",koliko);
                //printf("222: %s\n",sat[i].datum);
                //printf("333. %d\n",koji_je_dan(atoi(sat[i].datum),mesec,godina));
            br++;
        }
    }
    return br;
}

void upisi_police(FILE* fajl, FILE* police){
    char a = fgetc(police);
    while(a!= EOF){                                             /// Upisi sadrzaj iz police fajla
        fputc(a,fajl);
        a = fgetc(police);
    }
}

int radnih_dana_ima(int mesec, int godina, int koliko){
    int i;
    int br = 0;                                                     /// Koliko ima radnih dana u ulaznom fajlu
    for(i=1; i<=koliko; i++){
        if(koji_je_dan(i,mesec,godina) != 0 && koji_je_dan(i,mesec,godina) != 6){
                //printf("Koliko : %d",koliko);
                //printf("222: %s\n",sat[i].datum);
               // printf("333. %d\n",koji_je_dan(sat[i].datum,mesec,godina));
            br++;
        }
    }
    return br;
}

void ispisi_platu(FILE *fajl,SATI sat[MAX_NIZ], float cena, int n){
    int i;
    float hour;
    for(i=0; i<n; i++){
        hour += sat[i].sati;
    }
    float plata = hour * cena;
    //printf("%f %f\n",cena,hour);
    fprintf(fajl,"\n\n!!! Vasa plata sa satnicom od %.2f evra iznosi %.2f evra. !!!\n",cena,plata);
}

int main(){

  SATI sat[MAX_NIZ];
  PLATA plata[MAX_NIZ];

  FILE* in = safeopen("ulaz.txt","r",1);
  FILE* out = safeopen("izlaz.txt","w",2);
  FILE* police = safeopen("Pravila i Odgovornost.txt","r",3);

  int n;
  ucitaj_fajl(in,sat,&n);
  // printf("%d",n);

  int godina = ucitaj1();
  int mesec = ucitaj4();
  float cena_sata = ucitaj3();
  float bonus1 = ucitaj2(200);
  float bonus2 = ucitaj2(220);

  napravi_st(sat,plata,godina,n,cena_sata,mesec);                     /// Unesi podatke u strukturu PLATA
  upisi(out,plata,n,godina,mesec);

  int n2 = radnih_dana(sat,mesec,godina,n);                            /// Koliko ima radnih dana u ulaz fajlu
  int koliko = koliko_dana_u_mesecu(mesec,godina);

  int broj_radnih_dana = radnih_dana_ima(mesec,godina,koliko);            /// Koliko ima radnih dana u mesecu
   // printf("%d\n",broj_radnih_dana);
  double prosecna_zarada = predpostavka_plate(plata,n);         /// Kolika mu je prosecna zarada po danu.
  double koliko_jos200 = koliko_fali(sat,plata,n,broj_radnih_dana,200,mesec,godina);          /// Koliko mu fali sati po danu do 200 sati.
  double koliko_jos220 = koliko_fali(sat,plata,n,broj_radnih_dana,220,mesec,godina);          /// Koliko mu fali sati po danu do 220 sati.

  int koliko_jos200_sat = floor(koliko_jos200);                 /// Od flouta dobijam sate.
  int koliko_jos200_minut = izracunaj_minute(koliko_jos200);    /// Od flouta dobijam minute.

  int koliko_jos220_sat = floor(koliko_jos220);
  int koliko_jos220_minut = izracunaj_minute(koliko_jos220);


  int okx = 0;
  int oky = 0;
  //printf("%d\n",koliko_jos200_minut);
  //printf("%lf\n",koliko_jos200);
  fprintf(out,"\nVasa prosecna plata po danu je: %.2lf evra.\n",prosecna_zarada);
  if(koliko_jos200 > 0 && koliko_jos200 < 24){
    fprintf(out,"\nDa bi vam satnica bila %.2f evra trebate \nraditi jos %d sati i %d minuta po danu narednih %d radnih dana.\n",
            bonus1+cena_sata,koliko_jos200_sat,koliko_jos200_minut,broj_radnih_dana-n2);
  }
  else if(koliko_jos200 == 0){
    fprintf(out,"\nVec ste ostvarili bonus od %.2f evra po satu.\n",bonus1+cena_sata);
    okx = 1;
  }
  else{
    fprintf(out,"\nNemoguce je da ostvarite bonus od %.2f evra po satu.\n",bonus1+cena_sata);
    oky = 1;
  }

  if(koliko_jos220 > 0 && koliko_jos220 < 24){
    fprintf(out,"\nDa bi vam satnica bila %.2f evra trebate \nraditi jos %d sati i %d minuta po danu narednih %d radnih dana.\n",
            bonus2+cena_sata+bonus1,koliko_jos220_sat,koliko_jos220_minut,broj_radnih_dana-n2);
  }
  else if(koliko_jos220 == 0){
    fprintf(out,"\nVec ste ostvarili bonus od %.2f evra po satu.\n",bonus1+cena_sata+bonus2);
    okx = 2;
  }
  else{
    fprintf(out,"\nNemoguce je da ostvarite bonus od %.2f evra po satu.\n",bonus1+cena_sata+bonus2);
    oky = 2;
  }
    //printf("%d  ==  %d\n",n2,broj_radnih_dana);
  if(n2 == broj_radnih_dana){
    if(okx == 2){
        ispisi_platu(out,sat,bonus1+cena_sata+bonus2,n);
    }
    else if(oky == 2){
        if(okx == 0){
            ispisi_platu(out,sat,cena_sata,n);
        }
        else
            ispisi_platu(out,sat,cena_sata+bonus1,n);
    }
  }



  fprintf(out,"\n\n\n\n");
  upisi_police(out,police);

  printf("\nHvala Lepo :D\n");
  printf("\nRezultati vam se nalaze u fajlu \"izlaz\".\n");



  // printf("%s\n",day);

  fclose(in);
  fclose(out);
}
