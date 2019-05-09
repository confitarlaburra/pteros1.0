all:
	g++   src/MSDCyl_task.cc src/pfCyl_task.cc program/AQPmsd.cc -I/home/jgarate/opt/pteros1.0/include/ -L/home/jgarate/opt/pteros1.0/lib/ -L/home/jgarate/opt/pteros1.0/lib64/ -lpteros -lpteros_analysis -ltng_io -std=c++11 -o AQPmsd
	g++   src/pfCyl_task.cc  program/AQPpf.cc -I/home/jgarate/opt/pteros1.0/include/ -L/home/jgarate/opt/pteros1.0/lib/ -L/home/jgarate/opt/pteros1.0/lib64/ -lpteros -lpteros_analysis -ltng_io -std=c++11 -o AQPpf	
	g++   src/MSD_task.cc program/msdBulk.cc -I/home/jgarate/opt/pteros1.0/include/ -L/home/jgarate/opt/pteros1.0/lib/ -L/home/jgarate/opt/pteros1.0/lib64/ -lpteros -lpteros_analysis -ltng_io -std=c++11 -o msdBulk
        