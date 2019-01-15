import os
import sys
from config import BIN_NAME 

platformArg = ARGUMENTS.get("platform", False)

if not platformArg:
	print 'please set platform'
	sys.exit(255)

cFlags = ''

if platformArg == "windows":
	cFlags +='-DWIN32 '
elif platformArg == 'linux':
	cFlags +='-DLINUX '

cFlags += '-std=c++11 '

os.system(os.path.join('tools', 'gen_version.py'))
os.system(os.path.join('tools', 'gen_config.py'))

class MyEnvironment(Environment):
	def __init__(self):
		super(MyEnvironment, self).__init__(CPPPATH = '#src', CCFLAGS = cFlags)
		self.sourceFiles = []
		self.libs = []

	def add_source_files(self, fileList):
		dirPath = self.Dir('.').abspath
		for filename in fileList:
			pathname = os.path.join(dirPath, filename)
			self.sourceFiles.append(env.Object(pathname))

	def get_source_files(self):
		return self.sourceFiles

	def add_lib(self, lib):
		self.libs.append(lib)

	def get_libs(self):
		return self.libs

env = MyEnvironment()

Export("env")
SConscript('src/core/SCSub')
SConscript('src/gen/SCSub')
SConscript('src/third_party/SCSub')
SConscript('src/module/SCSub')
SConscript('src/platform/' + platformArg + '/SCSub')

if platformArg == 'Linux':
	env.add_lib('curses')

env.Program(target = BIN_NAME, source = ['src/main.cpp'] + env.get_source_files(), LIBS = env.get_libs())
env.Program(target = 'test-printf', source = ['src/test/test-printf.cpp'] + env.get_source_files(), LIBS = env.get_libs())
# env.Program(target = 'testRef', source = ['src/test/test-ref.cpp'] + env.get_source_files())
# env.Program(target = 'test-curses', source = ['src/test/test-curses.cpp'], LIBS=['curses'])