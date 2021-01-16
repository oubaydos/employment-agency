#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stddef.h>
//#include "offre.h"
#ifndef nl
#define nl printf("\n") // new line
#endif
#ifndef CMAX
#define CMAX 255 // max characters for a name of address ...
#endif
#define Malloc(x) (x*)malloc(sizeof(x))
#define maxmalloc(x) (x*)malloc(CMAX*sizeof(x)) // allocate 255 elements of x
typedef enum {false,true} bool; // false = 0 , true = 1

int indice ; // current number of candidates

typedef struct SCandidat{
	int ca_Index;
	char ca_Nom[CMAX];
	char ca_Prenom[CMAX];
	char ca_Adresse[CMAX];
	char ca_specialite[500];
}Candidat;

Candidat* lirecandidat(){// 9ra des donnees dyal chi candidat bach n ajoutiwh
    Candidat *temp = Malloc(Candidat);
    printf("svp entrer le nom du candidat : ");
    gets(temp->ca_Nom);
    printf("svp entrer le prenom du candidat : ");
    gets(temp->ca_Prenom);
    printf("svp entrer l'adresse du candidat : ");
    gets(temp->ca_Adresse);
    printf("svp entrer les domaines de specialite du candidat separe par '+' : ");
    gets(temp->ca_specialite);
    temp->ca_Index = indice; // kan3tiw indice mn 0 L numberofcandidates-1 automatiquement
    return temp;
}

int numberOfCandidats(){ // ch7al mn candidats 3ndna ( aykhs b9a ndiro f main : indice = numberOfCandidats())
    FILE* ptr = fopen("candidats.txt","r+");
    if (!ptr) // file mat7lch
    {
        printf("error with opening the file");
        return -1;
    }
    int i=0;
    char temp[500];
    while (fscanf(ptr,"%[^\n]\n",temp)!=EOF){
        i++;
    }
    fclose(ptr);
    return i/5; // kola candidat 3ndo 5 lines indice, nom, ....
}

void ajouter(){
    FILE* candidatsfile = fopen("candidats.txt","a+");//a+ == ila makanch l file gad wa7d jdid
    Candidat *temp = lirecandidat(); // 9ra les donnees li ghanzido
    indice++; // incrementer nombre des candidats
    fprintf(candidatsfile,"%d\n",temp->ca_Index);
    fprintf(candidatsfile,"%s\n",temp->ca_Nom);
    fprintf(candidatsfile,"%s\n",temp->ca_Prenom);
    fprintf(candidatsfile,"%s\n",temp->ca_Adresse);
    fprintf(candidatsfile,"%s\n",temp->ca_specialite);
    printf("le candidat est bien ajoute\n");
    fclose(candidatsfile);
    // file 7litih khas tsdo
    return;
}

bool in(int x,int* arr,int n){// wach l'element x kain f arr[n] ola la (b7al in dyal pyhton)
    for (int i = 0 ; i<n ; i++)
        if (arr[i]==x)
            return true;
    return false;
}

int indicemax(int arr[],int n){
    /*
        hna li kandiro howa kan9lbo 3la indice dyal li 3ndo akbar
        knya wila kano joj 3ndhom nfs lknya kaychuf smya
    */
    char name[CMAX]="0",tempname[CMAX];/*name ghandiro fih lknya li l9ina flkhr
                                        tempname == temporaire i3ni ghantraitiw 3liha
                                        oflkhr nlo7oha
                                        */
    char lastname[CMAX]="0",templname[CMAX]; // nfs l7aja
    int max; // ghandiro fih indice lmax li l9ina
    char temp[CMAX];
    char junk[500]; // zbL
    FILE* ptr = fopen("candidats.txt","r");
    while (fscanf(ptr,"%[^\n]\n",temp)!=EOF){
        fscanf(ptr,"%[^\n]\n",templname);
        fscanf(ptr,"%[^\n]\n",tempname);
        if (strcmp(templname,lastname)>0 && !in(atoi(temp),arr,n)){/* khas max mankunuch deja jbdnah
                                                                    ~~~chuf fct dyal sort
                                                                    atoi kat7wl mn char* l int
                                                                    atoi("55") = 55
                                                                    */
            strcpy(lastname,templname);
            strcpy(name,tempname);
            max=atoi(temp);
        }
        else if (!strcmp(templname,lastname)&& !in(atoi(temp),arr,n)){
            if (strcmp(tempname,name)>0){
                strcpy(lastname,templname);
                strcpy(name,tempname);
                max=atoi(temp);
            }
        }
        fgets(junk,500,ptr); /* daba kol candidat 3ndo 5 lines ldaba ankono dwzna
                                3 : indice , nom , prenom khasna n9zo 2 lines ohadchi
                                li drna hna
                            */
        fgets(junk,500,ptr);//same
    }
    fclose(ptr);
    return max;
}

