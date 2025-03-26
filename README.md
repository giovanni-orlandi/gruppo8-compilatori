# gruppo8-compilatori
Repository con la realizzazione degli assignments del corso di **Compilatori (II modulo)**.

**Membri del gruppo:** Ballotti Luca, Mancuso Francesco, Orlandi Giovanni.

---

**COME GENERARE ESEMPI A PARTIRE DA FILE .c**

Da file .c a file .ll
```bash
clang -Xclang -disable-O0-optnone -S -emit-llvm -O0 nome_file.c -o nome_file.ll
```
Rimuovere istruzioni load e store
```bash
opt -p mem2reg nome_file.ll -o nome_file.bc
```
Ritornare da binario a .ll
```
llvm-dis nome_file.bc -o nome_file.ll
```
---

## Cartella: `01_assignment`

Questa cartella contiene il codice relativo al primo assignment.

Si rimanda alla documentazione dentro la cartella: 
[`README.md`](https://github.com/giovanni-orlandi/gruppo8-compilatori/blob/main/01_assignment/README.md)
