function verif_rk4(step)
%VERIF_RK4 Verifies the RK4 implementation in 1D and with Euler's EOM for a given step size..
ok = true;
%% Basic 1D function (from Balbasi example)
f = @(x, theta) (-2.2067*1e-12)*(theta^4-81*1e8);
solutions = [594.91, 646.16, 647.54, 647.57];
step_sizes = [240, 120, 60, 30];
total_sim_num = length(step_sizes);
duration = 480;
for sim_no = 1:total_sim_num
    lstep = step_sizes(sim_no);
    expect = solutions(sim_no);
    num_it = ceil(lstep/480) + 1;
    hist = zeros(1, num_it);
    hist(1) = 1200;
    iterator = lstep:lstep:duration;
    for xi = iterator
        it = xi/lstep;
        [~, hist(it+1)] = rk4_step(xi, hist(it), f, lstep);
    end
    if abs(hist(end) - expect) > 1e-2
        ok = false;
        warning('Expected %3.3f but got %3.3f', expect, hist(end))
    end
end
if ok
    disp('[OK] RK4 in 1D.')
end

%% Euler's EOM simple propagator: confirm angular momentum is constant.
duration = 5; % Integrate over 500 seconds.
num_it = ceil(duration/step);
state_hist = zeros(7, num_it);
state_hist(1:3, 1) = [0.3; -0.4; 0.5];
state_hist(4:6, 1) = [0.1; 0.4; -0.2];
state_hist(7, 1) = -1;
max_mom = -inf;
min_mom = +inf;
prev_mom = 0;
rel_mom = zeros(1, num_it - 1);
for it = 1:num_it
    [~, state_hist(:, it+1)] = rk4_step(it, state_hist(:, it), @state_func, step, 6);
    cur_mom = norm(SC.I * state_hist(4:6, it))
    max_mom = max(max_mom, cur_mom);
    min_mom = min(min_mom, cur_mom);
    if it > 1
        rel_mom(it - 1) = abs(cur_mom - prev_mom)/prev_mom;
    end
    prev_mom = cur_mom;
end
if state_hist(7, end) ~= -1
    fprintf('Expected component 7 to be -1, got %2.3f instead.', state_hist(7, end))
end
mom_range = abs(max_mom - min_mom);
ttitle = sprintf('Angular momentum magnitude vs. time (step=%1.2f, Delta H=%1.2e)', step, mom_range);
plotter(step:step:duration-step, rel_mom, {'Time (s)'; '|H|'; ttitle}, {}, 0, true)
drawnow() % I'm impatient.
msg = sprintf('RK4 Euler EOM step=%1.2f Delta|H|=%1.2e, Delta T=%d s.\n', step, mom_range, duration);
if mom_range > 1e-6
    error('[ERROR] %s', msg)
else
    fprintf('[OK] %s', msg)
end
end
