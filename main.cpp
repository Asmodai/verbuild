#include <QDebug>
#include <QtCore/QString>
#include <QtCore/QFile>
#include <QtCore/QTextStream>

#include "VersionInfo.hpp"
#include "CFormatter.hpp"

int main(int argc, char *argv[])
{
  //QCoreApplication a(argc, argv);

  VersionInfo v1 = VersionInfo(10, 5, 8, 1983);
  VersionInfo v2 = VersionInfo();
  QString file = "foo.h";

  Formatter *foo = FormatterFactory::create("C");

  qDebug() << "Formatter name: " << foo->formatterName();

  foo->setFileName("foo.h");
  foo->read(v2);

  qDebug() << "Version - Base year: " << v2.baseYear() << endl
           << "          Major    : " << v2.major() << endl
           << "          Minor    : " << v2.minor() << endl
           << "          Patch    : " << v2.patch() << endl
           << "          Build    : " << v2.build() << endl;

  v2.incrementMajor();

  qDebug() << "Incrementing." << endl << endl
           << "Version - Base year: " << v2.baseYear() << endl
           << "          Major    : " << v2.major() << endl
           << "          Minor    : " << v2.minor() << endl
           << "          Patch    : " << v2.patch() << endl
           << "          Build    : " << v2.build() << endl
           << "Built on " << v2.buildDate() << endl;

  foo->write(v2);

  return 0; //a.exec();
}
