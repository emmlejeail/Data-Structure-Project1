#include "tp3.h"

T_Produit *creerProduit(char *marque, float prix, char qualite, int quantite)
{
    T_Produit *prod = malloc(sizeof(T_Produit));
    strcpy(prod->marque, marque);
    prod->prix=prix;
    prod->quantite_en_stock=quantite;
    prod->qualite=qualite;
    prod->suivant=NULL;
    return prod;

}

T_Rayon *creerRayon(char *nom)
{
    T_Rayon *ray = malloc(sizeof(T_Rayon));
    strcpy(ray->nom_rayon, nom);
    ray->nombre_produits=0;
    ray->premier=NULL;
    ray->suivant=NULL;
    return ray;
}

T_Magasin *creerMagasin(char *nom)
{
    T_Magasin *mag = malloc(sizeof(T_Magasin));
    strcpy(mag->nom, nom);
    mag->premier=NULL;
    return(mag);
}

int demanderAction (T_Magasin *magasinActuel)
{
    printf("Vous etes actuellement dans le magasin %s. \n", magasinActuel->nom);
    printf("Menu:\n\n");
    printf("\t1. Creer un nouveau magasin\n");
    printf("\t2. Ajouter un rayon au magasin\n");
    printf("\t3. Ajouter un produit dans un rayon\n");
    printf("\t4. Afficher les rayons du magasin\n");
    printf("\t5. Afficher les produits d'un rayon\n");
    printf("\t6. Supprimer un produit\n");
    printf("\t7. Supprimer un rayon\n");
    printf("\t8. Rechercher un produit par prix\n");
    printf("\t9. Fusionner 2 rayons\n");
    printf("\t10. Quitter\n");

    int choix = 0;
    while (choix < 1 || choix > 10)
    {
        printf("\nAction: ");
        scanf("%d", &choix);
    }

    return choix;
}

T_Rayon *trouverRayon(T_Rayon *actuel, char *nom)
{
    if (! actuel)
    {
        return NULL;
    }

    int comparaison = strcmp(actuel->nom_rayon, nom);

    ///Rayon trouv�
    if (comparaison == 0)
    {
        return actuel;
    }

    ///Rayon tri�s, donc on s'arr�te quand on trouve un rayon
    ///apr�s celui recherch� dans l'ordre alphab�tique
    if (comparaison > 0)
    {
        return NULL;
    }

    return trouverRayon(actuel->suivant, nom);
}

int ajouterRayon(T_Magasin *magasin, T_Rayon *aAjouter)
{
    //si il n'y a aucun rayon dans le magasin, on fait pointer magasin vers le rayon qu'on souhaite ajouter
    if (magasin->premier == NULL)
    {
        magasin->premier = aAjouter;
        aAjouter->suivant = NULL;
        return 1;
    }
    //si le premier rayon a un nom plus grand que celui que celui qu'on souhaite ajouter, alors on ajoute notre rayon en tête de liste
    else if(strcmp (magasin->premier->nom_rayon, aAjouter->nom_rayon)>0)
    {
        aAjouter->suivant = magasin->premier;
        magasin->premier= aAjouter;
        return 1;
    }
    //si le premier rayon a un nom identique à celui qu'on souhaite ajouter, alors on n'ajoute pas le nouveau rayon
    else if(strcmp (magasin->premier->nom_rayon, aAjouter->nom_rayon)==0)
    {
        return 0;
    }
    else{
        T_Rayon* actuel;
        actuel=magasin->premier;
        while(actuel->suivant!=NULL){
            int comparaison = strcmp (actuel->suivant->nom_rayon, aAjouter->nom_rayon);

            ///si egaux on peut pas ajouter le rayon
            if (comparaison == 0)
            {
                return 0;
            }

            ///Le rayon suivant doit �tre apr�s le rayon � ajouter
            if (comparaison > 0)
            {
                aAjouter->suivant = actuel->suivant;
                actuel->suivant = aAjouter;
                return 1;
            }
            actuel=actuel->suivant;
        }// on ajoute à la fin de la liste
        actuel->suivant = aAjouter;
        aAjouter->suivant = NULL;
        return 1;
    }
}

T_Produit* trouverProduit(T_Rayon *rayon, char *marque_produit){
    //fonction qui permet de rechercher si la marque de 'produit' n'est pas déjà présente dans la liste des produits du rayon
    //la fonction retourne l'adresse du produit si il est déjà dans le rayon, sinon elle retourne NULL
    T_Produit* tempProduit=rayon->premier;
    while((tempProduit!=NULL) && (strcmp(tempProduit->marque, marque_produit)!=0)){
      tempProduit=tempProduit->suivant;
    }
    return tempProduit;
}

