#include "offreGUI.h"
/*
la gestion des recrutements
*/

GtkWidget *WindowAjouterR,*ConfirmerR,*retR,*retPR,*nomR,*prenomR,*codeR,*typeR,*duree,*rstR,*idR;
GtkWidget *WindowAnnulerR,*AnnelerRet,*retPRAn,*retRAn,*codeAn,*resAn,*WindowAfficherR;
GtkWidget *codeRec[10],*nomRec[10],*prenomRec[10],*codeOffreR[10],*dureeRec[10],*typeRec[10];
bool byyearormonth = 1;//year
typedef struct SRecrutement{
	char id[10];
    char nom[CMAX];
    char prenom[CMAX];
    char codeOffre[CMAX];
    char duree[CMAX];
    char type[CMAX];
    int yeareffected;
    int montheffected;
}Recrutement;

void RetournerVersMenuPrincipaldeMenuRec(GtkWidget* widget, gpointer data){//retourner vers le menu principal de menu recrutement
	gtk_window_close(GTK_WINDOW(WindowR));
    main();
    gtk_button_clicked(GTK_BUTTON(identifier));
}
void funcretversPdeA(GtkWidget* widget, gpointer data){//meme + de fenetre ajouter un contrat
    gtk_window_close(GTK_WINDOW(WindowAjouterR));
    main();
    gtk_button_clicked(GTK_BUTTON(identifier));
}
void funcRetdeAoversR(GtkWidget* widget, gpointer data){// vers gestion des contrats
    //

    gtk_window_close(GTK_WINDOW(WindowAjouterR));
    main();
    gtk_button_clicked(GTK_BUTTON(identifier));
    gtk_button_clicked (GTK_BUTTON(buttonContats));
}
void funcAjouterR(GtkWidget* widget,gpointer data){
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
    Recrutement* temp=Malloc(Recrutement);
    strcpy(temp->id,gtk_entry_get_text (GTK_ENTRY(idR)));
    strcpy(temp->nom,gtk_entry_get_text (GTK_ENTRY(nomR)));
    strcpy(temp->prenom,gtk_entry_get_text (GTK_ENTRY(prenomR)));
    strcpy(temp->codeOffre,gtk_entry_get_text (GTK_ENTRY(codeR)));
    strcpy(temp->duree,gtk_entry_get_text (GTK_ENTRY(duree)));
    strcpy(temp->type,gtk_entry_get_text (GTK_ENTRY(typeR)));
    temp->yeareffected = tm.tm_year + 1900;
    temp->montheffected = tm.tm_mon + 1;
    if(!iscandidate(temp->nom,temp->prenom) || !isoffre(temp->codeOffre)){
    	gtk_label_set_text (GTK_LABEL(rstR),"échec! code offre ou/et candidat n'existent pas!");
    	return;
    }
    FILE* ptr = fopen("Recrutements.txt","a+");
    fprintf(ptr,"%s\n",temp->id);
    fprintf(ptr,"%s\n",temp->nom);
    fprintf(ptr,"%s\n",temp->prenom);
    fprintf(ptr,"%s\n",temp->codeOffre);
    fprintf(ptr,"%s\n",temp->duree);
    fprintf(ptr,"%s\n",temp->type);
    fprintf(ptr,"%d\n",temp->yeareffected);
    fprintf(ptr,"%d\n",temp->montheffected);
    fclose(ptr);
    modifyordeleteoffre(temp->codeOffre,1, 0,"z");
    modifyordelete(1,temp->nom,temp->prenom,0,temp->nom);
    gtk_label_set_text (GTK_LABEL(rstR),"le contrat est bien ajouté");
}

