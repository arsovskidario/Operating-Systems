# F1
  - hex dump od 8B pairs kude prv 4B e pozicija od kude pochnue chitanje na file i vtor 4B e kolko pozicie da chita
  - 0500 0000 e 5 pozicija u tj konkretan file (f2 e file ot 32bit broevi i zatoj se zimav po 4B)
  - 0200 0000 e 2 pozice na broj da chita od f2 

# F2
  - hex dump od 32bit brojke koi treba da se prochitva
  - 1200 0000  e broj 18 

# F3
  - rezultat gi ima svi broevi prochitani od f2 ss poziciju od f1 
 
# xxd -r f1.xxd f1  
  - convertira ga file od teskt hex dump   
