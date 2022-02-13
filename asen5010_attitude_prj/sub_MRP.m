function [ sigma_2p ] = sub_MRP( sigma, sigma_p )
%SUB_MRP Summary of this function goes here
%   Detailed explanation goes here

sigma_squared = norm(sigma).^2;
sigma_p_squared = norm(sigma_p).^2;

sigma_2p = (1 - sigma_p_squared)*sigma - (1 - sigma_squared)*sigma_p + 2*cross(sigma,sigma_p);
sigma_2p = sigma_2p/(1 + sigma_squared*sigma_p_squared + 2*sigma'*sigma_p);

sigma_2p = col_vec(sigma_2p);
end

