# TDL

Ce projet vise à fournir une interface pratique pour gérer sa "to do list" depuis son ordinateur.

Deux modes de fonctionnement son prévus : mode console et mode graphique.

# Mode Console 

Dans ce mode tout se gère depuis la console. Le principe de fonctionnement est simple : vous entrez les instructions à la suite et l'interface les traites une à une. Les différents arguments et valeurs doivent être entrés.

Vous verrez affiché l'instruction suivante : " >>>instruct "" et vous entrerez votre fonction et ses arguments à la suite. Vous appuyerez sur la touche ENTREE. L'instruction se lancera et vous pourrez en effectuer une à la suite. 

## Entrer des instructions

Afin de vous faire comprendre de l'API vous devez suivre un protocole. Le premier mot que vous entrez doit être la fonction que vous voulez éxécuter. A la suite vous pouvez mettre les arguments de votre fonction, repérés par des '--' avant l'argument. Par exemple si un argument est le titre vous mettrez '--title'. Après un argument l'API lira ses valeurs, et passera à l'argument suivant en lisant la prochaine occurence des caractères '--'. 

### Différent arguments

- title : repère le titre
- description : repère la description
- begin : repère le début de la tâche
- end : repère la fin de la tâche
- progress : repère le progrès de la tâche. Les valeurs compatibles avec cet argumement sont 0 pour une tâche ouverte, 1 pour une tâche en progrès et 2 pour une tâche fermée
- avancement : repère l'avancement de la tâche. Les valeurs compatibles avec cet argument sont les entiers
- priority : repère la priorité de la tâche. Comme pour le progrès les valeurs compatibles sont 0 pour une priorité faible, 1 pour normale, 2 pour haute et 3 pour super haute.
- comments : repère les commentaires. Pour séparer deux commentaires il faut mettre le caractère '^'.
- under : donne les IDs des sous tâches de cette tâche.

## Utilisation des fonctionnalités

4 fonctionnalités sont disponibles : créer, modifier, lister, supprimer.

### Créer

Pour créer une nouvelle tâche, vous devez entrer le mot "create" au début de votre instruction.

