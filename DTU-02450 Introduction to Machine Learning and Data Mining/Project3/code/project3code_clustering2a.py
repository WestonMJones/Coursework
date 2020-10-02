# -*- coding: utf-8 -*-
"""
Created on Mon Dec  2 11:27:36 2019

@author: Westo
"""

import numpy as np
import pandas as pd

from matplotlib.pyplot import figure, show, scatter, hist, plot, legend, xlabel
from scipy.io import loadmat
from toolbox_02450 import clusterplot
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

# Range of K's to try
KRange = range(1,21)
T = len(KRange)

covar_type = 'full'       # you can try out 'diag' as well
reps = 4                  # number of fits with different initalizations, best result will be kept
init_procedure = 'kmeans' # 'kmeans' or 'random'

# Allocate variables
BIC = np.zeros((T,))
AIC = np.zeros((T,))
CVE = np.zeros((T,))

# K-fold crossvalidation
CV = model_selection.KFold(n_splits=10,shuffle=True)

for t,K in enumerate(KRange):
        print('Fitting model for K={0}'.format(K))

        # Fit Gaussian mixture model
        gmm = GaussianMixture(n_components=K, covariance_type=covar_type, 
                              n_init=reps, init_params=init_procedure,
                              tol=1e-6, reg_covar=1e-6).fit(X)
        
        # Get BIC and AIC
        BIC[t,] = gmm.bic(X)
        AIC[t,] = gmm.aic(X)

        # For each crossvalidation fold
        for train_index, test_index in CV.split(X):

            # extract training and test set for current CV fold
            X_train = X[train_index]
            X_test = X[test_index]

            # Fit Gaussian mixture model to X_train
            gmm = GaussianMixture(n_components=K, covariance_type=covar_type, n_init=reps).fit(X_train)

            # compute negative log likelihood of X_test
            CVE[t] += -gmm.score_samples(X_test).sum()
            

# Plot results

figure(1); 
plot(KRange, BIC,'-*b')
plot(KRange, AIC,'-xr')
plot(KRange, 2*CVE,'-ok')
legend(['BIC', 'AIC', 'Crossvalidation'])
xlabel('K')
show()