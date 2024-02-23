# SLUG-the-game
Questo progetto prevede l'implementazione di un gioco platform con grafica ASCII, caratterizzato da più livelli, un sistema di punteggio e un protagonista controllato tramite tastiera. La mappa, esplorata dal giocatore, offre un'esperienza dinamica senza traguardi fissi. Il protagonista può tornare indietro nella mappa, trovando tutto esattamente come lo ha lasciato.

Il gioco include diversi tipi di nemici e artefatti, e per passare da una stanza all'altra è necessario raccogliere artefatti o sconfiggere nemici. Inoltre, il giocatore può trovare "poteri" che sbloccano passaggi verso artefatti nascosti. Il punteggio è gestito manualmente dal giocatore umano che controlla il protagonista, creando un coinvolgente mix di strategia e abilità nel superare sfide e accumulare punteggi sempre più alti.

I  punti vita cambieranno costantemente durante il gioco, in seguito all'incontro di artefatti che aggiungono, o di nemici che detraggono punteggio. Questo e i ripettivi cuori (<3) saranno sempre visibili sotto la finestra di gioco

Ci sono più tipi di nemici che si possono incontrare:

uno statico che rimane sempre nello stesso punto, che detrae 10 punti vita;
uno randomico che si muove nella satnza in maniera casuale, che detrae 50 punti vita;
uno mirato verso l'eroe, che lo rincorre per la stanza, che detrae altrettanto 50 punti vita. Tutti e tre questi tipi saranno in grado di sparare verso il nemico per sottrargli dei punti.
A volte sarà necessario, per proseguire nel gioco, raccogliere le chiavi "k" per aprire delle porte (XXX) che altrimenti da chiuse ostacolerebbero il percorso.

L'eroe continuerà ad andare avanti nelle stanze fino a quando i punti vita saranno finiti. A quel punto l'eroe sarà morto ed il gioco finito, ed apparirà una finestra che comunicherà al giocatore di aver perso.

## Autori
Chiara Tosadori,
Alice Marinelli,
Simona Paparesta,
Annamaria Carriello.

## Info
Per far avviare il progetto è necessario scaricarne il file .zip integralmente ed estrarlo in una cartella designata; dopo, aprire la stessa nel terminale e inviare prima "make main" e, quando ha terminato, "make run" per farlo partire.

Il terminale si aprirà sul menù del gioco, controllato attraverso la tastiera, ovvero le freccette e il tasto invio.

Al selezionamento di "start" inizierà la partita vera e propria. A questo punto si potranno controllare i movimenti dell'eroe attraverso le quattro freccette per spostarsi e "W" "A" "S" "D", per sparare nelle quattro direzioni, rispettivamente Nord, Ovest, Sud, Est.

