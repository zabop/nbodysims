#!/usr/bin/env python
# coding: utf-8

# In[30]:


import matplotlib.pyplot as plt


# In[31]:


import numpy as np


# In[32]:


data0 = np.genfromtxt('0')
x00, x01, v00, v01 = [data0[:,0],data0[:,1],data0[:,2],data0[:,3]]


# In[33]:


data1 = np.genfromtxt('1')
x10, x11, v10, v11 = [data1[:,0],data1[:,1],data1[:,2],data1[:,3]]


# In[36]:


data2 = np.genfromtxt('2')
x20, x21, v20, v21 = [data2[:,0],data2[:,1],data2[:,2],data2[:,3]]


# In[49]:


for index, each in enumerate(x00):
    if index%1==0 and index<39:
        plt.figure(figsize=(10,10))
        plt.xlim([-2.5,2.5])
        plt.ylim([-2.5,2.5])
        plt.quiver(x00[:index],x01[:index],v00[:index],v01[:index],color='b',zorder=2)
        plt.quiver(x10[:index],x11[:index],v10[:index],v11[:index],color='r',zorder=1)
        plt.quiver(x20[:index],x21[:index],v20[:index],v21[:index],color='k',zorder=0)
        plt.savefig('threestars_pngs/threestars'+str(index).zfill(3)+'.png')


# In[ ]:




