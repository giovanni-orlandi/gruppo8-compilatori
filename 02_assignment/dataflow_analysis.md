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

1. **Very Busy Expression Analysis**

Un'espressione `e` è *very busy* in un punto `p` se su **ogni** cammino da `p` all'`exit block`:
- `e` viene valutata **prima** che uno dei suoi operandi venga ridefinito.

Serve ad ottimizzare via **code hoisting**, ovvero anticipare il calcolo di espressioni senza invalidarle.

|                          | Very busy expression |
|--------------------------|--------------------|
| **Domain**               | $\text{Sets of expressions}$  |
| **Direction**            | $\text{Backword}$  |
| **Transfer function**    | $in[b] = Gen_b \cup \left( out[b] - Kill_b \right)$ |
| **Meet Operation (∧)**   | $\cap$             |
| **Boundary Condition**   | $out[\text{exit}] = \emptyset$ |
| **Initial interior points** | $in[b] = \text{Universal set}$ |


dove:
- $Gen_b$: espressioni generate da istruzioni nel basic block. Es: `a = x + y` genera `x + y` 
- $Kill_b$: ogni espressione di assegnamento killa l'espressione in cui la variabile riassegnata e' un operando 

L'implementazione e' stata pensata con un bit vector per ogni basic block. La lunghezza di ogni bit vector e' pari al numero di espressioni presenti nel CFG.  
In questo caso specifico il bit vector sara' lungo 2:
- **indice 0** → `b-a` (e1)
- **indice 1** → `a-b` (e2)

Esempio:
- `[1, 0]` vuol dire che `b-a` è busy, `a-b` no.





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
