#ifndef ERREURS_H
#define ERREURS_H

typedef enum
{
    ERREUR_OK = 0,                   // Pas d'erreur
    ERREUR_ALLOCATION_MEMOIRE,       // Problème d'allocation mémoire
    ERREUR_CARACTERE_NON_SUPPORTE,   // Caractère invalide détecté
    ERREUR_CONVERSION_WCHAR_TO_CHAR, // Erreur lors de la conversion de wchar_t vers char
    ERREUR_OUVERTURE_FICHIER         // Impossible d'ouvrir le fichier
} CodeErreur;

#endif