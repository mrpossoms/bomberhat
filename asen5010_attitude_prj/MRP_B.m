function [ B_sigma ] = MRP_B( sigma )
%MRP_B Computes the B matrix of sigma_dot.
% sigma: must be a vector in column form.
if min(size(sigma)) ~= 1
    error('sigma is not a vector.')
end
sigma = col_vec(sigma);
sigma_squared = sigma'*sigma;

B_sigma = (1-sigma_squared) * eye(3) + 2*tilde(sigma) + 2*(sigma*sigma');
end