int ajouterProduit (T_Rayon *rayon, T_Produit *aAjouter)
{ //l'ajout de produit se fait par ordre croissant de prix
  //on commence par vérifier que la marque du produit à ajouter n'est pas déjà dans le rayon
  if (trouverProduit(rayon,aAjouter->marque)==NULL){
    //si le rayon est vide, on ajoute le produit en tête de liste
    if (rayon->premier == NULL)
    {
        rayon->premier = aAjouter;
        aAjouter->suivant = NULL;
        rayon->nombre_produits+=1;
        return 1;
    }
    //si le premier produit a un prix plus élevé que celui qu'on souhaite ajouter, alors on ajoute le nouveau produit en tête de liste
    else if(rayon->premier->prix >= aAjouter->prix)
    {
        aAjouter->suivant = rayon->premier;
        rayon->premier= aAjouter;
        rayon->nombre_produits+=1;
        return 1;
    }

    else{
        T_Produit* actuel;
        actuel=rayon->premier;
        while(actuel->suivant!=NULL){

            ///Le produit suivant doit �tre apr�s le produit � ajouter
            if (actuel->suivant->prix >= aAjouter->prix)
            {
                aAjouter->suivant = actuel->suivant;
                actuel->suivant = aAjouter;
                rayon->nombre_produits+=1;
                return 1;
            }
            actuel=actuel->suivant;
        }
        // on ajoute à la fin de la liste si on n'a pas déjà ajouté le produit
        actuel->suivant = aAjouter;
        aAjouter->suivant = NULL;
        rayon->nombre_produits+=1;
        return 1;
      }
  }
  return 0;
}

char *demanderChaine (char *why)
{
    char *input = malloc(sizeof(char)*50);
    printf("%s (maximum 50 caracteres sans espaces): ", why);
    scanf("%s", input);
    return input;
}

void afficherMagasin(T_Magasin *magasin)
{
    T_Rayon* rayon=magasin->premier;
    if (rayon==NULL)
    {
      printf("Il n'y a aucun rayon.\n");
    }
    while (rayon != NULL)
    {
        printf("%s: %d\n", rayon->nom_rayon, rayon->nombre_produits);
        rayon=rayon->suivant;

    }
}

void afficherRayon(T_Rayon *rayon)
{
    T_Produit* produit=rayon->premier;
    if (produit==NULL)
    {
      printf("Il n'y a aucun produit dans le rayon.\n");
    }
    while (produit != NULL)
    {
        printf("%s: %.2f %c %d\n", produit->marque, produit->prix, produit->qualite, produit->quantite_en_stock);
        produit=produit->suivant;

    }
}


T_Produit* predProduit(T_Rayon *rayon, T_Produit *produit){
  //fonction qui permet de rechercher l'adresse du prédécesseur du produit situé dans le rayon
  //la fonction retourne l'adresse du prédécesseur du produit si elle existe
  //sinon elle retourne NULL (c'est à dire quand le produit est en tête de liste)

  //si le produit est en tête de liste on retourne NULL
  if (produit==rayon->premier)
    return NULL;
  T_Produit* tempProduit=rayon->premier;
  while(tempProduit->suivant!=produit){
    tempProduit=tempProduit->suivant;
  }
  return tempProduit;
}

int supprimerProduit(T_Rayon *rayon, char* marque_produit){
  //on commence par chercher le produit de marque 'marque_produit' dans le rayon
  T_Produit* aSupprimer=trouverProduit(rayon, marque_produit);
  //si le produit n'existe pas on retourne 0
  if (aSupprimer==NULL) {
    return 0;
  }
  T_Produit* pred_aSupprimer=predProduit(rayon,aSupprimer);
  if (pred_aSupprimer==NULL) {
    rayon->premier=aSupprimer->suivant;
  }else{
    pred_aSupprimer->suivant=aSupprimer->suivant;
  }
  free (aSupprimer);
  rayon->nombre_produits+=-1;
  return 1;
}

