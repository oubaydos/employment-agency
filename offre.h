#include "candidat.h"
const char endof[10]="EndOfOffer";
typedef struct SOffre{
    char code[20];
    char date[20];
    char entrep_Nom[CMAX];
    char intitule[CMAX];
    char ville[CMAX];
    int salaire;
    char listeCandidat[2][CMAX];
}Offre;
bool isdate(char* date){
    if (strlen(date)!=10)
      return false;
    if (isdigit(date[0])&&isdigit(date[1])&&isdigit(date[3])&&isdigit(date[4])&&isdigit(date[6])&&isdigit(date[7])&&isdigit(date[8])&&isdigit(date[9]) && date[2]=='/'&&date[5]=='/')
      return true;
    return false;
}

Offre* lireoffre(){// if wanna look for a candidat u should compare between other specifics than index !
    Offre *temp = Malloc(Offre);
    printf("svp entrer le nom de l'entreprise : ");
    gets(temp->entrep_Nom);
    printf("svp entrer la ville de l'entreprise : ");
    gets(temp->ville);
    printf("svp entrer l'intitule de l'offre : ");
    gets(temp->intitule);
    printf("svp entrer le code de l'offre : ");
    gets(temp->code);
    printf("svp entrer la date de debut de l'offre : \" jj/mm/aaaa \" ");
    gets(temp->date);
    while (!isdate(temp->date)){
                    printf("ce n'est pas une date");
                    gets(temp->date);
                }
    printf("svp entrer le salaire propose : ");
    scanf("%d",&temp->salaire);

    return temp;
}

void ajouteroffre(){
    Offre* temp = lireoffre();
    FILE* ptr = fopen("offres.txt","a+");
    fprintf(ptr,"%s\n",temp->code);
    fprintf(ptr,"%s\n",temp->entrep_Nom);
    fprintf(ptr,"%s\n",temp->ville);
    fprintf(ptr,"%s\n",temp->intitule);
    fprintf(ptr,"%d\n",temp->salaire);
    fprintf(ptr,"%s\n",temp->date);
    //fillcandidatstooffer

    fprintf(ptr,"EndOfOffer\n");
    fclose(ptr);
    return;
}

