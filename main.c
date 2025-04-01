#include "cesar.h"
#include "vigenere.h"
#include "erreurs.h"
#include "utilitaires.h"
#include <locale.h>

int main()
{
    // Permet la gestion des caractères spéciaux (accents, Unicode)
    setlocale(LC_ALL, "");

    while (1)
    {
        // Affichage du menu principal
        printf("\n**** PROGRAMME DE CHIFFREMENT ****\n");
        printf("1. Chiffrement César\n");
        printf("2. Chiffrement Vigenère\n");
        printf("3. Quitter\n");
        printf("Votre choix : ");

        CodeErreur erreur = ERREUR_OK;
        int choixAlgo = demanderEntierValide(&erreur);

        if (choixAlgo == 3)
        {
            printf("\nAu revoir!\n");
            break;
        }

        if (choixAlgo != 1 && choixAlgo != 2)
        {
            printf("\nEntrée invalide. Veuillez choisir entre 1 et 3.\n");
            continue;
        }

        while (1)
        {
            // Affichage du menu de chiffrement/déchiffrement
            printf("\n1. Chiffrer un message\n");
            printf("2. Déchiffrer un message\n");
            printf("3. Retour au menu principal\n");
            printf("Votre choix : ");

            int choixAction = demanderEntierValide(&erreur);

            if (choixAction == 3)
                break;

            if (choixAction != 1 && choixAction != 2)
            {
                printf("\nEntrée invalide. Veuillez choisir entre 1 et 3.\n");
                continue;
            }

            // Saisie du message à chiffrer ou déchiffrer
            wchar_t message[1024];
            printf("\nEntrez votre message : ");
            fgetws(message, sizeof(message) / sizeof(wchar_t), stdin);

            int longueurM = wcslen(message);
            // Suppression du retour à la ligne
            if (longueurM > 0 && message[longueurM - 1] == L'\n')
            {
                message[longueurM - 1] = L'\0';
                longueurM--;
            }

            if (choixAlgo == 1) // Chiffrement César
            {
                int cle;
                printf("Entrez la clé (décalage) : ");
                cle = demanderEntierValide(&erreur);

                // Appel au chiffrement ou déchiffrement de César
                char *messageResult = (choixAction == 1) ? chiffrementCesar(message, longueurM, cle, &erreur) : dechiffrementCesar(message, longueurM, cle, &erreur);

                if (!messageResult)
                {
                    if (erreur == ERREUR_ALLOCATION_MEMOIRE)
                        printf("Erreur : échec de l'allocation de mémoire.\n");
                    else if (erreur == ERREUR_CARACTERE_NON_SUPPORTE)
                        printf("Erreur : caractère non supporté détecté.\n");
                }
                else
                {
                    printf("\nRésultat : %s\n", messageResult);
                    free(messageResult);
                }
            }
            else // Chiffrement Vigenère
            {
                wchar_t cle[1024];
                printf("Entrez votre clé (mot) : ");
                fgetws(cle, sizeof(cle) / sizeof(wchar_t), stdin);

                int longueurC = wcslen(cle);
                // Suppression du retour à la ligne
                if (longueurC > 0 && cle[longueurC - 1] == L'\n')
                {
                    cle[longueurC - 1] = L'\0';
                    longueurC--;
                }

                // Vérification que la clé contient uniquement des lettres
                int estValide = 1;
                for (int i = 0; i < longueurC; i++)
                {
                    if (!iswalpha(cle[i]))
                    {
                        estValide = 0;
                        break;
                    }
                }

                if (!estValide)
                {
                    printf("\nErreur : La clé doit contenir uniquement des lettres.\n");
                    continue;
                }

                // Appel au chiffrement ou déchiffrement de Vigenère
                char *messageResult = (choixAction == 1) ? chiffrementVigenere(message, longueurM, cle, longueurC, &erreur) : dechiffrementVigenere(message, longueurM, cle, longueurC, &erreur);

                if (!messageResult)
                {
                    if (erreur == ERREUR_ALLOCATION_MEMOIRE)
                        printf("Erreur : échec de l'allocation de mémoire.\n");
                    else if (erreur == ERREUR_CARACTERE_NON_SUPPORTE)
                        printf("Erreur : caractère non supporté détecté.\n");
                    else if (erreur == ERREUR_CONVERSION_WCHAR_TO_CHAR)
                        printf("Erreur : échec conversion de wchar_t vers char.\n");
                }
                else
                {
                    printf("\nRésultat : %s\n", messageResult);
                    free(messageResult);
                }
            }
        }
    }
    return 0;
}