#include "cesar.h"

char chiffrerCarCesar(wchar_t c, int cle, CodeErreur *erreur)
{
    wchar_t *accents = L"àâäéèêëîïôöùûüçÀÂÄÉÈÊËÎÏÔÖÙÛÜÇ";
    wchar_t *no_accents = L"aaaeeeeiioouuucAAAEEEEIIOOUUUC";

    // Vérifie si le caractère est accentué et le remplace si nécessaire
    wchar_t *pos = wcschr(accents, c);
    if (pos != NULL)
    {
        c = no_accents[pos - accents];
    }

    // Applique le chiffrement de César uniquement aux lettres de l'alphabet
    if (isupper((int)c))
    {
        return ((int)c + cle - 65) % 26 + 65;
    }
    else if (islower((int)c))
    {
        return ((int)c + cle - 97) % 26 + 97;
    }
    // Conserve les espaces inchangés
    else if (c == ' ')
    {
        return ' ';
    }
    // Indique une erreur pour les caractères non supportés
    else
    {
        *erreur = ERREUR_CARACTERE_NON_SUPPORTE;
        return '?';
    }
}

char *chiffrementCesar(wchar_t *message, int longueur, int cle, CodeErreur *erreur)
{
    // Allocation de mémoire pour le message chiffré
    char *messageChiffre = malloc((longueur + 1) * sizeof(char));
    if (!messageChiffre)
    {
        *erreur = ERREUR_ALLOCATION_MEMOIRE;
        return NULL;
    }

    for (int i = 0; i < longueur; i++)
    {
        char c = chiffrerCarCesar(message[i], cle, erreur);
        if (*erreur != ERREUR_OK)
        {
            free(messageChiffre);
            return NULL;
        }
        messageChiffre[i] = c;
    }
    messageChiffre[longueur] = '\0';

    return messageChiffre;
}

char *dechiffrementCesar(wchar_t *message, int longueur, int cle, CodeErreur *erreur)
{
    return chiffrementCesar(message, longueur, 26 - cle, erreur);
}