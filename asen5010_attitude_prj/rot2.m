function r = rot2(angle)
r = [cos(angle), 0, -sin(angle);
    0, 1 , 0;
    sin(angle), 0, cos(angle)];
end