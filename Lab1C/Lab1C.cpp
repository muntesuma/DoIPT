#include <iostream>
#include <string>
#include <memory>

using namespace std;

// интерфейс для логгера
class ILogger {
public:
    virtual ~ILogger() = default;
    virtual void Log(const string& logText) = 0;
};

// логгер в файл
class FileLogger : public ILogger {
public:
    void Log(const string& logText) override {
        // запись в файл
        cout << "Logging to file: " << logText << endl;
    }
};

// логгер в базу данных
class DatabaseLogger : public ILogger {
public:
    void Log(const string& logText) override {
        // запись в БД
        cout << "Logging to database: " << logText << endl;
    }
};

// SmtpMailer, зависящий от ILogger
class SmtpMailer {
private:
    unique_ptr<ILogger> logger;

public:
    // конструктор принимает указатель на ILogger (внедрение зависимости)
    explicit SmtpMailer(unique_ptr<ILogger> logger) : logger(move(logger)) 
    {

    }

    void SendMessage(const string& message) {
        // отправка сообщения
        cout << "Sending message: " << message << endl;
        logger->Log("Message sent: " + message);
    }
};

int main() {
    // логирование в файл
    auto fileLogger = make_unique<FileLogger>();
    SmtpMailer mailerWithFileLog(move(fileLogger));
    mailerWithFileLog.SendMessage("FileLogger");

    // логирование в базу данных 
    auto dbLogger = make_unique<DatabaseLogger>();
    SmtpMailer mailerWithDbLog(move(dbLogger));
    mailerWithDbLog.SendMessage("DatabaseLogger");

    return 0;
}