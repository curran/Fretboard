#include <QApplication>
#include <signal.h>
#include "gui.h"
#include "midi.h"

static void signal_handler(int /*sig*/)
{
  disconnect_from_jack();
  exit(0);
}

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  connect_to_jack();

  signal(SIGQUIT, signal_handler);
  signal(SIGTERM, signal_handler);
  signal(SIGHUP, signal_handler);
  signal(SIGINT, signal_handler);
  
  GUI gui;
  gui.show();
  return app.exec();
}
