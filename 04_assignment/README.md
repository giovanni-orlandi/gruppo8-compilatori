### File principali

- [`LFOpt.cpp`](https://github.com/giovanni-orlandi/gruppo8-compilatori/blob/main/04_assignment/LFOpt.cpp)  
  Plugin LLVM che registra e gestisce il passo di ottimizzazione.

- [`loop_fusion.cpp`](https://github.com/giovanni-orlandi/gruppo8-compilatori/blob/main/04_assignment/loop_fusion.cpp)  
  Implementa il Passo di loop fusion

- [`utility.cpp`](https://github.com/giovanni-orlandi/gruppo8-compilatori/blob/main/04_assignment/utility.cpp)  
  Contiene funzioni ausiliarie

#### Cartella `test/`

Contiene file `.ll` e `.c` utilizzati per testare l'ottimizzazione, con diversi esempi e casi.  

---

### Uso e comandi

Una volta compilato, bastera' far partire lo script bash con il seguente comando 

```
./test_cmd.sh
```

### Passo disponibile

| Nome Ottimizzazione (`-p`) | Descrizione                                      | File Sorgente            |
|----------------------------|--------------------------------------------------|---------------------------|
| `loopfusion'               | Loop Fusion            | `loop_fusion.cpp`        |


---

### Logica algoritmica

Si rimanda al file sorgente [`loop_fusion.cpp`](https://github.com/giovanni-orlandi/gruppo8-compilatori/blob/main/04_assignment/loop_fusion.cpp) per una descrizione dettagliata dell'implementazione.

### Riassunto dell’approccio:

Si parte dalla funzione analyze_loop la cui struttura puo' sembrare complessa ma che e' realizzata in maniera tale da garantire l'ottimizzazione multipla di loop e subloop senza rompersi o dover ripartire da capo.  
E' infatti presente un ciclo esterno che va avanti fino a convergenza, ovvero fino a che tutti i possibili loop da unificare non sono stati unificati.  
Due sotto-cicli hanno invece il ruolo di:

1. Popolare una worklist con tutti i cicli
2. Scorrere la worklist a coppie per verificare eventuali possibilita' di fusion (nota: la scorriamo al contrario perche' i loop vengono inseriti dall'ultimo al primo); durante lo scorrimento, si verificano il rispetto di eventuali condizioni e, se cio' accade, si procede alla fusion. 
Una volta unificati due loop bisogna ripartire da capo, visto che sono state invalidate svariate analisi, e dunque abbiamo optato con l'invalidazione di tutte le analisi cosiche, una volta ripetuto il ciclo esterno, vengano ricalcolate nella maniera corretta e venga ripopolata la giusta worklist.

I dettagli sulle funzioni dei controlli e della fusion (e non solo) sono presenti nel sorgente.