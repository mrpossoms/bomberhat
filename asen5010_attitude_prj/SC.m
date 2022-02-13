classdef SC
   properties (Constant)
   name = 'Satellite';
   altitude = 400; % km
   I = [10, 0, 0;
         0, 5, 0;
         0, 0, 2];
   Omega = 20; % degrees
   i = 56; % degrees
   theta_dot = 0.0011314; % rad/s
   period = 2*pi/SC.theta_dot; % s
   r = EarthApprox.r + SC.altitude; % km
   v = sqrt(EarthApprox.mu/SC.r); % km/s
   end
end