# gruppo8-compilatori
Repository con la realizzazione degli assignments del corso di **Compilatori (II modulo)**.

**Membri del gruppo:** Ballotti Luca, Mancuso Francesco, Orlandi Giovanni.

---

## Cartella: `01_assignment`

Questa cartella contiene il codice relativo al primo assignment.

### File principali
- [`LocalOpts.cpp`](https://github.com/giovanni-orlandi/gruppo8-compilatori/blob/main/01_assignment/LocalOpts.cpp): plugin LLVM che implementa tre passi di ottimizzazione locale. Ogni pass esegue un'analisi semplice sulle funzioni di un modulo LLVM.
- [`AlgIdRem_skeleton.cpp`](https://github.com/giovanni-orlandi/gruppo8-compilatori/blob/main/01_assignment/AlgIdRem_skeleton.cpp): implementa il primo passo di ottimizzazione, **Algebraic Identity Removal**.
- [`StrRed_skeleton.cpp`](https://github.com/giovanni-orlandi/gruppo8-compilatori/blob/main/01_assignment/StrRed_skeleton.cpp): implementa il secondo passo, una **Strength Reduction** avanzata.
- `MultiInst_skeleton.cpp`: implementa il terzo passo, la **Multi-Instruction Optimization**.

### Cartella `test/`
Contiene file `.ll` utili per testare i diversi casi:

- `01.ll`: test per **Algebraic Identity Removal**
- `02.ll`: test per **Strength Reduction**, include casi particolari:
  - `x * n`, `n * x`, `x / 2` dove `n` è una potenza esatta di 2
  - `x * n`, `n * x` dove `n + 1` o `n - 1` è una potenza di 2
  - Casi limite che **non** devono essere trasformati (es. `x * n` con `n + 2` potenza di 2)
