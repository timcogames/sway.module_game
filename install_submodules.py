
import re
import os
import subprocess

##
# Читаем .gitmodules и извлекаем из него path
def get_submodule_paths(filepath):
  submodules_paths = []
  with (open(filepath) as gitmodules_file):
    for line in gitmodules_file:
      if line.startswith("[submodule"):
        submodules_paths.append(re.findall(r'"(.*?)"', line)[0])

  return submodules_paths

##
# Проверяет наличие .gitmodules файла
def is_exists_gitmodules_file(files):
  for file in files:
    if (file == '.gitmodules'):
      return True
  return False

##
# Проверяет содержание подмодуля
def is_empty_submodule_dir(dirname):
  if os.path.exists(dirname) and os.path.isdir(dirname):
    if len(os.listdir(dirname)) == 0:
      return True
  return False

##
#
def git(args):
  subprocess.run(["git", "status"], check=True)

##
#
def recurse():
  for root, dirs, files in os.walk('.'):
    path = root.split(os.sep)

    if is_exists_gitmodules_file(files):
      submodule_paths = get_submodule_paths(root + '/.gitmodules')
      for submodule_path in submodule_paths:
        path_pre = (len(path) - 1) * '-'
        path_str = os.path.basename(root) + '/' + submodule_path

        submodule_path_abst = root + '/' + submodule_path

        if is_empty_submodule_dir(submodule_path_abst):
          # git('git submodule update --init')
          path_str += ' [is empty]'

        print(path_pre, path_str)

recurse()
