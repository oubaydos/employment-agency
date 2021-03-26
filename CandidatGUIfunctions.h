#include <gtk/gtk.h>
#include "offre.h"

GtkBuilder *builder; // builder

GtkWidget *WindowR,*Window,*WindowC,*WindowLireC,*WindowModifier,*WindowAfficherC,*WindowOffresC,*WindowO; // windows

GtkWidget *nom,*prenom,*adresse,*specialite,*nomModifier,*prenomModifier,*nouveauChoix; // entry
GtkWidget *buttonCandidats,*buttonOffres,*buttonContats;//primary window buttons
GtkWidget *vider,*confirmer,*retversprinc,*retverscandidat,*resultajouter;/*pour ajoute */
GtkWidget *ModifierversC/*retourner de modifier vers meu candidats*/,*ModifierversP,*viderM;//lire buttons - label
GtkWidget *ModifierNom,*ModifierPrenom,*ModifierAdresse,*ModifierSpecialite,* resultatModifier,*SupprimerC;
GtkWidget *ind[20],*name[20],*fname[20],*add[20],*spec[20];
GtkWidget *nomcherche,*prenomchercher,*buttonchercheroffreC;
GtkWidget *Adresse,*Spec,*CodeOf[6],*Entrep[6],*Intitu[6],*Ville[6],*Salaire[6],*Date[6],*totaloffres,*ViderOC,*todaydate;
GtkWidget *RetversCfromO,*RetversPfromO;
GtkWidget *WindowSecure,*identifier,*inscrire,*usernameEntry,*passwordEntry,*accepted;
GtkWidget *WindowInfo;

bool WindowCisopen = false,WindowLireCisopen=false,WindowModifierisopen = false,*WindowAfficherCisopen=false;
Candidat* temp;
bool userisSafe=false;
int total=0;
gboolean checkESC(GtkWidget *widget, GdkEventKey *event, gpointer data)
{
  if (event->keyval == GDK_KEY_Escape) {
    gtk_main_quit();
    return TRUE;
  }
  return FALSE;
}

void quitmainWindow(GtkWidget* widget,gpointer data){//sortir du fenetre premiere
    if(!WindowCisopen)
        gtk_main_quit();
    else
        gtk_window_close(GTK_WINDOW(Window));
}
void quitmainWindowC(GtkWidget* widget,gpointer data){
    if(!WindowLireCisopen)
        gtk_main_quit();
    else
        gtk_window_close(GTK_WINDOW(WindowC));
}