void WindowAjouterRf(GtkWidget* widget,gpointer data){///ajouter GUI
    gtk_widget_destroy(WindowR);

    WindowAjouterR = GTK_WIDGET(gtk_builder_get_object(builder,"WindowAjouterR"));

    ConfirmerR = GTK_WIDGET(gtk_builder_get_object(builder,"AjouterCDD"));
    retR = GTK_WIDGET(gtk_builder_get_object(builder,"retverRdeA"));
    retPR = GTK_WIDGET(gtk_builder_get_object(builder,"retverPR"));
    nomR = GTK_WIDGET(gtk_builder_get_object(builder,"nomCR"));
    prenomR = GTK_WIDGET(gtk_builder_get_object(builder,"prenomCR"));
	codeR = GTK_WIDGET(gtk_builder_get_object(builder,"CodeR"));
    duree = GTK_WIDGET(gtk_builder_get_object(builder,"Duree"));
    typeR = GTK_WIDGET(gtk_builder_get_object(builder,"type"));
    rstR = GTK_WIDGET(gtk_builder_get_object(builder,"ResultatR"));
    idR = GTK_WIDGET(gtk_builder_get_object(builder,"idR"));

    g_signal_connect(ConfirmerR,"clicked",G_CALLBACK(funcAjouterR),NULL);
    g_signal_connect(retR,"clicked",G_CALLBACK(funcRetdeAoversR),NULL);
    g_signal_connect(retPR,"clicked",G_CALLBACK(funcretversPdeA),NULL);
    g_signal_connect(WindowAjouterR,"delete_event",G_CALLBACK(gtk_main_quit),NULL);
    g_signal_connect(WindowAjouterR, "key_press_event", G_CALLBACK(checkESC), NULL);
    gtk_widget_show_all(WindowAjouterR);
}
bool iscodeContrat(char* cherche){
	FILE* rptr = fopen("Recrutements.txt","r");
	char temp[CMAX];
	while (fscanf(rptr,"%[^\n]\n",temp)!=EOF){
            if (!strcmp(temp,cherche)){
            	fclose(rptr);
            	return true;
            }
            for (int i = 0 ; i<7 ; i++){
            	fscanf(rptr,"%[^\n]\n",temp);
            }
        }
	fclose(rptr);
	return false;
}
void funcAnnuler(GtkWidget* widget,gpointer data){
	char temp[CMAX],junk[CMAX];
    char num[CMAX],check[CMAX];
	strcpy(check,gtk_entry_get_text (GTK_ENTRY(codeAn)));
	if (!iscodeContrat(check)){
		gtk_label_set_text (GTK_LABEL(resAn),"le code n'est pas enregistré");
		return;
	}
    FILE* rptr = fopen("Recrutements.txt","r"),*newptr = fopen("temp.txt","w+");
    fscanf(rptr,"%[^\n]\n",num);
    while(true){
          if (!strcmp(check,num))
              break;
        fprintf(newptr,"%s\n",num);
        fscanf(rptr,"%[^\n]\n",num);
    }

    for (int i = 0 ; i<7 ; i++){
            fgets(junk,500,rptr);
        }
    while (fscanf(rptr,"%[^\n]\n",temp)!=EOF){
            fprintf(newptr,"%s\n",temp);
        }

    fclose(rptr);
    fclose(newptr);
    remove("Recrutements.txt");
    rename("temp.txt","Recrutements.txt");
    gtk_label_set_text (GTK_LABEL(resAn),"le contrat est bien supprimé");
    return;
}
void funcretversPdeAn(GtkWidget* widget, gpointer data){
    gtk_window_close(GTK_WINDOW(WindowAnnulerR));
    main();
    gtk_button_clicked(GTK_BUTTON(identifier));
}
void funcRetdeAnversR(GtkWidget* widget, gpointer data){
    //

    gtk_window_close(GTK_WINDOW(WindowAnnulerR));
    main();
    gtk_button_clicked(GTK_BUTTON(identifier));
    gtk_button_clicked (GTK_BUTTON(buttonContats));
}
void WindowAnnulerRf(GtkWidget* widget,gpointer data){
    gtk_widget_destroy(WindowR);

    WindowAnnulerR = GTK_WIDGET(gtk_builder_get_object(builder,"WindowAnnulerR"));

    AnnelerRet = GTK_WIDGET(gtk_builder_get_object(builder,"AnnulerCDD1"));
    retPRAn = GTK_WIDGET(gtk_builder_get_object(builder,"retverPR1"));
    retRAn = GTK_WIDGET(gtk_builder_get_object(builder,"retverRdeA1"));
    codeAn = GTK_WIDGET(gtk_builder_get_object(builder,"idR1"));
    resAn = GTK_WIDGET(gtk_builder_get_object(builder,"resAn"));


    g_signal_connect(AnnelerRet,"clicked",G_CALLBACK(funcAnnuler),NULL);
    g_signal_connect(retPRAn,"clicked",G_CALLBACK(funcretversPdeAn),NULL);
    g_signal_connect(retRAn,"clicked",G_CALLBACK(funcRetdeAnversR),NULL);
    g_signal_connect(WindowAnnulerR,"delete_event",G_CALLBACK(gtk_main_quit),NULL);
    g_signal_connect(WindowAnnulerR, "key_press_event", G_CALLBACK(checkESC), NULL);
    gtk_widget_show_all(WindowAnnulerR);
}

