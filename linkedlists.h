#include "candidat.h"

typedef struct _ListCandidats{
    Candidat *value;
    struct _ListCandidats *next;
}ListCandidats;
typedef ListCandidats* ptrliste;
bool eq(Candidat* c1,Candidat* c2){
    if (!strcmp(c1->ca_Nom,c2->ca_Nom))
        return false;
    if (!strcmp(c1->ca_Prenom,c2->ca_Prenom))
        return false;
    if (!strcmp(c1->ca_Adresse,c2->ca_Adresse))
        return false;
    if (!strcmp(c1->ca_specialite,c2->ca_specialite))
        return false;
    if (c1->ca_Index!=c2->ca_Index)
        return false;
    return true;
}
bool isempty(ptrliste head){
	if (head)
		return false;
	return true;
}
ptrliste push_back(ptrliste head,Candidat* value){// i will need insertbyorder when i know what is "ordre de merite"
	ptrliste temp =  Malloc(ListCandidats);
	temp->value=value;
	temp->next=NULL;
	if (isempty(head)){
		head=temp;
		return head;
	}
	ptrliste p = head;
	while (p->next)
		p=p->next;
	p->next = temp;
	return head;
}
bool candidatisinlist(ptrliste head,Candidat* value){
    if (isempty(head))
        return false;
    ptrliste p = head;
    while (p->next){
        if ((p->value)==value)
            return true;
        p=p->next;
    }
    return false;
}
ptrliste remove_candidat(ptrliste head,Candidat* value){
    if (isempty(head))
    {
        printf("liste vide!\n");
        return head;
    }
    ptrliste p = head;
    if (!candidatisinlist(head,value))
    {
        printf("candidat n'est pas dans la liste\n");
        return head;
    }
    if (p->value==value)
        return NULL;
    while (p->next)
    {
        if(eq(p->next->value,value)){
            ListCandidats *q=p->next;
            p->next=(p->next)->next;
            free(q);
            return head;
        }
        p=p->next;
    }
    return head;
}
