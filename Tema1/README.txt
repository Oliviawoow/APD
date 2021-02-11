Oprea Olivia Maria-Magdalena 333CA Tema1

Eu am gandit aceasta problema in felul urmator:
Deoarece se doreste ca mai intai sa se execute algoritmul Julia apoi algoritmul
Mandelbrot, m-am gandit ca mai intai ar trebui sa se termine complet de executat
primul algoritm ca mai apoi sa se execute cel de al doilea. In consecinta am decis
sa folosesc 2 bariere. Unul dupa executarea algoritmul Julia si cel de al doilea
dupa executarea algoritmul Mandelbrot.
Am creat ca in laboratoare o bariera barrier si thread-urile in functia main.
Am lasat in main ceea ce se executa o singura data cum ar fii functia de read
si calcularea width-ului, height-ului si rezultatului pentru inceput, deoarece 
nu are nici un sens sa se execute acestea pe fiecare thread. De asemenea am lasat
in main si transformarea rezultatului din coordonate matematice in coordonate
ecran, considerand ca se vor executa o singura data la final dupa ce avem 
rezultatul final al fiecarui algoritm. Si de sigur avem tot in main functia de 
write si de eliberare de memorie deoarece si acelea trebuie sa se execute o singura
data pentru eficienta.
In functia creata de mine, thread_function, imi calculez start si end pentru a le 
putea folosii in functia de run al fiecarui algoritm pentru a pareliza unul din
for-uri pentru a creste eficienta si a calcula pe thread-uri. De asemenea tot in 
functia thread_function am apelat si functiile de run ale algoritmilor.
Barierele au fost folosite una dupa ce am dat run algoritmul Julia pentru a astepta
sa se termine complet de executat, iar ce-a de a 2a bariera a fost folosita dupa
ce am dat run algoritmul Mandelbrot din aceelasi motiv, ca atunci cand se termina
complet sa avem rezultatele finale corecte ale celor 2 algoritmi fara a avea conditie
de cursa sau sa se distruga rezultatele scriindu-se unde nu trebuie.
Am mai modificat si functia get_args pentru a introduce P.
Am citit pe moodle si am schimbat si niste pow-uri in run_julia si run_mandelbrot
pentru eficienta si am vazut ca da acceleratia mai mare.