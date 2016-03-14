///funcao que organiza as filas e envia pras pistas

///estrutura da organizacao da fila

for(fila->pri; fila->ult; voo->pro){
  (if voo > novo){
    novo->pro=voo->pro
  }
  else{ //caso não exista nenhum voo menor q o novo
    fila->ult->pro=novo;
    fila->ult=novo;
  }
}
