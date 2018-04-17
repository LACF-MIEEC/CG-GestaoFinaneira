#ifndef DB_MANAGER_H
#define DB_MANAGER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>
#include <QDateTime>
#include <QVector>
#include <QString>

//---------------------------------------------------------------
//ESTRUTURAS
//---------------------------------------------------------------
struct GASTO {
  int ID_Gasto;
  QDate Data_Gasto;
  int Area;
  float Valor;
  int E_Fatura;
  QString Descricao;
  int ID_Pessoa;
} ;

struct ORCAMENTO{
    float Valor;
    int Ano;
    int Area;
};

struct PESSOA{
    int ID_Pessoa;
    QString Nome;
    QString Grau;
};

class DB_Manager
{
public:

    //constructor
    DB_Manager(const QString& path);

    //destructor
    ~DB_Manager();

    bool isOpen() const;


    //---------------------------------------------------------------
    //ADD
    //---------------------------------------------------------------
    /*!
     * \brief Cria Tabelas da Base de Dados
     * \return True - Tabelas criadas, False - Tabelas não criadas
     */
    bool createTables();

    //---------------------------------------------------------------
    //ADD
    //---------------------------------------------------------------

    /*!
     * \brief Adiciona novo orçamento
     * \param Area - Área do gasto (alimentação, vestuário, deslocações, lazer e outros)
     * \param Valor - Valor do orçamento anual
     * \param Ano - Ano do orçamento
     * \return True - orçamento Adicionado, False - orçamento não adicionado
     */
    bool addOrcamento(int , float , QDate);


    /*!
     * \brief Adicionar novo Gasto
     * \param Data_Gasto - Data e hora em que o gasto ocorreu
     * \param Area - Área do gasto (alimentação, vestuário, deslocações, lazer e outros)
     * \param Valor - Valor do gasto
     * \param Descricao - Breve descrição acerca do gasto
     * \param ID_Pessoa - ID correspondente à pessoa que efetuou o gasto
     * \param E_Fatura - (opcional) ID correspondente ao Efatura
     * \return ID atribuido ao gasto criado, em caso de erro retorna o valor 0.
     */
    int addGasto(QDate, int, float, const QString&, int, int);

    /*!
     * \brief Adiciona pessoa à Base de Dados.
     * \param Nome - Nome da Pessoa.
     * \param Grau - Grau de parentesco da pessoa
     * \return ID atribuido à pessoa criada, em caso de erro retorna o valor 0.
     */
    int addPessoa(const QString&, const QString&);



    //---------------------------------------------------------------
    //UPDATE
    //---------------------------------------------------------------

    /*!
     * \brief Actualiza as informações acerca de um gasto já feito
     * \param ID_Gasto - ID corresponde ao gasto feito
     * \param Data_Gasto - Data e hora em que o gasto ocorreu
     * \param Area - Área do gasto (alimentação, vestuário, deslocações, lazer e outros)
     * \param Valor - Valor do gasto
     * \param Descricao - Breve descrição acerca do gasto
     * \param ID_Pessoa - ID correspondente à pessoa que efetuou o gasto
     * \param E_Fatura - (opcional) ID correspondente ao Efatura
     * \return True - gasto atualizado, False - gasto não atualizado
     */
    bool updateGasto(int,QDate ,int ,float,const QString& ,int, int);

    /*!
     * \brief Atualiza valor de orçamento
     * \param Area - Área do gasto (alimentação, vestuário, deslocações, lazer e outros)
     * \param Valor - Valor do orçamento anual
     * \param Ano - Ano do orçamento
     * \return True - orçamento atualizado, False - orçamento não atualizado
     */
    bool updateOrcamento(int , float, QDate);



    //---------------------------------------------------------------
    //GET
    //---------------------------------------------------------------



    /*!
     * \brief Devolve todas as pessoas
     * \return
     */
    QVector<PESSOA*>* getPessoas();

