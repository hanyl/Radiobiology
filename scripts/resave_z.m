A=load("ED_Water.dat");

N_x = 50;
N_y = 50;
N_z = 300; 

B = [];

for index_z = 0:N_z-1
     mask = ( A(:,3) == index_z);
     de = sum(A(mask,4));
     B = [B;index_z,de];
endfor

plot(B(:,1),B(:,2));

print("de_z.eps",'-color');


A = B;

save -text ED_Water_z.dat A;
