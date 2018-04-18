#include "dbmanager.h"

struct ORCAMENTO;
struct GASTO;
struct PESSOA;



DB_Manager::DB_Manager(const QString &path)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);

    if (!m_db.open())
    {
        qDebug() << "Error: connection with database fail";
    }
    else
    {
        qDebug() << "Database: connection ok";
    }
}

DB_Manager::~DB_Manager()
{
    if (m_db.isOpen())
    {
        m_db.close();
    }
}

bool DB_Manager::isOpen() const
{
    return m_db.isOpen();
}
//---------------------------------------------------------------
//CREATE TABLES
//---------------------------------------------------------------
bool DB_Manager::createTables()
{
    //********************************************************************************
    //CRIA TABELA GASTO
    //********************************************************************************
    QSqlQuery query;
    query.prepare("CREATE TABLE GASTO("
                  "ID_Gasto INTEGER PRIMARY KEY AUTOINCREMENT,"
                  "Data_Gasto REAL," //JULIAN DAY NUMBER
                  "Area INT,"
                  "Valor FLOAT,"
                  "E_Fatura INT,"
                  "Descricao TEXT,"
                  "ID_Pessoa INT ,"
                  "FOREIGN KEY (ID_Pessoa) REFERENCES PESSOA(ID_Pessoa)"
                  ");");

    if (!query.exec())
    {
        qDebug() << "Couldn't create the table 'FOTO': one might already exist.";
        return false;
    }

    //********************************************************************************
    //CRIA TABELA PESSOA
    //********************************************************************************
    query.prepare("CREATE TABLE PESSOA("
                  "ID_Pessoa INTEGER PRIMARY KEY AUTOINCREMENT,"
                  "Nome_Pessoa TEXT,"
                  "Grau TEXT"
                  ");");

    if (!query.exec())
    {
        qDebug() << "Couldn't create the table 'ALBUM': one might already exist.";
        return false;
    }

    //********************************************************************************
    //CRIA TABELA ORCAMENTO
    //********************************************************************************

    query.prepare("CREATE TABLE ORCAMENTO("
                  "Area INT,"
                  "Ano INT,"
                  "Valor REAL"
                  ");");
    if (!query.exec())
    {
        qDebug() << "Couldn't create the table 'PAGINA': one might already exist.";
        return false;
    }




    return true;
}


//---------------------------------------------------------------
//ADD
//---------------------------------------------------------------
int DB_Manager::addPessoa(const QString& Nome, const QString& Grau){


        QSqlQuery queryAdd;
        queryAdd.prepare("INSERT INTO PESSOA (Nome_Pessoa, Grau) VALUES (:nome, :grau)");
        queryAdd.bindValue(":nome", Nome);
        queryAdd.bindValue(":grau", Grau);

        if(!queryAdd.exec())
        {
            qDebug() << "add Pessoa failed: " << queryAdd.lastError();
            return 0;
        }

        return queryAdd.lastInsertId().toInt();
}

int DB_Manager::addGasto(QDate Data_Gasto,int Area,float Valor,const QString& Descricao, int ID_Pessoa, int E_Fatura ){


    QSqlQuery queryAdd;
    queryAdd.prepare("INSERT INTO GASTO (Data_Gasto, Area, Valor, Descricao, ID_Pessoa, E_Fatura) VALUES (:data,:area,:valor,:desc,:id_pessoa,:e_fatura)");
    queryAdd.bindValue(":data", Data_Gasto.toJulianDay());
    queryAdd.bindValue(":area", Area);
    queryAdd.bindValue(":valor", Valor);
    queryAdd.bindValue(":desc", Descricao);
    queryAdd.bindValue(":id_pessoa", ID_Pessoa);
    queryAdd.bindValue(":e_fatura", E_Fatura);

    if(!queryAdd.exec())
    {
        qDebug() << "add Album failed: " << queryAdd.lastError();
        return 0;
    }

   return queryAdd.lastInsertId().toInt();
}

bool DB_Manager::addOrcamento(int Area,float Valor,QDate Ano)
{
    QSqlQuery queryAdd;
    queryAdd.prepare("INSERT INTO ORCAMENTO (Area, Ano, Valor) VALUES (:area,:ano, :valor);");
    queryAdd.bindValue(":area", Area);
    queryAdd.bindValue(":ano", Ano.year());
    queryAdd.bindValue(":valor", Valor);

    if(!queryAdd.exec())
    {
        qDebug() << "add Atachment failed: " << queryAdd.lastError();
        return false;
    }

    return true;
}


//---------------------------------------------------------------
//UPDATE
//---------------------------------------------------------------
bool DB_Manager::updateGasto(int ID_Gasto, QDate Data_Gasto,int Area,float Valor,const QString& Descricao, int ID_Pessoa, int E_Fatura ){


        QSqlQuery queryUpdate;
        queryUpdate.prepare("UPDATE GASTO SET Data_Gasto=:data_gasto, Area=:area, Valor=:valor, Descricao=:desc, ID_Pessoa=:id_pessoa, E_Fatura=:e_fatura WHERE ID_Gasto= :id_gasto;");
        queryUpdate.bindValue(":data_gasto", Data_Gasto.toJulianDay());
        queryUpdate.bindValue(":area", Area);
        queryUpdate.bindValue(":valor", Valor);
        queryUpdate.bindValue(":desc", Descricao);
        queryUpdate.bindValue(":id_pessoa", ID_Pessoa);
        queryUpdate.bindValue(":e_fatura", E_Fatura);
        queryUpdate.bindValue(":id_gasto", ID_Gasto);


        if(!queryUpdate.exec())
        {
            qDebug() << "add person failed: " << queryUpdate.lastError();
            return 0;
        }


        /*
        Função deve receber como parametro uma tabela de pessoas que estão associadas à foto e
        inserir na tabela tantas linhas quantas pessoas houver

        for(){

        }*/
        return true;
}

bool DB_Manager::updateOrcamento(int Area,float Valor,QDate Ano){

    QSqlQuery queryUpdate;
    queryUpdate.prepare("UPDATE ORCAMENTO SET Valor = :valor WHERE (Ano = :ano) AND (Area = :area); ");
    queryUpdate.bindValue(":area", Area);
    queryUpdate.bindValue(":ano", Ano.year());
    queryUpdate.bindValue(":valor", Valor);

    if(!queryUpdate.exec())
    {
        qDebug() << "update album failed: " << queryUpdate.lastError();
        return false;
    }

    return true;
}


//---------------------------------------------------------------
//GET
//---------------------------------------------------------------

QVector<PESSOA*>* DB_Manager::getPessoas(){

    QVector<PESSOA*> *pessoas = new QVector<PESSOA*>();
    PESSOA *Atributos;
    QSqlQuery query;
    query.prepare("SELECT * FROM PESSOA;");
    if(!query.exec())
    {
        qDebug() << "get Pessoas failed: " << query.lastError();
        return false;
    }
    while (query.next())
    {
        Atributos=new PESSOA;
        Atributos->Nome=query.value("Nome_Pessoa").toString();
        Atributos->Grau=query.value("Grau").toString();
        Atributos->ID_Pessoa=query.value("ID_Pessoa").toInt();
        pessoas->append(Atributos);
    }
    return pessoas;
}

