#include <iostream>
#include <queue>
#include "funcoes.cpp"

using namespace std;

struct fila
{
  int nrSenha;
  int nrHora;
  int nrMinuto;
};

void atendimento(fila &prio)
{
  prio.
}

int main()
{
  bool idEncerrado = false;
  char dsComando;
  int  nrContadorV = 0,
       nrContadorA = 0,
       nrContadorD = 0, 
       nrContadorB = 0;
  queue<fila> filaV;
  queue<fila> filaA;
  queue<fila> filaD;
  queue<fila> filaB;

  menu();

  while (!idEncerrado)
  {
    cin >> dsComando;

    if (!filaV.empty())
      atendimento(filaV);
    else if (filaV.empty() && !filaA.empty())
      atendimento(filaA);
    else if (filaA.empty() && !filaD.empty())
      atendimento(filaD);
    else
      atendimento(filaB);
    

      

    if (dsComando = 'Q')
      idEncerrado = true;
  }
  
  return 0;
}