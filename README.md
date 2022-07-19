# Milionario
Gioco inspirato al gioco televisivo "Chi vuol essere milionario?"

## Descrizone
Il programma del milionario è stato sviluppato da Contarin Davide e Tomita Andrei nella prima meta dell'anno 2020.
Abbiamo preso spunto dalla trasmissione televisiva condo a da Gerri Scotti, chiamata “Chi vuol essere
milionario?”
Abbiamo cercato di realizzare un programma il più simile possibile alla trasmissione.
Abbiamo creato un programma che pone all’utente 15 domande di cultura generale e di diﬃcoltà
crescente.
Il programma visualizza la domanda seguita da 4 risposte.
Le risposte sono idenﬁcate da una lettera che le precede.
Per rispondere alla domanda l’utente deve cercare di rispondere alla domanda selezionando l’unica
risposta giusta, e premendo l’unica risposta corretta.
L’obbiettivo è certamente quello di rispondere correttamente al maggior numero di domande possibile.
Se l’utente ha un dubbio può premere il tasto “5” per uttilizzare l’opzione presa dal programma chiamata 50/50.
Questa opzione permette di cancellare 2 risposte sbagliate per lasciare come risposte quella corretta e una sbagliata.
Questo permette di dimezzare le possibilità di errore e, magari, con fortuna, di eliminare i dubbi.
Una volta aperto il programma c’è una schermata di benvenuto che introduce il programma e brevemente come approcciarsi al gioco.
Una volta uscitti da questa schermata iniziale premendo un qualsiasi tasto, il gioco inizia.
Esaminata la domanda e decisa la risposta, o eventuale 50/50, si preme il tasto corrispondente.
A seguito di una risposta ci sarà un’animazione simile a quella della trasmissione per indicare la risposta selezionata, e successivamente, a seconda della risposa giusta o meno segue una animazione diﬀerente.
Se la risposta è corretta la corrispondente casella si illuminerà di verde e passerai alla domanda successiva, in caso contrario la risposta selezionata di illuminerà di rosso, mentre quella corre a di verde.
Se perderai il programma farà vedere una schermata conclusiva.
Se riuscirai ad arrivare alla quindicesima domanda e rispondere corre amente il programma visualizzerà invece una schermata di vittoria.

## Sviluppo
Il programma è sviluppato in modo da poter funzionare alla stessa maniera sia su sistemti che usano Windows che Linux.
Attravero dei commandi per il pre-processore, vengono smistate le librerie a seconda del sistema operativo per il quale il programma vienne compilato.
Il programma, è sviluppato in modo da poter leggere da ﬁle una domanda per ogni livello, e le sue 4 risposte.
I ﬁle di testo sono dei file strutturati nel seguente modo:

    5
    Un chilometro equivale a:
    1000 metri
    100 metri
    10000 centimetri
    1000 decimetri

    Quale storica auto è stata riprodotta dalla FIAT nel 2007?
    500
    450
    1000
    650

    ...

La prima riga di ogni file indica il numero di domande presenti nel file. Le righe successive dovranno includere le domande, una risposta coretta , una risposta da mostrare nel caso si usi lopzione 50 e 50 e due risposte errate. tra ogni domanda e l'altra vi è uno spazio vuoto come mostrato nelle file di test mostrato sopra.

## Compilazione

Paccheti neccessari:
- **Linux**: gcc
- **Windows**: Visual Studio

**Linux**:
    ./build.sh

**Windows**:
    build.bat

## Esecuzione
    cd build
    /milionario
