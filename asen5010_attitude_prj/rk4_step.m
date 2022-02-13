function [ xip1, yip1 ] = rk4_step( xi, yi, func, step, tdc )
%RK4_STEP Computes a single step in an RK4 integration.
% xi: previous time (usually), will be simply incremented by one.
% yi: previous step vector (no size limit).
% func: function which takes a vector of size yi as input.
% Returns: xi+1 (scalar) and yi+1 (vector).

%% Definitions
if nargin < 4
    % Define step to one since this computes a single step.
    step = 1;
end

if nargin < 5
    % Define the time dependent components.
    tdc = length(yi);
end

simple = tdc == length(yi);

%% Computation
% Compute the k_i.
if simple
    if length(yi) > 1
        disp('ip')
    end
    k1 = col_vec(step*func(xi, yi));
    k2 = col_vec(step*func(xi + step/2, yi + k1/2));
    k3 = col_vec(step*func(xi + step/2, yi + k2/2));
    k4 = col_vec(step*func(xi + step, yi + k3));
    yip1 = yi + (1/6)*(k1 + 2*k2 + 2*k3 + k4);
    xip1 = xi + step;
else
    extra = length(yi) - tdc;
    len_yi = length(yi);
    % k1
    k1_i = func(xi, yi);
    k1(1:tdc) = step*k1_i(1:tdc);
    k1(tdc + 1:len_yi) = zeros(extra, 1);
    k1 = col_vec(k1);
    % k2
    k2_i = func(xi + step/2, yi + k1/2);
    k2(1:tdc) = step*k2_i(1:tdc);
    k2(tdc + 1:len_yi) = zeros(extra, 1);
    k2 = col_vec(k2);
    % k3
    k3_i = func(xi + step/2, yi + k2/2);
    k3(1:tdc) = step*k3_i(1:tdc);
    k3(tdc + 1:len_yi) = zeros(extra, 1);
    k3 = col_vec(k3);
    % k4
    k4_i = func(xi + step, yi + k3);
    k4(1:tdc) = col_vec(step*k4_i(1:tdc));
    k4(tdc + 1:len_yi) = zeros(extra, 1);
    k4 = col_vec(k4);
    
    yip1 = yi + (1/6)*(k1 + 2*k2 + 2*k3 + k4);
    yip1(tdc + 1:len_yi) = k1_i(tdc + 1:end);
    xip1 = xi + step;
end
end

