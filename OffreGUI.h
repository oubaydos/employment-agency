#include "CandidatGUIfunctions.h"


GtkWidget *WindowLireO;
GtkWidget *code,*entr,*inti,*villezip,*sal,*dateoff,*resultajouterO,*nom1,*nom2;
GtkWidget  *confirmerO,*retversprincO,*Retversoffre,*viderO,*RetversoffredeM,*resModO,*SuppO,*newCode;
GtkWidget *WindowModifierO,*retversprincOdeM,*viderMO,*modCodeO,*modEntrepO,*modIntO,*modVilleO,*modSalO,*modDateO,*codeaMod;
GtkWidget *WindowAffSorted,*Code[20],*Ent[20],*Intitul[20],*Vil[20],*Sala[20],*Dat[20];
GtkWidget *afficherCandidatSuc,*can1,*can2,*entryoff,*confirmersearch;
void funcRetournerdeO(GtkWidget* widget, gpointer data){ // retourner de menu offres
                                                                               //vers la fenetre principale
    gtk_window_close(GTK_WINDOW(WindowO));
    main();
    gtk_button_clicked(GTK_BUTTON(identifier));
    gtk_button_clicked(GTK_BUTTON(identifier));
}


void AjouterOffre(GtkWidget *widget,  gpointer data){///fonction ajouter offre
    FILE* ptr = fopen("offres.txt","a+");
    Offre *temp = Malloc(Offre);
    strcpy(temp->code,gtk_entry_get_text (GTK_ENTRY(code)));
    strcpy(temp->entrep_Nom,gtk_entry_get_text (GTK_ENTRY(entr)));
    strcpy(temp->intitule,gtk_entry_get_text (GTK_ENTRY(inti)));

    temp->salaire=atoi(gtk_entry_get_text (GTK_ENTRY(sal)));
    strcpy(temp->ville,gtk_entry_get_text (GTK_ENTRY(villezip)));
    strcpy(temp->date,gtk_entry_get_text (GTK_ENTRY(dateoff)));
    strcpy(temp->listeCandidat[0],gtk_entry_get_text (GTK_ENTRY(nom1)));
    strcpy(temp->listeCandidat[1],gtk_entry_get_text (GTK_ENTRY(nom2)));

    if (!isdate(temp->date)){
    	fclose(ptr);
    	gtk_label_set_text(GTK_LABEL(resultajouterO),"échec! changer la date svp!");
    	return;
    }

    fprintf(ptr,"%s\n",temp->code);
    fprintf(ptr,"%s\n",temp->entrep_Nom);
    fprintf(ptr,"%s\n",temp->ville);
    fprintf(ptr,"%s\n",temp->intitule);
    fprintf(ptr,"%d\n",temp->salaire);
    fprintf(ptr,"%s\n",temp->date);
    fprintf(ptr,"%s\n",temp->listeCandidat[0]);
    fprintf(ptr,"%s\n",temp->listeCandidat[1]);
    fprintf(ptr,"EndOfOffer\n");
    fclose(ptr);
    gtk_label_set_text (GTK_LABEL(resultajouterO),"l'offre est bien ajoutée");


    return;
}
void viderfuncO(GtkWidget *widget,  gpointer data){///button vider
    gtk_entry_set_text (GTK_ENTRY(code),"");
    gtk_entry_set_text (GTK_ENTRY(entr),"");
    gtk_entry_set_text (GTK_ENTRY(inti),"");
    gtk_entry_set_text (GTK_ENTRY(sal),"");
    gtk_entry_set_text (GTK_ENTRY(villezip),"");
    gtk_entry_set_text (GTK_ENTRY(dateoff),"");
    gtk_label_set_text (GTK_LABEL(resultajouterO),"");


}
void funcretversPlireO(GtkWidget* widget, gpointer data){ 
    gtk_window_close(GTK_WINDOW(WindowLireO));
    main();
    gtk_button_clicked(GTK_BUTTON(identifier));
    gtk_button_clicked(GTK_BUTTON(identifier));
}
void funcRetdeoversO(GtkWidget* widget, gpointer data){ 
    //

    gtk_window_close(GTK_WINDOW(WindowLireO));
    main();
    gtk_button_clicked(GTK_BUTTON(identifier));
    gtk_button_clicked(GTK_BUTTON(identifier));
    gtk_button_clicked (GTK_BUTTON(buttonOffres));


}
void funcAjouterOffre(GtkWidget* widget,gpointer data){
    gtk_widget_destroy(WindowO);

    WindowLireO = GTK_WIDGET(gtk_builder_get_object(builder,"LireOffre"));

    confirmer = GTK_WIDGET(gtk_builder_get_object(builder,"ConfirmerLire1"));
    retversprincO = GTK_WIDGET(gtk_builder_get_object(builder,"retversprinc1"));
    Retversoffre = GTK_WIDGET(gtk_builder_get_object(builder,"retversoffre"));
    viderO = GTK_WIDGET(gtk_builder_get_object(builder,"clear1"));
    nom1 = GTK_WIDGET(gtk_builder_get_object(builder,"nom1"));
	nom2 = GTK_WIDGET(gtk_builder_get_object(builder,"nom2"));
    code = GTK_WIDGET(gtk_builder_get_object(builder,"code"));
    entr = GTK_WIDGET(gtk_builder_get_object(builder,"entrep"));
    inti = GTK_WIDGET(gtk_builder_get_object(builder,"intitule"));
    villezip = GTK_WIDGET(gtk_builder_get_object(builder,"ville"));
    sal = GTK_WIDGET(gtk_builder_get_object(builder,"salaire"));
    dateoff = GTK_WIDGET(gtk_builder_get_object(builder,"date"));

    resultajouterO = GTK_WIDGET(gtk_builder_get_object(builder,"resultajouter1"));

    g_signal_connect(confirmer,"clicked",G_CALLBACK(AjouterOffre),NULL);
    g_signal_connect(viderO,"clicked",G_CALLBACK(viderfuncO),NULL);
    g_signal_connect(retversprincO,"clicked",G_CALLBACK(funcretversPlireO),NULL);
    g_signal_connect(Retversoffre,"clicked",G_CALLBACK(funcRetdeoversO),NULL);
    g_signal_connect(WindowLireO,"delete_event",G_CALLBACK(gtk_main_quit),NULL);
    g_signal_connect(WindowLireO, "key_press_event", G_CALLBACK(checkESC), NULL);
    gtk_widget_show_all(WindowLireO);
}
//done with ajouter

