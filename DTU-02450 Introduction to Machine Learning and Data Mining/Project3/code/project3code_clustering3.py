# -*- coding: utf-8 -*-
"""
Created on Tue Dec  3 11:07:56 2019

@author: Westo
"""

# -*- coding: utf-8 -*-
"""
Created on Mon Dec  2 11:27:36 2019

@author: Westo
"""

import numpy as np
import pandas as pd

from matplotlib.pyplot import figure, show, scatter, hist, plot, legend, xlabel
from scipy.io import loadmat
from toolbox_02450 import clusterplot, clusterval
from scipy.cluster.hierarchy import linkage, fcluster, dendrogram
from sklearn.decomposition import PCA
from sklearn.mixture import GaussianMixture
from sklearn import model_selection


# Again import data
airbnb_data = "AB_NYC_2019.csv"

#Specify attirubutes
attributes_datatype = {
    'id': np.float64,  # 0
    'name': str,  # 1
    'host_id': np.float64,  # 2
    'host_name': str,  # 3
    'neighbourhood_group': str,  # 4
    'neighbourhood': str,  # 5
    'latitude': np.float64,  # 6
    'longitude': np.float64,  # 7
    'room_type': str,  # 8
    'price': np.float64,  # 9
    'minimum_nights': np.float64,  # 10
    'number_of_reviews': np.float64,  # 11
    # 'last_review': str,  # 12
    'reviews_per_month': np.float64,  # 13
    'calculated_host_listings_count': np.float64,  # 14
    'availability_365': np.float64  # 15
}

attributes_dates = ["last_review"]

# Import data
data_frame_original = pd.read_csv(airbnb_data, dtype=attributes_datatype, parse_dates=attributes_dates)

#Fill NAs with zero
data_frame_original.fillna(0, inplace=True)

#Take a smaller sample
data_frame = data_frame_original.sample(frac=0.05)
#data_frame = data_frame_original[:10]

#Get raw data
raw_data = data_frame.get_values()
raw_data = raw_data[:, 4:]
room_types = raw_data[:,[4]]
buroughs = raw_data[:,[0]]
prices = raw_data[:,[5]]
raw_data = np.delete(raw_data,[0,1,4,5,8,12],1)
size = np.size(raw_data,0)

#Normalize numerical data
for j in range(7):
    avg = np.mean(raw_data[:,[j]])
    std = np.std(raw_data[:,[j]])
    
    for i in range(size):
        raw_data[i,j] = (raw_data[i,j] - avg)/std;
        
#Out of k encoding for borough and room type
borough_k_encoding = np.zeros((size,5),dtype=int)
room_k_encoding = np.zeros((size,3),dtype=int)
Y = np.zeros((size,1),dtype=int)

for i in range(size):
    if buroughs[i]=="Bronx":
        borough_k_encoding[i,0]=1
    elif buroughs[i]=="Brooklyn":
        borough_k_encoding[i,1]=1
    elif buroughs[i]=="Manhattan":
        borough_k_encoding[i,2]=1
    elif buroughs[i]=="Queens":
        borough_k_encoding[i,3]=1
    elif buroughs[i]=="Staten Island":
        borough_k_encoding[i,4]=1
    else:
        print("Something is funky")
        
    if room_types[i]=="Private room":
        room_k_encoding[i,0]=1
    elif room_types[i]=="Entire home/apt":
        room_k_encoding[i,1]=1
    elif room_types[i]=="Shared room":
        room_k_encoding[i,2]=1
    else:
        print("Something messed up!")
        
    #Class labels for prices
    if prices[i]<100:
        Y[i]=1
    elif prices[i]<200:
        Y[i]=2
    elif prices[i]<300:
        Y[i]=3
    elif prices[i]<400:
        Y[i]=4
    elif prices[i]<500:
        Y[i]=5
    else:
        Y[i]=6

K = np.concatenate((borough_k_encoding,room_k_encoding),axis=1)
X = np.concatenate((raw_data,K),axis=1)

cols = [1,2,13,14,15]

print("Using columns: ")
x_labels = ["1. Lat","2. Long","3. Min Nights","4. Number Reviews",
            "5. Reviews per month","6. Host Listings","7. Availability",
            "8. Bronx","9. Brooklyn","10. Manhattan","11. Queens","12. Staten Island",
            "13. Private Room","14. Entire Home",
            "15. Shared Room"]
for i in cols:
    print(x_labels[i-1])
for i in range(len(cols)):
    cols[i] = cols[i]-1
X = X[:,cols]
M,N = np.shape(X)
Y = Y.flatten()

Method = 'complete'
Metric = 'euclidean'

Z = linkage(X, method=Method, metric=Metric)

cov_type = 'full' # e.g. 'full' or 'diag'

# define the initialization procedure (initial value of means)
initialization_method = 'random'#  'random' or 'kmeans'
# random signifies random initiation, kmeans means we run a K-means and use the
# result as the starting point. K-means might converge faster/better than  
# random, but might also cause the algorithm to be stuck in a poor local minimum 

# type of covariance, you can try out 'diag' as well
reps = 1
# number of fits with different initalizations, best result will be kept
# Fit Gaussian mixture model

# Maximum number of clusters:
K = 6

# Allocate variables:
Rand1 = np.zeros((K,))
Jaccard1 = np.zeros((K,))
NMI1 = np.zeros((K,))

Rand2 = np.zeros((K,))
Jaccard2 = np.zeros((K,))
NMI2 = np.zeros((K,))

for k in range(1,K):
    # run K-means clustering:
    #cls = Pycluster.kcluster(X,k+1)[0]
    #centroids, cls, inertia = k_means(X,k+1)
    # compute cluster validities:
    
    cls1 = fcluster(Z, criterion='maxclust', t=k)
    gmm = GaussianMixture(n_components=k, covariance_type=cov_type, n_init=reps, 
                          tol=1e-6, reg_covar=1e-6, init_params=initialization_method).fit(X)
    cls2 = gmm.predict(X)
    
    Rand1[k], Jaccard1[k], NMI1[k] = clusterval(Y,cls1)   
    Rand2[k], Jaccard2[k], NMI2[k] = clusterval(Y,cls2)    

        
# Plot results:



figure(1)
title('Cluster validity for Hierarchal')
plot(np.arange(K)+1, Rand1)
plot(np.arange(K)+1, Jaccard1)
plot(np.arange(K)+1, NMI1)
legend(['Rand', 'Jaccard', 'NMI'], loc=4)
show()

figure(2)
title('Cluster validity for GMM')
plot(np.arange(K)+1, Rand2)
plot(np.arange(K)+1, Jaccard2)
plot(np.arange(K)+1, NMI2)
legend(['Rand', 'Jaccard', 'NMI'], loc=4)
show()

