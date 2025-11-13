#include <iostream>
#include <queue>
#include <string>
#include <iomanip>

struct Paciente
{
  std::string nome;
  char        prioridade;
  int         hora, minuto;
};

void menu()
{
  std::cout << "\n===== MENU DE COMANDOS ====="    << std::endl
            << "C -> Chegada de paciente"          << std::endl
            << "A -> Atendimento"                  << std::endl
            << "D -> Exibir informações das filas" << std::endl
            << "Q -> Encerrar a simulação"         << std::endl
            << "=============================="    << std::endl;
}

int calcularMinutos(int nrHora, int nrMinuto)
{
  return (nrHora * 60) + nrMinuto;
}

void contarChegadaPessoa(std::queue<Paciente> &fila, const std::string &nome, char dsPrioridade, int nrHora, int nrMinuto)
{
  Paciente p = {nome, dsPrioridade, nrHora, nrMinuto};
  fila.push(p);
}

void atenderProximo(std::queue<Paciente> &fila, int nrHora, int nrMinuto, int &atendidos, int &total, int &tempoMaximo)
{
  if (fila.empty())
    return;

  int nrTempo  = calcularMinutos(nrHora, nrMinuto);
  Paciente p   = fila.front();
  fila.pop();

  atendidos++;
  total++;

  int espera = nrTempo - calcularMinutos(p.hora, p.minuto);

  if (espera > tempoMaximo)
    tempoMaximo = espera;

  std::cout << std::setw(2)    << std::setfill('0') << nrHora << ":"
            << std::setw(2)    << std::setfill('0') << nrMinuto
            << " Paciente "    << p.nome
            << " (Prioridade " << p.prioridade      << ") atendido."
            << std::endl;
}

void exibirFilas(std::queue<Paciente> filaV, std::queue<Paciente> filaA, std::queue<Paciente> filaD, std::queue<Paciente> filaB, int nrTotal)
{
  std::cout << "V:" << filaV.size()    << " "
            << "A:" << filaA.size()    << " "
            << "D:" << filaD.size()    << " "
            << "B:" << filaB.size()    << " | "
            << "Atendidos:" << nrTotal << std::endl;
}

void resumoFinal(int total, int qtFilaV, int qtFilaA, int qtFilaD, int qtFilaB, int pico, int nrTempoMaximo)
{
  std::cout << "Total atendidos: "       << total         << std::endl
            << "V: "                     << qtFilaV
            << " A: "                    << qtFilaA
            << " D: "                    << qtFilaD
            << " B: "                    << qtFilaB       << std::endl
            << "Pico de lotacao: "       << pico          << std::endl
            << "Maior tempo de espera: " << nrTempoMaximo << std::endl;
}

int main()
{
  int qtAtendidosV = 0,
      qtAtendidosA = 0,
      qtAtendidosD = 0,
      qtAtendidosB = 0,
      qtAtendidos  = 0,
      picoLotacao  = 0,
      nrMaxTempo   = 0;

  std::string comando;
  std::queue<Paciente> filaV, filaA, filaD, filaB;

  menu();

  while (std::cin >> comando)
  {
    int nrHora = 0, nrMinuto = 0;

    if (comando == "C")
    {
      std::string nome;
      char        dsPrioridade;
      int         nrHora, nrMinuto;

      std::cin >> nome >> dsPrioridade >> nrHora >> nrMinuto; dsPrioridade = toupper(dsPrioridade);

      if (dsPrioridade == 'V')
        contarChegadaPessoa(filaV, nome, dsPrioridade, nrHora, nrMinuto);
      else if (dsPrioridade == 'A')
        contarChegadaPessoa(filaA, nome, dsPrioridade, nrHora, nrMinuto);
      else if (dsPrioridade == 'D')
        contarChegadaPessoa(filaD, nome, dsPrioridade, nrHora, nrMinuto);
      else if (dsPrioridade == 'B')
        contarChegadaPessoa(filaB, nome, dsPrioridade, nrHora, nrMinuto);

      int qtTamanhoFila = filaV.size() + filaA.size() + filaD.size() + filaB.size();

      if (qtTamanhoFila > picoLotacao) 
        picoLotacao = qtTamanhoFila;
    }

    else if (comando == "A")
    {
      std::cin >> nrHora >> nrMinuto;
    
      if (!filaV.empty())
        atenderProximo(filaV, nrHora, nrMinuto, qtAtendidosV, qtAtendidos, nrMaxTempo);
      else if (!filaA.empty())
        atenderProximo(filaA, nrHora, nrMinuto, qtAtendidosA, qtAtendidos, nrMaxTempo);
      else if (!filaD.empty())
        atenderProximo(filaD, nrHora, nrMinuto, qtAtendidosD, qtAtendidos, nrMaxTempo);
      else if (!filaB.empty())
        atenderProximo(filaB, nrHora, nrMinuto, qtAtendidosB, qtAtendidos, nrMaxTempo);
      else
        std::cout << std::setw(2)                             << std::setfill('0') << nrHora << ":"
                  << std::setw(2)                             << std::setfill('0') << nrMinuto
                  << " Sem pacientes aguardando atendimento." << std::endl;
    }


    else if (comando == "D")
      exibirFilas(filaV, filaA, filaD, filaB, qtAtendidos);

    else if (comando == "Q")
    {
      resumoFinal(qtAtendidos, qtAtendidosV, qtAtendidosA, qtAtendidosD, 
                  qtAtendidosB, picoLotacao, nrMaxTempo);
      break;
    }
  }

  return 0;
}