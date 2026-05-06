import subprocess 
import argparse

def run_command(command):
    try:
        subprocess.run(
            command,
            shell=True,
            capture_output=False,
            text=True,
            check=True
        )
    except subprocess.CalledProcessError as e:
        print(f"--- Error ---")
        print(f"Command failed with return code {e.returncode}")
        print(f"Error message: {e.stderr}")

create_dir = "cmake -B build"
make_build = "cmake --build build"
create_release_dir = "cmake -S . -B build -DCMAKE_BUILD_TYPE=Release"
make_release_build = "cmake --build build"

if __name__=="__main__":
    
    parser = argparse.ArgumentParser(
        description="CMake -- Mandelbrot Generator"
    )
    parser.add_argument(
        "mode",
        default="debug",
        choices=["debug", "release"],
    )
    
    args = parser.parse_args()
    
    if args.mode == "debug":
        run_command(create_dir)
        run_command(make_build)
    elif args.mode == "release":
        run_command(create_release_dir)
        run_command(make_release_build)