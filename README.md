# TiimiA:n tietorakenteet

> **Projektin kuvaus**: Tämä ohjelma on C-ohjelmoinnin kurssi projekti, joka sisältää linkitettyyn listaan ja tasapainotettuun binäärihakupuuhun liittyviä ominaisuuksia.
> *(Students: Replace this block with your own description.)*

---

## 📁 Projektin rakenne

```
.
├── README.md
├── bin                         # Käännetyt ohjelmat (buildin tuottamat tiedostot)
│   ├── app
│   ├── test
│   └── tests
├── data
│   ├── miehet_2025.txt
│   ├── naiset_2025.txt
│   ├── readme.md
│   ├── sukunimet_2025.txt
│   ├── testi_miehet.txt
│   ├── testi_naiset.txt
│   ├── verkko_iso.txt
│   ├── verkko_iso_lyhenteilla.txt
│   └── verkko_pieni.txt
├── doc
│   ├── Doxyfile
│   ├── design.md
│   ├── readme.md
│   └── refman.pdf
├── documentation             # Doxygen dokumentaatio.
│   └── latex
│       └── refman.out
├── makefile                  # Käännöskomennot: käännä, suorita, testaa, siivoa jne.
├── src                       # C lähdekooditiedostot ja otsikkotiedostot.
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
    ├── test_binaaripuu.c           # Testitiedostot
    ├── test_haut.c
    ├── test_linkitettylista.c
    ├── test_main.c
    └── test_punamustapuu.c


Esimerkki vanhasta:
.
├── Makefile              # Build targets: build, run, test, clean, etc.
├── src/                  # C source files and headers
│   ├── main.c
│   ├── module.c
│   └── module.h
├── bin/                  # Compiled binaries (output of build)
│   └── app               # Example executable name
├── test/                 # Test sources (e.g., Unity/CMocka) + fixtures
│   ├── test_main.c
│   └── fixtures/
├── data/                 # Input datasets / sample inputs (no secrets)
│   ├── sample-input.txt
│   └── README.md         # Describe data sources and formats
└── doc/                  # Documentation (design notes, Doxygen config)
    └── design.md
```
```

> **Notes**
> - `bin/` is generated—usually excluded from version control.
> - Place configuration and design decisions in `doc/`.

---

## 🛠 Prerequisites

- **Compiler**: `gcc` (or `clang`)
- **Make**: GNU Make
- **(Optional)**: `valgrind`, `doxygen`

Check versions:

```bash
gcc --version
make --version
```

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
## 🧭 How to Use This Template (Students)

### 1) Use this template

### 2) Personalize the Project

- Rename the project in this README. ok
- Fill in the description, inputs/outputs, and known issues.
- Replace sample files in `src/` and `test/` with your implementation. Muutetaan, jos doxygenin sijainti vaihtuu.
- **Modify** this README as your project evolves.

### 3) Branching & Commits (Recommended Workflow)

```bash
# Create a feature branch
git checkout -b feature/<short-name>
# Work & commit small, focused changes
git add .
git commit -m "feat: short description"
# Push and open a Pull Request (PR)
git push -u origin feature/<short-name>
```

## 📚 Documentation

- High-level design: `doc/design.md`
- API docs: generate with Doxygen

```bash
# Generate docs
doxygen doc/Doxyfile
```

---

## 📏 Coding Standards

- **C standard**: C99 
- **Compiler flags**: `-Wall -pedantic`

---

## 🧪 Testaus

- Projektissa käytetään Unity testikehystä.
- Yksikkötestejä ja integraatiotestejä on koodattu viikoittain, ja ne on jaettu tiedostoihin sen perusteella, mitä toimintoja ne testaavat.
- Ohjelmaa on regressiotestattu jokaisella viikolla.
- Mustalaatikkotestausta (bloack-box) on tehty viikoittain ajamalla ohjelmaa sekä ns. oikeilla syötteillä, että viallisilla syötteillä.
- Kaikki 34 yksikkötestiä menevät läpi ajettaessa.

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
    - void test_VaraaMuistiaUsealleSolmullePuussa(void)  # Muokattu viikolla 4. 
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
    - void test_lomitusLajitteluYhdellaAlkiolla()
    - void test_lomitusLajitteluKahdellaAlkiolla(void)
    - void test_lomitusLajitteluUseallaAlkiolla(void)
    - void test_lomitusLajitteluSamaArvo(void)
    - void test_lisaysLajitteluTyhjaLista(void)
    - void test_lisaysLajitteluYhdellaAlkiolla(void)
    - void test_lisaysLajitteluKahdellaAlkiolla(void)
    - void test_lisaysLajitteluUseallaAlkiolla(void)
    - void test_lisaysLajitteluSamaArvo(void)

Viikko 12:
- Uusia testejä 4.
- Yhteensä 34 testiä.
- Testit liittyvät AVL-puun tasapainotuksen rotaatioihin.
- Uudet testit:
    - void test_LLtasapainotus();
    - void test_RRtasapainotus();
    - void test_LRtasapainotus();
    - void test_RLtasapainotus();

Aja testit komennolla: 
```bash
make test
```

---

## 🗂️ Version History

> *(Update this table as you progress. Use semantic versioning if possible.)*

| Version | Date       | Author      | Changes                                               |
|--------:|------------|-------------|-------------------------------------------------------|
| 0.1.0   | 2026-03-01 | Your Name   | Initial scaffold: folders, Makefile, sample main      |

Tag releases:
```bash
git tag -a v0.1.0 -m "Initial scaffold"
git push origin v0.1.0
```

---

## 👤 Author & Course

- **Authors**: Aino Pöyhönen, Sofia Toropainen ja Noora Vepsäläinen 
- **Course**: CT60A2600 Ohjelmistokehitys C-kielellä
- **Institution**: LUT University

---

## 📄 License

> *(Choose a license or keep the repository private if unsure.)*

