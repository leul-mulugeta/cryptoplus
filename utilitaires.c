#include "utilitaires.h"

void viderBuffer()
{
    int c;
    while ((c = getwchar()) != L'\n' && c != WEOF);
}

int demanderEntierValide(CodeErreur *erreur)
{
    wchar_t valeur[10];

    while (1)
    {
        // Lit l'entrée utilisateur
        fgetws(valeur, sizeof(valeur) / sizeof(valeur[0]), stdin);

        int l = wcslen(valeur);
        // Vérifier si l'entrée était trop longue
        if (l > 0 && valeur[l - 1] != L'\n')
        {
            viderBuffer(); // Vide le reste de la ligne
        }

        // Supprime le retour à la ligne si présent
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
            printf("\n\033[0;31mErreur lors de la conversion du chaine.\n");
            printf("\033[0;32mVotre choix : \033[0m");
            continue;
        }

        // Vérifie si l'entrée est bien un nombre et assure qu'il est composé d'1 ou 2 chiffres maximum
        if ((isdigit(v[0]) && v[1] == '\0') || (isdigit(v[0]) && isdigit(v[1]) && v[2] == '\0'))
        {
            int resultat = v[0] - '0';
            free(v);
            return resultat;
        }
        else
        {
            printf("\n\033[0;31mVeuillez entrer un seul chiffre valide.\n");
            printf("\033[0;32mVotre choix : \033[0m");
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

void enregistrerResultat(wchar_t *message, void *cle, char *messageResultat, int choixAlgo, int choixAction, CodeErreur *erreur)
{

    FILE *f = fopen("resultat.txt", "a");
    if (f != NULL)
    {
        // Récupérer la date et l'heure actuelles
        time_t now = time(NULL);
        struct tm *local = localtime(&now);
        wchar_t dateStr[100];
        wcsftime(dateStr, 100, L"%Y-%m-%d %H:%M:%S", local);

        // Écrire les informations dans le fichier
        fwprintf(f, L"Date : %ls\n", dateStr);
        fwprintf(f, L"Message original : %ls\n", message);

        if (choixAlgo == 1) // Chiffrement César
        {
            // Affichage de la clé pour César (int)
            int *cleCesar = (int *)cle; // Convertir void* en int*
            fwprintf(f, L"Clé utilisée : %d\n", *cleCesar);
        }
        else // Chiffrement Vigenère
        {
            // Affichage de la clé pour Vigenère (wchar_t*)
            wchar_t *cleVigenere = (wchar_t *)cle; // Convertir void* en wchar_t*
            fwprintf(f, L"Clé utilisée : %ls\n", cleVigenere);
        }

        fwprintf(f, L"Méthode : %s\n", (choixAlgo == 1) ? "Chiffrement César" : "Chiffrement Vigenère");
        fwprintf(f, L"Message chiffré : %s\n", messageResultat);
        fwprintf(f, L"\n");
        fclose(f);
    }
    else
    {
        *erreur = ERREUR_OUVERTURE_FICHIER;
    }
}