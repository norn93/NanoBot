#This is a Python 3 program to help analyse the movement data

import matplotlib.pyplot as plt #install this with pip: "pip install matplotlib"

#load up the data
with open("speed_motor_test_results.csv") as f:
    content = f.readlines()

#remove whitespace
content = [x.strip() for x in content]

#parse the data
ticks = []
times = []
for item in content:
    data = item.split(",")
    if data[0] != "" and str(int(data[0])) == data[0]: #if the first item in this row is an int
        ticks.append(int(data[0]))
        times.append(int(data[1])/1000)

#plot the distance/time data
plt.figure("Ticks/Time Data from File")
plt.plot(times, ticks, 'ro-')
plt.ylabel('Ticks')
plt.xlabel('Time (ms)')

#ESTIMATING VELOCITY#####################################################

#simulate the data gathering process
t_inc = 100 #ms: how often do we sample?
t_max = 2000 #when it's stopped moving, approximately
t = 0
velocity_times = [] #the times at which we sampled the optocoupler (actually speed. whatever...)
velocity_ticks = [] #the ticks at each given sample time

print("Sampling every", t_inc, "ms")

for t in range(0, t_max, t_inc):
    current_tick = 0 #assume we have completed no ticks
    i = 0
    while i < len(ticks) - 1 and times[i] < t: #find how many ticks we have done by this time
        i += 1
    velocity_times.append(t)
    velocity_ticks.append(ticks[i])

#print the times
#for i in range(len(velocity_ticks)):
#    print(velocity_times[i], velocity_ticks[i])

#plot the distance/time data
plt.figure("Sampled Ticks/Time Data")
plt.plot(velocity_times, velocity_ticks, 'ro-')
plt.ylabel('Ticks')
plt.xlabel('Time (ms)')

#actually calculate velocity over time
velocity_estimates = [0]
for i in range(1, len(velocity_times)):
    velocity_estimates.append((velocity_ticks[i]-velocity_ticks[i-1])/t_inc) #distance/time

#plot the speed data
plt.figure("Estimated Velocity from Sampled Data")
plt.plot(velocity_times, velocity_estimates, 'ro-')
plt.ylabel('Velocity')
plt.xlabel('Time (ms)')
plt.show()    
    
