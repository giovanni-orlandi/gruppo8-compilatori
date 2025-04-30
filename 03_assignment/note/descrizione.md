# Assignment 03 - LICM

L'assignment e' stato realizzato come un function pass e tutto il codice specifico di questa ottimizzazione e' nel file loop_invariant.cpp

1. L'ingresso e' una funzione analyze_loop, che itera su tutti i Loop di primo livello grazie a un oggetto LoopInfo.  
Per ogni loop, viene gestita una coda (inizializzata con il loop base) che verra' riempita con eventuali sottoloop e la visita andra' avanti fino a che la lista non sara' vuota.  
Successivamente, se il loop e' in forma naturale, parte l'analisi effettiva.  
Notazione tecnica: usiamo degli array globali per contenere, per ogni loop (e quindi ad ogni iterazione vengono resettati e ripopolati):

- ExitBlocks: tutti i BB di uscita 
- LI_instructions: le varie istruzioni LI individuate incrementalmente
- CMLI_instructions: le varie istruzioni CMLI individuate incrementalmente

2. lo step successivo e' quello di ricavare le istruzioni LI e a quello scopo si usa la funzione get_LI_instructions, che popola il vettore LI_instructions

   - get_LI_instructions -> per trovare le istruzioni LI fa una visita depth_first di tutti i blocchi del loop e, per ogni **istruzione binaria**, valuta i suoi due operandi tramite la funzione ausiliaria is_operand_invariant
     - is_operand_invariant -> ritona true se l'operando e' definito fuori dal loop oppure se e' esso stesso loop_invariant


- [ ] Fare tanti test
- [V] Sistemare codice con funzioni ecc...
- [ ] Finire questo documento + commentare il codice
- [ ] Guardare quella cosa dello spostamento istruzioni