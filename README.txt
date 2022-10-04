README

Structura TInreg va retine key si value pt fiecare elemnt dintr-o lista
functia codhash calculeaza suma elementelor si returneaza codul hash
functia citesteListaInreg este cea in care au loc rezolvarile comenzilor citite din fisier
deschidem fisierele din care citim si in care vom afisa
citim linie cu linie din fisier 
pt cazul in care se citeste print de la tastatura vom parcurge toate elementele din vectorul v din tabela hash
parcurgem toate elementle fiecarei liste si le afisam in fisier
functia put foloseste strtok pentru a determina key si value le introduce intr-o structura
TInreg si o trimite ca parametru functiei InsTH
In cazul comenzii remove generam codul hash si eliminam pe cazuri conform comentariilor din cod
in cazul in care elementul care trebuie eliminat nu se afla in lista nu se va face nicio modificare
In cazul comenzii print_bucket ne asiguram ca valoarea primita nu depaseste nr maxim de elemente ale tab hash
si afisam elementele listei primite ca parametru la citire; daca lista resp este goala afisam VIDA
In cazul com find vom determina codul hash si vom cauta key in lista coresp
In cazul in care lista nu e vida verificam daca primul element e cel cautat daca nu vom
parcurge lista in incercarea de a gasi elementul; dca il gasim afisam true, in caz contrar fals
Pt get vom determina codul hash coresp lui key, parametrul primit, si vom verifica daca se afla
pe prima pozitie din lista corespunzatoare. Daca aceasta conditie este indeplinita vom afisa valoarea
lui value a elementului si in caz contrar vom parcurge toata lista in incercarea de a gasi elementul cautat
Daca il gasim vom afisa value, in caz contrar afisam NULL

Functia InsLG realizeaza inserarea in lista; ea verifica daca elementul pe care dorim sa-l inseram se afla deja in 
lista si realizeaza inserarea pentru a mentine ordinea alfabetica a elementelor; mai multe detalii in
comentariile din cod
Functia IniTH realizeaza initializarea tabelei hash; aloca memoria necesara si pune in h->M nr maxim
de elemente si in h->fh functia de generare a codului hash

InstTh determina codul hash si apealeza functia de inserare in lista