void funcModO(GtkWidget* widget,gpointer data){
	int choice =GPOINTER_TO_INT(data);
	char tempcode[CMAX],tempnew[500];
	strcpy(tempcode,gtk_entry_get_text (GTK_ENTRY(codeaMod)));
	strcpy(tempnew,gtk_entry_get_text (GTK_ENTRY(newCode)));
	if (!isoffre(tempcode)){
		gtk_label_set_text (GTK_LABEL(resModO),"échec! code offre n'existe pas!");
		return;
	}
	if (choice == 6 && !isdate(tempnew)){
		gtk_label_set_text (GTK_LABEL(resModO),"échec : Format de date!");
		return;
	}
	modifyordeleteoffre(tempcode,choice, 1,tempnew);
	gtk_label_set_text (GTK_LABEL(resModO),"l'offre est bien modifié");

}
void funcSuppO(GtkWidget* widget,gpointer data){

	char tempcode[CMAX];
	strcpy(tempcode,gtk_entry_get_text (GTK_ENTRY(codeaMod)));
	if (!isoffre(tempcode)){
		gtk_label_set_text (GTK_LABEL(resModO),"échec! code offre n'existe pas!");
		return;
	}

	modifyordeleteoffre(tempcode,1, 0,tempcode);
	gtk_label_set_text (GTK_LABEL(resModO),"l'offre est bien supprimée");

}
void funcViderMO(GtkWidget* widget,gpointer data){

	gtk_entry_set_text (GTK_ENTRY(codeaMod),"");
    gtk_entry_set_text (GTK_ENTRY(newCode),"");
    gtk_label_set_text (GTK_LABEL(resModO),"");

}
void funcretversPdeM(GtkWidget* widget, gpointer data){ 
    gtk_window_close(GTK_WINDOW(WindowModifierO));
    main();
    gtk_button_clicked(GTK_BUTTON(identifier));
    gtk_button_clicked(GTK_BUTTON(identifier));
}
void funcRetdeMversO(GtkWidget* widget, gpointer data){ 
    //

    gtk_window_close(GTK_WINDOW(WindowModifierO));
    main();
    gtk_button_clicked(GTK_BUTTON(identifier));
    gtk_button_clicked(GTK_BUTTON(identifier));
    gtk_button_clicked (GTK_BUTTON(buttonOffres));


}
void ModifierouSuppOffre(GtkWidget* widget,gpointer data){
    gtk_widget_destroy(WindowO);

    WindowModifierO = GTK_WIDGET(gtk_builder_get_object(builder,"modifierOffre"));
    int c=1,e=2,v=3,i=4,s=5,d=6;
    retversprincOdeM = GTK_WIDGET(gtk_builder_get_object(builder,"retversPdeO"));
    RetversoffredeM = GTK_WIDGET(gtk_builder_get_object(builder,"retversOdeM"));
    viderMO = GTK_WIDGET(gtk_builder_get_object(builder,"clearOffre"));
    modCodeO = GTK_WIDGET(gtk_builder_get_object(builder,"modifierCode"));
    modEntrepO = GTK_WIDGET(gtk_builder_get_object(builder,"modifierEntreprise"));
    modIntO = GTK_WIDGET(gtk_builder_get_object(builder,"modifierIntitule"));
    modVilleO = GTK_WIDGET(gtk_builder_get_object(builder,"modifierVille"));
    modSalO = GTK_WIDGET(gtk_builder_get_object(builder,"modifierSalaire"));
    modDateO = GTK_WIDGET(gtk_builder_get_object(builder,"modifierDate"));
    SuppO = GTK_WIDGET(gtk_builder_get_object(builder,"SupprimerOffre"));

    codeaMod = GTK_WIDGET(gtk_builder_get_object(builder,"CodeModifier"));
    newCode = GTK_WIDGET(gtk_builder_get_object(builder,"nouveauCode"));

    resModO = GTK_WIDGET(gtk_builder_get_object(builder,"resultatModifier"));
    g_signal_connect(modCodeO,"clicked",G_CALLBACK(funcModO),GINT_TO_POINTER (c));
    g_signal_connect(modEntrepO,"clicked",G_CALLBACK(funcModO),GINT_TO_POINTER (e));
    g_signal_connect(modVilleO,"clicked",G_CALLBACK(funcModO),GINT_TO_POINTER (v));
    g_signal_connect(modIntO,"clicked",G_CALLBACK(funcModO),GINT_TO_POINTER (i));
    g_signal_connect(modSalO,"clicked",G_CALLBACK(funcModO),GINT_TO_POINTER (s));
    g_signal_connect(modDateO,"clicked",G_CALLBACK(funcModO),GINT_TO_POINTER (d));
    g_signal_connect(SuppO,"clicked",G_CALLBACK(funcSuppO),NULL);
    g_signal_connect(viderMO,"clicked",G_CALLBACK(funcViderMO),NULL);
    g_signal_connect(retversprincOdeM,"clicked",G_CALLBACK(funcretversPdeM),NULL);
    g_signal_connect(RetversoffredeM,"clicked",G_CALLBACK(funcRetdeMversO),NULL);
    g_signal_connect(WindowModifierO,"delete_event",G_CALLBACK(gtk_main_quit),NULL);
    g_signal_connect(WindowModifierO, "key_press_event", G_CALLBACK(checkESC), NULL);
    gtk_widget_show_all(WindowModifierO);
}
//done with modifier/supp un offre;
void funcAfficherOffres(){
	int num = numberofoffres();
	char** list=sortspec();
	for (int i = 0 ; i<min(num,20);i++){
		char **totalList = getdatafromintitule(list[i]);
		gtk_label_set_text (GTK_LABEL(Code[i]),totalList[0]);
	    gtk_label_set_text (GTK_LABEL(Ent[i]),totalList[1]);
	    gtk_label_set_text (GTK_LABEL(Intitul[i]),totalList[3]);
	    gtk_label_set_text (GTK_LABEL(Vil[i]),totalList[2]);
	    gtk_label_set_text (GTK_LABEL(Sala[i]),totalList[4]);
	    gtk_label_set_text (GTK_LABEL(Dat[i]),totalList[5]);
	}
}
void AfficherOffresSortedO(GtkWidget* widget,gpointer data){///ajouter GUI
    gtk_widget_destroy(WindowO);

    WindowAffSorted = GTK_WIDGET(gtk_builder_get_object(builder,"AfficherOffresSorted"));
    char I[5],N[5],P[5],A[5],S[5],temp[5];
    for (int i = 0 ; i<20 ;i++){
        strcpy(I,"c");
        sprintf(temp, "%d", i);
        strcat(I,temp);
        Code[i]=GTK_WIDGET(gtk_builder_get_object(builder,I));
        strcpy(N,"e");
        strcat(N,temp);
        Ent[i]=GTK_WIDGET(gtk_builder_get_object(builder,N));
        strcpy(P,"i");
        strcat(P,temp);
        Intitul[i]=GTK_WIDGET(gtk_builder_get_object(builder,P));
        strcpy(A,"v");
        strcat(A,temp);
        Vil[i]=GTK_WIDGET(gtk_builder_get_object(builder,A));
        strcpy(S,"s");
        strcat(S,temp);
        Sala[i]=GTK_WIDGET(gtk_builder_get_object(builder,S));
        strcpy(S,"d");
        strcat(S,temp);
        Dat[i]=GTK_WIDGET(gtk_builder_get_object(builder,S));
    }

    g_signal_connect(WindowAffSorted,"delete_event",G_CALLBACK(gtk_main_quit),NULL);
    g_signal_connect(WindowAffSorted, "key_press_event", G_CALLBACK(checkESC), NULL);
    funcAfficherOffres();
    gtk_widget_show_all(WindowAffSorted);
}

