Import("env")

env.Execute("$PYTHONEXE -m pip install css-html-js-minify")

import os
import sys
import glob
import pathlib
import shutil

from css_html_js_minify import process_single_html_file, process_single_css_file, process_single_js_file

def minimize_fs():
    print('Minimizing filesystem')

    root_dir = 'filesystem'
    output_dir = '.pio/build/data'

    if os.path.exists(output_dir):
        try:
            shutil.rmtree(output_dir)
        except OSError as e:
            print("Error: %s - %s." % (e.filename, e.strerror))

    # Ensure output_dir existence
    pathlib.Path(output_dir).mkdir(parents=True, exist_ok=True)

    for file_path in list(set(glob.iglob(os.path.join(root_dir, '**/**'), recursive=True))):
        if '.git' not in file_path and '.min' not in file_path:
            if os.path.isfile(file_path):
                
                output_file_path = file_path.replace(root_dir, output_dir)
                file_dir = os.path.join(*output_file_path.split('/')[:-1])
                pathlib.Path(file_dir).mkdir(parents=True, exist_ok=True)

                basename, extension = os.path.splitext(file_path)
                ext = extension.lower()

                if ext in ['.htm', '.html', '.xml']:
                    process_single_html_file(file_path, output_path=output_file_path)
                elif ext in ['.css']:
                    process_single_css_file(file_path, output_path=output_file_path)
                elif ext in ['.js', '.json']:
                    process_single_js_file(file_path, output_path=output_file_path)                    
                else:
                    shutil.copy2(file_path, output_file_path)

minimize_fs()