function [Bz,Br]  = magnet_rho (z,r, z0,R,I)
    mu = 4 * pi * 1.0e-7;
    
    L = z - z0;
    RR = power(R,2) + power(L,2);

    Br = 3./2 * r * L * power(RR,-5./2) \
       + power(r,3)/128. * (360. * L * power(RR,-7./2) \
             - 840. * power(L,3) * power(RR,-9/2)) \
       - power(r,5)/128. * (525. * L * power(RR,-9./2) \
             -3150. * power(L,3) * power(RR, -11./2) \
             + 3465. * power(L,5) / power(RR,-13./2));

    Bz = 1./power(RR,3./2) \
       + power(r,2)/256. * (192. * power(RR,-5./2) \
           - 960. * power(L,2) * power(RR,-7./2)) \
       + power(r,4)/256. * (180. * power(RR,-7./2) \
           - 2520 * power(L,2) * power(RR,-9./2) \
           + 3780. * power(L,4) * power(RR,-11./2)) \
       + power(r,6)/256. * (175. * power(RR,-9./2) \
           - 4725 * power(L,2) * power(RR,-11./2) \
           + 17325 * power(L,4) * power(RR,-13./2) \
           - 15015 * power(L,6) * power(RR,-15./2));

    Br *= mu/2.0*I*R*R;
    Bz *= mu/2.0*I*R*R;

endfunction

Z = [-2,-1,0,1,2,3,4,5,10,15,20,25]*1e-2;  # meter
R = [5,5,5,5,5,5,5,10,15,15,15,15]*1e-2; # meter
I = [8.45e5,-7.e4,-7.e4,-7.e4,-3.e4,-2.e4,3.5e4,3.5e4,3.5e4,3.5e4,2.5e4,2.0e4];

B = [];
r = 0.01 * sqrt(2);

for z = (0:0.02:20)*1e-2
  Bz = 0;
  Br = 0;
  for i = 1:length(Z)
      [bz,br] = magnet_rho(z,r,Z(i),R(i),I(i));
      Bz += bz;
      Br += br;
  endfor

  B = [B;z,Bz,Br];
endfor

save("field_calc_coil.dat",'B');
