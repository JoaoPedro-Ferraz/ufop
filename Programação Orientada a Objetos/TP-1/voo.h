#ifndef VOO_H
#define VOO_H

#include <vector>
#include <string>
#include <sstream>
using namespace std;

#include <fstream> // Para manipular os arquivos
#include <map> // Adicionado para estatísticas

//Classes
class Aeronave { //Classe para Aeronaves
    private:
        int codigo;
        string modelo;
        int capacidade;
        float velocidadeMed;
        float autonomiaVoo;
    public:
        Aeronave() : codigo(0), modelo(""), capacidade(1), velocidadeMed(0), autonomiaVoo(0) {}
        Aeronave(int codigo, string modelo, int capacidade, float velocidadeMed, float autonomiaVoo) {
        this -> codigo = codigo;
        this -> modelo = modelo;
        this -> capacidade = capacidade;
        this -> velocidadeMed = velocidadeMed;
        this -> autonomiaVoo = autonomiaVoo;
    }
        void mostrarDados() const;
        int getCapacidade() const {
            return capacidade;
        }
        int getVelocidade() const {
            return velocidadeMed;
        }
        string getModelo() const { // Adicionado para estatísticas
            return modelo;    
        }
        string serializar () const; // Para salvar dados
    };
    
class Pessoa {//Classe generalizada Pessoa
    protected: 
        string nome;
    public:
        Pessoa() : nome("0") {}
        Pessoa(string nome) {
            this -> nome = nome;
        }
        void mostrarDados() const;
    };

//Classes herdadas de pessoa Piloto | Passageiro
class Piloto    : public Pessoa {
    private:
        int matricula;
        string breve;
        double horasVoo;
    public:
        Piloto() : matricula(0), breve("0"), horasVoo(0) {}
        Piloto(string nome, int matricula, string breve, double horasVoo) : Pessoa(nome) {
            this -> matricula = matricula;
            this -> breve = breve;
            this -> horasVoo = horasVoo;
        }
        void mostrarDados() const;
        string serializar() const; // Salvar os dados
};

class Passageiro : public Pessoa {
    private: 
        int cpf;
        int numeroBilhete;
    public:
        Passageiro () : cpf(0), numeroBilhete(0) {}
        Passageiro(string nome, int cpf, int numeroBilhete) : Pessoa(nome) {
            this -> cpf = cpf;
            this -> numeroBilhete = numeroBilhete;
        }
        void mostrarDados() const;
        string serializar() const; // Salvar os dados
};

//Voos
class Voos {
    private:
        int codigo;
        string origem;
        string destino;
        double distancia;
        double horaSaida;
        double tempoEstimado;
        Aeronave aeronaveVoo;
        Piloto comandante;
        Piloto primeiroOficial;
        vector<Passageiro> passageiros;
    public:
        Voos () : codigo(0), origem("0"), destino("0"), distancia(0), horaSaida(0), tempoEstimado(0) {}
        Voos(int codigo, string origem, string destino, double distancia, double horaSaida, double tempoEstimado) {
            this -> codigo = codigo;
            this -> origem = origem;
            this -> destino = destino;
            this -> distancia = distancia;
            this -> horaSaida = horaSaida;
            this -> tempoEstimado = tempoEstimado;
        }
        void setAeronave(const Aeronave& a) {
            aeronaveVoo = a;
        }
        void setComandante(const Piloto& p) {
            comandante = p;
        }
        void setPrimeiroOficial(const Piloto& p) {
            primeiroOficial = p;
        }
        void adicionarPassageiro(const Passageiro& p) {
            passageiros.push_back(p);
        }
        int getSizePassageiros() const {
            return passageiros.size();  
        }
        int getCodigo() const{
            return codigo;
        }
        const Aeronave& getAeronaveVoo() const { //Para as estatisticas
            return aeronaveVoo;    
        }
        void mostrarDados() const;
        void mostrarDadosPassageiros() const;
        string serializar() const; // Adicionado para salvar dados
};

//Banco de dados(Salva passageiros, pilotos e pessoas que nao estao assoaciadas a um voo)
class BancoDeDados {
    private: 
        vector<Piloto>bancoDeDados_Pilotos;
        vector<Passageiro>bancoDeDados_Passageiros;
        vector<Aeronave>bancoDeDados_Aeronaves;
        vector<Voos>bancoDeDados_Voos;
    public:
        void adicionarPiloto(const Piloto& p) {
            bancoDeDados_Pilotos.push_back(p);
        }
        void adicionarPassageiro(const Passageiro& p) {
            bancoDeDados_Passageiros.push_back(p);
        }
        void adicionarAeronave(const Aeronave& a) {
            bancoDeDados_Aeronaves.push_back(a);
        }
        void adicionarVoo(const Voos& v) {
            bancoDeDados_Voos.push_back(v);
        }
        //Impressoes
        void mostrarDadosPiloto();
        void mostrarDadosPassageiro();
        void mostrarDadosAeronave();
        void mostrarDadosVoo();
        void mostrarDadosVooP();

        //Coleta de dados
        int getSizeAeronave() const{
            return bancoDeDados_Aeronaves.size();
        }
        int getSizePilotos() const{
            return bancoDeDados_Pilotos.size();
        }
        int getSizePassageiros() const{
            return bancoDeDados_Passageiros.size();
        }
        int getSizeVoos() const{
            return bancoDeDados_Voos.size();
        }
        const Voos getVoo(int dx) const{
            return bancoDeDados_Voos.at(dx);
        }
        Voos& getVooRef(int idx) {
            return bancoDeDados_Voos.at(idx);
        }
        Aeronave getAeronave(int opc) {
            Aeronave nova = bancoDeDados_Aeronaves[opc];
            bancoDeDados_Aeronaves.erase(bancoDeDados_Aeronaves.begin() + opc);
            return nova;
        }
        Piloto getPiloto(int opc) {
            Piloto novo = bancoDeDados_Pilotos[opc];
            bancoDeDados_Pilotos.erase(bancoDeDados_Pilotos.begin() + opc);
            return novo;
        }
        Passageiro getPassageiro(int opc) {
            Passageiro novo = bancoDeDados_Passageiros[opc];
            bancoDeDados_Passageiros.erase(bancoDeDados_Passageiros.begin() + opc);
            return novo;
        }
        const vector<Voos>& getVoos() const { // Adicionado para estatíticas
            return bancoDeDados_Voos;
        }

        //Persistência de dados
        void salvarDados();
};



//Menu
void menu(BancoDeDados&);
void printMenu();

//Cadastros 
Aeronave cadastrarAeronave(BancoDeDados&);
Piloto cadastrarPiloto(BancoDeDados&);
Passageiro cadastrarPassageiro(BancoDeDados&);
Voos cadastrarVoo(BancoDeDados&);

//Verificacoes
bool possuiNumeral(const string&);
bool possuiLetra(const string&);

//Entrada de dados
int retornaInteiro();
double retornaDouble();
string retornaString();
char retornaChar();

//Impressoes
void listarPassageirosVoo(BancoDeDados&);

//Embarcar Passageiros
void embarcarPassageiroVoo(BancoDeDados &);

// Relatórios e Estatísticas
void gerarRelatoriosEstatisticas(const BancoDeDados& b);
void relatorioTotalVoos(const BancoDeDados& b);
void relatorioMediaPassageiros(const BancoDeDados& b);
void relatorioAeronavesMaisUtilizadas(const BancoDeDados& b);

#endif //VOO_H