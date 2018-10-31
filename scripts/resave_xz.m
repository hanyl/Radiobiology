A=load("ED_Water.dat");

N_x = 50;
N_y = 50;
N_z = 300; 

B = [];

for index_x = 0:N_x-1
  for index_z = 0:N_z-1
     mask = (A(:,1) == index_x & A(:,3) == index_z);
     de = sum(A(mask,4));
     B = [B;index_x,index_z,de];
  endfor
endfor

A = B;

save -text ED_Water_octave.dat A;
