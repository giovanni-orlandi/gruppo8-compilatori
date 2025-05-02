### File principali

- [`LocalOpts.cpp`](https://github.com/giovanni-orlandi/gruppo8-compilatori/blob/main/03_assignment/CMLIOpt.cpp)  
  Plugin LLVM che registra e gestisce il passo di ottimizzazione.

- [`loop_invariant.cpp`](https://github.com/giovanni-orlandi/gruppo8-compilatori/blob/main/03_assignment/loop_invariant.cpp)  
  Implementa il Passo di LICM

#### Cartella `test/`

Contiene file `.ll` e `.c` utilizzati per testare l'ottimizzazione, con diversi esempi e casi.  

---

### Uso e comandi

Ogni ottimizzazione è invocabile singolarmente.  

(**NOTA**: per partire da un file `.c` si rimanda alla sezione *COME GENERARE ESEMPI A PARTIRE DA FILE .c* sul README generale del repository)

Una volta che si ha il file (`nome_file.ll`) di partenza su cui applicare l'ottimizzazione desiderata, questi sono i comandi da eseguire.


#### Comando per applicare un'ottimizzazione:
```
opt -load-pass-plugin build/libLocalOpts.so -p nome_ottimizzazione nome_file.ll -o nome_file.bc
```

#### Comando per convertire il file `.bc` ottimizzato in `.ll` leggibile:
```
llvm-dis nome_file.bc -o nome_file.optimized.ll
```

### Passo disponibile

| Nome Ottimizzazione (`-p`) | Descrizione                                      | File Sorgente            |
|----------------------------|--------------------------------------------------|---------------------------|
| `cmli`               | Loop Invariant Code Motion             | `loop_invariant.cpp`        |


---

### Logica algoritmica

Si rimanda al file sorgente [`loop_invariant.cpp`](https://github.com/giovanni-orlandi/gruppo8-compilatori/blob/main/03_assignment/loop_invariant.cpp) per una descrizione dettagliata dell'implementazione.

### Riassunto dell’approccio:

1. La funzione principale è `analyze_loop`, che analizza tutti i loop di primo livello sfruttando un oggetto `LoopInfo`.  
   Per ciascun loop, viene gestita una **coda** inizializzata con il loop stesso; eventuali sottoloop vengono aggiunti dinamicamente alla coda, che viene svuotata iterativamente.  
   Una volta estratto un loop, se questo è in **forma naturale**, si procede con l’analisi.  
   A ogni iterazione, vengono **azzerati e ripopolati** tre vettori globali utilizzati durante l’analisi:

   - `ExitBlocks`: blocchi di uscita del loop  
   - `LI_instructions`: istruzioni loop-invariant identificate in modo incrementale  
   - `CMLI_instructions`: istruzioni candidate alla code motion (sottoinsieme delle precedenti)

2. Successivamente, si individuano le istruzioni loop-invariant tramite la funzione `get_LI_instructions`, che popola `LI_instructions`.  
   > **Nota:** poiché l’invarianza viene determinata incrementando i risultati parziali, si utilizza una visita in profondità (depth-first) per garantire un ordine corretto. Questo evita la necessità di una fase di riordinamento finale per la code motion, in quanto le istruzioni risultano già ordinate correttamente.

3. Una volta raccolte tutte le istruzioni loop-invariant, si applicano le condizioni necessarie per la code motion. Le istruzioni che le soddisfano vengono aggiunte a `CMLI_instructions`.

4. Infine, vengono spostate solo le istruzioni in `CMLI_instructions` i cui operandi siano anch’essi già stati spostati, garantendo così la correttezza semantica dell’ottimizzazione.