void funcRetournerdeMenuCandidat(GtkWidget* widget, gpointer data){ // retourner de menu candidat
                                                                               //vers la fenetre principale
    WindowCisopen = false;
    gtk_window_close(GTK_WINDOW(WindowC));
    main();
    gtk_button_clicked(GTK_BUTTON(identifier));
}
void funcRetdeLireversPrin(GtkWidget* widget, gpointer data){ // retourner de lire vers la fenetre principale
    WindowLireCisopen=false;
    gtk_window_close(GTK_WINDOW(WindowLireC));
    main();
    gtk_button_clicked(GTK_BUTTON(identifier));
}
void funcRetdeLireverscandidat(GtkWidget* widget, gpointer data){ // retourner de lire vers menu candidat
    //

    WindowLireCisopen=false;
    gtk_window_close(GTK_WINDOW(WindowLireC));
    main();
    gtk_button_clicked(GTK_BUTTON(identifier));
    gtk_button_clicked (GTK_BUTTON(buttonCandidats));


}
void viderfunc(GtkWidget *widget,  gpointer data){///button vider
    gtk_entry_set_text (GTK_ENTRY(nom),"");
    gtk_entry_set_text (GTK_ENTRY(prenom),"");
    gtk_entry_set_text (GTK_ENTRY(adresse),"");
    gtk_entry_set_text (GTK_ENTRY(specialite),"");
    gtk_label_set_text (GTK_LABEL(resultajouter),"");
}
void Ajouterfunc(GtkWidget *widget,  gpointer data){///fonction ajouter candidat
    FILE* candidatsfile = fopen("candidats.txt","a+");
    temp = Malloc(Candidat);
    strcpy(temp->ca_Nom,gtk_entry_get_text (GTK_ENTRY(nom)));
    strcpy(temp->ca_Prenom,gtk_entry_get_text (GTK_ENTRY(prenom)));
    strcpy(temp->ca_Adresse,gtk_entry_get_text (GTK_ENTRY(adresse)));
    strcpy(temp->ca_specialite,gtk_entry_get_text (GTK_ENTRY(specialite)));
    if(iscandidate(temp->ca_Nom,temp->ca_Prenom))
    {
        fclose(candidatsfile);
        gtk_label_set_text (GTK_LABEL(resultajouter),"échec! ce Nom/Prenom est deja utilisé");
        return;
    }
    temp->ca_Index = indice++;
    fprintf(candidatsfile,"%d\n",temp->ca_Index);
    fprintf(candidatsfile,"%s\n",temp->ca_Nom);
    fprintf(candidatsfile,"%s\n",temp->ca_Prenom);
    fprintf(candidatsfile,"%s\n",temp->ca_Adresse);
    fprintf(candidatsfile,"%s\n",temp->ca_specialite);
    fclose(candidatsfile);
    gtk_label_set_text (GTK_LABEL(resultajouter),"le candidat est bien ajoute");

    return;
}
void funcAjouterCandidat(GtkWidget* widget,gpointer data){
    gtk_widget_destroy(WindowC);
    WindowLireCisopen = true;

    WindowLireC = GTK_WIDGET(gtk_builder_get_object(builder,"LireCandidat"));

    confirmer = GTK_WIDGET(gtk_builder_get_object(builder,"ConfirmerLire"));
    retversprinc = GTK_WIDGET(gtk_builder_get_object(builder,"retversprinc"));
    retverscandidat = GTK_WIDGET(gtk_builder_get_object(builder,"retverscandidat"));
    vider = GTK_WIDGET(gtk_builder_get_object(builder,"clear"));

    nom = GTK_WIDGET(gtk_builder_get_object(builder,"nom"));
    prenom = GTK_WIDGET(gtk_builder_get_object(builder,"prenom"));
    adresse = GTK_WIDGET(gtk_builder_get_object(builder,"adresse"));
    specialite = GTK_WIDGET(gtk_builder_get_object(builder,"specialite"));
    resultajouter = GTK_WIDGET(gtk_builder_get_object(builder,"resultajouter"));


    g_signal_connect(vider,"clicked",G_CALLBACK(viderfunc),NULL);
    g_signal_connect(retverscandidat,"clicked",G_CALLBACK(funcRetdeLireverscandidat),NULL);
    g_signal_connect(retversprinc,"clicked",G_CALLBACK(funcRetdeLireversPrin),NULL);
    g_signal_connect(confirmer,"clicked",G_CALLBACK(Ajouterfunc),NULL);
    g_signal_connect(WindowLireC,"delete_event",G_CALLBACK(gtk_main_quit),NULL);
    g_signal_connect(WindowLireC, "key_press_event", G_CALLBACK(checkESC), NULL);
    gtk_widget_show_all(WindowLireC);
}
/*************************/
/* done with ajouter ----> now modifier turn*/
void funcRetdeModversPrin(GtkWidget* widget, gpointer data){ // retourner de lire vers la fenetre principale
    WindowModifierisopen=false;
    gtk_window_close(GTK_WINDOW(WindowModifier));
    main();
    gtk_button_clicked(GTK_BUTTON(identifier));
}
void funcRetdeModverscandidat(GtkWidget* widget, gpointer data){ // retourner de lire vers menu candidat
    //

    WindowModifierisopen=false;
    gtk_window_close(GTK_WINDOW(WindowModifier));
    main();
    gtk_button_clicked(GTK_BUTTON(identifier));
    gtk_button_clicked (GTK_BUTTON(buttonCandidats));


}


