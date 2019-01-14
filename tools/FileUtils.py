import os

def write_file(pathname, content, overwrite):
	if os.path.exists(pathname) and (not overwrite):
		return False

	dirName = os.path.dirname(pathname)
	if not os.path.exists(dirName):
		os.makedirs(dirName)

	fp = file(pathname, 'w')
	fp.write(content)
	fp.close()

	return True
