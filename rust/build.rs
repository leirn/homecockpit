extern crate bindgen;

use std::env;
use std::path::PathBuf;

fn main() {
    env::set_var("RUST_BACKTRACE", "1");

    // Tell cargo to look for shared libraries in the specified directory
    println!("cargo:rustc-link-search=Simconnect SDK/lib");

    // Tell cargo to tell rustc to link the simconnect lib
    // shared library.
    println!("cargo:rustc-link-lib=simconnect");

    // Tell cargo to invalidate the built crate whenever the wrapper changes
    //println!("cargo:rerun-if-changed=wrapper.h");

    // The bindgen::Builder is the main entry point
    // to bindgen, and lets you build up options for
    // the resulting bindings.
    let bindings = bindgen::Builder::default()
        // The input header we would like to generate
        // bindings for.
        .header("wrapper.h")
        .clang_arg(r#"-IC:/Program Files (x86)/Microsoft Visual Studio/2019/BuildTools/VC/Tools/MSVC/14.29.30133/include"#)
        .clang_arg("-xc++")
        .clang_arg("-std=c++11")
        // Tell cargo to invalidate the built crate whenever any of the
        // included header files changed.
        .parse_callbacks(Box::new(bindgen::CargoCallbacks))
        // Finish the builder and generate the bindings.
        .generate()
        // Unwrap the Result and panic on failure.
        .expect("Unable to generate bindings");

    // Write the bindings to the $OUT_DIR/bindings.rs file.
    let out_path = PathBuf::from(env::var("OUT_DIR").unwrap());
    bindings
        .write_to_file("bindings.rs")
        //.write_to_file(out_path.join("bindings.rs"))
        .expect("Couldn't write bindings!");
    println!(
        "Outpath is {}",
        out_path.into_os_string().into_string().unwrap()
    );
}
