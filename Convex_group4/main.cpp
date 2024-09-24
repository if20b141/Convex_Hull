#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <fstream>

std::vector<float> generateRandomFloats() {
    std::srand(static_cast<unsigned int>(std::time(0)));

    int num_floats = 10 + std::rand() % 91;
    std::vector<float> random_numbers;

    for (int i = 0; i < num_floats; ++i) {
        float random_float = 10.0f + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / 90.0f));
        random_numbers.push_back(random_float);
    }

    return random_numbers;
}
std::vector<float> processFile(const std::string& filename) {
    std::vector<float> points;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Fehler beim Öffnen der Datei: " << filename << std::endl;
        return points;
    }

    int n;
    file >> n;  // Erste Zeile: Anzahl der Punkte

    for (int i = 0; i < n; ++i) {
        std::string line;
        if (std::getline(file, line)) {
            std::stringstream ss(line);
            float x, y;
            char comma;
            if (ss >> x >> comma >> y && comma == ',') {
                points.push_back(x);
                points.push_back(y);
            } else {
                std::cerr << "Fehlerhafte Zeile: " << line << std::endl;
            }
        }
    }

    file.close();
    return points;
}

int main() {
    int input = 1;

    while (input != 0) {
        std::cout << "Bitte eine Zahl eingeben (0 zum Beenden) (1 um die konvexe Hülle zu berechnen): ";
        std::cin >> input;

        if (input == 1) {
            int sub_input = 0;
            do {
                std::cout << "Sie haben 1 gewählt. Bitte wählen Sie 1(Zufallszahlen random generieren) oder 2(file einlesen): ";
                std::cin >> sub_input;
                if (sub_input == 1) {
                    std::cout << "Option 1 wurde gewählt. Generiere zufällige Zahlen..." << std::endl;
                    std::vector<float> random_numbers = generateRandomFloats();

                    std::cout << random_numbers.size() << " zufällige Zahlen wurden generiert und gespeichert." << std::endl;
                    for (float num : random_numbers) {
                        std::cout << num << " ";
                    }
                    std::cout << std::endl;
                }
                else if (sub_input == 2) {
                    std::cout << "Option 2 wurde gewählt. Bitte geben Sie den Dateinamen ein: ";
                    std::string filename;
                    std::cin >> filename;

                    std::vector<float> points = processFile(filename);
                    if (!points.empty()) {
                        std::cout << "Punkte erfolgreich eingelesen." << std::endl;
                        for (size_t i = 0; i < points.size(); i += 2) {
                            std::cout << "Punkt " << (i / 2) + 1 << ": (" << points[i] << ", " << points[i + 1] << ")" << std::endl;
                        }
                    } else {
                        std::cout << "Fehler beim Einlesen der Datei oder keine gültigen Punkte gefunden." << std::endl;
                    }
                }
                else {
                    std::cout << "Ungültige Eingabe, bitte versuchen Sie es erneut." << std::endl;
                }
            } while (sub_input != 1 && sub_input != 2);
        }
        else if (input == 0) {
            std::cout << "Programm wird beendet." << std::endl;
        }
        else {
            std::cout << "Sie haben " << input << " eingegeben." << std::endl;
        }
    }

    std::cout << "Programm beendet." << std::endl;
    return 0;
}