T_Rayon* predRayon(T_Magasin *magasin, T_Rayon *rayon){
  //fonction qui permet de rechercher l'adresse du prédécesseur du rayon situé dans le magasin
  //la fonction retourne l'adresse du prédécesseur du rayon si elle existe
  //sinon elle retourne NULL (c'est à dire quand le rayon est en tête de liste)

  //si le rayon est en tête de liste on retourne NULL
  if (rayon==magasin->premier)
    return NULL;
  T_Rayon* tempRayon=magasin->premier;
  while(tempRayon->suivant!=rayon){
    tempRayon=tempRayon->suivant;
  }
  return tempRayon;
}
void viderRayon(T_Rayon* rayon){
  T_Produit* tempProduit1=rayon->premier;
  T_Produit* tempProduit2=rayon->premier;
  while (tempProduit2!=NULL) {
    tempProduit2=tempProduit1->suivant;
    free(tempProduit1);
    tempProduit1=tempProduit2;
  }
}

int supprimerRayon(T_Magasin *magasin, char* nom_rayon){
  //on commence par chercher le rayon s'appelant nom_rayon
  T_Rayon* aSupprimer=trouverRayon(magasin->premier, nom_rayon);
  //si le rayon n'existe pas on retourne 0
  if (aSupprimer==NULL) {
    return 0;
  }
  //on cherche le prédécesseur
  T_Rayon* pred_aSupprimer=predRayon(magasin,aSupprimer);
  //si le rayon est en tête de liste, on change la tete de liste
  if (pred_aSupprimer==NULL) {
    magasin->premier=aSupprimer->suivant;
  }else{
    pred_aSupprimer->suivant=aSupprimer->suivant;
  }
  viderRayon(aSupprimer);
  free(aSupprimer);
  return 1;
}

ABR* ABR_inserer(ABR* tete, T_Produit* produit, char* rayon){
  ABR* y=NULL;
  ABR* x=tete;
  while (x!=NULL) {
    y=x;
    if (produit->prix < x->produit->prix) {
      x=x->gauche;
    }else{
      x=x->droite;
    }
  }
  //création d'un nouveau noeud
  ABR* noeud=malloc(sizeof(ABR));
  noeud->produit=produit;
  strcpy(noeud->nom_rayon,rayon);
  noeud->gauche=NULL;
  noeud->droite=NULL;

  if (y==NULL) {
    tete=noeud;
  }else if(produit->prix < y->produit->prix){
    y->gauche=noeud;
  }else{
    y->droite=noeud;
  }
  return tete;
}

void affichageABR(ABR* x){
  if (x!=NULL){
    affichageABR(x->gauche);
    printf("%s %.2f %c %d %s\n",x->produit->marque,x->produit->prix,x->produit->qualite, x->produit->quantite_en_stock,x->nom_rayon);
    affichageABR(x->droite);
    free(x);
  }
}

void rechercheProduits(T_Magasin *magasin, float prix_min, float prix_max){
  /*nous allons utiliser un arbre binaire de recherche, en effet la construction de l'arbre binaire de recherche est en O(????) et convient aux données que l'on a
  puisqu'à chaque produit que nous allons lire, nous l'ajouterons à l'arbre binaire de recherche. L'avantage énorme est qu'une fois l'arbre construit,
  l'affichage se fera dans l'ordre croissant des prix et en un temps optimal (complexité O(n) où n est le nombre de données stockées dans l'arbre)
  Si on réalise rechercheProduits de façon naive i.e sans créer d'arbre, alors nous allons lire tous les rayons (O(m*n) avec m le nombre de rayons et n le nombre de produits dans le plus grand rayon) comme pour la création de l'arbre
  mais il faudra en plus réaliser au plus m comparaisons (O(m)) avant chaque affichage de produit pour savoir lequel a le prix le plus faible.
  L'insertion d'un produit dans l'ABR a une compléxité inférieure à O(m) */

  T_Rayon* rayon=magasin->premier;
  T_Produit* produit;
  //construction de l'ABR
  ABR* teteABR=NULL;
  while (rayon!=NULL){
    produit=rayon->premier;

    while ((produit!=NULL) && (produit->prix<prix_min)) {
      produit=produit->suivant;
    }

    while ((produit!=NULL) && (produit->prix<=prix_max)) {
      teteABR=ABR_inserer(teteABR,produit,rayon->nom_rayon);

      produit=produit->suivant;
    }
    rayon=rayon->suivant;
  }
  affichageABR(teteABR);
}

