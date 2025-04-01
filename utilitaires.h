#ifndef UTILITAIRES_H
#define UTILITAIRES_H

#include "erreurs.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

// Demande un entier valide à l'utilisateur en s'assurant qu'il entre bien un nombre.
int demanderEntierValide(CodeErreur *erreur);

// Convertit une chaîne de caractères wide-char en une chaîne de caractères standard.
// Alloue dynamiquement une nouvelle chaîne et retourne son pointeur.
char *wcharToChar(const wchar_t *wstr, CodeErreur *erreur);

#endif