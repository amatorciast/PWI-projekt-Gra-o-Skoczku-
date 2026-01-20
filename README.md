
Ten projekt jest grą. Gracz wciela się w konia na szachownicy 8×8, który w każdej turze jest atakowany przez inne figury szachowe.
Celem gry jest przetrwać jak najdłużej i zdobyć jak największy score.

Projekt można podzielić na trzy główne części:

1) Praca z terminalem, wykorzystanie znaków Unicode w celu uzyskania czytelniejszego i ładniejszego widoku.
2) Interfejs użytkownika oraz logika ruchu gracza i przeciwników.
3) Praca z plikami, w tym zapisywanie i wczytywanie stanu gry oraz wyniku.

Aby uruchomić projekt, można skorzystać z gotowych plików gra.exe (Windows) lub gra.out (Linux), albo skompilować projekt samodzielnie.
W tym celu należy przejść do katalogu origin i użyć polecenia "gcc *.c" (lub innego kompilatora języka C).

Zasady ruchu są takie same jak w szachach. Dla każdej możliwej opcji ruchu przypisana jest odpowiednia litera:

   8   1
 7       2
     0
 6       3
   5   4


0 – pominięcie tury
p – pauza

Aby zmienić sterowanie, należy edytować plik set_input.h i zmienić przypisane znaki.

w menu mozna poruszac sie 'a' i 'd', i wybrac opcje spacja. lub tez mozna wpisac numer opcji liczac od 0.

Twórcy:
Gabriel Miś
Alan Drab
Andrei Dzhura
Jakub Sroka
Kacper Niebrzydowski
Natalia Piątek
