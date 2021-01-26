
Elemente de Grafica pe Calculator

[# Laboratoare EGC](https://github.com/user/repo/blob/branch/other_file.md)
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
    
### Laborator 4

    * Completați funcțiile de translație, rotație și scalare din /Laborator4/Transform3D.h.
    * Să se realizeze animații la apăsarea tastelor (în OnInputUpdate) pentru cele 3 cuburi, astfel:
          - cu tastele W, A, S, D, R, F să se deplaseze primul cub în scenă.
          - cu tastele 1 și 2 să se scaleze al doilea cub (să se mărească și să se micșoreze) față de centrul propriu.
          - cu tastele 3, 4, 5, 6, 7, 8 să se rotească al treilea cub față de axele locale OX, OY, OZ.
          
### Laborator 5

    * Să se implementeze camera de tip First Person (fișierul LabCamera.h).
    * Să se implementeze camera de tip Third Person (fișierul LabCamera.h).
    * Să se completeze funcțiile de translație ale camerei din Laborator5::OnInputUpdate().
    * Să se completeze funcțiile de rotație ale camerei din Laborator5::OnMouseMove().
    * Să se deseneze încă 2 obiecte în scena 3D având rotația/scalarea/translația diferite.
          - aveți grijă să setați matricea de modelare de fiecare dată înainte de desenare
          - utilizați glm::translate(), glm::rotate() și glm::scale() pentru a construi o matrice de modelare pentru fiecare obiect
    * Schimbare proiecție perspectivă/ortografică.
          - tasta O face trecerea în proiecție ortografică.
          - tasta P face trecerea în proiecție perspectivă.
    * Să se modifice FoV-ul camerei în cazul proiecției persepective.
          - folosiți 2 taste pentru a modifica pozitiv și negativ FoV-ul.
          - se va folosi OnInputUpdate().
    * Să se modifice lățimea și/sau înălțimea ferestrei de proiecție în cazul proiecției ortografice.
          - se va folosi OnInputUpdate().
          
### Laborator 6

    * Completati functia RenderSimpleMesh astfel inca sa trimiteti corect valorile uniform catre Shader.
    * Completati Vertex Shaderul.
    * Completati Fragment Shaderul.
    * Sa se utilizeze normala vertexilor pe post de culoare de output in cadrul Fragment Shader-ului.
    * Sa se interschimbe pipe-ul 1 cu pipe-ul 3. Trimiteti normala pe pipe-ul 3 si culoarea vertexului pe pipe-ul 1.
    ** sa se trimita timpul aplicatiei (Engine::GetElapsedTime()), si sa se varieze pozitia si culoarea (unul sau mai multe canale de culoare) dupa o functie de timp (trigonometrica etc.)
    
### Laborator 7

    * Completați funcția RenderSimpleMesh astfel încât să trimiteți corect valorile uniforme către Shader:
    * Implementați iluminarea în Vertex Shader.
    * Completați fragment shader-ul astfel încât să aplicați iluminarea calculată în Vertex Shader.
    * Colorați sfera și planul din scenă (de ex: sfera - albastru, planul - gri).
    
### Laborator 8

    * Sa se implementeze iluminarea de tip Phong in Fragment Shader.
    * Atunci cand se apasa tasta F sa se treaca in modul de iluminare Spot-light.
    ** Sa se modifice directia si unghiul de cut-off al luminii spotlight de la tastatura.
    ** Modelul de iluminare Phong, folosind 3 canale de culoare.
    
### Laborator 9 

    * Completati functia RenderSimpleMesh astfel incat sa trimiteti corect textura catre Shader.
    * Completati coordonatele de textura pentru patrat.
    * Completati shaderele astfel incat sa foloseasca coordonatele de textura.
    * Sa se completeze shaderul astfel incat sa se faca alpha discard.
    * Creati si incarcati pe GPU o textura random.
    * Modificati filterele GL_TEXTURE_MIN_FILTER si GL_TEXTURE_MAG_FILTER si observati diferentele de afisare.
    * Randati un quad folosind 2 texturi. Folositi functia mix() in fragment shader pentru a obtine o combinatie intre cele doua texturi.
    
