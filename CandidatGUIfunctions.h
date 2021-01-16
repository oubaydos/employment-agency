#include <gtk/gtk.h>
#include "offre.h"

GtkBuilder *builder; // builder
GtkWidget *Window,*WindowC,*WindowLireC; // windows
GtkWidget *nom,*prenom,*adresse,*specialite; // entry
GtkWidget *buttonCandidats,*buttonOffres,*buttonContats;//primary window buttons
GtkWidget *vider,*confirmer,*retversprinc,*retverscandidat,*resultajouter;//lire buttons - label

bool WindowCisopen = false,WindowLireCisopen=false;
Candidat* temp;
void quitmainWindow(GtkWidget* widget,gpointer data){//sortir du fenetre premiere
    if(!WindowCisopen)//need other cases for offers and recruitements
        gtk_main_quit();
    else
        gtk_window_close(GTK_WINDOW(Window));
}
void quitmainWindowC(GtkWidget* widget,gpointer data){//sortir du fenetre premiere
    if(!WindowLireCisopen)//need other cases for offers and recruitements
        gtk_main_quit();
    else
        gtk_window_close(GTK_WINDOW(WindowC));
}

static void funcRetournerdeMenuCandidat(GtkWidget* widget, gpointer data){ // retourner de menu candidat
                                                                               //vers la fenetre principale
    WindowCisopen = false;
    gtk_window_close(GTK_WINDOW(WindowC));
    main();
}
static void funcRetdeLireversPrin(GtkWidget* widget, gpointer data){ // retourner de lire vers la fenetre principale
    WindowLireCisopen=false;
    gtk_window_close(GTK_WINDOW(WindowLireC));
    main();
}
static void funcRetdeLireverscandidat(GtkWidget* widget, gpointer data){ // retourner de lire vers menu candidat
    //
    
    WindowLireCisopen=false;
    gtk_window_close(GTK_WINDOW(WindowLireC));
    main();
    gtk_button_clicked (GTK_BUTTON(buttonCandidats));


}
void viderfunc(GtkWidget *widget,  gpointer data){
    gtk_entry_set_text (nom,"");
    gtk_entry_set_text (prenom,"");
    gtk_entry_set_text (adresse,"");
    gtk_entry_set_text (specialite,"");
    gtk_label_set_text (resultajouter,"");
}
static void Ajouterfunc(GtkWidget *widget,  gpointer data){
    FILE* candidatsfile = fopen("candidats.txt","a+");
    temp = Malloc(Candidat);
    strcpy(temp->ca_Nom,gtk_entry_get_text (GTK_ENTRY(nom)));
    strcpy(temp->ca_Prenom,gtk_entry_get_text (GTK_ENTRY(prenom)));
    strcpy(temp->ca_Adresse,gtk_entry_get_text (GTK_ENTRY(adresse)));
    strcpy(temp->ca_specialite,gtk_entry_get_text (GTK_ENTRY(specialite)));
    temp->ca_Index = indice++;
    fprintf(candidatsfile,"%d\n",temp->ca_Index);
    fprintf(candidatsfile,"%s\n",temp->ca_Nom);
    fprintf(candidatsfile,"%s\n",temp->ca_Prenom);
    fprintf(candidatsfile,"%s\n",temp->ca_Adresse);
    fprintf(candidatsfile,"%s\n",temp->ca_specialite);
    printf("le candidat est bien ajoute\n");
    fclose(candidatsfile);
    gtk_label_set_text (resultajouter,"le candidat est bien ajoute");
    /*gtk_entry_set_text (nom,"");
    gtk_entry_set_text (prenom,"");
    gtk_entry_set_text (adresse,"");
    gtk_entry_set_text (specialite,"");*/
    return;
}
static void funcAjouterCandidat(GtkWidget* widget,gpointer data){
    gtk_window_close(GTK_WINDOW(WindowC));
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
    gtk_widget_show_all(WindowLireC);
}
