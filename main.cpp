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
  VersionInfo v2 = VersionInfo();
  Formatter *foo = FormatterFactory::create("C");
  Settings settings(argc, argv);

  if (settings.verbose()) {
    settings.dump();
  }

  if (!settings.useStdOut()) {
    foo->setFileName(settings.filePath());
  }

  foo->read(v2);

  if (settings.verbose()) {
    QTextStream out(stdout);

    out << "Read in version:     " << v2.toString() << endl;
  }

  v2.setBuildType(settings.incrementType());
  v2.increment(settings.incrementFields());

  for (int i = 0; i < 4; ++i) {
    InitialValues v = settings.initialVersion()[i];

    if (v.use) {
      switch (i) {
        case 0: v2.setMajor(v.value); break;
        case 1: v2.setMinor(v.value); break;
        case 2: v2.setBuild(v.value); break;
        case 3: v2.setPatch(v.value); break;
      }
    }
  }

  if (settings.verbose()) {
    QTextStream out(stdout);

    out << "Writing out version: " << v2.toString() << endl;
  }

  //foo->write(v2);

  return 0;
}
