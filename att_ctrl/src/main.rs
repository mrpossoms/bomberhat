extern crate nalgebra as na;
extern crate nyx_space as nyx;

mod mrp;
mod vehdynamics;
mod vehstate;

use mrp::MRP;
use nyx::linalg::{Matrix3, Vector3};
use nyx::propagators::{PropOpts, Propagator, RK4Fixed};
use nyx::time::{Epoch, TimeUnitHelper};
use vehdynamics::AttDynamics;
use vehstate::AttitudeState;

fn main() {
    println!("Hello, world!");
}

#[test]
fn test_momentum_conserved() {
    let init = AttitudeState {
        sigma: MRP::new(0.3, -0.4, 0.5),
        omega: Vector3::new(0.1, 0.4, -0.2),
        epoch: Epoch::from_tai_seconds(0.0),
        inertia_tensor: Matrix3::new(10.0, 0.0, 0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 2.0),
    };
    let init_mom = init.momentum();

    // WARNING: Trying to use an adaptive step propagator will fail!
    let final_state =
        Propagator::new::<RK4Fixed>(AttDynamics {}, PropOpts::with_fixed_step_s(0.01))
            .with(init)
            .for_duration(30.seconds())
            .unwrap();

    let leak_prct =
        (init_mom.norm() - final_state.momentum().norm()) / final_state.momentum().norm();
    println!("{:e}", leak_prct);
    assert!(leak_prct < 1e-12);
}
