#ifndef CESAR_H
#define CESAR_H

#include "erreurs.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>

// Fonction pour chiffrer un caractère avec le chiffrement de César
// Convertit les caractères accentués en leurs équivalents non accentués avant chiffrement.
char chiffrerCarCesar(wchar_t c, int cle, CodeErreur *erreur);

// Chiffre un message entier en appliquant le chiffrement de César caractère par caractère.
// Retourne une chaîne nouvellement allouée contenant le message chiffré.
char *chiffrementCesar(wchar_t *message, int longueur, int cle, CodeErreur *erreur);

// Déchiffre un message chiffré avec le chiffrement de César.
// Utilise la même fonction que le chiffrement en inversant la clé.
char *dechiffrementCesar(wchar_t *message, int longueur, int cle, CodeErreur *erreur);

#endif