import argparse
import sys
import os

__version__ = "x.x.x"

# *******************************************************************************
# @brief set all defines variable to configure the build
# @param None
# @return None
# *******************************************************************************
def configure(args):
    print("[CONFIGURE]")

    # copy the default configuration file
    if os.path.isdir("tools/generated"):
        os.system("rm -r tools/generated")
        os.mkdir("tools/generated")
    else:
        os.mkdir("tools/generated")

    os.system('cp tools/defconfig/default_defconfig tools/generated/.config')
    print("generate .config file")

    # convert the configuration file to a config.mk file
    input_file = open("tools/generated/.config", "r")
    output_file = open("tools/generated/config.mk", "w+")

    module_list = "GLOBAL_MODULE_LIST := "

    for line in input_file:
        if "CONFIG" in line:
            output_file.write(line)
        elif "MODULE" in line:
            if "=y" in line:
                line = line.replace("MODULE_", '')
                index = line.rfind("=y")
                line = line[:index]
                line = line.replace("_", "/")
                line = line.lower()

                module_list = module_list + line + ' '
    
    output_file.write(module_list)

    input_file.close()
    output_file.close()
    print("generate config.mk file")

# *******************************************************************************
# @brief delete build directory and all build artifacts
# @param None
# @return None
# *******************************************************************************
def clean(args):
    print("[CLEAN]")

    os.system('make -f tools/make/build.mk clean')

# *******************************************************************************
# @brief call make to build the kernel sources
# @param None
# @return None
# *******************************************************************************
def build(args):
    print("[BUILD]")

    os.system('make -f tools/make/build.mk build')

# *******************************************************************************
# @brief run the kernel on the configured target
# @param None
# @return None
# *******************************************************************************
def run(args):
    print("[RUN]")

    os.system('make -f tools/make/build.mk run')

# *******************************************************************************
# @brief find the root directory absolute path
# @param None
# @return None
# *******************************************************************************
def get_root_dir():
    # get the current absolute path
    root_dir = os.getcwd()

    return root_dir

# *******************************************************************************
# @brief update global __version__ from a version.h file
# @param None
# @return None
# *******************************************************************************
def update_version():
    global __version__
    root_dir = get_root_dir()
    version_file_name = os.path.join(root_dir, 'version.h')
    version_file = open(version_file_name)
    lines = version_file.readlines()
    for line in lines:
        if line.find("BUILD_VERSION") != -1:
            index = line.rfind(" ")
            __version__ = line[index+2:-1]

# *******************************************************************************
# @brief manage all subcommands
# @param detect function arguments : -p
# @return None
# *******************************************************************************
def options():
    parser = argparse.ArgumentParser(
        description='Anckor command line interface')

    # create a version command
    parser.add_argument('-v', '--version',
                    help='show the current kernel version',
                    action='version',
                    version = "Anckor project " + __version__)

    # create subcommands
    subparsers = parser.add_subparsers()

    # declare "configure" subcommand
    build_parser = subparsers.add_parser('configure',
                                         help='configure the build system for a target')
    build_parser.set_defaults(func=configure)

    # declare "clean" subcommand
    build_parser = subparsers.add_parser('clean',
                                         help='delete all build artifacts')
    build_parser.set_defaults(func=clean)

    # declare "build" subcommand
    build_parser = subparsers.add_parser('build',
                                         help='build the kernel following the saved configuration')
    build_parser.set_defaults(func=build)

    # declare "run" subcommand
    build_parser = subparsers.add_parser('run',
                                         help='run the kernel on the configured target')
    build_parser.set_defaults(func=run)

    return parser

# *******************************************************************************
# @brief parse arguments and launch subcommand function
# @param None
# @return None
# *******************************************************************************
def main():
    # update project version
    update_version()

    # declare options of the CLI
    parser = options()
    if len(sys.argv) > 1:
        # parse options
        args = parser.parse_args()
        # execute CLI subcommand
        args.func(args)
    else:
        print("not enough arguments")
        print("please check how to use this tool with 'anckor -h' or 'anckor --help'")    

if __name__ == '__main__':
    sys.exit(main())