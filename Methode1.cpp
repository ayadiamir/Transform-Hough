#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

struct Point{
    int x;
    int y;
};

vector<int> trans_hough(int x, int y,int M){
    vector<int> D(M);
    for(int i=0;i<M;i++){
        D[i]=-i*x+y; // formule de la transformée de Hough
    }
    return D;
}

vector<vector<int>> Score(vector<int> Droite, vector<vector<int>>& Mat){ //definir matrice de vote
    int N = Mat.size();
    int M = Mat[0].size();
    for (int i = 0; i<N; i++) {
        for (int j = 0; j<M; j++){   
            if(j == Droite[i] ) {
                Mat[i][j]+=1;
            }
        }
    }
    return Mat;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    int  N = 10;
    int M = 10;
    int value=0;
    std::vector<std::vector<int>> Matrice_vote(M, std::vector<int>(N)); 
    std::vector<std::vector<int>> image(N, std::vector<int>(M));
    image[1][1]=50;
    image[8][8]=50;


    ofstream fichier("hough.ppm");
    fichier << "P3" << endl;
    fichier << M << " " << N << endl;
    fichier << "255" << endl;
    for (int i = 0; i<N;i++) {
        for (int j = 0; j<M; j++){
            fichier << image[i][j] << " ";
        }
        fichier << endl;
    }

    //Etape 1:
    //On extrait les indices dans image tels que leur valeur est non nulle :
    for (int i = 0; i<N;i++) {
        for (int j = 0; j<M; j++){
            if(image[i][j]!=0) {
                vector<int> D = trans_hough(i, j,M);
                Matrice_vote = Score(D, Matrice_vote);
            }
        }
    }

    ofstream fichier_vote("hough_vote.ppm");
    for (int i = 0; i<M;i++) { 
        for (int j = 0; j<N; j++){
            int pixel = Matrice_vote[i][j]; 
            fichier_vote << pixel << " "<< " "; // Ecriture du pixel dans le fichier
        }
        fichier_vote << endl; 
    }
        
    
        //Etape 2:
    //On recherche les coordonnées des points maximum dans la matrice de vote
    int max_vote=0;
    vector<Point> points_max;
    for (int i = 0; i<M;i++) { 
        for (int j = 0; j<N; j++){ 
            if(Matrice_vote[i][j]>=max_vote) {
                max_vote=Matrice_vote[i][j];
                points_max.clear(); 
                points_max.push_back({i,j}); 
            }
        }
    }
    //Etape 3:
    //On trace les droites correspondant aux points maximum dans l'image
    for (auto p : points_max) {
        
        for(int i = 0; i < M; i++) {
            int j = p.y +p.x*i;
            if(i>=0 && i<N) { 
                image[i][j]=1; 
            }
        }
    }}

    

    ofstream fichier_resultat("hough_resultat.ppm"); 
    fichier_resultat << "P3" << endl;
    fichier_resultat << M << " " << N << endl;
    fichier_resultat << "255" << endl;
    for (int i = 0; i<N;i++) {
        for (int j = 0; j<M; j++){
            fichier_resultat << image[i][j] << " ";
        }
        fichier_resultat << endl;
    }

    return 0;
}
