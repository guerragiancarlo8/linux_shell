linux_shell
===========

Autho: Giancarlo M. Guerra


A shell written in C that can be launched from any linux terminal. Handles basic instructions and has ability to fork and wait. 

Instruction set:

  ext = exit the shell
  
    example = --> ext
  
  typ = print contents of text file on the screen
  
    example = --> typ file1
  
  cop = reads contents of one file, creates a new file, and copies contents of first file into the new file
  
    example = --> cop file1 file2
  
  rem = removes desired file
  
    example = --> rem file1
  
If none of the instructions above are described, the shell will assume it is the name of an executable and will attempt to execute it.

  example = --> firefox (will execute the firefox browser and wait until termination. Once user closes firefox, the shell will prompt again)
  

