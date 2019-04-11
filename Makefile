all:
	g++   src/MSD_task.cc program/AQPDym.cc -I/home/jgarate/opt/pteros1.0/include/ -L/home/jgarate/opt/pteros1.0/lib/ -L/home/jgarate/opt/pteros1.0/lib64/ -lpteros -lpteros_analysis -ltng_io -std=c++11 -o AQPDym
	#g++    program/AQPDym.cc -I/home/jgarate/opt/pteros1.0/include/ -L/home/jgarate/opt/pteros1.0/lib/  -L/home/jgarate/opt/pteros1.0/lib64/  -lpteros -lpteros_analysis  -ltng_io -std=c++11 -o AQPDym
