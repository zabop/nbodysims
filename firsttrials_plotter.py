#!/usr/bin/env python
# coding: utf-8

import matplotlib.pyplot as plt
import numpy as np

data0 = np.genfromtxt('0')
x00, x01, v00, v01 = [data0[:,0],data0[:,1],data0[:,2],data0[:,3]]

data1 = np.genfromtxt('1')
x10, x11, v10, v11 = [data1[:,0],data1[:,1],data1[:,2],data1[:,3]]

for index, each in enumerate(x00):
    if index%1==0 and index<120:
        plt.figure(figsize=(10,10))
        plt.xlim([-5,5])
        plt.ylim([-5,5])
        plt.quiver(x00[:index],x01[:index],v00[:index],v01[:index],color='b')
        plt.quiver(x10[:index],x11[:index],v10[:index],v11[:index],color='r')
        plt.savefig('firsttrials_pngs/firsttrials'+str(index).zfill(3)+'.png')






