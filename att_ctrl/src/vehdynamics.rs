use super::nyx::dynamics::Dynamics;
use super::nyx::linalg::{
    allocator::Allocator, Const, DefaultAllocator, OVector, Vector3, Vector6,
};
use super::nyx::State;
use crate::vehstate::AttitudeState;

#[derive(Copy, Clone)]
pub struct AttDynamics {}

impl<'a> Dynamics for AttDynamics {
    type HyperdualSize = Const<6>;
    type StateType = AttitudeState;

    fn eom(
        &self,
        delta_t: f64,
        state_vec: &OVector<f64, <Self::StateType as nyx::State>::VecLength>,
        ctx: &Self::StateType,
    ) -> Result<OVector<f64, <Self::StateType as nyx::State>::VecLength>, nyx::NyxError>
    where
        DefaultAllocator: Allocator<f64, <Self::StateType as nyx::State>::VecLength>,
    {
        // Rebuild the osculating state
        let osc = ctx.set_with_delta_seconds(delta_t, state_vec);

        let mrp_dt = 0.25 * osc.sigma.linearized_eom() * osc.omega;
        // Euler's EOM

        let body_accels = Vector3::new(
            (osc.i_yy() - osc.i_zz()) / osc.i_xx() * osc.omega[1] * osc.omega[2],
            (osc.i_zz() - osc.i_xx()) / osc.i_yy() * osc.omega[2] * osc.omega[0],
            (osc.i_xx() - osc.i_yy()) / osc.i_zz() * osc.omega[0] * osc.omega[1],
        );

        Ok(Vector6::from_iterator(
            mrp_dt.iter().chain(body_accels.iter()).cloned(),
        ))
    }
}
