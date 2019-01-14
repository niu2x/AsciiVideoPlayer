#!/usr/bin/python

from common import srcGenDir, projectDir
import FileUtils
import os
import sys

sys.path.append(projectDir)

import config

from jinja2 import Template

if __name__ == '__main__':

	versionFile = os.path.join(srcGenDir, 'config.h')
	content = Template("""
#ifndef CONFIG_H
#define CONFIG_H

{% for key in kv %}#define {{key}} {{kv[key]}}
{% endfor %}
#endif""")
	content = content.render(kv = config.c_configs)
	content = content.strip() + '\n'
	FileUtils.write_file(versionFile, content, True)