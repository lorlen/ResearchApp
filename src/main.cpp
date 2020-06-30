#include <QtWidgets/QApplication>
#include "ui/MainWindow.h"
#include "ui/LoginWindow.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    auto* loginWindow = new LoginWindow{};
    loginWindow->setAttribute(Qt::WA_DeleteOnClose);
    loginWindow->show();

    return app.exec();
}
