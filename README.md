# GameOfLife
Simple engine for Conway's Game of Life.

Intended to be run from the command line.

```
GameOfLife.exe [-h][-f inputFile][-g <iterations>]
   -h             : show this help text
   -f <inputFile> : input filename for grid initialization
   -g <iterations>: specify number of iterations to model, 'c' for continuous
   -q             : quiet mode - don't print out itermediate grid states
                                 (does not apply to 'continuous' mode)

   Grid initialization should be one cell per line, format (<col>, <row).
   
   If no input file is specified, user will be prompted to enter cells
   one line at a time. An empty line indicates the end of grid input.
   
   If no number of iterations is specified in the command line args, 
   the user will be prompted for a number of iterations to proceed.
   The character 'c' may be entered for continuous generations
   until the program is interrupted.
