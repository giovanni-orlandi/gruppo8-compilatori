#!/bin/bash

# Verifica che sia stato passato un argomento
if [ -z "$1" ]; then
  echo "Uso: $0 <file.cpp>"
  exit 1
fi

# Path completo senza estensione
FILE="$1"
BASENAME="${FILE%.*}"  # rimuove .cpp

# Compila in LLVM IR (.ll)
clang++ -Xclang -disable-O0-optnone -O0 -S -emit-llvm "$FILE" -o "$BASENAME.ll" || exit 1

# Applica mem2reg
opt -S -p mem2reg "$BASENAME.ll" -o "$BASENAME.m2r.ll" || exit 1

# Applica il tuo pass cmli
opt -load-pass-plugin ./build/libCMLIOpt.so -passes=cmli "$BASENAME.m2r.ll" -S -o "$BASENAME.optimized.ll" || exit 1

echo "Ottimizzazione completata: $BASENAME.optimized.ll"
