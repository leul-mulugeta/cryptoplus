#ifndef UTILITAIRES_H
#define UTILITAIRES_H

#include "erreurs.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <time.h>

// Vide les caractères restants dans le tampon après une lecture wide.
void viderBuffer();

// Demande un entier valide à l'utilisateur en s'assurant qu'il entre bien un nombre.
int demanderEntierValide(CodeErreur *erreur);

// Convertit une chaîne de caractères wide-char en une chaîne de caractères standard.
// Alloue dynamiquement une nouvelle chaîne et retourne son pointeur.
char *wcharToChar(const wchar_t *wstr, CodeErreur *erreur);

// Enregistre les résultats du chiffrement ou déchiffrement dans un fichier texte.
// La clé peut être soit un entier pour le chiffrement César, soit une chaîne de 
// caractères pour le chiffrement Vigenère donc on utilise void.
void enregistrerResultat(wchar_t *message, void *cle, char *messageResultat, int choixAlgo, int choixAction, CodeErreur *erreur);

#endif