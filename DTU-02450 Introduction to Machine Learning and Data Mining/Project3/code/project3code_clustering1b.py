# -*- coding: utf-8 -*-
"""
Created on Mon Dec  2 11:27:36 2019

@author: Westo
"""

import numpy as np
import pandas as pd

from matplotlib.pyplot import figure, show, scatter, hist
from scipy.io import loadmat
from toolbox_02450 import clusterplot
from scipy.cluster.hierarchy import linkage, fcluster, dendrogram
from sklearn.decomposition import PCA


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
data_frame = data_frame_original.sample(frac=0.3)
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
        Y[i]=0
    elif prices[i]<200:
        Y[i]=1
    elif prices[i]<300:
        Y[i]=2
    elif prices[i]<400:
        Y[i]=3
    elif prices[i]<500:
        Y[i]=4
    else:
        Y[i]=5

K = np.concatenate((borough_k_encoding,room_k_encoding),axis=1)
X = np.concatenate((raw_data,K),axis=1)

cols = [1,2,5,13,14,15]

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

# Do PCA for plot
pca = PCA(n_components=2)
PCASpace = pca.fit_transform(X)

# Perform hierarchical/agglomerative clustering on data matrix
Method = 'complete'
Metric = 'euclidean'

Z = linkage(X, method=Method, metric=Metric)

# Compute and display clusters by thresholding the dendrogram
Maxclust = 6
cls = fcluster(Z, criterion='maxclust', t=Maxclust)
figure(1)
clusterplot(PCASpace, cls.reshape(cls.shape[0],1), y=Y)

# Display dendrogram
max_display_levels=6
figure(2,figsize=(10,4))
dendrogram(Z, truncate_mode='level', p=max_display_levels)

show()





