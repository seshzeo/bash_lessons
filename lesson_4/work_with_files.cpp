#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

vector< vector <long double> > reading_coords(string);
template <typename T, typename Container>
void writing_coords_to_file(string, const Container&); 

int main() {
    auto my_coords = reading_coords("coordinates.txt");
    vector < vector<long double> > sorting_coords(0, vector<long double>(2));
    sorting_coords.reserve(20);
    for (auto &coord : my_coords) {
        long double x = coord[0], y = coord[1];
        if (50.0 <= x && x <= 80.0 && 20.0 <= y && y <= 45.0) {
            sorting_coords.push_back({x, y});
            cout << "[" << x << " : " << y << "]" << endl;
        }
    }
    writing_coords_to_file<vector <long double> >("result.txt", sorting_coords);
}

vector< vector <long double> > reading_coords(string path) {
    // string path = "text.txt";
    ifstream fin;
    fin.open(path);
    vector< vector <long double> > result(0, vector <long double>(2));
    result.reserve(20);
    if (!fin.is_open()) {
        cout << "Error to open\n";
        exit(0);
    } else {
        cout << "File is open!\n\n";
        string tmp_str, lat, lon;
        while(!fin.eof()) {
            tmp_str = "";
            getline(fin, tmp_str);
            if (tmp_str[0] != '(') {
                // throw invalid_argument("Wrong format of data");
                continue;
            } else {
                lat = lon = "";
                bool isLat = true;
                for (auto &ch : tmp_str) {
                    if (ch == '(' || ch == ')' || ch == ' ') {
                        continue;
                    }
                    if (ch == ',') {
                        isLat = false;
                        continue;
                    }
                    if (isLat) {
                        lat += ch;
                    } else {
                        lon += ch;
                    }
                }
                // cout << "Долгота: " << stold(lat) << " Широта: " << stold(lon) << endl;
                result.push_back({stold(lat), stold(lon)});
            }
        }
    }
    fin.close();
    return result;
}

template <typename T, typename Container>
void writing_coords_to_file(string path, const Container& coordinates) {
    ofstream fout;
    fout.open(path);
    if (!fout.is_open()) {
        cout << "Error to open\n";
        exit(0);
    } else {
        for (auto &&coord : coordinates) {
            fout << '(' << coord[0] << ", " << coord[1] << ")\n";
        }
        fout.close();
        cout << "\nFile is recorded\n";
    }
}