QVector<ORCAMENTO*>* DB_Manager::getOrcamentos(){

    QVector<ORCAMENTO*> *orcamentos = new QVector<ORCAMENTO*>();
    ORCAMENTO *Atributos;
   QSqlQuery query;
   query.prepare("SELECT * FROM ORCAMENTO;");
   if(!query.exec())
   {
       qDebug() << "get Orcamentos failed: " << query.lastError();
       return false;
   }
    while (query.next())
    {
        Atributos=new ORCAMENTO;
        Atributos->Ano=query.value("Ano").toInt();
        Atributos->Area=query.value("Area").toInt();
        Atributos->Valor=query.value("Valor").toFloat();

        orcamentos->append(Atributos);

    }
    return orcamentos;
}


//---------------------------------------------------------------
//GET BY ...
//---------------------------------------------------------------
QVector<GASTO*>* DB_Manager::getGastos(){

    QVector<GASTO*> *gastos = new QVector<GASTO*>();
    GASTO *Atributos;
    QSqlQuery query;
    query.prepare("SELECT * FROM GASTO;");
    if(!query.exec())
    {
        qDebug() << "get Gastos failed: " << query.lastError();
    }

    while (query.next())
    {

        Atributos = new GASTO;
        Atributos->Area         = query.value("Area").toInt();
        Atributos->Data_Gasto   = QDate::fromJulianDay(query.value("Data_Gasto").toReal());
        Atributos->Descricao    = query.value("Descricao").toString();
        Atributos->Valor        = query.value("Valor").toFloat();
        Atributos->ID_Pessoa    = query.value("ID_Pessoa").toInt();
        Atributos->E_Fatura     = query.value("E_Fatura").toInt();
        Atributos->ID_Gasto     = query.value("ID_Gasto").toInt();

        gastos->append(Atributos);
    }

return gastos;

}

QVector<GASTO*>* DB_Manager::getGastosByPessoa(int ID_Pessoa){

    QVector<GASTO*> *gastos = new QVector<GASTO*>();
    GASTO *Atributos;


    QSqlQuery query;
    query.prepare("SELECT * FROM GASTO WHERE ID_Pessoa = :id_pessoa;");
    query.bindValue(":id_pessoa", ID_Pessoa);
    if(!query.exec())
    {
        qDebug() << "get Gastos failed: " << query.lastError();
    }
    while (query.next())
    {
        Atributos = new GASTO;
        Atributos->Area=query.value("Area").toInt();
        Atributos->Data_Gasto=QDate::fromJulianDay(query.value("Data_Gasto").toReal());
        Atributos->Descricao=query.value("Descricao").toString();
        Atributos->Valor=query.value("Valor").toFloat();
        Atributos->ID_Pessoa=query.value("ID_Pessoa").toInt();
        Atributos->E_Fatura=query.value("E_Fatura").toInt();
        Atributos->ID_Gasto=query.value("ID_Gasto").toInt();

        gastos->append(Atributos);

    }
return gastos;}

QVector<GASTO*>* DB_Manager::getGastosByID(int ID_Gasto){


    QVector<GASTO*> *gastos = new QVector<GASTO*>();
    GASTO *Atributos;
    QSqlQuery query;
    query.prepare("SELECT * FROM GASTO WHERE ID_Gasto = :id_gasto;");
    query.bindValue(":id_gasto", ID_Gasto);
    if(!query.exec())
    {
        qDebug() << "get Gastos failed: " << query.lastError();
    }
    while (query.next())
    {
        Atributos = new GASTO;
        Atributos->Area=query.value("Area").toInt();
        Atributos->Data_Gasto=QDate::fromJulianDay(query.value("Data_Gasto").toReal());
        Atributos->Descricao=query.value("Descricao").toString();
        Atributos->Valor=query.value("Valor").toFloat();
        Atributos->ID_Pessoa=query.value("ID_Pessoa").toInt();
        Atributos->E_Fatura=query.value("E_Fatura").toInt();
        Atributos->ID_Gasto=query.value("ID_Gasto").toInt();

        gastos->append(Atributos);

    }
return gastos;
}

QVector<GASTO*>* DB_Manager::getGastosByAno(QDate Ano){

    QVector<GASTO*> *gastos = new QVector<GASTO*>();
    GASTO *Atributos;
    QDate Datai,Dataf;
    Datai=Ano.addDays(-Ano.day()+1);
    Datai=Datai.addMonths(-Datai.month()+1);
    Dataf=Datai.addMonths(12);
    //qDebug() << "data_i: " << Datai <<"data_f:" << Dataf;
    QSqlQuery query;
    query.prepare("SELECT * FROM GASTO WHERE (Data_Gasto >= :datai) AND (Data_Gasto<:dataf);");
    query.bindValue(":datai",Datai.toJulianDay());
    query.bindValue(":dataf", Dataf.toJulianDay());
    if(!query.exec())
    {
        qDebug() << "get Gastos failed: " << query.lastError();
    }

    while (query.next())
    {
        Atributos = new GASTO;

        Atributos->Area=query.value("Area").toInt();
        Atributos->Data_Gasto=QDate::fromJulianDay(query.value("Data_Gasto").toReal());
        Atributos->Descricao=query.value("Descricao").toString();
        Atributos->Valor=query.value("Valor").toFloat();
        Atributos->ID_Pessoa=query.value("ID_Pessoa").toInt();
        Atributos->E_Fatura=query.value("E_Fatura").toInt();
        Atributos->ID_Gasto=query.value("ID_Gasto").toInt();

        gastos->append(Atributos);

    }

return gastos;
}

QVector<GASTO*>* DB_Manager::getGastosByPessoaByAno(int ID_Pessoa,QDate Ano){

    QVector<GASTO*> *gastos = new QVector<GASTO*>();
    GASTO *Atributos;
    QDate Datai,Dataf;
    Datai=Ano.addDays(-Ano.day()+1);
    Datai=Datai.addMonths(-Datai.month()+1);
    Dataf=Datai.addMonths(12);
    //qDebug() << "data_i: " << Datai <<"data_f:" << Dataf;
    QSqlQuery query;
    query.prepare("SELECT * FROM GASTO WHERE (ID_Pessoa=:id_pessoa) AND (Data_Gasto >= :datai) AND (Data_Gasto<:dataf);");
    query.bindValue(":datai",Datai.toJulianDay());
    query.bindValue(":dataf", Dataf.toJulianDay());
    query.bindValue(":id_pessoa", ID_Pessoa);
    if(!query.exec())
    {
        qDebug() << "get Gastos failed: " << query.lastError();
    }

    while (query.next())
    {
        Atributos = new GASTO;

        Atributos->Area=query.value("Area").toInt();
        Atributos->Data_Gasto=QDate::fromJulianDay(query.value("Data_Gasto").toReal());
        Atributos->Descricao=query.value("Descricao").toString();
        Atributos->Valor=query.value("Valor").toFloat();
        Atributos->ID_Pessoa=query.value("ID_Pessoa").toInt();
        Atributos->E_Fatura=query.value("E_Fatura").toInt();
        Atributos->ID_Gasto=query.value("ID_Gasto").toInt();

        gastos->append(Atributos);

    }

return gastos;
}

