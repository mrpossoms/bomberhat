function [ x_tilde ] = tilde( x )
%TILDEM returns the tilde matrix representation.

x_tilde = [0, -x(3), x(2);
           x(3), 0, -x(1);
           -x(2), x(1), 0];

end