void funcaff(GtkWidget* widget,gpointer data){
	char temp1[CMAX];
	strcpy(temp1,gtk_entry_get_text (GTK_ENTRY(entryoff)));
	if (!isoffre(temp1)){
		gtk_label_set_text(GTK_LABEL(can1),"échec! l'offre entrée n'existe pas!");
		return;
	}
	FILE *ptr = fopen("offres.txt","r");
    
    char temp[CMAX],junk[CMAX];
    while (fscanf(ptr,"%[^\n]\n",temp)!=EOF){
        if (!strcmp(temp,temp1))
            {
                for (int i=0;i<5;i++){
                    fgets(junk,CMAX,ptr);
                }
                
                fscanf(ptr,"%[^\n]\n",temp);
                if (temp[0]=='E' && temp[1]=='n'&&temp[2]=='d')
                    break;
                gtk_label_set_text(GTK_LABEL(can1),temp);
                fscanf(ptr,"%[^\n]\n",temp);
                if (temp[0]=='E' && temp[1]=='n'&&temp[2]=='d')
                    break;
                gtk_label_set_text(GTK_LABEL(can2),temp);
                return ;
            }
    }
    fclose(ptr);
    return ;
}
void afficherCandidatsO(GtkWidget* widget,gpointer data){
	gtk_widget_destroy(WindowO);
	afficherCandidatSuc = GTK_WIDGET(gtk_builder_get_object(builder,"candidatSusceptible"));

	can1 = GTK_WIDGET(gtk_builder_get_object(builder,"can1"));
	can2 = GTK_WIDGET(gtk_builder_get_object(builder,"can2"));
	entryoff = GTK_WIDGET(gtk_builder_get_object(builder,"entryOffre"));
	confirmersearch = GTK_WIDGET(gtk_builder_get_object(builder,"confirmersearch"));

	g_signal_connect(confirmersearch,"clicked",G_CALLBACK(funcaff),NULL);
	g_signal_connect(afficherCandidatSuc,"delete_event",G_CALLBACK(gtk_main_quit),NULL);
    g_signal_connect(afficherCandidatSuc, "key_press_event", G_CALLBACK(checkESC), NULL);
    gtk_widget_show_all(afficherCandidatSuc);
}
