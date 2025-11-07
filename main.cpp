#include <iostream>
#include <queue>
#include <string>
#include <iomanip>
using namespace std;

struct Paciente
{
  string nome;
  char prioridade;
  int hora;
  int minuto;
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

int calcularMinutosTotais(int h, int m)
{
  return h * 60 + m;
}

void chegadaPaciente(queue<Paciente> &fila, const string &nome, char prior, int hh, int mm)
{
  Paciente p = {nome, prior, hh, mm};
  fila.push(p);
}

void atendimento(queue<Paciente> &fila, int hh, int mm, int &atendidos, int &total, int &tempoMaximo)
{
  if (fila.empty()) return;

  int nrTempo  = calcularMinutosTotais(hh, mm);
  Paciente p = fila.front();
  fila.pop();

  atendidos++;
  total++;

  int espera = nrTempo - calcularMinutosTotais(p.hora, p.minuto);

  if (espera > tempoMaximo)
    tempoMaximo = espera;

  cout << setw(2)         << setfill('0') << hh << ":"
       << setw(2)         << setfill('0') << mm
       << " Paciente "    << p.nome
       << " (Prioridade " << p.prioridade << ") atendido."
       << endl;
}

void exibirFilas(queue<Paciente> filaV, queue<Paciente> filaA, queue<Paciente> filaD, queue<Paciente> filaB, int nrTotal) {
  cout << "V:" << filaV.size()    << " "
       << "A:" << filaA.size()    << " "
       << "D:" << filaD.size()    << " "
       << "B:" << filaB.size()    << " | "
       << "Atendidos:" << nrTotal << endl;
}

void resumoFinal(int total, int qtFilaV, int qtFilaA, int qtFilaD, int qtFilaB, int pico, int nrTempoMaximo) {
  cout << "Total atendidos: "       << total         << endl
       << "V: " << qtFilaV
       << " A: " << qtFilaA
       << " D: " << qtFilaD
       << " B: " << qtFilaB       << endl
       << "Pico de lotacao: "       << pico          << endl
       << "Maior tempo de espera: " << nrTempoMaximo << endl;
}

int main()
{
  int qtAtendidosV      = 0,
      qtAtendidosA      = 0,
      qtAtendidosD      = 0,
      qtAtendidosB      = 0,
      totalAtendidos    = 0,
      picoLotacao       = 0,
      tempoMaximoEspera = 0;
  string comando;
  queue<Paciente> filaV, filaA, filaD, filaB;

  while (cin >> comando)
  {
    if (comando == "C")
    {
      string nome;
      char   prior;
      int    hh, mm;

      cin >> nome >> prior >> hh >> mm; prior = toupper(prior);

      if (prior == 'V')
        chegadaPaciente(filaV, nome, prior, hh, mm);
      else if (prior == 'A')
        chegadaPaciente(filaA, nome, prior, hh, mm);
      else if (prior == 'D')
        chegadaPaciente(filaD, nome, prior, hh, mm);
      else if (prior == 'B')
        chegadaPaciente(filaB, nome, prior, hh, mm);

      int qtTamanhoFila = filaV.size() + filaA.size() + filaD.size() + filaB.size();

      if (qtTamanhoFila > picoLotacao) 
        picoLotacao = qtTamanhoFila;
    }

    else if (comando == "A")
    {
      int hh, mm; cin >> hh >> mm;
    
      if (!filaV.empty())
        atendimento(filaV, hh, mm, qtAtendidosV, totalAtendidos, tempoMaximoEspera);
      else if (!filaA.empty())
        atendimento(filaA, hh, mm, qtAtendidosA, totalAtendidos, tempoMaximoEspera);
      else if (!filaD.empty())
        atendimento(filaD, hh, mm, qtAtendidosD, totalAtendidos, tempoMaximoEspera);
      else if (!filaB.empty())
        atendimento(filaB, hh, mm, qtAtendidosB, totalAtendidos, tempoMaximoEspera);
      else
        cout << setw(2)                                  << setfill('0') << hh << ":"
             << setw(2)                                  << setfill('0') << mm
             << " Sem pacientes aguardando atendimento." << endl;
    }


    else if (comando == "D")
      exibirFilas(filaV, filaA, filaD, filaB, totalAtendidos);

    else if (comando == "Q")
    {
      resumoFinal(totalAtendidos, qtAtendidosV, qtAtendidosA, qtAtendidosD, 
                  qtAtendidosB, picoLotacao, tempoMaximoEspera);
      break;
    }
  }

  return 0;
}