#ifndef TP3_H_INCLUDED
#define TP3_H_INCLUDED

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef enum qualite qualite;
enum qualite
{
    A, B, C
};

typedef struct Produit
{
    char marque[50];
    float prix;
    char qualite;
    int quantite_en_stock;
    struct Produit *suivant;

}T_Produit;

typedef struct Rayon
{
   char nom_rayon[50];
   int nombre_produits;
   struct Produit *premier;
   struct Rayon *suivant;

}T_Rayon;

typedef struct Magasin
{
    char nom[50];
    struct Rayon *premier;

}T_Magasin;

typedef struct ABR{
  T_Produit* produit;
  char nom_rayon[50];
  struct ABR *gauche, *droite;
}ABR;
T_Magasin *creerMagasin(char *nom);
T_Rayon *creerRayon(char *nom);
T_Produit *creerProduit(char *marque, float prix, char qualite, int quantite);
T_Rayon *trouverRayon(T_Rayon *actuel, char *nom);
int ajouterProduit (T_Rayon *rayon, T_Produit *aAjouter);
int ajouterProduitListe(T_Produit *actuel, T_Produit *aAjouter);
int ajouterRayon(T_Magasin *magasin, T_Rayon *aAjouter);
int ajouterRayonListe(T_Rayon *actuel, T_Rayon *aAjouter);
int demanderAction (T_Magasin *magasinActuel);
char *demanderChaine (char *why);
void afficherMagasin(T_Magasin *magasin);
void afficherRayon(T_Rayon *rayon);
T_Produit* predProduit(T_Rayon *rayon, T_Produit *produit);
int supprimerProduit(T_Rayon *rayon, char* marque_produit);
int supprimerRayon(T_Magasin *magasin, char* nom_rayon);
void rechercheProduits(T_Magasin *magasin, float prix_min, float prix_max);
void fusionnerRayons(T_Magasin *magasin);

#endif // TP3_H_INCLUDED
