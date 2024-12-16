#include <iostream>
#include <string>
#include <memory>
#include <mutex>

class Logger {
public:
    // Забороняємо копіювання та присвоювання
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    // Статичний метод для отримання єдиного екземпляра
    static Logger& getInstance() {
        // Статичний екземпляр, створюється при першому виклику
        static Logger instance;
        return instance;
    }

    void log(const std::string& message) {
        // Можлива реалізація: запис у файл чи виведення в консоль
        // Тут просто виведемо повідомлення
        std::lock_guard<std::mutex> lock(mutex_);
        std::cout << "[LOG]: " << message << std::endl;
    }

private:
    Logger() = default; // Приватний конструктор
    ~Logger() = default;

    std::mutex mutex_;
};

int main() {
    // Отримуємо посилання на єдиний екземпляр логера
    Logger& logger = Logger::getInstance();
    logger.log("Application started.");

    // В іншому місці коду ми не створюємо новий логер, а звертаємось до існуючого
    Logger::getInstance().log("Another log message.");

    return 0;
}