void sort(int* arr){
    //an3tiwha arr[indice] i3ni fih n element (n == numberofcandidates)
    memset(arr,-1,indice); // had lfct kat3mr chi tableau bchi valeur (-1)
    for (int i = 0 ; i<indice ; i++){
        arr[i]=indicemax(arr,indice);//kanjbdo les indices mrtbin
    }
    for (int i = 0 ; i<indice/2 ; i++){//kanrtbohom alphabetiquement
        int temp = arr[i];
        arr[i]=arr[indice-1-i];
        arr[indice-1-i]=temp;
    }
    return;
}

void printsort(int *arr){//kanakhdo array li sortina o kanprintiw nom - prenom mrtbin
    FILE* ptr = fopen("candidats.txt","r");
    char temp[CMAX],first[CMAX],last[CMAX],junk[CMAX];
    for (int i =0; i<indice; i++){

        while (fscanf(ptr,"%[^\n]\n",temp)!=EOF){
            fscanf(ptr,"%[^\n]\n",last);
            fscanf(ptr,"%[^\n]\n",first);
            if (atoi(temp)==arr[i]){
                printf("candidat : %s %s\n",last,first);
                break;
            }
            fgets(junk,500,ptr);
            fgets(junk,500,ptr);
        }
        fseek(ptr,0,SEEK_SET);// bach l curseur irj3 l lwl dyal fichier
    }
    fclose(ptr);
    return;
}

bool iscandidate(char* nom, char* prenom){ //wach had candidat kain f candidats.txt ola la
    char temp[CMAX],templ[CMAX];
    FILE* ptr = fopen("candidats.txt","r");
    while (fscanf(ptr,"%[^\n]\n",temp)!=EOF){
        if (!strcmp(temp,nom)){
            fscanf(ptr,"%[^\n]\n",templ);
            if (!strcmp(templ,prenom)){
                fclose(ptr);
                return true;
            }

        }
    }
    fclose(ptr);
    return false;
}

int indexof(char* nom, char* prenom){//kan3tiwh smya o knya o kayrd lina indice dyalha
    if (!iscandidate(nom,prenom)){
        printf("ce n'est pas un candidat !\n");
        return -1;
    }

    int i=0;
    FILE* ptr = fopen("candidats.txt","r+");
    char temp[CMAX],templ[CMAX];
    while (fscanf(ptr,"%[^\n]\n",temp)!=EOF){
        if (!strcmp(temp,nom)){
            fscanf(ptr,"%[^\n]\n",templ);
            if (!strcmp(templ,prenom)){
                fclose(ptr);
                i++;
                return i/5;//ila l9a dik smya o lknya kayrd i/5 (ch7al mn candidat dwzna)
            }

        }
        i++;
    }
    fclose(ptr);
    return -1;
}

bool strisnum(char* num){// kan3tiwh tableau dyal char o kaychuf wach ra9m ola la
    for (int i = 0 ; num[i];i++)
        if (!isdigit(num[i]))
            return false;
    return true;
}