void funcModifierNom(GtkWidget *widget,  gpointer data){
    char tempNom[CMAX],tempPrenom[CMAX],newentry[500];
    strcpy(tempNom,gtk_entry_get_text (GTK_ENTRY(nomModifier)));
    strcpy(tempPrenom,gtk_entry_get_text (GTK_ENTRY(prenomModifier)));
    strcpy(newentry,gtk_entry_get_text (GTK_ENTRY(nouveauChoix)));
    if (!iscandidate(tempNom,tempPrenom)){
        gtk_label_set_text (GTK_LABEL(resultatModifier),"échec! le candidat n'est pas enregistré!!");
        return;
    }
    modifyordelete(1,tempNom, tempPrenom,1,newentry);
    gtk_label_set_text (GTK_LABEL(resultatModifier),"le nom du candidat est bien Changé");
}
void funcModifierPrenom(GtkWidget *widget,  gpointer data){
    char tempNom[CMAX],tempPrenom[CMAX],newentry[500];
    strcpy(tempNom,gtk_entry_get_text (GTK_ENTRY(nomModifier)));
    strcpy(tempPrenom,gtk_entry_get_text (GTK_ENTRY(prenomModifier)));
    strcpy(newentry,gtk_entry_get_text (GTK_ENTRY(nouveauChoix)));
    if (!iscandidate(tempNom,tempPrenom)){
        gtk_label_set_text (GTK_LABEL(resultatModifier),"échec! le candidat n'est pas enregistré!!");
        return;
    }
    modifyordelete(2,tempNom, tempPrenom,1,newentry);
    gtk_label_set_text (GTK_LABEL(resultatModifier),"le prenom du candidat est bien Changé");
}
void funcModifierAdresse(GtkWidget *widget,  gpointer data){
    char tempNom[CMAX],tempPrenom[CMAX],newentry[500];
    strcpy(tempNom,gtk_entry_get_text (GTK_ENTRY(nomModifier)));
    strcpy(tempPrenom,gtk_entry_get_text (GTK_ENTRY(prenomModifier)));
    strcpy(newentry,gtk_entry_get_text (GTK_ENTRY(nouveauChoix)));
    if (!iscandidate(tempNom,tempPrenom)){
        gtk_label_set_text (GTK_LABEL(resultatModifier),"échec! le candidat n'est pas enregistré!!");
        return;
    }
    modifyordelete(3,tempNom, tempPrenom,1,newentry);
    gtk_label_set_text (GTK_LABEL(resultatModifier),"l'adresse du candidat est bien Changé");
}
void funcModifierSpecialite(GtkWidget *widget,  gpointer data){
    char tempNom[CMAX],tempPrenom[CMAX],newentry[500];
    strcpy(tempNom,gtk_entry_get_text (GTK_ENTRY(nomModifier)));
    strcpy(tempPrenom,gtk_entry_get_text (GTK_ENTRY(prenomModifier)));
    strcpy(newentry,gtk_entry_get_text (GTK_ENTRY(nouveauChoix)));
    if (!iscandidate(tempNom,tempPrenom)){
        gtk_label_set_text (GTK_LABEL(resultatModifier),"échec! le candidat n'est pas enregistré!!");
        return;
    }
    modifyordelete(4,tempNom, tempPrenom,1,newentry);
    gtk_label_set_text (GTK_LABEL(resultatModifier),"la specialité du candidat est bien Changé");
}
void funcSupprimerCandidat(GtkWidget *widget,  gpointer data){
    char tempNom[CMAX],tempPrenom[CMAX];
    strcpy(tempNom,gtk_entry_get_text (GTK_ENTRY(nomModifier)));
    strcpy(tempPrenom,gtk_entry_get_text (GTK_ENTRY(prenomModifier)));
    if (!iscandidate(tempNom,tempPrenom)){
        gtk_label_set_text (GTK_LABEL(resultatModifier),"échec! le candidat n'est pas enregistré!!");
        return;
    }
    modifyordelete(1,tempNom, tempPrenom,0,"a");
    gtk_label_set_text (GTK_LABEL(resultatModifier),"le candidat est Supprimé!");
}
void viderfuncModifier(GtkWidget *widget,  gpointer data){///button vider
    gtk_entry_set_text (GTK_ENTRY(nomModifier),"");
    gtk_entry_set_text (GTK_ENTRY(prenomModifier),"");
    gtk_entry_set_text (GTK_ENTRY(nouveauChoix),"");
    gtk_label_set_text (GTK_LABEL(resultatModifier),"");
}

