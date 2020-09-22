# -*- coding: utf-8 -*-
"""
Created on Tue Nov 12 10:48:29 2019

@author: Westo
"""

import numpy as np
import xlrd
import matplotlib.pyplot as plt
import pandas as pd
from scipy.linalg import svd
from categoric2numeric import categoric2numeric
from matplotlib.pyplot import figure, plot, xlabel, ylabel, legend, show
import sklearn.linear_model as lm
import sklearn.model_selection as skmd
# =============================================================================
# from toolbox.Toolbox_Python02450.Tools.toolbox_02450 import feature_selector_lr, bmplot, rlr_validate, train_neural_net,\
#     draw_neural_net, visualize_decision_boundary
# =============================================================================
import toolbox_02450
from matplotlib.pyplot import figure, plot, xlabel, ylabel, clim, semilogx, loglog, legend, title, subplot, show, grid
import pprint
import random
import torch

from sklearn.linear_model import LogisticRegression
from sklearn.model_selection import train_test_split


# Again import data
airbnb_data = "AB_NYC_2019.csv"

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

data_frame_original = pd.read_csv(airbnb_data, dtype=attributes_datatype, parse_dates=attributes_dates)
data_frame_original.fillna(0, inplace=True)

print("Size of original dataframe: ", data_frame_original.size)

# TODO TAKE CARE
# Get random part of data to get more sense of visualization:
data_frame = data_frame_original.sample(frac=0.1)

raw_data = data_frame.get_values()
attributes = list(data_frame.columns)

print("Atributes of dataframe: ", attributes)

print("Size of dataframe: ", data_frame.size)

prity_atributes = [
    'id',
    'name',
    'host id',
    'host name',
    'borough',
    'neighbourhood',
    'latitude',
    'longitude',
    'room type',
    'price',
    'minimum nights',
    'review number',
    'last review',
    'rev per month',
    'host listing count',
    'availability']

# Make a list of unique room types and neighbourhoods and unique boroughs
unique_boroughs = data_frame['neighbourhood_group'].unique()
unique_roomtypes = data_frame['room_type'].unique()
unique_neighbourhoods = data_frame['neighbourhood'].unique()

# Try to predict room type:

rtype_dict = dict()
num_to_atribute = dict()

for j,i in enumerate(unique_roomtypes):
    rtype_dict[i] = j
    num_to_atribute[j] = i

result_atributes = (8)
result_data = raw_data[:, result_atributes]
result_data = [rtype_dict[i] for i in result_data]
# print(result_data)
Y = np.array(result_data).T
yy_data = list()
for i in result_data:
    if i == 0:
        yy_data.append(np.array([1,0,0]))
    if i == 1:
        yy_data.append(np.array([0,1,0]))
    if i == 2:
        yy_data.append(np.array([0,0,1]))
YY = np.array(yy_data)
# Y = Y.reshape((Y.shape[0], 1))
print(Y.shape)
print(YY.shape)

# Standarize our data matrix
# One out K for nbh
nbh_data = raw_data[:, (4)]
x_nbh = np.array(nbh_data).T
X_K1, K1_labels = categoric2numeric(x_nbh)

# roomtype_data = raw_data[:, (8)]
# x_rty = np.array(roomtype_data).T
# X_K2, K2_labels = categoric2numeric(x_rty)

# Get other parameters and standardise them
other_params = (9, 15)
other_data = np.array(raw_data[:, other_params])

N, M = other_data.shape

# To get a shape of (n,1) to use in concatenate (only if we only use one additional parameter
if N == 1:
    other_data = other_data.reshape((other_data.shape[0], 1))

other_data = other_data - np.ones((N, 1)) * other_data.mean(axis=0)
other_data = other_data.astype(np.float64)
other_data = other_data * (1 / np.std(other_data, 0))

# Centered around 0. 
# Concatenate all of the data int one matrix

X = np.concatenate((X_K1, other_data), axis=1)
X_labesls = K1_labels + [attributes[i] for i in other_params]

print("Wes")
print(X_labesls)
print("Wes")
print(X[0])
print(X[1])


K = 10
CV = skmd.KFold(K, shuffle=True)

lambda_interval = np.logspace(-8, 2, 50)
print("Here!")
print(lambda_interval)

Error_test_lin = np.empty((K, 1))
Opt_lambdas_lin = np.empty((K, 1))

Error_test_baseline = np.empty((K, 1))

Error_test_ann = np.empty((K, 1))
Opt_h_ann = np.empty((K, 1))

cv_k = 0
for train_index, test_index in CV.split(X, Y):

    X_train = X[train_index]
    y_train = Y[train_index]
    X_test = X[test_index]
    y_test = Y[test_index]

    # Logistic regression
    train_error_rate = np.zeros(len(lambda_interval))
    test_error_rate = np.zeros(len(lambda_interval))
    coefficient_norm = np.zeros(len(lambda_interval))
    for k in range(0, len(lambda_interval)):
        mdl = LogisticRegression(penalty='l2', C=1 / lambda_interval[k],solver = "lbfgs",multi_class="auto", max_iter=10000)

        mdl.fit(X_train, y_train)

        y_train_est = mdl.predict(X_train).T
        y_test_est = mdl.predict(X_test).T

        train_error_rate[k] = np.sum(y_train_est != y_train) / len(y_train)
        test_error_rate[k] = np.sum(y_test_est != y_test) / len(y_test)

        print(k,train_error_rate[k],test_error_rate[k])

        w_est = mdl.coef_[0]
        coefficient_norm[k] = np.sqrt(np.sum(w_est ** 2))

    min_error = np.min(test_error_rate)
    opt_lambda_idx = np.argmin(test_error_rate)
    opt_lambda = lambda_interval[opt_lambda_idx]

    Error_test_lin[cv_k] = min_error
    Opt_lambdas_lin[cv_k] = opt_lambda
    
    print("Look here")
    print(mdl.coef_)
    print("Look here")

    plt.figure(figsize=(8,8))
    #plt.plot(np.log10(lambda_interval), train_error_rate*100)
    #plt.plot(np.log10(lambda_interval), test_error_rate*100)
    #plt.plot(np.log10(opt_lambda), min_error*100, 'o')
    plt.plot(lambda_interval, train_error_rate*100)
    plt.plot(lambda_interval, test_error_rate*100)
    plt.plot(opt_lambda, min_error*100, 'o')
    plt.text(1e-8, 3, "Minimum test error: " + str(np.round(min_error*100,2)) + ' % at 1e' + str(np.round(np.log10(opt_lambda),2)))
    plt.xlabel('Regularization strength, $\log_{10}(\lambda)$')
    plt.ylabel('Error rate (%)')
    plt.title('Classification error')
    plt.legend(['Training error','Test error','Test minimum'],loc='upper right')
    plt.ylim([0, 4])
    plt.grid()
    plt.show()

    plt.figure(figsize=(8,8))
    plt.plot(lambda_interval, coefficient_norm,'k')
    plt.ylabel('L2 Norm')
    plt.xlabel('Regularization strength, $\log_{10}(\lambda)$')
    plt.title('Parameter vector L2 norm')
    plt.grid()
    plt.show()

    

    cv_k += 1


print("Lin reg results")
print("lambdas: ")
print(Opt_lambdas_lin)
print("Errors: ")
print(Error_test_lin)

# Latex table
for index,res in enumerate(zip(Opt_h_ann, Error_test_ann, Opt_lambdas_lin, Error_test_lin, Error_test_baseline)):
    print(str(index)+" & {0:.3f} & {1:.3f} & {2:.3f} & {3:.3f} & {4:.3f}".format(*[i[0] for i in res])+r" \\")