# Projekt 1 - Problem Ucztujących Filozofów

#### [Ścieżka do .cpp](https://github.com/sevna90377/sysop2/blob/main/Dining_philosophers/Dining_philosophers/Dining_philosophers.cpp)

### Instrukcja uruchomienia:
w lokalizacji pliku .exe

  (linux)
```
./Filozofowie <liczba filozofów> 
```
  (windows) 
```
  Filozofowie.exe <liczba filozofów> 
```

## Opis problemu
Początkowo opisywany dla pięciu filozofów problem obrazuje zjawisko zakleszczenia przy współdzieleniu zasobów przez wiele procesów.

Między filozofami znajduje się w sumie pięć widelców, jednak każdy z filozofów do spożywania potrzebuje ich dwóch. Po każdej stronie filozofa jest jeden widelec, a siedzą oni w kręgu, tak że między każdą parą filozofów znajduje się jeden widelec. Ławtwo zauważyć, że powstanie w tym układzie pewna konkurencja o dostęp do widelców.

Filozofowie w nieregularnych interwałach jedzą (co jest poprzedzone próbą zdobycia dwóch widelców) oraz rozmyślają. Filozofowie jednak nie komunikują się ze sobą, a po zdobyciu jednego sztućca nie ustępują go sąsiadom, aż nie skończą jeść.
Wynika z tego, że próba podjęcia przez każdego filozofa w tym samym czasie lewego widelca doprowadzi do sytuacji, w której żaden z nich nie będzie mógł uzyskać prawego zasobu i odwrotnie.

Jednym z naturalnych rozwiązań jest wprowadzenie "poddawania się" filozofów, tj. rezygnowania z widelca, gdy oczekiwanie na drugi trwa zbyt długo. Dzięki temu, któryś z filozofów może zmienić swój stan również w sytuacji deadlock'a (zakleszczenia). Nie zabezpiecza on jednak 

## Wątki
W programie pojawiają się wątki filozofów. Obiekty klasy `Philosophers` pracują współbieżnie symulując różne stany filozofów.

## Sekcje krytyczne
Reprezentuje je klasa `Fork`, w której pojawia się obiekt `std::mutex`. Filozofowie, kiedy tylko widelec nie jest w użyciu, blokują jego dostępność dla innych wątków. Po określonym czasie pożywiania, zasób jest zwalniany umożliwiając dostęp innym filozofom. W implementacji nie ma bezpośrednich zabezpieczeń przed głodzeniem lub zakleszczaniem wątków. Unika się tych sytucji dzięki zaproponowanemu rozwiązaniu.

Kolejną sekcją krytyczną jest wypisywanie przez wątki komunikatów na ekranie. Jednoczesny dostęp do wspólnego zasobu, jakim jest okno konsoli, spowodowałby mieszanie się przekazywanych wartości i zniekształcenia niwelujące czytelność komunikatów.

## Rozwiązanie
W niniejszym kodzie zastosowane zostało rozwiązanie przy użyciu hiearchii zasobów. Dowolny z filozofów (w tym przypadku dla prostoty jest to "ostatni") jako jedyny ma odwrotną kolejność podejmowania widelca. Ponadto, zasoby zwalniane są w kolejności odwrotnej od ich zajmowania. Pierwsza kwestia zabezpiecza przed zakleszczeniem, druga zaś zmniejsza głodzenie wątków.
