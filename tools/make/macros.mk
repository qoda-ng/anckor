# get the current module ID from the MAKEFILE_LIST built-in variable
GET_MODULE_ID = $(patsubst %/,%,$(dir $(word $(words $(MAKEFILE_LIST)),$(MAKEFILE_LIST))))

# create a build directory for the current mdule if it doesn't already exist
MKDIR = if [ ! -d $(dir $@) ]; then mkdir -p $(dir $@); fi