QVector<GASTO*>* DB_Manager::getGastosByPessoaByMes(int ID_Pessoa,QDate Mes){

    QVector<GASTO*> *gastos = new QVector<GASTO*>();
    GASTO *Atributos;
    QDate Datai,Dataf;
    Datai=Mes.addDays(-Mes.day()+1);
    Dataf=Datai.addMonths(1);
    //qDebug() << "data_i: " << Datai <<"data_f:" << Dataf;
    QSqlQuery query;
    query.prepare("SELECT * FROM GASTO WHERE (ID_Pessoa=:id_pessoa) AND (Data_Gasto >= :datai) AND (Data_Gasto<:dataf);");
    query.bindValue(":datai",Datai.toJulianDay());
    query.bindValue(":dataf", Dataf.toJulianDay());
    query.bindValue(":id_pessoa", ID_Pessoa);
    if(!query.exec())
    {
        qDebug() << "get Gastos failed: " << query.lastError();
    }

    while (query.next())
    {
        Atributos = new GASTO;

        Atributos->Area=query.value("Area").toInt();
        Atributos->Data_Gasto=QDate::fromJulianDay(query.value("Data_Gasto").toReal());
        Atributos->Descricao=query.value("Descricao").toString();
        Atributos->Valor=query.value("Valor").toFloat();
        Atributos->ID_Pessoa=query.value("ID_Pessoa").toInt();
        Atributos->E_Fatura=query.value("E_Fatura").toInt();
        Atributos->ID_Gasto=query.value("ID_Gasto").toInt();

        gastos->append(Atributos);

    }

return gastos;
}

QVector<GASTO*>* DB_Manager::getGastosByAnoByArea(QDate Ano,int Area){
    QVector<GASTO*> *gastos = new QVector<GASTO*>();
    GASTO *Atributos;
    QDate Datai,Dataf;
    Datai=Ano.addDays(-Ano.day()+1);
    Datai=Datai.addMonths(-Datai.month()+1);
    Dataf=Datai.addMonths(12);
    //qDebug() << "data_i: " << Datai <<"data_f:" << Dataf;
    QSqlQuery query;
    query.prepare("SELECT * FROM GASTO WHERE (Area=area) AND (Data_Gasto >= :datai) AND (Data_Gasto<:dataf);");
    query.bindValue(":datai",Datai.toJulianDay());
    query.bindValue(":dataf", Dataf.toJulianDay());
    query.bindValue(":area", Area);
    if(!query.exec())
    {
        qDebug() << "get Gastos failed: " << query.lastError();
    }

    while (query.next())
    {
        Atributos = new GASTO;

        Atributos->Area=query.value("Area").toInt();
        Atributos->Data_Gasto=QDate::fromJulianDay(query.value("Data_Gasto").toReal());
        Atributos->Descricao=query.value("Descricao").toString();
        Atributos->Valor=query.value("Valor").toFloat();
        Atributos->ID_Pessoa=query.value("ID_Pessoa").toInt();
        Atributos->E_Fatura=query.value("E_Fatura").toInt();
        Atributos->ID_Gasto=query.value("ID_Gasto").toInt();

        gastos->append(Atributos);

    }

return gastos;
}

QVector<GASTO*>* DB_Manager::getGastosByMesByArea(QDate Mes,int Area){

    QVector<GASTO*> *gastos = new QVector<GASTO*>();
    GASTO *Atributos;
    QDate Datai,Dataf;
    Datai=Mes.addDays(-Mes.day()+1);
    Dataf=Datai.addMonths(1);
    //qDebug() << "data_i: " << Datai <<"data_f:" << Dataf;
    QSqlQuery query;
    query.prepare("SELECT * FROM GASTO WHERE (Area=area) AND (Data_Gasto >= :datai) AND (Data_Gasto<:dataf);");
    query.bindValue(":datai",Datai.toJulianDay());
    query.bindValue(":dataf", Dataf.toJulianDay());
    query.bindValue(":area", Area);
    if(!query.exec())
    {
        qDebug() << "get Gastos failed: " << query.lastError();
    }

    while (query.next())
    {
        Atributos = new GASTO;

        Atributos->Area=query.value("Area").toInt();
        Atributos->Data_Gasto=QDate::fromJulianDay(query.value("Data_Gasto").toReal());
        Atributos->Descricao=query.value("Descricao").toString();
        Atributos->Valor=query.value("Valor").toFloat();
        Atributos->ID_Pessoa=query.value("ID_Pessoa").toInt();
        Atributos->E_Fatura=query.value("E_Fatura").toInt();
        Atributos->ID_Gasto=query.value("ID_Gasto").toInt();

        gastos->append(Atributos);

    }

return gastos;
}

QVector<GASTO*>* DB_Manager::getGastosByMes(QDate Mes){

    QVector<GASTO*> *gastos = new QVector<GASTO*>();
    GASTO *Atributos;
    QDate Datai,Dataf;
    Datai=Mes.addDays(-Mes.day()+1);
    Dataf=Datai.addMonths(1);
    QSqlQuery query;
    query.prepare("SELECT * FROM GASTO WHERE (Data_Gasto >= :datai) AND (Data_Gasto<:dataf);");
    query.bindValue(":datai",Datai.toJulianDay());
    query.bindValue(":dataf", Dataf.toJulianDay());
    if(!query.exec())
    {
        qDebug() << "get Gastos failed: " << query.lastError();
    }

    while (query.next())
    {
        Atributos = new GASTO;

        Atributos->Area=query.value("Area").toInt();
        Atributos->Data_Gasto=QDate::fromJulianDay(query.value("Data_Gasto").toReal());
        Atributos->Descricao=query.value("Descricao").toString();
        Atributos->Valor=query.value("Valor").toFloat();
        Atributos->ID_Pessoa=query.value("ID_Pessoa").toInt();
        Atributos->E_Fatura=query.value("E_Fatura").toInt();
        Atributos->ID_Gasto=query.value("ID_Gasto").toInt();

        gastos->append(Atributos);

    }

return gastos;
}

QVector<GASTO*>* DB_Manager::getGastosByData(QDate Data_Gasto){

    QVector<GASTO*> *gastos = new QVector<GASTO*>();
    GASTO *Atributos;
    QSqlQuery query;
    query.prepare("SELECT * FROM GASTO WHERE Data_Gasto = :data_gasto;");
    query.bindValue(":data_gasto", Data_Gasto.toJulianDay());
    if(!query.exec())
    {
        qDebug() << "get Gastos failed: " << query.lastError();
    }

    while (query.next())
    {
        Atributos = new GASTO;

        Atributos->Area=query.value("Area").toInt();
        Atributos->Data_Gasto=QDate::fromJulianDay(query.value("Data_Gasto").toReal());
        Atributos->Descricao=query.value("Descricao").toString();
        Atributos->Valor=query.value("Valor").toFloat();
        Atributos->ID_Pessoa=query.value("ID_Pessoa").toInt();
        Atributos->E_Fatura=query.value("E_Fatura").toInt();
        Atributos->ID_Gasto=query.value("ID_Gasto").toInt();

        gastos->append(Atributos);

    }
return gastos;


}

QVector<GASTO*>* DB_Manager::getGastosByPessoaByData(int ID_Pessoa, QDate Data_Gasto){

    QVector<GASTO*> *gastos = new QVector<GASTO*>();
    GASTO *Atributos;
    QSqlQuery query;
    query.prepare("SELECT * FROM GASTO WHERE (ID_Pessoa=:id_pessoa) AND (Data_Gasto = :data_gasto);");
    query.bindValue(":data_gasto", Data_Gasto.toJulianDay());
    query.bindValue(":id_pessoa", ID_Pessoa);
    if(!query.exec())
    {
        qDebug() << "get Gastos failed: " << query.lastError();
    }

    while (query.next())
    {
        Atributos = new GASTO;


        Atributos->Area=query.value("Area").toInt();
        Atributos->Data_Gasto=QDate::fromJulianDay(query.value("Data_Gasto").toReal());
        Atributos->Descricao=query.value("Descricao").toString();
        Atributos->Valor=query.value("Valor").toFloat();
        Atributos->ID_Pessoa=query.value("ID_Pessoa").toInt();
        Atributos->E_Fatura=query.value("E_Fatura").toInt();
        Atributos->ID_Gasto=query.value("ID_Gasto").toInt();

        gastos->append(Atributos);

    }
return gastos;


}

