use crate::vehstate::AttitudeState;

use super::nyx::linalg::{Matrix3, Vector3};
use super::MRP;

pub struct AttCtrl {
    pub sigma_tgt: Option<MRP>,
    pub omega_tgt: Option<Vector3<f64>>,
    pub sigma_gain: Matrix3<f64>,
    pub omega_gain: Matrix3<f64>,
}

impl AttCtrl {
    /// Given an input attitude state, return the angular velocity control to stablize around the targets
    pub fn omega_ctrl(&self, osc: AttitudeState) -> Vector3<f64> {
        todo!()
    }
}
