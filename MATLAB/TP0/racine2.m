%On demande un nombre a l'utilisateur
x = input('Entrez un nombre : ');
negatif = 0;

%On calcule la valeur absolue de ce nombre : s'il est negatif, on inverse
%son signe
if x < 0
    x = -x;
    negatif = 1;
end

%On place dans r1 la racine du nombre x
r1 = sqrt(x);
if negatif == 1
    r1 = r1*i;
end

%On affiche la valeur de r1
disp(r1);

%Et si x est différent de 0, on a une seconde racine r2 qui est l'oppose de r1 
if x>0
    r2 = -r1;
    disp(r2);
end