# GIMPteam

## ----- NOTA PER FAR FUNZIONARE LE LIBRERIE PER IL DATABASE E PER SQL ----- 
Attenzione: le seguenti info sono per gli utilizzatori di Windows... Se stai utilizzando Linux, arrangiati, io ho già smanettato abbastanza...

Copiare le due librerie libmysql.dll e libmysqld.dll nel percorso ---> C:\Qt\5.12.3\mingw73_64\bin 

## ----- NOTA PER IMPORTARE IL DB -----
1) Aprire XAMPP
2) Cliccare su "Start" nelle prime due righe (i due "Start" relativi a "Apache" e a "MySQL")
3) Nella riga relativa a "MySQL" cliccare "Admin"
4) Si aprirà una schermata nel browser... Nella barra in grigio a SX cliccare su "Nuovo"
5) Scrivere "gimpdocs_db" e cliccare su "Crea"
6) Il nuovo DB appena creato verrà visualizzato sempre nella barra grigia a SX... Cliccare sopra al nuovo DB appena creato
7) Ora... C'è una barra in alto con le scritte "Struttura, SQL, Cerca, Query da esempio etc"... Cliccare sulla sesta, cioè "Importa"
8) Cliccare su "Sfoglia" e scegliere il file dal nome "gimpdocs_db.sql" che io, Ilaria Gioda, ho caricato qui su Git nella cartella "FileUtili"
9) Cliccare sul pulsante "Esegui" al fondo della pagina
10) Controllare che siano sbucate fuori le tabelle nel DB... Se non sono sbucate fuori, non bestemmiate, scrivetemi, ci facciamo un pianto assieme e poi capiamo cosa è andato storto
	
## ----- NOTA PER FAR FUNZIONARE LE COSE IN CLION -----
0) Se non lo si è ancora fatto, vedere ----- NOTA PER IMPORTARE IL DB -----
1) Aprire XAMPP
2) Cliccare su "Start" nelle prime due righe (i due "Start" relativi a "Apache" e a "MySQL")
3) Aprire CLion
4) Creare un nuovo progetto in CLion e chiamarlo "gimpdocs"
5) Prendere i file, CMakeLists.txt compreso (molto importante!), e copiarli nella cartella del nuovo progetto creato
6) Buildare, runnare e far sì che la magia avvenga nella console

## ----- NOTA PER FAR FUNZIONARE LE COSE IN QTCREATOR -----
0) Se non lo si è ancora fatto, vedere ----- NOTA PER IMPORTARE IL DB -----
1) Aprire XAMPP
2) Cliccare su "Start" nelle prime due righe (i due "Start" relativi a "Apache" e a "MySQL")
3) Aprire QtCreator
4) Creare un nuovo progetto 
5) Aggiungere i file .cpp e .h al progetto cliccando sul progetto, tasto DX, "Add Existing Files..."
6) Aggiungere al file .pro la riga ---->   QT += sql
