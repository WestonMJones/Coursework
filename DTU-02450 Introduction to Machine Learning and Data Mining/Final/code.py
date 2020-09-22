# -*- coding: utf-8 -*-
"""
Created on Tue Dec 17 04:22:03 2019

@author: Westo
"""

import numpy as np
import pandas as pd

from matplotlib.pyplot import figure, show, scatter, hist, plot, legend, xlabel
from scipy.io import loadmat
from ../toolbox_02450 import clusterplot
from scipy.cluster.hierarchy import linkage, fcluster, dendrogram
from sklearn.decomposition import PCA
from sklearn.mixture import GaussianMixture
from sklearn import model_selection

print(toolbox_02450.__version__)
