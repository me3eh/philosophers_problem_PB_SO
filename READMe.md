Problem pięciu filozofów

1. Napisz rozwiązanie problemu pięciu filozofów z możliwością blokady. Zaimplementuj pięć widelców przy pomocy pięcioelementowej tablicy muteksów (funkcje pthread_mutex_lock i pthread_mutex_unlock). W rozwiązaniu tym filozof o numerze i=0...4 podnosi najpierw widelec lewy (o numerze i) a następnie widelec prawy (o numerze (i+1)%5). Zademonstruj prowadzącemu wystąpienie zjawiska blokady.

2. Zmodyfikuj rozwiązanie zadania 1 przez wprowadzenie asymetrii. Niech jeden z filozofów (np. o numerze zero) próbuje podnieść najpierw prawy, a następnie lewy widelec. Czy przy takim rozwiązaniu może wystąpić blokada? Czy może wystąpić zagłodzenie ?
