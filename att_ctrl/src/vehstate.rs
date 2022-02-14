use nalgebra::Matrix3;

use super::mrp::MRP;
use super::nyx::linalg::{Const, OVector, Vector3};
use super::nyx::time::Epoch;
use super::nyx::State;
use std::fmt;

#[derive(Copy, Clone, Debug, PartialEq)]
pub struct AttitudeState {
    pub epoch: Epoch,
    pub sigma: MRP,
    pub omega: Vector3<f64>,
    pub inertia_tensor: Matrix3<f64>,
}

impl AttitudeState {
    pub fn i_xx(&self) -> f64 {
        self.inertia_tensor[(0, 0)]
    }

    pub fn i_yy(&self) -> f64 {
        self.inertia_tensor[(1, 1)]
    }

    pub fn i_zz(&self) -> f64 {
        self.inertia_tensor[(2, 2)]
    }

    /// Returns the angular momentum of the system, i.e. [I]ω
    pub fn momentum(&self) -> Vector3<f64> {
        self.inertia_tensor * self.omega
    }
}

impl State for AttitudeState {
    type Size = Const<6>;

    type VecLength = Const<6>;

    fn as_vector(&self) -> Result<nalgebra::OVector<f64, Self::VecLength>, nyx::NyxError> {
        Ok(OVector::<f64, Const<6>>::from_iterator(
            self.sigma.0.iter().chain(self.omega.iter()).cloned(),
        ))
    }

    fn set(
        &mut self,
        epoch: Epoch,
        vector: &nalgebra::OVector<f64, Self::VecLength>,
    ) -> Result<(), nyx::NyxError> {
        self.epoch = epoch;
        // Update orientation
        self.sigma.0[0] = vector[0];
        self.sigma.0[1] = vector[1];
        self.sigma.0[2] = vector[2];
        self.sigma.normalize_mut();

        // Update body rates
        self.omega[0] = vector[3];
        self.omega[1] = vector[4];
        self.omega[2] = vector[5];

        Ok(())
    }

    fn epoch(&self) -> Epoch {
        self.epoch
    }

    fn set_epoch(&mut self, epoch: Epoch) {
        self.epoch = epoch;
    }
}

impl fmt::Display for AttitudeState {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(
            f,
            "{}\nOrientation{:?}\nBody rates:{}",
            self.epoch, self.sigma, self.omega
        )
    }
}

impl fmt::LowerExp for AttitudeState {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(f, "{}", self)
    }
}