void funcModifierCandidat(GtkWidget* widget,gpointer data){
    gtk_widget_destroy(WindowC);
    WindowModifierisopen = true;
    //labels
    nomModifier = GTK_WIDGET(gtk_builder_get_object(builder,"nomModifier"));
    prenomModifier = GTK_WIDGET(gtk_builder_get_object(builder,"prenomModifier"));
    nouveauChoix = GTK_WIDGET(gtk_builder_get_object(builder,"nouveauChoix"));
    resultatModifier = GTK_WIDGET(gtk_builder_get_object(builder,"resModifier"));
    //buttons

    ModifierNom = GTK_WIDGET(gtk_builder_get_object(builder,"modifierNomCandidat"));
    ModifierPrenom = GTK_WIDGET(gtk_builder_get_object(builder,"modifierPreomCandidat"));
    ModifierAdresse = GTK_WIDGET(gtk_builder_get_object(builder,"modifierAdresseCandidat"));
    ModifierSpecialite = GTK_WIDGET(gtk_builder_get_object(builder,"modifierSpecialitéCandidat"));

    WindowModifier = GTK_WIDGET(gtk_builder_get_object(builder,"modifierCandidat"));
    ModifierversC = GTK_WIDGET(gtk_builder_get_object(builder,"retverscandidatdeModifier"));
    ModifierversP = GTK_WIDGET(gtk_builder_get_object(builder,"retversprincdeModifier"));
    viderM = GTK_WIDGET(gtk_builder_get_object(builder,"clearModifier"));
    SupprimerC = GTK_WIDGET(gtk_builder_get_object(builder,"SupprimerCandidatx"));

    g_signal_connect(ModifierversC,"clicked",G_CALLBACK(funcRetdeModverscandidat),NULL);
    g_signal_connect(ModifierversP,"clicked",G_CALLBACK(funcRetdeModversPrin),NULL);
    g_signal_connect(WindowModifier,"delete_event",G_CALLBACK(gtk_main_quit),NULL);
    g_signal_connect(viderM,"clicked",G_CALLBACK(viderfuncModifier),NULL);
    g_signal_connect(WindowModifier, "key_press_event", G_CALLBACK(checkESC), NULL);

    g_signal_connect(ModifierNom,"clicked",G_CALLBACK(funcModifierNom),NULL);
    g_signal_connect(ModifierPrenom,"clicked",G_CALLBACK(funcModifierPrenom),NULL);
    g_signal_connect(ModifierAdresse,"clicked",G_CALLBACK(funcModifierAdresse),NULL);
    g_signal_connect(ModifierSpecialite,"clicked",G_CALLBACK(funcModifierSpecialite),NULL);
    g_signal_connect(SupprimerC,"clicked",G_CALLBACK(funcSupprimerCandidat),NULL);

    gtk_widget_show_all(WindowModifier);
}

