//Bibliotecas utilizadas
#include <iostream>
#include <limits>
#include "voo.h"


#include <fstream>
#include <map>
#include <iomanip> // Adicionado para formatação

using namespace std;

//MENU
void menu(BancoDeDados& b) {
    int opc = 0;
    do {
        printMenu();
        cin >> opc;
        cin.ignore();

        switch (opc) {
            case 1:{
                Aeronave novaAeronave = cadastrarAeronave(b);
                b.adicionarAeronave(novaAeronave);
                break;
            }
            case 2:{ 
                Piloto novoPiloto = cadastrarPiloto(b);
                b.adicionarPiloto(novoPiloto);
                break;
            }
            case 3:{ 
                Passageiro novoPassageiro = cadastrarPassageiro(b);
                b.adicionarPassageiro(novoPassageiro);
                break;
            }
            case 4:{
                Voos novoVoo = cadastrarVoo(b);
                b.adicionarVoo(novoVoo);
                break;
            }
            case 5:
                embarcarPassageiroVoo(b);
                break;
            case 6 :
                b.mostrarDadosVoo();
                break;
            case 7:
                listarPassageirosVoo(b);
                break;
            case 8:
                gerarRelatoriosEstatisticas(b);
                break;
            case 9:
                b.salvarDados();
                cout << "Dados salvos com sucesso. Saindo do programa." << endl;
                break;
            default:
                if (opc != 9) {
                    cout << "Opcao invalida! Tente novamente." << endl;
                }
                break;
        }
    }
    while(opc != 9);
    return;
}

//Cadastros
Aeronave cadastrarAeronave(BancoDeDados& b) {
    string entrada, modelo;
    int cod, cap;
    float velM, autV;

    cout << "|Cadastro Aeronave|\n";
    //Entrada codigo
    cout << "Digite o codigo: ";
    cod = retornaInteiro();

    //entrada modelo
    cout << "Digite o modelo: ";
    modelo = retornaString();

    // entrada capacidade 
    cout << "Digite a capacidade: ";
    cap = retornaInteiro();

    //Entrada velocidade media
    cout << "Digite a velocidade media(milhas por hora): ";
    velM = retornaDouble();

    //Entrada autonomia media
    cout << "Digite a autonomia media(distancia em milhas): ";
    autV = retornaDouble();

    Aeronave novaAeronave(cod, modelo, cap, velM, autV);
    return novaAeronave; 
}

Piloto cadastrarPiloto(BancoDeDados& b) { //Cadastro Piloto
    int matricula;
    double horasVoo;
    string entrada, nome, breve;

    cout << "|Cadastro Piloto|\n";
    //Entrada nome
    cout << "Digite o nome do piloto: ";
    nome = retornaString();

    //Entrada matricula
    cout << "Digite a matricula do piloto: ";
    matricula = retornaInteiro();

    //Entrada breve
    cout << "Digite o breve do piloto: ";
    breve = retornaString();

    //Entrada horas de voo
    cout << "Digite as horas de voo: ";
    horasVoo = retornaDouble();

    //Funcao construtor Piloto
    Piloto novoPiloto(nome, matricula, breve, horasVoo);
    return novoPiloto;
}

Passageiro cadastrarPassageiro(BancoDeDados& b) { //Cadastro passageiros
    string nome;
    int cpf, numeroBilhete;

    cout << "|Cadastrar Passageiro|\n";
    //Entrada nome
    cout << "Digite o nome do passageiro: ";
    nome = retornaString();   

    //Entrada CPF
    cout << "Digite o CPF: ";
    cpf = retornaInteiro();

    //Entrada bilhete
    cout << "Digite o numero do bilhete: ";
    numeroBilhete = retornaInteiro();

    //Funcao construtor Passageiro
    Passageiro novoPassageiro(nome, cpf, numeroBilhete);
    return novoPassageiro;
}



