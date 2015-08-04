## Python Script for performing linear regression
## on Stock Cortisol Characterization Results
## This script takes optical density results and performs a linear
## regression on a logarithmic scale

## Requires Scipy and numpy

import numpy as np
from scipy import special, optimize
from scipy import stats

## Data
OD  = np.array([.062,.112,.194,.314,.4,.504,.606,])
C   = np.array([10,5,2.5,1.25,.625,.313,.156,])
LC  = np.log10(C)
#print(OD)
#print(C)
#print(LC)

## Linear Regression
slope, intercept, r_value, p_value, std_err = scipy.stats.linregress(LC, OD)
print(p)
print(R)

