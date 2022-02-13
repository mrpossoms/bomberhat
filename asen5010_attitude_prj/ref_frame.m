function [ sigma_RN ] = ref_frame( t, detumbled )
%REF_FRAME Computes the appropriate reference frame based on whether the
%spacecraft has detumbled or not, and the time.

r_TN_E = rot2(Target.North)*rot3(-Target.East)*[EarthApprox.r; 0; 0];
DCM_HN = Euler_313(SC.Omega, SC.i, SC.theta_dot*t);
r_HN_N = DCM_HN'*[SC.r; 0; 0];

    function sigma = frame(R1)
        % Velocity vector of the SC.
        v__N = DCM_HN'*[0; SC.v; 0];
        R2 = unit_vector(cross(R1, v__N));
        % Determine the second vector of R.
        R3 = unit_vector(cross(R1, R2)); % Ensure right-handedness.
        % Ensure frame is orthonormal (errors if not).
        verify_ortho(R1, R2, R3)
        % Before using those vectors for the DCM, let's make sure they are
        % defined as columns.
        R1 = col_vec(R1);
        R2 = col_vec(R2);
        R3 = col_vec(R3);
        % Build the RN DCM.
        DCM_RN = [R1'; R2'; R3'];
        sigma = Short_MRP(DCM2MRP(DCM_RN));
    end

if detumbled
    DCM_EN = rot3(EarthApprox.rot_rate*t);
    r_TN_N = DCM_EN'*r_TN_E;
    sigma_RN = frame(unit_vector(r_HN_N - r_TN_N));
else
    sigma_RN = frame(unit_vector(r_HN_N));
end

end