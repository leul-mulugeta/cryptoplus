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
        printf("\n\033[1;36m**** PROGRAMME DE CHIFFREMENT ****\033[0m\n");
        printf("1. Chiffrement César\n");
        printf("2. Chiffrement Vigenère\n");
        printf("3. Quitter\n");
        printf("\033[0;32mVotre choix : \033[0m");

        CodeErreur erreur = ERREUR_OK;
        int choixAlgo = demanderEntierValide(&erreur);

        if (choixAlgo == 3)
        {
            printf("\nAu revoir!\n");
            break;
        }

        if (choixAlgo != 1 && choixAlgo != 2)
        {
            printf("\n\033[0;31mEntrée invalide. Veuillez choisir entre 1 et 3.\033[0m\n");
            continue;
        }

        while (1)
        {
            // Affichage du menu de chiffrement/déchiffrement
            printf("\n1. Chiffrer un message\n");
            printf("2. Déchiffrer un message\n");
            printf("3. Retour au menu principal\n");
            printf("\033[0;32mVotre choix : \033[0m");

            int choixAction = demanderEntierValide(&erreur);

            if (choixAction == 3)
                break;

            if (choixAction != 1 && choixAction != 2)
            {
                printf("\n\033[0;31mEntrée invalide. Veuillez choisir entre 1 et 3.\033[0m\n");
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
                char *messageResultat = (choixAction == 1) ? chiffrementCesar(message, longueurM, cle, &erreur) : dechiffrementCesar(message, longueurM, cle, &erreur);

                if (!messageResultat)
                {
                    if (erreur == ERREUR_ALLOCATION_MEMOIRE)
                        printf("\n\033[0;31mErreur : échec de l'allocation de mémoire.\033[0m\n");
                    else if (erreur == ERREUR_CARACTERE_NON_SUPPORTE)
                        printf("\n\033[0;31mErreur : caractère non supporté détecté.\033[0m\n");
                }
                else
                {
                    enregistrerResultat(message, (void *)&cle, messageResultat, choixAlgo, choixAction, &erreur);
                    if (erreur == ERREUR_OUVERTURE_FICHIER) 
                    {
                        printf("\n\033[0;31mErreur : ouverture du fichier.\033[0m\n");
                        free(messageResultat);
                    } 
                    else 
                    {
                        printf("\033[1;34m\nRésultat :\033[0m %s\n", messageResultat);
                        free(messageResultat);
                    }
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
                    printf("\n\033[0;31mErreur : La clé doit contenir uniquement des lettres.\033[0m\n");
                    continue;
                }

                // Appel au chiffrement ou déchiffrement de Vigenère
                char *messageResultat = (choixAction == 1) ? chiffrementVigenere(message, longueurM, cle, longueurC, &erreur) : dechiffrementVigenere(message, longueurM, cle, longueurC, &erreur);

                if (!messageResultat)
                {
                    if (erreur == ERREUR_ALLOCATION_MEMOIRE)
                        printf("\n\033[0;31mErreur : échec de l'allocation de mémoire.\033[0m\n");
                    else if (erreur == ERREUR_CARACTERE_NON_SUPPORTE)
                        printf("\n\033[0;31mErreur : caractère non supporté détecté.\033[0m\n");
                    else if (erreur == ERREUR_CONVERSION_WCHAR_TO_CHAR)
                        printf("\n\033[0;31mErreur : échec conversion de wchar_t vers char.\033[0m\n");
                }
                else
                {
                    enregistrerResultat(message, (void *)cle, messageResultat, choixAlgo, choixAction, &erreur);
                    if (erreur == ERREUR_OUVERTURE_FICHIER) 
                    {
                        printf("\n\033[0;31mErreur : ouverture du fichier.\033[0m\n");
                        free(messageResultat);
                    } 
                    else 
                    {
                        printf("\033[1;34m\nRésultat :\033[0m %s\n", messageResultat);
                        free(messageResultat);
                    }
                }
            }
        }
    }
    return 0;
}