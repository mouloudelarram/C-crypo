%La matrice note (vecteur ligne) contient toutes les notes de la classe
note = [4.5 7 12 3.5 14.5 16 12 12 8 9.2];
nom = {'Eric','Sarah','Andrew','Omar','Marwa','Alex','John','Mahdi','Laurent','Clemence'}

%On calcule la moyenne de la classe
somme = sum(note);
moy = somme/numel(note)

disp('La moyenne de la classe est ');
disp(moy);


%On calcule le nombre de notes supérieures à 10
note_superieur_10 = (note >= 10);
nb_note_sup_10 = sum(note_superieur_10);

disp('Le nombre de notes au-dessus de 10 est ');
disp(nb_note_sup_10);


%On affiche les noms des élèves qui ont une note supérieure à 10
indice_note_sup_10 = find(note_superieur_10);
noms_bons_eleves = nom(indice_note_sup_10);

disp('Les bons eleves sont')
disp(noms_bons_eleves)