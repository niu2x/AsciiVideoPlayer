BIN_NAME = 'avp'
DEFAULT_LOG_LEVEL = 2

c_configs = {}
def include_to_c(name, value):
	if type(value) == type(""):
		value = '"' + value + '"'
	c_configs[name] = value

include_to_c('BIN_NAME', BIN_NAME)
include_to_c('DEFAULT_LOG_LEVEL', DEFAULT_LOG_LEVEL)