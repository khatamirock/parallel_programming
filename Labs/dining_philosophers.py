# https://rosettacode.org/wiki/Dining_philosophers#Python

import threading
import random
import time

# Dining philosophers, 5 Phillies with 5 forks. Must have two forks to eat.
#
# Deadlock is avoided by never waiting for a fork while holding a fork (locked)
# Procedure is to do block while waiting to get first fork, and a nonblocking
# acquire of second fork.  If failed to get second fork, release first fork,
# swap which fork is first and which is second and retry until getting both.
#
# See discussion page note about 'live lock'.


class Philosopher(threading.Thread):

    running = True

    def __init__(self, xname, fork_on_left, fork_on_right):
        threading.Thread.__init__(self)
        self.name = xname
        self.fork_on_left = fork_on_left
        self.fork_on_right = fork_on_right

    def run(self):
        while self.running:
            #  Philosopher is thinking (but really is sleeping).
            time.sleep(random.uniform(3, 13))
            print(f'{self.name} is hungry.')
            self.dine()

    def dine(self):
        fork1, fork2 = self.fork_on_left, self.fork_on_right

        while self.running:
            xx=fork1.acquire(True)
            locked = fork2.acquire(False)
            # the returns statement is true/ false 
            # depending on the basis of the lock is held or not
            # not related with the parameter passed
            # the parameter is just for waiting or not!!!! purpose
            
            print(self.name,xx,locked,end='  >>')
            if locked:
                break
            fork1.release()
            print(f'{self.name} swaps forks')
            fork1, fork2 = fork2, fork1
        else:
            return

        self.dining()
        fork2.release()
        fork1.release()

    def dining(self):
        print(f'{self.name} starts eating')
        time.sleep(random.uniform(10, 50))
        print(f'{self.name} finishes eating and leaves to think.')


def dining_philosophers():
# threading.Lock() object.............................

    forks = [threading.Lock() for n in range(5)]
    philosopher_names = ('Aristotle', 'Kant', 'Buddha', 'Marx', 'Russel')

    philosophers = [Philosopher(philosopher_names[i], forks[i % 5], forks[(i+1) % 5]) for i in range(5)]

    random.seed(507129)
    Philosopher.running = True
    for p in philosophers:
        p.start()
    time.sleep(100)
    Philosopher.running = False
    print("Now we're finishing.")


dining_philosophers()
# 
# Russel is hungry.
# Russel starts eat""" ing
# Aristotle is hungry.
# Marx is hungry.
# Marx swaps forks
# Kant is hungry.
# Kant starts eating
# Buddha is hungry.
# Russel finishes eating and leaves to think.
# Aristotle swaps forks
# Marx starts eating   
# Kant finishes eating and leaves to think.
# Aristotle starts eating
# Buddha swaps forks     
# Marx finishes eating and leaves to think.
# Buddha starts eating
# Russel is hungry.
# Russel swaps forks
# Traceback (most recent call last):
#   File "c:\Users\hp\Desktop\dining_philosophers.py", line 74, in <module>
#     dining_philosophers()
#   File "c:\Users\hp\Desktop\dining_philosophers.py", line 69, in dining_philosophers
#     time.sleep(100)
# KeyboardInterrupt
# Aristotle finishes eating and leaves to think.
# Russel starts eating
# Buddha finishes eating and leaves to think.
# Marx is hungry.
# Marx swaps forks
# Russel finishes eating and leaves to think.
# Marx starts eating
# Aristotle is hungry.
# Aristotle starts eating
# Kant is hungry.
# Marx finishes eating and leaves to think.
# Buddha is hungry.
# Buddha starts eating
# Russel is hungry.
# Russel swaps forks
# Buddha finishes eating and leaves to think.
# Aristotle finishes eating and leaves to think.
# Kant starts eating
# Russel starts eating
# Buddha is hungry.
# Marx is hungry.
# Marx swaps forks
# Aristotle is hungry.
# Kant finishes eating and leaves to think.
# Buddha starts eating
# Russel finishes eating and leaves to think.
# Marx swaps forks
# Aristotle starts eating
# Buddha finishes eating and leaves to think.
# Marx starts eating
# Russel is hungry. """
# #