QVector<GASTO*>* DB_Manager::getGastosByPessoaByArea(int ID_Pessoa, int Area){

    QVector<GASTO*> *gastos = new QVector<GASTO*>();
    GASTO *Atributos;
    QSqlQuery query;
    query.prepare("SELECT * FROM GASTO WHERE (ID_Pessoa=:id_pessoa) AND (Area = :area);");
    query.bindValue(":area", Area);
    query.bindValue(":id_pessoa", ID_Pessoa);
    if(!query.exec())
    {
        qDebug() << "get Gastos failed: " << query.lastError();
    }

    while (query.next())
    {
        Atributos = new GASTO;


        Atributos->Area=query.value("Area").toInt();
        Atributos->Data_Gasto=QDate::fromJulianDay(query.value("Data_Gasto").toReal());
        Atributos->Descricao=query.value("Descricao").toString();
        Atributos->Valor=query.value("Valor").toFloat();
        Atributos->ID_Pessoa=query.value("ID_Pessoa").toInt();
        Atributos->E_Fatura=query.value("E_Fatura").toInt();
        Atributos->ID_Gasto=query.value("ID_Gasto").toInt();

        gastos->append(Atributos);

    }
return gastos;


}

QVector<GASTO*>* DB_Manager::getGastosByArea(int Area){

    QVector<GASTO*> *gastos = new QVector<GASTO*>();
    GASTO *Atributos;
    QSqlQuery query;
    query.prepare("SELECT * FROM GASTO WHERE Area = :area;");
    query.bindValue(":area", Area);
    if(!query.exec())
    {
        qDebug() << "get Gastos failed: " << query.lastError();
    }

    while (query.next())
    {
        Atributos = new GASTO;

        Atributos->Area=query.value("Area").toInt();
        Atributos->Data_Gasto=QDate::fromJulianDay(query.value("Data_Gasto").toReal());
        Atributos->Descricao=query.value("Descricao").toString();
        Atributos->Valor=query.value("Valor").toFloat();
        Atributos->ID_Pessoa=query.value("ID_Pessoa").toInt();
        Atributos->E_Fatura=query.value("E_Fatura").toInt();
        Atributos->ID_Gasto=query.value("ID_Gasto").toInt();

        gastos->append(Atributos);

    }
return gastos;
}

QVector<GASTO*>* DB_Manager::getGastosByAreaByData(int Area,QDate Data_Gasto){


    QVector<GASTO*> *gastos = new QVector<GASTO*>();
    GASTO *Atributos;
    QSqlQuery query;
    query.prepare("SELECT * FROM GASTO WHERE (Data_Gasto = :data_gasto) AND Area=:area;");
    query.bindValue(":data_gasto", Data_Gasto.toJulianDay());
    query.bindValue(":area", Area);
    if(!query.exec())
    {
        qDebug() << "get Gastos failed: " << query.lastError();
    }

    while (query.next())
    {
        Atributos = new GASTO;


        Atributos->Area=query.value("Area").toInt();
        Atributos->Data_Gasto=QDate::fromJulianDay(query.value("Data_Gasto").toReal());
        Atributos->Descricao=query.value("Descricao").toString();
        Atributos->Valor=query.value("Valor").toFloat();
        Atributos->ID_Pessoa=query.value("ID_Pessoa").toInt();
        Atributos->E_Fatura=query.value("E_Fatura").toInt();
        Atributos->ID_Gasto=query.value("ID_Gasto").toInt();

        gastos->append(Atributos);

    }
return gastos;

}

QVector<GASTO*>* DB_Manager::getGastosByPessoaByAreaByAno(int ID_Pessoa,int Area,QDate Ano){
    QVector<GASTO*> *gastos = new QVector<GASTO*>();
    GASTO *Atributos;
    QDate Datai,Dataf;
    Datai=Ano.addDays(-Ano.day()+1);
    Datai=Datai.addMonths(-Datai.month()+1);
    Dataf=Datai.addMonths(12);
    //qDebug() << "data_i: " << Datai <<"data_f:" << Dataf;
    QSqlQuery query;
    query.prepare("SELECT * FROM GASTO WHERE (ID_Pessoa=:id_pessoa) AND (Area=:area) AND (Data_Gasto >= :datai) AND (Data_Gasto<:dataf);");
    query.bindValue(":datai",Datai.toJulianDay());
    query.bindValue(":dataf", Dataf.toJulianDay());
    query.bindValue(":id_pessoa", ID_Pessoa);
    query.bindValue(":area", Area);
    if(!query.exec())
    {
        qDebug() << "get Gastos failed: " << query.lastError();
    }

    while (query.next())
    {
        Atributos = new GASTO;

        Atributos->Area=query.value("Area").toInt();
        Atributos->Data_Gasto=QDate::fromJulianDay(query.value("Data_Gasto").toReal());
        Atributos->Descricao=query.value("Descricao").toString();
        Atributos->Valor=query.value("Valor").toFloat();
        Atributos->ID_Pessoa=query.value("ID_Pessoa").toInt();
        Atributos->E_Fatura=query.value("E_Fatura").toInt();
        Atributos->ID_Gasto=query.value("ID_Gasto").toInt();

        gastos->append(Atributos);


    }

return gastos;

}

QVector<GASTO*>* DB_Manager::getGastosByPessoaByAreaByMes(int ID_Pessoa,int Area,QDate Mes){
    QVector<GASTO*> *gastos = new QVector<GASTO*>();
    GASTO *Atributos;
    QDate Datai,Dataf;
    Datai=Mes.addDays(-Mes.day()+1);
    Dataf=Datai.addMonths(1);
    //qDebug() << "data_i: " << Datai <<"data_f:" << Dataf;
    QSqlQuery query;
    query.prepare("SELECT * FROM GASTO WHERE (ID_Pessoa=:id_pessoa) AND (Area=:area) AND (Data_Gasto >= :datai) AND (Data_Gasto<:dataf);");
    query.bindValue(":datai",Datai.toJulianDay());
    query.bindValue(":dataf", Dataf.toJulianDay());
    query.bindValue(":id_pessoa", ID_Pessoa);
    query.bindValue(":area", Area);
    if(!query.exec())
    {
        qDebug() << "get Gastos failed: " << query.lastError();
    }

    while (query.next())
    {
        Atributos = new GASTO;

        Atributos->Area=query.value("Area").toInt();
        Atributos->Data_Gasto=QDate::fromJulianDay(query.value("Data_Gasto").toReal());
        Atributos->Descricao=query.value("Descricao").toString();
        Atributos->Valor=query.value("Valor").toFloat();
        Atributos->ID_Pessoa=query.value("ID_Pessoa").toInt();
        Atributos->E_Fatura=query.value("E_Fatura").toInt();
        Atributos->ID_Gasto=query.value("ID_Gasto").toInt();

        gastos->append(Atributos);


    }

return gastos;

}

