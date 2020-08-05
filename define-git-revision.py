#!/usr/bin/env python3
"""Git revision and working tree state"""

import subprocess


REVISION = subprocess.check_output(["git", "rev-parse", "HEAD"]).strip()

if subprocess.check_output(["git", "diff", "--stat"]).strip() == "":
    STATE = "clean"
else:
    STATE = "dirty"


print("-D X55B_SRC_REVISION='\"{}\"'".format(REVISION.decode("UTF-8")))
print("-D X55B_SRC_STATE='\"{}\"'".format(STATE))