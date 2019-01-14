import os
import sys
from config import BIN_NAME 

class MyEnvironment(Environment):
	def __init__(self):
		super(MyEnvironment, self).__init__()
		self.sourceFiles = []

	def add_source_files(self, fileList):
		dirPath = self.Dir('.').abspath
		self.sourceFiles += map(lambda x:os.path.join(dirPath, x), fileList)

	def get_source_files(self):
		return self.sourceFiles

env = MyEnvironment()

platformArg = ARGUMENTS.get("platform", False)

if not platformArg:
	print 'please set platform'
	sys.exit(255)

cFlags = ''

if platformArg == "windows":
	cFlags +='-DWIN32'

os.system(os.path.join('tools', 'gen_version.py'))
os.system(os.path.join('tools', 'gen_config.py'))

# env.add_source_files(['src/main.cpp'])

Export("env")
SConscript('src/core/SCSub')
SConscript('src/gen/SCSub')
SConscript('src/third_party/SCSub')
SConscript('src/platform/' + platformArg + '/SCSub')

env.Program(target = BIN_NAME, source = ['src/main.cpp'] + env.get_source_files(), CCFLAGS = cFlags, CPPPATH='src')
env.Program(target = 'testRef', source = ['src/test/test-ref.cpp'] + env.get_source_files(), CCFLAGS = cFlags, CPPPATH='src')