Voos cadastrarVoo(BancoDeDados& b) { //Cadastro Voos
    int codigo;
    string origem, destino;
    double distancia, horaSaida;
    Aeronave novaAeronave;
    Piloto novoPrimeiroOfc;
    Piloto novoComandante;
    Passageiro novoPassageiro;
    
    cout << "|Cadastro Voo|\n";
    //Entrada codigo do voo
    cout << "Digite o codigo do Voo: ";
    codigo = retornaInteiro();

    //Entrada origem
    cout << "Digite a origem do Voo: ";
    origem = retornaString();

    //Entrada destino
    cout << "Digite o destino do Voo: ";
    destino = retornaString();

    //Entrada distancia
    cout << "Digite a distancia do Voo: ";
    distancia = retornaDouble();

    //Entrada horas saida
    cout << "Digite a hora de saida do Voo (formato 24h): ";
    horaSaida = retornaDouble();

    //Cadastro de classes
    //Aeronaves
    cout << "Deseja cadastrar uma Aeronave ou usar o banco de dados para ver as disponiveis? (c / b)";
    char AeroOpc;
    while(true) {
        //Entrada opcao
        AeroOpc = retornaChar();
        if(toupper(AeroOpc) != 'C' && toupper(AeroOpc) != 'B') {
            cout << "Digite uma opcao valida! (c / b)";
            continue;
        }
        //opcao cadastrar
        else if(toupper(AeroOpc) == 'C') 
            novaAeronave = cadastrarAeronave(b);
        //Banco de dados
        else {
            if(b.getSizeAeronave() == 0) {
                cout << "Nao ha Aeronaves cadastradas! \n";
                novaAeronave = cadastrarAeronave(b);
            }
            else {
                b.mostrarDadosAeronave();
                int opc;
                cout << "Digite o numero correspondente a Aeronave desejada: ";
                opc = retornaInteiro();
                if(opc > b.getSizeAeronave())
                    opc = b.getSizeAeronave();
                novaAeronave = b.getAeronave(opc -1);
            }
        }
        break;
    }
    //Comandante
    cout << "Deseja cadastrar um Comandante ou usar o banco de dados para ver os disponiveis? (c / b)";
    while(true) {
        //Entrada opcao
        AeroOpc = retornaChar();
        if(toupper(AeroOpc) != 'C' && toupper(AeroOpc) != 'B') {
            cout << "Digite uma opcao valida! (c / b)";
            continue;
        }
        //opcao cadastrar
        else if(toupper(AeroOpc) == 'C') 
            novoComandante = cadastrarPiloto(b);
        //Banco de dados
        else {
            if(b.getSizePilotos() == 0) {
                cout << "Nao ha Comandantes cadastradas! \n";
                novoComandante = cadastrarPiloto(b);
            }
            else {
                b.mostrarDadosPiloto();
                int opc;
                cout << "Digite o numero correspondente ao comandante desejado: ";
                opc = retornaInteiro();
                if(opc > b.getSizePilotos())
                    opc = b.getSizePilotos();
                novoComandante = b.getPiloto(opc -1);
            }
        }
        break;
    }
    //Primeiro oficial
    cout << "Deseja cadastrar um Primeiro oficial ou usar o banco de dados para ver os disponiveis? (c / b)";
    while(true) {
        //Entrada opcao
        AeroOpc = retornaChar();
        if(toupper(AeroOpc) != 'C' && toupper(AeroOpc) != 'B') {
            cout << "Digite uma opcao valida! (c / b)";
            continue;
        }
        //opcao cadastrar
        else if(toupper(AeroOpc) == 'C') 
            novoPrimeiroOfc = cadastrarPiloto(b);
        //Banco de dados
        else {
            if(b.getSizePilotos() == 0) {
                cout << "Nao ha Primeiros oficiais cadastradas! \n";
                novoPrimeiroOfc = cadastrarPiloto(b);
            }
            else {
                b.mostrarDadosPiloto();
                int opc;
                cout << "Digite o numero correspondente ao comandante desejado: ";
                opc = retornaInteiro();
                if(opc > b.getSizePilotos())
                    opc = b.getSizePilotos();
                novoPrimeiroOfc = b.getPiloto(opc -1);
            }
        }
        break;
    }

    cout << "Deseja cadastrar ou buscar no banco de dados algum passageiro para o voo? (C / B)";
    while(true) {
        //Entrada opcao
        AeroOpc = retornaChar();
        if(toupper(AeroOpc) != 'C' && toupper(AeroOpc) != 'B') {
            cout << "Digite uma opcao valida! (c / b)";
            continue;
        }
        //opcao cadastrar
        else if(toupper(AeroOpc) == 'C') 
            novoPassageiro = cadastrarPassageiro(b);
        //Banco de dados
        else {
            if(b.getSizePassageiros() == 0) {
                cout << "Nao ha Passageiros cadastradas! \n";
                novoPassageiro = cadastrarPassageiro(b);
            }
            else {
                b.mostrarDadosPassageiro();
                int opc;
                cout << "Digite o numero correspondente ao Passageiro desejado: ";
                opc = retornaInteiro();
                if(opc > b.getSizePassageiros())
                    opc = b.getSizePassageiros();
                novoPassageiro = b.getPassageiro(opc -1);
            }
        }
        break;
    }

    //Setando informacoes no Voo
    double tempoEstimado = novaAeronave.getVelocidade() / distancia;
    Voos novoVoo (codigo, origem, destino, distancia, horaSaida, tempoEstimado);
    novoVoo.setAeronave(novaAeronave);
    novoVoo.setComandante(novoComandante);
    novoVoo.setPrimeiroOficial(novoPrimeiroOfc);
    novoVoo.adicionarPassageiro(novoPassageiro);
    return novoVoo;
}

