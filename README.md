make sure run.sh has the permission to be executed with:
```bash
chmod +x runs.sh
```
return to normal

1. Running a single compiled C++ executable: The executable will contain all three functions combined into one program. When you run it, the operating system needs to load the entire program into 
memory once, initialize the data structures, and then execute each function sequentially as instructed by the main function. This approach might be faster if the tasks are highly interdependent or 
if there's minimal overhead in loading and initializing the program.

2. Running multiple C++ executables: In this case, you would have separate executables for each task. The operating system loads each executable into memory, initializes data structures, and 
executes the specified task. This approach might be slower due to the increased overhead of loading and initializing multiple programs, but it can potentially leverage the benefits of 
parallelization if the tasks are independent or only require minimal communication between them.

##macOS version

If on macOS and want to automate the email alerts, please use the scripts in `macOS_scripts` folder.
Place the `auto.sh` file somewhere in `Users/username/` but neither in Documents nor in Downloads as Apple tends to restrict access to these folder. THis might lead to `Unload failed: 5: Input/output error \'Try running launchctl bootout\' as root for richer errors.` in the terminal when loading the .plist with the `launchctl` command or `/bin/bash ... operation not permitted` in the error.log file if the script eventualy loads.