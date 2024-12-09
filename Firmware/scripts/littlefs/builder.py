Import("env")

from os.path import join
from SCons.Script import AlwaysBuild

def buildFS(source, target, env):
    target_firm = env.DataToBin(
        join("$BUILD_DIR", "spiffs"), "$PROJECTDATA_DIR")
    AlwaysBuild(target_firm)

    print("Before upload")
    print("Before upload")
    print("Before upload")
    print("Before upload")
    print("Before upload")
    print("Before upload")
    print("Before upload")
    print("Before upload")
    print("Before upload")

env.AddPreAction("upload", buildFS)