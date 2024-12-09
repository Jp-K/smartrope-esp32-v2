import os
import glob
import pathlib

Import("env")


def generate_serial_number():
    return "19030001"
    # return "19120027"


def process_files():
    parameters = {
        'serial_number': generate_serial_number()
    }

    print('Pre-processing files')

    root_dir = 'pre-processed'

    git_ignore_file = open(".gitignore")
    git_ignore_contents = git_ignore_file.read()
    git_ignore_file.close()
    
    if os.path.exists(root_dir):
        for input_file_path in list(set(glob.iglob(os.path.join(root_dir, '**/**'), recursive=True))):
            if os.path.isfile(input_file_path):

                output_file_path = input_file_path.replace(root_dir, "")

                if output_file_path.startswith("/"):
                    output_file_path = output_file_path[1:]

                output_file_directory = os.path.join(
                    *output_file_path.split('/')[:-1])

                pathlib.Path(output_file_directory).mkdir(
                    parents=True, exist_ok=True)

                input_file = open(input_file_path, "r")
                file_content = input_file.read()

                for param in parameters:
                    file_content = file_content.replace("{{" + param + "}}", parameters[param])

                input_file.close()

                lines = [
                    "// This file was auto generated, do not modify it directly,",
                    "// modify the original file instead:",
                    "//",
                    "// " + input_file_path,
                    "",
                    file_content
                ]

                output_file = open(output_file_path, "w")

                for line in lines:
                    output_file.write(line)
                    output_file.write("\n")

                output_file.close()

                if output_file_path not in git_ignore_contents:
                    git_ignore_contents = git_ignore_contents + "\n" + output_file_path

                print("File processed: ", output_file_path)

            # shutil.copy2(file_path, output_file_path)

    print("Updating .gitignore")
    
    git_ignore_file = open(".gitignore", "w")
    git_ignore_file.write(git_ignore_contents)
    git_ignore_file.close()

process_files()
