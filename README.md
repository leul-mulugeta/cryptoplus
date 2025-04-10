# 📌 CryptoPlus

## 🛠 Présentation
CryptoPlus est une application qui permet le **chiffrement et le déchiffrement** de messages à l'aide des algorithmes de **César et Vigenère**.

## Fonctionnalités
- Interface en ligne de commande avec menu interactif
- Chiffrement et déchiffrement avec l'algorithme de **César**
- Chiffrement et déchiffrement avec l'algorithme de **Vigenère**
- Gestion des **caractères accentués**
- Gestion des erreurs avec messages explicatifs

## Algorithmes implémentés
### César
Le chiffrement de **César** est une méthode qui décale chaque lettre d'un message d'un nombre fixe de positions dans l'alphabet.

_Exemple avec une clé de 3:_
- **Message d'origine** : `HELLO`
- **Message chiffré** : `KHOOR`

### Vigenère
Le chiffrement de **Vigenère** est une méthode polyalphabétique qui utilise une **clé (mot)** pour déterminer le décalage de chaque lettre.

_Exemple avec la clé "CLE" :_
- **Message d'origine** : `HELLO`
- **Message chiffré** : `KLOGT`

## Particularités et limitations
- **Respect de la capitalisation pour Vigenère** : Le message et la clé doivent être soit **tout en majuscules, soit tout en minuscules** pour garantir un chiffrement correct.
  - ✅ Clé : `"SECRET"` et Message : `"HELLO"` (Le chiffrement est correct)
  - ❌ Clé : `"Secret"` et Message : `"HELLO"` (Le chiffrement sera incorrect)

- **Gestion des caractères accentués** :
  - La clé pour **Vigenère** **ne peut pas** contenir de caractères accentués, mais le message, oui.
  - Les **caractères accentués dans le message sont convertis** en leur version non accentuée avant chiffrement.
  - _Exemple_ : `"École"` devient `"Ecole"` avant chiffrement.

- **Seuls les caractères alphabétiques sont pris en charge** :
  - Les **chiffres, symboles et espaces ne sont pas supportés**.
  - Un caractère non alphabétique déclenche une **erreur (ERREUR_CARACTERE_NON_SUPPORTE)**.
  - _Exemple_ :
    - ✅ `"Bonjour"` (OK)
    - ❌ `"Hello123!"` (Erreur)

## Compilation et exécution
Avant de compiler, récupérez le projet via **Git** :
```sh
 git clone https://github.com/leul-mulugeta/cryptoplus.git
 cd cryptoplus
```

Ensuite, utilisez `make` pour compiler :
```sh
make
```

Pour nettoyer les fichiers objet et l'exécutable :
```sh
make clean
```

Pour recompiler entièrement le projet :
```sh
make rebuild
```

Pour exécuter l'application :
```sh
./main
```

## Sources
- [Caesar Cipher in Cryptography](https://www.geeksforgeeks.org/caesar-cipher-in-cryptography/)
- [Le chiffre de Vigenère](https://haltode.fr/algo/chiffrement/chiffre_vigenere.html)
- [Les caractères larges en C](https://zestedesavoir.com/tutoriels/755/le-langage-c-1/notions-avancees/les-caracteres-larges/)

## À propos
Projet développé par **Leul Nebeyu MULUGETA** dans le cadre d'études en développement logiciel.

## Licence

Ce projet est sous licence MIT - voir le fichier [LICENSE](LICENSE) pour plus de détails.