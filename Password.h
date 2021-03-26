#include "Rectutement.h"

/*
la gestion de la premiere fenetre
*/

bool checkuserandpass(char* checkuser,char* checkpass){// voir si checkuser/checkpass correspond à un utilisateur
	FILE* rptr = fopen("passwords.txt","r");
	char temp[CMAX];
	while (fscanf(rptr,"%[^\n]\n",temp)!=EOF){
            if (!strcmp(temp,checkuser)){
            	if (fscanf(rptr,"%[^\n]\n",temp)!=EOF){
            		if (!strcmp(temp,checkpass)){
            			fclose(rptr);
            			return true;
            		}	
            	}
            	
            }
        }
	fclose(rptr);
	return false;
}
void checkAccepted(GtkWidget* widget, gpointer data){//fonction qui choisir à ouvrir la fenetre primaire ou pas 
													// après fait appel a la fonction checkuserandpass
	char userentered[CMAX],passentered[CMAX];
	strcpy(userentered,gtk_entry_get_text (GTK_ENTRY(usernameEntry)));
	strcpy(passentered,gtk_entry_get_text (GTK_ENTRY(passwordEntry)));
	if (userisSafe){
		WindowPrimaire(widget,data);
	}
	if (checkuserandpass(userentered,passentered)){
		userisSafe = true;
		WindowPrimaire(widget,data);
		return;
	}
	else {
		gtk_label_set_text (GTK_LABEL(accepted),"ERREUR Utilisateur et/ou Mot de passe");
		return;
	}
}
void funcWindowInfo(GtkWidget* widget, gpointer data){// la fenetre des infos sur l'inscription
	WindowInfo = GTK_WIDGET(gtk_builder_get_object(builder,"signupWindow"));

	gtk_widget_show_all(WindowInfo);
}