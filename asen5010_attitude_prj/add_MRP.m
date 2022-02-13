function [ sigma ] = add_MRP( sigma_p, sigma_2p )
%ADD_MRP Summary of this function goes here
%   Detailed explanation goes here

sigma_p_squared = norm(sigma_p).^2;
sigma_2p_squared = norm(sigma_2p).^2;

sigma = (1-sigma_p_squared)*sigma_2p + (1-sigma_2p_squared)*sigma_p - 2*cross(sigma_2p, sigma_p);
sigma = sigma / (1 + sigma_p_squared*sigma_2p_squared - 2*(sigma_p'*sigma_2p));

sigma = Short_MRP(col_vec(sigma));

end
