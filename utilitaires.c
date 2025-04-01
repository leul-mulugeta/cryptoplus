#include "utilitaires.h"

int demanderEntierValide(CodeErreur *erreur)
{
    wchar_t valeur[10];

    while (1)
    {
        // Lit l'entrée utilisateur
        fgetws(valeur, sizeof(valeur) / sizeof(valeur[0]), stdin);

        int l = wcslen(valeur);
        // Supprime le retour à la ligne
        if (l > 0 && valeur[l - 1] == L'\n')
        {
            valeur[l - 1] = L'\0';
            l--;
        }

        // Convertit la chaîne wide-char en chaîne standard
        char *v = wcharToChar(valeur, erreur);
        // Vérifie si la conversion a échoué
        if (!v)
        {
            printf("Erreur lors de la conversion du texte.\n");
            *erreur = ERREUR_OK;
            printf("\nVotre choix :");
            continue;
        }

        // Vérifie si l'entrée est bien un nombre et assure que c'est un chiffre unique
        if (isdigit(v[0]) && v[1] == '\0')
        {
            int resultat = v[0] - '0';
            free(v);
            return resultat;
        }
        else
        {
            printf("\nVeuillez entrer un seul chiffre valide.\n");
            printf("\nVotre choix :");
            free(v);
        }
    }
}

char *wcharToChar(const wchar_t *wstr, CodeErreur *erreur)
{
    // Calcule la longueur nécessaire
    size_t len = wcstombs(NULL, wstr, 0);
    // Échec de conversion, souvent dû à un caractère non convertible
    if (len == (size_t)-1)
    {
        *erreur = ERREUR_CONVERSION_WCHAR_TO_CHAR;
        return NULL;
    }
    len++;
    
    // Allocation de memoire puis effectue la conversion
    char *str = malloc(len);
    if (str)
    {
        wcstombs(str, wstr, len);
    }
    return str;
}