#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// defintion des structure utliser
typedef struct Date {
    int jour , mois , annee ;
} Date ;

typedef struct Permis {
    int NumPermis ;
    Date DateObtantion ;
    
} Permis;

typedef struct Personne {
    int identifiant; 
    int age;
    char nom[100]; 
    char prenom[100]; 
    char sexe[100] ;
    char adress[100];
    char email[100];
    char nationalite[100];
    int numtel ;
    Permis permis ; 
} Personne ;

typedef struct location { 
    Personne Data;
    Date DebutLocation ; 
    Date FinLocation ;
} Location; 

typedef struct voiture {
    char model[100]; 
    char matricule[100] ; 
    char couleur[100] ; 
    char etat[100];
    float PrixDeLocation ;
    float CautionParJour;
    float CautionParMois;
    float CautionParAns;
    Location LocataireActuelle ; //si la voiture n'est pas loue le nom du locataire sera "personne"
    char NomFicher[100]; 
} voiture ;

typedef struct marque {
    char nom[100];
    voiture data;
    struct marque *next;
} Marque;

//definition des fonction utliser
Date Dateactuelle(){
    Date aujourdhui ;
    printf("quelle est jour on est :");
    scanf("%d", &aujourdhui.jour);
    printf("En quelle mois on est :");
    scanf("%d", &aujourdhui.mois);
    printf("En quelle annee on est :");
    scanf("%d", &aujourdhui.annee);
    return aujourdhui;
}

Date SaisieDate(){
    Date date ;
    printf("Donner le jour :");
    scanf("%d", &date.jour);
    printf("Donner le mois :");
    scanf("%d", &date.mois);
    printf("Donner l'annee :");
    scanf("%d", &date.annee);
    return date;
}

int ClientValide(Date dateactuelle , Date datepermis){
    if(dateactuelle.annee - datepermis.annee < 2){
        return 0 ;
    }
    else{
        if(dateactuelle.mois > datepermis.mois){
            return 0;
        }
        else{
            if(dateactuelle.jour > datepermis.jour){
                return 0;
            }
        }
    }
    return 1;
}

void CreerLocataire(Personne client, Date dateactuelle){

    printf("quelle est le numero de permis du client :");
    scanf("%d", &client.permis.NumPermis);
    printf("quelle est la Date d'obtention du permis :");
    scanf("%d", client.permis.DateObtantion.jour);
    scanf("%d", client.permis.DateObtantion.mois);
    scanf("%d", client.permis.DateObtantion.annee);

    if(ClientValide(dateactuelle , client.permis.DateObtantion)){
        printf("le numero de la carte d'indentité du client :");
        scanf("%d", &client.identifiant);

        printf("quelle est le nom du client :");
        fgets(client.nom, 100, stdin) ;

        printf("quelle est le prenom du client :");
        fgets(client.prenom, 100, stdin);

        printf("quelle est le sexe du client :");
        fgets(client.sexe, 100, stdin);

        do{
            printf("quelle est l'age du client :");
            scanf("%d", &client.age);
        } while(client.age < 18) ; 

        printf("quelle est la nationalite du client :");
        fgets(client.nationalite, 100, stdin);

        printf("quelle est l'adress physique du client :");
        fgets(client.adress, 100, stdin);

        printf("quelle est l'adress mail du client :");
        fgets(client.email, 100, stdin);

        printf("quelle est le numero de telephone du client :");
        scanf("%d" , client.numtel);  
    } else {
        printf("Cette personne ne peut permette au personne en periode probatoire de louer une voiture") ;
    }
    
}

int TailleFichier(FILE *file_pointer){

    char line[1000];
    char **array_of_lines;
    int number_of_lines = 0;
    while (fgets(line, 1000, file_pointer) != NULL) {
        number_of_lines++;
    }

    rewind(file_pointer);
    return number_of_lines ;
}

