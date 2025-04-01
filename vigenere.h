#ifndef VIGENERE_H
#define VIGENERE_H

#include "utilitaires.h"
#include <ctype.h>
#include <stdlib.h>
#include <wchar.h>

// Génère une clé de la même longueur que le message en répétant la clé fournie.
char *genererCle(int longueurM, char *cle, int longueurC, CodeErreur *erreur);

// Chiffre un caractère en utilisant le chiffrement de Vigenère.
char chiffrerCarVigenere(wchar_t c, char cle, CodeErreur *erreur);

// Déchiffre un caractère en utilisant le chiffrement de Vigenère.
char dechiffrerCarVigenere(wchar_t c, char messageCle, CodeErreur *erreur);

// Chiffre un message entier en utilisant le chiffrement de Vigenère.
char *chiffrementVigenere(wchar_t *message, int longueurM, wchar_t *cle, int longueurC, CodeErreur *erreur);

// Déchiffre un message chiffré avec le chiffrement de Vigenère.
char *dechiffrementVigenere(wchar_t *message, int longueurM, wchar_t *cle, int longueurC, CodeErreur *erreur);

#endif