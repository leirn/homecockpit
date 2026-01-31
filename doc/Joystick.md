# Approche joysitck

L'objectif est de limiter le code côté PC. EN utilisant la librairie [Arduino Joystick](https://github.com/MHeironimus/ArduinoJoystickLibrary/tree/version-2.0)

## F16
- La librairie permet de définir plusieurs Joystick. Il faut détecter si un module est branché sur un port en particulier, et si oui déclarer le module correspond.
    - Est-il possible de détecter quel module est branché ? Oui, il exsite plusieurs options, mais pas certain desquelles sont les bonnes pour moi, pour limiter la complexité
        - La version "lire une valeur avec une résistance" porurait fonctionner, seule la carte multifonction n'a pas de port dispo, mais justement elle sortira du lot. Il faut juste pouvoir la différencier d'une prise vide, à tester


> 1. Résistance d’identification (ID resistor)
> C’est la méthode la plus utilisée dans les systèmes modulaires low‑cost (ex : batteries, capteurs interchangeables, accessoires propriétaires).
> Principe
> Chaque module contient une résistance de valeur unique entre une broche dédiée et la masse.
> Sur la carte principale, tu lis cette broche via une entrée analogique.
> Exemple
> - Module A → résistance 1 kΩ
> - Module B → résistance 4.7 kΩ
> - Module C → résistance 10 kΩ
> L’Arduino lit une tension différente selon le module branché → tu identifies immédiatement lequel c’est.
