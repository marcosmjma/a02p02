#!/usr/bin/env python

import numpy as np
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt

with open("measures.dat") as f:
    data = f.readlines()
    x = [row.split(' ')[0] for row in data]
    y = [row.split(' ')[1] for row in data]
    z = [row.split(' ')[2] for row in data]

fig = plt.figure(1)
plot1 = fig.add_subplot(121)
plot1.set_xlabel('Message Size (bytes)')
plot1.set_ylabel('Round Trip Time (seconds)')
plot1.loglog(x,y, basex=2, basey=2, c='r', label='0.5*rtt')
plot1.set_title("MPI Point-to-Point Performance")

plot2 = fig.add_subplot(122)
plot2.set_xlabel('Message Size (bytes)')
plot2.set_ylabel('Bandwidth (MB/second)')
plot2.loglog(x,z, basex=2, basey=2, c='r', label='bandwidth')
plot2.set_title("MPI Point-to-Point Performance")

#plt.show()
fig.savefig("measures.png")
plt.close(fig)