QVector<GASTO*>* DB_Manager::getGastosByPessoaByAreaByData(int ID_Pessoa,int Area,QDate Data_Gasto){

    QVector<GASTO*> *gastos = new QVector<GASTO*>();
    GASTO *Atributos;
    QSqlQuery query;
    query.prepare("SELECT * FROM GASTO WHERE (Data_Gasto = :data_gasto) AND (ID_Pessoa = :id_pessoa) AND Area=:area;");
    query.bindValue(":data_gasto", Data_Gasto.toJulianDay());
    query.bindValue(":area", Area);
    query.bindValue(":id_pessoa", ID_Pessoa);
    if(!query.exec())
    {
        qDebug() << "get Gastos failed: " << query.lastError();
    }

    while (query.next())
    {
        Atributos = new GASTO;


        Atributos->Area=query.value("Area").toInt();
        Atributos->Data_Gasto=QDate::fromJulianDay(query.value("Data_Gasto").toReal());
        Atributos->Descricao=query.value("Descricao").toString();
        Atributos->Valor=query.value("Valor").toFloat();
        Atributos->ID_Pessoa=query.value("ID_Pessoa").toInt();
        Atributos->E_Fatura=query.value("E_Fatura").toInt();
        Atributos->ID_Gasto=query.value("ID_Gasto").toInt();

        gastos->append(Atributos);

    }
return gastos;

}



QVector<GASTO*>* DB_Manager::getGastosByAreaBetweenData(int Area, QDate Data_Gasto_Inicio,QDate Data_Gasto_Fim){

    QVector<GASTO*> *gastos = new QVector<GASTO*>();
    GASTO *Atributos;
    QSqlQuery query;
    query.prepare("SELECT * FROM GASTO WHERE Area=:area AND (Data_Gasto  < :data_gasto_fim) AND (Data_Gasto  > :data_gasto_inicio);");
    query.bindValue(":area", Area);
    query.bindValue(":data_gasto_fim", Data_Gasto_Fim.toJulianDay());
    query.bindValue(":data_gasto_inicio", Data_Gasto_Inicio.toJulianDay());
    if(!query.exec())
    {
        qDebug() << "get Gastos failed: " << query.lastError();
    }

    while (query.next())
    {
        Atributos = new GASTO;


        Atributos->Area=query.value("Area").toInt();
        Atributos->Data_Gasto=QDate::fromJulianDay(query.value("Data_Gasto").toReal());
        Atributos->Descricao=query.value("Descricao").toString();
        Atributos->Valor=query.value("Valor").toFloat();
        Atributos->ID_Pessoa=query.value("ID_Pessoa").toInt();
        Atributos->E_Fatura=query.value("E_Fatura").toInt();
        Atributos->ID_Gasto=query.value("ID_Gasto").toInt();

        gastos->append(Atributos);

    }
return gastos;

}

QVector<GASTO*>* DB_Manager::getGastosBetweenData(QDate Data_Gasto_Inicio,QDate Data_Gasto_Fim){

    QVector<GASTO*> *gastos = new QVector<GASTO*>();
    GASTO *Atributos;
    QSqlQuery query;
    query.prepare("SELECT * FROM GASTO WHERE (Data_Gasto  < :data_gasto_fim) AND (Data_Gasto  > :data_gasto_inicio);");
    query.bindValue(":data_gasto_fim", Data_Gasto_Fim.toJulianDay());
    query.bindValue(":data_gasto_inicio", Data_Gasto_Inicio.toJulianDay());
    if(!query.exec())
    {
        qDebug() << "get Gastos failed: " << query.lastError();
    }

    while (query.next())
    {
        Atributos = new GASTO;


        Atributos->Area=query.value("Area").toInt();
        Atributos->Data_Gasto=QDate::fromJulianDay(query.value("Data_Gasto").toReal());
        Atributos->Descricao=query.value("Descricao").toString();
        Atributos->Valor=query.value("Valor").toFloat();
        Atributos->ID_Pessoa=query.value("ID_Pessoa").toInt();
        Atributos->E_Fatura=query.value("E_Fatura").toInt();
        Atributos->ID_Gasto=query.value("ID_Gasto").toInt();

        gastos->append(Atributos);

    }
return gastos;


}


//---------------------------------------------------------------
//ORCAMENTOS
//---------------------------------------------------------------


float DB_Manager::getOrcamentoByAreaByAno(int Area, QDate Ano){


    QSqlQuery query;
    query.prepare("SELECT * FROM ORCAMENTO WHERE (Area = :area) AND (Ano = :ano);");
    query.bindValue(":area", Area);
    query.bindValue(":ano", Ano.year());
    if(!query.exec())
    {
        qDebug() << "get Gastos failed: " << query.lastError();
        return 0;
    }

    float valor;
    while (query.next())
    {
          valor = query.value("Valor").toFloat();
    }
    return valor;

}

float DB_Manager::getOrcamentoTotalByAno(QDate Ano){

    QSqlQuery query;
    query.prepare("SELECT SUM(VALOR) as Valor FROM ORCAMENTO WHERE (Ano = :ano);");
    query.bindValue(":ano", Ano.year());
    if(!query.exec())
    {
        qDebug() << "get Gastos failed: " << query.lastError();
        return 0;
    }

    float valor;
    while (query.next())
    {
          valor = query.value("Valor").toFloat();
    }
    return valor;
}


//---------------------------------------------------------------
//E_FATURA
//---------------------------------------------------------------

QVector<GASTO*>* DB_Manager::getGastosByFatura(int E_Fatura){

    QVector<GASTO*> *gastos = new QVector<GASTO*>();
    GASTO *Atributos;

    QDate data;
    QSqlQuery query;
    query.prepare("SELECT * FROM GASTO WHERE E_Fatura = :e_fatura;");
    query.bindValue(":e_fatura", E_Fatura);
    if(!query.exec())
    {
        qDebug() << "get Gastos failed: " << query.lastError();
    }
    while (query.next())
    {
        Atributos->Area=query.value("Area").toInt();
        Atributos->Data_Gasto=QDate::fromJulianDay(query.value("Data_Gasto").toReal());
        Atributos->Descricao=query.value("Descricao").toString();
        Atributos->Valor=query.value("Valor").toFloat();
        Atributos->ID_Pessoa=query.value("ID_Pessoa").toInt();
        Atributos->E_Fatura=query.value("E_Fatura").toInt();
        Atributos->ID_Gasto=query.value("ID_Gasto").toInt();
    }
    gastos->append(Atributos);
return gastos;
}

float DB_Manager::getTotalGastosFatura(int E_Fatura){


    QDate data;


    QSqlQuery query;
    query.prepare("SELECT SUM(Valor) AS Valor FROM GASTO WHERE E_Fatura = :e_fatura;");
    query.bindValue(":e_fatura", E_Fatura);
    if(!query.exec())
    {
        qDebug() << "get Gastos failed: " << query.lastError();
        return 0;
    }
    while (query.next())
    {
        return query.value("Valor").toFloat();
    }
}

//---------------------------------------------------------------
//TOTAIS
//---------------------------------------------------------------

float DB_Manager::getTotalGastos(){



    QSqlQuery query;
    query.prepare("SELECT SUM(Valor) AS Valor FROM GASTO ;");
    if(!query.exec())
    {
        qDebug() << "get Gastos failed: " << query.lastError();
        return 0;
    }

    while (query.next())
    {
    return query.value("Valor").toFloat();
    }

}