void fusionnerRayons(T_Magasin *magasin){
  //on commence par demander et chercher les 2 rayons à fusionner

  printf("Quels rayons voulez-vous fusionner?\n");

  char* nom_rayon1;
  T_Rayon* rayon1=NULL;
  while (rayon1==NULL) {
    nom_rayon1=demanderChaine("rayon 1: ");
    rayon1=trouverRayon(magasin->premier,nom_rayon1);
  }

  char *nom_rayon2;
  T_Rayon* rayon2=NULL;
  while (rayon2==NULL) {
    nom_rayon2=demanderChaine("rayon 2: ");
    rayon2=trouverRayon(magasin->premier,nom_rayon2);
  }
  //on fusionne les 2 rayons dans le rayon 1
  T_Produit* prodRayon1=rayon1->premier;
  T_Produit* prodPrecedentRayon1=rayon1->premier;
  T_Produit* prodRayon2=rayon2->premier;
  T_Produit* prodSuivantRayon2=rayon2->premier;

  while ((prodRayon2!=NULL) && (prodRayon1!=NULL)) {
    if (prodRayon2->prix <= prodRayon1->prix) {

      prodSuivantRayon2=prodRayon2->suivant;
      if(prodRayon1==rayon1->premier){
        prodRayon2->suivant=prodRayon1;
        rayon1->premier=prodRayon2;
        prodPrecedentRayon1=prodRayon2;
        rayon1->nombre_produits+=1;

      }else{
        prodRayon2->suivant=prodRayon1;
        prodPrecedentRayon1->suivant=prodRayon2;
        rayon1->nombre_produits+=1;
      }
      prodRayon2=prodSuivantRayon2;
    }else{
      prodPrecedentRayon1=prodRayon1;
      prodRayon1=prodRayon1->suivant;
    }
  }

  if (((prodRayon2!=NULL) && (prodRayon1==NULL))) {
    if(prodPrecedentRayon1!=NULL){
      prodPrecedentRayon1->suivant=prodRayon2;
    }else{
      rayon1->premier=prodRayon2;
    }
    rayon1->nombre_produits+=1;
    while (prodRayon2!=NULL) {
      prodRayon2=prodRayon2->suivant;
      rayon1->nombre_produits+=1;
    }
    rayon1->nombre_produits+=-1;
  }

  //on supprime le rayon 2
  rayon2->premier=NULL;
  supprimerRayon(magasin,nom_rayon2);

  free(nom_rayon2);

  //choix du nom du rayon fusionné, on vérifie que le nom du nouveau rayon fusionné n'est pas déjà dans le magasin
  T_Rayon* tempRayonPrecedent=magasin->premier;//prédecesseur de là où il faut insérer rayon1
  T_Rayon* tempRayon=magasin->premier;//successeur de là où il faut insérer rayon1

  do {
    tempRayonPrecedent=magasin->premier;
    tempRayon=magasin->premier;
    nom_rayon1=demanderChaine("Nom du rayon fusionné: ");
    while ((tempRayon!=NULL) && (strcmp(nom_rayon1, tempRayon->nom_rayon)>0)) {
      tempRayonPrecedent=tempRayon;
      tempRayon=tempRayon->suivant;
    }
  } while((tempRayon!=NULL)&& (strcmp(tempRayon->nom_rayon, nom_rayon1)==0));

  strcpy(rayon1->nom_rayon,nom_rayon1);
  free(nom_rayon1);
  T_Rayon* predRayon1=magasin->premier;
  if (rayon1!=magasin->premier) {
    while (predRayon1->suivant!=rayon1) {//on cherche le prédécesseur de rayon 1
      predRayon1=predRayon1->suivant;
    }
  }

  //on déplace le rayon1 pour que l'ordre alphabétique soit respecté
  if ((tempRayonPrecedent!=rayon1) && (tempRayon!=rayon1)) {
    if (tempRayon==magasin->premier) { //on déplace en tête de liste le rayon1 qui n'est pas en tête de liste
      predRayon1->suivant=rayon1->suivant;
      rayon1->suivant=magasin->premier;
      magasin->premier=rayon1;
    }else{ //on déplace autre part qu'en tête de liste
      if (rayon1==magasin->premier) {//on déplace de la tête de liste vers autre part
        magasin->premier=rayon1->suivant;
        rayon1->suivant=tempRayon;
        tempRayonPrecedent->suivant=rayon1;
      }else{//on déplace d'un endroit qui n'est pas la tête de liste vers un endroit qui n'est pas la tête de liste
        predRayon1->suivant=rayon1->suivant;
        rayon1->suivant=tempRayon;
        tempRayonPrecedent->suivant=rayon1;
      }
    }
  }

}