bool isoffre(char* code){
    FILE *ptr = fopen("offres.txt","r+");
    char temp[CMAX],junk[CMAX]="\0";
    while (fscanf(ptr,"%[^\n]\n",temp)!=EOF){
        strcpy(junk,"\0");
        if (!strcmp(temp,code)){
            fclose(ptr);
            return true;
        }
        else {
            while (strcmp(junk,endof)){
                fscanf(ptr,"%[^\n]\n",junk);
            }
        }
    }
    fclose(ptr);
    return false;
}
int nombredecandidat(char* code){
    FILE *ptr = fopen("offres.txt","r+");
    int c=0;
    char temp[CMAX],junk[CMAX];
    while (fscanf(ptr,"%[^\n]\n",temp)!=EOF){
        if (!strcmp(temp,code))
            {
                for (int i=0;i<5;i++){
                    fgets(junk,CMAX,ptr);
                }
                fscanf(ptr,"%[^\n]\n",temp);
                while (strcmp(temp,endof)){
                    ++c;
                    fscanf(ptr,"%[^\n]\n",temp);
                }

                fclose(ptr);
                return c;
            }
    }
    fclose(ptr);
    return -1;
}
void modifyordeleteoffre(char* code,int what, int choice,char *newM){
    int nombrecandidats = nombredecandidat(code);

    if (!isoffre(code))
    {
        printf("l'offre n'existe pas");
        return;
    }
    FILE* rptr = fopen("offres.txt","r"),*newptr = fopen("temp.txt","w+");
    char temp[CMAX],junk[CMAX];
    char num[CMAX];
    fscanf(rptr,"%[^\n]\n",num);
    while(true){// kanktbo ga3 dakchi li 9bl mn candidat li bghina nbdlo f file jdid
        if (!strcmp(num,code))
            break;
        fprintf(newptr,"%s\n",num);
        fscanf(rptr,"%[^\n]\n",num);
    }
    //1 == code 2 == nom entreprise 3 == ville 4 == intitule 5 == salaire 6 == date
    // achno bghina nbdlo z3ma (chuf switch lt7t)
    if (choice){//ila  kan choice == 1 i3ni bghina nmodifyiw machi nsupprimiw
        if (what != 1)
            fprintf(newptr,"%s\n",num);//kanktbo code dyal dak li ghanmodifyiw
        switch(what){
            case 1:
                printf("donner le nouveau code : ");//kanakhdo nom jdid
                strcpy(temp,newM);
                fprintf(newptr,"%s\n",temp);
                for (int i = 0 ; i<(6+nombrecandidats) ; i++){//kanktbo les infos lakhrin
                    fscanf(rptr,"%[^\n]\n",temp);
                    fprintf(newptr,"%s\n",temp);
                }
                break;
            case 2:
                printf("donner le nouveau nom de l' entreprise : ");//kanakhdo nom jdid
                strcpy(temp,newM);
                fprintf(newptr,"%s\n",temp);//kanktboh
                fgets(junk,500,rptr);//kan9zoh f file lwl
                for (int i = 0 ; i<(5+nombrecandidats) ; i++){//dakchi li b9a
                    fscanf(rptr,"%[^\n]\n",temp);
                    fprintf(newptr,"%s\n",temp);
                }
                break;
            case 3://b7al dakchi li 9bl
                fscanf(rptr,"%[^\n]\n",temp);//kanktbo entreprise
                fprintf(newptr,"%s\n",temp);
                printf("donner la nouvelle ville  : ");
                strcpy(temp,newM);
                fprintf(newptr,"%s\n",temp);
                fgets(junk,500,rptr);
                for (int i = 0 ; i<(4+nombrecandidats) ; i++){//dakchi li b9a
                    fscanf(rptr,"%[^\n]\n",temp);
                    fprintf(newptr,"%s\n",temp);
                }
                break;
            case 4:
                for (int i = 0 ; i<2 ; i++){
                    fscanf(rptr,"%[^\n]\n",temp);
                    fprintf(newptr,"%s\n",temp);
                }
                printf("donner le nouveau intitule : ");
                strcpy(temp,newM);
                fprintf(newptr,"%s\n",temp);
                fgets(junk,500,rptr);
                for (int i = 0 ; i<(3+nombrecandidats) ; i++){
                    fscanf(rptr,"%[^\n]\n",temp);
                    fprintf(newptr,"%s\n",temp);
                }
                break;
            case 5:
                for (int i = 0 ; i<3 ; i++){
                    fscanf(rptr,"%[^\n]\n",temp);
                    fprintf(newptr,"%s\n",temp);
                }
                printf("donner le nouveau salaire : ");
                int tempsal;
                tempsal = atoi(newM);
                fprintf(newptr,"%d\n",tempsal);
                fgets(junk,500,rptr);
                for (int i = 0 ; i<(2+nombrecandidats) ; i++){
                    fscanf(rptr,"%[^\n]\n",temp);
                    fprintf(newptr,"%s\n",temp);
                }
                break;
            case 6:
                for (int i = 0 ; i<4 ; i++){
                    fscanf(rptr,"%[^\n]\n",temp);
                    fprintf(newptr,"%s\n",temp);
                }
                printf("donner la nouvelle date : ");
                strcpy(temp,newM);
                fprintf(newptr,"%s\n",temp);
                fgets(junk,500,rptr);
                for (int i = 0 ; i<(1+nombrecandidats) ; i++){
                    fscanf(rptr,"%[^\n]\n",temp);
                    fprintf(newptr,"%s\n",temp);
                }
                break;
            default :
                printf("le choix que vous avez choisi n'est pas possible\n");
                break;
        }
    }
    else {//ila kan choice == 0 i3ni bghina nsupprimiw
        for (int i = 0 ; i<(6+nombrecandidats) ; i++){//n9z dak offre
            fgets(junk,500,rptr);
        }
        while (fscanf(rptr,"%[^\n]\n",temp)!=EOF){//ktb dakchi li b9a
            fprintf(newptr,"%s\n",temp);
        }
    }
    while (fscanf(rptr,"%[^\n]\n",temp)!=EOF){//ila kan bghina nsupprimiw rah kan9zo had lpartie 7it
                                              // kayl9a curseur wasl l lkhr dyal file (EOF)
        fprintf(newptr,"%s\n",temp);
    }
    fclose(rptr);
    fclose(newptr);
    remove("offres.txt");//7yd l9dim
    rename("temp.txt","offres.txt");//bdl smya l jdid --> l9dim
    return;
}
bool iscompany(char* company){
    FILE *rptr = fopen("offres.txt","r");
    char temp[CMAX];
    while (fscanf(rptr,"%[^\n]\n",temp)!=EOF){
        if (isoffre(temp))
        {
            fscanf(rptr,"%[^\n]\n",temp);
            if(!strcmp(company,temp))
                return true;
        }
    }
    fclose(rptr);
    return false;
}
bool isintitule(char* intitule){
    FILE *rptr = fopen("offres.txt","r");
    char temp[CMAX];
    while (fscanf(rptr,"%[^\n]\n",temp)!=EOF){
        if (isoffre(temp)){
            fscanf(rptr,"%[^\n]\n",temp);
            fscanf(rptr,"%[^\n]\n",temp);
            strcpy(temp,"0");
            fscanf(rptr,"%[^\n]\n",temp);
            if (!strcmp(temp,intitule))
                return true;
        }
    }
    fclose(rptr);
    return false;
}
char ** getdatafromcompany(char* entreprise){
    char ** templist=(char**)malloc(6*sizeof(char*));
    for (int i = 0 ; i<6;i++){
        templist[i]=(char*)malloc(CMAX * sizeof(char));
    }

    if (!iscompany(entreprise))
    {
        printf("ce n'est pas une entreprise!\n");
        return NULL;
    }
    long cur;
    FILE *rptr = fopen("offres.txt","r");
    char temp[CMAX],junk[CMAX];
    bool deja=false;
    const char *strings[] = {"ville : ","intitule : ","salaire : ","date : "};
    while (fscanf(rptr,"%[^\n]\n",temp)!=EOF){
        if (isoffre(temp)&&!deja){
            cur = ftell(rptr)-strlen(temp)-2; // rj3 str lor (-2 dyan \n)
            deja = true;
        }
        if(!strcmp(entreprise,temp)){
            fseek(rptr, cur, SEEK_SET);
            fscanf(rptr,"%[^\n]\n",temp);
            strcpy(templist[0],temp);
            fscanf(rptr,"%[^\n]\n",temp);
            strcpy(templist[1],temp);
            for (int i = 2 ; i<=5 ;i++){
                strcpy(temp,"0");
                fscanf(rptr,"%[^\n]\n",temp);
                strcpy(templist[i],temp);
            }
            printf("\n");
            deja = false;
            //return templist;
        }
        else deja = false;
    }
    fclose(rptr);
    return templist;
}