float DB_Manager::getTotalGastosByMes(QDate Mes){


    QDate data,Datai,Dataf;
    Datai=Mes.addDays(-Mes.day()+1);
    Dataf=Datai.addMonths(1);
    QSqlQuery query;
    query.prepare("SELECT SUM(Valor) as Valor FROM GASTO WHERE (Data_Gasto >= :datai) AND (Data_Gasto<:dataf);");
    query.bindValue(":datai",Datai.toJulianDay());
    query.bindValue(":dataf", Dataf.toJulianDay());
    if(!query.exec())
    {
        qDebug() << "get Gastos failed: " << query.lastError();
        return 0;
    }

    while (query.next())
    {
        return query.value("Valor").toFloat();
    }

}

float DB_Manager::getTotalGastosByMesByArea(QDate Mes, int Area){


    QDate data,Datai,Dataf;
    Datai=Mes.addDays(-Mes.day()+1);
    Dataf=Datai.addMonths(1);
    QSqlQuery query;
    query.prepare("SELECT SUM(Valor) as Valor FROM GASTO WHERE (Area=:area) AND (Data_Gasto >= :datai) AND (Data_Gasto<:dataf);");
    query.bindValue(":datai",Datai.toJulianDay());
    query.bindValue(":dataf", Dataf.toJulianDay());
    query.bindValue(":area", Area);
    if(!query.exec())
    {
        qDebug() << "get Gastos failed: " << query.lastError();
        return 0;
    }

    while (query.next())
    {
        return query.value("Valor").toFloat();
    }

}

float DB_Manager::getTotalGastosByAno(QDate Ano){

    QDate data,Datai,Dataf;
    Datai=Ano.addDays(-Ano.day()+1);
    Datai=Datai.addMonths(-Datai.month()+1);
    Dataf=Datai.addMonths(12);
    //qDebug() << "data_i: " << Datai <<"data_f:" << Dataf;
    QSqlQuery query;
    query.prepare("SELECT SUM(Valor) as Valor FROM GASTO WHERE (Data_Gasto >= :datai) AND (Data_Gasto<:dataf);");
    query.bindValue(":datai",Datai.toJulianDay());
    query.bindValue(":dataf", Dataf.toJulianDay());
    if(!query.exec())
    {
        qDebug() << "get Gastos failed: " << query.lastError();
        return 0;
    }

    while (query.next())
    {
        return query.value("Valor").toFloat();
    }

}

float DB_Manager::getTotalGastosByData(QDate Dia){


    QSqlQuery query;
    query.prepare("SELECT SUM(Valor) as Valor FROM GASTO WHERE (Data_Gasto = :data);");
    query.bindValue(":data",Dia.toJulianDay());
    if(!query.exec())
    {
        qDebug() << "get Gastos failed: " << query.lastError();
        return 0;
    }

    while (query.next())
    {
        return query.value("Valor").toFloat();
    }

}

float DB_Manager::getTotalGastosByAnoByArea(QDate Mes,int Area){

    QDate data,Datai,Dataf;
    Datai=Mes.addDays(-Mes.day()+1);
    Datai=Datai.addMonths(-Datai.month()+1);
    Dataf=Datai.addMonths(12);
    qDebug() << "data_i: " << Datai <<"data_f:" << Dataf;
    QSqlQuery query;
    query.prepare("SELECT SUM(Valor) as Valor FROM GASTO WHERE(Area=:area) AND (Data_Gasto >= :datai) AND (Data_Gasto<:dataf);");
    query.bindValue(":datai",Datai.toJulianDay());
    query.bindValue(":dataf", Dataf.toJulianDay());
    query.bindValue(":area", Area);
    if(!query.exec())
    {
        qDebug() << "get Gastos failed: " << query.lastError();
        return 0;
    }

    while (query.next())
    {
        return query.value("Valor").toFloat();
    }

}

float DB_Manager::getTotalGastosByPessoa(int ID_Pessoa){


    QDate data;


    QSqlQuery query;
    query.prepare("SELECT SUM(Valor) AS Valor FROM GASTO WHERE ID_Pessoa = :id_pessoa;");
    query.bindValue(":id_pessoa", ID_Pessoa);
    if(!query.exec())
    {
        qDebug() << "get Gastos failed: " << query.lastError();
        return 0;
    }
    while (query.next())
    {
        return query.value("Valor").toFloat();
    }
}

float DB_Manager::getTotalGastosByPessoaByData(int ID_Pessoa,QDate Data){


    QSqlQuery query;
    query.prepare("SELECT SUM(Valor) AS Valor FROM GASTO WHERE (ID_Pessoa = :id_pessoa) AND Data_Gasto=:data;");
    query.bindValue(":id_pessoa", ID_Pessoa);
    query.bindValue(":data", Data);
    if(!query.exec())
    {
        qDebug() << "get Gastos failed: " << query.lastError();
        return 0;
    }
    while (query.next())
    {
        return query.value("Valor").toFloat();
    }
}

float DB_Manager::getTotalGastosByPessoaByArea(int ID_Pessoa,int Area){


    QDate data;


    QSqlQuery query;
    query.prepare("SELECT SUM(Valor) AS Valor FROM GASTO WHERE (ID_Pessoa = :id_pessoa) AND Area=:area;");
    query.bindValue(":id_pessoa", ID_Pessoa);
    query.bindValue(":area", Area);
    if(!query.exec())
    {
        qDebug() << "get Gastos failed: " << query.lastError();
        return 0;
    }
    while (query.next())
    {
        return query.value("Valor").toFloat();
    }
}

float DB_Manager::getTotalGastosByArea(int ID_Area){


    QDate data;


    QSqlQuery query;
    query.prepare("SELECT SUM(Valor) AS Valor FROM GASTO WHERE ID_Area = :id_area;");
    query.bindValue(":id_area", ID_Area);
    if(!query.exec())
    {
        qDebug() << "get Gastos failed: " << query.lastError();
        return 0;
    }
    while (query.next())
    {
        return query.value("Valor").toFloat();
    }
}

float DB_Manager::getTotalGastosByPessoaByAreaByAno(int ID_Pessoa,int Area,QDate Ano){

    QDate data,Datai,Dataf;
    Datai=Ano.addDays(-Ano.day()+1);
    Datai=Datai.addMonths(-Datai.month()+1);
    Dataf=Datai.addMonths(12);
    qDebug() << "data_i: " << Datai <<"data_f:" << Dataf;

    QSqlQuery query;
    query.prepare("SELECT SUM(Valor) AS Valor FROM GASTO WHERE (Area=:area) AND (ID_Pessoa = :id_pessoa) AND (Data_Gasto >= :datai) AND (Data_Gasto<:dataf);");
    query.bindValue(":id_pessoa", ID_Pessoa);
    query.bindValue(":datai", Datai.toJulianDay());
    query.bindValue(":dataf", Dataf.toJulianDay());
    query.bindValue(":area", Area);
    if(!query.exec())
    {
        qDebug() << "get Gastos failed: " << query.lastError();
        return 0;
    }
    while (query.next())
    {
        return query.value("Valor").toFloat();
    }
}

float DB_Manager::getTotalGastosByPessoaByAno(int ID_Pessoa,QDate Ano){

    QDate data,Datai,Dataf;
    Datai=Ano.addDays(-Ano.day()+1);
    Datai=Datai.addMonths(-Datai.month()+1);
    Dataf=Datai.addMonths(12);


    QSqlQuery query;
    query.prepare("SELECT SUM(Valor) AS Valor FROM GASTO WHERE (ID_Pessoa = :id_pessoa) AND (Data_Gasto >= :datai) AND (Data_Gasto<:dataf);");
    query.bindValue(":id_pessoa", ID_Pessoa);
    query.bindValue(":datai", Datai.toJulianDay());
    query.bindValue(":dataf", Dataf.toJulianDay());
    if(!query.exec())
    {
        qDebug() << "get Gastos failed: " << query.lastError();
        return 0;
    }
    while (query.next())
    {
        return query.value("Valor").toFloat();
    }

}

