# Laboratoare EGC
Elemente de Grafica pe Calculator

### Laborator 1
  
    * Încărcați un alt model 3D și randați-l în scenă la o poziție diferită față de cele 2 cuburi.
    * La apăsarea unei taste să se schimbe culoarea de ștergere a ecranului.
    * La apăsarea unei taste să se schimbe obiectul afisat (render) la o poziție (să cicleze prin 3 obiecte, de ex cube, teapot, sphere).
    * Să se miște prin spațiu un obiect oarecare la apăsarea tastelor W, A, S, D, E, Q (pozitiv și negativ pe toate cele 3 axe)
    ** La apăsarea unei taste să se roteasca un obiect in jurul centrului (x, y, z) = (0, 0, 0)

### Laborator 2

    * Completați geometria și topologia unui cub: vectorii de vertecși și indecși din inițializare. VertexFormat este o structură pentru vertex cu 2 parametrii (poziție, culoare).
    * Completați funcția Laborator2::CreateMesh astfel încât să încărcați geometria pe GPU.
    * Creați o nouă formă geometrică simplă, de exemplu un tetraedru și desenați-l în scenă.
    * Atunci când se apasă tasta F2 faceți toggle între modul de culling GL_BACK și GL_FRONT.
    * Creați un pătrat format din 2 triunghiuri astfel încât fiecare triunghi să fie vizibil doar dintr-o parte.
    ** Construiti un cerc.
    
### Laborator 3

    * Completați funcțiile de translație, rotație și scalare din /Laborator3/Transform2D.h .
    * Să se modifice pașii de translație, rotație și scalare pentru cele trei pătrate ca să se creeze animații.
    * Cu tastele W, A, S, D să se translateze fereastra logică Laborator3_Vis2D. Cu tastele Z și X să se facă zoom in și zoom out pe fereastra logică.
    ** Sa se formeze un cub care se roteste la 180 miscanduse pe scena.
