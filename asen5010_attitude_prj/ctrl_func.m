function [ ctrl ] = ctrl_func( state )
%CTRL_FUNC Control function for the given state.

K = 5e-2 * eye(3);
P = 5e-2 * eye(3);

sigma_BR = col_vec(state(8:10));
omega_BR = col_vec(state(11:13));

ctrl = -K*sigma_BR - P*omega_BR;

end

