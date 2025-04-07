# Assignment 2: Dataflow Analysis

**Gruppo 8**  
Componenti:
- Giovanni Orlandi
- Francesco Mancuso
- Luca Ballotti

---

## Introduzione

Questo documento presenta il lavoro svolto dal gruppo 8 per l'Assignment 2 del corso di Compilatori, incentrato sull'implementazione di analisi di flusso di dati (**Dataflow Analysis**) all'interno di un compilatore.

L'obiettivo principale dell'assegnamento era progettare e implementare un'analisi capace di raccogliere informazioni statiche sul comportamento dei programmi, utilizzando tecniche standard di forward e backward analysis. L'analisi è stata sviluppata seguendo i principi teorici introdotti a lezione, adattandoli al contesto pratico fornito.

---

1. **Very busy expression**

|                          | Very busy expression |
|--------------------------|--------------------|
| **Domain**               | $\text{Sets of expressions}$  |
| **Direction**            | $\text{Backword}$  |
| **Transfer function**    | $in[b] = gen[b] \cup \left( out[b] - kill[b] \right)$ |
| **Meet Operation (∧)**   | $\cap$             |
| **Boundary Condition**   | $out[\text{exit}] = \emptyset$ |
| **Initial interior points** | $in[b] = \text{Universal set}$ |


---

2. **Dominator analysis**

|                          | Dominator Analysis |
|--------------------------|--------------------|
| **Domain**               | $\text{Sets of BB}$ |
| **Direction**            | $\text{Forward}$ |
| **Transfer function**    | $out[b] = B \cup in[b]$ |
| **Meet Operation (∧)**   | $\cap$ |
| **Boundary Condition**   | $out[\text{Entry}] = \text{Entry}$ |
| **Initial interior points** | $out[b] = \text{Universal set}$ |


---

3. **Constant propagation**
   
|                          | Constant propagation |
|--------------------------|--------------------|
| **Domain**               | $\text{(var, valore)}$ |
| **Direction**            | $\text{Forward}$ |
| **Transfer function**    | $out[b] = gen[b] \cup \left( in[b] - kill[b] \right)$ |            
| **Meet Operation (∧)**   | $\cap$ |
| **Boundary Condition**   | $out[\text{Entry}] = \emptyset$ |
| **Initial interior points** | $out[b] = \text{Universal set}$ |