//Impressoes
void printMenu() { //Print do meu
    cout << "======= SISTEMA DE CONTROLE DE VOOS =======\n"
         << "1. Cadastrar aeronave\n"
         << "2. Cadastrar piloto\n"
         << "3. Cadastrar passageiro\n"
         << "4. Criar voo\n"
         << "5. Embarcar passageiro em voo\n"
         << "6. Listar voos\n"
         << "7. Listar passageiros de um voo\n"
         << "8. Gerar relatorios e estatisticas\n"
         << "9. Salvar dados e sair\n"
         << "===========================================\n"
         << "Escolha uma opcao: ";
}

void Aeronave::mostrarDados() const{ //Impressao informacoes Aeronaves
    cout << "Dados aeronave: \n"
         << "Codigo - " << codigo << endl
          << "Modelo - "<< modelo << endl
          << "Capacidade - " << capacidade << endl
          << "Velocidade media - " << velocidadeMed << endl
          << "Autonomia voo - " << autonomiaVoo << endl;
    cout << "-------------------------------------\n";    
}

void Piloto::mostrarDados() const{ //Impressao Pilotos
    cout << "Dados Piloto: \n"
         << "Nome - " << nome << endl
          << "Matricula - "<< matricula << endl
          << "Breve - " << breve << endl
          << "Horas Voo - " << horasVoo << endl;
    cout << "-------------------------------------\n";       
}

void Passageiro::mostrarDados() const{ //Impressao Passageiros
    cout << "Dados Passageiro: \n"
         << "Nome - " << nome << endl
         << "CPF - "<< cpf << endl
         << "Numero do bilhete - " << numeroBilhete << endl;
    cout << "-------------------------------------\n";    
}

void Voos :: mostrarDados() const {
    cout << "Dados Voo: \n"
         << "Codigo - " << codigo << endl
         << "Origem - " << origem << endl
         << "Destino - " << destino << endl
         << "Distancia - " << distancia << endl
         << "Hora de saida - " << horaSaida << endl
         << "Tempo estimado - " << tempoEstimado << endl;

    aeronaveVoo.mostrarDados();
    comandante.mostrarDados();
    primeiroOficial.mostrarDados();
    for(int i = 0; i < getSizePassageiros(); i++)
        passageiros[i].mostrarDados();
}

//Listar elementos do banco de dados (Nao vinculados a um Voo)
void BancoDeDados::mostrarDadosPiloto() { //Dados Pilotos
    cout << "<=========Lista Pilotos=========>\n";
    for(size_t i = 0; i < bancoDeDados_Pilotos.size(); i++) {
        cout << i + 1 << " - ";
        bancoDeDados_Pilotos[i].mostrarDados();
    }
}

void BancoDeDados::mostrarDadosPassageiro() { //Dados Passageiros
    cout << "<=========Lista Passageiros=========>\n";
    for(size_t i = 0; i < bancoDeDados_Passageiros.size(); i++) {
        cout << i + 1 << " - ";
        bancoDeDados_Passageiros[i].mostrarDados();
    }
}

void BancoDeDados::mostrarDadosAeronave() { //Dados Aeronaves
    cout << "<=========Lista Aeronaves=========>\n";
    for(size_t i = 0; i < bancoDeDados_Aeronaves.size(); i++) {
        cout << i + 1 << " - ";
        bancoDeDados_Aeronaves[i].mostrarDados();
    }
}

void BancoDeDados::mostrarDadosVoo() {
    if(bancoDeDados_Voos.size() == 0) {
        cout << "Nao ha Voos!\n";
        return;
    }
    cout << "<============Lista Voos =============>\n";
     for(size_t i = 0; i < bancoDeDados_Voos.size(); i++) {
        cout << i + 1 << " - ";
        bancoDeDados_Voos[i].mostrarDados();
    }
}

//Listar passageiros Voo
void BancoDeDados::mostrarDadosVooP() {
    cout << "<============Lista Voos =============>";
     for(size_t i = 0; i < bancoDeDados_Voos.size(); i++) {
        cout << i + 1 << " - ";
        cout << "Codigo do Voo - \n" << bancoDeDados_Voos[i].getCodigo();
    }
}

