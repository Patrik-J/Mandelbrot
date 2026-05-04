import subprocess 

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

if __name__=="__main__":
    run_command(create_dir)
    run_command(make_build)
    