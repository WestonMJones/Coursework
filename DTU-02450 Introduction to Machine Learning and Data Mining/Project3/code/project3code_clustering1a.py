# -*- coding: utf-8 -*-
"""
Created on Mon Dec  2 11:27:36 2019

@author: Westo
"""

import numpy as np
import pandas as pd
from matplotlib.pyplot import figure, show, scatter
from scipy.io import loadmat
from toolbox_02450 import clusterplot
from scipy.cluster.hierarchy import linkage, fcluster, dendrogram

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
raw_data = np.delete(raw_data,[0,1,4,8,12],1)
size = np.size(raw_data,0)

#Transform data by:
#-Dropping irrelevant attributes
#-1 out of k encoding
#-standardizing the other numeric elements
Y = np.zeros((size,1),dtype=int)
room_type_k_encoding = np.zeros((size,3),dtype=int)

for i in range(size):
    if room_types[i]=="Private room":
        room_type_k_encoding[i,0]=1
    elif room_types[i]=="Entire home/apt":
        room_type_k_encoding[i,1]=1
    elif room_types[i]=="Shared room":
        room_type_k_encoding[i,2]=1
    else:
        print("Something is funky")
        
    if buroughs[i,0]=="Bronx":
        Y[i] = 0
    elif buroughs[i,0]=="Brooklyn":
        Y[i] = 1
    elif buroughs[i,0]=="Manhattan":
        Y[i] = 2
    elif buroughs[i,0]=="Queens":
        Y[i] = 3
    elif buroughs[i,0]=="Staten Island":
        Y[i] = 4
    else:
        print("Something else is funky")

for j in range(8):
    avg = np.mean(raw_data[:,[j]])
    std = np.std(raw_data[:,[j]])
    
    for i in range(size):
        raw_data[i,j] = (raw_data[i,j] - avg)/std;

X = np.concatenate((raw_data,room_type_k_encoding),axis=1)
M,N = np.shape(X)

cols = [1,2,3,4,5,6,7,8,9,10,11]

print("Using columns: ")
x_labels = ["Lat","Long","Price","Min Nights","Number Reviews",
            "Reviews per month","Host Listings","Availability","Private Room","Entire Home",
            "Shared Room"]
for i in cols:
    print(x_labels[i-1])
for i in range(len(cols)):
    cols[i] = cols[i]-1
X = X[:,cols]
print(X)

# Perform hierarchical/agglomerative clustering on data matrix
Method = 'single'
Metric = 'euclidean'

Z = linkage(X, method=Method, metric=Metric)

# Compute and display clusters by thresholding the dendrogram
Maxclust = 5
cls = fcluster(Z, criterion='maxclust', t=Maxclust)
figure(1)
clusterplot(X, cls.reshape(cls.shape[0],1), y=Y)

# Display dendrogram
max_display_levels=6
figure(2,figsize=(10,4))
dendrogram(Z, truncate_mode='level', p=max_display_levels)

show()




    





