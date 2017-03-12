#include "tp3.h"

int main()
{
    char nomMag[50];
    printf("Il faut creer un premier magasin, entrez son nom:\n");
    scanf(" %s", nomMag);
    T_Magasin *magInitial = creerMagasin(nomMag);

    int choix=0;

    while (choix != 10)
    {
        choix = demanderAction (magInitial);

        printf("\n");
        /// Cr�er un nouveau magasin
        if (choix == 1)
        {
            //supprimerMagasin(magInitial);
            magInitial = creerMagasin(demanderChaine("Nom du nouveau magasin"));

            printf("Magasin Cree");
        }
        else if (choix == 2)
        {
            int result;
            result = ajouterRayon(magInitial, creerRayon(demanderChaine("Nom du rayon")));
            if (result == 1)
            {
                printf("Rayon ajoute\n");
            }
            else{
              printf("Le rayon existe deja\n");
            }
        }
        else if (choix == 3)
        {
          if (magInitial->premier!=NULL){
            T_Rayon *rayon;
            rayon = trouverRayon(magInitial->premier, demanderChaine("Nom du rayon dans lequel ajouter le produit"));
            if(! rayon)
            {
                printf("Rayon introuvable\n");
            }
            else
            {
                char *marque = demanderChaine("Marque");
                float prix;
                printf("\nEntrez un prix:");
                scanf("%f", &prix);
                char qualite;
                printf("\nEntrez une qualite (A, B, C):");
                scanf(" %c", &qualite);
                int quantite;
                printf("\nEntrez une quantite:");
                scanf(" %d", &quantite);

                int result;
                result = ajouterProduit(rayon, creerProduit(marque, prix, qualite, quantite));
                if (result == 1)
                {
                    printf("\nProduit ajoute\n");
                }else{
                  printf("Le produit a ajouter a la meme marque qu'un produit deja present dans le rayon.\n");
                }
            }
          }else{
            printf("Il n'y aucun rayon dans le magasin %s\n",magInitial->nom);
          }
        }
        else if (choix == 4)
        {
            afficherMagasin(magInitial);
        }
        else if (choix == 5)
        {
            if (magInitial->premier!=NULL){
                T_Rayon *rayon = trouverRayon(magInitial->premier, demanderChaine("Nom du rayon a afficher"));

                if (! rayon)
                {
                    printf("Rayon introuvable\n");
                }
                else
                {
                    afficherRayon(rayon);
                }
            }else{
              printf("Il n'y aucun rayon dans le magasin %s\n",magInitial->nom);
            }
        }
        else if (choix == 6)
        {
            if (magInitial->premier!=NULL){
                T_Rayon *rayon = trouverRayon(magInitial->premier, demanderChaine("Nom du rayon contenant le produit"));

                if (! rayon)
                {
                    printf("Rayon introuvable\n");
                }
                else
                {
                    int suppressionProduit=supprimerProduit(rayon, demanderChaine("Marque du produit a supprimer:"));
                    if (suppressionProduit==1) {
                      printf("Le produit a ete supprime.\n");
                    }else{
                      printf("Le produit n'existe pas.\n");
                    }
                }
            }else{
              printf("Il n'y aucun rayon dans le magasin %s\n",magInitial->nom);
            }
        }
        else if (choix == 7)
        {
            if (magInitial->premier!=NULL){
              int suppressionRayon=supprimerRayon(magInitial, demanderChaine("Nom du rayon a supprimer:"));
              if (suppressionRayon==1) {
                printf("Le rayon a ete supprime.\n");
              }else{
                printf("Le rayon n'existe pas.\n");
              }
            }else{
              printf("Il n'y aucun rayon dans le magasin %s.\n",magInitial->nom);
            }
        }
        else if (choix == 8)
        {
            if (magInitial->premier!=NULL){
              float prix_min,prix_max;
              printf("Prix min:");
              scanf("%f", &prix_min);
              printf("\nPrix max:");
              scanf("%f", &prix_max);
              printf("\n");
              rechercheProduits(magInitial, prix_min, prix_max);
            }else{
              printf("Il n'y aucun rayon dans le magasin %s.\n",magInitial->nom);
            }
        }
        else if (choix == 9)
        {
            if ((magInitial->premier!=NULL) && (magInitial->premier->suivant!=NULL)){
              fusionnerRayons(magInitial);
            }else{
              printf("Il y a moins de 2 rayons dans le magasin %s.\n",magInitial->nom);
            }
        }
    }

    return 0;
}
