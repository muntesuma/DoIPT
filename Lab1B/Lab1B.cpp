#include <iostream>
#include <vector>
#include <cstdint>
#include <string>

using namespace std;

// классы-заглушки
struct Image {
    string name;
    Image(const string& n) : name(n) {}
};

struct Account {
    string username;
    Account(const string& u) : username(u) {}
};

struct Url {
    string address;
    Url(const string& a) : address(a) {}
};
// работа с файловой системой
class ImageStorage {
public:
    static void Save(const Image& image) 
    {
        // сохранение изображения
        cout << "Image '" << image.name << "' saved to filesystem\n";
    }

    static int DeleteDuplicates() {
        int deletedCount = rand() % 5; // случайное число для демонстрации

        // удаление дубликатов
        cout << "Deleted " << deletedCount << " duplicate images\n";

        // возврат количества удаленных
        return deletedCount;
    }
};

// операции с изображениями в аккаунте
class AccountImageService {
public:
    static void SetImageAsAccountPicture(const Image& image, const Account& account) {
        // запрос к базе данных для сохранения ссылки на это изображение для пользователя
        cout << "Image '" << image.name
            << "' set as profile picture for account '"
            << account.username << "'\n";
    }
};

// преобразования изображений
class ImageProcessor {
public:
    static Image Resize(const Image& image, int height, int width) {
        // изменение размеров
        cout << "Image '" << image.name
            << "' resized to "
            << width << "x" << height << "\n";
        return image;
    }

    static Image InvertColors(const Image& image) {
        // инверсия цвета
        cout << "Colors inverted for image '" << image.name << "'\n";
        return image;
    }
};

// загрузка изображений по URL
class ImageDownloader {
public:
    static vector<uint8_t> Download(const Url& imageUrl) { 
        // uint8_t - "безопасный" беззнаковый 8-битный целочисленный тип
        // загрузка битового массива с изображением с помощью HTTP запроса
        cout << "Downloading image from URL: " << imageUrl.address << "\n";
        return vector<uint8_t>(100); // возврат фиктивных данных
    }
};

void showMenu() {
    cout << "\n=== Image Processing Menu ===\n";
    cout << "1. Save image\n";
    cout << "2. Delete duplicates\n";
    cout << "3. Set as profile picture\n";
    cout << "4. Resize image\n";
    cout << "5. Invert colors\n";
    cout << "6. Download from URL\n";
    cout << "0. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    Image testImage("test.jpg");
    Account testAccount("user123");
    Url testUrl("http://example.com/image.png");

    int choice;
    do {
        showMenu();
        cin >> choice;
        cin.ignore(); // очистка буфера от '\n'

        switch (choice) {
        case 1:
            ImageStorage::Save(testImage);
            break;
        case 2:
            ImageStorage::DeleteDuplicates();
            break;
        case 3:
            AccountImageService::SetImageAsAccountPicture(testImage, testAccount);
            break;
        case 4: {
            int w, h;
            cout << "Enter width and height: ";
            cin >> w >> h;
            ImageProcessor::Resize(testImage, h, w);
            break;
        }
        case 5:
            ImageProcessor::InvertColors(testImage);
            break;
        case 6:
            ImageDownloader::Download(testUrl);
            break;
        case 0:
            cout << "Exiting program\n";
            break;
        default:
            cout << "Invalid choice!\n";
        }
    } while (choice != 0);

    return 0;
}
