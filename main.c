#include "Password.h"

void WindowCandidats(GtkWidget* widget, gpointer data){//la fenêtre de la gestion des candidats
    ///traitement des candidats
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

    g_signal_connect(AfficherOffresC,"clicked",G_CALLBACK(funcAfficherOffresC),NULL);
    g_signal_connect(WindowC,"delete-event",G_CALLBACK(quitmainWindowC),NULL);
    g_signal_connect(RetournerC,"clicked",G_CALLBACK(funcRetournerdeMenuCandidat),NULL);
    g_signal_connect(Ajouter,"clicked",G_CALLBACK(funcAjouterCandidat),NULL);
    g_signal_connect(Modifier,"clicked",G_CALLBACK(funcModifierCandidat),NULL);
    g_signal_connect(Afficher,"clicked",G_CALLBACK(funcAfficherCandidats),NULL);
    g_signal_connect(WindowC, "key_press_event", G_CALLBACK(checkESC), NULL);


    gtk_widget_show_all(WindowC);
}



void WindowOffre(GtkWidget* widget, gpointer data){//la fenêtre de la gestion des offres
    gtk_widget_destroy(Window);
    GtkWidget *Ajouter,*Modifier,*Afficher,*AfficherCandidatsF,*RetournerO;

    WindowO = GTK_WIDGET(gtk_builder_get_object(builder,"GestionDesOffres"));
    Ajouter = GTK_WIDGET(gtk_builder_get_object(builder,"AjouterCandidat1"));
    Modifier = GTK_WIDGET(gtk_builder_get_object(builder,"ModifierCandidat1"));
    Afficher = GTK_WIDGET(gtk_builder_get_object(builder,"AfficherOffres"));
    AfficherCandidatsF = GTK_WIDGET(gtk_builder_get_object(builder,"AfficherOffresCandidat1"));
    RetournerO = GTK_WIDGET(gtk_builder_get_object(builder,"RetournerOffres"));


    g_signal_connect(Ajouter,"clicked",G_CALLBACK(funcAjouterOffre),NULL);
    g_signal_connect(Afficher,"clicked",G_CALLBACK(AfficherOffresSortedO),NULL);
    g_signal_connect(Modifier,"clicked",G_CALLBACK(ModifierouSuppOffre),NULL);
    g_signal_connect(RetournerO,"clicked",G_CALLBACK(funcRetournerdeO),NULL);
    g_signal_connect(AfficherCandidatsF,"clicked",G_CALLBACK(afficherCandidatsO),NULL);
    g_signal_connect(WindowO,"delete-event",G_CALLBACK(gtk_main_quit),NULL);
    g_signal_connect(WindowO, "key_press_event", G_CALLBACK(checkESC), NULL);
    gtk_widget_show_all(WindowO);
}
void WindowRecrutement(GtkWidget* widget, gpointer data){//la fenêtre de la gestion des contrats
    
    gtk_widget_destroy(Window);

    GtkWidget *AjouterRec,*AnnulerRec,*AfficherRec,*RetournerR,*AfficherMonth;

    WindowR = GTK_WIDGET(gtk_builder_get_object(builder,"GestionDeRecrutement"));
    AjouterRec = GTK_WIDGET(gtk_builder_get_object(builder,"AjouterRec"));
    AnnulerRec = GTK_WIDGET(gtk_builder_get_object(builder,"AnnulerRec"));
    AfficherRec = GTK_WIDGET(gtk_builder_get_object(builder,"AfficherRecAN"));
    RetournerR = GTK_WIDGET(gtk_builder_get_object(builder,"RetournerR"));
    AfficherMonth = GTK_WIDGET(gtk_builder_get_object(builder,"AfficherRecMOIS"));
    g_signal_connect(AnnulerRec,"clicked",G_CALLBACK(WindowAnnulerRf),NULL);
    g_signal_connect(AjouterRec,"clicked",G_CALLBACK(WindowAjouterRf),NULL);
    g_signal_connect(AfficherRec,"clicked",G_CALLBACK(WindowAfficherRec),NULL);
    g_signal_connect(AfficherMonth,"clicked",G_CALLBACK(MonthWINDOW),NULL);
    g_signal_connect(RetournerR,"clicked",G_CALLBACK(RetournerVersMenuPrincipaldeMenuRec),NULL);
    g_signal_connect(WindowR,"delete-event",G_CALLBACK(gtk_main_quit),NULL);
    g_signal_connect(WindowR, "key_press_event", G_CALLBACK(checkESC), NULL);


    gtk_widget_show_all(WindowR);
}
void WindowPrimaire(GtkWidget* widget, gpointer data){// la fenêtre primaire
    gtk_widget_destroy(WindowSecure);
    Window = GTK_WIDGET(gtk_builder_get_object(builder,"PrimaryWindow"));

    buttonCandidats = GTK_WIDGET(gtk_builder_get_object(builder,"ButtonCandidats"));
    buttonOffres = GTK_WIDGET(gtk_builder_get_object(builder,"ButtonOffres"));
    buttonContats = GTK_WIDGET(gtk_builder_get_object(builder,"ButtonRecrutement"));



    g_signal_connect(buttonCandidats,"clicked",G_CALLBACK(WindowCandidats),NULL);
    g_signal_connect(buttonOffres,"clicked",G_CALLBACK(WindowOffre),NULL);
    g_signal_connect(buttonContats,"clicked",G_CALLBACK(WindowRecrutement),NULL);
    g_signal_connect(Window,"delete-event",G_CALLBACK(quitmainWindow),NULL);
    g_signal_connect(Window, "key_press_event", G_CALLBACK(checkESC), NULL);

    gtk_widget_show_all(Window);
}

int main(int argc,char* argv[]){// la premiere fenetre (securisé)
    indice=numberOfCandidats();//initializing indice
    gtk_init(&argc,&argv);
    WindowCisopen = false,WindowLireCisopen=false,WindowModifierisopen=false;
    builder = gtk_builder_new_from_file("temp.glade");
    WindowSecure = GTK_WIDGET(gtk_builder_get_object(builder,"Secure"));
    identifier = GTK_WIDGET(gtk_builder_get_object(builder,"enter"));
    inscrire = GTK_WIDGET(gtk_builder_get_object(builder,"signupButton"));
    usernameEntry= GTK_WIDGET(gtk_builder_get_object(builder,"username"));
    passwordEntry= GTK_WIDGET(gtk_builder_get_object(builder,"password"));
    accepted = GTK_WIDGET(gtk_builder_get_object(builder,"accepted"));


    g_signal_connect(identifier,"clicked",G_CALLBACK(checkAccepted),NULL);
    g_signal_connect(inscrire,"clicked",G_CALLBACK(funcWindowInfo),NULL);
    g_signal_connect(WindowSecure,"delete-event",G_CALLBACK(quitmainWindow),NULL);
    g_signal_connect(WindowSecure, "key_press_event", G_CALLBACK(checkESC), NULL);

    gtk_widget_show_all(WindowSecure);
    gtk_main();
    return 0;
}
