#include "CandidatGUIfunctions.h"

/*
DONE:
    Open cadidates management window
    configure button "sortir"
    button : retourner

*/




void WindowCandidats(GtkWidget* widget, gpointer data){// traitement des candidats
    gtk_window_close(GTK_WINDOW(Window));
    WindowCisopen = true;

    GtkWidget *Ajouter,*Modifier,*Supprimer,*Afficher,*AfficherOffresC,*RetournerC;

    WindowC = GTK_WIDGET(gtk_builder_get_object(builder,"GestionDesCandidats"));
    Ajouter = GTK_WIDGET(gtk_builder_get_object(builder,"AjouterCandidat"));
    Modifier = GTK_WIDGET(gtk_builder_get_object(builder,"ModifierCandidat"));
    Supprimer = GTK_WIDGET(gtk_builder_get_object(builder,"SupprimerCandidat"));
    Afficher = GTK_WIDGET(gtk_builder_get_object(builder,"AfficherCandidats"));
    AfficherOffresC = GTK_WIDGET(gtk_builder_get_object(builder,"AfficherOffresCandidat"));
    RetournerC = GTK_WIDGET(gtk_builder_get_object(builder,"RetournerCandidats"));

    g_signal_connect(WindowC,"delete-event",G_CALLBACK(quitmainWindowC),NULL);
    g_signal_connect(RetournerC,"clicked",G_CALLBACK(funcRetournerdeMenuCandidat),NULL);
    g_signal_connect(Ajouter,"clicked",G_CALLBACK(funcAjouterCandidat),NULL);


    gtk_widget_show_all(WindowC);
}

int main(int argc,char* argv[]){
    indice=numberOfCandidats();//initializing indice
    gtk_init(&argc,&argv);
    
    WindowCisopen = false,WindowLireCisopen=false;// 7it n9dro nkono 7alin dik fenetre mra fayta o db sdinaha
    builder = gtk_builder_new_from_file("temp.glade");
    Window = GTK_WIDGET(gtk_builder_get_object(builder,"PrimaryWindow"));
    buttonCandidats = GTK_WIDGET(gtk_builder_get_object(builder,"ButtonCandidats"));
    buttonOffres = GTK_WIDGET(gtk_builder_get_object(builder,"ButtonOffres"));
    buttonContats = GTK_WIDGET(gtk_builder_get_object(builder,"ButtonRecrutement"));


    g_signal_connect(buttonCandidats,"clicked",G_CALLBACK(WindowCandidats),NULL);
    g_signal_connect(Window,"delete-event",G_CALLBACK(quitmainWindow),NULL);
    //g_signal_connect(buttonSortir,"clicked",G_CALLBACK(gtk_main_quit),NULL);

    gtk_widget_show_all(Window);
    gtk_main();
    return 0;
}
