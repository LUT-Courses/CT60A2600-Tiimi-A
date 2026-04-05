# TiimiA:n tietorakenteet

> **Projektin kuvaus**: Tämä ohjelma on C-ohjelmoinnin kurssiprojekti, joka sisältää linkitettyyn listaan ja tasapainotettuun binäärihakupuuhun liittyviä ominaisuuksia.

---

## 📁 Projektin rakenne

````
.
├── README.md
├── bin                       # Käännetyt ohjelmat (buildin tuottamat tiedostot)
│   └── .empty
├── data                      # Syötetiedostot
│   ├── miehet_2025.txt
│   ├── naiset_2025.txt
│   ├── readme.md
│   ├── sukunimet_2025.txt
│   ├── verkko_iso.txt
│   ├── verkko_iso_lyhenteilla.txt
│   └── verkko_pieni.txt
├── doc
│   ├── /html                 # doc/html/index.html avattava selaimessa
│   ├── Doxyfile
│   ├── refman.pdf
│   └── Manuaali.pdf
├── makefile                  # Käännöskomennot: käännä, suorita, testaa, siivoa jne.
├── src                       # C lähdekooditiedostot ja otsikkotiedostot
│   ├── binaaripuu.c
│   ├── binaaripuu.h
│   ├── haut.c
│   ├── haut.h
│   ├── linkitettylista.c
│   ├── linkitettylista.h
│   ├── paaohjelma.c
│   ├── punamustapuu.c
│   ├── punamustapuu.h
│   ├── yleiset.c
│   └── yleiset.h
└── test
    ├── test_binaaripuu.c     # Testitiedostot
    ├── test_haut.c
    ├── test_linkitettylista.c
    ├── test_main.c
    └── test_punamustapuu.c
---

## 🛠 Prerequisites

- **Compiler**: `gcc` (or `clang`)
- **Make**: GNU Make
- **(Optional)**: `valgrind`, `doxygen`

Check versions:

```bash
gcc --version
make --version
````

---

## 🚀 Nopea aloitus (käännös / ajo / testaus)

```bash
# Käännä (luo oletuksena ./bin/app)
make

# Suorita
./bin/app

# Testit
make test

