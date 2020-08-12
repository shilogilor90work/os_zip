to compile please type from the correct directory:
make all

to run:
sudo ./set_policy <policy as int> <priority as int>

to check if worked:
chrt -p <pid>
