#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

struct fila
{
  int nrSenha;
  int nrHora;
  int nrMinuto;
};

void menu()
{
  cout << "\n===== MENU DE COMANDOS ====="    << endl
       << "C -> Chegada de paciente"          << endl
       << "A -> Atendimento"                  << endl
       << "D -> Exibir informações das filas" << endl
       << "Q -> Encerrar a simulação"         << endl
       << "=============================="    << endl;
}

fila gerarSenha(int &contador)
{
  filaNova.nrSenha  = ++contador;
}

void chegadaPaciente(queue<fila> &filaNova, int &contador, const string &tipo)
{
  filaNova nova = gerarSenha(contador);
  filaNova.push(nova);
}

void exibirFilas(queue<fila> filaV, queue<fila> filaA, queue<fila> filaD, queue<fila> filaB)
{
}

void atendimento(queue<fila> &filaAtendimento, const string &tipo)
{
  if (!filaAtendimento.empty())
  {
    fila atual = fila.front();
    filaAtendimento.pop();
  }
  else
    cout << "Nenhum paciente na fila " << tipo << "!\n";
}

void atendimento(queue<fila> &fila, const string &tipo)
{
  if (!fila.empty())
  {
    fila atual = fila.front();
    fila.pop();
  }
  else
    cout << "Nenhum paciente na fila " << tipo << "!\n";
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
  fila        aux;

  menu();

  while (!idEncerrado)
  {
    cin >> dsComando;
    transform(dsComando.begin(), dsComando.end(), dsComando.begin(), ::toupper);

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