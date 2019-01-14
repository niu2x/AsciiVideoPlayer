#!/usr/bin/python

from common import srcGenDir, projectDir
import FileUtils
import os
import sys

sys.path.append(projectDir)

from version import MAJOR_VERSION, MINOR_VERSION

if __name__ == '__main__':
	versionFile = os.path.join(srcGenDir, 'version.h')
	content = """
#ifndef VERSION_H
#define VERSION_H

#define MAJOR_VERSION %s
#define MINOR_VERSION %s

#endif

	""" % (MAJOR_VERSION, MINOR_VERSION)


	content = content.strip() + '\n'
	FileUtils.write_file(versionFile, content, True)