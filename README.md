# GIMPteam

## ----- NOTA PER FAR FUNZIONARE LE LIBRERIE PER IL DATABASE E PER SQL ----- 
Attenzione:
le seguenti info sono per gli utilizzatori di Windows... Se stai utilizzando Linux, arrangiati, io ho già smanettato abbastanza...

1) Copiare le due librerie libmysql.dll e libmysqld.dll nel percorso ---> C:\Qt\5.12.3\mingw73_64\bin

2) Se non ancora presenti, aggiungere al file CMakelists.txt de progetto le seguenti linee di codice:	
			find_package(Qt5 REQUIRED COMPONENTS Core Quick Sql)
			find_package(Qt5Sql REQUIRED)
			target_link_libraries(nomeprogetto Qt5::Core Qt5::Quick Qt5::Sql)