float DB_Manager::getTotalGastosByPessoaByAreaByMes(int ID_Pessoa,int Area,QDate Mes){

    QDate data,Datai,Dataf;
    Datai=Mes.addDays(-Mes.day()+1);
    Dataf=Datai.addMonths(1);


    QSqlQuery query;
    query.prepare("SELECT SUM(Valor) AS Valor FROM GASTO WHERE (Area=:area) AND(ID_Pessoa = :id_pessoa) AND (Data_Gasto >= :datai) AND (Data_Gasto<:dataf);");
    query.bindValue(":id_pessoa", ID_Pessoa);
    query.bindValue(":datai", Datai.toJulianDay());
    query.bindValue(":dataf", Dataf.toJulianDay());
    query.bindValue(":area", Area);
    if(!query.exec())
    {
        qDebug() << "get Gastos failed: " << query.lastError();
        return 0;
    }
    while (query.next())
    {
        return query.value("Valor").toFloat();
    }
    return -1;
}

float DB_Manager::getTotalGastosByPessoaByMes(int ID_Pessoa,QDate Mes){

    QDate data,Datai,Dataf;
    Datai=Mes.addDays(-Mes.day()+1);
    Dataf=Datai.addMonths(1);


    QSqlQuery query;
    query.prepare("SELECT SUM(Valor) AS Valor FROM GASTO WHERE (ID_Pessoa = :id_pessoa) AND (Data_Gasto >= :datai) AND (Data_Gasto<:dataf);");
    query.bindValue(":id_pessoa", ID_Pessoa);
    query.bindValue(":datai", Datai.toJulianDay());
    query.bindValue(":dataf", Dataf.toJulianDay());
    if(!query.exec())
    {
        qDebug() << "get Gastos failed: " << query.lastError();
        return 0;
    }
    while (query.next())
    {
        return query.value("Valor").toFloat();
    }

}

float DB_Manager::getTotalGastosByAreaByData(int Area,QDate Data){


    QSqlQuery query;
    query.prepare("SELECT SUM(Valor) AS Valor FROM GASTO WHERE (Area = :area) AND Data_Gasto=:data;");
    query.bindValue(":area", Area);
    query.bindValue(":data", Data);
    if(!query.exec())
    {
        qDebug() << "get Gastos failed: " << query.lastError();
        return 0;
    }
    while (query.next())
    {
        return query.value("Valor").toFloat();
    }
}

float DB_Manager::getTotalGastosByPessoaByAreaByData(int ID_Pessoa,int Area,QDate Data){


    QSqlQuery query;
    query.prepare("SELECT SUM(Valor) AS Valor FROM GASTO WHERE (Area = :area) AND (Data_Gasto=:data) AND (ID_Pessoa=id_pessoa);");
    query.bindValue(":area", Area);
    query.bindValue(":data", Data);
    query.bindValue(":id_pessoa", ID_Pessoa);
    if(!query.exec())
    {
        qDebug() << "get Gastos failed: " << query.lastError();
        return 0;
    }
    while (query.next())
    {
        return query.value("Valor").toFloat();
    }
}



//---------------------------------------------------------------
//DELETE
//---------------------------------------------------------------
bool DB_Manager::deletePessoa(int ID_Pessoa){
    QSqlQuery queryDel;
    queryDel.prepare("DELETE FROM PESSOA WHERE ID_Pessoa=:id_pessoa;");
    queryDel.bindValue(":id_pessoa", ID_Pessoa);

    if(!queryDel.exec())
    {
        qDebug() << "Clear Table failed: " << queryDel.lastError();
        return false;
    }
    return true;
}

bool DB_Manager::deleteOrcamento(QDate Ano, int Area){
    QSqlQuery queryDel;
    queryDel.prepare("DELETE FROM ORCAMENTO WHERE (Ano = :ano) AND (Area= :area);");
    queryDel.bindValue(":ano", Ano.year());
    queryDel.bindValue(":area", Area);

    if(!queryDel.exec())
    {
        qDebug() << "delete Orcamento failed: " << queryDel.lastError();
        return false;
    }
    return true;
}

bool DB_Manager::deleteGasto(int ID_Gasto){

    QSqlQuery queryDel;
    queryDel.prepare("DELETE FROM GASTO WHERE ID_Gasto=:id_gasto;");
    queryDel.bindValue(":id_gasto", ID_Gasto);

    if(!queryDel.exec())
    {
        qDebug() << "delte Gasto failed: " << queryDel.lastError();
        return false;
    }
    return true;
}


//---------------------------------------------------------------
//PERSONALIZADAS
//---------------------------------------------------------------

float DB_Manager::getTotalBy(int ID_Pessoa,int Area,QDate Data,int flag){


    if(Area==0){
        if(ID_Pessoa==0){
            if(flag==0){

                qDebug() << "TOTAL";
                return getTotalGastos();

                //GET TOTAL
            }
            else{
                if(flag==1){

                    qDebug() << "TOTAL BY ANO";
                    return getTotalGastosByAno(Data);
                 //GET TOTAL BY ANO
                }

                if(flag==2){
                    qDebug() << "TOTAL BY MES";
                    return getTotalGastosByMes(Data);
                 //GET TOTAL BY MES
                }

                if(flag==3){

                    qDebug() << "TOTAL BY DIA";
                   return getTotalGastosByData(Data);
                 //GET TOTAL BY DIA
                }
            }
        }
        else{ //ID_Pessoa != 0

            if(flag==0){
                qDebug() << "TOTAL BY PESSOA";
                return getTotalGastosByPessoa(ID_Pessoa);
                //GET TOTAL BY PESSOA
            }
            else{
                if(flag==1){
                    qDebug() << "TOTAL BY ANO BY PESSOA";
                    return getTotalGastosByPessoaByAno(ID_Pessoa,Data);
                 //GET TOTAL  BY ANO  BY PESSOA
                }

                if(flag==2){
                    qDebug() << "TOTAL BY MES BY PESSOA";
                    return getTotalGastosByPessoaByMes(ID_Pessoa,Data);
                 //GET TOTAL BY MES   BY PESSOA
                }

                if(flag==3){
                    qDebug() << "TOTAL BY DIA BY PESSOA";

                    return getTotalGastosByPessoaByData(ID_Pessoa,Data);
                 //GET TOTAL BY DIA  BY PESSOA
                }
            }

        }
         }else{
        if(ID_Pessoa==0){
            if(flag==0){

                qDebug() << "TOTAL BY AREA";
                return getTotalGastosByArea(Area);
                //GET TOTAL BY AREA
            }
            else{
                if(flag==1){
                    qDebug() << "TOTAL BY ANO BY AREA";
                    return getTotalGastosByAnoByArea(Data,Area);
                 //GET TOTAL BY ANO   BY AREA
                }

                if(flag==2){
                    qDebug() << "TOTAL BY MES BY AREA";
                    return getTotalGastosByMesByArea(Data,Area);
                 //GET TOTAL BY MES   BY AREA
                }

                if(flag==3){
                    qDebug() << "TOTAL BY DIA BY AREA";
                 //GET TOTAL BY DIA   BY AREA
                    return getTotalGastosByAreaByData(Area,Data);
                }
            }
        }
        else{ //ID_Pessoa != 0

            if(flag==0){
                qDebug() << "TOTAL BY PESSOA BY AREA";
                return getTotalGastosByPessoaByArea(ID_Pessoa,Area);
                //GET TOTAL BY PESSOA BY AREA
            }
            else{
                if(flag==1){
                    qDebug() << "TOTAL BY ANO BY PESSOA BY AREA";
                    return getTotalGastosByPessoaByAreaByAno(ID_Pessoa,Area,Data);
                 //GET TOTAL  BY ANO   BY PESSOA BY AREA
                }

                if(flag==2){
                    qDebug() << "TOTAL BY MES BY PESSOA BY AREA";
                    return getTotalGastosByPessoaByAreaByMes(ID_Pessoa,Area,Data);
                 //GET TOTAL BY MES   BY PESSOA BY AREA
                }

                if(flag==3){
                    qDebug() << "TOTAL BY DIA BY PESSOA BY AREA";
                    return getTotalGastosByPessoaByAreaByData(ID_Pessoa,Area,Data);
                 //GET TOTAL BY DIA   BY PESSOA BY AREA
                }
            }

        }

    }

}

