use std::ops::{Add, Sub};

use super::nyx::linalg::{Matrix3, Vector3};
#[derive(Copy, Clone, PartialEq, Debug, PartialOrd)]
pub struct MRP(pub(crate) Vector3<f64>);

impl MRP {
    pub fn squared(&self) -> f64 {
        self.0.norm().powi(2)
    }

    pub fn normalize(&self) -> Self {
        let mut me = *self;
        me.normalize_mut();
        me
    }

    pub fn normalize_mut(&mut self) {
        if self.0.norm() > 1.0 {
            self.0 = -self.0 / self.squared();
        }
    }

    pub fn new(s1: f64, s2: f64, s3: f64) -> Self {
        let mut me = Self(Vector3::new(s1, s2, s3));
        me.normalize_mut();
        me
    }

    /// Compute the B matrix for the mrp
    pub fn linearized_eom(&self) -> Matrix3<f64> {
        (1.0_f64 - self.squared()) * Matrix3::identity()
            + 2.0 * tilde(&self.0)
            + 2.0 * self.0 * self.0.transpose()
    }
}

impl Sub for MRP {
    type Output = Self;

    fn sub(self, sigma_p: Self) -> Self::Output {
        let sigma_squared = self.squared();
        let sigma_p_squared = sigma_p.squared();

        let sigma_2p = ((1.0 - sigma_p_squared) * self.0 - (1.0 - sigma_squared) * sigma_p.0
            + 2.0 * self.0.cross(&sigma_p.0))
            / (1.0 + sigma_squared * sigma_p_squared + 2.0 * (sigma_p.0.transpose() * self.0)[0]);

        let mut me = Self(sigma_2p);
        me.normalize_mut();
        me
    }
}

impl Add for MRP {
    type Output = Self;

    fn add(self, sigma_2p: Self) -> Self::Output {
        let sigma_p_squared = self.squared();
        let sigma_2p_squared = sigma_2p.squared();

        let sigma = ((1.0 - sigma_p_squared) * sigma_2p.0 + (1.0 - sigma_2p_squared) * self.0
            - 2.0 * sigma_2p.0.cross(&self.0))
            / (1.0 + sigma_p_squared * sigma_2p_squared
                - 2.0 * (self.0.transpose() * sigma_2p.0)[0]);

        let mut me = Self(sigma);
        me.normalize_mut();
        me
    }
}

fn tilde(v: &Vector3<f64>) -> Matrix3<f64> {
    Matrix3::from_row_slice(&[0.0, -v[2], v[1], v[2], 0.0, -v[0], -v[1], v[0], 0.0])
}
