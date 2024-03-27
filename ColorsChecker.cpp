#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

struct Color {
    int r, g, b;

    bool operator<(const Color& other) const {
        return tie(r, g, b) < tie(other.r, other.g, other.b);
    }
};

void processImage(const string& path) {
    ifstream file(path);
    if (!file.is_open()) {
        cout << "Nie mozna otworzyc pliku." << endl;
        return;
    }

    string line, format;
    getline(file, format); 

    while (getline(file, line) && line[0] == '#');

    stringstream dimensions(line);
    int width, height;
    dimensions >> width >> height;

    int maxVal = 1;
    if (format == "P2" || format == "P3") {
        file >> maxVal;
    }

    map<Color, int> colorCounts;
    int r, g, b;

    if (format == "P3") { 
        while (file >> r >> g >> b) {
            colorCounts[{r, g, b}]++;
        }
    }
    else {
        while (file >> r) {
            if (format == "P1") { 
                r = r * 255; 
            }
            colorCounts[{r, r, r}]++;
        }
    }

    auto mostCommon = max_element(colorCounts.begin(), colorCounts.end(),
        [](const pair<Color, int>& a, const pair<Color, int>& b) {
            return a.second < b.second;
        });

    cout << "Szerokosc obrazu: " << width << endl;
    cout << "Wysokosc obrazu: " << height << endl;
    if (mostCommon != colorCounts.end()) {
        cout << "Najczęściej wystepujacy kolor to " << mostCommon->first.r << "-" << mostCommon->first.g << "/" << mostCommon->first.b << " i wystapil " << mostCommon->second << " razy" << endl;
    }
    else {
        cout << "Nie znaleziono kolorów." << endl;
    }
    cout << "Liczba unikalnych kolorow: " << colorCounts.size() << endl;
}

int main() {
    string path;
    string decision;

    do {
        cout << "Podaj nazwe pliku: ";
        cin >> path;
        processImage(path);
        cout << "Czy chcesz wczytac kolejny plik(tak/nie): ";
        cin >> decision;
    } while (decision == "tak");

    return 0;
}
