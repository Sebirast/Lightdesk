# Lightdesk - EF Projekt
## Ziel
- Problem mit dem Encoder beheben
- Shows hinzufügen. So dass Shows gespeichert werden können und danach auch wieder geöffnet werden können (nach dem Abschalten des Stroms)

## Methoden
1. Das Problem mit dem Encoder probierte ich durch vertieftes Lesen des Codes zu verstehen und zu lösen. Ich habe einige Anpassungsmöglichkeiten für die Encoder gefunden.
2. Um Shows zu speichern und wieder aufzurufen benutzte ich den eingebauten SD-Slots des Teensys. Somit werden die Daten, die für die Speicherung nötig sind auf diese SD geschrieben. Das Aufrufen der Daten musste dann extrem genau geregelt werden, damit die richtigen Zahlen wieder am richtigen Ort landeten.

## Hardware
Die Verkabelung kann dem Lightdesk.pdf (im Ordner schematics) entnommen werden.

## Fazit
1. Das Problem mit dem Encoder konnte vermeintlich gelöst werden. Es trat aber wieder auf, als das Lichtpult in der Aula im Einsatz war. Als nächstes würde ich den Encoder auswechseln somit de Lötstellen besser machen. Somit kann es zumindest nicht mehr an der Hardware liegen. Falls es dann immer noch Probleme geben würde, würde ich probieren die Library für den Encoder Input selber zu schreiben.
2. Es konnte ein System für die Speicherung von Shows eingebettet werden. Dieses konnte jedoch nie in einem realen Szenarion gestest werden, da das Lichtpult momentan nicht funktioniert. Daher habe ich einen Testaufbau gemacht, wobei nur die grundlegensten Funktionen getestet werden konnten.

## Relevante Files für dieses Probjekt
Der ganze neugeschriebene Code kann in den folgenden Files gefunden werden:
- showController.h / showController.cpp
- cue.h
- parameterMenu.h (neue Menü-Defintionen)
- playback.cpp