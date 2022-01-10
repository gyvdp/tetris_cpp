# [ATLIR5-ATLC] Projet: Tetris

## Authors

- Andrew SASSOYE
- Constantin GUNDUZ
- Gregory VAN DER PLUIJM
- Thomas LEUTSCHER

## Project structure

```
.
├── src
│   ├── client
│   │   └── main.cpp
│   ├── model
│   └── server
│       └── main.cpp
├── CMakeLists.txt
├── doxygen
├── LICENSE
├── Makefile
└── README.md
```

## Compilation

### Make + CMake build

```bash
$ make release
```

### Documentation

```bash
$ make docs
```

### Unit Testing

```bash
$ make test
```

## Execution

```bash
$ ./build/release/tetris_server 127.0.0.1 9999
$ ./build/release/tetris_client 127.0.0.1 9999 Nom1
$ ./build/release/tetris_client 127.0.0.1 9999 Nom2
```

Le serveur doit être allumé, et deux clients doivent être connectés pour lancer une partie.