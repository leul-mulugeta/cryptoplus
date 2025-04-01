#ifndef ERREURS_H
#define ERREURS_H

typedef enum
{
    ERREUR_OK = 0,                 // Pas d'erreur
    ERREUR_ALLOCATION_MEMOIRE,     // Problème d'allocation mémoire
    ERREUR_CARACTERE_NON_SUPPORTE, // Caractère invalide détecté
    ERREUR_CONVERSION_WCHAR_TO_CHAR
} CodeErreur;

#endif