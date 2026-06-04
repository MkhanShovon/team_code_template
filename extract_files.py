import os

path = r"C:\D drive\CP_templates"
for root, dirs, files in os.walk(path):
    for f in files:
        full_path = os.path.join(root, f)
        rel_path = os.path.relpath(full_path, path)
        print(f"File: {rel_path} (Size: {os.path.getsize(full_path)} bytes)")
