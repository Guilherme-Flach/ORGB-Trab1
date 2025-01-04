from os import listdir,mkdir,makedirs
from os.path import isfile, join, exists
from shutil import copy2
from subprocess import run, CalledProcessError

def run_bash_script(script_path, *args):
    """
    Runs a bash script with optional arguments.

    :param script_path: Path to the bash script
    :param args: Optional arguments to pass to the script
    """
    try:
        # Construct the command
        command = ["bash", script_path] + list(args)
        
        # Run the script and capture output
        result = run(command, check=True, text=True, capture_output=True)
        
        # Print output and return it
        print(f"Script Output:\n{result.stdout}")
        return result.stdout
    except CalledProcessError as error:
        print(f"Error running script: {error.stderr}")
        raise
    except FileNotFoundError:
        print(f"Script file not found: {script_path}")
        raise


def copy_and_rename_file(src_file, dest_folder, new_filename):
    """
    Copies a file to a destination folder and renames it.
    Overwrites the file if it already exists.

    :param src_file: Path to the source file
    :param dest_folder: Path to the destination folder
    :param new_filename: New name for the file in the destination folder
    """
    try:
        # Ensure the destination folder exists
        makedirs(dest_folder, exist_ok=True)
        
        # Create the full destination file path
        dest_file = join(dest_folder, new_filename)
        
        # Copy and rename the file
        copy2(src_file, dest_file)
        print(f"File copied and renamed to: {dest_file}")
    except Exception as error:
        print(f"Error copying file: {error}")




config_folder = "NewConfigs"
stats_folder = "Stats"

configs = listdir(config_folder)

for folder in configs:
    stats_path = join(stats_folder, folder + "-stats") 
    if not exists(stats_path):
        stat_folder = mkdir(stats_path)

    subconfigs = listdir(join(config_folder, folder))
    for subconfig in subconfigs:

        inner_stats_path = join(stats_folder, folder + "-stats", subconfig + "-stats") 
        if not exists(inner_stats_path):
            inner_stat_folder = mkdir(inner_stats_path)

        print(subconfig)

        # Copy config files from folder unto gem5
        #copy_and_rename_file("CPU.py", "DEST FOLDER", "NAME" )

        # run all benchmarks
        

        # retrieve results into 