Marque* MarqueList(char *NomFicher){
    FILE *ficherMarque = fopen(NomFicher, "rt");
    if(ficherMarque == NULL){
        printf("Le fichier n'existe pas veuillez verifier le Nom");
        fclose(ficherMarque);
        return NULL;
    }
    
    char line[1000];
    
    int taille = TailleFichier(ficherMarque);
    int taillelist = taille/10;
    Marque* list = malloc(taillelist * sizeof(Marque));
    for(int i = 0; i < taillelist; i++){

        fgets(line, 1000, ficherMarque);
        char *pos = strchr(line,':');
        int index = pos - line +1;
        strcpy((list+i)->nom, "");
        for(int j = index+1; line[j] != '\0'; j++){
            (list+i)->nom[j-index-1] = line[j];
        }

        fgets(line, 1000, ficherMarque);
        char *pos = strchr(line,':');
        int index = pos - line +1;
        strcpy((list+i)->data.model, "");
        for(int j = index+1; line[j] != '\0'; j++){
            (list+i)->data.model[j-index-1] = line[j];
        }

        fgets(line, 1000, ficherMarque);
        char *pos = strchr(line,':');
        int index = pos - line +1;
        strcpy((list+i)->data.matricule, "");
        for(int j = index+1; line[j] != '\0'; j++){
            (list+i)->data.matricule[j-index-1] = line[j];
        }

        fgets(line, 1000, ficherMarque);
        char *pos = strchr(line,':');
        int index = pos - line +1;
        strcpy((list+i)->data.couleur, "");
        for(int j = index+1; line[j] != '\0'; j++){
            (list+i)->data.couleur[j-index-1] = line[j];
        }

        fgets(line, 1000, ficherMarque);
        char *pos = strchr(line,':');
        int index = pos - line +1;
        strcpy((list+i)->data.etat, "");
        for(int j = index+1; line[j] != '\0'; j++){
             (list+i)->data.etat[j-index-1] = line[j];
        }

        fgets(line, 1000, ficherMarque);
        char *pos = strchr(line,':');
        int index = pos - line +1;
        char prix[100] = "";
        for(int j = index+1; line[j] != '\0'; j++){
            prix[j-index-1] = line[j];
        }
        (list+i)->data.PrixDeLocation = atof(prix) ;

        fgets(line, 1000, ficherMarque);
        char *pos = strchr(line,':');
        int index = pos - line +1;
        char Cj[100] = "";
        for(int j = index+1; line[j] != '\0'; j++){
            Cj[j-index-1] = line[j];
        }
        (list+i)->data.CautionParJour = atof(Cj) ;

        fgets(line, 1000, ficherMarque);
        char *pos = strchr(line,':');
        int index = pos - line +1;
        char Cm[100] = "";
        for(int j = index+1; line[j] != '\0'; j++){
            Cm[j-index-1] = line[j];
        }
        (list+i)->data.CautionParMois = atof(Cm) ;

        fgets(line, 1000, ficherMarque);
        char *pos = strchr(line,':');
        int index = pos - line +1;
        char Ca[100] = "";
        for(int j = index+1; line[j] != '\0'; j++){
            Ca[j-index-1] = line[j];
        }
        (list+i)->data.CautionParAns = atof(Ca);

        fgets(line, 1000, ficherMarque);
        char *pos = strchr(line,':');
        int index = pos - line +1;
        strcpy((list+i)->data.NomFicher, "");
        for(int j = index+1; line[j] != '\0'; j++){
            (list+i)->data.NomFicher[j-index-1] = line[j];
        }

        if(i == 0){
            (list+i)->next = NULL;
        }
        else{
            (list+i)->next = (list+i-1);
        }
    }

    fclose(ficherMarque);
    return list+taillelist ;
}

void AfficherVoiture(char *NomFicher){
    Marque *list = MarqueList(NomFicher);
    FILE *fichier = fopen(NomFicher, "rt");
    int taille = TailleFichier(fichier) / 10;
    for(int i = 0; i < taille; i++){
        Marque *temp = (list+i);
        while(temp != NULL){
            printf("le model de la voiture est: %s", temp->data.model);
            printf("la matricule de la voiture est: %s", temp->data.matricule);
            printf("la couleur de la voiture est: %s", temp->data.couleur);
            printf("l'etat de la voiture est: %s", temp->data.etat);
            printf("le prix de location de la voiture est: %f", temp->data.PrixDeLocation);
            printf("la cautisation par jour de la voiture est: %f celle par mois est : %f et celle par ans est : %f", temp->data.CautionParJour, temp->data.CautionParMois, temp->data.CautionParAns);
            temp = temp->next;
        }
    }
    fclose(fichier);
}