void Voos::mostrarDadosPassageiros() const{
    for(size_t i = 0; i < passageiros.size(); i++){
        cout << i + 1 << " - ";
        passageiros[i].mostrarDados();
    }
}

void listarPassageirosVoo(BancoDeDados& b) {
    cout << "Digite o Numero do Voo que deseja ver os passageiros: \n";
    b.mostrarDadosVooP();
    int opc = retornaInteiro();
    if(opc > b.getSizeVoos())
        opc = b.getSizeVoos(); 
    const Voos& voo = b.getVoo(opc -1);

    // Exibe os passageiros desse voo
    if(voo.getSizePassageiros() == 0)
        cout << "Esse Voo nao possui passageiros!\n";
    else
        voo.mostrarDadosPassageiros();
}

//Verificacoes (input)
bool possuiNumeral(const string& str) { //Verificacao de numerais
     for (char c : str) 
        if (isdigit(c)) return true;
    return false;
}

bool possuiLetra(const string& str) { // Verificacao de letras
    for (char c : str) 
        if (isalpha(c)) return true;
    return false;
}

int retornaInteiro() {
    string entrada;

    while(true) {
        getline(cin, entrada);
        if(!entrada.empty() && !possuiLetra(entrada))
            break;
        else cout << "Entrada invalida, Digite novamente! (Apenas numeros)\n";
    }
    return stoi(entrada);
}

double retornaDouble() {
    string entrada;

      while(true) {
        getline(cin, entrada);
        if(!entrada.empty() && !possuiLetra(entrada))
            break;
        else 
            cout << "Entrada invalida, Digite novamente! (Apenas numeros)\n";
    }
    return stod(entrada);
}

string retornaString() {
    string entrada;

    while(true) {
        getline(cin, entrada);
        if(!entrada.empty() && !possuiNumeral(entrada))
            break;  
        else 
            cout << "Entrada invalida, Digite novamente! (Apenas Letras)\n";
    }
    return entrada;
}

char retornaChar() {
    string entrada;

    while (true) {
        getline(cin, entrada);
        if (!entrada.empty() && entrada.length() == 1 && !possuiNumeral(entrada)) 
            return entrada[0];
         else 
            cout << "Entrada invalida! Digite apenas um caractere.\n";
    }
}

//Embarcar passageiro Voo
void embarcarPassageiroVoo(BancoDeDados &b) {
    if(b.getSizeVoos() == 0) {
        cout << "Não a Voos disponiveis!\n";
        return;
    }

    b.mostrarDadosVoo();
    cout << "Digite o numero do Voo no qual voce quer adicionar um passageiro: ";
    int voo = retornaInteiro();
    if(voo > b.getSizeVoos())
        voo = b.getSizeVoos();

    if(b.getSizePassageiros() == 0) {
        cout << "Nao ha passageiros cadastrados!\n";
        return;
    }
    cout << "Digite o numero do passageiro que deseja vincular ao Voo: ";
    b.mostrarDadosPassageiro();
    int pas = retornaInteiro();
    if(pas > b.getSizePassageiros())
        pas = b.getSizePassageiros();
    Passageiro passageiro = b.getPassageiro(pas-1);
    // Corrigido: acessar o voo por referência para adicionar o passageiro corretamente
    Voos& adVoo = b.getVooRef(voo-1);
    adVoo.adicionarPassageiro(passageiro);
    cout << "Passageiro vinculado com sucesso\n";
}

// Implementação da Serialização
string Aeronave::serializar() const {
    stringstream ss;
    ss << codigo << "," << modelo << "," << capacidade << "," << velocidadeMed << "," << autonomiaVoo;
    return ss.str();
}

string Piloto::serializar() const {
    stringstream ss;
    ss << nome << "," << matricula << "," << breve << "," << horasVoo;
    return ss.str();
}

string Passageiro::serializar() const {
    stringstream ss;
    ss << nome << "," << cpf << "," << numeroBilhete;
    return ss.str();
}

string Voos::serializar() const {
    stringstream ss;
    ss << codigo << "," << origem << "," << destino << "," << distancia << "," << horaSaida << "," << tempoEstimado
       << "," << aeronaveVoo.serializar(); // Simplificado para incluir dados da aeronave
    return ss.str();
}


