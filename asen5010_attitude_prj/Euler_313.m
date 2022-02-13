function [ DCM ] = Euler_313( Omega, i, theta )

DCM = [cos(theta)*cos(Omega) - sin(theta)*cos(i)*sin(Omega), cos(theta)*sin(Omega)+ sin(theta)*cos(i)*cos(Omega), sin(theta)*sin(i);
       -sin(theta)*sin(i)*cos(Omega) - cos(theta)*cos(i)*sin(Omega), -sin(theta)*sin(Omega) + cos(theta)*cos(i)*cos(Omega), cos(theta)*sin(i);
       sin(i)*sin(theta), -sin(i)*cos(Omega), cos(i)];

end

