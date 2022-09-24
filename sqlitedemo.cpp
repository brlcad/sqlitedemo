#include <iostream>

#include <QCoreApplication>

#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QVariant>

int main(int ac, char *av[]) {

  QCoreApplication a(ac, av);

  /* OPEN UP AN IN-MEMORY SQLite DATABASE */
  const QString DRIVER("QSQLITE");
  if(QSqlDatabase::isDriverAvailable(DRIVER))
    printf("sqlite is available\n");
  else
    printf("sqlite is NOT available\n");

  QSqlDatabase db = QSqlDatabase::addDatabase(DRIVER);

  db.setDatabaseName(":memory:");

  if(!db.open()) {
    std::cerr << "ERROR: " << db.lastError().text().toStdString() << std::endl;
    return 1;
  }

  /* CREATE OUR SQLite TABLE */
  QSqlQuery query1("CREATE TABLE issues (id INTEGER PRIMARY KEY, object_name TEXT NOT NULL, severity TEXT CHECK( severity in ('E', 'W', 'I') ) NOT NULL, description TEXT DEFAULT NULL)");
  if(!query1.isActive()) {
    std::cerr  << "ERROR: on creation: " << query1.lastError().text().toStdString() << std::endl;
    return 2;
  }

  /* ADD SOME ISSUES */
  QSqlQuery query2;
  if(!query2.exec("INSERT INTO issues(object_name, severity, description) VALUES('/all.g/foo.r', 'W', 'object name implies region, but is not a region')"))
    std::cerr  << "ERROR: on insertion1: " << query2.lastError().text().toStdString() << std::endl;
  if(!query2.exec("INSERT INTO issues(object_name, severity, description) VALUES('/all.g/bar.r', 'E', 'null combination')"))
    std::cerr  << "ERROR: on insertion2: " << query2.lastError().text().toStdString() << std::endl;

  /* LOOK UP ERROR ISSUES */
  QSqlQuery query3;
  query3.prepare("SELECT object_name, severity, description FROM issues WHERE severity = 'E'");
  if(!query3.exec())
    std::cerr  << "ERROR: on select " << query3.lastError().text().toStdString() << std::endl;

  /* PRINT ONE OF THEM TO CONSOLE */
  if(query3.first()) {
    switch (query3.value(1).toString().toStdString().c_str()[0]) {
      case 'E':
        std::cout << "ERROR: ";
        break;
      case 'W':
        std::cout << "WARNING: ";
        break;
      case 'I':
      default:
        std::cout << "INFO: ";
        break;
    }
    std::cout << query3.value(0).toString().toStdString();
    if (!query3.value(2).toString().isEmpty())
      std::cout << " " << query3.value(2).toString().toStdString() << std::endl;
    else
      std::cout << std::endl;

  } else {
    std::cout << "no errors found" << std::endl;
  }

  return 0;
}