void SauvgardeDeModification(char *NomFichier){

    Marque *list = Marquelist(NomFichier);
    FILE *fichier = fopen(NomFichier, "wt");
    int taille =TailleFichier(fichier) / 10 ;
    for(int i = 0; i < taille ; i++){
        Marque *temp = list+i ;
        while(temp != NULL){
            char NomMarque[] = temp->nom;
            fprintf(fichier,"La marque de la voiture est: %s \n", NomMarque);
            char model[] = temp->data.model;
            fprintf(fichier,"Le model de la voiture est: %s \n", model);
            char matricule[] = temp->data.matricule;
            fprintf(fichier,"La matricule de la voiture est: %s \n", matricule);
            char couleur[] = temp->data.couleur;
            fprintf(fichier,"La couleur de la voiture est: %s \n", couleur);
            char etat[] = temp->data.etat;
            fprintf(fichier,"L'etat de la voiture est: %s \n", etat);
            char prix[1000];
            sprintf(prix, "%f", temp->data.PrixDeLocation);
            fprintf(fichier,"Le prix de location de la voiture est: %s \n", prix);
            char Cj[1000];
            sprintf(Cj, "%f", temp->data.CautionParJour);
            fprintf(fichier,"La cautisaion par jour de la voiture est: %s \n", Cj);
            char Cm[1000];
            sprintf(Cm, "%f", temp->data.CautionParMois);
            fprintf(fichier,"La cautisaion par mois de la voiture est: %s \n", Cm);
            char Ca[1000];
            sprintf(Ca, "%f", temp->data.CautionParAns);
            fprintf(fichier,"La cautisaion par ans de la voiture est: %s \n", Ca);
        }
    }
    fclose(fichier);
}

void SupprimeVoiturePanne(char *NomFichier){
    Marque *list = Marquelist(NomFichier);
    FILE *fichier = fopen(NomFichier, "wt");
    int taille = TailleFichier(fichier) / 9 ;
    for(int i = 0; i < taille ; i++){
        Marque *temp = list ;
        while(temp != NULL && temp->next != NULL){
            if(temp->next->data.etat == "Panne"){
                temp->next = temp->next->next ;
            }
            temp=temp->next ;
        }
    }
    SauvgardeDeModification(NomFichier);
    fclose(fichier);
}

void ModifierVoiture(voiture car, char Modification){
    if (strcmp(Modification, "tous") == 0){
        printf("quelle est la nouvelle matricule de la voiture :");
        scanf("%s", car.matricule);
        printf("quelle est la nouvelle couleur de la voiture :");
        scanf("%s", car.couleur);
        printf("quelle est le nouvel etat de la voiture :");
        scanf("%s", car.etat);
        printf("quelle est le nouvel prix de location de la voiture :");
        scanf("%f", &car.PrixDeLocation);
        printf("quelle est la nouvelle caution par jour de la voiture :");
        scanf("%f", &car.CautionParJour);
        printf("quelle est la nouvelle caution par mois de la voiture :");
        scanf("%f", &car.CautionParMois);
        printf("quelle est la nouvelle caution par ans de la voiture :");
        scanf("%f", &car.CautionParAns);
        printf("quelle est le nouveau ficher d'historique de location :");
        scanf("%s", car.NomFicher);
    }
    else if(strcmp(Modification, "matricule") == 0){
        printf("quelle est la nouvelle matricule de la voiture :");
        scanf("%s", car.matricule);
    }
    else if(strcmp(Modification, "couleur") == 0){
        printf("quelle est la nouvelle couleur de la voiture :");
        scanf("%s", car.couleur);
    }
    else if(strcmp(Modification, "etat") == 0){
        printf("quelle est le nouvel etat de la voiture :");
        scanf("%s", car.etat);
    }
    else if(strcmp(Modification, "prix") == 0){
        printf("quelle est le nouvel prix de location de la voiture :");
        scanf("%f", &car.PrixDeLocation);
        printf("quelle est la nouvelle caution par jour de la voiture :");
        scanf("%f", &car.CautionParJour);
        printf("quelle est la nouvelle caution par mois de la voiture :");
        scanf("%f", &car.CautionParMois);
        printf("quelle est la nouvelle caution par ans de la voiture :");
        scanf("%f", &car.CautionParAns);
    }
    else if(strcmp(Modification, "NomFichier") == 0){
        printf("Le nom du Fichier ne peut etre modifier au risque de perdre tous les informations stockees");
    }
    else{
        printf("Modification non reconnue");
    }       
}


