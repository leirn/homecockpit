# Architecture générale

## F-16 / F-18

- Connexion au PC réalisé par le module Core, qui peut contenir un arduino format Nano, configuré comme un périphérique USB Device Input de type Joystick
- 4 ports RJ45 dispos pour des modules additionnels, de type F16 CMFD

## Avion Civil

- Connexion au PC réalisé par le module Core, qui peut contenir un arduino format Nano, configuré avec un protocol d'échange spécifique pour mettre de fournir des données bidirectionnelles
- 4 ports RJ45 disponibles
    - 1x Module multifonction
    - 2x GDU Softkey
    - 1x Lghts and systems

# Hardware components decription

Synthèse :

| Composant | PCB | Status | 3D Model | Status |
|-----------|-----|--------|----------|--------|
| Core       | F16-18-Core |  A vérifier | ? | ? |
| F16 CMFD / DDI      | F16-18-DDI |  A vérifier | ? | ? |
| GDU       | Small_Softkey_Core |  A vérifier | ? | ? |
| Multifonction       | Small_full_WS2811 |  A vérifier | ? | ? |
| Systèmes | Systems_light | Suspendu | ? | ? |
| Lumières | Systems_light | Suspendu | ? | ? |

## Core

### PCB

F16-18-Core :

- Status : terminé, à vérifier, en particulier le refroidissement du convertisseur de tension

### 3d print

- Status : modèle 3D à réaliser

## F16 CMFD

### PCB

F16-18-DDI :

- Status : terminé, à vérifier

### 3d print

- Status : modèle 3D à réaliser


## GDU

### PCB

Small_Softkey_core : nouvelle version RJ45

- Status : terminé, à vérifier

### 3d print

- Status : modèle 3D à réaliser

## Multifonction

### PCB

Small_full_WS2811 : 

- Status : terminé, à vérifier

### 3d print

- Status : modèle 3D à réaliser

## Systèmes / lumières

### PCB

Pas de PCB eistant en RJ45 à date. Nécessiterait une carte unique et commune pour n'utiliser qu'un seul RJ45, sauf à modifier soft key

Status : en pause, status systèmes en partie sur full WS2811

### 3d print

- Status : Sans objet
