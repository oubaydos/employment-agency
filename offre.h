#include "linkedlists.h"
const char* endof="EndOfOffer";
typedef struct SOffre{
    char code[20];
    char date[20];
    char entrep_Nom[CMAX];
    char intitule[CMAX];
    char ville[CMAX];
    int salaire;
    ListCandidats *liste_candidats;//par ordre de merite
}Offre;
bool isdate(char* date){
    char* temp=(char*)malloc(CMAX*sizeof(char));
    strcpy(temp,date);
    int c=0,countslash = 0,j=0;
    for (int i = 0 ; temp[i];i++)
        if (temp[i]=='/')
            countslash++;
    if (countslash!=2)
        return false;
    char* day = strtok(temp,"/");
    while(day){///////////// i could work on conditions more like if month = 2 & day =30 false
        if(strisnum(temp)){
            if(j==0 && atoi(day)<32 && atoi(day)>0)
                c++;
            else if (j==1 && atoi(day)<13 && atoi(day)>0)
                c++;
            else if (j==2 && atoi(day)>0)
                c++;
        }
        else break;
        day=strtok(NULL,"/");
        if (c>3)
            return false;
        j++;

    }

    if (c==3)
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
    temp->liste_candidats = NULL; // dont know if that is true;
    return temp;
}
ListCandidats* fillcandidatstooffer(Offre* offre);
    // i need to work that function

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
    while(temp->liste_candidats){
        fprintf(ptr,"%s -- %s\n",temp->liste_candidats->value->ca_Nom,temp->liste_candidats->value->ca_Nom);
    }
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
void modifyordeleteoffre(char* code,int what, int choice){
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
                gets(temp);
                fprintf(newptr,"%s\n",temp);
                for (int i = 0 ; i<(6+nombrecandidats) ; i++){//kanktbo les infos lakhrin
                    fscanf(rptr,"%[^\n]\n",temp);
                    fprintf(newptr,"%s\n",temp);
                }
                break;
            case 2:
                printf("donner le nouveau nom de l' entreprise : ");//kanakhdo nom jdid
                gets(temp);
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
                gets(temp);
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
                gets(temp);
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
                scanf("%d",&tempsal);
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
                gets(temp);
                while (!isdate(temp)){
                    printf("ce n'est pas une date, entrer la date svp : ");
                    gets(temp);
                }
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
            fscanf(rptr,"%[^\n]\n",temp);
            if (!strcmp(temp,intitule))
                return true;
        }
    }
    fclose(rptr);
    return false;
}
void getdatafromcompany(char* entreprise){
    if (!iscompany(entreprise))
    {
        printf("ce n'est pas une entreprise!\n");
        return;
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
            printf("offre : %s\t",temp);
            fgets(junk,CMAX,rptr);
            for (int i = 0 ; i<4 ;i++){
                fscanf(rptr,"%[^\n]\n",temp);
                printf("%s%s\t",strings[i],temp);
            }
            printf("\n");
            deja = false;
        }
        else deja = false;
    }
    fclose(rptr);
    return;
}

void getdatafromintitule(char* intitule){
    if (!isintitule(intitule))
    {
        printf("ce n'est pas une intitule!\n");
        return;
    }
    long cur;
    FILE *rptr = fopen("offres.txt","r");
    char temp[CMAX],junk[CMAX];
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
                printf("%s%s\t",strings[i],temp);
            }
            fgets(junk,CMAX,rptr);
            for (int i = 3 ; i<5 ;i++){
                fscanf(rptr,"%[^\n]\n",temp);
                printf("%s%s\t",strings[i],temp);
            }
            printf("\n");
            deja = false;
        }
        else {
            deja = false;
        }
    }
    fclose(rptr);
    return;
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
bool instr(char* s,char** list,int taille){
    //printf("%s",list[0]);
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
        getdatafromintitule(list[i]);

    }
    return ;
}


void getalloffers(char* nom,char* prenom){// all offers that could interest someone
    char** domaines = getalldomaines(nom,prenom);
    int n = numberofdomaines(nom,prenom);
    char *temp = maxmalloc(char);
    for (int i = 0 ; i<n ; i++){
        strcpy(temp,domaines[i]);
        delspace(temp);
        if (isintitule(temp)){
            printf("intitule : %s\t",temp);
            getdatafromintitule(temp);
        }

    }
    return;
}
void printallcandidats(int code);//linkedlists