// Implementação para Salvar Dados
void BancoDeDados::salvarDados() {
    ofstream arquivo;

    // Salvar Aeronaves
    arquivo.open("aeronaves.csv");
    if (arquivo.is_open()) {
        arquivo << "Codigo,Modelo,Capacidade,VelocidadeMedia,Autonomia\n";
        for (size_t i = 0; i < bancoDeDados_Aeronaves.size(); ++i) {
            arquivo << bancoDeDados_Aeronaves[i].serializar() << "\n";
        }
        arquivo.close();
    } else {
        cout << "Erro ao abrir o arquivo aeronaves.csv" << endl;
    }

    // Salvar Pilotos
    arquivo.open("pilotos.csv");
    if (arquivo.is_open()) {
        arquivo << "Nome,Matricula,Breve,HorasVoo\n";
        for (size_t i = 0; i < bancoDeDados_Pilotos.size(); ++i) {
            arquivo << bancoDeDados_Pilotos[i].serializar() << "\n";
        }
        arquivo.close();
    } else {
        cout << "Erro ao abrir o arquivo pilotos.csv" << endl;
    }

    // Salvar Passageiros
    arquivo.open("passageiros.csv");
    if (arquivo.is_open()) {
        arquivo << "Nome,CPF,NumeroBilhete\n";
        for (size_t i = 0; i < bancoDeDados_Passageiros.size(); ++i) {
            arquivo << bancoDeDados_Passageiros[i].serializar() << "\n";
        }
        arquivo.close();
    } else {
        cout << "Erro ao abrir o arquivo passageiros.csv" << endl;
    }

    // Salvar Voos
    arquivo.open("voos.csv");
    if (arquivo.is_open()) {
        arquivo << "Codigo,Origem,Destino,Distancia,HoraSaida,TempoEstimado,Aeronave\n";
        for (size_t i = 0; i < bancoDeDados_Voos.size(); ++i) {
            arquivo << bancoDeDados_Voos[i].serializar() << "\n";
        }
        arquivo.close();
    } else {
        cout << "Erro ao abrir o arquivo voos.csv" << endl;
    }
}

// Implementação dos Relatórios e Estatísticas
void gerarRelatoriosEstatisticas(const BancoDeDados& b) {
    int opc = 0;
    do {
        cout << "\n======= RELATORIOS E ESTATISTICAS =======\n"
             << "1. Numero total de voos cadastrados\n"
             << "2. Media de passageiros por voo\n"
             << "3. Lista de aeronaves mais utilizadas\n"
             << "4. Voltar ao menu principal\n"
             << "=========================================\n"
             << "Escolha uma opcao: ";
        opc = retornaInteiro();

        switch (opc) {
            case 1:
                relatorioTotalVoos(b);
                break;
            case 2:
                relatorioMediaPassageiros(b);
                break;
            case 3:
                relatorioAeronavesMaisUtilizadas(b);
                break;
            case 4:
                cout << "Voltando ao menu principal...\n";
                break;
            default:
                cout << "Opcao invalida! Tente novamente.\n";
                break;
        }
    } while (opc != 4);
}

void relatorioTotalVoos(const BancoDeDados& b) {
    cout << "\n--- Relatorio: Total de Voos ---\n";
    cout << "Numero total de voos cadastrados: " << b.getSizeVoos() << endl;
    cout << "----------------------------------\n";
}

void relatorioMediaPassageiros(const BancoDeDados& b) {
    cout << "\n--- Relatorio: Media de Passageiros por Voo ---\n";
    const vector<Voos>& voos = b.getVoos();
    if (voos.empty()) {
        cout << "Nenhum voo cadastrado para calcular a media." << endl;
        return;
    }

    int totalPassageiros = 0;
    for (size_t i = 0; i < voos.size(); ++i) {
        totalPassageiros += voos[i].getSizePassageiros();
    }

    double media = static_cast<double>(totalPassageiros) / voos.size();
    cout << "Media de passageiros por voo: " << fixed << setprecision(2) << media << endl;
    cout << "----------------------------------------------\n";
}

void relatorioAeronavesMaisUtilizadas(const BancoDeDados& b) {
    cout << "\n--- Relatorio: Aeronaves Mais Utilizadas ---\n";
    const vector<Voos>& voos = b.getVoos();
    if (voos.empty()) {
        cout << "Nenhum voo cadastrado." << endl;
        return;
    }

    map<string, int> contagemAeronaves;
    for (size_t i = 0; i < voos.size(); ++i) {
        contagemAeronaves[voos[i].getAeronaveVoo().getModelo()]++;
    }

    cout << "Uso de cada modelo de aeronave:\n";
    for (map<string, int>::const_iterator it = contagemAeronaves.begin(); it != contagemAeronaves.end(); ++it) {
        cout << " - Modelo: " << it->first << ", Vezes utilizada: " << it->second << endl;
    }
    cout << "-------------------------------------------\n";
}