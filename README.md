# gruppo8-compilatori
Repository con la realizzazione degli assignments del corso di **Compilatori (II modulo)**.

**Membri del gruppo:** Ballotti Luca, Mancuso Francesco, Orlandi Giovanni.

---

**COME GENERARE ESEMPI A PARTIRE DA FILE .c**

Da file .cpp a .ll
```bash
clang++ -Xclang -disable-O0-optnone -O0 -S -emit-llvm file_test.cpp -o file_test.ll
```

Rimuovere istruzioni load e store
```bash
opt -S -p file_test.ll -o file_test.m2r.ll
```

---

## Cartella: `01_assignment`

Questa cartella contiene il codice relativo al primo assignment.

Si rimanda alla documentazione dentro la cartella: 
[`README.md`](https://github.com/giovanni-orlandi/gruppo8-compilatori/blob/main/01_assignment/README.md)

---

## Cartella: `02_assignment`

Questa cartella contiene la realizzazione del secondo assignment, in quest'unico file: [`dataflow_analysis.md`](https://github.com/giovanni-orlandi/gruppo8-compilatori/blob/main/02_assignment/dataflow_analysis.md)

---

## Cartella: `03_assignment`

Questa cartella contiene il codice relativo al terzi assignment.

Si rimanda alla documentazione dentro la cartella: 
[`README.md`](https://github.com/giovanni-orlandi/gruppo8-compilatori/blob/main/03_assignment/README.md)

---