format long;
close all;
%% Vector computation
% Nomenclature:
%   + u_LO_M means the u vector from L to O in the M frame.
%     In the cases where the vector is evident, there will be a double
%     underscore instead of the two points, e.g. a__B could be the
%     acceleration in the B frame. Similarly, reference frame vectors are
%     written as b_K_X1 which means it is the first vector of the reference
%     frame X and referred to as b_K in the report.
%   + DMC_HO means the DCM from O to H frames.

%% Initial states
sigma_BN = [0.3; -0.4; 0.5];
omega_BN_B = [0.1; 0.4; -0.2];
                      
%% Definitions
duration = ceil(2.5*SC.period);
detumbled = false;
[dur_h , dur_m, dur_s]= timeconv(duration);
step = 0.01;
num_it = ceil(duration / step);
fprintf('[INFO] Propagation duration~=%02.f h %02.f min %02.1f. Step=%1.2f. Iterations=%1.3e\n', dur_h, dur_m, dur_s, step, num_it)
% State definition [\sigma_BN; \omega_BN; {control law enabled}; \sigma_BR; \omega_BR].
state_hist = zeros(13, num_it);
state_hist(1:3, 1) = sigma_BN;
state_hist(4:6, 1) = omega_BN_B;
state_hist(7, :) = ones(num_it, 1); % Use zeros(num_it, 1) to turn OFF control.

% State RN definition [\sigma_RN, |\sigma_RN|, \omega_RN, |\omega_RN|]
state_RN_hist = zeros(8, num_it);
% Various history.
var_hist = zeros(7, num_it);
reported = zeros(0, 10);
eta_reported = false;
%% Verifications
disp('[STANDBY] Verifying RK4.')
verif_rk4(step) % Will error if any issue was detected.
%% Simulation
disp('[INFO] Propagation started.')
eta_tic = tic;
for t = step:step:duration
    %% Report status
    percentage = ceil(100 * t / duration);
    if mod(percentage, 10) == 0 && ~ismember(percentage, reported)
        if ~eta_reported
            [eta_h, eta_m, eta_s] = timeconv(toc(eta_tic)*10);
            fprintf('[INFO] Expected elapse time: %02.f h %02.f min %02.3f\n', eta_h, eta_m, eta_s)
            eta_reported = true;
        end
        fprintf('[STANDBY] Completion: %2d%%\n', percentage)
        reported((percentage/10)+1) = percentage;
    end
    %% Definitions.
    it = round(t / step); % Iteration position.
    sigma_BN = col_vec(state_hist(1:3, it));
    omega_BN_B = col_vec(state_hist(4:6, it));
    %% Create the R ref. frame. If not detumbled, R points to nadir.
    sigma_RN = ref_frame(t, detumbled);
    state_RN_hist(1:3, it) = sigma_RN;
    state_RN_hist(4, it) = norm(sigma_RN);
    %% Tracking errors.
    sigma_BR = Short_MRP(sub_MRP(sigma_BN, sigma_RN));
    DCM_BR = MRP2DCM(sigma_BR);
    % Store attitude error in state for control law.
    state_hist(8:10, it) = sigma_BR;
    var_hist(1, it) = norm(sigma_BR);
    % Compute omega_RN from the rate of sigma RN, if possible.
    if it > 1 && state_hist(7, it) == 1
        sigma_RN_rate = 1/step * (sigma_RN - state_RN_hist(1:3, it - 1));
        if norm(sigma_RN_rate) > 1e-3
            % Shadow set was used for sigma_RN. Let's correct the
            % sigma_RN_rate.
            sigma_RN_rate = 1/step * (Long_MRP(sigma_RN) - state_RN_hist(1:3, it - 1));
        end
        omega_RN_B = DCM_BR * (4/((1+norm(sigma_RN)^2)^2))*MRP_B(sigma_RN)'*sigma_RN_rate;
    else
        omega_RN_B = [0; 0; 0];
    end
    state_RN_hist(5:7, it) = omega_RN_B;
    state_RN_hist(8, it) = norm(omega_RN_B);
    omega_BR_B = omega_BN_B - omega_RN_B;
    % Store velocity error in state for control law and its norm in var_hist.
    state_hist(11:13, it) = omega_BR_B;
    var_hist(2, it) = norm(omega_BR_B);
    %% Propagate attitude and angular velocity.
    [~, state_hist(:, it + 1)] = rk4_step(it, state_hist(:, it), @state_func, step, 6);
    state_hist(1:3, it + 1) = Short_MRP(state_hist(1:3, it + 1));
    % Reenable control if needed.
    if state_hist(7, it + 1) == 0
        state_hist(7, it + 1) = 1;
    end
    % Store the control function which was applied for future reference.
    ctrl = ctrl_func(state_hist(:, it));
    var_hist(3:5, it) = ctrl;
    var_hist(6, it) = norm(ctrl);
    %% Determine if we have detumbled.
    if ~detumbled && norm(omega_BR_B) < 0.1 && norm(sigma_BR) < 0.1
        fprintf('[OK] Detumble occured in %5.3f seconds (iteration = %d).\n', t, it);
        detumbled = true;
        fprintf('[INFO] Switching to mission phase 2.\n')
        state_hist(7, it + 1) = 0;
    end
end
[real_h, real_m, real_s] = timeconv(toc(eta_tic));
disp('[OK] Propagation completed.')
fprintf('[INFO] Elapsed time = %02.f h %02.f min %02.3f\n', real_h, real_m, real_s)
%% Plotting
err_time = step:step:duration;
hist_time = step:step:duration+step;
% Plot BN attitude and velocity components
plotter(hist_time, state_hist(1:3, :), {'Time (s)'; '\sigma_i'; '\sigma_{BN} all components'}, {'\sigma_1','\sigma_2','\sigma_3'})
plotter(hist_time, state_hist(4:6, :), {'Time (s)'; '\omega_i'; '\omega_{BN} all components'}, {'\omega_1','\omega_2','\omega_3'})

% Plot attitude error.
plotter(hist_time, state_hist(8:10, :), {'Time (s)'; '\sigma_i'; '\sigma_{BR} all components'}, {'\sigma_1','\sigma_2','\sigma_3'})
plotter(err_time, var_hist(1, :), {'Time (s)'; '|\sigma_{BR}|'; '|\sigma_{BR}| vs time'}, {'|\sigma_{BR}|'}, 0.1)
plotter(err_time, var_hist(1, :), {'Time (s)'; 'log(|\sigma_{BR}|)'; 'log(|\sigma_{BR}|) vs time'}, {'log(|\sigma_{BR}|)'}, 0, true)

% Plot velocity error.
plotter(hist_time, state_hist(11:13, :), {'Time (s)'; '\omega_i'; '\omega_{BR} all components'}, {'\omega_1','\omega_2','\omega_3'})
plotter(err_time, var_hist(2, :), {'Time (s)'; '|\omega_{BR}|'; '|\omega_{BR}| vs time'}, {'|\omega_{BR}|'}, 0.1)
plotter(err_time, var_hist(2, :), {'Time (s)'; 'log(|\omega_{BR}|)'; 'log(|\omega_{BR}|) vs time'}, {'log(|\omega_{BR}|)'}, 0, true)

% Plot control.
plotter(err_time, var_hist(6, :), {'Time (s)'; 'Control'; 'log(|ctrl|) vs time'}, {'log(|ctrl|)'}, 0, true)
