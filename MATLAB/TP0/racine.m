%On demande un nombre a l'utilisateur
x = input('Entrez un nombre positif ou nul : ');

%On place dans r1 la racine du nombre x
r1 = sqrt(x);


disp(r1);

 
if x>0
    r2 = -r1;
    disp(r2);
end