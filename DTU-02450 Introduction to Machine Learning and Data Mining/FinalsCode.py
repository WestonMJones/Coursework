# -*- coding: utf-8 -*-
"""
Created on Tue Dec 17 04:22:03 2019

@author: Westo
"""

import numpy as np
import pandas as pd
import toolbox_02450

#from matplotlib.pyplot import figure, show, scatter, hist, plot, legend, xlabel
#from scipy.io import loadmat
#from toolbox_02450 import clusterplot
#from scipy.cluster.hierarchy import linkage, fcluster, dendrogram
#from sklearn.decomposition import PCA
#from sklearn.mixture import GaussianMixture
#from sklearn import model_selection

def variance_explained():
    pc1 = [27.77, 13.86]
    other_pcs = [43.67, 33.47, 31.15, 30.36, 27.77, 13.86]
    top = 0
    bottom = 0
    
    for i in range(len(pc1)):
        
        top += (pc1[i])**2
       
    
    for i in range(len(other_pcs)):
        
        
        bottom += (other_pcs[i])**2
        
    
    print(top / bottom)
    
    
X1 = np.zeros(1500)
X2 = np.zeros(1500) 
for i in range(1499):
    X2[i]=1



X1[0]=1
X2[0]=0

    
    
    

Rand1, Jaccard1, NMI1 = toolbox_02450.clusterval(X1,X2)
print(Jaccard1)  





    
