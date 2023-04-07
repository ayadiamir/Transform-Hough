#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

// Structure Point pour stocker les coordonnées d'un point dans l'image
struct Point {
    int x;
    int y;
};

// Classe pour stocker l'image et effectuer la transformation de Hough
class HoughTransform {
public:
    HoughTransform(int width, int height) : width_(width), height_(height) {
        // Initialiser la matrice de votes de Hough avec des zéros
        rho_max_ = sqrt(width_*width_ + height_*height_);
        num_theta_ = 180;
        hough_matrix_.resize(rho_max_*2, vector<int>(num_theta_, 0));
    }

    void addPoint(Point p) {      // Ajouter un point à l'image
        image_.push_back(p);
          
    }
    void printInitialMatrix() {    //affichage de la matrice
        vector<vector<char>> initial_matrix(height_, vector<char>(width_, ' '));
        for (auto p : image_) {
            initial_matrix[p.y][p.x] = '*';
        }
        for (auto row : initial_matrix) {
            for (auto cell : row) {
                cout << cell;
            }
            cout << endl;
        }
    }

    void printHoughMatrix() {
        for (auto row : hough_matrix_) {
            for (auto cell : row) {
                cout << cell << " ";
            }
            cout << endl;
        }
    }
    void scoreH_Transform() {    
        // Calculer la transformation de Hough
        for (auto p : image_) {
            for (int i = 0; i < num_theta_; i++) {
                double theta = i * M_PI / num_theta_;
                double rho = p.x * cos(theta) + p.y * sin(theta);
                int rho_idx = (int)(rho + rho_max_ + 0.5);
                hough_matrix_[rho_idx][i]++;
            }
        }
    }

    void saveImage(const char* filename) {
        // Sauvegarder la matrice de votes de Hough dans un fichier PPM P3
        ofstream file(filename);
        file << "P3" << endl;
        file << num_theta_ << " " << round(rho_max_*2) << endl;
        file << "255" << endl;
        for (int i = 0; i < rho_max_*2; i++) {
            for (int j = 0; j < num_theta_; j++) {
                int value = hough_matrix_[i][j];
                file << value << " ";
            }
            file << endl;
        }
        file.close();
    }
 
private:      //definir les parametres privés
    int width_;
    int height_;
    double rho_max_;
    int num_theta_;
    vector<Point> image_;
    vector<vector<int>> hough_matrix_;
};

int main() {
    // Exemple d'utilisation avec une matrice de taille 50 * 50
    HoughTransform ht(50, 50);
    ht.addPoint({40, 10});   //ajout un point
    ht.addPoint({30,20});  //ajout un point
    //ht.addPoint({10, 30});
   // ht.addPoint({10, 40});

    cout << "Matrice aprés l'ajout des points : " << endl;
    ht.printInitialMatrix();

    ht.scoreH_Transform();

    

    ht.saveImage("matrice_2.ppm");  //enregistrer l'image

    return 0;
}

