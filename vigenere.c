#include "vigenere.h"

char *genererCle(int longueurM, char *cle, int longueurC, CodeErreur *erreur)
{
    // Si la clé est déjà assez longue, on la retourne telle quelle.
    if (longueurC >= longueurM)
    {
        return cle;
    }

    char *cleGenerer = malloc((longueurM + 1) * sizeof(char));
    if (!cleGenerer)
    {
        
        *erreur = ERREUR_ALLOCATION_MEMOIRE;
        return NULL;
    }

    // Remplit la clé générée en répétant la clé originale
    for (int i = 0; i < longueurM; i++)
    {
        cleGenerer[i] = cle[i % longueurC];
    }
    cleGenerer[longueurM] = '\0';

    return cleGenerer;
}

char chiffrerCarVigenere(wchar_t c, char messageCle, CodeErreur *erreur)
{
    wchar_t *accents = L"àâäéèêëîïôöùûüçœÀÂÄÉÈÊËÎÏÔÖÙÛÜÇŒ";
    wchar_t *no_accents = L"aaaeeeeiioouuucoeAAAEEEEIIOOUUUCOE";

    // Remplace les caractères accentués par leurs équivalents non accentués
    wchar_t *pos = wcschr(accents, c);
    if (pos != NULL)
    {
        c = (char)no_accents[pos - accents];
    }

    // Applique le chiffrement de Vigenère uniquement aux lettres de l'alphabet
    if (isupper((int)c))
    {
        return ((messageCle % 65) + (c % 65)) % 26 + 65;
    }
    else if (islower((int)c))
    {
        return ((messageCle % 97) + (c % 97)) % 26 + 97;
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

char dechiffrerCarVigenere(wchar_t c, char messageCle, CodeErreur *erreur)
{
    if (isupper((int)c))
    {
        return ((c % 65) - (messageCle % 65) + 26) % 26 + 65;
    }
    else if (islower((int)c))
    {
        return ((c % 97) - (messageCle % 97) + 26) % 26 + 97;
    }
    else if (c == ' ')
    {
        return ' ';
    }
    else
    {
        *erreur = ERREUR_CARACTERE_NON_SUPPORTE;
        return '!';
    }
}

char *chiffrementVigenere(wchar_t *message, int longueurM, wchar_t *cle, int longueurC, CodeErreur *erreur)
{
    // Allocation de mémoire pour le message chiffré
    char *messageChiffre = malloc((longueurM + 1) * sizeof(char));
    if (!messageChiffre)
    {
        *erreur = ERREUR_ALLOCATION_MEMOIRE;
        return NULL;
    }

    // Convertit la clé wide-char en char pour faciliter
    char *cleConvertit = wcharToChar(cle, erreur);
    if (!cleConvertit)
    {
        return NULL;
    }

    // Génère une clé répétée de la longueur du message
    char *cleGenerer = genererCle(longueurM, cleConvertit, longueurC, erreur);
    if (!cleGenerer)
    {
        free(messageChiffre);
        free(cleConvertit);
        return NULL;
    }
    
    for (int i = 0; i < longueurM; i++)
    {
        char c = chiffrerCarVigenere(message[i], cleGenerer[i], erreur);
        if (*erreur != ERREUR_OK)
        {
            free(messageChiffre);
            free(cleGenerer);
            free(cleConvertit);
            return NULL;
        }
        messageChiffre[i] = c;
    }
    messageChiffre[longueurM] = '\0';

    // Libère la mémoire allouée dynamiquement si une nouvelle clé a été générée
    if (cleGenerer != cleConvertit)
    {
        free(cleGenerer);
    }
    free(cleConvertit);

    return messageChiffre;
}

char *dechiffrementVigenere(wchar_t *message, int longueurM, wchar_t *cle, int longueurC, CodeErreur *erreur)
{
    // Allocation de mémoire pour le message déchiffré
    char *messageChiffre = malloc((longueurM + 1) * sizeof(char));
    if (!messageChiffre)
    {
        *erreur = ERREUR_ALLOCATION_MEMOIRE;
        return NULL;
    }

    // Convertit la clé wide-char en char
    char *cleConvertit = wcharToChar(cle, erreur);
    if (!cleConvertit)
    {
        free(messageChiffre);
        return NULL;
    }

    // Génère une clé répétée de la longueur du message
    char *cleGenerer = genererCle(longueurM, cleConvertit, longueurC, erreur);
    if (!cleGenerer)
    {
        free(messageChiffre);
        free(cleConvertit);
        return NULL;
    }

    for (int i = 0; i < longueurM; i++)
    {
        char c = dechiffrerCarVigenere(message[i], cleGenerer[i], erreur);
        if (*erreur != ERREUR_OK)
        {
            free(messageChiffre);
            free(cleGenerer);
            free(cleConvertit);
            return NULL;
        }
        messageChiffre[i] = c;
    }
    messageChiffre[longueurM] = '\0';

    // Libère la mémoire allouée dynamiquement si une nouvelle clé a été générée
    if (cleGenerer != cleConvertit)
    {
        free(cleGenerer);
    }
    free(cleConvertit);

    return messageChiffre;
}