void printsortt(int *arr){//on prent le tableau trié et on fait printsortt(ce tableau)
    FILE* ptr = fopen("candidats.txt","r");
    char temp[CMAX],first[CMAX],last[CMAX],junk[CMAX],speci[500],adr[500];
    printf("\n");
    for (int i = 0 ; i<indice ; i++)
        printf("%d\t",arr[i]);
    for (int i =0; i<min(indice,19); i++){
        while (fscanf(ptr,"%[^\n]\n",temp)!=EOF){
            fscanf(ptr,"%[^\n]\n",last);
            fscanf(ptr,"%[^\n]\n",first);
            fscanf(ptr,"%[^\n]\n",adr);
            fscanf(ptr,"%[^\n]\n",speci);
            if (atoi(temp)==arr[i]){
                gtk_label_set_text (GTK_LABEL(ind[i]),temp);
                gtk_label_set_text (GTK_LABEL(name[i]),last);
                gtk_label_set_text (GTK_LABEL(fname[i]),first);
                gtk_label_set_text (GTK_LABEL(add[i]),adr);
                gtk_label_set_text (GTK_LABEL(spec[i]),speci);
                break;
            }

        }
        if (i<min(indice,20)) fseek(ptr,0,SEEK_SET);// bach l curseur irj3 l lwl dyal fichier
    }
    fclose(ptr);
    return;
}

void funcAfficherCandidats(GtkWidget* widget,gpointer data){
    gtk_widget_destroy(WindowC);
    char I[5],N[5],P[5],A[5],S[5],temp[5];
    for (int i = 0 ; i<19 ;i++){
        strcpy(I,"I");
        sprintf(temp, "%d", i);
        strcat(I,temp);
        ind[i]=GTK_WIDGET(gtk_builder_get_object(builder,I));
        strcpy(N,"N");
        strcat(N,temp);
        name[i]=GTK_WIDGET(gtk_builder_get_object(builder,N));
        strcpy(P,"P");
        strcat(P,temp);
        fname[i]=GTK_WIDGET(gtk_builder_get_object(builder,P));
        strcpy(A,"A");
        strcat(A,temp);
        add[i]=GTK_WIDGET(gtk_builder_get_object(builder,A));
        strcpy(S,"S");
        strcat(S,temp);
        spec[i]=GTK_WIDGET(gtk_builder_get_object(builder,S));

    }
    int arr[indice];
    sort(arr);
    printsortt(arr);
    WindowAfficherC = GTK_WIDGET(gtk_builder_get_object(builder,"AfficherCandidat"));
    g_signal_connect(WindowAfficherC,"delete_event",G_CALLBACK(gtk_main_quit),NULL);
    g_signal_connect(WindowAfficherC, "key_press_event", G_CALLBACK(checkESC), NULL);


    gtk_widget_show_all(WindowAfficherC);

}
bool instrlist(char* x,int choix,int n){
    /*
    choix == 1 --> dv (dev) 2=bd 3=md 4=ng
    */
    switch (choix){
        case 1 : for (int i = 0 ; i<n ; i++){

                    if (!strcmp(x,dv[i]))
                        return true;
                    }
                 return false;
        case 2 : for (int i = 0 ; i<n ; i++){

                    if (!strcmp(x,bd[i]))
                        return true;
                    }
                 return false;
        case 3 : for (int i = 0 ; i<n ; i++){

                    if (!strcmp(x,md[i]))
                        return true;
                    }
                 return false;
        case 4 : for (int i = 0 ; i<n ; i++){

                    if (!strcmp(x,ng[i]))
                        return true;
                    }
                 return false;
    }

}
void getdatafromoffer(char a[3]){
    FILE *ptr = fopen("offres.txt","r+");
    char temp[CMAX],junk[CMAX]="\0";

    while (fscanf(ptr,"%[^\n]\n",temp)!=EOF && total<=5){
        strcpy(junk,"\0");
        if (a[0]==temp[3] && a[1]==temp[4] && temp[2]=='_'){
            gtk_label_set_label (GTK_LABEL(CodeOf[total+1]),temp);
            fscanf(ptr,"%[^\n]\n",temp);
            gtk_label_set_text (GTK_LABEL(Entrep[total+1]),temp);
            fscanf(ptr,"%[^\n]\n",temp);
            gtk_label_set_text (GTK_LABEL(Ville[total+1]),temp);
            fscanf(ptr,"%[^\n]\n",temp);
            gtk_label_set_text (GTK_LABEL(Intitu[total+1]),temp);
            fscanf(ptr,"%[^\n]\n",temp);
            gtk_label_set_text (GTK_LABEL(Salaire[total+1]),temp);
            fscanf(ptr,"%[^\n]\n",temp);
            gtk_label_set_text (GTK_LABEL(Date[total+1]),temp);
            total++;
            while (!(junk[0]=='E',junk[1]=='n',junk[2]=='d')){
                fscanf(ptr,"%[^\n]\n",junk);
            }
        }
        else {
            while (!(junk[0]=='E',junk[1]=='n',junk[2]=='d')){
                fscanf(ptr,"%[^\n]\n",junk);
            }
        }
    }
    fclose(ptr);
    return;
}
char* delspaceret(char* data){
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
    return temp;
}