int numberofoffres(){
    FILE *rptr = fopen("offres.txt","r");
    int c=0;
    char temp[CMAX];
    while (fscanf(rptr,"%[^\n]\n",temp)!=EOF){
        if(isoffre(temp))
            c++;
    }
    return c;
}
char** getdatafromintitule(char* intitule){
    char ** templist=(char**)malloc(6*sizeof(char*));
    for (int i = 0 ; i<6;i++){
        templist[i]=(char*)malloc(CMAX * sizeof(char));
    }

    if (!isintitule(intitule))
    {
        printf("ce n'est pas une intitule!\n");
        return NULL;
    }
    long cur;
    FILE *rptr = fopen("offres.txt","r");
    char *temp=(char*)calloc(CMAX,sizeof(char)),junk[CMAX];
    bool deja=false;
    const char *strings[] = {"code : ","entreprise : ","ville : ","salaire : ","date : "};
    while (fscanf(rptr,"%[^\n]\n",temp)!=EOF){
        if (isoffre(temp)&&!deja){
            cur = ftell(rptr)-strlen(temp)-2;// rj3 str lor (-2 dyal \n)
            fscanf(rptr,"%[^\n]\n",temp);
            fscanf(rptr,"%[^\n]\n",temp);//n9z joj
            deja = true;
        }
        if(!strcmp(intitule,temp)){
            fseek(rptr, cur, SEEK_SET);
            for (int i = 0 ; i<3 ;i++){
                fscanf(rptr,"%[^\n]\n",temp);
                strcpy(templist[i],temp);
            }
            strcpy(templist[3],intitule);
            fgets(junk,CMAX,rptr);
            for (int i = 4 ; i<6 ;i++){
                strcpy(temp,"0");
                fscanf(rptr,"%[^\n]\n",temp);
                printf("%s",temp);
                strcpy(templist[i],temp);

            }
            printf("\n");
            deja = false;
        }
        else {
            deja = false;
        }
    }
    fclose(rptr);
    return templist;
}
bool instr(char* s,char** list,int taille){
    for (int i = 0 ; i<taille ; i++)
        if (!strcmp(list[i],s))
            return true;
    return false;
}
char* getmaxspec(char** list,int taille){
    char* max = maxmalloc(char);
    FILE *rptr = fopen("offres.txt","r");
    char temp[CMAX];
    strcpy(max,"\0");
    while (fscanf(rptr,"%[^\n]\n",temp)!=EOF){
        if (isintitule(temp)){
            if (strcmp(temp,max)>0 && !instr(temp,list,taille)){
                strcpy(max,temp);
            }
        }
    }
    fclose(rptr);
    return max;
}
char* getcom(char** list,int taille){
    char* max = maxmalloc(char);
    FILE *rptr = fopen("offres.txt","r");
    char temp[CMAX];
    strcpy(max,"\0");
    while (fscanf(rptr,"%[^\n]\n",temp)!=EOF){
        if (iscompany(temp)){
            if (!instr(temp,list,taille)){
                strcpy(max,temp);
            }
        }
    }
    fclose(rptr);
    return max;
}
char** sortspec(){
    char** ans;
    int n = numberofoffres(),j=0;
    ans = (char**)malloc(n*sizeof(char*));
    for (int i = 0 ; i<n ; i++){
        ans[i] = maxmalloc(char);
    }
    for (int i = 0 ; i<n ; i++){
        char* temp = getmaxspec(ans,n);
        strcpy(ans[j++],temp);
    }
    return ans;
}
void printofferssorted(){
    int n = numberofoffres();
    char** list=sortspec();
    for (int i = 0 ;i<n ; i++){
        printf("intitule : %s\t",list[i]);
        for (int j = 0 ; j<6; j++)
            printf("%s",getdatafromintitule(list[i])[j]);

    }
    return ;
}