void LouerVoiture(Personne client, voiture car, Date DateDebutLocation, Date DateFinLocation , char *NomFichierLocation){
    if(DateDebutLocation.annee > DateFinLocation.annee){
        printf("veuillez verifier les dates saisies");
    }
    else if(DateDebutLocation.mois > DateFinLocation.mois){
        printf("veuillez verifier les dates saisies");
    }
    else if(DateDebutLocation.jour > DateFinLocation.jour){
        printf("veuillez verifier les dates saisies");
    }
    else{
        if(car.LocataireActuelle.Data.nom == "Personne"){
            car.LocataireActuelle.Data = client;
            car.LocataireActuelle.DebutLocation = DateDebutLocation;
            car.LocataireActuelle.FinLocation = DateFinLocation;
            printf("la location c'est effectuer avec succes");
            FILE *HistoriqueLocation = fopen(NomFichierLocation, "w");
            char nom[] = client.nom;
            char indentifiant[8];
            itoa(client.identifiant, indentifiant, 10);
            char JourD[2];
            char MoisD[2];
            char AnneeD[4];
            char JourF[2];
            char MoisF[2];
            char AnneeF[4];
            itoa(DateDebutLocation.jour, JourD, 10);
            itoa(DateDebutLocation.mois, MoisD, 10);
            itoa(DateDebutLocation.annee, AnneeD, 10);
            itoa(DateFinLocation.jour, JourD, 10);
            itoa(DateFinLocation.mois, MoisD, 10);
            itoa(DateFinLocation.annee, AnneeD, 10);
            char dateD[11]; 
            sprintf(dateD, "%s/%s/%s", JourD, MoisD, AnneeD);
            char dateF[11]; 
            sprintf(dateF, "%s/%s/%s", JourF, MoisF, AnneeF);
            char ligne[100];
            sprintf(ligne, "Le client: %s, d'indentifiant: %s, à louer cette voiture du %s au %s", nom , indentifiant, dateD, dateF);
            fprintf(HistoriqueLocation, ligne);
            fclose(HistoriqueLocation);
        } 
        else{
            printf("Cette voiture est deja louer veuillez choisir une autre");
        }

    }
}

void HistoriqueDeLocation(voiture car){
    FILE *HistoriqueLocation = fopen(car.NomFicher, "rt");
    if(HistoriqueLocation == NULL){
        printf("Cette Voiture n'a jammais été louer");
    }
    else{
        char ligne[1000];
        while (fgets(ligne, 1000, HistoriqueLocation) != NULL) {
            printf("%s", ligne);
        }
    }
    fclose(HistoriqueLocation);
}

void RetourSousReclamation(voiture car){
    strcpy(car.LocataireActuelle.Data.nom, "Personne");
    char Reclamation[1000];
    printf("quelle est le type de reclamation ?");
    scanf("%s", Reclamation);
    ModifierVoiture(car, Reclamation);
}


//fonction main

int main(){
    Date Aujourdhui;
    Personne client;
    Marque *list_de_voiture_disponible;
    Date debutlocation, DateFinLocation ;

    Aujourdhui = Dateactuelle();
    CreerLocataire(client, Aujourdhui);
    debutlocation = SaisieDate();
    DateFinLocation = SaisieDate();
    list_de_voiture_disponible = MarqueList("MarqueRENAULT.txt");
    AfficherVoiture("MarqueRENAULT.txt");
    strcpy(list_de_voiture_disponible->data.LocataireActuelle.Data.nom, "Personne");
    LouerVoiture(client, list_de_voiture_disponible->data, debutlocation , DateFinLocation, list_de_voiture_disponible->data.NomFicher);
    HistoriqueDeLocation(list_de_voiture_disponible->data);
    RetourSousReclamation(list_de_voiture_disponible->data);
    SupprimeVoiturePanne("MarqueRENAULT.txt");
}
