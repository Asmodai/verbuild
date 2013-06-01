#include <QDebug>
#include <QtCore/QString>
#include <QtCore/QFile>
#include <QtCore/QTextStream>

#include "Enums.hpp"
#include "Settings.hpp"
#include "VersionInfo.hpp"
#include "CFormatter.hpp"

#include <iostream>

int main(int argc, char **argv)
{
  VersionInfo v1 = VersionInfo(10, 5, 8, 5, 1983, BuildType::Simple);
  VersionInfo v2 = VersionInfo();
  Formatter *foo = FormatterFactory::create("C");
  Settings settings(argc, argv);

  qDebug() << "Formatter name: " << foo->formatterName();

  if (settings.useStdOut()) {
    qDebug() << "Using STDOUT.";
  } else {
    qDebug() << "Writing to" << settings.filePath();
  }

  settings.dump();

  foo->setFileName("foo.h");
  foo->read(v2);
  v2.setBuildType(BuildType::ByMonths);
  v2.increment();

  /*
  v1.increment();
  qDebug() << "Version - Base year: " << v1.baseYear() << endl
           << "          Major    : " << v1.major() << endl
           << "          Minor    : " << v1.minor() << endl
           << "          Patch    : " << v1.patch() << endl
           << "          Build    : " << v1.build() << endl;
  */

  qDebug() << "Incrementing." << endl << endl
           << "Version - Base year: " << v2.baseYear() << endl
           << "          Major    : " << v2.major() << endl
           << "          Minor    : " << v2.minor() << endl
           << "          Patch    : " << v2.patch() << endl
           << "          Build    : " << v2.build() << endl
           << "Built on " << v2.toDate().toString() << endl;

  /*
  foo->write(v2);
  */

  return 0; //a.exec();
}
