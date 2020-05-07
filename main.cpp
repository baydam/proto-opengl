#include "OpenGLWindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  OpenGLWindow window;

  window.resize(1024, 768);

  window.show();
  return a.exec();
}
