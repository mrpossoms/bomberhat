function [ state_dot ] = state_func( t, state )
%STATE_FUNC Returns the derivative of the state, which is [sigma; omega].
% Parameters are the previous state and a provided control. If control is
% not provided, it will be set to 0.

%% Extract information from state.
sigma_BN = Short_MRP(col_vec(state(1:3)));
omega_BN = col_vec(state(4:6));

%% Check whether to apply control law.
if state(7) == -1
    % State used in verif RK4 - do nothing more.
else if state(7) ~= 0 && state(7) ~= 1
    error('[ERROR] Component 7 is neither 0 nor 1 at time %d: %d.', t, state(7))
    end
end
if length(state) >= 7 && state(7) == 1
    % If set to True, then we must apply the control to this EOM.
    ctrl = ctrl_func(state);
else
    ctrl = zeros(1, 3);
    if state(7) ~= -1
        disp('[WARN] Control is OFF.')
    end
end

%% Compute state_dot.
% Copy previous state over, and then rewrite specific components.
state_dot = state(:);
state_dot(1:3) = 1/4 * MRP_B(sigma_BN) * omega_BN;
% Compute Euler's EOM.
state_dot(4:6) = [(SC.I(2,2)-SC.I(3,3))/(SC.I(1,1)) * omega_BN(2) * omega_BN(3) + ctrl(1);
                  (SC.I(3,3)-SC.I(1,1))/(SC.I(2,2)) * omega_BN(3) * omega_BN(1) + ctrl(2);
                  (SC.I(1,1)-SC.I(2,2))/(SC.I(3,3)) * omega_BN(1) * omega_BN(2) + ctrl(3);];
end
