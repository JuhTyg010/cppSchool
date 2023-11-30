# Špecifikácia zápočtového programu
## Autor
Meno: Marek Sádovský
## Téma
(pseudo)3D hra (na štýl doom) jde o real-time vykreslovanie. Celá hra pracuje na jednej výške.
to zaručuje, že ju vieme previesť na top-down hru s objektamy. Steny (v top-down štvorce) 
sa nám vykreslia na základe raycastingu (player "vyšle" lúče na základe uhlu v ktorom 
vidí a dostane odpoveď v akej vzdialenosti je stena odd čoho závisí jej výška a farba v 3D). Prípadne dať vzdialenostný limit čili ak moj ray nenájde stenu do nejakej dĺžky tak tam bude tma a nedovidíme. 

## Popis
-First person pohlad. Mechanika na otáčanie sa a na chôdzu vpred a vzad pomocov wasd.
-V hre sa budú nachádzať itemy, itemy sa budú dať zobrať po stlačení special key
ktorý bude neskôr špecifikovaný. Itemy budú naprogramované všeobecne ale budú existovať
aj konkrétne itemy so špeci vlastnosťami(napr. kľúče).
-Ciel je nájsť a pozbierať špeci itemy a nájsť východ ktorý sa otvorí až keď mame itemy. 
-Mapa bude editovatelná definovaná nejakým pekným txt filom. Momentálny plán je vyrobiť 
nejaký map editor. V neskoršej verzí možno nejaké automatické generovanie konečných máp 
pomocou Randomized depth-first search nebe Kruskal's algorithm
Prípadne automatické ukladanie itemove na mapu. Tak že žiadne dva itemy nie sú na jednej pozícii.
Pomocou nejakej random funkcie.
## Knižnice
Program by mal používať štandartné knižnice pre matematiku, random či čítanie mapy a sfml knižnicu na kreslenie
