# Cont to Discrete Time

from matplotlib.pyplot import *
from control import *
from control.matlab import *

N = [2]
D = [3,1]

Gtf = tf(N,D)  # Transfer function

y,t = step(Gtf)

plot(t,y)
    

Gtfd = c2d(Gtf,0.1)

print(Gtfd)
