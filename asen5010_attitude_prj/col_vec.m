function [ vec ] = col_vec( vec )
%COL_VEC Returns this vector as a column.
[n, m] = size(vec);
if n < m
    vec = vec';
end
end