void modifyordelete(int what,char* nom, char* prenom,int choice){// create a new file and write on it till the wanted index write then the rest of the file
    /* choice == 1 : modify ; choice == 0 : delete*/

    if (!iscandidate(nom,prenom)){
        printf("le candidat n'est pas encore enregistre\n");
        return ;
    }
    int wantedindex = indexof(nom,prenom);
    FILE* rptr = fopen("candidats.txt","r"),*newptr = fopen("temp.txt","w+");
    //1 == nom 2 == prenom 3 == adresse 4 == specialite
    // achno bghina nbdlo z3ma (chuf switch lt7t)
    char temp[CMAX],junk[CMAX];
    char num[CMAX];
    fscanf(rptr,"%[^\n]\n",num);
    while(true){// kanktbo ga3 dakchi li 9bl mn candidat li bghina nbdlo f file jdid
        if (strisnum(num))
            if (atoi(num)==wantedindex)
                break;
        fprintf(newptr,"%s\n",num);
        fscanf(rptr,"%[^\n]\n",num);
    }

    if (choice){//ila  kan choice == 1 i3ni bghina nmodifyiw machi nsupprimiw
        fprintf(newptr,"%s\n",num);//kanktbo indice dyal dak li ghanmodifyiw
        switch(what){
            case 1:
                printf("donner le nouveau nom : ");//kanakhdo nom jdid
                gets(temp);
                fprintf(newptr,"%s\n",temp);
                fgets(junk,500,rptr);//kan9zo nom l9dim
                for (int i = 0 ; i<3 ; i++){//kanktbo les infos lakhrin
                    fscanf(rptr,"%[^\n]\n",temp);
                    fprintf(newptr,"%s\n",temp);
                }
                break;
            case 2:
                fscanf(rptr,"%[^\n]\n",temp);//kanktbo nom l9dim
                fprintf(newptr,"%s\n",temp);
                printf("donner le nouveau prenom : ");//kanakhdo nom jdid
                gets(temp);
                fprintf(newptr,"%s\n",temp);//kanktboh
                fgets(junk,500,rptr);//kan9zoh f file lwl
                for (int i = 0 ; i<2 ; i++){//dakchi li b9a
                    fscanf(rptr,"%[^\n]\n",temp);
                    fprintf(newptr,"%s\n",temp);
                }
                break;
            case 3://b7al dakchi li 9bl
                fscanf(rptr,"%[^\n]\n",temp);//kanktbo nom - prenom
                fprintf(newptr,"%s\n",temp);
                fscanf(rptr,"%[^\n]\n",temp);
                fprintf(newptr,"%s\n",temp);
                printf("donner le nouveau adresse : ");
                gets(temp);
                fprintf(newptr,"%s\n",temp);
                fgets(junk,500,rptr);
                fscanf(rptr,"%[^\n]\n",temp);
                fprintf(newptr,"%s\n",temp);
                break;
            case 4:
                fscanf(rptr,"%[^\n]\n",temp);
                fprintf(newptr,"%s\n",temp);
                for (int i = 0 ; i<2 ;i++){
                    fscanf(rptr,"%[^\n]\n",temp);
                    fprintf(newptr,"%s\n",temp);
                }
                printf("donner la nouvelle specialite : ");
                gets(temp);
                fprintf(newptr,"%s\n",temp);
                fgets(junk,500,rptr);
                break;
            default :
                printf("le choix que vous avez choisi n'est pas possible\n");
                break;
        }
    }
    else {//ila kan choice == 0 i3ni bghina nsupprimiw
        for (int i = 0 ; i<4 ; i++){//n9z dak candidat
            fgets(junk,500,rptr);
        }
        while (fscanf(rptr,"%[^\n]\n",temp)!=EOF){//ktb dakchi li b9a
            if (strisnum(temp))
                fprintf(newptr,"%d\n",atoi(temp)-1);//bdl dok les indices lakhrin n9s mnhom 1
            else
                fprintf(newptr,"%s\n",temp);
        }
    }

    while (fscanf(rptr,"%[^\n]\n",temp)!=EOF){//ila kan bghina nsupprimiw rah kan9zo had lpartie 7it
                                              // kayl9a curseur wasl l lkhr dyal file (EOF)
        fprintf(newptr,"%s\n",temp);
    }
    fclose(rptr);
    fclose(newptr);
    remove("candidats.txt");//7yd l9dim
    rename("temp.txt","candidats.txt");//bdl smya l jdid --> l9dim
    return;

}
char* getspecialite(char* nom,char* prenom){// gets how many domaines a candidate has
    if (!iscandidate(nom,prenom))
        return "not found";
    char* ans = (char*)malloc(500*sizeof(char));
    char temp[CMAX],templ[CMAX];
    FILE* ptr = fopen("candidats.txt","r");
    while (fscanf(ptr,"%[^\n]\n",temp)!=EOF){
        if (!strcmp(temp,nom)){
            fscanf(ptr,"%[^\n]\n",templ);
            if (!strcmp(templ,prenom)){
                fgets(templ,500,ptr);
                fscanf(ptr,"%[^\n]\n",ans);
                fclose(ptr);
                return ans;
            }
        }
    }
    return NULL;//hadi yalah zdtha la dir chi mochkil
}
int numberofdomaines(char* nom, char* prenom){
    if (!iscandidate(nom,prenom))
        return -1;
    int c=1;
    char temp[500];
    strcpy(temp,getspecialite(nom,prenom));
    for (int i = 0 ; temp[i];i++){
        if (temp[i]=='+')
            c++;
    }
    return c;
}
char** getalldomaines(char* nom, char* prenom){//get all domaines from a candidate
    /* l'espace avant 2eme domaine ... peuvent etre une issue*/
    char** ans;
    int j=0;
    char temp[500];
    strcpy(temp,getspecialite(nom,prenom));
    int n = numberofdomaines(nom,prenom);
    ans = (char**)malloc(n*sizeof(char*));
    for (int i = 0 ; i<n ; i++){
        ans[i] = (char*) malloc(500*sizeof(char));
    }
    char* day = strtok(temp,"+");

    while(day){
        strcpy(ans[j++],day);
        day = strtok (NULL, "+");
    }

    return ans;
}
void delspace(char* data){
    char* temp = maxmalloc(char);
    int beg = 0 , end = strlen(data),j=0;
    char space = ' ';
    if (data[0]==space)
        beg++;
    if (data[end-1]==space)
        end--;
    for (int i = beg ; i<end;i++){
        temp[j++]=data[i];
    }
    temp[j]='\0';
    strcpy(data,temp);
}