void funcafficherMonth(GtkWidget* widget,gpointer data){
	int counter=0;
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	char tempid[CMAX],tempname[CMAX],tempfname[CMAX],tempoffre[CMAX],tempduree[CMAX],temptype[20],tempyear[20],tempmonth[20];
	FILE* rptr = fopen("Recrutements.txt","r");
	char temp[CMAX];
	while (fscanf(rptr,"%[^\n]\n",temp)!=EOF){
		strcpy(tempid,temp);
		fscanf(rptr,"%[^\n]\n",temp);
		strcpy(tempname,temp);
		fscanf(rptr,"%[^\n]\n",temp);
		strcpy(tempfname,temp);
		fscanf(rptr,"%[^\n]\n",temp);
		strcpy(tempoffre,temp);
		fscanf(rptr,"%[^\n]\n",temp);
		strcpy(tempduree,temp);
		fscanf(rptr,"%[^\n]\n",temp);
		strcpy(temptype,temp);
		fscanf(rptr,"%[^\n]\n",temp);
		strcpy(tempyear,temp);
		fscanf(rptr,"%[^\n]\n",temp);
		strcpy(tempmonth,temp);
		if (atoi(tempmonth)==tm.tm_mon + 1){
			gtk_label_set_text (GTK_LABEL(codeRec[counter]),tempid);
	    	gtk_label_set_text (GTK_LABEL(nomRec[counter]),tempname);
	    	gtk_label_set_text (GTK_LABEL(prenomRec[counter]),tempfname);
	    	gtk_label_set_text (GTK_LABEL(codeOffreR[counter]),tempoffre);
	    	gtk_label_set_text (GTK_LABEL(dureeRec[counter]),tempduree);
	   		gtk_label_set_text (GTK_LABEL(typeRec[counter]),temptype);
	   		counter++;
		}
		if (counter>=10)
			break;
	}
	fclose(rptr);
	return;
}
void funcafficherYear(GtkWidget* widget,gpointer data){
	int counter=0;
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	char tempid[CMAX],tempname[CMAX],tempfname[CMAX],tempoffre[CMAX],tempduree[CMAX],temptype[20],tempyear[20],tempmonth[20];
	FILE* rptr = fopen("Recrutements.txt","r");
	char temp[CMAX];
	while (fscanf(rptr,"%[^\n]\n",temp)!=EOF){
		strcpy(tempid,temp);
		fscanf(rptr,"%[^\n]\n",temp);
		strcpy(tempname,temp);
		fscanf(rptr,"%[^\n]\n",temp);
		strcpy(tempfname,temp);
		fscanf(rptr,"%[^\n]\n",temp);
		strcpy(tempoffre,temp);
		fscanf(rptr,"%[^\n]\n",temp);
		strcpy(tempduree,temp);
		fscanf(rptr,"%[^\n]\n",temp);
		strcpy(temptype,temp);
		fscanf(rptr,"%[^\n]\n",temp);
		strcpy(tempyear,temp);
		fscanf(rptr,"%[^\n]\n",temp);
		strcpy(tempmonth,temp);
		if (atoi(tempyear)==tm.tm_year + 1900){
			gtk_label_set_text (GTK_LABEL(codeRec[counter]),tempid);
	    	gtk_label_set_text (GTK_LABEL(nomRec[counter]),tempname);
	    	gtk_label_set_text (GTK_LABEL(prenomRec[counter]),tempfname);
	    	gtk_label_set_text (GTK_LABEL(codeOffreR[counter]),tempoffre);
	    	gtk_label_set_text (GTK_LABEL(dureeRec[counter]),tempduree);
	   		gtk_label_set_text (GTK_LABEL(typeRec[counter]),temptype);
	   		counter++;
		}
		if (counter>=10)
			break;
	}
	fclose(rptr);
	return;
}
void WindowAfficherRec(GtkWidget* widget,gpointer data){
    gtk_widget_destroy(WindowR);

    WindowAfficherR = GTK_WIDGET(gtk_builder_get_object(builder,"AfficherRec"));
    char I[10],N[10],P[10],A[10],S[10],temp[10];
    for (int i = 1 ; i<=10 ;i++){
        strcpy(I,"id");
        sprintf(temp, "%d", i);
        strcat(I,temp);
        codeRec[i-1]=GTK_WIDGET(gtk_builder_get_object(builder,I));
        strcpy(N,"n");
        strcat(N,temp);
        nomRec[i-1]=GTK_WIDGET(gtk_builder_get_object(builder,N));
        strcpy(P,"p");
        strcat(P,temp);
        prenomRec[i-1]=GTK_WIDGET(gtk_builder_get_object(builder,P));
        strcpy(A,"o");
        strcat(A,temp);
        codeOffreR[i-1]=GTK_WIDGET(gtk_builder_get_object(builder,A));
        strcpy(S,"du");
        strcat(S,temp);
        dureeRec[i-1]=GTK_WIDGET(gtk_builder_get_object(builder,S));
        strcpy(S,"t");
        strcat(S,temp);
        typeRec[i-1]=GTK_WIDGET(gtk_builder_get_object(builder,S));
    }
    if (byyearormonth)
        funcafficherYear(widget,data);
    else funcafficherMonth(widget,data);
    g_signal_connect(WindowAfficherR,"delete_event",G_CALLBACK(gtk_main_quit),NULL);
    g_signal_connect(WindowAfficherR, "key_press_event", G_CALLBACK(checkESC), NULL);
    gtk_widget_show_all(WindowAfficherR);
}

void MonthWINDOW(GtkWidget* widget,gpointer data){
    byyearormonth = false;
    WindowAfficherRec(widget,data);
}
