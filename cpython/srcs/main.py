# -*- coding:utf-8 -*-

import os

all_so = next(os.walk("."))[2]
all_so = [fileName for fileName in all_so if fileName.split('.')[-1] == "so"]

if len(all_so) > 0:
  try:
    import superfastcode
    print("Tanh(3): {}".format(superfastcode.fast_tanh(3)))
  except Exception as err:
    print("Can't execute the CPython. {}".format(err))
else:
  print("Can't find the shared library.")