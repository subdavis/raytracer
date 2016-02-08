  _____               _______                        _____  ______          _____  __  __ ______ 
 |  __ \             |__   __|                      |  __ \|  ____|   /\   |  __ \|  \/  |  ____|
 | |__) |__ _ _   _     | |_ __ __ _  ___ ___ _ __  | |__) | |__     /  \  | |  | | \  / | |__   
 |  _  // _` | | | |    | | '__/ _` |/ __/ _ \ '__| |  _  /|  __|   / /\ \ | |  | | |\/| |  __|  
 | | \ \ (_| | |_| |    | | | | (_| | (_|  __/ |    | | \ \| |____ / ____ \| |__| | |  | | |____ 
 |_|  \_\__,_|\__, |    |_|_|  \__,_|\___\___|_|    |_|  \_\______/_/    \_\_____/|_|  |_|______|
               __/ |                                                                             
              |___/     Written by Brandon Davis in straight C++                           

---------------------------------------Compile Instructions--------------------------------------

    1. unzip this archive
    2. open a terminal and cd to the project root
    3. run ./build.sh
    4. run ./run.sh
    5. images will be located in ./Images

----------------------------------------Build Requirements---------------------------------------

    + Any OS capable of running a BASH script
    + The g++ compiler
        * Can be installed on ubuntu-based systems via `sudo apt-get install build-essential`
    + An image viewer that supports the .ppm format
        * Alternatively, see the imagemagick conversion instructions below to create a .png
    + OpenGL is NOT required.

--------------------------------------ImageMagick Conversion-------------------------------------

    If you do not have a .ppm viewer:

    1. `sudo apt-get install imagemagick`
    2. `cd Images`
    3. `convert <ppm image name>  <png image name>`