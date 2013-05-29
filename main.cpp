#include <QtCore/QString>
#include <QtCore/QFile>
#include <QtCore/QTextStream>

#include "VersionInfo.hpp"
#include "COutput.hpp"

#include <iostream>

int main(int argc, char *argv[])
{
  //QCoreApplication a(argc, argv);

  VersionInfo v1 = VersionInfo(10, 5, 8, 1983);
  QString file = "foo.h";

  Output *foo = OutputFactory::create("C");

  std::cout << "Output type is: " << foo->outputName().toStdString()
               << std::endl;

  foo->setFileName("foo.h");
  foo->write(v1);

  return 0; //a.exec();
}
