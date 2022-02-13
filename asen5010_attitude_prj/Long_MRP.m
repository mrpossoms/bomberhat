function [ sigma ] = Long_MRP( sigma )
%MRP_S Return the shadow MRP if needed, otherwise the originally provided
%MRP.

% Check if shadow set switch is needed.
sigma_norm = norm(sigma);
if sigma_norm < 1
    sigma = - sigma / (sigma_norm^2);
end

end