    /*!
     * \brief Devolve todos os orçamentos registados
     * \return
     */
    QVector<ORCAMENTO*>* getOrcamentos();


    //---------------------------------------------------------------
    //GET BY ID
    //---------------------------------------------------------------

    /*!
     * \brief Devolve todos os gastos feitos
     * \return
     */
    QVector<GASTO*>* getGastos();


    /*!
     * \brief Devolve todos os gastos efetuados por determinada pessoa
     * \return
     */
    QVector<GASTO*> *getGastosByPessoa(int);

    QVector<GASTO*>* getGastosByID(int);

    QVector<GASTO*>* getGastosByMes(QDate);

    QVector<GASTO*>* getGastosByAno(QDate);

    QVector<GASTO*>* getGastosByFatura(int);

    QVector<GASTO*>* getGastosByData(QDate);

    QVector<GASTO*>* getGastosByArea(int);

    QVector<GASTO*>* getGastosByAreaByData(int, QDate );

    QVector<GASTO*>* getGastosByPessoaByAno(int,QDate);

    QVector<GASTO*>* getGastosByPessoaByMes(int ,QDate );

    QVector<GASTO*>* getGastosByPessoaByData(int , QDate);

    QVector<GASTO*>* getGastosByAnoByArea(QDate, int);

    QVector<GASTO*>* getGastosByPessoaByArea(int,int);

    QVector<GASTO*>* getGastosByMesByArea(QDate, int);

    QVector<GASTO*>* getGastosByPessoaByAreaByAno(int,int,QDate);

    QVector<GASTO*>* getGastosByPessoaByAreaByMes(int,int,QDate);

    QVector<GASTO*>* getGastosByPessoaByAreaByData(int,int,QDate);




    QVector<GASTO*>* getGastosByAreaBetweenData(int ,QDate,QDate);

    QVector<GASTO*>* getGastosBetweenData(QDate ,QDate);

    float getOrcamentoByAreaByAno(int, QDate );

    float getOrcamentoTotalByAno(QDate);



    //TOTAIS

    float getTotalGastos();

    float getTotalGastosByMes(QDate);

    float getTotalGastosByMesByArea(QDate, int);

    float getTotalGastosByAno(QDate);

    float getTotalGastosByAnoByArea(QDate,int);

    float getTotalGastosByPessoa(int);

    float getTotalGastosByPessoaByArea(int,int);

    float getTotalGastosByPessoaByAreaByAno(int,int,QDate);

    float getTotalGastosByPessoaByAno(int , QDate);

    float getTotalGastosByPessoaByAreaByMes(int, int, QDate );

    float getTotalGastosByPessoaByMes(int, QDate);

    float getTotalGastosByData(QDate);

    float getTotalGastosByPessoaByData(int,QDate);

    float getTotalGastosByArea(int);

    float getTotalGastosByAreaByData(int,QDate);

    float getTotalGastosByPessoaByAreaByData(int,int,QDate);

    float getTotalGastosFatura(int);








    float getTotalBy(int,int,QDate,int);

    QVector<GASTO *> *getBy(int,int,QDate,int);

    //---------------------------------------------------------------
    //DELETE
    //---------------------------------------------------------------
    /*!
     * \brief Elimina Pessoa com o ID pretendido
     * \return True - Pessoa eliminada, False - Pessoa não eliminada
     */
    bool deletePessoa(int);

    /*!
     * \brief Elimina gasto com o ID pretendido
     * \return True - Gasto eliminado, False - Gasto não eliminado
     */
    bool deleteGasto(int);

    /*!
     * \brief Elimina orçamento com o ano e Area pretendidos
     * \return True - Orçamento eliminado, False - Orçamento não eliminado
     */
    bool deleteOrcamento(QDate, int);



    //---------------------------------------------------------------
    //OUTROS
    //---------------------------------------------------------------

    bool removeAll();

    bool clearAll();

    //bool deleteFromDB();

private:
    QSqlDatabase m_db;
};

#endif // DB_MANAGER_H