void funcvider(GtkWidget* widget,gpointer data){
    for (int i = 1 ; i<=5 ;i++){
        gtk_label_set_label (GTK_LABEL(CodeOf[i]),"");
        gtk_label_set_text (GTK_LABEL(Entrep[i]),"");
        gtk_label_set_text (GTK_LABEL(Ville[i]),"");
        gtk_label_set_text (GTK_LABEL(Intitu[i]),"");
        gtk_label_set_text (GTK_LABEL(Salaire[i]),"");
        gtk_label_set_text (GTK_LABEL(Date[i]),"");
    }
}
void funcchercherdomaines(GtkWidget* widget,gpointer data){

    char totstr[10]="0";
    char nameC[CMAX],fnameC[CMAX];
    strcpy(nameC,gtk_entry_get_text (GTK_ENTRY(nomcherche)));
    strcpy(fnameC,gtk_entry_get_text (GTK_ENTRY(prenomchercher)));
    if (!iscandidate(nameC,fnameC)){
        gtk_label_set_text (GTK_LABEL(Adresse),"ce n'est pas un candidat");
        gtk_label_set_text (GTK_LABEL(Spec),"ce n'est pas un candidat");
        return;
    }

    char** dom = getalldomaines(nameC,fnameC);
    int n = numberofdomaines(nameC,fnameC);

    for (int i =0 ; i<n ;i++){

        if(instrlist(delspaceret(dom[i]),1,6))
            getdatafromoffer("dv");
        else if(instrlist(delspaceret(dom[i]),2,5))
            getdatafromoffer("bd");
        else if(instrlist(delspaceret(dom[i]),3,5))
            getdatafromoffer("md");
        else if(instrlist(delspaceret(dom[i]),4,3))
            getdatafromoffer("ng");
        else {
            printf("ce genre de domaines n'est pas encore traité\n");
        }
    }
    sprintf(totstr, "%d", total);//total
    gtk_label_set_text (GTK_LABEL(totaloffres),totstr);

    gtk_label_set_text (GTK_LABEL(Spec),getspecialite(nameC,fnameC));
    gtk_label_set_text (GTK_LABEL(Adresse),getadresse(nameC,fnameC));
    total = 0;
    return;
}
void functodaydate(){
    time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  char wholedate[20]="\0",year[6]="\0",month[4]="\0",day[4]="\0";
  sprintf(year, "%d", tm.tm_year + 1900);
  sprintf(month, "%02d", tm.tm_mon + 1);
  sprintf(day, "%02d", tm.tm_mday);
  strcat(wholedate,day);
  strcat(wholedate,"/");
  strcat(wholedate,month);
  strcat(wholedate,"/");
  strcat(wholedate,year);
  gtk_label_set_text(GTK_LABEL(todaydate),wholedate);

}
void funcretversPfromO(GtkWidget* widget, gpointer data){ // retourner de menu candidat
                                                                               //vers la fenetre principale
    gtk_window_close(GTK_WINDOW(WindowOffresC));
    main();
    gtk_button_clicked(GTK_BUTTON(identifier));
}
void funcRetdeoversc(GtkWidget* widget, gpointer data){ // retourner de lire vers menu candidat
    //

    gtk_window_close(GTK_WINDOW(WindowOffresC));
    main();
    gtk_button_clicked(GTK_BUTTON(identifier));
    gtk_button_clicked (GTK_BUTTON(buttonCandidats));


}
void funcAfficherOffresC(GtkWidget* widget,gpointer data){
    gtk_widget_destroy(WindowC);



    nomcherche = GTK_WIDGET(gtk_builder_get_object(builder,"nomcherche"));
    prenomchercher = GTK_WIDGET(gtk_builder_get_object(builder,"prenomchercher"));
    WindowOffresC = GTK_WIDGET(gtk_builder_get_object(builder,"WindowOffresC"));
    buttonchercheroffreC = GTK_WIDGET(gtk_builder_get_object(builder,"buttonchercheroffreC"));


    char I[10],N[10],P[10],A[10],S[10],T[10],temp[5];
    for (int i = 1 ; i<=5 ;i++){
        strcpy(I,"code");
        sprintf(temp, "%d", i);
        strcat(I,temp);
        CodeOf[i]=GTK_WIDGET(gtk_builder_get_object(builder,I));
        strcpy(N,"Entrep");
        strcat(N,temp);
        Entrep[i]=GTK_WIDGET(gtk_builder_get_object(builder,N));
        strcpy(P,"Inti");
        strcat(P,temp);
        Intitu[i]=GTK_WIDGET(gtk_builder_get_object(builder,P));
        strcpy(A,"Ville");
        strcat(A,temp);
        Ville[i]=GTK_WIDGET(gtk_builder_get_object(builder,A));
        strcpy(S,"Sal");
        strcat(S,temp);
        Salaire[i]=GTK_WIDGET(gtk_builder_get_object(builder,S));
        strcpy(T,"date");
        strcat(T,temp);
        Date[i]=GTK_WIDGET(gtk_builder_get_object(builder,T));
    }
    Adresse = GTK_WIDGET(gtk_builder_get_object(builder,"addC"));
    Spec = GTK_WIDGET(gtk_builder_get_object(builder,"specC"));
    totaloffres = GTK_WIDGET(gtk_builder_get_object(builder,"totaloffrez"));
    ViderOC = GTK_WIDGET(gtk_builder_get_object(builder,"ViderOC"));
    todaydate = GTK_WIDGET(gtk_builder_get_object(builder,"datetoday"));
    RetversCfromO = GTK_WIDGET(gtk_builder_get_object(builder,"RetversCdeOffC1"));
    RetversPfromO = GTK_WIDGET(gtk_builder_get_object(builder,"RetversPrincdeOffC"));

    g_signal_connect(WindowOffresC,"delete_event",G_CALLBACK(gtk_main_quit),NULL);
    g_signal_connect(WindowOffresC, "key_press_event", G_CALLBACK(checkESC), NULL);
    g_signal_connect(buttonchercheroffreC,"clicked",G_CALLBACK(funcchercherdomaines),NULL);
    g_signal_connect(ViderOC,"clicked",G_CALLBACK(funcvider),NULL);
    g_signal_connect(RetversPfromO,"clicked",G_CALLBACK(funcretversPfromO),NULL);
    g_signal_connect(RetversCfromO,"clicked",G_CALLBACK(funcRetdeoversc),NULL);


    gtk_widget_show_all(WindowOffresC);


}
