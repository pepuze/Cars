#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
#include <fstream>

class Car {
private:
    std::string company, model, color;
    int fwd;
    bool del;
public:
    Car() {
        company = model = color = "N/A";
        fwd = -1; del = 0;
    }

    std::string getClr() { return color; }

    void setClr(std::string s) { color = s; }

    std::string getMdl() { return model; }

    void setMdl(std::string s) { model = s; }

    std::string getCmp() { return company; }

    void setCmp(std::string s) { company = s; }

    int getFwd() { return fwd; }

    void setFwd(int n) { fwd = n; }

    void setDel(bool b) { del = b; }

    bool isDel() { return del; }

    bool changeProp(std::string prop, std::string newProp) {
        if (prop == "color") {
            color = newProp;
            return 1;
        }
        else if (prop == "company") {
            company = newProp;
            return 1;
        }
        else if (prop == "model") {
            model = newProp;
            return 1;
        }
        else if (prop == "fwd") {
            fwd = stoi(newProp);
            return 1;
        }
        else if (prop == "all") {
            company = newProp;
            std::cin >> model >> color >> fwd;
            return 1;
        }
        else {
            std::cout << prop << " - такого свойства нет\n";
            return 0;
        }
    }

    void printProp(std::string prop) {
        if (prop == "color")        std::cout << color << std::endl;
        else if (prop == "company") std::cout << company << std::endl;
        else if (prop == "model")   std::cout << model << std::endl;
        else if (prop == "fwd")     std::cout << fwd << std::endl;
        else if (prop == "all")     std::cout << company << " " << model << " " << color << " " << fwd << std::endl;
		else std::cout << prop << " - такого свойства нет\n\n";
    }

};

void printList(std::vector<Car>& cars) {
    for (int i = 0; i < cars.size(); ++i) {
        std::cout << i + 1 << " - " << cars[i].getCmp() << " " << cars[i].getMdl() << " " << cars[i].getClr() << " " << cars[i].getFwd();
        if (cars[i].isDel()) std::cout << " - помечен на удаление";
        std::cout << "\n";
    }
    std::cout << "\n";
}

void save(std::vector<Car>& cars) {
    std::ofstream fout("save.txt");
    for (int i = 0; i < cars.size(); ++i) {
        if (!cars[i].isDel()) {
            fout << cars[i].getCmp() << " " << cars[i].getMdl() << " " << cars[i].getClr() << " " << cars[i].getFwd() << std::endl;
        }
    }
    fout.close();
}

void saveIn(std::vector<Car>& cars, std::string savePath) {
    std::ofstream fout(savePath);
    for (int i = 0; i < cars.size(); ++i) {
        if (!cars[i].isDel()) {
            fout << cars[i].getCmp() << " " << cars[i].getMdl() << " " << cars[i].getClr() << " " << cars[i].getFwd() << std::endl;
        }
    }
    fout.close();
}

void printHelp() {
    std::cout << "свойства элемента 'машина' идут в таком порядке - company, model, color, fwd\n";
    std::cout << "change *номер элемента* *свойство* - меняет свойство элемента\n";
    std::cout << "show *номер элемента* *свойство* - выводит свойство элемента\n";
    std::cout << "list - выводит список всех элементов\n";
    std::cout << "add - добавляет новый элемент\n";
    std::cout << "delete *номер элемента* - помечает элемент на удаление\n";
    std::cout << "remove - подтвердить удаление поченных элементов\n";
    std::cout << "undelete *номер элемента* - убирает пометку на удаление элемента\n";
    std::cout << "save - сохраняет текущий список элементов в savet.txt\n";
    std::cout << "saveIn *savepath.txt* - сохраняет текущий список элементов в savepath.txt\n";
    std::cout << "loadFrom *loadpath.txt* - загружает список элементов из loadpath.txt\n";
    std::cout << "exit - закрывает программу с сохранением текущего списка элементов\n\n";
}

std::vector<Car> cars;

void load(std::vector<Car> &cars) {
    std::string s;
    cars.clear();
    std::ifstream fin("save.txt");
    while (fin >> s) {
        Car car;
        car.setCmp(s);
        fin >> s;
        car.setMdl(s);
        fin >> s;
        car.setClr(s);
        fin >> s;
        car.setFwd(stoi(s));
        cars.push_back(car);
    }
    fin.close();
}

void loadFrom(std::vector<Car>& cars, std::string loadPath) {
    std::string s;
    cars.clear();
    std::ifstream fin(loadPath);
    while (fin >> s) {
        Car car;
        car.setCmp(s);
        fin >> s;
        car.setMdl(s);
        fin >> s;
        car.setClr(s);
        fin >> s;
        car.setFwd(stoi(s));
        cars.push_back(car);
    }
    fin.close();
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    
    std::string command;

    printList(cars);
    std::cout << "help - вывод списка комманд\n\n";

    while (1) {
        std::cin >> command;
        if (command == "change") {
            int num;
            std::string prop, newProp;
            std::cin >> num;
            if (num > cars.size() || num <= 0) {
                std::cout << "Элемента с таким номером нет\n\n";
                continue;
            }
            std::cin >> prop >> newProp;
            if (cars[--num].changeProp(prop, newProp)) std::cout << "Элемент изменен успешно\n\n";
            else std::cout << "Элемент не изменен\n\n";
        }

        else if (command == "show") {
            int num;
            std::string prop;
            std::cin >> num;
            if (num > cars.size() || num <= 0) {
                std::cout << "Элемента с таким номером нет\n\n";
                continue;
            }
            std::cin >> prop;
            cars[--num].printProp(prop);
            std::cout << "\n\n";
        }

        else if (command == "help") {
            printHelp();
        }

        else if (command == "list") {
            printList(cars);
        }

        else if (command == "loadFrom") {
            std::string loadPath;
            std::cin >> loadPath;
            loadFrom(cars, loadPath);
            std::cout << "Данные загружены из " << loadPath << "\n\n";
        }

        else if (command == "add") {
            std::cout << "Добавлен новый элемент\nВведите свойства нового элемента:\n";
            Car car;
            std::string newProp;
            std::cin >> newProp;
            car.changeProp("all", newProp);
            cars.push_back(car);
            std::cout << "Свойства успешно добавлены\n\n";
        }

        else if (command == "delete") {
            int num;
            std::cin >> num;
            if (num > cars.size() || num <= 0) {
                std::cout << "Элемента с таким номером нет\n\n";
                continue;
            }
            cars[--num].setDel(1);
            std::cout << "Элемент " << num + 1 << " помечен на удаление\n\n";
        }

        else if (command == "remove") {
            save(cars);
            load(cars);
            std::cout << "Элементы, помеченные на удаление, удалены успешно\n\n";
        }

        else if (command == "undelete") {
            int num;
            std::cin >> num;
            if (num > cars.size() || num <= 0) {
                std::cout << "Элемента с таким номером нет\n\n";
                continue;
            }
            cars[--num].setDel(0);
            std::cout << "Элемент " << num + 1 << " будет сохранен\n\n";
        }

        else if (command == "save") {
            save(cars);
            std::cout << "Данные сохранены\n\n";
        }

        else if (command == "saveIn") {
            std::string savePath;
            std::cin >> savePath;
            saveIn(cars, savePath);
            std::cout << "Данные сохранены в " << savePath << "\n\n";
        }

        else if (command == "exit") {
            save(cars);
            break;
        }

        else std::cout << command << " - не является командой\n\n";
    }
    return 0;
}