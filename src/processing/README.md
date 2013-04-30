Processing
==========
moti.pde
--------
Pour utiliser moti.pde ouvrez le avec processing, il est possible que rien ne se passe et dans ce cas il y a deux explications possible :
* Installez les librairies nécéssaire en suivant ce tutoriel : http://playground.arduino.cc/interfacing/processing
* Modifier le port (par défaut 0) à la ligne 26, pour savoir quel port est le bon tapez : `println(Serial.list());` vous pourrez ensuite choisir le votre

Une fois que c'est réglé appuyez sur play et c'est parti !
post_moti.pde
-------------
Pour utiliser moti.pde ouvrez le avec processing, si vous avez précédement utilsé moti.pde le programme aura automatiquement créé un fichier txt dans le dossier log.
Renommez le fichier qui correspond au test que vous voulez visualiser de nouveau (car c'est très vite embêtant de taper des timestamp sans copier coller...) puis executez post_moti.pde, entrez le nom du fichier à consulter sans ajouter le `.txt` et régalez vous !

