to compile please type from the correct directory:
make all


This will compile the c code.
in order to see info about it we can run:
objdump -x q1_302537394

in order to see a specific variable info type:
objdump -x q1_302537394 | grep "<variable>"

other option is :
nm q1_302537394 | grep "<variable>"

To see assembly code type:
objdump -d q1_302537394