# Muistintarkistus
make memcheck
```

---

## 📚 Dokumentaatio

- Projektin dokumentaatio on toteutettu Doxygen-työkalulla.
- Dokumentaatio löytyy projektin rakenteesta doc/refman.pdf ja doc/html/index.html (avattava selaimessa).

---

## 📏 Koodin standardit

- **C standardi**: C99
- **Kääntäjän liput**: `-Wall -pedantic`

---

## 🧪 Testaus

- Projektissa käytetään Unity-testikehystä (https://www.throwtheswitch.org/unity).
- Yksikkötestejä ja integraatiotestejä on koodattu viikoittain, ja ne on jaettu tiedostoihin sen perusteella, mitä toimintoja ne testaavat.
- Ohjelmaa on regressiotestattu jokaisella viikolla.
- Mustalaatikkotestausta (black-box) on tehty viikoittain ajamalla ohjelmaa sekä ns. oikeilla syötteillä, että viallisilla syötteillä.
- Kaikki 41 yksikkötestiä menevät läpi ajettaessa.

Viikko 08:

- Uusia yksikkötestejä 3.
- Yhteensä 3 testiä.
- Ohjelmaa regressiotestattu.
- Uudet testit:
  - void test_VaraaMuistia(void)
  - void test_VapautaMuisti(void)
  - void test_VaraaMuistiUsealleAlkiolle(void)

Viikko 09:

- Uusia yksikkötestejä 4.
- Yhteensä 7 testiä.
- Testit liittyvät puun muistin varaukseen ja vapautukseen.
- Uudet testit:
  - void test_VaraaMuistiaPuulle(void)
  - void test_VaraaMuistiaUsealleSolmullePuussa(void) # Muokattu viikolla 4.
  - void test_VapautaPuunMuisti(void)
  - void test_VapautaPuunMuistiUseastaSolmusta(void)

Viikko 10:

- Uusia yksikkötestejä 7.
- Yhteensä 14 testiä.
- Testit liittyvät binääripuun poisto-operaatioon, sekä jonon muistin varaukseen ja vapautukseen.
- Uudet testit:
  - void test_onkoLuku(void)
  - void test_nimenArvo(void)
  - void test_poistaSolmuNimi(void)
  - void test_poistaSolmuArvo(void)
  - void test_VaraaMuistiaRBSolmulle(void)
  - void test_VapautaMuistiJono(void)
  - void test_VaraaMuistiaJonolle(void)

Viikko 11:

- Uusi yksikkötestejä 16.
- Yhteensä 30 testiä.
- Uudet testit:
  - void test_lisaaListaan_tyhja(void)
  - void test_lisaaListaan_alkuun(void)
  - void test_lisaaListaan_indeksilla(void)
  - void test_useammalleAlkiolleSamaLKM(void)
  - void test_poistaListaLkmPerusteella(void)
  - void test_poistaListaNimenPerusteella(void)
  - void test_lomitusLajitteluTyhjaLista(void)
  - void test_lomitusLajitteluYhdellaAlkiolla(void)
  - void test_lomitusLajitteluKahdellaAlkiolla(void)
  - void test_lomitusLajitteluUseallaAlkiolla(void)
  - void test_lomitusLajitteluSamaArvo(void)
  - void test_lisaysLajitteluTyhjaLista(void)
  - void test_lisaysLajitteluYhdellaAlkiolla(void)
  - void test_lisaysLajitteluKahdellaAlkiolla(void)
  - void test_lisaysLajitteluUseallaAlkiolla(void)
  - void test_lisaysLajitteluSamaArvo(void)

Viikko 12:

- Uusia testejä 11.
- Yhteensä 41 testiä.
- Testit liittyvät AVL-puun tasapainotuksen rotaatioihin, sekä punamustapuun muistin varaamiseen ja vapauttamiseen, ja rotaatioihin.
- Uudet testit:
  - void test_LLtasapainotus(void)
  - void test_RRtasapainotus(void)
  - void test_LRtasapainotus(void)
  - void test_RLtasapainotus(void)
  - void test_VaraaMuistiaUsealleRBSolmulle(void)
  - void test_VapautaRBMuisti(void)
  - void test_VapautaRBMuistiUseastaSolmusta(void)
  - void test_RBlisayksenKorjaus(void)
  - void test_RBLisayksenKorjausSolmujenPaikatVaihtuu(void)

Aja testit komennolla:

```bash
make test
```

---

## 🗂️ Versio historia

- Projektin joka viikosta on tehty oma tag, jotta yhden viikon toimivakoodi on tallessa.

| Versio | Päivämäärä | Tekijä        | Muutokset             |
| ------ | ---------- | ------------- | --------------------- |
| L08TA  | 2026-03-09 | Aino Pöyhönen | Viikon 08 koko koodi. |
| L09TA  | 2026-03-16 | Aino Pöyhönen | Viikon 09 koko koodi. |
| L10TA  | 2026-03-23 | Aino Pöyhönen | Viikon 10 koko koodi. |

Tag releases:

```bash
git tag -a v0.1.0 -m "Initial scaffold"
git push origin v0.1.0
```

---

## Tunnetut ongelmat

- Mikäli syötetään merkkijono kohtaan, jossa odotetaan kokonaisluku syötettä:
  - Ohjelma joko loppuu, ja tulostaa ensimmäisen valikon, ja kiitos ohjelman käytöstä.
  - Tai jättää osan merkkijonosta puskuriin:
    - Esim. Jos syöttää listaan lisäys kohdassa rivin kohdalle nimen, ohjelma tulkitsee ensimmäisen merkin nimeksi, ja asettaa loput kirjaimet nimeksi.

---

## 👤 Author & Course

- **Authors**: Aino Pöyhönen, Sofia Toropainen ja Noora Vepsäläinen
- **Course**: CT60A2600 Ohjelmistokehitys C-kielellä
- **Institution**: LUT University

---

## 📄 License

MIT License

Copyright (c) 2026 Aino Pöyhönen, Sofia Toropainen, Noora Vepsäläinen

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