QVector<GASTO*>* DB_Manager::getBy(int ID_Pessoa,int Area,QDate Data,int flag){


    if(Area==0){
        if(ID_Pessoa==0){
            if(flag==0){

                qDebug() << "TOTAL";
                return getGastos();

                //GET TOTAL
            }
            else{
                if(flag==1){

                    qDebug() << "TOTAL BY ANO";
                    return getGastosByAno(Data);
                 //GET TOTAL BY ANO
                }

                if(flag==2){
                    qDebug() << "TOTAL BY MES";
                    return getGastosByMes(Data);
                 //GET TOTAL BY MES
                }

                if(flag==3){

                    qDebug() << "TOTAL BY DIA";
                   return getGastosByData(Data);
                 //GET TOTAL BY DIA
                }
            }
        }
        else{ //ID_Pessoa != 0

            if(flag==0){
                qDebug() << "TOTAL BY PESSOA";
                return getGastosByPessoa(ID_Pessoa);
                //GET TOTAL BY PESSOA
            }
            else{
                if(flag==1){
                    qDebug() << "TOTAL BY ANO BY PESSOA";
                    return getGastosByPessoaByAno(ID_Pessoa,Data);
                 //GET TOTAL  BY ANO  BY PESSOA
                }

                if(flag==2){
                    qDebug() << "TOTAL BY MES BY PESSOA";

                    return getGastosByPessoaByMes(ID_Pessoa,Data);
                 //GET TOTAL BY MES   BY PESSOA
                }

                if(flag==3){
                    qDebug() << "TOTAL BY DIA BY PESSOA";
                     return getGastosByPessoaByData(ID_Pessoa,Data);
                 //GET TOTAL BY DIA  BY PESSOA
                }
            }

        }
         }else{
        if(ID_Pessoa==0){
            if(flag==0){

                qDebug() << "TOTAL BY AREA";
                return getGastosByArea(Area);
                //GET TOTAL BY AREA
            }
            else{
                if(flag==1){
                    qDebug() << "TOTAL BY ANO BY AREA";

                    return getGastosByAnoByArea(Data,Area);
                 //GET TOTAL BY ANO   BY AREA
                }

                if(flag==2){
                    qDebug() << "TOTAL BY MES BY AREA";
                     return getGastosByMesByArea(Data,Area);
                 //GET TOTAL BY MES   BY AREA
                }

                if(flag==3){
                    qDebug() << "TOTAL BY DIA BY AREA";
                 //GET TOTAL BY DIA   BY AREA
                     return getGastosByAreaByData(Area,Data);
                }
            }
        }
        else{ //ID_Pessoa != 0

            if(flag==0){
                qDebug() << "TOTAL BY PESSOA BY AREA";

                return getGastosByPessoaByArea(ID_Pessoa,Area);
                //GET TOTAL BY PESSOA BY AREA
            }
            else{
                if(flag==1){
                    qDebug() << "TOTAL BY ANO BY PESSOA BY AREA";
                    return getGastosByPessoaByAreaByAno(ID_Pessoa,Area,Data);
                 //GET TOTAL  BY ANO   BY PESSOA BY AREA
                }

                if(flag==2){
                    qDebug() << "TOTAL BY MES BY PESSOA BY AREA";
                    return getGastosByPessoaByAreaByMes(ID_Pessoa,Area,Data);
                 //GET TOTAL BY MES   BY PESSOA BY AREA
                }

                if(flag==3){
                    qDebug() << "TOTAL BY DIA BY PESSOA BY AREA";
                     return getGastosByPessoaByAreaByData(ID_Pessoa,Area,Data);
                 //GET TOTAL BY DIA   BY PESSOA BY AREA
                }
            }

        }

    }

}

//---------------------------------------------------------------
//TESTES
//---------------------------------------------------------------
/*

QVector<GASTO*>* DB_Manager::GET_TESTE(int Area, QDate Data_Gasto_Inicio,QDate Data_Gasto_Fim){

    QDate data;
    QSqlQuery query;
    query.prepare("SELECT * FROM GASTO WHERE Area=:area AND (Data_Gasto  < :data_gasto_fim) AND (Data_Gasto  > :data_gasto_inicio);");
    query.bindValue(":area", Area);
    query.bindValue(":data_gasto_fim", Data_Gasto_Fim.toJulianDay());
    query.bindValue(":data_gasto_inicio", Data_Gasto_Inicio.toJulianDay());



    if(!query.exec())
    {
        qDebug() << "get Gastos failed: " << query.lastError();
    }

    while (query.next())
    {

        data=QDate::fromJulianDay(query.value("Data_Gasto").toReal());
        qDebug()        << query.value("ID_Gasto").toInt()
                 << " " << query.value("ID_Pessoa").toInt()
                 << " " << data
                 << " " << query.value("Area").toInt()
                 << " " << query.value("Valor").toFloat()
                 << " " << query.value("Descricao").toString()
                 << " " << query.value("E_Fatura").toInt();
        qDebug();
    }
    return true;


}*/


//---------------------------------------------------------------
//DELETE
//---------------------------------------------------------------

bool DB_Manager::removeAll(){

    QSqlQuery queryRem;
    queryRem.prepare("DROP TABLE PESSOA;");

    if(!queryRem.exec())
    {
        qDebug() << "Drop Table failed: " << queryRem.lastError();
        return false;
    }

    queryRem.prepare("DROP TABLE GASTO;");

    if(!queryRem.exec())
    {
        qDebug() << "Drop Table failed: " << queryRem.lastError();
        return false;
    }


    queryRem.prepare("DROP TABLE ORCAMENTO;");

    if(!queryRem.exec())
    {
        qDebug() << "Drop Table failed: " << queryRem.lastError();
        return false;
    }
return true;
}

bool DB_Manager::clearAll(){

    QSqlQuery queryClr;
    queryClr.prepare("DELETE FROM PESSOA;");

    if(!queryClr.exec())
    {
        qDebug() << "Clear PESSOA Table failed: " << queryClr.lastError();
        return false;
    }

    queryClr.prepare("DELETE FROM GASTO;");

    if(!queryClr.exec())
    {
        qDebug() << "Clear GASTO Table failed: " << queryClr.lastError();
        return false;
    }


    queryClr.prepare("DELETE FROM ORCAMENTO;");

    if(!queryClr.exec())
    {
        qDebug() << "Clear ORCAMENTO Table failed: " << queryClr.lastError();
        return false;
    }


return true;
}
