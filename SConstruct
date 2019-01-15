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
elif platformArg == 'osx':
	cFlags +='-DOSX '


cFlags += '-std=c++11 '

os.system(os.path.join('tools', 'gen_version.py'))
os.system(os.path.join('tools', 'gen_config.py'))

class MyEnvironment(Environment):
	def __init__(self):
		super(MyEnvironment, self).__init__(CPPPATH = '#src', CCFLAGS = cFlags)
		self.sourceFiles = []
		self.libs = []
		self.sysLibs = []
		self.testMainSource = []

	def get_abs_pathname(self, pathname):
		dirPath = self.Dir('.').abspath
		return os.path.join(dirPath, pathname)

	def add_source_files(self, fileList):
		for filename in fileList:
			if type(filename) == type(''):
				filename = self.get_abs_pathname(filename)
			self.sourceFiles.append(env.Object(filename))

	def get_source_files(self):
		return self.sourceFiles

	def add_lib(self, lib):
		if type(lib) == type(''):
			lib = env.File(self.get_abs_pathname(lib))
		self.libs.append(lib)

	def add_system_lib(self, lib):
		self.sysLibs.append(lib)

	def get_system_lib(self):
		return self.sysLibs

	def get_libs(self):
		return self.libs

	def get_platform(self):
		return platformArg

	def add_test(self, binName, testMain):
		if type(testMain) == type(''):
			testMain = self.get_abs_pathname(testMain)
		self.testMainSource.append((binName, testMain))

	def get_test(self):
		return self.testMainSource

	def define(self, name, value = None):
		self.Append(CCFLAGS = ['-D' + name])

env = MyEnvironment()

Export("env")
SConscript('src/core/SCSub')
SConscript('src/gen/SCSub')
SConscript('src/third_party/SCSub')
SConscript('src/module/SCSub')
SConscript('src/platform/' + platformArg + '/SCSub')
SConscript('src/third_party/ffmpeg/doc/examples/SCSub')

if platformArg == 'osx':
	env.add_system_lib('curses')
	env.add_system_lib('z')
	env.add_system_lib('lzma' )
	env.add_system_lib('iconv')
	env.add_system_lib('bz2')
	env.Append(FRAMEWORKS = Split('VideoToolbox CoreVideo CoreMedia CoreFoundation Security CoreAudio AudioToolBox'))
	env.define('__STDC_CONSTANT_MACROS')

env.Program(target = BIN_NAME, source = ['src/main.cpp'] + env.get_source_files(), LIBS = env.get_libs() + env.get_system_lib())

for v in env.get_test():
	env.Program(target = v[0], source = [v[1]] + env.get_source_files(), LIBS = env.get_libs() + env.get_system_lib())

# env.Program(target = 'test-printf', source = ['src/test/test-printf.cpp'] + env.get_source_files(), LIBS = env.get_libs())
# env.Program(target = 'testRef', source = ['src/test/test-ref.cpp'] + env.get_source_files())
# env.Program(target = 'test-curses', source = ['src/test/test-curses.cpp'], LIBS=['curses'])