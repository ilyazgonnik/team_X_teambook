GNU GCC Compiler

1. Settings->Debugger->Default :: write in the "Debugger initialization commands" field: 
    source $(TARGET_COMPILER_DIR)etc\gdbinit
    handle SIGABRT stop print

2. Off "Disable startup scripts (-nx) (GDB only)" ibid (Settings->Debugger->Default)

3. Project -> Build options... 
  Compiler flags:: Debugging: On "Produce Debugging symbols [-g]"
  Other compiler options: write 
    -g3 -Og
  #defines: write
    _GLIBCXX_DEBUG
Tjikni na juka +"Watches" + main in "Call Stack"
