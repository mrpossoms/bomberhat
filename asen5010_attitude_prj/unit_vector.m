function [ v ] = unit_vector( v )
%UNIT_VECTOR Returns the unit vector.
v = v/norm(v);
end

