### File principali

#### Cartella `src/` 

- [`LocalOpts.cpp`](https://github.com/giovanni-orlandi/gruppo8-compilatori/blob/main/01_assignment/src/LocalOpts.cpp)  
  Plugin LLVM che registra e gestisce tre passi di ottimizzazione locali. Ogni pass effettua una trasformazione semplice sulle funzioni di un modulo LLVM.

- [`AlgIdRem.cpp`](https://github.com/giovanni-orlandi/gruppo8-compilatori/blob/main/01_assignment/src/AlgIdRem.cpp)  
  Implementa il Passo 1: Algebraic Identity Removal, eliminando operazioni banali come `x + 0`, `x * 1`, `x - 0`, ecc.

- [`StrRed.cpp`](https://github.com/giovanni-orlandi/gruppo8-compilatori/blob/main/01_assignment/src/StrRed.cpp)  
  Implementa il Passo 2: Strength Reduction avanzata, trasformando moltiplicazioni e divisioni per potenze di 2 in shift.

- [`MultiInstOpt.cpp`](https://github.com/giovanni-orlandi/gruppo8-compilatori/blob/main/01_assignment/src/MultiInstOpt.cpp)  
  Implementa il Passo 3: Multi-Instruction Optimization, semplificando catene di istruzioni aritmetiche ridondanti.

#### Cartella `test/`

Contiene file `.ll` e `.c` utilizzati per testare i vari passi di ottimizzazione.  
Ogni sottocartella corrisponde a un pass specifico:

- `test/1stPass/Foo.ll`: test per Algebraic Identity Removal
- `test/2ndPass/Foo.ll`: test per Strength Reduction, include casi come:
  - `x * n`, `n * x`, `x / 2` dove `n` è una potenza esatta di 2
  - `x * n`, `n * x` dove `n + 1` o `n - 1` è una potenza di 2
  - Casi limite che **non** devono essere trasformati (es. `x * n` con `n + 2` potenza di 2)

- `test/3rdPass/`: test per Multi-Instruction Optimization
  - `Foo.ll`: input originale
  - `Foo.optimized.bc`: output ottimizzato in bytecode
  - `Foo.optimized.ll`: output ottimizzato in formato leggibile LLVM IR

---

### Uso e comandi

Ogni ottimizzazione è invocabile singolarmente.  

**NOTA**: per partire da un file `.c` si rimanda alla sezione *COME GENERARE ESEMPI A PARTIRE DA FILE .c* sul README generale del repository.

Una volta che si ha il file (`nome_file.ll`) di partenza su cui applicare l'ottimizzazione desiderata, questi sono i comandi da eseguire.


#### Comando per applicare un'ottimizzazione:
```
opt -load-pass-plugin build/libLocalOpts.so -p nome_ottimizzazione nome_file.ll -o nome_file.bc
```

#### Comando per convertire il file `.bc` ottimizzato in `.ll` leggibile:
```
llvm-dis nome_file.bc -o nome_file.optimized.ll
```

### Tabella dei passi disponibili

| Nome Ottimizzazione (`-p`) | Descrizione                                      | File Sorgente (dir src/)            |
|----------------------------|--------------------------------------------------|---------------------------|
| `alg-id-rem`               | Algebraic Identity Removal (Passo 1)             | `AlgIdRem.cpp`        |
| `str-red`                  | Strength Reduction (Passo 2)                     | `StrRed.cpp`          |
| `multi-inst`               | Multi-Instruction Optimization (Passo 3)         | `MultiInstOpt.cpp`    |

---

### Logica algoritmica

Si rimanda ai singoli file sorgente, che contengono descrizioni dettagliate.
