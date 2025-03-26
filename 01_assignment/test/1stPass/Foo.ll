define dso_local i32 @foo(i32 noundef %0, i32 noundef %1) #0 {
  ;Somma con valore nullo nel primo operatore
  %3 = add i32 0, %1
  ;Somma con valore nullo nel secondo operatore
  %4 = add i32 %0, 0
  ;Somma con entrambi gli operatori operatore nullo
  %5 = add i32 0, 0
  
  ;Moltiplicazione con valore nullo nel primo operatore
  %6 = mul i32 1, %4
  ;Moltiplicazione con valore nullo nel secondo operatore
  %7 = mul i32 %3, 1
  ;Moltiplicazione con entrambi gli operatori operatore nullo
  %8 = mul i32 1, 1

  ;Sottrazione con valore nullo nel primo operatore
  %9 = sub i32 0, %7
  ;Sottrazione con valore nullo nel secondo operatore
  %10 = sub i32 %6, 0
  ;Sottrazione con entrambi gli operatori operatore nullo
  %11 = sub i32 0, 0

  ;VEDERE CASO IN CUI IL NUMERATORE = 0 (STESSA ROBA PER MUL)
  ;Divisione con valore nullo nel primo operatore
  %12 = sdiv i32 1, %10
  ;Divisione con valore nullo nel secondo operatore
  %13 = sdiv i32 %9, 1
  ;Divisione con entrambi gli operatori operatore nullo 
  %14 = sdiv i32 1, 1

  ret i32 %14
}