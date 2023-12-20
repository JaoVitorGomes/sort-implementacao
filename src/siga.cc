#include <cassert>
#include <sstream>
#include <string>

using namespace std;

#include "config.h"
#include "siga.h"

namespace Siga
{

    Siga::Siga()
    {
        this->arquivo_nome = "";
        this->n_estudantes = 0;
    }

    void Siga::InitDatabase(string database_name)
    {

        this->arquivo_nome = INPUT_DATA_DIR + database_name + ".bin";
        cout << "teste: " << INPUT_DATA_DIR << endl;
        // Obter numero de estudantes no arquivo
        // Se o arquivo não existir, o numero de estudantes é zero
        // Se o arquivo existir, o numero de estudantes é o numero de registros no arquivo
        //  o numero de estudantes é armazenado no atributo n_estudantes

        this->file_stream = fstream(this->arquivo_nome, ios::in | ios::out | ios::binary);
        cout << "SIGA: Inicializado com sucesso" << endl;

        // arquivo nao existe ainda
        if (!this->file_stream.is_open())
        {

            // cria um arquivo vazio
            ofstream out(arquivo_nome, ios::binary);
            out.close();
            // reabre para leitura e escrita
            this->file_stream = fstream(this->arquivo_nome, ios::in | ios::out | ios::binary);
            if (!this->file_stream.is_open())
            {
                cout << "SIGA: Erro ao criar arquivo de dados de estudante" << endl;
                return;
            }
        }

        cout << "SIGA: Opened file " << this->arquivo_nome << endl;
        cout << "SIGA: Arquivo de dados de estudante aberto com sucesso" << endl;
        this->file_stream.seekg(0, this->file_stream.end);
        int length = this->file_stream.tellg();
        this->file_stream.seekg(0, this->file_stream.beg);
        this->n_estudantes = length / sizeof(Estudante);
        cout << this->n_estudantes << " registros de estudantes" << endl;

        if (this->n_estudantes == 0)
        {
            // Abre o arquivo csv para inicializar o arquivo binario
            cout << "SIGA: importando dados de " << database_name << ".csv" << endl;
            this->LerCSV(database_name);
            cout << "SIGA: " << this->n_estudantes << " estudantes importados" << endl;
        }

        
    }

    void Siga::LerCSV(string arquivo_csv)
    {
   
        string arquivo_csv_path = INPUT_DATA_DIR + arquivo_csv + ".csv";
        ifstream csv_file;
        csv_file.open(arquivo_csv_path);
        if (!csv_file.is_open())
        {
            cout << "Erro ao abrir arquivo CSV" << endl;
            return;
        }
        // Ler cabeçalho
        string line;

        this->n_estudantes = 0;

        // header line
        // matricula,nome,ano_ingresso,semestre_ingresso,curso,ira
        getline(csv_file, line);

        // TODO: Altere esse codigo para ler os campos extras do arquivo CSV de entrada.
        // Para cada linha de dados
        while (getline(csv_file, line))
        {
            // Ler um estudante do arquivo CSV
            Estudante est;
            stringstream ss(line);
            string token;
            getline(ss, token, ','); // le matricula
            est.TrocarMatricula(stoi(token));
            getline(ss, token, ','); // le nome
            est.TrocarNome(token.c_str());
            getline(ss, token, ','); // ano_ingresso
            est.TrocarAnoIngresso(stoi(token));
            getline(ss, token);//semestre_ingresso
            est.TrocarSemestreIngresso(stoi(token));
            getline(ss, token);//curso
            est.TrocarCurso(stoi(token));
            getline(ss, token); // ira
            est.TrocarIRA(stof(token));

            this->EscrevaEstudante(this->n_estudantes, est);
            this->n_estudantes++;
        }
        // Fim-Para
        // Fechar arquivo CSV
        csv_file.close();

    }

    int Siga::PesquisaPorMatricula(int matricula)
    {

    Estudante estudante;
    string line;

    this->file_stream.seekg(0, ios::beg); 
    cout << "valores: " << n_estudantes << endl;
    for(int i = 0; i < this->n_estudantes; i++){
        this->LeiaEstudante(i, estudante);
        if(estudante.ObterMatricula() == matricula){
            cout << "entrou " << i  << endl;
            return i;
        }
    }

    this->file_stream.seekg(0, ios::end); 
    return -1;
        
    }

    void Siga::AdicionaEstudante(Estudante est)
    {

    int verify = this->PesquisaPorMatricula(est.ObterMatricula());

    if(verify == -1){
        this->file_stream.seekg(0, ios::end); 
        this->EscrevaEstudante(n_estudantes, est);
        this->n_estudantes++;
    }

    return;    
    }

    Estudante Siga::ObterEstudante(int idx)
    {

    Estudante est;
    this->file_stream.seekg(0, ios::beg); 
    this->file_stream.seekg(idx,ios::cur);
    this->LeiaEstudante(idx,est);

    return est;

    }

    void Siga::SalvaCSV(string arquivo_csv, std::vector<Estudante> &estudantes)
    {
        string arquivo_csv_path = INPUT_DATA_DIR + arquivo_csv;
        
        ofstream csv_file;
        csv_file.open(arquivo_csv_path);
        if (!csv_file.is_open())
        {
            cout << "Erro ao abrir arquivo CSV" << endl;
            return;
        }
        csv_file << "matricula,nome,ano_ingresso,semestre_ingresso,curso,ira" << endl;
        for (int i = 0; i < estudantes.size(); i++)
        {
            csv_file << estudantes[i].ObterMatricula() << ","
                     << estudantes[i].ObterNome() << ","
                     << estudantes[i].ObterAnoIngresso() << ","
                     << estudantes[i].ObterSemestreIngresso() << ","
                     << estudantes[i].ObterCurso() << ","
                     << estudantes[i].ObterIRA() << endl;
        }

        csv_file.close();
    }

    void Siga::AlteraCadastroEstudante(int idx, Estudante est)
    {
        
    Estudante estudante;
    this->file_stream.seekg(0, ios::beg);
    this->file_stream.seekg(idx,ios::cur);
    this->EscrevaEstudante(idx, est);
    return;
        
    }

    Siga::~Siga()
    {
        this->file_stream.close();
    }

    int Siga::ObterNumeroEstudantes()
    {
        return this->n_estudantes;
    }

    // Le um objeto estudante no arquivo binario
    void Siga::LeiaEstudante(int idx, Estudante &est)
    {
        this->file_stream.seekg(idx * sizeof(Estudante), this->file_stream.beg);
        this->file_stream.read((char *)&est, sizeof(Estudante));
    }

    // Escreve um objeto estudante no arquivo binario
    void Siga::EscrevaEstudante(int idx, Estudante est)
    {
        this->file_stream.seekp(idx * sizeof(Estudante), this->file_stream.beg);
        this->file_stream.write((char *)&est, sizeof(Estudante));
    }

    // Retorna uma vetor de estudantes
    void Siga::ExtraiaEstudantes(std::vector<int> idxs, std::vector<Estudante> &list)
    {
        list.resize(idxs.size());
        for (int i = 0; i < idxs.size(); i++)
        {
            this->LeiaEstudante(idxs[i], list[i]);
        }
    }

}