# Circuit dédié à l'allumage des boutons

## Caractéristiques

- Alimentation VLed 12V
- Arduino alimenté par Vin
- 3 leds par lignes
- 24 lignes = 72 boutons

# Répartition des besoins en TA18040

- Chaque GDU : 12 boutons = 4 lignes. Total de 8 lignes
- PFD/MFD multi : 8 boutons = 3 lignes
- Radio : 4 boutons = 2 ligne
- Audio : 12 boutons = 4 lignes
- AP : 14 boutons = 5 lignes

Total = 22 lignes. Fonctionne avec un seul TLC5947

# Répartition des besoins en led pour textes

Premier problème : identifier les bonnes LED, en termes de tension, de courant, et surtout de luminosité...