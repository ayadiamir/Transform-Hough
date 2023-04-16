# Transform-Hough
Itroduction:

    Ce code C++ utilise la bibliothèque standard pour effectuer une transformation de Hough sur 
    une image constituée de points. La transformation de Hough est une technique de traitement 
    d'images qui permet de détecter des formes géométriques telles que des lignes  dans une image.


Objectif:

    Dans ce projet, notre objectif est de détecter les droites présentes sur une image en
    utilisant la transformation de Hough.  Cette transformation se divise en deux parties :
      
    La première partie est la transformation de Hough classique. Nous prenons une matrice d'image 
    et un pixel de cette matrice. Ensuite, nous appliquons la transformation de Hough sur ce pixel,
    ce qui nous donne une droite dans l'espace (m, p). Nous répétons cette étape pour un autre point 
    de notre image. Si les deux droites de ces deux points s'intersectent dans l'espace (m, p), cela 
    signifie que ces deux points sont alignés dans l'espace (x, y). Nous répétons ce processus pour 
    tous les points de l'image et nous récupérons dans l'espace (m, p) les intersections des droites
    des points de (x, y) avec la valeur la plus grande. Enfin, nous traçons les droites sur l'image 
    à l'aide de l'équation yi = m*xi + p.
    La deuxième transformation de Hough travaille sur (r, theta) au lieu de (m, p). Elle transforme 
    chaque point de notre matrice en courbe sinusoïdale, puis les étapes suivantes sont les mêmes que
    celles de la transformation de Hough classique.


Expliquation de la première méthode :


       Le code définit une structure Point pour stocker les coordonnées d'un point dans un plan.
       La fonction trans_hough prend en entrée les coordonnées x et y d'un point dans une image,
       ainsi que la taille M de l'image, et retourne un vecteur D de taille M contenant les valeurs 
       de la transformée de Hough pour cette position. Cette fonction utilise la formule de la 
       transformée de Hough pour calculer les valeurs de D.
       La fonction Score prend en entrée un vecteur Droite et une matrice Mat, et met à jour les valeurs 
       de la matrice Mat en incrémentant de 1 les valeurs correspondant à la droite. Cette fonction est 
       appelée dans la boucle principale du programme pour incrémenter les valeurs dans la matrice de vote.
       La fonction main commence par initialiser les variables N et M à 10, et crée deux matrices image et
       Matrice_vote de taille N x M. La matrice image contient des valeurs binaires de pixels pour représenter
       une image. La matrice Matrice_vote est initialisée à zéro et sera mise à jour pour stocker les votes 
       pour chaque droite possible.
       Le code écrit également une image PPM de l'image originale dans le fichier "hough.ppm", qui peut être
       visualisée dans un éditeur d'image.
       La boucle principale du programme commence par parcourir tous les pixels de l'image, et pour chaque 
       pixel non nul, elle calcule le vecteur D de la transformée de Hough correspondant à ce pixel en 
       appelant trans_hough, puis met à jour la matrice de vote en appelant Score.
       Ensuite, la boucle principale recherche les points maximums dans la matrice de vote, stocke les
       coordonnées de ces points dans un vecteur de structures Point, et trace les droites correspondant 
       à ces points maximums dans l'image.
       Enfin, le code écrit une image PPM de l'image traitée avec les droites détectées dans le 
       fichier"hough_resultat.ppm".


Expliquation de la deuxième méthode :


      Dans ce cote on a créé  une structure de données appelée "Point" est définie pour
      *stocker les coordonnées d'un point dans l'image.
      Ensuite, une classe "HoughTransform" est définie pour stocker l'image et effectuer 
      la transformation de Hough.


      Le constructeur de la classe prend deux arguments, la largeur et la hauteur de l'image. 
      Il initialise ensuite la matrice de votes de Hough avec des zéros.
      Les paramètres "rho_max_" et "num_theta_" sont utilisés pour calculer les dimensions de la matrice.
      La méthode "addPoint" ajoute un point à l'image, tandis que la méthode "computeHoughTransform" 
      calcule la transformation de Hough en parcourant chaque point dans l'image.
      La méthode "saveImage" sauvegarde la matrice de votes de Hough dans un fichier au format PPM P3.
      Enfin, dans la fonction "main", un exemple d'utilisation de la classe est présenté. 
      Une instance de "HoughTransform" est créée avec une taille d'image de 50x50 pixels.
      Quatre points sont ajoutés à l'image, puis la transformation de Hough est calculée. 
      Enfin, la matrice de votes de Hough est sauvegardée dans un fichier appelé "matrice_final.ppm".
