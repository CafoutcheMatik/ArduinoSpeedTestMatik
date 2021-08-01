# Temps d'éxécution des instructions du MÉGA2560 rev 3 #

## But ##
Déterminer le temps des différentes instructions d'un Arduino MÉGA2560 dans le cadre d'un projet de séquenceur hardware
nécessitant l'acquisition de +500 boutons équipés de led et de +70 potentiomètres.

Le but n'est pas de comparer la vitesse de différents Arduino mais d'estimer le temps probable des instructions

## Configuration ##
_#define PIN_ENTREE_PULLUP 13_       // PIN configurée en entrée avec PullUp interne

_#define PIN_ENTREE 12_              // PIN configurée en entrée

_#define PIN_SORTIE 11_              // PIN configurée en sortie

_#define SERIAL_SPEED_HIGH 250000ul_ // sur ce projet 250000bauds

_#define SERIAL_SPEED_LOW 9600_     // bauds trés lent

_#define NB_BOUCLE 10000_           // la mesure de temps à la micro seconde sur Méga

_#define DELAY_PRINT 0_             // pour laisser le temps de vider le buffer en millis


## Particularité ##
On utilise la commande de précompilateur _#pragma GCC optimize("-O0")_
afin d'interdire les optimisations de code qui pourrait fausser les résultats.
