# CarRental

Et bilutleieprogram skrevet i C++ med SQLite-database, utviklet som eksamen i IKT103 ved Universitetet i Agder.

## Om prosjektet

CarRental er et konsolbasert system for administrasjon av bilutleie. Programmet håndterer kunder, biler og leieforhold ved hjelp av en lokal SQLite-database.

## 🛠️ Teknologier

- **Språk:** C / C++
- **Database:** SQLite3
- **Byggesystem:** CMake
- **Pakkehåndtering:** vcpkg
- **Bibliotek:** SQLiteCpp

## Prosjektstruktur
```
CarRental/
├── Classes/          # Klassefiler (Car, Customer, Rental, osv.)
├── UML/              # UML-diagrammer (bilder)
├── sqlite3/          # SQLite3-kildekode
├── sqlitecpp/        # SQLiteCpp-wrapper
├── main.cpp          # Inngangspunkt
├── CMakeLists.txt    # Byggekonfigurasjon
├── CarRental.sqlite  # SQLite-database
├── UMLClass.puml     # Klassediagram (PlantUML)
├── UMLDB.puml        # Databasediagram (PlantUML)
└── vcpkg.json        # Avhengigheter
```

## Kom i gang

### Forutsetninger

- CMake ≥ 3.15
- En C++17-kompatibel kompilator (GCC, Clang, MSVC)
- [vcpkg](https://github.com/microsoft/vcpkg) (valgfritt, for avhengighetsstyring)

### Bygg prosjektet
```bash
git clone https://github.com/NikolaiPOlsen/CarRental.git
cd CarRental
mkdir build && cd build
cmake ..
cmake --build .
```

### Kjør programmet
```bash
./CarRental
```

## Lisens

Dette prosjektet er laget som eksamensoppgave i IKT103 ved UiA og er ikke lisensiert for kommersiell bruk.
