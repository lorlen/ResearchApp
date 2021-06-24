#include <memory>

#include <QtWidgets/QApplication>

#include "db/LoginManager.h"
#include "db/storage.h"
#include "ui/LoginWindow.h"

int main(int argc, char* argv[]) {
    auto storage = std::make_shared<Storage>(createStorage("research.db"));
    LoginManager::setStorage(storage);

    QApplication app(argc, argv);
    auto* loginWindow = new LoginWindow{storage};
    loginWindow->setAttribute(Qt::WA_DeleteOnClose);
    loginWindow->show();

    return QApplication::exec();
}
