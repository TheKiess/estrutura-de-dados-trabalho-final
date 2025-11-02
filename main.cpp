#include <iostream>
#include <queue>
#include "funcoes.h"

using namespace std;

struct fila
{
  int nrSenha;
  int nrHora;
  int nrMinuto;
};

int main()
{
  bool idEncerrado = false;
  char dsComando;
  queue<fila> filaV;
  queue<fila> filaA;
  queue<fila> filaD;
  queue<fila> filaB;

  while (!idEncerrado)
  {
    menu();
    cin >> dsComando;

    if (dsComando = 'Q')
      idEncerrado = true;
  }
  
  return 0;
}